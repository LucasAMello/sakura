class_name World5CardHolder
extends Node2D

signal opened(spawn_position: Vector2, card_id: int)

const CLOSED_TEXTURE := preload("res://assets/world5/card_holder.png")
const OPEN_TEXTURE := preload("res://assets/world5/card_holder_broken.png")
const CARD_TEXTURES := World1CardPickup.TEXTURES
const BODY_SIZE := Vector2(40, 60)

var sprite: Sprite2D
var card_sprite: Sprite2D
var card_id := 9
var opened_state := false
var timer := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = CLOSED_TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)
	card_sprite = Sprite2D.new()
	card_sprite.centered = false
	card_sprite.position = Vector2(9, 12)
	card_sprite.texture = CARD_TEXTURES[0]
	card_sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(card_sprite)


func _physics_process(_delta: float) -> void:
	timer += 1
	if opened_state:
		sprite.visible = int(timer / 4.0) % 2 == 0
		if timer >= 80:
			queue_free()
		return
	var frame_tick := int(timer / 4.0) % 40
	if frame_tick <= 16 and frame_tick % 2 == 0:
		card_sprite.texture = CARD_TEXTURES[mini(int(frame_tick / 2.0), CARD_TEXTURES.size() - 1)]
	card_sprite.flip_h = frame_tick >= 10


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return not opened_state and Rect2(position, BODY_SIZE).intersects(projectile_rect)


func take_projectile_hit(_damage: int) -> void:
	if opened_state:
		return
	opened_state = true
	timer = 0
	get_node("/root/AudioManager").play_sfx("glass", 1.0, 125.0 / 255.0)
	sprite.texture = OPEN_TEXTURE
	card_sprite.visible = false
	opened.emit(position + Vector2(9, 12), card_id)
