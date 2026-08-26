class_name TurretShotExplosion
extends Node2D

const FRAMES := [
	preload("res://assets/world1/turret_shot_explosion_1.png"),
	preload("res://assets/world1/turret_shot_explosion_2.png"),
	preload("res://assets/world1/turret_shot_explosion_3.png"),
]

var sprite: Sprite2D
var timer := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = FRAMES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func _physics_process(_delta: float) -> void:
	timer += 1
	if timer == 2:
		sprite.texture = FRAMES[1]
	elif timer == 6:
		sprite.texture = FRAMES[2]
	elif timer >= 10:
		queue_free()
