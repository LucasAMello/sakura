class_name World6IceNeedle
extends SakuraEnemy

const TEXTURES := [
	preload("res://assets/world6/ice_needle_1.png"),
	preload("res://assets/world6/ice_needle_2.png"),
	preload("res://assets/world6/ice_needle_3.png"),
	preload("res://assets/world6/ice_needle_4.png"),
]
const ORIGINAL_SIZES := [Vector2(9, 7), Vector2(11, 11), Vector2(8, 12), Vector2(9, 12)]
const SPEEDS := [Vector2(20, 0), Vector2(15, -10), Vector2(10, -15), Vector2(0, -20)]

var velocity := Vector2.ZERO


func _ready() -> void:
	super._ready()
	hit_points = 1
	contact_damage = 1


func configure(variant: int, direction: int) -> void:
	set_update_interval(1)
	var index := clampi(variant, 0, TEXTURES.size() - 1)
	body_size = TEXTURES[index].get_size()
	position -= (body_size - ORIGINAL_SIZES[index]) * 0.5
	sprite.texture = TEXTURES[index]
	velocity = SPEEDS[index] * 0.25
	if direction == 0:
		velocity.x *= -1.0
	else:
		sprite.flip_h = true


func _update_enemy() -> void:
	if not _move_and_hit(velocity):
		queue_free()
		return
	if position.x < -40.0 or position.x > terrain.world_size.x + 40.0 or position.y < -40.0 or position.y > terrain.world_size.y + 40.0:
		queue_free()


func _move_and_hit(amount: Vector2) -> bool:
	var steps := maxi(1, ceili(maxf(absf(amount.x), absf(amount.y))))
	var step := amount / float(steps)
	for _index in range(steps):
		if terrain.rect_hits_solid(Rect2(position + step, body_size)):
			return false
		position += step
	return true


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return preload("res://scripts/shared/projectile_interception.gd").overlaps(self, projectile_rect, body_size, 1)
