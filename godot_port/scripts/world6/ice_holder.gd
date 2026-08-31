class_name World6IceHolder
extends Node2D

signal opened(spawn_position: Vector2, card_id: int)

const FRAMES := [
	preload("res://assets/world6/ice_holder_1.png"),
	preload("res://assets/world6/ice_holder_2.png"),
	preload("res://assets/world6/ice_holder_3.png"),
	preload("res://assets/world6/ice_holder_4.png"),
]
const BODY_SIZE := Vector2(40, 50)

var sprite: Sprite2D
var next_sprite: Sprite2D
var card_sprite: Sprite2D
var card_id := 0
var breaking := false
var frame_index := 0
var current_alpha := 200
var next_alpha := 0
var update_phase := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	card_sprite = Sprite2D.new()
	card_sprite.centered = false
	card_sprite.position = Vector2(9, 6)
	card_sprite.texture = World1CardPickup.TEXTURES[0]
	card_sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(card_sprite)
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = FRAMES[0]
	sprite.modulate.a = 200.0 / 255.0
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)
	next_sprite = Sprite2D.new()
	next_sprite.centered = false
	next_sprite.texture = FRAMES[1]
	next_sprite.modulate.a = 0.0
	next_sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(next_sprite)


func _physics_process(_delta: float) -> void:
	if not breaking:
		return
	update_phase = (update_phase + 1) % 2
	if update_phase != 0:
		return
	current_alpha -= 18
	next_alpha += 20
	sprite.modulate.a = maxf(0.0, float(current_alpha) / 255.0)
	next_sprite.modulate.a = minf(1.0, float(next_alpha) / 255.0)
	if current_alpha > 2:
		return
	frame_index += 1
	if frame_index >= FRAMES.size():
		opened.emit(position + Vector2(9, 6), card_id)
		queue_free()
		return
	sprite.texture = FRAMES[frame_index]
	current_alpha = 200
	if frame_index + 1 < FRAMES.size():
		next_sprite.texture = FRAMES[frame_index + 1]
		next_sprite.visible = true
	else:
		next_sprite.visible = false
	next_alpha = 0


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return not breaking and Rect2(position, BODY_SIZE).intersects(projectile_rect)


func take_projectile_hit(_damage: int) -> void:
	breaking = true
	update_phase = 0

