class_name PirikitoEnemy
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world1/bird_1.png"),
	preload("res://assets/world1/bird_2.png"),
	preload("res://assets/world1/bird_3.png"),
]
const MOVEMENT_SCALE := 1.0
const TIMING_SCALE := 2
const ASCENT_DISTANCE_SCALE := 101.25 / 98.16

var timer := 0
var vertical_speed := 0.0
var base_y := 0.0


func configure(initial_timer: int = 0) -> void:
	set_update_interval(1)
	body_size = Vector2(37, 33)
	hit_points = 3
	contact_damage = 2
	drops_recovery = false
	timer = initial_timer * TIMING_SCALE
	base_y = position.y
	sprite.texture = FRAMES[0]


func _update_enemy() -> void:
	timer += 1
	var source_tick := int((timer - 1) / float(TIMING_SCALE)) + 1
	var substep := (timer - 1) % TIMING_SCALE
	if source_tick >= 1 and source_tick < 46:
		if substep == 0 and not is_equal_approx(vertical_speed, 2.5):
			vertical_speed += 0.25
		position.y += vertical_speed * MOVEMENT_SCALE / float(TIMING_SCALE)
	if source_tick >= 46 and source_tick < 76:
		if substep == 0:
			if is_equal_approx(vertical_speed, 2.5):
				vertical_speed = -6.0
			vertical_speed += 0.176
		position.y += vertical_speed * ASCENT_DISTANCE_SCALE * MOVEMENT_SCALE / float(TIMING_SCALE)
	if source_tick == 45:
		sprite.texture = FRAMES[1]
	if source_tick == 46:
		sprite.texture = FRAMES[2]
	if source_tick == 48:
		sprite.texture = FRAMES[1]
	if source_tick == 49:
		sprite.texture = FRAMES[0]
	elif source_tick == 76 and substep == TIMING_SCALE - 1:
		timer = 0
		vertical_speed = 0.0
		position.y = base_y
