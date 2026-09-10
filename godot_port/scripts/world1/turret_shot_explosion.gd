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
var move_direction := -1


func setup(target_player: SakuraPlayer, direction: int) -> void:
	player = target_player
	move_direction = direction


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	if is_instance_valid(player):
		get_node("/root/AudioManager").play_sfx_near_player("anim13", position, player.position, 1.0, 150.0 / 255.0)
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = FRAMES[0]
	sprite.flip_h = move_direction > 0
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
