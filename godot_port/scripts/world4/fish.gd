class_name World4Fish
extends SakuraEnemy

const TEXTURES := [
	[
		preload("res://assets/world4/fish_1_1.png"),
		preload("res://assets/world4/fish_1_2.png"),
		preload("res://assets/world4/fish_1_3.png"),
	],
	[
		preload("res://assets/world4/fish_2_1.png"),
		preload("res://assets/world4/fish_2_2.png"),
		preload("res://assets/world4/fish_2_3.png"),
	],
	[
		preload("res://assets/world4/fish_3_1.png"),
		preload("res://assets/world4/fish_3_2.png"),
		preload("res://assets/world4/fish_3_3.png"),
	],
	[
		preload("res://assets/world4/fish_4_1.png"),
		preload("res://assets/world4/fish_4_2.png"),
		preload("res://assets/world4/fish_4_3.png"),
	],
]

var water_surface_y := 0.0
var variant := 0
var state := 0
var timer := 0
var velocity := Vector2.ZERO


func configure(surface_y: float, texture_variant: int = -1) -> void:
	water_surface_y = surface_y
	variant = randi_range(0, TEXTURES.size() - 1) if texture_variant < 0 else clampi(texture_variant, 0, TEXTURES.size() - 1)
	body_size = Vector2(40.0, 20.0)
	hit_points = 3
	contact_damage = 2
	drops_recovery = true
	sprite.texture = TEXTURES[variant][0]


func _update_enemy() -> void:
	if not is_instance_valid(player):
		return
	var offset := player.get_center() - get_hit_rect().get_center()
	if state == 0:
		timer = (timer + 1) % 20
		_update_idle_bob()
		if absf(offset.x) <= 260.0:
			state = 1
			timer = 0
			sprite.texture = TEXTURES[variant][1]
		return
	if absf(offset.x) > 300.0:
		velocity.x = move_toward(velocity.x, 0.0, 0.2)
		velocity.y = move_toward(velocity.y, 0.0, 0.2)
		_move_with_terrain(velocity)
		if velocity.is_zero_approx():
			state = 0
			timer = 0
			sprite.texture = TEXTURES[variant][0]
		return
	timer += 1
	sprite.texture = TEXTURES[variant][1 if timer % 4 == 0 else 2 if timer % 2 == 0 else 1]
	var x_acceleration := 0.4 if signf(offset.x) != signf(velocity.x) and not is_zero_approx(velocity.x) else 0.3
	velocity.x = clampf(velocity.x + signf(offset.x) * x_acceleration, -5.0, 5.0)
	velocity.y = clampf(velocity.y + signf(offset.y) * 0.3, -5.0, 5.0)
	sprite.flip_h = velocity.x < 0.0
	_move_with_terrain(velocity)


func _update_idle_bob() -> void:
	match timer:
		2, 4, 12, 14:
			_move_with_terrain(Vector2(0.0, 1.0 if timer < 10 else -1.0))
		6, 16:
			_move_with_terrain(Vector2(0.0, 2.0 if timer < 10 else -2.0))
		8, 18:
			_move_with_terrain(Vector2(0.0, 1.0 if timer < 10 else -1.0))


func _move_with_terrain(amount: Vector2) -> void:
	_move_axis(Vector2(amount.x, 0.0))
	_move_axis(Vector2(0.0, amount.y))
	if position.y < water_surface_y:
		position.y = water_surface_y
		velocity.y = maxf(0.0, velocity.y)


func _move_axis(amount: Vector2) -> void:
	var distance := absf(amount.x if amount.x != 0.0 else amount.y)
	if distance <= 0.0:
		return
	var direction := amount.normalized()
	while distance > 0.0:
		var step := direction * minf(1.0, distance)
		if terrain.rect_hits_solid(Rect2(position + step, body_size)):
			if amount.x != 0.0:
				velocity.x = 0.0
			else:
				velocity.y = 0.0
			return
		position += step
		distance -= step.length()
