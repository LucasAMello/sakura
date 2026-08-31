class_name World4Seahorse
extends SakuraEnemy

const TEXTURES := [
	preload("res://assets/world4/seahorse_1.png"),
	preload("res://assets/world4/seahorse_2.png"),
	preload("res://assets/world4/seahorse_3.png"),
]

var water_surface_y := 0.0
var state := 1
var timer := 0
var horizontal_speed := 0.0
var visible_height := 0.0


func configure(surface_y: float) -> void:
	water_surface_y = surface_y
	body_size = Vector2(36.0, 0.0)
	hit_points = 3
	contact_damage = 2
	drops_recovery = true
	sprite.texture = TEXTURES[0]
	sprite.region_enabled = true
	sprite.visible = false
	_update_sprite_geometry()


func _update_enemy() -> void:
	if not is_instance_valid(player):
		return
	timer += 1
	match state:
		1:
			_update_emergence()
		2:
			if timer >= 6:
				state = 3
				timer = 0
				body_size = Vector2(30.0, 30.0)
				sprite.texture = TEXTURES[2]
				sprite.region_enabled = false
				_update_sprite_geometry()
		3:
			if timer == 1:
				horizontal_speed = -25.0 if player.get_center().x < get_hit_rect().get_center().x else 25.0
			if timer >= 10:
				position.x += horizontal_speed
				sprite.rotation_degrees += 24.0
			if absf(player.position.x - position.x) > 640.0:
				queue_free()


func _update_emergence() -> void:
	if timer <= 3:
		var growth := minf(17.0, 51.0 - visible_height)
		visible_height += growth
		position.y -= growth
		body_size.y = visible_height
		sprite.visible = true
		_update_sprite_geometry()
		return
	if position.y <= player.position.y or position.y <= water_surface_y + 20.0:
		position.y = maxf(position.y, water_surface_y + 20.0)
		state = 2
		timer = 0
		body_size = Vector2(40.0, 41.0)
		sprite.texture = TEXTURES[1]
		sprite.region_enabled = false
		_update_sprite_geometry()
	else:
		position.y -= 17.0


func _update_sprite_geometry() -> void:
	if sprite.region_enabled:
		sprite.region_rect = Rect2(0.0, 51.0 - visible_height, 36.0, visible_height)
	sprite.centered = false
	sprite.position = Vector2.ZERO


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return visible_height > 0.0 and get_hit_rect().intersects(projectile_rect)
