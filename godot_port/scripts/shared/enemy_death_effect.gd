class_name EnemyDeathEffect
extends Node2D

const FRAMES := [
	preload("res://assets/world1/enemy_death_1.png"),
	preload("res://assets/world1/enemy_death_2.png"),
	preload("res://assets/world1/enemy_death_3.png"),
]

var sprite: Sprite2D
var timer := 0
var frame_hold_ticks := 5


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = true
	sprite.texture = FRAMES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func _physics_process(_delta: float) -> void:
	timer += 1
	sprite.texture = FRAMES[mini(int(timer / float(frame_hold_ticks)), FRAMES.size() - 1)]
	if timer >= frame_hold_ticks * FRAMES.size():
		queue_free()
