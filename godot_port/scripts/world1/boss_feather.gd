class_name BossFeather
extends Node2D

const BODY_SIZE := Vector2(20, 9)
const TEXTURE := preload("res://assets/world1/boss_feather.png")
const SUBSTEP_SPEED := 5.0

var terrain: SakuraTerrain
var player: SakuraPlayer
var move_direction := -1


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_PAUSABLE
	add_to_group("boss_projectiles")
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite.flip_h = move_direction > 0
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, direction: int) -> void:
	terrain = map_terrain
	player = target_player
	move_direction = direction


func _physics_process(_delta: float) -> void:
	for step in range(2):
		position.x += move_direction * SUBSTEP_SPEED
		var hit_rect := Rect2(position, BODY_SIZE)
		if terrain.rect_hits_solid(hit_rect):
			queue_free()
			return
		if is_instance_valid(player) and hit_rect.intersects(player.get_hit_rect()):
			player.take_damage(3)
			queue_free()
			return
		if position.x < 2660.0 or position.x > 4080.0:
			queue_free()
			return
