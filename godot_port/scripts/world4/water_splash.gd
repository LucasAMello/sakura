class_name World4WaterSplash
extends Node2D

const FRAMES := [
	preload("res://assets/world4/splash_1.png"),
	preload("res://assets/world4/splash_2.png"),
	preload("res://assets/world4/splash_3.png"),
]

var sprite: Sprite2D
var animation_ticks := 0
var gameplay_active := true


func _ready() -> void:
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = FRAMES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func _physics_process(_delta: float) -> void:
	if not gameplay_active:
		return
	animation_ticks += 1
	if animation_ticks == 12:
		sprite.texture = FRAMES[1]
	elif animation_ticks == 20:
		sprite.texture = FRAMES[2]
	elif animation_ticks >= 28:
		queue_free()
