extends "res://scripts/world5/stage5.gd"

const REMATCH_CONFIGS := {
	79: {
		"width": 300,
		"height": 120,
		"start": Vector2(5400, 2220),
		"exit": Rect2(),
		"next": 0,
		"horizontal_flamethrowers": [],
		"vertical_flamethrowers": [],
		"flamemets": [],
		"lava": [
			[Vector2(5300, 2320), 80],
			[Vector2(5540, 2320), 140],
			[Vector2(5840, 2320), 60],
		],
		"squids": [],
		"cards": [],
		"holder": [],
	},
}

var rematch_intro_started := false


func _first_map_number() -> int:
	return -1


func _world_number() -> int:
	return 5


func _map_configs() -> Dictionary:
	return REMATCH_CONFIGS


func _build_stage_boss_area() -> void:
	super._build_stage_boss_area()
	boss = FifthBossScript.new()
	_spawn_enemy(boss, Vector2(5700, 2205))
	boss.projectile_requested.connect(_on_boss_projectile_requested)
	boss.boss_defeated.connect(_on_boss_defeated)


func _entry_complete_state() -> int:
	camera_locked = true
	camera_lock_position = Vector2(5600, 2160)
	return StageState.BOSS_INTRO


func _update_boss_intro() -> void:
	if not rematch_intro_started:
		rematch_intro_started = true
		boss.start_intro()
		boss.set_gameplay_active(true)
	super._update_boss_intro()



func _entry_has_portal() -> bool:
	return true


func _update_camera() -> void:
	if not is_instance_valid(camera):
		return
	camera_lock_position = Vector2(5600, 2160)
	camera.position = camera_lock_position
	_update_background()
