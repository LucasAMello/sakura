class_name World4OysterLower
extends SakuraEnemy

const TEXTURE := preload("res://assets/world4/oyster_lower.png")


func configure(facing_direction: int) -> void:
	set_update_interval(1)
	body_size = Vector2(36.0, 14.0)
	hit_points = 1
	contact_damage = 0
	drops_recovery = false
	sprite.texture = TEXTURE
	sprite.flip_h = facing_direction == 1


func take_projectile_hit(_damage: int) -> void:
	return
