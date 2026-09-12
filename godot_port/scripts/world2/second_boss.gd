class_name SecondStageBoss
extends SakuraEnemy

signal boss_ready
signal control_lock_requested(value: bool)
signal clone_requested(spawn_position: Vector2)
signal boss_defeated

const SHADOW_TEXTURES := [
	preload("res://assets/world2/boss_shadow_1.png"),
	preload("res://assets/world2/boss_shadow_2.png"),
	preload("res://assets/world2/boss_shadow_3.png"),
]
const TRANSFORM_TEXTURES := [
	preload("res://assets/world2/boss_transform_1.png"),
	preload("res://assets/world2/boss_transform_2.png"),
	preload("res://assets/world2/boss_transform_3.png"),
	preload("res://assets/world2/boss_transform_4.png"),
	preload("res://assets/world2/boss_transform_5.png"),
	preload("res://assets/world2/boss_transform_6.png"),
	preload("res://assets/world2/boss_transform_7.png"),
	preload("res://assets/world2/boss_transform_8.png"),
	preload("res://assets/world2/boss_transform_9.png"),
	preload("res://assets/world2/boss_transform_10.png"),
	preload("res://assets/world2/boss_transform_11.png"),
	preload("res://assets/world2/boss_transform_12.png"),
]
const BALL_TEXTURE := preload("res://assets/world2/boss_ball.png")
const ROOM_CENTER_X := 5650.0
const SPLIT_CENTER_DISTANCE := 80.0

enum BossState { WAITING, TURNING, TRANSFORMING, METER_FILL, ACTIVE, SPLITTING, ACTIVE_SPLIT, DEFEATED }

var state := BossState.WAITING
var timer := 0
var x_velocity := -3.75
var y_velocity := -3.75
var intro_meter_ticks := 0
var boss_health := 30.0
var clone_drift_direction := 1


func set_update_interval(_ticks: int) -> void:
	super.set_update_interval(1)


func _ready() -> void:
	super._ready()
	body_size = Vector2(50, 50)
	hit_points = 30
	boss_health = 30.0
	contact_damage = 3
	drops_recovery = false
	sprite.texture = SHADOW_TEXTURES[0]


func begin_intro() -> void:
	if state == BossState.WAITING:
		state = BossState.TURNING
		timer = 0


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	if state != BossState.ACTIVE and state != BossState.ACTIVE_SPLIT:
		return false
	return super.projectile_mask_overlap(projectile_rect)


func take_projectile_hit(damage: int) -> void:
	_take_boss_damage(float(damage))


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	_take_boss_damage(3.0 if weapon_id == 2 else 0.5)


func _take_boss_damage(damage: float) -> void:
	if state != BossState.ACTIVE and state != BossState.ACTIVE_SPLIT:
		return
	boss_health -= damage
	hit_points = ceili(boss_health)
	hit_flash_ticks = 16
	if boss_health <= 0.0:
		boss_health = 0.0
		hit_points = 0
		state = BossState.DEFEATED
		defeated_state = true
		x_velocity = 0.0
		y_velocity = 0.0
		control_lock_requested.emit(true)
		boss_defeated.emit()


func receive_clone_hit(damage: int) -> void:
	take_projectile_hit(damage)


func receive_clone_weapon_hit(damage: int, weapon_id: int) -> void:
	take_weapon_hit(damage, weapon_id)


func _update_enemy() -> void:
	match state:
		BossState.WAITING:
			_update_waiting()
		BossState.TURNING:
			_update_turning()
		BossState.TRANSFORMING:
			_update_transforming()
		BossState.METER_FILL:
			_update_meter_fill()
		BossState.ACTIVE:
			_update_active(false)
		BossState.SPLITTING:
			_update_splitting()
		BossState.ACTIVE_SPLIT:
			_update_active(true)


func _update_waiting() -> void:
	if timer % 4 == 3:
		_set_shadow_cycle_frame(int(timer / 4.0) % 8)
	timer += 1


func _update_shadow_cycle() -> void:
	timer += 1
	if timer % 4 == 0:
		_set_shadow_cycle_frame(int(timer / 4.0) % 8)


func _set_shadow_cycle_frame(cycle: int) -> void:
	if cycle == 0:
		sprite.texture = SHADOW_TEXTURES[0]
	elif cycle == 2 or cycle == 6:
		sprite.texture = SHADOW_TEXTURES[1]
	elif cycle == 4:
		sprite.texture = SHADOW_TEXTURES[2]
	if cycle == 6:
		sprite.flip_h = not sprite.flip_h


func _update_turning() -> void:
	_update_shadow_cycle()
	if timer % 4 == 0 and sprite.texture == SHADOW_TEXTURES[0] and not sprite.flip_h:
		state = BossState.TRANSFORMING
		timer = 0


func _update_transforming() -> void:
	var animation_tick := int(timer / 4.0)
	if timer == 19:
		position.y -= 50.0
	for index in range(TRANSFORM_TEXTURES.size()):
		if timer % 4 == 3 and animation_tick == 4 + index * 2:
			sprite.texture = TRANSFORM_TEXTURES[index]
	if timer == 115:
		position.x += 25.0
		sprite.texture = BALL_TEXTURE
	elif animation_tick > 29 and animation_tick < 39:
		position.y -= 1.25
	elif timer == 163:
		position.y -= 3.0
		state = BossState.METER_FILL
		timer = 0
		intro_meter_ticks = 0
		return
	timer += 1


func _update_meter_fill() -> void:
	timer += 1
	if timer % 4 != 0:
		return
	intro_meter_ticks += 1
	get_node("/root/AudioManager").play_sfx("recuperator")
	if intro_meter_ticks >= 30:
		state = BossState.ACTIVE
		timer = 0
		boss_ready.emit()


func _update_active(split_active: bool) -> void:
	_bounce_move()
	var center_x := position.x + body_size.x * 0.5
	if not split_active and hit_points <= 15 and absf(center_x - ROOM_CENTER_X) <= SPLIT_CENTER_DISTANCE:
		clone_drift_direction = 1 if center_x <= ROOM_CENTER_X else -1
		state = BossState.SPLITTING
		timer = 0
		control_lock_requested.emit(true)


func _update_splitting() -> void:
	if timer == 27:
		get_node("/root/AudioManager").play_sfx("tiro3")
		clone_requested.emit(position)
	elif timer == 147:
		x_velocity = -clone_drift_direction * absf(x_velocity)
		y_velocity = -absf(y_velocity)
		state = BossState.ACTIVE_SPLIT
		control_lock_requested.emit(false)
	timer += 1


func _bounce_move() -> void:
	_move_axis(Vector2(x_velocity, 0.0), true)
	_move_axis(Vector2(0.0, y_velocity), false)


func _move_axis(amount: Vector2, horizontal: bool) -> void:
	var distance := absf(amount.x if horizontal else amount.y)
	var direction := signf(amount.x if horizontal else amount.y)
	while distance > 0.0:
		var step := minf(1.0, distance) * direction
		var offset := Vector2(step, 0.0) if horizontal else Vector2(0.0, step)
		if horizontal and (position.x + step < 5340.0 or position.x + step > 5910.0):
			x_velocity *= -1.0
			return
		if terrain.rect_hits_solid(Rect2(position + offset, body_size)):
			if horizontal:
				x_velocity *= -1.0
			else:
				y_velocity *= -1.0
			return
		position += offset
		distance -= absf(step)


func _death_effect_position() -> Vector2:
	return position + Vector2(25, 25)
