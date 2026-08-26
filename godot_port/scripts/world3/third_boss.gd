class_name ThirdStageBoss
extends SakuraEnemy

signal flash_requested(alpha: float)
signal lightning_requested(spawn_position: Vector2)
signal ball_requested(spawn_position: Vector2, direction: int)
signal beam_requested(spawn_position: Vector2)
signal boss_defeated

const THUNDER_FRAMES := [
	preload("res://assets/world3/boss_thunder_1.png"),
	preload("res://assets/world3/boss_thunder_2.png"),
	preload("res://assets/world3/boss_thunder_3.png"),
	preload("res://assets/world3/boss_thunder_4.png"),
	preload("res://assets/world3/boss_thunder_5.png"),
]
const UP_FRAMES := [
	preload("res://assets/world3/boss_up_1.png"),
	preload("res://assets/world3/boss_up_2.png"),
	preload("res://assets/world3/boss_up_3.png"),
	preload("res://assets/world3/boss_up_4.png"),
]

enum BossState { WAITING, FLICKER, CROUCH, DASH_LEFT, DASH_RIGHT, TAKEOFF, HIGH_ATTACK, LOW_ATTACK, DEFEATED }

var state := BossState.WAITING
var timer := 0
var attack_pattern := 0


func _ready() -> void:
	super._ready()
	body_size = Vector2(98, 69)
	hit_points = 30
	contact_damage = 3
	drops_recovery = false
	sprite.texture = THUNDER_FRAMES[0]


func start_fight() -> void:
	if state == BossState.WAITING:
		state = BossState.FLICKER
		timer = 0


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	if not _can_receive_damage():
		return false
	return super.projectile_mask_overlap(projectile_rect)


func take_projectile_hit(damage: int) -> void:
	if defeated_state or not _can_receive_damage():
		return
	hit_points -= damage
	hit_flash_ticks = 5
	if hit_points <= 0:
		hit_points = 0
		defeated_state = true
		state = BossState.DEFEATED
		boss_defeated.emit()


func _update_enemy() -> void:
	match state:
		BossState.FLICKER:
			_update_flicker()
		BossState.CROUCH:
			_update_crouch()
		BossState.DASH_LEFT:
			_update_dash_left()
		BossState.DASH_RIGHT:
			_update_dash_right()
		BossState.TAKEOFF:
			_update_takeoff()
		BossState.HIGH_ATTACK:
			_update_high_attack()
		BossState.LOW_ATTACK:
			_update_low_attack()


func _update_flicker() -> void:
	sprite.visible = true
	sprite.texture = THUNDER_FRAMES[1] if timer % 4 < 2 else THUNDER_FRAMES[0]
	if timer == 40:
		state = BossState.CROUCH
		timer = 0
	else:
		timer += 1


func _update_crouch() -> void:
	if timer == 0:
		sprite.texture = THUNDER_FRAMES[2]
		body_size = Vector2(100, 63)
		position.y += 6.0
	if timer == 5:
		state = BossState.DASH_LEFT
		timer = 0
	else:
		timer += 1


func _update_dash_left() -> void:
	sprite.flip_h = false
	var x_speeds := [-35.0, -55.0, -55.0, -55.0, -55.0, -42.0, -26.0, -15.0]
	var y_speeds := [-2.0, -2.0, -1.0, -1.0, 1.0, 1.0, 2.0, 2.0]
	if timer == 0 or timer == 6:
		sprite.texture = THUNDER_FRAMES[3]
		body_size = Vector2(96, 64)
	elif timer == 2:
		sprite.texture = THUNDER_FRAMES[4]
		body_size.x = 130.0
	if timer == 8:
		state = BossState.DASH_RIGHT
		timer = 0
		sprite.texture = THUNDER_FRAMES[2]
		sprite.flip_h = true
		body_size = Vector2(100, 63)
		return
	position += Vector2(x_speeds[timer], y_speeds[timer])
	timer += 1


func _update_dash_right() -> void:
	if timer == 15:
		state = BossState.TAKEOFF
		timer = 0
		sprite.texture = THUNDER_FRAMES[2]
		sprite.flip_h = false
		body_size = Vector2(100, 63)
		return
	if timer >= 7:
		var movement_tick := timer - 7
		var x_speeds := [35.0, 55.0, 55.0, 55.0, 55.0, 42.0, 26.0, 15.0]
		var y_speeds := [-2.0, -2.0, -1.0, -1.0, 1.0, 1.0, 2.0, 2.0]
		if timer == 7 or timer == 13:
			sprite.texture = THUNDER_FRAMES[3]
			body_size = Vector2(96, 64)
		elif timer == 9:
			sprite.texture = THUNDER_FRAMES[4]
			body_size.x = 130.0
		position += Vector2(x_speeds[movement_tick], y_speeds[movement_tick])
	timer += 1


func _update_takeoff() -> void:
	timer += 1
	if timer >= 2 and timer <= 22 and timer % 2 == 0:
		sprite.texture = THUNDER_FRAMES[1] if timer % 4 == 2 else THUNDER_FRAMES[0]
		if timer == 2:
			body_size = Vector2(98, 69)
			position.y -= 6.0
	elif timer == 24:
		sprite.texture = THUNDER_FRAMES[2]
		position.y += 6.0
	elif timer == 28:
		sprite.texture = UP_FRAMES[0]
		position += Vector2(15, 13)
	elif timer == 29:
		sprite.texture = UP_FRAMES[1]
		position += Vector2(-4, 11)
	elif timer == 30:
		sprite.texture = UP_FRAMES[2]
		position += Vector2(16, -46)
	elif timer == 31:
		sprite.texture = UP_FRAMES[3]
		position += Vector2(17, -44)
	elif timer == 32 or timer == 33:
		position.y -= 100.0
	elif timer == 34:
		sprite.visible = false
		position.x += 200.0
		timer = 0
		if hit_points > 15:
			state = BossState.HIGH_ATTACK
		else:
			state = BossState.LOW_ATTACK
			attack_pattern = randi() % 2


func _update_high_attack() -> void:
	timer += 1
	if timer == 20:
		lightning_requested.emit(Vector2(5570, 160))
	elif timer == 24:
		flash_requested.emit(0.5)
	elif timer == 25:
		flash_requested.emit(1.0)
		ball_requested.emit(Vector2(5580, 460), 1)
		ball_requested.emit(Vector2(5590, 460), 3)
		ball_requested.emit(Vector2(5585, 440), 1)
		ball_requested.emit(Vector2(5585, 440), 3)
	elif timer == 26:
		flash_requested.emit(0.5)
	elif timer == 27:
		flash_requested.emit(0.0)
	elif timer == 57:
		lightning_requested.emit(Vector2(5740, 160))
	elif timer == 58:
		flash_requested.emit(0.5)
	elif timer == 59:
		flash_requested.emit(1.0)
		_reappear()
	elif timer == 60:
		flash_requested.emit(0.5)
	elif timer == 61:
		flash_requested.emit(0.0)
		state = BossState.FLICKER
		timer = 0


func _update_low_attack() -> void:
	timer += 1
	if timer == 20:
		flash_requested.emit(0.5)
	elif timer == 21:
		flash_requested.emit(1.0)
	elif timer == 22:
		flash_requested.emit(0.5)
	elif timer == 23:
		flash_requested.emit(0.0)
	elif timer == 26:
		_spawn_beam_pair(5377, 5790 if attack_pattern == 0 else 5654)
	elif timer == 34:
		_spawn_beam_pair(5445, 5722)
	elif timer == 42:
		_spawn_beam_pair(5513, 5654 if attack_pattern == 0 else 5790)
	elif timer == 50:
		beam_requested.emit(Vector2(5583, 160))
	elif timer == 67:
		lightning_requested.emit(Vector2(5740, 160))
	elif timer == 71:
		flash_requested.emit(0.5)
	elif timer == 72:
		flash_requested.emit(1.0)
		_reappear()
	elif timer == 73:
		flash_requested.emit(0.5)
	elif timer == 74:
		flash_requested.emit(0.0)
		state = BossState.FLICKER
		timer = 0


func _spawn_beam_pair(first_x: float, second_x: float) -> void:
	beam_requested.emit(Vector2(first_x, 160))
	beam_requested.emit(Vector2(second_x, 160))


func _reappear() -> void:
	position = Vector2(5720, 411)
	body_size = Vector2(98, 69)
	sprite.texture = THUNDER_FRAMES[0]
	sprite.flip_h = false
	sprite.visible = true


func _can_receive_damage() -> bool:
	return state == BossState.FLICKER or state == BossState.CROUCH or state == BossState.DASH_LEFT or state == BossState.DASH_RIGHT


func _death_effect_position() -> Vector2:
	return position + Vector2(49, 34)
