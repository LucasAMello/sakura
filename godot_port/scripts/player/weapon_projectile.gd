class_name WeaponProjectile
extends Node2D

signal finished

const MAX_PLAYER_DISTANCE := 640.0
const SOURCE_UPDATE_INTERVAL := 4
const SOURCE_MOTION_SCALE := 1.0 / SOURCE_UPDATE_INTERVAL
const ImpactParticleScript = preload("res://scripts/player/weapon_impact_particle.gd")
const WIND_TEXTURES := [
	preload("res://assets/player/wind_shot_1.png"),
	preload("res://assets/player/wind_shot_2.png"),
	preload("res://assets/player/wind_shot_3.png"),
]
const THUNDER_TEXTURES := [
	preload("res://assets/player/thunder_shot_1.png"),
	preload("res://assets/player/thunder_shot_2.png"),
	preload("res://assets/player/thunder_shot_3.png"),
	preload("res://assets/player/thunder_shot_4.png"),
]
const FIRE_TEXTURES := [
	preload("res://assets/player/fire_shot_1.png"),
	preload("res://assets/player/fire_shot_2.png"),
	preload("res://assets/player/fire_hit_1.png"),
	preload("res://assets/player/fire_hit_2.png"),
	preload("res://assets/player/fire_hit_3.png"),
	preload("res://assets/player/fire_hit_4.png"),
	preload("res://assets/player/fire_hit_5.png"),
]
const WATER_HIT_TEXTURES := [
	preload("res://assets/player/water_hit_1.png"),
	preload("res://assets/player/water_hit_2.png"),
	preload("res://assets/player/water_hit_3.png"),
	preload("res://assets/player/water_hit_4.png"),
	preload("res://assets/player/water_hit_5.png"),
	preload("res://assets/player/water_hit_6.png"),
	preload("res://assets/player/water_hit_7.png"),
	preload("res://assets/player/water_hit_8.png"),
	preload("res://assets/player/water_hit_9.png"),
]

var terrain: SakuraTerrain
var player: SakuraPlayer
var stage: Node
var weapon_id := 2
var move_direction := 1
var sprite: Sprite2D
var body_size := Vector2(10, 10)
var velocity := Vector2.ZERO
var life_ticks := 0
var ending := false
var ending_ticks := 0
var finish_emitted := false
var water_impact_kind := 3
var impact_particles_spawned := false


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_PAUSABLE
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, owner_player: SakuraPlayer, owner_stage: Node, direction: int, selected_weapon: int) -> void:
	terrain = map_terrain
	player = owner_player
	stage = owner_stage
	move_direction = 1 if direction >= 0 else -1
	weapon_id = selected_weapon
	sprite.flip_h = move_direction < 0
	match weapon_id:
		2:
			body_size = Vector2(65, 32)
			velocity.x = move_direction * 25.0 * SOURCE_MOTION_SCALE
			sprite.texture = WIND_TEXTURES[0]
		3:
			body_size = Vector2(30, 30)
			velocity = Vector2(move_direction * 20.0, 12.0) * SOURCE_MOTION_SCALE
			sprite.texture = preload("res://assets/player/shadow_shot.png")
			_resolve_shadow_spawn()
		4:
			body_size = Vector2(16, 16)
			velocity.x = move_direction * 20.0 * SOURCE_MOTION_SCALE
			sprite.texture = THUNDER_TEXTURES[0]
		5:
			body_size = Vector2(29, 29)
			velocity = Vector2(move_direction * 20.0, -4.0) * SOURCE_MOTION_SCALE
			sprite.texture = preload("res://assets/player/water_shot.png")
		6:
			body_size = Vector2(34, 24)
			velocity.x = move_direction * 32.0 * SOURCE_MOTION_SCALE
			sprite.texture = FIRE_TEXTURES[0]
		7:
			body_size = Vector2(47, 19)
			sprite.texture = preload("res://assets/world6/boss_attack_4.png")


func _physics_process(_delta: float) -> void:
	if weapon_id == 3 and _shadow_outside_vertical_bounds():
		_emit_finished()
		queue_free()
		return
	if ending:
		_update_ending()
		return
	life_ticks += 1
	_update_animation()
	match weapon_id:
		2, 4, 6:
			_move_and_collide(velocity)
		3:
			_move_shadow()
			if _shadow_outside_vertical_bounds():
				_emit_finished()
				queue_free()
				return
		5:
			if (life_ticks - 1) % (3 * SOURCE_UPDATE_INTERVAL) == 2 * SOURCE_UPDATE_INTERVAL:
				velocity.y += 4.0 * SOURCE_MOTION_SCALE
			_move_water()
		7:
			if (life_ticks - 1) % SOURCE_UPDATE_INTERVAL == 0:
				velocity.x += move_direction * 0.5 * SOURCE_MOTION_SCALE
				if (life_ticks - 1) % (3 * SOURCE_UPDATE_INTERVAL) == 2 * SOURCE_UPDATE_INTERVAL:
					velocity.x *= 2.0
				velocity.x = clampf(velocity.x, -40.0 * SOURCE_MOTION_SCALE, 40.0 * SOURCE_MOTION_SCALE)
			_move_and_collide(Vector2(velocity.x, 0.0))
	if not ending and (not is_instance_valid(player) or absf(position.x - player.position.x) > MAX_PLAYER_DISTANCE or life_ticks >= 240):
		_end()


func _shadow_outside_vertical_bounds() -> bool:
	if position.y < 0.0 or position.y >= terrain.world_size.y:
		return true
	if is_instance_valid(player):
		var vertical_distance := position.y - player.position.y
		return vertical_distance < -480.0 or vertical_distance > 560.0
	return false


func _resolve_shadow_spawn() -> void:
	var requested_x := position.x
	position.x = player.position.x + (SakuraPlayer.BODY_SIZE.x - body_size.x) * 0.5
	if _terrain_collision_after(Vector2.ZERO):
		_end()
		return
	var remaining := absf(requested_x - position.x)
	var direction := signf(requested_x - position.x)
	while remaining > 0.0:
		var step := minf(1.0, remaining)
		var offset := Vector2(direction * step, 0.0)
		if _terrain_collision_after(offset):
			velocity.x *= -1.0
			sprite.flip_h = velocity.x < 0.0
			get_node("/root/AudioManager").play_sfx("quicar")
			return
		position += offset
		remaining -= step


func _move_shadow() -> void:
	if _terrain_collision_after(Vector2.ZERO):
		_end()
		return
	var horizontal := Vector2(velocity.x, 0.0)
	if _terrain_collision_after(horizontal):
		velocity.x *= -1.0
		sprite.flip_h = velocity.x < 0.0
		get_node("/root/AudioManager").play_sfx("quicar")
	else:
		position += horizontal
	if _terrain_collision_after(Vector2(0.0, velocity.y)):
		velocity.y *= -1.0
		get_node("/root/AudioManager").play_sfx("quicar")
	else:
		position.y += velocity.y
	if stage.damage_enemy_in_rect(Rect2(position, body_size), _damage(), weapon_id):
		_end(true)


func _move_and_collide(amount: Vector2) -> void:
	var distance := amount.length()
	var steps := maxi(1, ceili(distance / 2.0))
	var step := amount / float(steps)
	for _index in range(steps):
		position += step
		var rect := Rect2(position, body_size)
		if stage.projectile_hits_solid(rect) or stage.damage_enemy_in_rect(rect, _damage(), weapon_id):
			_end(true)
			return


func _move_water() -> void:
	if _move_water_axis(Vector2(velocity.x, 0.0), 1):
		return
	_move_water_axis(Vector2(0.0, velocity.y), 2)


func _move_water_axis(amount: Vector2, impact_kind: int) -> bool:
	var distance := amount.length()
	var steps := maxi(1, ceili(distance / 2.0))
	var step := amount / float(steps)
	for _index in range(steps):
		position += step
		var rect := Rect2(position, body_size)
		if stage.projectile_hits_solid(rect) or stage.damage_enemy_in_rect(rect, _damage(), weapon_id):
			water_impact_kind = impact_kind
			_end(true)
			return true
	return false


func _terrain_collision_after(offset: Vector2) -> bool:
	return stage.projectile_hits_solid(Rect2(position + offset, body_size))


func _damage() -> int:
	match weapon_id:
		2, 4, 7:
			return 2
		3, 6:
			return 3
	return 1


func _update_animation() -> void:
	if weapon_id == 2:
		var wind_frame := int(life_ticks / 6.0) % WIND_TEXTURES.size()
		sprite.texture = WIND_TEXTURES[wind_frame]
	elif weapon_id == 4:
		sprite.texture = THUNDER_TEXTURES[life_ticks % THUNDER_TEXTURES.size()]
	elif weapon_id == 6:
		sprite.texture = FIRE_TEXTURES[int(life_ticks / 4.0) % 2]


func _update_ending() -> void:
	ending_ticks += 1
	match weapon_id:
		2:
			position.x += move_direction * 10.0 * SOURCE_MOTION_SCALE
			sprite.modulate.a = 1.0 - float(ending_ticks) / 32.0
			if ending_ticks >= 32:
				queue_free()
		3:
			position += velocity * 0.25
			sprite.modulate.a = 1.0 - float(ending_ticks) / 32.0
			if ending_ticks >= 32:
				_emit_finished()
				queue_free()
		5:
			_update_water_impact()
		6:
			var frame := mini(2 + int(ending_ticks / 2.0), FIRE_TEXTURES.size() - 1)
			sprite.texture = FIRE_TEXTURES[frame]
			if ending_ticks >= 10:
				queue_free()
		7:
			if not impact_particles_spawned:
				impact_particles_spawned = true
				_spawn_ice_particles()
			queue_free()
		_:
			queue_free()


func _update_water_impact() -> void:
	var first_frame := (water_impact_kind - 1) * 3
	if ending_ticks == 1:
		sprite.texture = WATER_HIT_TEXTURES[first_frame]
		if water_impact_kind == 1:
			if move_direction > 0:
				position.x += 7.0
			body_size = Vector2(22, 29)
		elif water_impact_kind == 2:
			position.y += 7.0
			body_size = Vector2(29, 22)
		else:
			body_size = Vector2(29, 22)
	elif ending_ticks == 4:
		sprite.texture = WATER_HIT_TEXTURES[first_frame + 1]
	elif ending_ticks == 8:
		sprite.texture = WATER_HIT_TEXTURES[first_frame + 2]
		_spawn_water_particles()
	elif ending_ticks >= 12:
		queue_free()


func _spawn_water_particles() -> void:
	if water_impact_kind == 1:
		_spawn_impact_particle(ImpactParticleScript.Kind.WATER_DOWN, position, -move_direction * 13.0)
		_spawn_impact_particle(ImpactParticleScript.Kind.WATER_DOWN, position + Vector2(0, 15), -move_direction * 8.0)
	else:
		var y_offset := 16.0 if water_impact_kind == 3 else 0.0
		_spawn_impact_particle(ImpactParticleScript.Kind.WATER_UP, position + Vector2(0, y_offset), 8.0)
		_spawn_impact_particle(ImpactParticleScript.Kind.WATER_UP, position + Vector2(15, y_offset), -8.0)


func _spawn_ice_particles() -> void:
	for index in range(4):
		var horizontal_speed := float(randi_range(1, 2)) * (-1.0 if index % 2 == 0 else 1.0)
		_spawn_impact_particle(ImpactParticleScript.Kind.ICE, position + Vector2(randi_range(0, 14), randi_range(0, 4)), horizontal_speed)


func _spawn_impact_particle(kind: int, spawn_position: Vector2, horizontal_speed: float) -> void:
	var particle: WeaponImpactParticle = ImpactParticleScript.new()
	particle.position = spawn_position
	particle.z_index = z_index
	get_parent().add_child(particle)
	particle.configure(terrain, stage, kind, horizontal_speed)


func _end(play_impact_sound: bool = false) -> void:
	if ending:
		return
	if play_impact_sound:
		match weapon_id:
			5:
				get_node("/root/AudioManager").play_sfx("splaash")
			6:
				get_node("/root/AudioManager").play_sfx("haduex")
			7:
				get_node("/root/AudioManager").play_sfx_near_player("iceanim", position, player.position)
	ending = true
	if weapon_id != 3:
		_emit_finished()


func _emit_finished() -> void:
	if finish_emitted:
		return
	finish_emitted = true
	finished.emit()


func _exit_tree() -> void:
	_emit_finished()
