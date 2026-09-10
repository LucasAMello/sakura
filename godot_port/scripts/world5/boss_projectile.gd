class_name World5BossProjectile
extends SakuraEnemy

enum Kind { SPRAY, HADOUKEN, SLASH_STRAIGHT, SLASH_RISING }

const SPRAY_FRAMES := [
	preload("res://assets/world5/boss_spray_1.png"),
	preload("res://assets/world5/boss_spray_2.png"),
	preload("res://assets/world5/boss_spray_3.png"),
	preload("res://assets/world5/boss_spray_4.png"),
	preload("res://assets/world5/boss_spray_5.png"),
	preload("res://assets/world5/boss_spray_6.png"),
	preload("res://assets/world5/boss_spray_7.png"),
]
const HADOUKEN_FRAMES := [
	preload("res://assets/world5/boss_hadouken_1.png"),
	preload("res://assets/world5/boss_hadouken_2.png"),
	preload("res://assets/world5/boss_hadouken_3.png"),
	preload("res://assets/world5/boss_hadouken_4.png"),
	preload("res://assets/world5/boss_hadouken_5.png"),
	preload("res://assets/world5/boss_hadouken_6.png"),
	preload("res://assets/world5/boss_hadouken_7.png"),
]
const SLASH_FRAMES := [
	preload("res://assets/world5/boss_slash_1.png"),
	preload("res://assets/world5/boss_slash_2.png"),
]

var kind := Kind.SPRAY
var direction := 1
var state := 0
var timer := 0
var velocity := Vector2.ZERO


func configure(projectile_kind: Kind, facing: int) -> void:
	set_update_interval(1)
	kind = projectile_kind
	direction = facing
	drops_recovery = false
	match kind:
		Kind.SPRAY:
			body_size = Vector2(25, 20)
			contact_damage = 2
			timer = randi() % 4
			velocity = Vector2(-(16 + randi() % 12), -3 + randi() % 4)
			sprite.texture = SPRAY_FRAMES[timer]
			timer *= 4
			sprite.flip_h = direction == 1
		Kind.HADOUKEN:
			body_size = Vector2(31, 24)
			contact_damage = 7
			velocity.x = -40.0
			sprite.texture = HADOUKEN_FRAMES[0]
			sprite.flip_h = direction == 1
		Kind.SLASH_STRAIGHT:
			body_size = Vector2(20, 40)
			contact_damage = 3
			velocity.x = -30.0
			sprite.texture = SLASH_FRAMES[0]
			sprite.flip_h = direction == 1
		Kind.SLASH_RISING:
			body_size = Vector2(27, 37)
			contact_damage = 3
			velocity = Vector2(-25, -14)
			sprite.texture = SLASH_FRAMES[1]
			sprite.flip_h = direction == 1


func _update_enemy() -> void:
	match kind:
		Kind.SPRAY:
			_update_spray()
		Kind.HADOUKEN:
			_update_hadouken()
		Kind.SLASH_STRAIGHT, Kind.SLASH_RISING:
			_update_slash()


func _update_spray() -> void:
	if state == 1:
		timer += 1
		if timer >= 28:
			queue_free()
			return
		if timer >= 4:
			sprite.texture = SPRAY_FRAMES[4 + int((timer - 4) / 8.0)]
		return
	var source_tick := int(timer / 4.0)
	sprite.texture = SPRAY_FRAMES[source_tick % 4]
	if timer % 4 == 0 and source_tick % 2 == 1:
		velocity.y += 1.0
	timer += 1
	if _move_axis(Vector2(0, velocity.y * 0.25)):
		_begin_impact()
		return
	if _move_axis(Vector2(velocity.x * 0.25, 0)):
		_begin_impact()
		return
	if is_instance_valid(player) and get_hit_rect().intersects(player.get_hit_rect()):
		player.take_damage(contact_damage)
		queue_free()


func _update_hadouken() -> void:
	if state == 1:
		timer += 1
		if timer >= 24:
			queue_free()
			return
		if timer == 4:
			position += Vector2(-18, -17)
			body_size = Vector2(58, 53)
		if timer >= 4:
			sprite.texture = HADOUKEN_FRAMES[2 + int((timer - 4) / 4.0)]
		return
	sprite.texture = HADOUKEN_FRAMES[int(timer / 8.0) % 2]
	timer += 1
	if _move_axis(Vector2(velocity.x * 0.125, 0)) or _move_axis(Vector2(velocity.x * 0.125, 0)):
		_begin_impact()
		return
	if is_instance_valid(player) and get_hit_rect().intersects(player.get_hit_rect()):
		player.take_damage(contact_damage)
		position.x = player.position.x + 40.0
		_begin_impact()


func _update_slash() -> void:
	if _move_axis(Vector2(velocity.x * 0.25, 0)):
		queue_free()
		return
	if kind == Kind.SLASH_RISING and _move_axis(Vector2(0, velocity.y * 0.25)):
		queue_free()


func _move_axis(amount: Vector2) -> bool:
	var distance := absf(amount.x if amount.x != 0.0 else amount.y)
	if distance <= 0.0:
		return false
	var step_direction := amount.normalized()
	while distance > 0.0:
		var step := step_direction * minf(1.0, distance)
		if terrain.rect_hits_solid(Rect2(position + step, body_size)):
			return true
		position += step
		distance -= step.length()
	return false


func _begin_impact() -> void:
	if kind == Kind.HADOUKEN:
		get_node("/root/AudioManager").play_sfx("haduex")
	state = 1
	timer = 0
	contact_damage = 0


func take_projectile_hit(_damage: int) -> void:
	if kind == Kind.SPRAY:
		queue_free()
