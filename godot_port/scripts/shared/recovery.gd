class_name RecoveryPickup
extends Node2D

const TEXTURES := [
	preload("res://assets/player/recovery_small.png"),
	preload("res://assets/player/recovery_medium.png"),
	preload("res://assets/player/extra_life.png"),
]
const BODY_SIZES := [Vector2(10, 10), Vector2(20, 20), Vector2(37, 31)]
const FALL_SPEED := 7.5

var player: SakuraPlayer
var terrain: SakuraTerrain
var pickup_type := SakuraEnemy.DropType.SMALL
var body_size: Vector2 = BODY_SIZES[0]
var sprite: Sprite2D
var vertical_speed := FALL_SPEED


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, type: SakuraEnemy.DropType) -> void:
	terrain = map_terrain
	player = target_player
	pickup_type = type
	var index: int = clampi(type - SakuraEnemy.DropType.SMALL, 0, TEXTURES.size() - 1)
	body_size = BODY_SIZES[index]
	sprite.texture = TEXTURES[index]


func _physics_process(_delta: float) -> void:
	_move_down(vertical_speed)
	if position.y > terrain.world_size.y or position.y < 0.0:
		queue_free()
		return
	if is_instance_valid(player) and Rect2(position, body_size).intersects(player.get_hit_rect()):
		if pickup_type == SakuraEnemy.DropType.SMALL:
			player.add_health(1)
		elif pickup_type == SakuraEnemy.DropType.MEDIUM:
			player.add_health(3)
		else:
			player.add_life()
		queue_free()


func _move_down(amount: float) -> void:
	var remaining := amount
	while remaining > 0.0:
		var step := minf(1.0, remaining)
		var candidate := Rect2(position + Vector2(0, step), body_size)
		if terrain.rect_hits_solid(candidate):
			vertical_speed = 0.0
			position.y = floorf(candidate.end.y / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE - body_size.y
			return
		position.y += step
		remaining -= step
