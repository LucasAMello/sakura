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

enum BossState { WAITING, TURNING, TRANSFORMING, METER_FILL, ACTIVE, SPLITTING, ACTIVE_SPLIT, DEFEATED }

var state := BossState.WAITING
var timer := 0
var x_velocity := -8.0
var y_velocity := -8.0
var intro_meter_ticks := 0


func _ready() -> void:
	super._ready()
	body_size = Vector2(50, 50)
	hit_points = 30
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
	if state != BossState.ACTIVE and state != BossState.ACTIVE_SPLIT:
		return
	hit_points -= damage
	hit_flash_ticks = 5
	if hit_points <= 0:
		hit_points = 0
		state = BossState.DEFEATED
		defeated_state = true
		x_velocity = 0.0
		y_velocity = 0.0
		control_lock_requested.emit(true)
		boss_defeated.emit()


func receive_clone_hit(damage: int) -> void:
	take_projectile_hit(damage)


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
	var cycle := timer % 8
	_set_shadow_cycle_frame(cycle)
	timer += 1


func _update_shadow_cycle() -> void:
	timer += 1
	_set_shadow_cycle_frame(timer % 8)


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
	if sprite.texture == SHADOW_TEXTURES[0] and not sprite.flip_h:
		state = BossState.TRANSFORMING
		timer = 0


func _update_transforming() -> void:
	var animation_tick := timer
	if animation_tick == 4:
		position.y -= 50.0
	for index in range(TRANSFORM_TEXTURES.size()):
		if animation_tick == 4 + index * 2:
			sprite.texture = TRANSFORM_TEXTURES[index]
	if animation_tick == 28:
		position.x += 25.0
		sprite.texture = BALL_TEXTURE
	elif animation_tick > 29 and animation_tick < 39:
		position.y -= 5.0
	elif animation_tick == 40:
		position.y -= 3.0
		state = BossState.METER_FILL
		timer = 0
		intro_meter_ticks = 0
		return
	timer += 1


func _update_meter_fill() -> void:
	intro_meter_ticks += 1
	if intro_meter_ticks >= 30:
		state = BossState.ACTIVE
		timer = 0
		boss_ready.emit()


func _update_active(split_active: bool) -> void:
	_bounce_move()
	if not split_active and hit_points <= 15 and position.y > 200.0 and position.y < 300.0:
		state = BossState.SPLITTING
		timer = 0
		control_lock_requested.emit(true)


func _update_splitting() -> void:
	if timer == 6:
		clone_requested.emit(position)
	elif timer == 36:
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
