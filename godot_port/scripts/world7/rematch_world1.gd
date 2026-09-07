extends "res://scripts/world1/stage1.gd"

const REMATCH_CONFIGS := {
	75: {
		"width": 200,
		"height": 28,
		"start": Vector2(3380, 300),
		"exit": Rect2(),
		"next": 0,
		"red_balls": [],
		"springs": [],
		"turrets": [],
		"birds": [],
		"pumpkins": [],
		"cards": [],
		"holder": [],
	},
}


func _first_map_number() -> int:
	return -1


func _world_number() -> int:
	return 1


func _map_configs() -> Dictionary:
	return REMATCH_CONFIGS


func _entry_complete_state() -> int:
	boss_room_active = true
	return StageState.BOSS_INTRO


func _update_boss_intro() -> void:
	state_ticks += 1
	if not boss_spawn_started and state_ticks >= 35:
		boss_spawn_started = true
		boss_meter_ticks = 0
		boss_meter_fill_phase = 0
		boss = FirstBossScript.new()
		_spawn_enemy(boss, Vector2(3180, -100))
		boss.configure()
		boss.boss_defeated.connect(_on_boss_defeated)
		boss.set_gameplay_active(true)
	if boss_spawn_started and is_instance_valid(boss) and boss.state != FirstStageBoss.BossState.ENTERING:
		boss_meter_fill_phase += 1
		if boss_meter_fill_phase >= BOSS_METER_FILL_INTERVAL:
			boss_meter_fill_phase = 0
			boss_meter_ticks += 1
			get_node("/root/AudioManager").play_sfx("recuperator")
	if is_instance_valid(boss) and boss.vulnerable:
		stage_state = StageState.BOSS
		state_ticks = 0
		camera_locked = false
		_set_gameplay_active(true)

