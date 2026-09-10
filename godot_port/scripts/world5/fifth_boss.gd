class_name FifthStageBoss
extends SakuraEnemy

signal projectile_requested(kind: int, spawn_position: Vector2, direction: int)
signal boss_defeated

const IDLE_FRAMES := [
	preload("res://assets/world5/boss_idle_1.png"),
	preload("res://assets/world5/boss_idle_2.png"),
	preload("res://assets/world5/boss_idle_3.png"),
	preload("res://assets/world5/boss_idle_4.png"),
]
const FIRE_FRAMES := [
	preload("res://assets/world5/boss_fire_1.png"),
	preload("res://assets/world5/boss_fire_2.png"),
	preload("res://assets/world5/boss_fire_3.png"),
]
const CUT_FRAMES := [
	preload("res://assets/world5/boss_cut_1.png"),
	preload("res://assets/world5/boss_cut_2.png"),
]

enum BossState { WAITING, INTRO, IDLE, SPRAY, HADOUKEN, SLASH, DEFEATED }

var state := BossState.WAITING
var timer := 0
var direction := 1
var boss_health := 30.0


func set_update_interval(_ticks: int) -> void:
	super.set_update_interval(1)


func _ready() -> void:
	super._ready()
	body_size = Vector2(129, 106)
	hit_points = 30
	boss_health = 30.0
	contact_damage = 4
	drops_recovery = false
	sprite.texture = IDLE_FRAMES[0]
	sprite.flip_h = direction == 1


func start_intro() -> void:
	state = BossState.INTRO
	timer = 0


func start_fight() -> void:
	state = BossState.IDLE
	timer = 0


func take_projectile_hit(damage: int) -> void:
	_take_boss_damage(float(damage))


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	_take_boss_damage(3.0 if weapon_id == 5 else 0.5)


func _take_boss_damage(damage: float) -> void:
	if defeated_state or state == BossState.WAITING or state == BossState.INTRO:
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
		BossState.WAITING:
			_update_idle_animation()
		BossState.INTRO:
			_update_intro()
		BossState.IDLE:
			_update_idle()
		BossState.SPRAY:
			_update_spray()
		BossState.HADOUKEN:
			_update_hadouken()
		BossState.SLASH:
			_update_slash()


func _update_idle_animation() -> void:
	timer += 1
	if timer % 12 == 0:
		sprite.texture = IDLE_FRAMES[int(timer / 12.0 - 1.0) % IDLE_FRAMES.size()]


func _update_intro() -> void:
	timer += 1
	if timer == 8 or timer == 88:
		sprite.texture = FIRE_FRAMES[0]
	elif timer == 16 or timer == 80:
		sprite.texture = FIRE_FRAMES[1]
		if timer == 16:
			get_node("/root/AudioManager").play_sfx("roar")
	elif timer == 24:
		sprite.texture = FIRE_FRAMES[2]
	elif timer == 96:
		sprite.texture = IDLE_FRAMES[0]


func _update_idle() -> void:
	_update_idle_animation()
	if timer == 200:
		timer = 0
		match randi() % 3:
			0:
				state = BossState.SPRAY
			1:
				state = BossState.HADOUKEN
			2:
				state = BossState.SLASH
		sprite.texture = IDLE_FRAMES[0]


func _update_spray() -> void:
	timer += 1
	if timer % 24 == 0 and timer < 220:
		projectile_requested.emit(World5BossProjectile.Kind.SPRAY, position + Vector2(12 + randi() % 6, 13 + randi() % 6), direction)
	if timer == 4 or timer == 236:
		sprite.texture = FIRE_FRAMES[0]
	elif timer == 12 or timer == 228:
		sprite.texture = FIRE_FRAMES[1]
	elif timer == 20:
		sprite.texture = FIRE_FRAMES[2]
	elif timer == 244:
		_return_to_idle()


func _update_hadouken() -> void:
	timer += 1
	if timer == 4 or timer == 72:
		sprite.texture = FIRE_FRAMES[0]
	elif timer == 12 or timer == 64:
		sprite.texture = FIRE_FRAMES[1]
	elif timer == 20:
		sprite.texture = FIRE_FRAMES[2]
	elif timer == 40:
		projectile_requested.emit(World5BossProjectile.Kind.HADOUKEN, position + Vector2(30, 15), direction)
	elif timer == 80:
		_return_to_idle()


func _update_slash() -> void:
	timer += 1
	if timer == 4:
		sprite.texture = CUT_FRAMES[0]
		position.y -= 8.0
		body_size.y = 114.0
	elif timer == 32:
		projectile_requested.emit(World5BossProjectile.Kind.SLASH_STRAIGHT, position + Vector2(5, 32), direction)
		projectile_requested.emit(World5BossProjectile.Kind.SLASH_RISING, position + Vector2(5, 32), direction)
		sprite.texture = CUT_FRAMES[1]
	elif timer == 60:
		position.y += 8.0
		body_size = Vector2(129, 106)
		_return_to_idle()


func _return_to_idle() -> void:
	state = BossState.IDLE
	timer = 12
	sprite.texture = IDLE_FRAMES[0]


func _death_effect_position() -> Vector2:
	return position + Vector2(64, 53)
