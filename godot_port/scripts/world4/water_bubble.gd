class_name World4WaterBubble
extends Node2D

const BUBBLE_TEXTURE := preload("res://assets/world4/bubble.png")

var surface_y := 0.0
var update_ticks := 0
var gameplay_active := true
var sprite: Sprite2D


func _ready() -> void:
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = BUBBLE_TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(water_surface_y: float, player_facing: int) -> void:
	surface_y = water_surface_y
	sprite.flip_h = player_facing < 0


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func _physics_process(_delta: float) -> void:
	if not gameplay_active:
		return
	update_ticks += 1
	if update_ticks < 2:
		return
	update_ticks = 0
	position.y -= 6.0
	if position.y < surface_y:
		queue_free()
