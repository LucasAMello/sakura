class_name World4OysterLower
extends SakuraEnemy

const TEXTURE := preload("res://assets/world4/oyster_lower.png")


func configure(facing_direction: int) -> void:
	body_size = Vector2(36.0, 14.0)
	hit_points = 1
	contact_damage = 3
	drops_recovery = true
	sprite.texture = TEXTURE
	sprite.flip_h = facing_direction == 1
