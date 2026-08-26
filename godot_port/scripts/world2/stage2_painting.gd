class_name Stage2Painting
extends Node2D

const BASE_TEXTURE := preload("res://assets/world2/painting_1.png")
const REVEAL_TEXTURE := preload("res://assets/world2/painting_2.png")
const REVEAL_SIZE := Vector2(100, 100)
const REVEAL_SPEED := SakuraPlayer.MAX_X_SPEED

var player: SakuraPlayer
var reveal_sprite: Sprite2D
var reveal_started := false
var reveal_complete := false
var reveal_width := 0.0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	var base_sprite := Sprite2D.new()
	base_sprite.centered = false
	base_sprite.texture = BASE_TEXTURE
	base_sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(base_sprite)
	reveal_sprite = Sprite2D.new()
	reveal_sprite.centered = false
	reveal_sprite.texture = REVEAL_TEXTURE
	reveal_sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	reveal_sprite.region_enabled = true
	reveal_sprite.region_rect = Rect2(Vector2.ZERO, Vector2(0, REVEAL_SIZE.y))
	add_child(reveal_sprite)


func setup(target_player: SakuraPlayer) -> void:
	player = target_player


func _physics_process(_delta: float) -> void:
	if not is_instance_valid(player) or reveal_complete:
		return
	if not reveal_started:
		if player.get_center().x < position.x:
			return
		reveal_started = true
	reveal_width = minf(REVEAL_SIZE.x, reveal_width + REVEAL_SPEED)
	reveal_sprite.region_rect = Rect2(Vector2.ZERO, Vector2(reveal_width, REVEAL_SIZE.y))
	if is_equal_approx(reveal_width, REVEAL_SIZE.x):
		reveal_complete = true
