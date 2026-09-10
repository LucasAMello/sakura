class_name TurretDeathEffect
extends Node2D

const FRAMES := [
	preload("res://assets/world1/turret_death_1.png"),
	preload("res://assets/world1/turret_death_2.png"),
	preload("res://assets/world1/turret_death_3.png"),
]

var sprite: Sprite2D
var timer := 0
var flip_h := false


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = true
	sprite.texture = FRAMES[0]
	sprite.flip_h = flip_h
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func _physics_process(_delta: float) -> void:
	timer += 1
	sprite.texture = FRAMES[mini(int(timer / 8.0), FRAMES.size() - 1)]
	if timer >= 24:
		queue_free()
