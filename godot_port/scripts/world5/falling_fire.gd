class_name World5FallingFire
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world5/falling_fire_1.png"),
	preload("res://assets/world5/falling_fire_2.png"),
	preload("res://assets/world5/falling_fire_3.png"),
	preload("res://assets/world5/falling_fire_4.png"),
	preload("res://assets/world5/falling_fire_5.png"),
	preload("res://assets/world5/falling_fire_6.png"),
	preload("res://assets/world5/falling_fire_7.png"),
]

var state := 0
var timer := 0


func configure() -> void:
	body_size = Vector2(20, 39)
	hit_points = 1
	contact_damage = 2
	drops_recovery = false
	sprite.texture = FRAMES[0]


func _update_enemy() -> void:
	if state == 1:
		if timer >= 2:
			queue_free()
			return
		sprite.texture = FRAMES[5 + timer]
		timer += 1
		return
	sprite.texture = FRAMES[timer % 4]
	timer += 1
	var candidate := Rect2(position + Vector2(0, 8), body_size)
	if terrain.rect_hits_solid(candidate):
		position.y = floorf(candidate.end.y / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE - body_size.y - 1.0
		position.x -= 9.0
		body_size = Vector2(42, 40)
		sprite.texture = FRAMES[4]
		state = 1
		timer = 0
	else:
		position.y += 8.0


func projectile_mask_overlap(_projectile_rect: Rect2) -> bool:
	return false
