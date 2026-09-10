class_name RedBallEnemy
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world1/red_ball_1.png"),
	preload("res://assets/world1/red_ball_2.png"),
	preload("res://assets/world1/red_ball_3.png"),
	preload("res://assets/world1/red_ball_4.png"),
	preload("res://assets/world1/red_ball_5.png"),
]
const ANIMATION_SEQUENCE := [
	FRAMES[0], FRAMES[1], FRAMES[2], FRAMES[1],
	FRAMES[0], FRAMES[3], FRAMES[4], FRAMES[3],
]
const animation_speed := 8
var move_direction := -1
var animation_tick := 0
const speed := 1.5
const ground_probe_depth := 10

func configure(initial_direction: int) -> void:
	set_update_interval(1)
	body_size = Vector2(40, 40)
	hit_points = 5
	contact_damage = 1
	drops_recovery = true
	move_direction = 1 if initial_direction == 1 else -1
	sprite.texture = FRAMES[0]
	sprite.flip_h = move_direction >= 0


func _update_enemy() -> void:
	animation_tick = (animation_tick + 1) % (15 * 4)
	var current_frame := int(animation_tick / float(animation_speed))
	sprite.texture = ANIMATION_SEQUENCE[current_frame]

	var step := Vector2(move_direction * speed, 0)
	var candidate := Rect2(position + step, body_size)
	var leading_x := candidate.end.x - 1.0 if move_direction > 0 else candidate.position.x
	var wall_a := terrain.is_solid_at(Vector2(leading_x, candidate.position.y + 4))
	var wall_b := terrain.is_solid_at(Vector2(leading_x, candidate.end.y - 4))
	var floor_left := terrain.has_solid_below(Vector2(candidate.position.x + 1, candidate.end.y), ground_probe_depth)
	var floor_right := terrain.has_solid_below(Vector2(candidate.end.x - 2, candidate.end.y), ground_probe_depth)
	if wall_a or wall_b or not floor_left or not floor_right:
		move_direction *= -1
		sprite.flip_h = move_direction >= 0
	else:
		position += step
