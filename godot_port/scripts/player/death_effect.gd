class_name PlayerDeathEffect
extends Node2D

const FRAMES: Array[Resource] = [
	preload("res://assets/player/death_1.png"),
	preload("res://assets/player/death_2.png"),
	preload("res://assets/player/death_3.png"),
	preload("res://assets/player/death_4.png"),
	preload("res://assets/player/death_5.png"),
]
const VELOCITIES := [
	Vector2(2.5, -3.5), Vector2(3.5, -2.5), Vector2(4, 0),
	Vector2(3.5, 2.5), Vector2(2.5, 3.5), Vector2(0, 4),
	Vector2(-2.5, 3.5), Vector2(-3.5, 2.5), Vector2(-4, 0),
	Vector2(-3.5, -2.5), Vector2(-2.5, -3.5), Vector2(0, -4),
]
const OFFSETS := [
	Vector2(7, 5), Vector2(12, 10), Vector2(17, 17),
	Vector2(12, 24), Vector2(7, 29), Vector2(0, 34),
	Vector2(-7, 29), Vector2(-12, 24), Vector2(-17, 17),
	Vector2(-12, 10), Vector2(-7, 5), Vector2.ZERO,
]

var particles: Array[Sprite2D] = []
var timer := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	for index in range(VELOCITIES.size()):
		var particle := Sprite2D.new()
		particle.centered = true
		particle.texture = FRAMES[0]
		particle.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		particle.position = OFFSETS[index]
		add_child(particle)
		particles.append(particle)


func _physics_process(_delta: float) -> void:
	timer += 1
	var frame := FRAMES[int(timer / 5.0) % FRAMES.size()]
	for index in range(particles.size()):
		particles[index].texture = frame
		particles[index].position += VELOCITIES[index]
	if timer >= 100:
		queue_free()
