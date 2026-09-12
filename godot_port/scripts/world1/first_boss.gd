class_name FirstStageBoss
extends SakuraEnemy

signal boss_defeated

const AIR_FRAMES := [
	preload("res://assets/world1/boss_bird_1.png"),
	preload("res://assets/world1/boss_bird_2.png"),
	preload("res://assets/world1/boss_bird_3.png"),
	preload("res://assets/world1/boss_bird_2.png"),
]
const FLY_TEXTURE := preload("res://assets/world1/boss_bird_fly_1.png")
const STAND_FRAME := preload("res://assets/world1/boss_bird_stand_1.png")
const ATTACK_FRAMES := [
	preload("res://assets/world1/boss_bird_stand_4.png"),
	preload("res://assets/world1/boss_bird_stand_3.png"),
	preload("res://assets/world1/boss_bird_stand_2.png"),
	preload("res://assets/world1/boss_bird_stand_3.png"),
]
const FeatherScript = preload("res://scripts/world1/boss_feather.gd")

enum BossState { ENTERING, HOVERING, RISING, DASH_DELAY, DASHING, LANDING, ATTACKING }

var state := BossState.ENTERING
var state_ticks := 0
var dash_direction := 1
var dash_pass := 0
var landing_side := 1
var vulnerable := false
var boss_health := 30.0


func configure() -> void:
	body_size = Vector2(83, 117)
	hit_points = 30
	boss_health = 30.0
	contact_damage = 3
	drops_recovery = false
	sprite.texture = AIR_FRAMES[0]


func _update_enemy() -> void:
	state_ticks += 1
	match state:
		BossState.ENTERING:
			if state_ticks == 1:
				position.x += 180.0
			_update_air_frame()
			position.y += 5.0 / 4.0
			if state_ticks >= 200:
				position.y = 157.0
				_set_state(BossState.HOVERING)
		BossState.HOVERING:
			_update_air_frame(8)
			if state_ticks >= 160:
				vulnerable = true
				_begin_rising()
		BossState.RISING:
			_update_air_frame(12)
			position.y -= 3.0
			if state_ticks >= 100:
				position.y -= 7.0
				_begin_dash_sequence()
		BossState.DASH_DELAY:
			if state_ticks >= 40:
				_start_dash_pass()
		BossState.DASHING:
			sprite.texture = FLY_TEXTURE
			position.x += dash_direction * 9.75
			if position.x < 2600.0 or position.x > 4080.0:
				position.x = clampf(position.x, 2615.0, 4020.0)
				_finish_dash_pass()
		BossState.LANDING:
			_update_air_frame(12 if landing_side < 0 else 0)
			position.y += 10.0 / 4.0
			if state_ticks >= 100:
				position.y = 157.0
				_set_state(BossState.ATTACKING)
		BossState.ATTACKING:
			if state_ticks < 48:
				sprite.texture = STAND_FRAME
			else:
				sprite.texture = ATTACK_FRAMES[int(state_ticks / 8.0) % ATTACK_FRAMES.size()]
			_update_feather_attack()
			if state_ticks >= 200:
				_begin_rising()


func _update_air_frame(phase_offset: int = 0) -> void:
	sprite.texture = AIR_FRAMES[int((state_ticks + phase_offset) / 8.0) % AIR_FRAMES.size()]


func _set_state(next_state: BossState) -> void:
	state = next_state
	state_ticks = 0


func _begin_rising() -> void:
	body_size = Vector2(83, 110)
	_set_state(BossState.RISING)


func _begin_dash_sequence() -> void:
	dash_pass = 0
	if landing_side == 1:
		dash_direction = -1
		position.x = 4020.0
	else:
		dash_direction = 1
		position.x = 2615.0
	_set_state(BossState.DASH_DELAY)


func _start_dash_pass() -> void:
	body_size = Vector2(113, 43)
	position.y = 195.0 if randi() % 2 == 0 else 305.0
	sprite.flip_h = dash_direction > 0
	get_node("/root/AudioManager").play_sfx("windydash")
	_set_state(BossState.DASHING)


func _finish_dash_pass() -> void:
	dash_pass += 1
	dash_direction *= -1
	if dash_pass == 3:
		landing_side *= -1
		_begin_landing()
		return
	_set_state(BossState.DASH_DELAY)


func _begin_landing() -> void:
	body_size = Vector2(83, 110)
	position.x = 3500.0 if landing_side > 0 else 3180.0
	position.y = -100.0
	sprite.flip_h = landing_side < 0
	_set_state(BossState.LANDING)


func _update_feather_attack() -> void:
	if landing_side > 0:
		if state_ticks == 80 or state_ticks == 144:
			_fire_feather(40.0)
			_fire_feather(80.0)
		elif state_ticks == 112 or state_ticks == 176:
			_fire_feather(60.0)
	else:
		if state_ticks == 80 or state_ticks == 144:
			_fire_feather(60.0)
		elif state_ticks == 112 or state_ticks == 176:
			_fire_feather(40.0)
			_fire_feather(80.0)


func _fire_feather(y_offset: float) -> void:
	get_node("/root/AudioManager").play_sfx("penasound")
	var feather: BossFeather = FeatherScript.new()
	var direction := 1 if sprite.flip_h else -1
	feather.position = position + Vector2(35.0, y_offset)
	feather.z_index = 14
	feather.setup(terrain, player, direction)
	get_parent().add_child(feather)


func take_projectile_hit(damage: int) -> void:
	_take_boss_damage(damage * 0.5)


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	_take_boss_damage(4.0 if weapon_id == 7 else 0.5)


func _take_boss_damage(damage: float) -> void:
	if defeated_state or not vulnerable:
		return
	boss_health -= damage
	hit_points = ceili(boss_health)
	hit_flash_ticks = 16
	if boss_health <= 0.0:
		boss_health = 0.0
		hit_points = 0
		defeated_state = true
		boss_defeated.emit()
