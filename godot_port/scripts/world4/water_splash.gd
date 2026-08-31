class_name World4WaterSplash
extends Node2D

const FRAMES := [
	preload("res://assets/world4/splash_1.png"),
	preload("res://assets/world4/splash_2.png"),
	preload("res://assets/world4/splash_3.png"),
]

var sprite: Sprite2D
var physics_ticks := 0
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
	physics_ticks += 1
	if physics_ticks < 2:
		return
	physics_ticks = 0
	animation_ticks += 1
	if animation_ticks == 3:
		sprite.texture = FRAMES[1]
	elif animation_ticks == 5:
		sprite.texture = FRAMES[2]
	elif animation_ticks >= 7:
		queue_free()
