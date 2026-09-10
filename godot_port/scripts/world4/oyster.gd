class_name World4Oyster
extends SakuraEnemy

signal pearl_requested(spawn_position: Vector2, shot_direction: int)

const CLOSED_TEXTURE := preload("res://assets/world4/oyster_closed.png")
const OPEN_TEXTURE := preload("res://assets/world4/oyster_open.png")
const MIRRORED_TEXTURE := preload("res://assets/world4/oyster_mirrored.png")

var direction := 0
var state := 0
var timer := 0
var rotation_units := 0.0


func configure(facing_direction: int) -> void:
	set_update_interval(1)
	direction = facing_direction
	body_size = Vector2(43.0, 27.0)
	hit_points = 2
	contact_damage = 2
	drops_recovery = true
	sprite.texture = CLOSED_TEXTURE
	sprite.flip_h = direction == 1


func _update_enemy() -> void:
	if not is_instance_valid(player):
		return
	if state == 0:
		var horizontal_offset := player.position.x - position.x
		var player_on_firing_side := horizontal_offset > 0.0 if direction == 1 else horizontal_offset < 0.0
		var horizontal_gap := horizontal_offset - 36.0 if direction == 1 else -horizontal_offset - 40.0
		if player_on_firing_side and horizontal_gap < 360.0:
			state = 1
			timer = 0
		_update_shell_visual()
		return
	timer += 1
	match state:
		1:
			_update_opening()
		2:
			if timer >= 40:
				state = 3
				timer = 0
				position += Vector2(-6.0, 6.0)
				body_size = Vector2(46.0, 38.0)
				sprite.texture = CLOSED_TEXTURE
		3:
			_update_closing()
		4:
			if timer >= 160:
				state = 0
				timer = 0
				body_size = Vector2(43.0, 27.0)
				sprite.texture = CLOSED_TEXTURE
				sprite.rotation_degrees = 0.0
	_update_shell_visual()


func _update_opening() -> void:
	if timer == 4:
		pearl_requested.emit(position + Vector2(17.0, 4.0), direction)
	if timer >= 13 and timer <= 24:
		var step_index := int((timer - 13) / 4.0)
		var x_steps := [2.0, 3.0, 4.0]
		var y_steps := [-5.0, -4.0, -3.0]
		position += Vector2(x_steps[step_index] * (-1.0 if direction == 1 else 1.0), y_steps[step_index]) * 0.25
		body_size = Vector2(46.0, 38.0)
		rotation_units += -2.75 if direction == 1 else 2.75
	elif timer >= 28:
		position += Vector2(6.0, -6.0)
		state = 2
		timer = 0
		body_size = Vector2(31.0, 37.0)
		sprite.texture = OPEN_TEXTURE
		sprite.rotation_degrees = 0.0


func _update_closing() -> void:
	if timer >= 5 and timer <= 16:
		var step_index := int((timer - 5) / 4.0)
		var x_steps := [4.0, 3.0, 2.0]
		var y_steps := [3.0, 4.0, 5.0]
		position += Vector2(x_steps[step_index] * (1.0 if direction == 1 else -1.0), y_steps[step_index]) * 0.25
		rotation_units += 2.75 if direction == 1 else -2.75
		if timer == 16:
			body_size = Vector2(43.0, 21.0)
	elif timer >= 20:
		state = 4
		timer = 0
		sprite.rotation_degrees = 0.0


func _update_shell_visual() -> void:
	var rotating := state == 1 or state == 3
	sprite.texture = OPEN_TEXTURE if state == 2 else MIRRORED_TEXTURE if rotating and direction == 1 else CLOSED_TEXTURE
	sprite.flip_h = direction == 1 and not rotating
	sprite.centered = rotating
	sprite.position = sprite.texture.get_size() * 0.5 if rotating else Vector2.ZERO
	sprite.rotation_degrees = rotation_units * 360.0 / 256.0 if rotating else 0.0
