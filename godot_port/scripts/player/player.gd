class_name SakuraPlayer
extends Node2D

signal shot_requested(origin: Vector2, facing: int, weapon_id: int)
signal died
signal hp_changed(current_hp: int, maximum_hp: int)
signal shot_count_changed(active: int)
signal water_state_changed(entered_water: bool)

const BODY_SIZE := Vector2(40, 80)
const MAX_HP := 15
const MAX_SUPPORTED_HP := 20
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
const NORMAL_FRAME_FILES := ["idle.png", "walk2.png", "jump.png", "walk4.png", "walk5.png"]
const FIRING_FRAME_FILES := ["fire_idle.png", "fire_walk2.png", "fire_jump.png", "fire_walk4.png", "fire_walk5.png"]
const WEAPON_SPRITE_DIRECTORIES := {
	2: "weapon2_wind",
	3: "weapon3_shadow",
	4: "weapon4_thunder",
	5: "weapon5_water",
	6: "weapon6_fire",
	7: "weapon7_ice",
}
const FLASH_SHADER := preload("res://shaders/white_flash.gdshader")
const ATTACK_OVERLAY_TEXTURE := preload("res://assets/player/attack_overlay.png")
const WALK_SEQUENCE := [0, 1, 2, 1, 0, 3, 4, 3]
const ANIMATION_SPEED := 8
const WEAPON_INTERVALS := {1: 25, 2: 100, 3: 1, 4: 100, 5: 80, 6: 140, 7: 100}

var terrain: SakuraTerrain
var sprite: Sprite2D
var attack_overlay: Sprite2D
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
var jump_blocked_until_release := false
var walk_tick := 0
var firing_ticks := 0
var fire_interval := 25
var fire_counter := fire_interval
var active_shots := 0
var current_weapon := 1
var normal_textures_by_weapon: Dictionary = {1: NORMAL_TEXTURES}
var firing_textures_by_weapon: Dictionary = {1: FIRING_TEXTURES}
var hp := MAX_HP
var maximum_hp := MAX_HP
var lives := 5
var immunity_ticks := 0
var dead := false
var water_surface_y := -1.0
var in_water := false


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	_load_weapon_sprite_sets()
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	flash_material = ShaderMaterial.new()
	flash_material.shader = FLASH_SHADER
	sprite.material = flash_material
	add_child(sprite)
	attack_overlay = Sprite2D.new()
	attack_overlay.centered = false
	attack_overlay.texture = ATTACK_OVERLAY_TEXTURE
	attack_overlay.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	attack_overlay.visible = false
	add_child(attack_overlay)
	_update_sprite(0)


func _load_weapon_sprite_sets() -> void:
	for weapon_id in range(2, 8):
		var directory: String = WEAPON_SPRITE_DIRECTORIES[weapon_id]
		var normal_set: Array[Texture2D] = []
		var firing_set: Array[Texture2D] = []
		for file_name in NORMAL_FRAME_FILES:
			normal_set.append(load("res://assets/player/%s/%s" % [directory, file_name]))
		for file_name in FIRING_FRAME_FILES:
			firing_set.append(load("res://assets/player/%s/%s" % [directory, file_name]))
		normal_textures_by_weapon[weapon_id] = normal_set
		firing_textures_by_weapon[weapon_id] = firing_set


func setup(map_terrain: SakuraTerrain, initial_maximum_hp: int = MAX_HP) -> void:
	terrain = map_terrain
	maximum_hp = clampi(initial_maximum_hp, MAX_HP, MAX_SUPPORTED_HP)
	hp = maximum_hp
	select_weapon(get_node("/root/SakuraProgress").selected_weapon)
	hp_changed.emit(hp, maximum_hp)


func set_maximum_hp(value: int) -> void:
	maximum_hp = clampi(value, MAX_HP, MAX_SUPPORTED_HP)
	hp = mini(hp, maximum_hp)
	hp_changed.emit(hp, maximum_hp)


func set_water_surface(surface_y: float, starts_in_water: bool = false) -> void:
	water_surface_y = surface_y
	in_water = starts_in_water or (water_surface_y >= 0.0 and position.y + 24.0 >= water_surface_y)


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func block_jump_until_release() -> void:
	jump_blocked_until_release = true


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


func get_normal_frame_texture(frame_index: int) -> Texture2D:
	var textures: Array = normal_textures_by_weapon.get(current_weapon, NORMAL_TEXTURES)
	return textures[frame_index]


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
	_update_weapon_selection()
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
	if jump_blocked_until_release:
		if jump_pressed:
			jump_pressed = false
		else:
			jump_blocked_until_release = false
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
	var was_in_water := in_water
	if water_surface_y < 0.0:
		in_water = false
	else:
		if not in_water and position.y + 24.0 >= water_surface_y:
			in_water = true
		elif in_water and position.y + 29.0 < water_surface_y:
			in_water = false
	if in_water != was_in_water:
		water_state_changed.emit(in_water)


func _move_horizontal(amount: float) -> void:
	var remaining := absf(amount)
	var direction := signf(amount)
	while remaining > 0.0001:
		var step := minf(1.0, remaining) * direction
		var candidate := _hit_rect_offset(Vector2(step, 0))
		var slope_supported := grounded and terrain.rect_hits_slope(_hit_rect_offset(Vector2(0, 1)))
		if terrain.rect_hits_solid(candidate):
			var climbed := false
			if grounded and terrain.rect_hits_slope(candidate):
				for rise in range(1, 3):
					if not terrain.rect_hits_solid(_hit_rect_offset(Vector2(0, -rise))) and not terrain.rect_hits_solid(_hit_rect_offset(Vector2(step, -rise))):
						position.y -= rise
						climbed = true
						break
			if not climbed:
				x_speed = 0.0
				break
		position.x += step
		if slope_supported:
			for drop in range(1, 4):
				if terrain.rect_hits_solid(_hit_rect_offset(Vector2(0, drop))):
					position.y += drop - 1
					break
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
				position.y = floorf(candidate.end.y - 0.001) - BODY_SIZE.y
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
		var shot_limit := 4 if current_weapon == 1 or current_weapon == 4 else 1
		var shot_available := current_weapon == 2 or active_shots < shot_limit
		var cooldown_ready := fire_counter >= fire_interval or (just_pressed and current_weapon != 2)
		if shot_available and cooldown_ready:
			_fire()
	else:
		fire_counter = mini(fire_counter + 1, fire_interval)


func _fire() -> void:
	var origin := _weapon_origin()
	if current_weapon != 2:
		active_shots += 1
	fire_counter = 0
	firing_ticks = 5
	shot_count_changed.emit(active_shots)
	shot_requested.emit(origin, facing, current_weapon)


func _weapon_origin() -> Vector2:
	match current_weapon:
		2:
			return position + Vector2(25 if facing > 0 else -46, 20)
		3:
			return position + Vector2(50 if facing > 0 else -21, 0)
		4:
			return position + Vector2(40 if facing > 0 else -21, 30)
		5:
			return position + Vector2(40 if facing > 0 else -21, 20)
		6:
			return position + Vector2(40 if facing > 0 else -21, 28)
		7:
			return position + Vector2(40 if facing > 0 else -21, 30)
	return position + Vector2(40 if facing > 0 else -21, 35)


func _update_weapon_selection() -> void:
	if Input.is_action_pressed("fire"):
		return
	if Input.is_action_just_pressed("weapon_next"):
		_cycle_weapon(1)
	elif Input.is_action_just_pressed("weapon_previous"):
		_cycle_weapon(-1)
	else:
		for weapon_id in range(1, 8):
			if Input.is_action_just_pressed("weapon_%d" % weapon_id):
				_select_weapon(weapon_id)
				break


func _cycle_weapon(direction: int) -> void:
	var candidate := current_weapon
	for _index in range(7):
		candidate = wrapi(candidate - 1 + direction, 0, 7) + 1
		if get_node("/root/SakuraProgress").is_weapon_unlocked(candidate):
			_select_weapon(candidate)
			return


func cycle_weapon(direction: int) -> void:
	_cycle_weapon(direction)


func select_weapon(weapon_id: int) -> void:
	_select_weapon(weapon_id)


func _select_weapon(weapon_id: int) -> void:
	if not get_node("/root/SakuraProgress").is_weapon_unlocked(weapon_id):
		return
	current_weapon = weapon_id
	get_node("/root/SakuraProgress").selected_weapon = weapon_id
	fire_interval = WEAPON_INTERVALS[current_weapon]
	fire_counter = fire_interval


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
		attack_overlay.visible = false
		return
	if immunity_ticks > 0 and immunity_ticks % 4 >= 2:
		sprite.visible = false
		attack_overlay.visible = false
		return
	sprite.visible = true
	var firing := gameplay_active and Input.is_action_pressed("fire")
	var texture_sets: Dictionary = firing_textures_by_weapon if firing else normal_textures_by_weapon
	var textures: Array = texture_sets.get(current_weapon, NORMAL_TEXTURES)
	sprite.texture = textures[frame_index]
	flash_material.set_shader_parameter("flash_amount", 1.0 if immunity_ticks > 0 and immunity_ticks % 8 == 0 else 0.0)
	sprite.flip_h = facing < 0
	sprite.position.x = -10.0 if facing < 0 else 0.0
	attack_overlay.visible = firing
	attack_overlay.flip_h = facing < 0
	attack_overlay.position = Vector2(
		26.0 if facing < 0 else 2.0,
		28.0 if (frame_index == 2 or frame_index == 4) else 26.0
	)


func _update_immunity() -> void:
	if immunity_ticks > 0:
		immunity_ticks -= 1


func take_damage(amount: int) -> void:
	if dead or immunity_ticks > 0 or amount <= 0:
		return
	hp -= amount
	immunity_ticks = 80
	hp_changed.emit(hp, maximum_hp)
	if hp <= 0:
		_die()


func add_health(amount: int) -> void:
	if dead:
		return
	hp = mini(maximum_hp, hp + amount)
	hp_changed.emit(hp, maximum_hp)


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
	attack_overlay.visible = false
	died.emit()
