class_name SakuraPlayer
extends Node2D

signal shot_requested(origin: Vector2, facing: int)
signal died
signal hp_changed(current_hp: int, maximum_hp: int)
signal shot_count_changed(active: int)

const BODY_SIZE := Vector2(40, 80)
const MAX_HP := 15
const MAX_X_SPEED := 4.0

const NORMAL_TEXTURES := [
	preload("res://assets/player/player_idle.png"),
	preload("res://assets/player/player_walk2.png"),
	preload("res://assets/player/player_jump.png"),
	preload("res://assets/player/player_walk4.png"),
	preload("res://assets/player/player_walk5.png"),
]
const FIRING_TEXTURES := [
	preload("res://assets/player/player_fire_idle.png"),
	preload("res://assets/player/player_fire_walk2.png"),
	preload("res://assets/player/player_fire_jump.png"),
	preload("res://assets/player/player_fire_walk4.png"),
	preload("res://assets/player/player_fire_walk5.png"),
]
const FLASH_SHADER := preload("res://shaders/white_flash.gdshader")
const WALK_SEQUENCE := [0, 1, 2, 1, 0, 3, 4, 3]
const ANIMATION_SPEED := 8

var terrain: SakuraTerrain
var sprite: Sprite2D
var flash_material: ShaderMaterial
var gameplay_active := false
var scripted_animation_active := false
var presentation_hidden := false
var grounded := true
var facing := 1
var x_speed := 0.0
var y_speed := 0.0
var ascent_ticks := 0
var fall_ticks := 0
var landed_this_tick := false
var jump_latched := false
var walk_tick := 0
var firing_ticks := 0
var fire_interval := 25
var fire_counter := fire_interval
var active_shots := 0
var hp := MAX_HP
var lives := 5
var immunity_ticks := 0
var dead := false
var water_surface_y := -1.0
var in_water := false


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	flash_material = ShaderMaterial.new()
	flash_material.shader = FLASH_SHADER
	sprite.material = flash_material
	add_child(sprite)
	_update_sprite(0)


func setup(map_terrain: SakuraTerrain) -> void:
	terrain = map_terrain
	hp = MAX_HP
	hp_changed.emit(hp, MAX_HP)


func set_water_surface(surface_y: float, starts_in_water: bool = false) -> void:
	water_surface_y = surface_y
	in_water = starts_in_water or (water_surface_y >= 0.0 and position.y + 24.0 >= water_surface_y)


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func set_scripted_animation_active(value: bool) -> void:
	scripted_animation_active = value


func set_presentation_hidden(value: bool) -> void:
	presentation_hidden = value
	if sprite != null:
		sprite.visible = not value


func get_hit_rect() -> Rect2:
	return Rect2(position, BODY_SIZE)


func get_center() -> Vector2:
	return position + BODY_SIZE * 0.5


func _hit_rect_offset(offset: Vector2) -> Rect2:
	return Rect2(position + offset, BODY_SIZE)


func _physics_process(_delta: float) -> void:
	if dead:
		return
	landed_this_tick = false
	_update_immunity()
	if not gameplay_active:
		if not scripted_animation_active:
			_update_sprite(0)
		return

	_update_water_state()
	var left := Input.is_action_pressed("move_left")
	var right := Input.is_action_pressed("move_right")
	var direction := int(right) - int(left)
	_update_horizontal(direction)
	_update_jump()
	_update_fire()
	_update_animation(direction)


func _update_horizontal(direction: int) -> void:
	if direction == 0:
		x_speed = 0.0
		return
	if signf(x_speed) != 0.0 and signf(x_speed) != float(direction):
		x_speed = 0.0
	if absf(x_speed) < 1.0:
		x_speed += 0.2 * direction
	else:
		x_speed += 1.0 * direction
	x_speed = clampf(x_speed, -MAX_X_SPEED, MAX_X_SPEED)
	facing = direction
	var target_x := int(position.x + x_speed)
	_move_horizontal(target_x - int(position.x))
	if grounded and not terrain.rect_hits_solid(_hit_rect_offset(Vector2(0, 1))):
		grounded = false
		fall_ticks = 0
		y_speed = 0.0


func _update_jump() -> void:
	var jump_pressed := Input.is_action_pressed("jump")
	if not jump_pressed:
		jump_latched = false

	if grounded and jump_pressed and not jump_latched:
		jump_latched = true
		grounded = false
		ascent_ticks = 1
		fall_ticks = 0
		y_speed = -2.0
		_move_vertical(y_speed * 5.0)
		return

	if grounded:
		y_speed = 0.0
		ascent_ticks = 0
		fall_ticks = 0
		return

	if y_speed < 0.0:
		if not jump_pressed:
			y_speed = 0.4
			fall_ticks = 0
		else:
			ascent_ticks += 1
			if ascent_ticks <= (2 if in_water else 10):
				y_speed += 0.10
			elif ascent_ticks <= 20:
				y_speed += 0.06
			else:
				y_speed += 0.04
			if y_speed >= 0.0:
				fall_ticks = 0
		_move_vertical(y_speed * 5.0)
	else:
		fall_ticks += 1
		if in_water:
			y_speed += 0.04
		elif fall_ticks <= 10:
			y_speed += 0.04
		elif fall_ticks <= 20:
			y_speed += 0.06
		else:
			y_speed += 0.10
		y_speed = minf(y_speed, 1.2 if in_water else 2.0)
		_move_vertical(y_speed * 5.0)


func _update_water_state() -> void:
	if water_surface_y < 0.0:
		in_water = false
		return
	if not in_water and position.y + 24.0 >= water_surface_y:
		in_water = true
	elif in_water and position.y + 29.0 < water_surface_y:
		in_water = false


func _move_horizontal(amount: float) -> void:
	var remaining := absf(amount)
	var direction := signf(amount)
	while remaining > 0.0001:
		var step := minf(1.0, remaining) * direction
		var candidate := _hit_rect_offset(Vector2(step, 0))
		if terrain.rect_hits_solid(candidate):
			x_speed = 0.0
			break
		position.x += step
		remaining -= absf(step)
	position.x = maxf(0.0, position.x)


func _move_vertical(amount: float) -> void:
	var remaining := absf(amount)
	var direction := signf(amount)
	while remaining > 0.0001:
		var step := minf(1.0, remaining) * direction
		var candidate := _hit_rect_offset(Vector2(0, step))
		if terrain.rect_hits_solid(candidate):
			if direction > 0.0:
				var tile_size := float(SakuraTerrain.TILE_SIZE)
				var surface_y := floorf(candidate.end.y / tile_size) * tile_size
				position.y = surface_y - BODY_SIZE.y
				grounded = true
				fall_ticks = 0
				landed_this_tick = true
			else:
				grounded = false
				fall_ticks = 0
			if direction > 0.0:
				y_speed = 0.0
			break
		position.y += step
		remaining -= absf(step)
		if direction > 0.0 and terrain.rect_touches_lethal_floor(get_hit_rect()):
			_die()
			return
	if position.y > terrain.world_size.y + 80.0:
		_die()


func _update_fire() -> void:
	if firing_ticks > 0:
		firing_ticks -= 1
	var pressed := Input.is_action_pressed("fire")
	var just_pressed := Input.is_action_just_pressed("fire")
	if pressed:
		fire_counter += 1
		if active_shots < 4 and (just_pressed or fire_counter >= fire_interval):
			_fire()
	else:
		fire_counter = mini(fire_counter + 1, fire_interval)


func _fire() -> void:
	var origin := position + Vector2(40 if facing > 0 else -21, 35)
	active_shots += 1
	fire_counter = 0
	firing_ticks = 5
	shot_count_changed.emit(active_shots)
	shot_requested.emit(origin, facing)


func projectile_ended() -> void:
	active_shots = maxi(0, active_shots - 1)
	shot_count_changed.emit(active_shots)


func _update_animation(direction: int) -> void:
	var frame_index := 0
	if not grounded:
		frame_index = 2
	elif landed_this_tick:
		var landing_sequence_frame := WALK_SEQUENCE.find(2)
		walk_tick = landing_sequence_frame * ANIMATION_SPEED
		frame_index = 2
	elif direction != 0:
		walk_tick = (walk_tick + 1) % (WALK_SEQUENCE.size() * ANIMATION_SPEED)
		var current_frame := int(walk_tick / float(ANIMATION_SPEED))
		frame_index = WALK_SEQUENCE[current_frame]
	else:
		walk_tick = 0
	_update_sprite(frame_index)


func _update_sprite(frame_index: int) -> void:
	if sprite == null:
		return
	if dead or presentation_hidden:
		sprite.visible = false
		return
	if immunity_ticks > 0 and immunity_ticks % 4 >= 2:
		sprite.visible = false
		return
	sprite.visible = true
	var textures := FIRING_TEXTURES if Input.is_action_pressed("fire") else NORMAL_TEXTURES
	sprite.texture = textures[frame_index]
	flash_material.set_shader_parameter("flash_amount", 1.0 if immunity_ticks > 0 and immunity_ticks % 8 == 0 else 0.0)
	sprite.flip_h = facing < 0
	sprite.position.x = -10.0 if facing < 0 else 0.0


func _update_immunity() -> void:
	if immunity_ticks > 0:
		immunity_ticks -= 1


func take_damage(amount: int) -> void:
	if dead or immunity_ticks > 0 or amount <= 0:
		return
	hp -= amount
	immunity_ticks = 80
	hp_changed.emit(hp, MAX_HP)
	if hp <= 0:
		_die()


func add_health(amount: int) -> void:
	if dead:
		return
	hp = mini(MAX_HP, hp + amount)
	hp_changed.emit(hp, MAX_HP)


func add_life() -> void:
	var progress: Variant = get_node("/root/SakuraProgress")
	lives = progress.add_life()


func scripted_step_right(amount: float) -> void:
	scripted_step(1, amount)


func scripted_step(direction: int, amount: float) -> void:
	if dead:
		return
	facing = 1 if direction >= 0 else -1
	position.x += facing * amount
	walk_tick = (walk_tick + 1) % (WALK_SEQUENCE.size() * ANIMATION_SPEED)
	var current_frame := int(walk_tick / float(ANIMATION_SPEED))
	_update_sprite(WALK_SEQUENCE[current_frame])


func _die() -> void:
	if dead:
		return
	dead = true
	var progress: Variant = get_node("/root/SakuraProgress")
	lives = progress.lose_life()
	gameplay_active = false
	sprite.visible = false
	died.emit()
