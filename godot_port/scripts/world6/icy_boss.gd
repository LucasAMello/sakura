class_name SixthStageBoss
extends SakuraEnemy

signal intro_finished
signal attack_requested(spawn_position: Vector2, variant: int, direction: int)
signal boss_defeated

const SHADOW_FRAMES := [
	preload("res://assets/world6/boss_shadow_1.png"),
	preload("res://assets/world6/boss_shadow_2.png"),
	preload("res://assets/world6/boss_shadow_3.png"),
	preload("res://assets/world6/boss_shadow_4.png"),
]
const SIDE_FRAMES := [
	preload("res://assets/world6/boss_side_1.png"),
	preload("res://assets/world6/boss_side_2.png"),
	preload("res://assets/world6/boss_side_3.png"),
	preload("res://assets/world6/boss_side_4.png"),
]
const UP_FRAMES := [
	preload("res://assets/world6/boss_up_1.png"),
	preload("res://assets/world6/boss_up_2.png"),
	preload("res://assets/world6/boss_up_3.png"),
]

enum BossState {
	WAITING,
	SHADOW_INTRO,
	RISE_INTRO,
	CENTER_ATTACK,
	BOTTOM_DASH,
	DESCEND_LEFT,
	DESCEND_RIGHT,
	EMERGE_HIGH_RIGHT,
	EMERGE_HIGH_LEFT,
	ATTACK_HIGH_RIGHT,
	ATTACK_HIGH_LEFT,
	EMERGE_MID_RIGHT,
	EMERGE_MID_LEFT,
	ATTACK_MID_RIGHT,
	ATTACK_MID_LEFT,
	EMERGE_LOW_RIGHT,
	EMERGE_LOW_LEFT,
	ATTACK_LOW_RIGHT,
	ATTACK_LOW_LEFT,
	DEFEATED,
}

var state := BossState.WAITING
var timer := 0
var direction := 1
var damage_form := false
var fight_started := false
var intro_notified := false
var boss_health := 30.0


func _ready() -> void:
	super._ready()
	body_size = Vector2(154, 65)
	hit_points = 30
	boss_health = 30.0
	contact_damage = 4
	drops_recovery = false
	_set_shadow(1, Vector2(154, 65))


func begin_intro() -> void:
	position = Vector2(3980, 1120)
	state = BossState.SHADOW_INTRO
	timer = 0
	direction = 1
	fight_started = false
	intro_notified = false
	_set_shadow(1, Vector2(154, 65))


func start_fight() -> void:
	fight_started = true
	state = BossState.CENTER_ATTACK
	timer = 0


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	if not _can_receive_damage():
		return false
	return super.projectile_mask_overlap(projectile_rect)


func take_projectile_hit(damage: int) -> void:
	_take_boss_damage(float(damage))


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	_take_boss_damage(4.0 if weapon_id == 6 else 0.5)


func _take_boss_damage(damage: float) -> void:
	if defeated_state or not _can_receive_damage():
		return
	boss_health -= damage
	hit_points = ceili(boss_health)
	hit_flash_ticks = 5
	if boss_health <= 0.0:
		boss_health = 0.0
		hit_points = 0
		defeated_state = true
		state = BossState.DEFEATED
		boss_defeated.emit()


func _update_enemy() -> void:
	match state:
		BossState.SHADOW_INTRO:
			_update_shadow_intro()
		BossState.RISE_INTRO:
			_update_rise_intro()
		BossState.CENTER_ATTACK:
			_update_center_attack()
		BossState.BOTTOM_DASH:
			_update_bottom_dash()
		BossState.DESCEND_LEFT, BossState.DESCEND_RIGHT:
			_update_descent()
		BossState.EMERGE_HIGH_RIGHT, BossState.EMERGE_HIGH_LEFT, BossState.EMERGE_MID_RIGHT, BossState.EMERGE_MID_LEFT, BossState.EMERGE_LOW_RIGHT, BossState.EMERGE_LOW_LEFT:
			_update_emergence()
		BossState.ATTACK_HIGH_RIGHT, BossState.ATTACK_HIGH_LEFT:
			_update_high_attack()
		BossState.ATTACK_MID_RIGHT, BossState.ATTACK_MID_LEFT:
			_update_mid_attack()
		BossState.ATTACK_LOW_RIGHT, BossState.ATTACK_LOW_LEFT:
			_update_low_attack()


func _update_shadow_intro() -> void:
	timer += 1
	var sequence := [0, 1, 2, 1]
	_set_shadow(sequence[(timer - 1) % sequence.size()], Vector2(154, 65))
	position.x -= 20.0
	if timer >= 45:
		state = BossState.RISE_INTRO
		timer = 0


func _update_rise_intro() -> void:
	timer += 1
	if timer == 6:
		position += Vector2(690, 0)
		position.y = 1220.0
		_set_shadow(3, Vector2(65, 154))
	elif timer > 6 and timer < 18:
		position.y -= 30.0
	elif timer == 18:
		position.x -= 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 20:
		position.x -= 5.0
		_set_up(2, Vector2(120, 138))
	elif timer >= 22 and not intro_notified:
		intro_notified = true
		intro_finished.emit()


func _update_center_attack() -> void:
	timer += 1
	if timer == 20:
		attack_requested.emit(position + Vector2(-50, 60), 3, direction)
	elif timer == 35:
		attack_requested.emit(position + Vector2(-30, 130), 3, direction)
	elif timer == 50:
		position.x += 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 52:
		position.x += 5.0
		_set_up(0, Vector2(65, 154))
	elif timer > 53:
		_rise_out_and_choose()


func _update_bottom_dash() -> void:
	timer += 1
	if timer == 1:
		position = Vector2(3140, 1110)
		direction = 0
		_set_shadow(1, Vector2(154, 65))
	elif timer > 10 and timer < 16:
		position.x += 30.0
	elif timer > 15 and timer < 19:
		position += Vector2(30, -10)
	elif timer > 18 and timer < 40:
		position.x += 30.0
	elif timer >= 40:
		_choose_emergence()


func _update_descent() -> void:
	timer += 1
	var from_left := state == BossState.DESCEND_LEFT
	if timer == 1:
		position = Vector2(3140, 880) if from_left else Vector2(3966, 880)
		direction = 0 if from_left else 1
		_set_shadow(1, Vector2(154, 65))
	elif timer > 5 and timer < 18:
		var horizontal_step := 12.0 if from_left else -12.0
		position.x += horizontal_step
	elif timer == 18:
		_set_side(1, Vector2(140, 106))
		position += Vector2(20 if from_left else -6, 2)
	elif timer == 19:
		position += Vector2(15 if from_left else -15, 4)
	elif timer == 20:
		_set_side(2, Vector2(138, 120))
		position += Vector2(15 if from_left else -13, 7)
	elif timer == 21:
		position += Vector2(15 if from_left else -15, 8)
	elif timer == 22:
		_set_side(3, Vector2(90, 148))
		position += Vector2(50 if from_left else -2, 12)
	elif timer == 23:
		position += Vector2(12 if from_left else -12, 14)
	elif timer == 24:
		_set_up(0, Vector2(65, 154))
		position += Vector2(26 if from_left else -1, 18)
	elif timer == 25:
		position += Vector2(10 if from_left else -10, 20)
	elif timer > 25:
		position.y += 20.0
		if position.y > 1260.0:
			_choose_emergence()


func _update_emergence() -> void:
	timer += 1
	var on_right := state == BossState.EMERGE_HIGH_RIGHT or state == BossState.EMERGE_MID_RIGHT or state == BossState.EMERGE_LOW_RIGHT
	if timer == 6:
		position = Vector2(3770, 1220) if on_right else Vector2(3430, 1220)
		direction = 1 if on_right else 0
		_set_shadow(3, Vector2(65, 154))
	elif timer > 6 and timer < 18:
		position.y -= 30.0
	elif timer == 18:
		if on_right:
			position.x -= 5.0
		else:
			position.x -= 38.0
		_set_up(1, Vector2(106, 140))
	elif timer == 20:
		var horizontal_offset := 5.0 if on_right else 12.0
		position.x -= horizontal_offset
		_set_up(2, Vector2(120, 138))
	elif timer >= 30:
		state = int(state) + 2
		timer = 0


func _update_high_attack() -> void:
	timer += 1
	var on_right := state == BossState.ATTACK_HIGH_RIGHT
	if timer == 20:
		var first_origin := position + (Vector2(-50, 60) if on_right else Vector2(123, 60))
		attack_requested.emit(first_origin, 3, direction)
	elif timer == 35:
		var second_origin := position + (Vector2(-30, 130) if on_right else Vector2(103, 130))
		attack_requested.emit(second_origin, 3, direction)
	elif timer == 50:
		var first_offset := 5.0 if on_right else 12.0
		position.x += first_offset
		_set_up(1, Vector2(106, 140))
	elif timer == 52:
		var second_offset := 5.0 if on_right else 38.0
		position.x += second_offset
		_set_up(0, Vector2(65, 154))
	elif timer > 53:
		_rise_out_and_choose()


func _update_mid_attack() -> void:
	timer += 1
	var on_right := state == BossState.ATTACK_MID_RIGHT
	if timer == 25:
		_emit_fan(on_right)
	elif timer == 40:
		position.x += 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 42:
		position.x += 5.0
		_set_up(0, Vector2(65, 154))
	elif timer > 43:
		_rise_out_and_choose()


func _update_low_attack() -> void:
	timer += 1
	var on_right := state == BossState.ATTACK_LOW_RIGHT
	if timer == 20:
		_emit_fan(on_right)
	if timer == 35:
		_emit_cross(on_right)
	elif timer == 60:
		position.x += 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 62:
		position.x += 5.0
		_set_up(0, Vector2(65, 154))
	elif timer > 63:
		_rise_out_and_choose()


func _emit_fan(on_right: bool) -> void:
	var offsets := [
		Vector2(6, 71), Vector2(-25, 67), Vector2(-56, 51), Vector2(-67, 26), Vector2(-56, -5),
	] if on_right else [
		Vector2(67, 71), Vector2(98, 67), Vector2(129, 51), Vector2(140, 26), Vector2(129, -5),
	]
	for variant in range(5):
		attack_requested.emit(position + offsets[variant], variant, direction)


func _emit_cross(on_right: bool) -> void:
	var base_x := -43.0 if on_right else 116.0
	var front_x := -50.0 if on_right else 123.0
	attack_requested.emit(position + Vector2(front_x, 60), 3, direction)
	attack_requested.emit(position + Vector2(base_x, 94), 2, direction)
	attack_requested.emit(position + Vector2(base_x, 94), 4, direction)
	attack_requested.emit(position + Vector2(base_x, 20), 4, direction)
	attack_requested.emit(position + Vector2(base_x, 20), 2, direction)


func _rise_out_and_choose() -> void:
	position.y -= 30.0
	if position.y <= 820.0:
		_set_shadow(3, Vector2(65, 154))
	if position.y < 580.0:
		timer = 0
		if player.position.y > 1010.0:
			state = BossState.BOTTOM_DASH
		elif player.position.x < 3640.0:
			state = BossState.DESCEND_LEFT
		else:
			state = BossState.DESCEND_RIGHT


func _choose_emergence() -> void:
	timer = 0
	var player_on_right := player.position.x > 3640.0
	if hit_points > 25:
		state = BossState.EMERGE_HIGH_RIGHT if player_on_right else BossState.EMERGE_HIGH_LEFT
	elif hit_points > 10:
		state = BossState.EMERGE_MID_RIGHT if player_on_right else BossState.EMERGE_MID_LEFT
	else:
		state = BossState.EMERGE_LOW_RIGHT if player_on_right else BossState.EMERGE_LOW_LEFT


func _set_shadow(index: int, size: Vector2) -> void:
	sprite.texture = SHADOW_FRAMES[index]
	body_size = size
	damage_form = false
	_update_facing()


func _set_side(index: int, size: Vector2) -> void:
	sprite.texture = SIDE_FRAMES[index]
	body_size = size
	damage_form = true
	_update_facing()


func _set_up(index: int, size: Vector2) -> void:
	sprite.texture = UP_FRAMES[index]
	body_size = size
	damage_form = true
	_update_facing()


func _update_facing() -> void:
	sprite.flip_h = direction == 1


func _can_receive_damage() -> bool:
	return fight_started and damage_form and state != BossState.DEFEATED


func _death_effect_position() -> Vector2:
	return position + Vector2(60, 70)
