class_name ShadowSpike
extends Node2D

const TEXTURE := preload("res://assets/world2/shadow_spike.png")

var player: SakuraPlayer
var body_size := Vector2(60, 29)


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	queue_redraw()


func setup(target_player: SakuraPlayer, width: float) -> void:
	player = target_player
	body_size.x = width
	queue_redraw()


func _draw() -> void:
	var width := int(body_size.x)
	draw_texture_rect_region(TEXTURE, Rect2(0, 0, 20, 28), Rect2(0, 0, 20, 28))
	for x in range(20, width - 20, 20):
		draw_texture_rect_region(TEXTURE, Rect2(x, 0, mini(20, width - 20 - x), 28), Rect2(20, 0, mini(20, width - 20 - x), 28))
	draw_texture_rect_region(TEXTURE, Rect2(width - 20, 0, 20, 28), Rect2(40, 0, 20, 28))


func _physics_process(_delta: float) -> void:
	if is_instance_valid(player) and Rect2(position, body_size).intersects(player.get_hit_rect()):
		player.take_damage(20)
