class_name World5Squid
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world5/squid_1.png"),
	preload("res://assets/world5/squid_2.png"),
	preload("res://assets/world5/squid_3.png"),
	preload("res://assets/world5/squid_4.png"),
	preload("res://assets/world5/squid_5.png"),
	preload("res://assets/world5/squid_6.png"),
]

var home_y := 0.0
var state := 0
var timer := 0
var vertical_speed := 0.0


func configure() -> void:
	home_y = position.y
	body_size = Vector2(25, 59)
	hit_points = 3
	contact_damage = 2
	drops_recovery = false
	sprite.texture = FRAMES[0]
	sprite.visible = false


func take_weapon_hit(damage: int, weapon_id: int) -> void:
	take_projectile_hit(3 if weapon_id == 5 else damage)


func _update_enemy() -> void:
	match state:
		0:
			_update_waiting()
		1:
			_update_rising()
		2:
			_update_turnaround()
		3:
			_update_falling()
		4:
			timer += 1
			if timer == 10:
				state = 0
				timer = 0
	if state != 2:
		sprite.texture = FRAMES[timer % 4]
	_update_surface_clip()


func _update_waiting() -> void:
	if not is_instance_valid(player):
		return
	var player_left := player.position.x
	var squid_left := position.x
	var close_from_left := player.facing > 0 and squid_left - player_left - 40.0 > 15.0 and squid_left - player_left - 40.0 < 80.0
	var close_from_right := player.facing < 0 and player_left - squid_left - 37.0 > 15.0 and player_left - squid_left - 37.0 < 80.0
	if (close_from_left or close_from_right) and player.position.y + 400.0 > position.y and player.position.y - 80.0 <= position.y:
		state = 1
		vertical_speed = -25.0
		sprite.visible = true
		_update_rising()


func _update_rising() -> void:
	vertical_speed += 1.0 if timer < 7 else 2.0 if timer < 16 else 4.0
	position.y += vertical_speed
	timer += 1
	if vertical_speed == -4.0:
		timer = 0
		state = 2
		vertical_speed = 0.0


func _update_turnaround() -> void:
	timer += 1
	if timer == 1:
		sprite.texture = FRAMES[4]
		body_size = Vector2(27, 33)
		position += Vector2(-2, 6)
	elif timer == 2:
		sprite.texture = FRAMES[5]
	elif timer == 3:
		sprite.texture = FRAMES[5]
		sprite.flip_v = true
		position.y += 4.0
	elif timer == 4:
		sprite.texture = FRAMES[4]
		sprite.flip_v = true
		position.y += 6.0
	elif timer == 5:
		timer = 0
		body_size = Vector2(25, 59)
		position += Vector2(2, -20)
		state = 3
		_update_falling()


func _update_falling() -> void:
	vertical_speed += 1.0 if timer < 8 else 2.0 if timer < 16 else 4.0
	position.y += vertical_speed
	timer += 1
	if vertical_speed == 44.0:
		timer = 0
		state = 4
		position.y = home_y
		vertical_speed = 0.0
		sprite.flip_v = false
		sprite.visible = false


func _update_surface_clip() -> void:
	if state == 0 or state == 4:
		sprite.visible = false
		sprite.region_enabled = false
		return
	sprite.visible = true
	if state != 1 and state != 3:
		sprite.region_enabled = false
		return
	var visible_height := clampf(home_y - position.y, 0.0, 59.0)
	if visible_height >= 59.0:
		sprite.region_enabled = false
		return
	sprite.region_enabled = true
	var source_y := 59.0 - visible_height if state == 3 else 0.0
	sprite.region_rect = Rect2(0.0, source_y, 25.0, visible_height)


func _death_effect_position() -> Vector2:
	return position + Vector2(12, 22)
