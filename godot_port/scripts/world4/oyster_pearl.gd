class_name World4OysterPearl
extends Node2D

const TEXTURE := preload("res://assets/world4/oyster_pearl.png")
const BODY_SIZE := Vector2(12.0, 12.0)

var terrain: SakuraTerrain
var player: SakuraPlayer
var gameplay_active := false
var timer := 0
var velocity := Vector2.ZERO
var shot_direction := 0


func _ready() -> void:
	add_to_group("enemy_projectile_blockers")
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURE
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, firing_direction: int) -> void:
	terrain = map_terrain
	player = target_player
	shot_direction = firing_direction


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func _physics_process(_delta: float) -> void:
	if not gameplay_active or not is_instance_valid(player):
		return
	timer += 1
	if timer <= 20:
		return
	if timer == 21:
		var offset := player.position - position
		var horizontal_gap := offset.x - 20.0 if shot_direction == 1 else -offset.x - 40.0
		var horizontal_speed := 5.0 if horizontal_gap >= 180.0 else 3.75 if horizontal_gap >= 125.0 else 2.5
		velocity.x = horizontal_speed if shot_direction == 1 else -horizontal_speed
		velocity.y = (-3.5 if offset.y < -20.0 else -2.5 if offset.y < 0.0 else -1.5) - 0.1875
	else:
		velocity.y += 0.125
	if not _move_axis(Vector2(velocity.x, 0.0)) or not _move_axis(Vector2(0.0, velocity.y)):
		queue_free()
		return
	if Rect2(position, BODY_SIZE).intersects(player.get_hit_rect()):
		player.take_damage(2)
		queue_free()
	elif position.x < -40.0 or position.x > terrain.world_size.x + 40.0 or position.y > terrain.world_size.y + 40.0:
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


func blocks_player_projectile(rect: Rect2, weapon_id: int, _water_splash: bool = false) -> bool:
	return true and preload("res://scripts/shared/projectile_interception.gd").overlaps(self, rect, BODY_SIZE, weapon_id)
