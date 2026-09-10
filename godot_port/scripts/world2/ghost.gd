class_name GhostEnemy
extends SakuraEnemy

const TEXTURES := [
	preload("res://assets/world2/ghost_1.png"),
	preload("res://assets/world2/ghost_2.png"),
	preload("res://assets/world2/ghost_3.png"),
	preload("res://assets/world2/ghost_4.png"),
]

var action_state := 0
var timer := 0
var x_velocity := 0.0
var y_velocity := 0.0
var alpha_level := 20.0


func set_update_interval(_ticks: int) -> void:
	super.set_update_interval(1)


func _ready() -> void:
	super._ready()
	body_size = Vector2(40, 51)
	hit_points = 5
	contact_damage = 2
	drops_recovery = true
	sprite.texture = TEXTURES[3]
	sprite.modulate.a = float(alpha_level) / 255.0


func get_hit_rect() -> Rect2:
	if action_state == 0:
		return Rect2(position, Vector2.ZERO)
	return super.get_hit_rect()


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return action_state != 0 and super.projectile_mask_overlap(projectile_rect)


func _update_enemy() -> void:
	var x_distance := absf(player.position.x - position.x)
	var in_vertical_range := player.position.y < position.y + 290.0 and player.position.y > position.y - 250.0
	if action_state == 0:
		alpha_level = 20
		sprite.texture = TEXTURES[3]
		if x_distance < 300.0 and in_vertical_range:
			action_state = 1
			sprite.texture = TEXTURES[2]
	else:
		if x_distance > 300.0 or not in_vertical_range:
			_slow_to_rest()
		else:
			timer += 1
			if timer % 20 == 0:
				var frame_index := TEXTURES.find(sprite.texture)
				if frame_index == 0 or frame_index == 2:
					sprite.texture = TEXTURES[1]
				else:
					sprite.texture = TEXTURES[0]
			if player.position.x < position.x:
				if x_velocity > 0.0:
					x_velocity -= 0.1
					alpha_level = int(150.0 - (x_distance + 20.0) * 0.5)
				else:
					x_velocity -= 0.075
					alpha_level = int(170.0 - (x_distance + 20.0) * 0.5)
				sprite.flip_h = false
			elif player.position.x > position.x:
				if x_velocity < 0.0:
					x_velocity += 0.1
					alpha_level = int(150.0 - (x_distance + 20.0) * 0.5)
				else:
					x_velocity += 0.075
					alpha_level = int(170.0 - (x_distance + 20.0) * 0.5)
				sprite.flip_h = true
			if player.position.y < position.y:
				y_velocity -= 0.075
			elif player.position.y > position.y:
				y_velocity += 0.075
			x_velocity = clampf(x_velocity, -5.0, 5.0)
			y_velocity = clampf(y_velocity, -5.0, 5.0)
			alpha_level = clampf(alpha_level, 20.0, 128.0)
		position += Vector2(x_velocity, y_velocity) / 2.0
	sprite.modulate.a = float(alpha_level) / 255.0


func _slow_to_rest() -> void:
	sprite.texture = TEXTURES[2] if absf(x_velocity) > 1.0 else TEXTURES[3]
	alpha_level = maxf(20.0, alpha_level - 2.5)
	x_velocity = move_toward(x_velocity, 0.0, 0.05)
	y_velocity = move_toward(y_velocity, 0.0, 0.05)
	if absf(x_velocity) <= 0.4 and absf(y_velocity) <= 0.4:
		x_velocity = 0.0
		y_velocity = 0.0
		action_state = 0
