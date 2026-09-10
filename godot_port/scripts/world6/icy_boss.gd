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
var shadow_sprite: Sprite2D
var form_texture: Texture2D


func set_update_interval(_ticks: int) -> void:
	super.set_update_interval(1)


func _ready() -> void:
	super._ready()
	shadow_sprite = Sprite2D.new()
	shadow_sprite.centered = false
	shadow_sprite.modulate.a = 50.0 / 255.0
	add_child(shadow_sprite)
	var normal_material := ShaderMaterial.new()
	normal_material.shader = preload("res://shaders/boss_wall_clip.gdshader")
	sprite.material = normal_material
	var shadow_material := ShaderMaterial.new()
	shadow_material.shader = normal_material.shader
	shadow_material.set_shader_parameter("outside", true)
	shadow_sprite.material = shadow_material
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

	_update_wall_visuals()


func _update_shadow_intro() -> void:
	timer += 1
	var sequence := [0, 1, 2, 1]
	_set_shadow(sequence[maxi(0, int(timer / 4.0) - 1) % sequence.size()], Vector2(154, 65))
	position.x -= 5.0
	if timer >= 180:
		state = BossState.RISE_INTRO
		timer = 0


func _update_rise_intro() -> void:
	timer += 1
	if timer == 24:
		position += Vector2(690, 0)
		position.y = 1220.0
		_set_shadow(3, Vector2(65, 154))
	elif timer > 24 and timer <= 68:
		position.y -= 7.5
	elif timer == 72:
		position.x -= 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 80:
		position.x -= 5.0
		_set_up(2, Vector2(120, 138))
	elif timer >= 88 and not intro_notified:
		intro_notified = true
		intro_finished.emit()


func _update_center_attack() -> void:
	timer += 1
	if timer == 80:
		attack_requested.emit(position + Vector2(-50, 60), 3, direction)
	elif timer == 140:
		attack_requested.emit(position + Vector2(-30, 130), 3, direction)
	elif timer == 200:
		position.x += 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 208:
		position.x += 5.0
		_set_up(0, Vector2(65, 154))
	elif timer > 212:
		_rise_out_and_choose()


func _update_bottom_dash() -> void:
	timer += 1
	if timer == 4:
		position = Vector2(3140, 1110)
		direction = 0
		_set_shadow(1, Vector2(154, 65))
	elif timer > 40 and timer <= 60:
		position.x += 7.5
	elif timer > 60 and timer <= 72:
		position += Vector2(7.5, -2.5)
	elif timer > 72 and timer <= 156:
		position.x += 7.5
	elif timer >= 160:
		_choose_emergence()


func _update_descent() -> void:
	timer += 1
	var from_left := state == BossState.DESCEND_LEFT
	if timer == 4:
		position = Vector2(3140, 880) if from_left else Vector2(3966, 880)
		direction = 0 if from_left else 1
		_set_shadow(1, Vector2(154, 65))
	elif timer > 20 and timer <= 68:
		var horizontal_step := 3.0 if from_left else -3.0
		position.x += horizontal_step
	elif timer == 72:
		_set_side(1, Vector2(140, 106))
		position += Vector2(20 if from_left else -6, 2)
	elif timer > 72 and timer <= 76:
		position += Vector2(15 if from_left else -15, 4) * 0.25
	elif timer == 80:
		_set_side(2, Vector2(138, 120))
		position += Vector2(15 if from_left else -13, 7)
	elif timer > 80 and timer <= 84:
		position += Vector2(15 if from_left else -15, 8) * 0.25
	elif timer == 88:
		_set_side(3, Vector2(90, 148))
		position += Vector2(50 if from_left else -2, 12)
	elif timer > 88 and timer <= 92:
		position += Vector2(12 if from_left else -12, 14) * 0.25
	elif timer == 96:
		_set_up(0, Vector2(65, 154))
		position += Vector2(26 if from_left else -1, 18)
	elif timer > 96 and timer <= 100:
		position += Vector2(10 if from_left else -10, 20) * 0.25
	elif timer > 100:
		position.y += 5.0
		if position.y > 1260.0:
			_choose_emergence()


func _update_emergence() -> void:
	timer += 1
	var on_right := state == BossState.EMERGE_HIGH_RIGHT or state == BossState.EMERGE_MID_RIGHT or state == BossState.EMERGE_LOW_RIGHT
	if timer == 24:
		position = Vector2(3770, 1220) if on_right else Vector2(3430, 1220)
		direction = 1 if on_right else 0
		_set_shadow(3, Vector2(65, 154))
	elif timer > 24 and timer <= 68:
		position.y -= 7.5
	elif timer == 72:
		if on_right:
			position.x -= 5.0
		else:
			position.x -= 38.0
		_set_up(1, Vector2(106, 140))
	elif timer == 80:
		var horizontal_offset := 5.0 if on_right else 12.0
		position.x -= horizontal_offset
		_set_up(2, Vector2(120, 138))
	elif timer >= 120:
		state = int(state) + 2
		timer = 0


func _update_high_attack() -> void:
	timer += 1
	var on_right := state == BossState.ATTACK_HIGH_RIGHT
	if timer == 80:
		var first_origin := position + (Vector2(-50, 60) if on_right else Vector2(123, 60))
		attack_requested.emit(first_origin, 3, direction)
	elif timer == 140:
		var second_origin := position + (Vector2(-30, 130) if on_right else Vector2(103, 130))
		attack_requested.emit(second_origin, 3, direction)
	elif timer == 200:
		var first_offset := 5.0 if on_right else 12.0
		position.x += first_offset
		_set_up(1, Vector2(106, 140))
	elif timer == 208:
		var second_offset := 5.0 if on_right else 38.0
		position.x += second_offset
		_set_up(0, Vector2(65, 154))
	elif timer > 212:
		_rise_out_and_choose()


func _update_mid_attack() -> void:
	timer += 1
	var on_right := state == BossState.ATTACK_MID_RIGHT
	if timer == 100:
		_emit_fan(on_right)
	elif timer == 160:
		position.x += 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 168:
		position.x += 5.0
		_set_up(0, Vector2(65, 154))
	elif timer > 172:
		_rise_out_and_choose()


func _update_low_attack() -> void:
	timer += 1
	var on_right := state == BossState.ATTACK_LOW_RIGHT
	if timer == 80:
		_emit_fan(on_right)
	if timer == 140:
		_emit_cross(on_right)
	elif timer == 240:
		position.x += 5.0
		_set_up(1, Vector2(106, 140))
	elif timer == 248:
		position.x += 5.0
		_set_up(0, Vector2(65, 154))
	elif timer > 252:
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
	position.y -= 7.5
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
	form_texture = SHADOW_FRAMES[index]
	sprite.texture = form_texture
	body_size = size
	damage_form = false
	_update_facing()


func _set_side(index: int, size: Vector2) -> void:
	form_texture = SIDE_FRAMES[index]
	sprite.texture = form_texture
	body_size = size
	damage_form = true
	_update_facing()


func _set_up(index: int, size: Vector2) -> void:
	form_texture = UP_FRAMES[index]
	sprite.texture = form_texture
	body_size = size
	damage_form = true
	_update_facing()


func _update_facing() -> void:
	sprite.flip_h = direction == 1
	_update_wall_visuals()


func _update_wall_visuals() -> void:
	if not is_instance_valid(shadow_sprite) or form_texture == null:
		return
	var descending := state == BossState.DESCEND_LEFT or state == BossState.DESCEND_RIGHT
	var vertical := form_texture == UP_FRAMES[0] or form_texture == SHADOW_FRAMES[3]
	sprite.texture = form_texture
	if SHADOW_FRAMES.has(form_texture):
		sprite.texture = UP_FRAMES[0] if vertical else SIDE_FRAMES[0]
	shadow_sprite.texture = SHADOW_FRAMES[3] if vertical else SHADOW_FRAMES[1]
	if state == BossState.SHADOW_INTRO:
		shadow_sprite.texture = form_texture
	sprite.flip_v = descending and vertical
	sprite.flip_h = direction == 0 if descending and vertical else direction == 1
	shadow_sprite.flip_h = sprite.flip_h
	shadow_sprite.flip_v = sprite.flip_v
	shadow_sprite.position = Vector2.ZERO
	if descending and not vertical and direction == 1 and not SHADOW_FRAMES.has(form_texture):
		shadow_sprite.position.x = body_size.x - 154.0


func _can_receive_damage() -> bool:
	return fight_started and damage_form and state != BossState.DEFEATED


func _death_effect_position() -> Vector2:
	return position + Vector2(60, 70)
