class_name HappySpringEnemy
extends SakuraEnemy

const IDLE_TEXTURE := preload("res://assets/world1/spring_idle.png")
const JUMP_TEXTURE := preload("res://assets/world1/spring_jump.png")

var timer := 0
var vertical_speed := 3.0
var base_y := 0.0
const TIMING_SCALE := 3


func configure(initial_timer: int = 0) -> void:
	body_size = Vector2(40, 60)
	hit_points = 6
	contact_damage = 3
	drops_recovery = true
	timer = initial_timer * TIMING_SCALE
	base_y = position.y
	sprite.texture = IDLE_TEXTURE


func _update_enemy() -> void:
	timer += 1
	var source_tick := int((timer - 1) / float(TIMING_SCALE)) + 1
	var substep := (timer - 1) % TIMING_SCALE
	if source_tick >= 40 and source_tick < 48:
		_set_airborne()
		position.y -= vertical_speed * 5.0 / float(TIMING_SCALE)
		if substep == TIMING_SCALE - 1:
			vertical_speed -= 0.16
	elif source_tick >= 48 and source_tick < 60:
		_set_airborne()
		if substep == 0:
			vertical_speed -= 0.16
		position.y -= vertical_speed * 5.0 / float(TIMING_SCALE)
	elif source_tick >= 80 and source_tick < 88:
		_set_airborne()
		position.y -= vertical_speed * 5.0 / float(TIMING_SCALE)
		if substep == TIMING_SCALE - 1:
			vertical_speed -= 0.14
	elif source_tick >= 88 and source_tick < 96:
		if substep == 0:
			vertical_speed -= 0.13
		position.y -= vertical_speed * 5.0 / float(TIMING_SCALE)
	elif source_tick >= 96 and source_tick < 100:
		if substep == 0:
			vertical_speed -= 0.12
		position.y -= vertical_speed * 5.0 / float(TIMING_SCALE)

	if source_tick == 59 and substep == TIMING_SCALE - 1:
		timer = 79 * TIMING_SCALE
		vertical_speed = 0.0
	elif source_tick == 99 and substep == TIMING_SCALE - 1:
		position.y = base_y
		vertical_speed = 3.0
		timer = 0
		body_size = Vector2(40, 60)
		sprite.texture = IDLE_TEXTURE

	if is_instance_valid(player):
		sprite.flip_h = player.position.x >= position.x + 20.0


func _set_airborne() -> void:
	body_size = Vector2(40, 73)
	sprite.texture = JUMP_TEXTURE


func _drop_position(_drop_type: int) -> Vector2:
	return position + Vector2(10, 25)
