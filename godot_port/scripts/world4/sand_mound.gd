class_name World4SandMound
extends Node2D

signal opened(spawn_position: Vector2, card_id: int)

const TEXTURES := [
	preload("res://assets/world4/sand_mound_1.png"),
	preload("res://assets/world4/sand_mound_2.png"),
	preload("res://assets/world4/sand_mound_3.png"),
	preload("res://assets/world4/sand_mound_4.png"),
]
const BODY_SIZE := Vector2(46.0, 36.0)

var sprite: Sprite2D
var card_id := 0
var opened_state := false
var timer := 0


func _ready() -> void:
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func configure(contained_card_id: int) -> void:
	card_id = contained_card_id


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return not opened_state and Rect2(position, BODY_SIZE).intersects(projectile_rect)


func take_projectile_hit(_damage: int, projectile_direction: int = 1) -> void:
	if opened_state:
		return
	opened_state = true
	timer = 0
	sprite.texture = TEXTURES[1]
	sprite.flip_h = projectile_direction < 0
	opened.emit(position + Vector2(11.0, 0.0), card_id)


func _physics_process(_delta: float) -> void:
	if not opened_state:
		return
	timer += 1
	if timer == 3:
		sprite.texture = TEXTURES[2]
	elif timer == 6:
		sprite.texture = TEXTURES[3]
	elif timer >= 9:
		queue_free()
