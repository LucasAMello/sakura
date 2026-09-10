class_name World4Fish
extends SakuraEnemy

const ALERT_TEXTURE := preload("res://assets/world4/fish_alert.png")

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
var alert_sprite: Sprite2D
var alert_ticks := 0


func _ready() -> void:
	super._ready()
	alert_sprite = Sprite2D.new()
	alert_sprite.centered = false
	alert_sprite.texture = ALERT_TEXTURE
	alert_sprite.z_index = 18
	alert_sprite.visible = false
	add_child(alert_sprite)
	alert_sprite.top_level = true


func configure(surface_y: float, texture_variant: int = -1) -> void:
	set_update_interval(1)
	water_surface_y = surface_y
	variant = randi_range(0, TEXTURES.size() - 1) if texture_variant < 0 else clampi(texture_variant, 0, TEXTURES.size() - 1)
	body_size = Vector2(40.0, 20.0)
	hit_points = 3
	contact_damage = 2
	drops_recovery = true
	sprite.texture = TEXTURES[variant][0]


func take_weapon_hit(damage: int, weapon_id: int) -> void:
	take_projectile_hit(4 if weapon_id == 4 else damage)


func _update_enemy() -> void:
	if alert_ticks > 0:
		alert_ticks -= 1
		alert_sprite.visible = alert_ticks > 0
	if not is_instance_valid(player):
		return
	var offset := player.position - position
	var horizontal_gap := -offset.x - 40.0 if offset.x < 0.0 else offset.x - 20.0
	if state == 0:
		if not is_zero_approx(offset.x) and horizontal_gap < 260.0:
			state = 1
			timer = 0
			sprite.texture = TEXTURES[variant][1]
			alert_sprite.global_position = global_position + Vector2(50.0 if sprite.flip_h else -10.0, -23.0)
			alert_ticks = 24
			alert_sprite.visible = true
		else:
			timer = (timer + 1) % 80
			_update_idle_bob()
		return
	if not is_zero_approx(offset.x) and horizontal_gap > 300.0:
		sprite.texture = TEXTURES[variant][1 if absf(velocity.x) > 1.0 else 0]
		if absf(velocity.y) > 0.4:
			velocity.y -= signf(velocity.y) * 0.05
		if absf(velocity.x) > 0.4:
			velocity.x -= signf(velocity.x) * 0.05
		else:
			state = 0
			timer = 0
			velocity = Vector2.ZERO
		_move_with_terrain(velocity * 0.25)
		return
	timer += 1
	if timer % 8 == 0:
		sprite.texture = TEXTURES[variant][1 if timer % 16 == 0 else 2]
	var x_acceleration := 0.2 if signf(offset.x) != signf(velocity.x) and not is_zero_approx(velocity.x) else 0.1
	velocity.x = clampf(velocity.x + signf(offset.x) * x_acceleration, -10.0, 10.0)
	velocity.y = clampf(velocity.y + signf(offset.y) * 0.1, -10.0, 10.0)
	if not is_zero_approx(offset.x):
		sprite.flip_h = offset.x > 0.0
	_move_with_terrain(velocity * 0.25)


func _update_idle_bob() -> void:
	match int((timer + 3) / 4.0) % 20:
		2, 4, 12, 14:
			_move_with_terrain(Vector2(0.0, 0.25 if timer < 40 else -0.25))
		6, 16:
			_move_with_terrain(Vector2(0.0, 0.5 if timer < 40 else -0.5))
		8, 18:
			_move_with_terrain(Vector2(0.0, 0.25 if timer < 40 else -0.25))


func _move_with_terrain(amount: Vector2) -> void:
	_move_axis(Vector2(amount.x, 0.0))
	_move_axis(Vector2(0.0, amount.y))
	if position.y < water_surface_y:
		position.y = water_surface_y


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
