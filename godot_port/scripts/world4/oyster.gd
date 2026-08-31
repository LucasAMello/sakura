class_name World4Oyster
extends SakuraEnemy

signal pearl_requested(spawn_position: Vector2)

const CLOSED_TEXTURE := preload("res://assets/world4/oyster_closed.png")
const OPEN_TEXTURE := preload("res://assets/world4/oyster_open.png")
const MIRRORED_TEXTURE := preload("res://assets/world4/oyster_mirrored.png")

var direction := 0
var state := 0
var timer := 0


func configure(facing_direction: int) -> void:
	direction = facing_direction
	body_size = Vector2(43.0, 27.0)
	hit_points = 2
	contact_damage = 3
	drops_recovery = true
	sprite.texture = CLOSED_TEXTURE
	sprite.flip_h = direction == 1


func _update_enemy() -> void:
	if not is_instance_valid(player):
		return
	if state == 0:
		var horizontal_offset := player.get_center().x - get_hit_rect().get_center().x
		var player_on_firing_side := horizontal_offset >= 0.0 if direction == 0 else horizontal_offset <= 0.0
		if player_on_firing_side and absf(horizontal_offset) <= 360.0:
			state = 1
			timer = 0
		return
	timer += 1
	match state:
		1:
			_update_opening()
		2:
			if timer >= 10:
				state = 3
				timer = 0
				position += Vector2(-6.0 if direction == 0 else 6.0, 6.0)
				body_size = Vector2(46.0, 38.0)
				sprite.texture = MIRRORED_TEXTURE if direction == 1 else CLOSED_TEXTURE
		3:
			_update_closing()
		4:
			if timer >= 40:
				state = 0
				timer = 0
				body_size = Vector2(43.0, 27.0)
				sprite.texture = CLOSED_TEXTURE
				sprite.rotation_degrees = 0.0


func _update_opening() -> void:
	if timer == 1:
		pearl_requested.emit(position + Vector2(17.0, 4.0))
	if timer >= 4 and timer <= 6:
		var step_index := timer - 4
		var x_steps := [2.0, 3.0, 4.0]
		var y_steps := [-5.0, -4.0, -3.0]
		position += Vector2(x_steps[step_index] * (-1.0 if direction == 1 else 1.0), y_steps[step_index])
		sprite.rotation_degrees += -11.0 if direction == 1 else 11.0
	elif timer >= 7:
		position += Vector2(-6.0 if direction == 1 else 6.0, -6.0)
		state = 2
		timer = 0
		body_size = Vector2(31.0, 37.0)
		sprite.texture = OPEN_TEXTURE
		sprite.rotation_degrees = 0.0


func _update_closing() -> void:
	if timer >= 2 and timer <= 4:
		var step_index := timer - 2
		var x_steps := [4.0, 3.0, 2.0]
		var y_steps := [3.0, 4.0, 5.0]
		position += Vector2(x_steps[step_index] * (1.0 if direction == 1 else -1.0), y_steps[step_index])
		sprite.rotation_degrees += 11.0 if direction == 1 else -11.0
	elif timer >= 5:
		state = 4
		timer = 0
		sprite.rotation_degrees = 0.0
