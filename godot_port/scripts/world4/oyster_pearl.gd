class_name World4OysterPearl
extends Node2D

const TEXTURE := preload("res://assets/world4/oyster_pearl.png")
const BODY_SIZE := Vector2(12.0, 12.0)

var terrain: SakuraTerrain
var player: SakuraPlayer
var gameplay_active := false
var timer := 0
var velocity := Vector2.ZERO
var lifetime := 0


func _ready() -> void:
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer) -> void:
	terrain = map_terrain
	player = target_player


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func _physics_process(_delta: float) -> void:
	if not gameplay_active or not is_instance_valid(player):
		return
	timer += 1
	lifetime += 1
	if timer <= 5:
		return
	if timer == 6:
		var offset := player.get_center() - Rect2(position, BODY_SIZE).get_center()
		var horizontal_speed := 10.0 if absf(offset.x) < 120.0 else 15.0 if absf(offset.x) < 240.0 else 20.0
		velocity.x = signf(offset.x) * horizontal_speed
		velocity.y = -14.0 if offset.y < -20.0 else -10.0 if offset.y < 0.0 else -6.0
	else:
		velocity.y += 2.0
	if not _move_axis(Vector2(velocity.x, 0.0)) or not _move_axis(Vector2(0.0, velocity.y)):
		queue_free()
		return
	if Rect2(position, BODY_SIZE).intersects(player.get_hit_rect()):
		player.take_damage(2)
		queue_free()
	elif lifetime > 180 or position.x < -40.0 or position.x > terrain.world_size.x + 40.0 or position.y > terrain.world_size.y + 40.0:
		queue_free()


func _move_axis(amount: Vector2) -> bool:
	var distance := absf(amount.x if amount.x != 0.0 else amount.y)
	if distance <= 0.0:
		return true
	var direction := amount.normalized()
	while distance > 0.0:
		var step := direction * minf(1.0, distance)
		if terrain.rect_hits_solid(Rect2(position + step, BODY_SIZE)):
			return false
		position += step
		distance -= step.length()
	return true
