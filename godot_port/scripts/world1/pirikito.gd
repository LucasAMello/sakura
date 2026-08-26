class_name PirikitoEnemy
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world1/bird_1.png"),
	preload("res://assets/world1/bird_2.png"),
	preload("res://assets/world1/bird_3.png"),
]
const MOVEMENT_SCALE := 0.75

var timer := 0
var vertical_speed := 0.0
var base_y := 0.0


func configure(initial_timer: int = 0) -> void:
	body_size = Vector2(37, 33)
	hit_points = 3
	contact_damage = 2
	drops_recovery = false
	timer = initial_timer
	base_y = position.y
	sprite.texture = FRAMES[0]


func _update_enemy() -> void:
	timer += 1
	if timer >= 1 and timer < 46:
		if not is_equal_approx(vertical_speed, 2.5):
			vertical_speed += 0.25
		position.y += vertical_speed * MOVEMENT_SCALE
	if timer >= 46 and timer < 76:
		if is_equal_approx(vertical_speed, 2.5):
			vertical_speed = -6.0
		vertical_speed += 0.176
		position.y += vertical_speed * MOVEMENT_SCALE
	if timer == 45:
		sprite.texture = FRAMES[1]
	if timer == 46:
		sprite.texture = FRAMES[2]
	if timer == 48:
		sprite.texture = FRAMES[1]
	if timer == 49:
		sprite.texture = FRAMES[0]
	elif timer == 76:
		timer = 0
		vertical_speed = 0.0
		position.y = base_y
