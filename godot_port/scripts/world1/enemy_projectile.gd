class_name EnemyProjectile
extends Node2D

const BODY_SIZE := Vector2(20, 10)
const TEXTURE := preload("res://assets/world1/turret_shot.png")
const ExplosionScript = preload("res://scripts/world1/turret_shot_explosion.gd")
const SPEED_PER_TICK := 5.0

var terrain: SakuraTerrain
var player: SakuraPlayer
var sprite: Sprite2D
var move_direction := -1
var lifetime := 80
var exploded := false


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite.flip_h = move_direction > 0
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, direction: int) -> void:
	terrain = map_terrain
	player = target_player
	move_direction = 1 if direction == 1 else -1
	sprite.flip_h = move_direction > 0
	get_node("/root/AudioManager").play_sfx_near_player("turret", position, target_player.position, 1.0, 100.0 / 255.0)


func _physics_process(_delta: float) -> void:
	if exploded:
		return
	for _substep in range(4):
		position.x += move_direction * SPEED_PER_TICK / 4.0
		var hit_rect := Rect2(position, BODY_SIZE)
		if terrain.rect_hits_solid(hit_rect):
			_explode()
			return
		if is_instance_valid(player) and hit_rect.intersects(player.get_hit_rect()):
			player.take_damage(4)
			_explode()
			return
	lifetime -= 1
	if lifetime <= 0:
		_explode(true)


func _explode(from_lifetime: bool = false) -> void:
	if exploded:
		return
	exploded = true
	var explosion: TurretShotExplosion = ExplosionScript.new()
	var explosion_x
	if from_lifetime:
		explosion_x = -5.0 if move_direction > 0 else 5.0
	else:
		explosion_x = 5.0 if move_direction > 0 else -15.0
	explosion.position = position + Vector2(explosion_x, -10)
	explosion.z_index = z_index
	explosion.setup(player, move_direction)
	get_parent().add_child(explosion)
	queue_free()
