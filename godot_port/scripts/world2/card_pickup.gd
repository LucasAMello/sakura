class_name CardPickup
extends Node2D

const TEXTURES := [
	preload("res://assets/world2/boss_reward_1.png"),
	preload("res://assets/world2/boss_reward_2.png"),
	preload("res://assets/world2/boss_reward_3.png"),
	preload("res://assets/world2/boss_reward_4.png"),
	preload("res://assets/world2/boss_reward_5.png"),
	preload("res://assets/world2/boss_reward_4.png"),
	preload("res://assets/world2/boss_reward_3.png"),
	preload("res://assets/world2/boss_reward_2.png"),
	preload("res://assets/world2/boss_reward_1.png"),
]
const BODY_SIZE := Vector2(22, 36)
const ANIMATION_TICK_SCALE := 2

var terrain: SakuraTerrain
var player: SakuraPlayer
var progress: Variant
var sprite: Sprite2D
var card_id := 0
var timer := 0
var vertical_speed := 0.0
var oscillation_direction := 0
var collected := false
var update_phase := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = TEXTURES[0]
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, pickup_card_id: int, falls: bool) -> void:
	terrain = map_terrain
	player = target_player
	progress = get_node("/root/SakuraProgress")
	card_id = pickup_card_id
	vertical_speed = 10.0 if falls else 0.0


func _physics_process(_delta: float) -> void:
	if not collected and is_instance_valid(player) and Rect2(position, BODY_SIZE).intersects(player.get_hit_rect()):
		collected = true
		timer = 0
	update_phase = (update_phase + 1) % 2
	if update_phase != 0:
		return
	timer += 1
	if collected:
		sprite.modulate.a -= 30.0 / 255.0
		if sprite.modulate.a <= 0.0:
			progress.collect_card(card_id)
			queue_free()
		return
	var frame_tick := int(timer / float(ANIMATION_TICK_SCALE)) % 40
	if frame_tick <= 16 and frame_tick % 2 == 0:
		sprite.texture = TEXTURES[mini(int(frame_tick / 2.0), TEXTURES.size() - 1)]
	sprite.flip_h = frame_tick >= 10
	if vertical_speed > 4.0 or timer % 4 == 0:
		_move_vertical(vertical_speed)
	if timer % 4 == 0:
		if oscillation_direction == 0:
			vertical_speed += 1.0
			if vertical_speed >= 2.0 and vertical_speed <= 4.0:
				oscillation_direction = 1
		else:
			vertical_speed -= 1.0
			if vertical_speed <= -2.0:
				oscillation_direction = 0
	if not collected and is_instance_valid(player) and Rect2(position, BODY_SIZE).intersects(player.get_hit_rect()):
		collected = true
		timer = 0


func _move_vertical(amount: float) -> void:
	if amount == 0.0:
		return
	var direction := signf(amount)
	var remaining := absf(amount)
	while remaining > 0.0:
		var step := minf(1.0, remaining) * direction
		var candidate := Rect2(position + Vector2(0, step), BODY_SIZE)
		if direction > 0.0 and terrain.rect_hits_solid(candidate):
			vertical_speed = 0.0
			position.y = floorf(candidate.end.y / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE - BODY_SIZE.y - 10.0
			return
		position.y += step
		remaining -= absf(step)
	if position.y > terrain.world_size.y or position.y < 0.0:
		queue_free()
