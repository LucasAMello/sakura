class_name TurretShotExplosion
extends Node2D

const FRAMES := [
	preload("res://assets/world1/turret_shot_explosion_1.png"),
	preload("res://assets/world1/turret_shot_explosion_2.png"),
	preload("res://assets/world1/turret_shot_explosion_3.png"),
]

var sprite: Sprite2D
var player: SakuraPlayer
var timer := 0


func setup(target_player: SakuraPlayer) -> void:
	player = target_player


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	if is_instance_valid(player):
		get_node("/root/AudioManager").play_sfx_near_player("anim13", position, player.position, 1.0, 150.0 / 255.0)
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
