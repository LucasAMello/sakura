class_name FinalBossProjectile
extends Node2D

signal fire_orbit_finished

const BALL_FRAMES := [
	preload("res://assets/world7/last_ball_1.png"), preload("res://assets/world7/last_ball_2.png"),
	preload("res://assets/world7/last_ball_3.png"), preload("res://assets/world7/last_ball_4.png"),
]
const SMALL_FRAMES := [
	preload("res://assets/world7/last_small_1.png"), preload("res://assets/world7/last_small_2.png"),
	preload("res://assets/world7/last_small_3.png"), preload("res://assets/world7/last_small_4.png"),
]
const THUNDER_FRAMES := [
	preload("res://assets/world7/thunder_shot_1.png"), preload("res://assets/world7/thunder_shot_2.png"),
	preload("res://assets/world7/thunder_shot_3.png"),
]
const FIRE_FRAMES := [
	preload("res://assets/world7/fire_1.png"), preload("res://assets/world7/fire_2.png"),
	preload("res://assets/world7/fire_3.png"), preload("res://assets/world7/fire_4.png"),
]
const ICE_FRAMES := [
	preload("res://assets/world7/ice_attack_1.png"), preload("res://assets/world7/ice_attack_2.png"),
	preload("res://assets/world7/ice_attack_3.png"), preload("res://assets/world7/ice_attack_4.png"),
	preload("res://assets/world7/ice_attack_5.png"), preload("res://assets/world7/ice_attack_6.png"),
]
const ICE_SIZES := [Vector2(19, 47), Vector2(25, 40), Vector2(40, 25), Vector2(47, 19), Vector2(40, 25), Vector2(25, 40)]
const ICE_SPEEDS := [Vector2(0, 24), Vector2(10, 12), Vector2(17, 7), Vector2(24, 0), Vector2(17, -7), Vector2(10, -12)]
const FIRE_DELTAS := [
	Vector2(-15, -3), Vector2(-13, -9), Vector2(-8, -12), Vector2(-3, -15),
	Vector2(3, -15), Vector2(9, -13), Vector2(12, -8), Vector2(15, -3),
	Vector2(15, 3), Vector2(13, 9), Vector2(8, 12), Vector2(3, 15),
	Vector2(-3, 15), Vector2(-9, 13), Vector2(-12, 8), Vector2(-15, 3),
]

var player: SakuraPlayer
var terrain: SakuraTerrain
var sprite: Sprite2D
var kind := 75
var direction := 0
var variant := 0
var timer := 0
var physics_phase := 0
var animation_ticks := 0
var animation_frame := 0
var damage := 3
var action_state := 0
var rotation_count := 0
var fire_orbit_index := 0
var fire_orbit_ticks := 0
var body_size := Vector2.ZERO
var beam_segments: Array[Sprite2D] = []


func _ready() -> void:
	add_to_group("enemy_projectile_blockers")
	process_mode = Node.PROCESS_MODE_PAUSABLE
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_to_group("final_boss_projectiles")
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func configure(target: SakuraPlayer, map_terrain: SakuraTerrain, projectile_kind: int, projectile_direction: int, projectile_variant: int) -> void:
	player = target
	terrain = map_terrain
	kind = projectile_kind
	direction = projectile_direction
	variant = projectile_variant
	match kind:
		75:
			body_size = Vector2(48, 46)
			sprite.texture = SMALL_FRAMES[0]
			sprite.modulate.a = 0.0
		76:
			body_size = Vector2(34, 512)
			sprite.visible = false
			_build_beam()
		77, 78:
			body_size = Vector2(20, 39)
			sprite.texture = FIRE_FRAMES[0]
			sprite.modulate.a = 0.0
		79:
			variant = clampi(variant, 0, ICE_FRAMES.size() - 1)
			body_size = ICE_SIZES[variant]
			sprite.texture = ICE_FRAMES[variant]
			sprite.flip_h = direction == 1
			sprite.modulate.a = 0.0


func _physics_process(_delta: float) -> void:
	if kind == 76:
		_update_thunder()
		return
	_update_animation()
	if kind in [77, 78]:
		_update_fire()
		return
	if kind == 79:
		_update_ice()
		return
	physics_phase = (physics_phase + 1) % 4
	if physics_phase != 0:
		return
	match kind:
		75:
			_update_target_ball()


func _update_animation() -> void:
	if kind not in [75, 77, 78]:
		return
	animation_ticks += 1
	var frame_delay := 6 if kind == 75 else (8 if kind == 77 else 12)
	if animation_ticks >= frame_delay:
		animation_ticks = 0
		animation_frame = (animation_frame + 1) % 4
	if kind == 75:
		sprite.texture = SMALL_FRAMES[animation_frame] if action_state == 0 else BALL_FRAMES[animation_frame]
	else:
		sprite.texture = FIRE_FRAMES[animation_frame]


func _update_target_ball() -> void:
	timer += 1
	if action_state == 0:
		sprite.modulate.a = minf(1.0, float(timer) * 42.0 / 255.0)
		if timer >= 6:
			action_state = 1
			timer = 0
			sprite.texture = BALL_FRAMES[0]
			animation_frame = 0
			sprite.modulate.a = 1.0
	else:
		if timer >= 8:
			sprite.modulate.a -= 42.0 / 255.0
			if sprite.modulate.a <= 0.0:
				queue_free()
				return
	if sprite.modulate.a >= 0.999:
		_damage_player_if_touching()


func _update_thunder() -> void:
	timer += 1
	if timer == 1:
		_damage_player_if_touching()
	elif timer == 5:
		_set_beam_texture(THUNDER_FRAMES[1])
	elif timer == 9:
		_set_beam_texture(THUNDER_FRAMES[2])
	elif timer >= 13:
		queue_free()


func _update_fire() -> void:
	timer += 1
	if action_state == 0:
		sprite.modulate.a = minf(1.0, float(timer) / 32.0)
		if timer >= 32:
			action_state = 1
			timer = 0
			sprite.modulate.a = 1.0
		return
	if action_state == 1:
		_update_fire_orbit()
	else:
		_update_fire_settle()
	if sprite.modulate.a >= 0.999:
		_damage_player_if_touching()


func _update_fire_orbit() -> void:
	var segment_ticks := 4 if rotation_count == 0 and fire_orbit_index == 0 else 8
	var amount: Vector2 = FIRE_DELTAS[fire_orbit_index] / float(segment_ticks)
	if kind == 78:
		amount.x *= -1.0
	position += amount
	fire_orbit_ticks += 1
	if fire_orbit_ticks < segment_ticks:
		return
	fire_orbit_ticks = 0
	var checkpoint_indices := [15, 13, 11, 8, 5, 2]
	if rotation_count == 2 and fire_orbit_index == checkpoint_indices[variant - 1]:
		action_state = 10 + variant
		timer = 0
		fire_orbit_finished.emit()
		return
	fire_orbit_index += 1
	if fire_orbit_index >= FIRE_DELTAS.size():
		rotation_count += 1
		fire_orbit_index = 0


func _update_fire_settle() -> void:
	var targets_left := [Vector2.ZERO, Vector2(1080, 410), Vector2(1240, 330), Vector2(1400, 410), Vector2(1560, 290), Vector2(1360, 170), Vector2(920, 290)]
	var speeds_left := [Vector2.ZERO, Vector2(-2, 6), Vector2(2, 4), Vector2(6, 6), Vector2(10, 4), Vector2(6, 2), Vector2(-6, 4)]
	var targets_right := [Vector2.ZERO, Vector2(1400, 410), Vector2(1240, 330), Vector2(1080, 410), Vector2(920, 290), Vector2(1120, 170), Vector2(1560, 290)]
	var speeds_right := [Vector2.ZERO, Vector2(2, 6), Vector2(-2, 4), Vector2(-6, 6), Vector2(-10, 4), Vector2(-6, 2), Vector2(6, 4)]
	var target: Vector2 = targets_left[variant] if kind == 77 else targets_right[variant]
	var speed: Vector2 = speeds_left[variant] if kind == 77 else speeds_right[variant]
	position.x = _approach(position.x, target.x, absf(speed.x) / 4.0)
	position.y = _approach(position.y, target.y, absf(speed.y) / 4.0)
	if timer > 340:
		sprite.modulate.a = maxf(0.0, 1.0 - float(timer - 340) / 28.0)
		if timer >= 368:
			queue_free()


func _update_ice() -> void:
	timer += 1
	if action_state == 0:
		sprite.modulate.a = minf(1.0, float(timer) * 15.0 / 255.0)
		_damage_player_if_touching()
		if timer >= 20:
			action_state = 1
			timer = 0
			sprite.modulate.a = 1.0
		return
	var velocity: Vector2 = ICE_SPEEDS[variant] / 4.0
	if direction == 1:
		velocity.x *= -1.0
	for _step_index in range(2):
		var step := velocity * 0.5
		position += step
		_damage_player_if_touching()
	if position.x < 840.0 or position.x > 1740.0 or position.y < -80.0 or position.y > 680.0:
		queue_free()


func _damage_player_if_touching() -> void:
	if is_instance_valid(player) and Rect2(position, body_size).intersects(player.get_hit_rect()):
		player.take_damage(damage)


func _build_beam() -> void:
	for offset in range(int(body_size.y)):
		if terrain.rect_hits_solid(Rect2(position + Vector2(0, offset), Vector2(body_size.x, 1))):
			body_size.y = float(offset)
			break
	for offset in range(0, int(body_size.y), 128):
		var segment := Sprite2D.new()
		segment.centered = false
		segment.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		segment.texture = THUNDER_FRAMES[0]
		segment.position = Vector2(0, offset)
		segment.region_enabled = true
		segment.region_rect = Rect2(0, 0, body_size.x, minf(128.0, body_size.y - offset))
		add_child(segment)
		beam_segments.append(segment)


func _set_beam_texture(texture: Texture2D) -> void:
	for segment in beam_segments:
		segment.texture = texture


func _approach(value: float, target: float, amount: float) -> float:
	if value < target:
		return minf(value + amount, target)
	if value > target:
		return maxf(value - amount, target)
	return value


func blocks_player_projectile(rect: Rect2, weapon_id: int, water_splash: bool = false) -> bool:
	return (kind >= 77 or weapon_id in [6, 7] or water_splash) and preload("res://scripts/shared/projectile_interception.gd").overlaps(self, rect, body_size, weapon_id)
