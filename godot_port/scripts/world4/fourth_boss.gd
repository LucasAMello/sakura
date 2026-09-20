class_name FourthStageBoss
extends SakuraEnemy

signal intro_finished
signal water_shot_requested(spawn_position: Vector2, direction: int, trailing: bool)
signal boss_defeated

const CLOSED := preload("res://assets/world4/boss_turtle.png")
const ENTER_1 := preload("res://assets/world4/boss_turtle_enter_1.png")
const ENTER_2 := preload("res://assets/world4/boss_turtle_enter_2.png")
const ENTER_3 := preload("res://assets/world4/boss_turtle_enter_3.png")
const OPEN_1 := preload("res://assets/world4/boss_turtle_open_1.png")
const OPEN_2 := preload("res://assets/world4/boss_turtle_open_2.png")

enum BossState {
	WAITING,
	INTRO,
	IDLE_LEFT,
	SHOOT_LEFT,
	DASH_LEFT,
	RECOVER_RIGHT,
	IDLE_RIGHT,
	SHOOT_RIGHT,
	DASH_RIGHT,
	RECOVER_LEFT,
	CHAIN_LEFT,
	RAPID_SHOOT_LEFT,
	RAPID_DASH_LEFT,
	RAPID_RECOVER_RIGHT,
	CHAIN_RIGHT,
	RAPID_SHOOT_RIGHT,
	RAPID_DASH_RIGHT,
	RAPID_RECOVER_LEFT,
	DEFEATED,
}

var state := BossState.WAITING
var timer := 0
var direction := 0
var intro_notified := false
var boss_health := 30.0


func set_update_interval(_ticks: int) -> void:
	super.set_update_interval(1)


func _ready() -> void:
	super._ready()
	body_size = Vector2(128, 60)
	hit_points = 30
	boss_health = 30.0
	contact_damage = 4
	drops_recovery = false
	sprite.texture = CLOSED
	_update_facing()


func start_intro() -> void:
	state = BossState.INTRO
	timer = 0
	intro_notified = false


func start_fight() -> void:
	state = BossState.IDLE_LEFT if direction == 0 else BossState.IDLE_RIGHT
	timer = 0


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	if state == BossState.WAITING or state == BossState.INTRO or state == BossState.DEFEATED:
		return false
	return super.projectile_mask_overlap(projectile_rect)


func take_projectile_hit(_damage: int) -> void:
	_take_boss_damage(0.5)


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	_take_boss_damage(2.0 if weapon_id == 4 else 0.5)


func _take_boss_damage(damage: float) -> void:
	if not is_instance_valid(player) or player.dead:
		return
	if defeated_state or state == BossState.WAITING or state == BossState.INTRO:
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
		BossState.INTRO:
			_update_intro()
		BossState.IDLE_LEFT, BossState.IDLE_RIGHT:
			_update_idle()
		BossState.SHOOT_LEFT, BossState.SHOOT_RIGHT:
			_update_shot(false)
		BossState.RAPID_SHOOT_LEFT, BossState.RAPID_SHOOT_RIGHT:
			_update_shot(true)
		BossState.DASH_LEFT, BossState.DASH_RIGHT, BossState.RAPID_DASH_LEFT, BossState.RAPID_DASH_RIGHT:
			_update_dash()
		BossState.RECOVER_RIGHT, BossState.RECOVER_LEFT:
			_update_recovery(false)
		BossState.RAPID_RECOVER_RIGHT, BossState.RAPID_RECOVER_LEFT:
			_update_recovery(true)
		BossState.CHAIN_LEFT, BossState.CHAIN_RIGHT:
			_choose_chained_attack()


func _update_intro() -> void:
	if timer < 44:
		timer += 1
		if timer == 8 or timer == 40:
			sprite.texture = OPEN_1
			if timer == 8:
				get_node("/root/AudioManager").play_sfx("roar")
		elif timer == 12:
			sprite.texture = OPEN_2
		elif timer == 44:
			sprite.texture = CLOSED
	if timer >= 44 and not intro_notified:
		intro_notified = true
		intro_finished.emit()


func _update_idle() -> void:
	timer += 1
	var chooses_shot := randi() % 2 == 0
	if boss_health <= 20.0:
		timer = 0
		if direction == 0:
			state = BossState.RAPID_SHOOT_LEFT if chooses_shot else BossState.RAPID_DASH_LEFT
		else:
			state = BossState.RAPID_SHOOT_RIGHT if chooses_shot else BossState.RAPID_DASH_RIGHT
	elif timer >= 120:
		timer = 0
		if direction == 0:
			state = BossState.SHOOT_LEFT if chooses_shot else BossState.DASH_LEFT
		else:
			state = BossState.SHOOT_RIGHT if chooses_shot else BossState.DASH_RIGHT


func _update_shot(rapid: bool) -> void:
	timer += 1
	if timer == 4:
		sprite.texture = OPEN_1
	elif timer == 8:
		sprite.texture = OPEN_2
	elif timer == 24:
		var offset_x := 31.0 if direction == 0 else 77.0
		water_shot_requested.emit(position + Vector2(offset_x, 31), direction, false)
	elif timer == (52 if rapid else 64):
		sprite.texture = OPEN_1
	elif timer == (56 if rapid else 68):
		sprite.texture = CLOSED
	elif timer >= (60 if rapid else 108):
		timer = 0
		if rapid:
			state = BossState.CHAIN_LEFT if direction == 0 else BossState.CHAIN_RIGHT
		else:
			state = BossState.IDLE_LEFT if direction == 0 else BossState.IDLE_RIGHT


func _update_dash() -> void:
	timer += 1
	if timer == 8:
		sprite.texture = ENTER_1
		position.y += 1.0
	elif timer == 12:
		sprite.texture = ENTER_2
		position.y += 2.0
	elif timer == 16:
		sprite.texture = ENTER_3
		position.y += 3.0
		body_size.x = 96.0
		if direction == 0:
			position.x += 32.0
	elif timer == 28:
		var offset_x := 40.0 if direction == 0 else 58.0
		water_shot_requested.emit(position + Vector2(offset_x, 25), 1 - direction, true)
	elif timer >= 29:
		if timer == 40:
			get_node("/root/AudioManager").play_sfx("turtledash")
		var movement := -8.0 if direction == 0 else 8.0
		if _dash_hits_obstacle(movement):
			timer = 0
			if state == BossState.DASH_LEFT:
				state = BossState.RECOVER_RIGHT
			elif state == BossState.DASH_RIGHT:
				state = BossState.RECOVER_LEFT
			elif state == BossState.RAPID_DASH_LEFT:
				state = BossState.RAPID_RECOVER_RIGHT
			else:
				state = BossState.RAPID_RECOVER_LEFT


func _update_recovery(rapid: bool) -> void:
	timer += 1
	var recovering_on_right := state == BossState.RECOVER_RIGHT or state == BossState.RAPID_RECOVER_RIGHT
	if timer == (8 if rapid else 24):
		direction = 1 if recovering_on_right else 0
		_update_facing()
	if timer == (16 if rapid else 40):
		sprite.texture = ENTER_2
		position.y -= 3.0
		if not recovering_on_right:
			position.x -= 32.0
			body_size.x = 128.0
	elif timer == (20 if rapid else 44):
		sprite.texture = ENTER_1
		position.y -= 2.0
	elif timer == (24 if rapid else 48):
		sprite.texture = CLOSED
		position.y -= 1.0
		body_size.x = 128.0
	elif timer >= (28 if rapid else 52):
		timer = 0
		if rapid:
			state = BossState.CHAIN_RIGHT if direction == 1 else BossState.RAPID_SHOOT_LEFT
		else:
			state = BossState.IDLE_RIGHT if direction == 1 else BossState.IDLE_LEFT


func _choose_chained_attack() -> void:
	timer += 1
	if timer < 4:
		return
	var chooses_shot := randi() % 2 == 0
	if direction == 0:
		state = BossState.RAPID_SHOOT_LEFT if chooses_shot else BossState.RAPID_DASH_LEFT
	else:
		state = BossState.RAPID_SHOOT_RIGHT if chooses_shot else BossState.RAPID_DASH_RIGHT
	timer = 0


func _dash_hits_obstacle(amount: float) -> bool:
	var step_direction := signf(amount)
	for _step in range(int(absf(amount))):
		var candidate := Rect2(position + Vector2(step_direction, 0), body_size)
		if candidate.position.x < 9360.0 or candidate.end.x > terrain.world_size.x:
			return true
		if terrain.rect_hits_solid(candidate):
			return true
		if is_instance_valid(player) and candidate.intersects(player.get_hit_rect()):
			player.take_damage(contact_damage)
		position.x += step_direction
	return false


func _update_facing() -> void:
	sprite.flip_h = direction == 1


func _death_effect_position() -> Vector2:
	return position + Vector2(64, 30)
