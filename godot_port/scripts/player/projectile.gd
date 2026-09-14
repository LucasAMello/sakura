class_name DefaultProjectile
extends Node2D

signal finished

const BODY_SIZE := Vector2(10, 10)
const MAX_PLAYER_DISTANCE := 480.0
const TEXTURE := preload("res://assets/player/default_shot.png")
const HIT_TEXTURES := [
	preload("res://assets/player/shot_hit_1.png"),
	preload("res://assets/player/shot_hit_2.png"),
	preload("res://assets/player/shot_hit_3.png"),
]

var terrain: SakuraTerrain
var player: SakuraPlayer
var stage: Node
var move_direction := 1
var ending := false
var explosion_ticks := 0
var sprite: Sprite2D


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, owner_player: SakuraPlayer, owner_stage: Node, direction: int) -> void:
	terrain = map_terrain
	player = owner_player
	stage = owner_stage
	move_direction = direction


func _physics_process(_delta: float) -> void:
	if ending:
		explosion_ticks += 1
		if explosion_ticks == 2:
			sprite.texture = HIT_TEXTURES[1]
		elif explosion_ticks == 4:
			sprite.texture = HIT_TEXTURES[2]
		elif explosion_ticks >= 6:
			queue_free()
		return
	for _substep in range(6):
		position.x += move_direction * 1.5
		var rect := Rect2(position, BODY_SIZE)
		if not Rect2(Vector2.ZERO, terrain.world_size).intersects(Rect2(position, TEXTURE.get_size())):
			queue_free()
			return
		if stage.projectile_hits_solid(rect, true):
			_end()
			return
		if stage.damage_enemy_in_rect(rect, 1):
			_end()
			return
	if not is_instance_valid(player) or absf(position.x - player.position.x) > MAX_PLAYER_DISTANCE:
		_end()


func _exit_tree() -> void:
	if not ending:
		ending = true
		finished.emit()


func _end() -> void:
	if ending:
		return
	ending = true
	position -= Vector2(5, 5)
	sprite.texture = HIT_TEXTURES[0]
	finished.emit()
