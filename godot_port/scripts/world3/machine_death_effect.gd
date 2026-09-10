class_name World3MachineDeathEffect
extends Node2D

const FRAMES := [
	preload("res://assets/world3/machine_death_1.png"),
	preload("res://assets/world3/machine_death_2.png"),
	preload("res://assets/world3/machine_death_3.png"),
]

var sprite: Sprite2D
var timer := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.position = Vector2(-32, -35)
	sprite.texture = FRAMES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func _physics_process(_delta: float) -> void:
	timer += 1
	if timer == 8:
		sprite.texture = FRAMES[1]
	elif timer == 16:
		sprite.texture = FRAMES[2]
	elif timer >= 24:
		queue_free()
