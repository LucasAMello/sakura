class_name SakuraFinalBoss
extends SakuraEnemy

signal attack_requested(kind: int, origin: Vector2, direction: int, variant: int)
signal flash_requested(alpha: float)
signal boss_defeated

enum BossState { WAITING, FADE_IN, ATTACK, FADE_OUT, DEFEATED }
enum Attack { TARGET = 2, LIGHTNING_LEFT = 3, LIGHTNING_RIGHT = 4, FIRE_LEFT = 5, FIRE_RIGHT = 6, ICE_LEFT = 7, ICE_RIGHT = 8 }

const ATTACK_POSITIONS := {
	Attack.TARGET: Vector2(1215, 276),
	Attack.LIGHTNING_LEFT: Vector2(1075, 356),
	Attack.LIGHTNING_RIGHT: Vector2(1355, 356),
	Attack.FIRE_LEFT: Vector2(1115, 116),
	Attack.FIRE_RIGHT: Vector2(1315, 116),
	Attack.ICE_LEFT: Vector2(1515, 236),
	Attack.ICE_RIGHT: Vector2(915, 236),
}
const ICE_TIMES := [60, 70, 80, 86, 96, 106, 120, 130, 140, 150, 160, 165, 180, 190]
const FIRE_SPAWN_TIMES := [25, 29, 33, 39, 45, 51]
const LIGHTNING_LANES := {
	Attack.TARGET: Vector2(1218, 30),
	Attack.LIGHTNING_LEFT: Vector2(1078, 10),
	Attack.LIGHTNING_RIGHT: Vector2(1382, 6),
	Attack.FIRE_LEFT: Vector2(1118, 30),
	Attack.FIRE_RIGHT: Vector2(1318, 30),
	Attack.ICE_LEFT: Vector2(1518, 30),
	Attack.ICE_RIGHT: Vector2(918, 30),
}

var state := BossState.WAITING
var timer := 0
var attack_kind: Attack = Attack.TARGET
var last_attack: Attack = Attack.TARGET
var vulnerable := false
var hit_this_appearance := false
var boss_health := 30.0
var finished_fire_orbits := 0


func _ready() -> void:
	super._ready()
	body_size = Vector2(80, 109)
	hit_points = 30
	contact_damage = 3
	drops_recovery = false
	sprite.texture = preload("res://assets/world7/final_boss.png")
	sprite.modulate.a = 0.0


func begin_intro() -> void:
	position = ATTACK_POSITIONS[Attack.TARGET]
	state = BossState.WAITING
	timer = 0
	attack_kind = Attack.TARGET
	vulnerable = false
	hit_this_appearance = false
	sprite.modulate.a = 0.0


func begin_fight() -> void:
	position = ATTACK_POSITIONS[Attack.TARGET]
	state = BossState.ATTACK
	timer = 20
	attack_kind = Attack.TARGET
	last_attack = Attack.TARGET
	vulnerable = true
	hit_this_appearance = false
	sprite.modulate.a = 1.0


func get_hit_rect() -> Rect2:
	if state == BossState.WAITING or state == BossState.DEFEATED or sprite.modulate.a < 0.5:
		return Rect2(position, Vector2.ZERO)
	return super.get_hit_rect()


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return vulnerable and super.projectile_mask_overlap(projectile_rect)


func accepts_weapon_hit(weapon_id: int) -> bool:
	return weapon_id == 1


func take_weapon_hit(_damage: int, weapon_id: int) -> void:
	if not is_instance_valid(player) or player.dead:
		return
	if weapon_id != 1 or not vulnerable or defeated_state or hit_this_appearance:
		return
	# hit_this_appearance = true
	boss_health -= 0.5
	hit_points = ceil(boss_health)
	hit_flash_ticks = 16
	if hit_points <= 0:
		hit_points = 0
		defeated_state = true
		vulnerable = false
		state = BossState.DEFEATED
		flash_requested.emit(0.0)
		boss_defeated.emit()


func _update_enemy() -> void:
	_update_facing()
	match state:
		BossState.FADE_IN:
			_update_fade_in()
		BossState.ATTACK:
			_update_attack()
		BossState.FADE_OUT:
			_update_fade_out()


func _update_facing() -> void:
	if not is_instance_valid(player):
		return
	var face_left := player.position.x + 20.0 < position.x + 35.0
	sprite.flip_h = face_left
	sprite.position.x = -10.0 if face_left else 0.0


func _update_fade_in() -> void:
	timer += 1
	sprite.modulate.a = clampf(float(timer - 1) * 16.0 / 255.0, 0.0, 1.0)
	if timer >= 20:
		state = BossState.ATTACK
		timer = 20
		vulnerable = true


func _update_attack() -> void:
	timer += 1
	match attack_kind:
		Attack.TARGET:
			_update_target_attack()
		Attack.LIGHTNING_LEFT, Attack.LIGHTNING_RIGHT:
			_update_lightning_attack()
		Attack.FIRE_LEFT, Attack.FIRE_RIGHT:
			_update_fire_attack()
		Attack.ICE_LEFT, Attack.ICE_RIGHT:
			_update_ice_attack()


func _update_target_attack() -> void:
	if timer % 15 == 0:
		attack_requested.emit(75, player.position + Vector2(-2, 16), 0, 0)
	elif timer >= 160:
		_finish_attack()


func _update_lightning_attack() -> void:
	if timer == 25:
		flash_requested.emit(0.5)
	elif timer == 26:
		flash_requested.emit(1.0)
	elif timer == 27:
		flash_requested.emit(0.5)
	elif timer == 28:
		flash_requested.emit(0.0)
	elif timer > 25 and timer % 10 == 0:
		var lane := randi_range(Attack.TARGET, Attack.ICE_RIGHT)
		while lane == attack_kind:
			lane = randi_range(Attack.TARGET, Attack.ICE_RIGHT)
		var lane_data: Vector2 = LIGHTNING_LANES[lane]
		attack_requested.emit(76, Vector2(lane_data.x + randi_range(0, int(lane_data.y) - 1), 0), 0, 0)
	elif timer >= 128:
		_finish_attack()


func _update_fire_attack() -> void:
	if timer == FIRE_SPAWN_TIMES[0]:
		finished_fire_orbits = 0
	var spawn_index := FIRE_SPAWN_TIMES.find(timer)
	if spawn_index >= 0:
		var projectile_type := 77 if attack_kind == Attack.FIRE_LEFT else 78
		attack_requested.emit(projectile_type, position + Vector2(30, 80), 0, spawn_index + 1)


func on_fire_orbit_finished() -> void:
	if state != BossState.ATTACK or attack_kind not in [Attack.FIRE_LEFT, Attack.FIRE_RIGHT]:
		return
	finished_fire_orbits += 1
	if finished_fire_orbits == FIRE_SPAWN_TIMES.size():
		_finish_attack()


func _update_ice_attack() -> void:
	var direction := 1 if attack_kind == Attack.ICE_LEFT else 0
	if timer == 25:
		for ice_variant in range(1, 6):
			attack_requested.emit(79, _ice_origin(direction, ice_variant), direction, ice_variant)
	elif ICE_TIMES.has(timer):
		var ice_variant := _targeted_ice_variant(direction)
		attack_requested.emit(79, _ice_origin(direction, ice_variant), direction, ice_variant)
	elif timer >= 200:
		_finish_attack()


func _ice_origin(direction: int, ice_variant: int) -> Vector2:
	var left_offsets := [Vector2.ZERO, Vector2(-30, 9), Vector2(-70, 44), Vector2(-80, 70), Vector2(-70, 90), Vector2(-30, 110)]
	var right_offsets := [Vector2.ZERO, Vector2(87, 9), Vector2(102, 44), Vector2(106, 70), Vector2(102, 90), Vector2(87, 110)]
	return position + (left_offsets[ice_variant] if direction == 1 else right_offsets[ice_variant])


func _targeted_ice_variant(direction: int) -> int:
	if player.position.y < 160.0:
		if (direction == 1 and player.position.x < 1240.0) or (direction == 0 and player.position.x > 1240.0):
			return 4
		return 5
	if player.position.y <= 301.0:
		return 3
	if (direction == 1 and player.position.x < 1240.0) or (direction == 0 and player.position.x > 1240.0):
		return 2
	return 1


func _finish_attack() -> void:
	last_attack = attack_kind
	vulnerable = false
	state = BossState.FADE_OUT
	timer = 0
	flash_requested.emit(0.0)


func _update_fade_out() -> void:
	timer += 1
	if timer <= 10:
		sprite.modulate.a = maxf(0.0, sprite.modulate.a - 32.0 / 255.0)
	elif timer == 11:
		position = Vector2(10, 10)
	else:
		var target = 90 if last_attack == Attack.FIRE_LEFT or last_attack == Attack.FIRE_RIGHT else 50
		if timer >= target:
			var next_attack: Attack = randi_range(Attack.TARGET, Attack.ICE_RIGHT) as Attack
			while next_attack == last_attack:
				next_attack = randi_range(Attack.TARGET, Attack.ICE_RIGHT) as Attack
			attack_kind = next_attack
			position = ATTACK_POSITIONS[attack_kind]
			state = BossState.FADE_IN
			timer = 0
			hit_this_appearance = false
			sprite.modulate.a = 0.0
