extends "res://scripts/world6/stage6.gd"

const REMATCH_CONFIGS := {
	74: {
		"width": 200,
		"height": 60,
		"start": Vector2(3620, 1020),
		"exit": Rect2(),
		"next": 0,
		"ice_mets": [],
		"icicles": [],
		"spikes": [],
		"pumpkins": [],
		"cards": [],
		"card_holders": [],
		"ice_holders": [],
		"ice_blocks": [
			[Vector2(3440, 990), 1], [Vector2(3460, 990), 2], [Vector2(3480, 990), 1],
			[Vector2(3760, 990), 2], [Vector2(3780, 990), 1], [Vector2(3800, 990), 2],
		],
	},
}

var rematch_intro_started := false


func _first_map_number() -> int:
	return -1


func _world_number() -> int:
	return 6


func _map_configs() -> Dictionary:
	return REMATCH_CONFIGS


func _build_stage_boss_area() -> void:
	super._build_stage_boss_area()
	_build_boss_area()
	for door in boss_doors:
		terrain.solid_sprites.erase(door)
		door.hide()
		door.queue_free()
	boss_doors.clear()


func _entry_complete_state() -> int:
	camera_locked = true
	camera_lock_position = Vector2(3640, 960)
	return StageState.BOSS_INTRO


func _update_boss_intro() -> void:
	if not rematch_intro_started:
		rematch_intro_started = true
		boss_intro_ready = false
		boss_meter_ticks = 0
		boss.visible = true
		boss.set_gameplay_active(true)
		boss.begin_intro()
	super._update_boss_intro()



func _entry_has_portal() -> bool:
	return true


func _update_camera() -> void:
	if not is_instance_valid(camera):
		return
	camera_lock_position = Vector2(3640, 960)
	camera.position = camera_lock_position
	_update_background()
