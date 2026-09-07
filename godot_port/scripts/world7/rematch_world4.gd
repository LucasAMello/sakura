extends "res://scripts/world4/stage4.gd"

const REMATCH_CONFIGS := {
	78: {
		"width": 500,
		"height": 40,
		"start": Vector2(9500, 560),
		"exit": Rect2(),
		"next": 0,
		"water_surface": 300,
		"starts_in_water": true,
		"background_rows": [60.0],
		"resettis": [],
		"seahorse_spawners": [],
		"fish": [],
		"oysters": [],
		"cards": [],
		"sand_mounds": [],
	},
}

var rematch_intro_started := false


func _first_map_number() -> int:
	return -1


func _world_number() -> int:
	return 4


func _map_configs() -> Dictionary:
	return REMATCH_CONFIGS


func _build_stage_boss_area() -> void:
	super._build_stage_boss_area()
	_build_boss_area()


func _entry_complete_state() -> int:
	camera_locked = true
	camera_lock_position = Vector2(9680, 400)
	return StageState.BOSS_INTRO


func _update_boss_intro() -> void:
	if not rematch_intro_started:
		rematch_intro_started = true
		boss.set_gameplay_active(true)
		boss.start_intro()
	super._update_boss_intro()

