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

enum BossState { WAITING, FLICKER, CROUCH, DASH, DASH_WAIT, TAKEOFF, HIGH_ATTACK, LOW_ATTACK, DEFEATED }

var state := BossState.WAITING
var timer := 0
var attack_pattern := 0
var dash_direction := -1
var boss_health := 30.0
var flash_alpha := 0.0
var flash_target := 0.0
var flash_step := 0.0


func set_update_interval(_ticks: int) -> void:
	super.set_update_interval(1)


func _ready() -> void:
	super._ready()
	body_size = Vector2(98, 69)
	hit_points = 30
	boss_health = 30.0
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
	_take_boss_damage(float(damage))


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	_take_boss_damage(4.0 if weapon_id == 3 else 0.5)


func _take_boss_damage(damage: float) -> void:
	if not is_instance_valid(player) or player.dead:
		return
	if defeated_state or not _can_receive_damage():
		return
	boss_health -= damage
	hit_points = ceili(boss_health)
	hit_flash_ticks = 16
	if boss_health <= 0.0:
		boss_health = 0.0
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
		BossState.DASH:
			_update_dash()
		BossState.DASH_WAIT:
			_update_dash_wait()
		BossState.TAKEOFF:
			_update_takeoff()
		BossState.HIGH_ATTACK:
			_update_high_attack()
		BossState.LOW_ATTACK:
			_update_low_attack()


func _update_flicker() -> void:
	sprite.visible = true
	sprite.texture = THUNDER_FRAMES[1] if timer % 16 < 8 else THUNDER_FRAMES[0]
	if timer == 160:
		state = BossState.CROUCH
		timer = 0
	else:
		timer += 1


func _update_crouch() -> void:
	if timer == 0:
		sprite.texture = THUNDER_FRAMES[2]
		body_size = Vector2(100, 63)
		position.y += 6.0
	if timer == 20:
		state = BossState.DASH
		dash_direction = -1
		timer = 0
	else:
		timer += 1


func _update_dash() -> void:
	sprite.flip_h = dash_direction > 0
	if timer == 0 && dash_direction < 0:
		get_node("/root/AudioManager").play_sfx("roar2")
	var x_speeds := [35.0, 55.0, 55.0, 55.0, 55.0, 42.0, 26.0, 15.0]
	var y_speeds := [-2.0, -2.0, -1.0, -1.0, 1.0, 1.0, 2.0, 2.0]
	if timer == 0:
		sprite.texture = THUNDER_FRAMES[4]
		body_size = Vector2(130, 64)
		if dash_direction > 0:
			position.x -= 30.0
	elif timer == 24:
		sprite.texture = THUNDER_FRAMES[3]
		body_size = Vector2(123, 64)
		if dash_direction > 0:
			position.x += 7.0
	elif timer == 32:
		state = BossState.DASH_WAIT if dash_direction < 0 else BossState.TAKEOFF
		timer = 0
		sprite.texture = THUNDER_FRAMES[2]
		sprite.flip_h = dash_direction < 0
		body_size = Vector2(100, 63)
		if dash_direction > 0:
			position.x += 23.0
		return
	var speed_frame = floori(timer / 4.0)
	position += Vector2(x_speeds[speed_frame] * dash_direction / 4, y_speeds[speed_frame] / 4)
	timer += 1


func _update_dash_wait() -> void:
	if timer == 24:
		state = BossState.DASH
		dash_direction = 1
		timer = 0
		return
	timer += 1


func _update_takeoff() -> void:
	timer += 1
	if timer >= 8 and timer <= 88 and timer % 2 == 0:
		sprite.texture = THUNDER_FRAMES[1] if timer % 16 < 8 else THUNDER_FRAMES[0]
		if timer == 8:
			body_size = Vector2(98, 69)
			position.y -= 6.0
	elif timer == 96:
		sprite.texture = THUNDER_FRAMES[2]
		position.y += 6.0
	elif timer == 112:
		sprite.texture = UP_FRAMES[0]
		position += Vector2(15, 13)
	elif timer == 116:
		sprite.texture = UP_FRAMES[1]
		position += Vector2(-4, 11)
	elif timer == 120:
		sprite.texture = UP_FRAMES[2]
		position += Vector2(16, -46)
	elif timer == 124:
		sprite.texture = UP_FRAMES[3]
		position += Vector2(17, -44)
	elif timer == 128 or timer == 132:
		position.y -= 100.0
	elif timer == 136:
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
	if timer == 80:
		lightning_requested.emit(Vector2(5570, 160))
	elif timer == 96:
		flash_requested.emit(0.5)
	elif timer == 100:
		flash_requested.emit(1.0)
		ball_requested.emit(Vector2(5580, 460), 1)
		ball_requested.emit(Vector2(5590, 460), 3)
		ball_requested.emit(Vector2(5585, 440), 1)
		ball_requested.emit(Vector2(5585, 440), 3)
	elif timer == 104:
		flash_requested.emit(0.5)
	elif timer == 108:
		flash_requested.emit(0.0)
	elif timer == 228:
		lightning_requested.emit(Vector2(5740, 160))
	elif timer == 232:
		flash_requested.emit(0.5)
	elif timer == 236:
		flash_requested.emit(1.0)
		_reappear()
	elif timer == 240:
		flash_requested.emit(0.5)
	elif timer == 244:
		flash_requested.emit(0.0)
		state = BossState.FLICKER
		timer = 0


func _update_low_attack() -> void:
	timer += 1
	if timer == 80:
		flash_requested.emit(0.5)
	elif timer == 84:
		flash_requested.emit(1.0)
	elif timer == 88:
		flash_requested.emit(0.5)
	elif timer == 92:
		flash_requested.emit(0.0)
	elif timer == 104:
		_spawn_beam_pair(5377, 5790 if attack_pattern == 0 else 5654)
	elif timer == 136:
		_spawn_beam_pair(5445, 5722)
	elif timer == 168:
		_spawn_beam_pair(5513, 5654 if attack_pattern == 0 else 5790)
	elif timer == 200:
		beam_requested.emit(Vector2(5583, 160))
	elif timer == 268:
		lightning_requested.emit(Vector2(5740, 160))
	elif timer == 284:
		flash_requested.emit(0.5)
	elif timer == 288:
		flash_requested.emit(1.0)
		_reappear()
	elif timer == 292:
		flash_requested.emit(0.5)
	elif timer == 296:
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
	return state != BossState.WAITING and state != BossState.DEFEATED and sprite.visible and THUNDER_FRAMES.has(sprite.texture)


func _death_effect_position() -> Vector2:
	return position + Vector2(49, 34)
