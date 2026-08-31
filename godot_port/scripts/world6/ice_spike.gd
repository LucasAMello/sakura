class_name World6IceSpike
extends SakuraEnemy

const TEXTURE := preload("res://assets/world6/ice_spike.png")


func _ready() -> void:
	super._ready()
	body_size = Vector2(60, 29)
	hit_points = 1
	contact_damage = 20
	sprite.visible = false
	queue_redraw()


func configure(width: float) -> void:
	body_size.x = width
	queue_redraw()


func projectile_mask_overlap(_projectile_rect: Rect2) -> bool:
	return false


func _draw() -> void:
	var width := int(body_size.x)
	draw_texture_rect_region(TEXTURE, Rect2(0, 0, 20, 29), Rect2(0, 0, 20, 29))
	for x in range(20, width - 20, 20):
		draw_texture_rect_region(TEXTURE, Rect2(x, 0, mini(20, width - 20 - x), 29), Rect2(20, 0, mini(20, width - 20 - x), 29))
	draw_texture_rect_region(TEXTURE, Rect2(width - 20, 0, 20, 29), Rect2(40, 0, 20, 29))
