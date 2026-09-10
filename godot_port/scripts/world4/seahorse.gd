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
	set_update_interval(1)
	water_surface_y = surface_y
	body_size = Vector2(36.0, 0.0)
	hit_points = 3
	contact_damage = 2
	drops_recovery = true
	sprite.texture = TEXTURES[0]
	sprite.region_enabled = true
	sprite.visible = false
	_update_sprite_geometry()


func take_weapon_hit(damage: int, weapon_id: int) -> void:
	take_projectile_hit(4 if weapon_id == 4 else damage)


func _update_enemy() -> void:
	if not is_instance_valid(player):
		return
	if state != 3 or timer == 0:
		sprite.flip_h = player.position.x > position.x
	timer += 1
	match state:
		1:
			_update_emergence()
		2:
			if timer >= 24:
				state = 3
				timer = 0
				if sprite.flip_h:
					position.x += body_size.x - 40.0
				body_size = Vector2(40.0, 41.0)
				sprite.texture = TEXTURES[1]
				sprite.region_enabled = false
				_update_sprite_geometry()
		3:
			if timer == 4:
				horizontal_speed = 6.25 if player.position.x > position.x else -6.25
				if sprite.flip_h:
					position.x += body_size.x - 30.0
				body_size = Vector2(30.0, 30.0)
				sprite.texture = TEXTURES[2]
				sprite.flip_h = false
				_update_sprite_geometry()
			elif timer > 4:
				sprite.rotation_degrees = fposmod(sprite.rotation_degrees + 24.0 * 360.0 / 256.0, 360.0)
			if timer >= 37:
				position.x += horizontal_speed
			if position.x - player.position.x - 40.0 > 640.0 or player.position.x - position.x - 30.0 > 640.0:
				queue_free()


func _update_emergence() -> void:
	if timer <= 12:
		var growth := minf(4.25, 51.0 - visible_height)
		visible_height += growth
		position.y -= growth
		body_size.y = visible_height
		sprite.visible = true
		_update_sprite_geometry()
		return
	if position.y <= player.position.y:
		if timer % 4 == 0:
			state = 2
			timer = 0
	elif position.y <= water_surface_y + 20.0:
		position.y = water_surface_y + 20.0
		if timer % 4 == 0:
			state = 2
			timer = 0
	else:
		position.y -= 4.25


func _update_sprite_geometry() -> void:
	if sprite.region_enabled:
		sprite.region_rect = Rect2(0.0, 0.0, 36.0, visible_height)
	sprite.centered = sprite.texture == TEXTURES[2]
	sprite.position = body_size * 0.5 if sprite.centered else Vector2.ZERO


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return visible_height > 0.0 and get_hit_rect().intersects(projectile_rect)
