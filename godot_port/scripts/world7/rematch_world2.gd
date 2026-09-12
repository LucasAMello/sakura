extends "res://scripts/world2/stage2.gd"

const REMATCH_CONFIGS := {
	76: {
		"width": 300,
		"height": 36,
		"start": Vector2(5500, 460),
		"exit": Rect2(),
		"next": 0,
		"background": false,
		"ghosts": [],
		"paintings": [],
		"armors": [],
		"spikes": [],
		"mask_spawners": [],
		"cards": [],
	},
}

var rematch_intro_started := false


func _first_map_number() -> int:
	return -1


func _world_number() -> int:
	return 2


func _map_configs() -> Dictionary:
	return REMATCH_CONFIGS


func _build_stage_boss_area() -> void:
	_build_boss_area()
	for door in boss_doors:
		terrain.solid_sprites.erase(door)
		door.hide()
		door.queue_free()
	boss_doors.clear()


func _entry_complete_state() -> int:
	camera_locked = true
	camera_lock_position = Vector2(5640, 360)
	return StageState.BOSS_INTRO


func _update_boss_intro() -> void:
	if not rematch_intro_started:
		rematch_intro_started = true
		boss.set_gameplay_active(true)
		boss.begin_intro()
	super._update_boss_intro()



func _entry_has_portal() -> bool:
	return true


func _update_camera() -> void:
	if not is_instance_valid(camera):
		return
	camera_lock_position = Vector2(5640, 360)
	camera.position = camera_lock_position
	_update_background()
