class_name ThirdBossReward
extends Node2D

signal collected

const FRAMES := [
	preload("res://assets/world3/boss_reward_1.png"),
	preload("res://assets/world3/boss_reward_2.png"),
	preload("res://assets/world3/boss_reward_3.png"),
	preload("res://assets/world3/boss_reward_4.png"),
	preload("res://assets/world3/boss_reward_5.png"),
	preload("res://assets/world3/boss_reward_4.png"),
	preload("res://assets/world3/boss_reward_3.png"),
	preload("res://assets/world3/boss_reward_2.png"),
]

var player: SakuraPlayer
var sprite: Sprite2D
var timer := 0
var state := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = FRAMES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(target_player: SakuraPlayer) -> void:
	player = target_player


func begin_homing() -> void:
	if state == 0:
		state = 1
		timer = 0


func _physics_process(_delta: float) -> void:
	timer += 1
	if state == 0:
		return
	if state == 1:
		sprite.texture = FRAMES[int(timer / 2.0) % FRAMES.size()]
		var target := player.position + Vector2(14, 22)
		position.x = move_toward(position.x, target.x, 5.0)
		position.y = move_toward(position.y, target.y, 5.0)
		if position.distance_to(target) <= 0.1 and timer % 16 == 0:
			state = 2
			timer = 0
	else:
		sprite.modulate.a -= 30.0 / 255.0
		if sprite.modulate.a <= 0.0:
			collected.emit()
			queue_free()
