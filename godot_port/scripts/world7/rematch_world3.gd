extends "res://scripts/world3/stage3.gd"

const REMATCH_CONFIGS := {
	77: {
		"width": 300,
		"height": 32,
		"start": Vector2(5400, 400),
		"exit": Rect2(),
		"next": 0,
		"wall_turrets": [],
		"machines": [],
		"oranges": [],
		"shockers": [],
		"cards": [],
		"holder": [],
	},
}

var rematch_intro_started := false


func _first_map_number() -> int:
	return -1


func _world_number() -> int:
	return 3


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
	camera_lock_position = Vector2(5600, 400)
	return StageState.BOSS_INTRO


func _update_boss_intro() -> void:
	if not rematch_intro_started:
		rematch_intro_started = true
		state_ticks = 160
		boss.set_gameplay_active(false)
	super._update_boss_intro()


func _entry_has_portal() -> bool:
	return true


func _update_camera() -> void:
	if not is_instance_valid(camera):
		return
	camera_lock_position = Vector2(5600, 400)
	camera.position = camera_lock_position
	_update_background()
