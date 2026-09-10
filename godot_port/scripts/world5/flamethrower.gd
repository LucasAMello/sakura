class_name World5Flamethrower
extends SakuraEnemy

signal flame_requested(vertical: bool, spawn_position: Vector2, direction: int)

const HORIZONTAL_TEXTURE := preload("res://assets/world5/flamethrower_horizontal.png")
const VERTICAL_TEXTURE := preload("res://assets/world5/flamethrower_vertical.png")

var vertical := false
var direction := 0
var timer := 0


func configure(is_vertical: bool, facing: int, initial_timer: int) -> void:
	set_update_interval(1)
	vertical = is_vertical
	direction = facing
	timer = initial_timer * 4
	body_size = Vector2(40, 80) if vertical else Vector2(80, 40)
	hit_points = 1
	contact_damage = 0
	drops_recovery = false
	sprite.texture = VERTICAL_TEXTURE if vertical else HORIZONTAL_TEXTURE
	sprite.flip_v = vertical and direction == 0
	sprite.flip_h = not vertical and direction == 1


func _update_enemy() -> void:
	if timer == 183:
		var spawn_position: Vector2
		var flame_direction: int
		if vertical:
			var offset := Vector2(-9, -90 if direction == 1 else 80)
			spawn_position = position + offset
			flame_direction = direction
		else:
			var offset := Vector2(-90 if direction == 1 else 80, -9)
			spawn_position = position + offset
			flame_direction = 0 if direction == 1 else 1
		flame_requested.emit(vertical, spawn_position, flame_direction)
	if timer == 307:
		timer = 3
	timer += 1


func take_projectile_hit(_damage: int) -> void:
	pass
