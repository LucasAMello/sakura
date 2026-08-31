class_name World4CardPickup
extends "res://scripts/world1/card_pickup.gd"

const WORLD4_ANIMATION_TICK_SCALE := 2


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, pickup_card_id: int, falls: bool) -> void:
	super.setup(map_terrain, target_player, pickup_card_id, falls)
	oscillation_direction = 0


func _physics_process(_delta: float) -> void:
	if not collected and is_instance_valid(player) and Rect2(position, BODY_SIZE).intersects(player.get_hit_rect()):
		collected = true
		timer = 0
	timer += 1
	if collected:
		sprite.modulate.a -= 30.0 / 255.0
		if sprite.modulate.a <= 0.0:
			progress.collect_card(card_id)
			queue_free()
		return
	var frame_tick := int(timer / float(WORLD4_ANIMATION_TICK_SCALE)) % 40
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
