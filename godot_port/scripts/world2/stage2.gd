extends "res://scripts/shared/stage_base.gd"

const GhostScript = preload("res://scripts/world2/ghost.gd")
const GhostMaskScript = preload("res://scripts/world2/ghost_mask.gd")
const ShadowSpikeScript = preload("res://scripts/world2/shadow_spike.gd")
const PaintingScript = preload("res://scripts/world2/stage2_painting.gd")
const ArmorScript = preload("res://scripts/world2/stage2_armor.gd")
const CardPickupScript = preload("res://scripts/world2/card_pickup.gd")
const SecondBossScript = preload("res://scripts/world2/second_boss.gd")
const ShadowCloneScript = preload("res://scripts/world2/shadow_clone.gd")
const SecondBossRewardScript = preload("res://scripts/world2/second_boss_reward.gd")
const STAGE2_ATLAS := preload("res://assets/world2/terrain.png")
const STAGE2_SOURCE_RECTS := {
	"2": Vector2i(20, 0),
	"3": Vector2i(0, 20),
	"4": Vector2i(40, 20),
	"5": Vector2i(20, 40),
	"6": Vector2i(20, 20),
	"a": Vector2i(0, 0),
	"b": Vector2i(40, 0),
	"c": Vector2i(0, 40),
	"d": Vector2i(40, 40),
	"e": Vector2i(60, 0),
	"f": Vector2i(80, 0),
	"g": Vector2i(60, 20),
	"h": Vector2i(80, 20),
	"m": Vector2i(100, 40),
	"n": Vector2i(100, 20),
	"x": Vector2i(60, 40),
	"z": Vector2i(80, 40),
	"w": Vector2i(60, 40),
	"q": Vector2i(80, 40),
}
const STAGE2_NON_SOLID := ["1", "6", "m", "n", "x", "z"]

const MAP_CONFIGS := {
	20: {
		"width": 100,
		"height": 24,
		"start": Vector2(40, 260),
		"exit": Rect2(1960, 100, 80, 200),
		"next": 21,
		"background": true,
		"ghosts": [[Vector2(1580, 200), 0]],
		"paintings": [],
		"armors": [],
		"spikes": [],
		"mask_spawners": [],
		"cards": [[Vector2(1770, 280), true, 12]],
	},
	21: {
		"width": 210,
		"height": 28,
		"start": Vector2(0, 300),
		"exit": Rect2(4160, 340, 80, 200),
		"next": 22,
		"background": false,
		"ghosts": [
			[Vector2(510, 220), 0], [Vector2(1300, 200), 0],
			[Vector2(2670, 280), 0], [Vector2(3630, 400), 0],
		],
		"paintings": [Vector2(2100, 180)],
		"armors": [[Vector2(1120, 370), 0], [Vector2(3860, 390), 22]],
		"spikes": [],
		"mask_spawners": [[Vector2(3120, 180), -1, 140, 1580]],
		"cards": [[Vector2(2040, 300), true, 16]],
	},
	22: {
		"width": 120,
		"height": 70,
		"start": Vector2(0, 120),
		"exit": Rect2(2360, 940, 80, 200),
		"next": 23,
		"background": false,
		"ghosts": [
			[Vector2(600, 230), 0], [Vector2(1800, 200), 0],
			[Vector2(1860, 560), 1], [Vector2(720, 1080), 0],
			[Vector2(1610, 960), 0],
		],
		"paintings": [],
		"armors": [[Vector2(1180, 250), 0], [Vector2(400, 1250), 0], [Vector2(1770, 990), 35]],
		"spikes": [
			[Vector2(740, 352), 120], [Vector2(1620, 352), 160],
			[Vector2(2100, 772), 100], [Vector2(1160, 772), 220],
			[Vector2(620, 772), 120], [Vector2(1160, 1172), 120],
		],
		"mask_spawners": [[Vector2(120, 560), 1, 140, 2400]],
		"cards": [[Vector2(1680, 200), false, 47], [Vector2(40, 1040), false, 39]],
	},
	23: {
		"width": 300,
		"height": 36,
		"start": Vector2(0, 440),
		"exit": Rect2(),
		"next": 0,
		"background": false,
		"ghosts": [
			[Vector2(620, 340), 0], [Vector2(860, 460), 0],
			[Vector2(1230, 530), 0], [Vector2(1400, 200), 0],
			[Vector2(1760, 400), 0], [Vector2(2160, 260), 0],
			[Vector2(3300, 460), 0],
		],
		"paintings": [],
		"armors": [[Vector2(3860, 530), 27]],
		"spikes": [[Vector2(340, 652), 2500]],
		"mask_spawners": [[Vector2(4560, 440), -1, 140, 3080]],
		"cards": [[Vector2(660, 60), false, 24]],
	},
}

var mask_spawners: Array[Dictionary] = []
var boss: SecondStageBoss
var boss_reward: SecondBossReward
var defeated_clone_positions: Array[Vector2] = []
var world2_tick_phase := 0


func _first_map_number() -> int:
	return 20


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE2_ATLAS,
		STAGE2_SOURCE_RECTS,
		PackedStringArray(STAGE2_NON_SOLID),
		PackedStringArray(),
		{}
	)


func _configure_checkpoint() -> void:
	if map_number == 23 and progress.second_boss_checkpoint:
		player.position = Vector2(4840, 460)
		checkpoint_active = true
		camera_locked = true
		camera_lock_position = Vector2(5020, 380)


func _build_stage_boss_area() -> void:
	if map_number == 23:
		_build_boss_area()


func _enemy_update_interval() -> int:
	return 2


func _physics_process(_delta: float) -> void:
	if _handle_global_input():
		return
	world2_tick_phase = (world2_tick_phase + 1) % 2
	var world2_logic_tick := world2_tick_phase == 0
	match stage_state:
		StageState.ENTRY:
			_update_entry()
		StageState.PLAYING:
			_update_playing()
		StageState.EXITING:
			_update_exit()
		StageState.DYING:
			_update_death()
		StageState.CHECKPOINT_ENTRY:
			_update_checkpoint_entry()
		StageState.CHECKPOINT:
			_update_checkpoint()
		StageState.BOSS_ENTRY:
			_update_boss_entry()
		StageState.BOSS_INTRO:
			_update_boss_intro()
		StageState.BOSS:
			_update_boss()
		StageState.VICTORY:
			if departure_ticks > 0:
				_update_departure()
			elif world2_logic_tick:
				_update_victory()
	if world2_logic_tick and (stage_state == StageState.PLAYING or stage_state == StageState.CHECKPOINT):
		_update_mask_spawners()
	_finish_physics_tick()


func _update_playing() -> void:
	if map_number == 23:
		if player.position.x >= 4660.0:
			player.position.x = 4660.0
			player.x_speed = minf(player.x_speed, 0.0)
		if player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(4700, 440, 30, 100), true):
			_begin_checkpoint_entry()
		return
	if player.grounded and player.get_hit_rect().intersects(map_config["exit"]):
		stage_state = StageState.EXITING
		state_ticks = 0
		_set_gameplay_active(false)
		player.set_scripted_animation_active(true)


func _update_checkpoint_entry() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		player.position.y = move_toward(player.position.y, 460.0, 10.0)
		if player.position.y == 460.0:
			player.y_speed = 0.0
			player.grounded = true
		_set_door_opening(0, float(state_ticks) / 40.0)
	elif state_ticks <= 120:
		_set_door_opening(0, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(5020, 380), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(0, 1.0 - float(state_ticks - 120) / 40.0)
	else:
		_set_door_opening(0, 0.0)
		camera_lock_position = Vector2(5020, 380)
		progress.set_second_boss_checkpoint(true)
		stage_state = StageState.CHECKPOINT
		state_ticks = 0
		player.set_scripted_animation_active(false)
		_set_gameplay_active(true)


func _update_checkpoint() -> void:
	player.position.x = clampf(player.position.x, 4730.0, 5270.0)
	if player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(5310, 440, 30, 100), true):
		_begin_boss_entry()


func _update_boss_entry() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		_set_door_opening(1, float(state_ticks) / 40.0)
	elif state_ticks <= 120:
		_set_door_opening(1, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(5640, 380), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(1, 1.0 - float(state_ticks - 120) / 40.0)
	else:
		_set_door_opening(1, 0.0)
		camera_lock_position = Vector2(5640, 380)
		player.position.y = 460.0
		player.y_speed = 0.0
		player.grounded = true
		player.set_scripted_animation_active(false)
		stage_state = StageState.BOSS_INTRO
		state_ticks = 0
		boss.set_gameplay_active(true)
		boss.begin_intro()


func _update_boss_intro() -> void:
	state_ticks += 1


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 5340.0, 5920.0)


func _on_boss_ready() -> void:
	stage_state = StageState.BOSS
	state_ticks = 0
	camera_locked = true
	camera_lock_position = Vector2(5640, 380)
	_set_gameplay_active(true)


func _on_boss_control_lock_requested(value: bool) -> void:
	player.set_gameplay_active(not value)


func _on_clone_requested(spawn_position: Vector2) -> void:
	var clone: ShadowClone = ShadowCloneScript.new()
	_spawn_enemy(clone, spawn_position)
	clone.configure(boss)
	clone.set_gameplay_active(true)


func _on_boss_defeated() -> void:
	boss_reward_position = boss.position + Vector2(14, 7)
	enemies.erase(boss)
	for clone in get_tree().get_nodes_in_group("second_boss_clones"):
		if is_instance_valid(clone):
			defeated_clone_positions.append(clone.position)
	stage_state = StageState.VICTORY
	state_ticks = 0
	_set_gameplay_active(false)
	player.immunity_ticks = 0
	hud.set_boss_health(0, false)
	boss_reward_started = false
	boss_reward_homing = false
	hud.set_boss_flash(0.0)


func _update_victory() -> void:
	_move_player_to_boss_departure(2)
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 5:
				for burst in range(3):
					_spawn_boss_explosion(boss.position + Vector2(25, 25))
					for clone_position in defeated_clone_positions:
						_spawn_boss_explosion(clone_position + Vector2(25, 25))
			if state_ticks % 7 == 3 and is_instance_valid(boss):
				_spawn_boss_explosion(boss.position + Vector2(randi_range(0, 50), randi_range(0, 50)))
			if state_ticks % 7 == 6:
				for clone_position in defeated_clone_positions:
					_spawn_boss_explosion(clone_position + Vector2(randi_range(0, 46), randi_range(0, 46)))
			return
		if state_ticks <= 285:
			hud.set_boss_flash(1.0)
			return
		if is_instance_valid(boss):
			boss.queue_free()
		for clone in get_tree().get_nodes_in_group("second_boss_clones"):
			if is_instance_valid(clone):
				clone.queue_free()
		_spawn_boss_reward()
	if not boss_reward_homing:
		var fade_tick := state_ticks - 285
		hud.set_boss_flash(1.0 - float(fade_tick) / 255.0)
		if fade_tick >= 255:
			boss_reward_homing = true
			hud.set_boss_flash(0.0)
			if is_instance_valid(boss_reward):
				boss_reward.begin_homing()
			else:
				_start_departure()


func _spawn_boss_reward() -> void:
	boss_reward_started = true
	if _is_active_rematch():
		return
	boss_reward = SecondBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(1)
	progress.unlock_second_boss_reward()
	_start_departure()


func _complete_departure() -> void:
	progress.set_second_boss_checkpoint(false)
	if get_tree().current_scene == self:
		_finish_elemental_or_rematch(2)


func _spawn_stage_objects() -> void:
	for data in map_config["ghosts"]:
		var ghost: GhostEnemy = GhostScript.new()
		_spawn_enemy(ghost, data[0])
		ghost.sprite.flip_h = data[1] > 0
	for painting_position in map_config["paintings"]:
		var painting: Stage2Painting = PaintingScript.new()
		painting.position = painting_position
		painting.z_index = 5
		add_child(painting)
		painting.setup(player)
	for data in map_config["armors"]:
		var armor: Stage2Armor = ArmorScript.new()
		_spawn_enemy(armor, data[0])
		armor.z_index = 9
		armor.configure(data[1])
		armor.opened.connect(_on_armor_opened)
	for data in map_config["spikes"]:
		var spike: ShadowSpike = ShadowSpikeScript.new()
		spike.position = data[0]
		spike.z_index = 8
		add_child(spike)
		spike.setup(player, data[1])
	for source_data in map_config["mask_spawners"]:
		mask_spawners.append({
			"position": source_data[0],
			"direction": source_data[1],
			"span": source_data[2],
			"stop_x": source_data[3],
			"timer": 40,
		})
	for data in map_config["cards"]:
		if not progress.has_card(data[2]):
			_spawn_card(data[0], data[2], data[1])


func _update_mask_spawners() -> void:
	for index in range(mask_spawners.size()):
		var data := mask_spawners[index]
		var should_spawn := false
		if data["direction"] < 0:
			should_spawn = player.position.x < data["position"].x - 350.0
		else:
			should_spawn = player.position.x > data["position"].x + 420.0
		if not should_spawn:
			continue
		data["timer"] += 1
		if data["timer"] >= 80:
			var mask: GhostMaskEnemy = GhostMaskScript.new()
			var spawn_position: Vector2 = data["position"] + Vector2(0, randi_range(0, int(data["span"]) - 1))
			_spawn_enemy(mask, spawn_position)
			mask.configure(data["direction"], data["stop_x"])
			mask.set_gameplay_active(true)
			data["timer"] = 0
		mask_spawners[index] = data


func _on_armor_opened(drop_position: Vector2, card_id: int) -> void:
	if card_id == 0:
		_spawn_recovery(drop_position, SakuraEnemy.DropType.SMALL)
	elif not progress.has_card(card_id):
		_spawn_card(drop_position, card_id, true)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)


func _build_background() -> void:
	var fill := ColorRect.new()
	fill.position = Vector2.ZERO
	fill.size = Vector2(map_config["width"] * 20, map_config["height"] * 20)
	fill.color = Color8(56, 72, 96) if map_config["background"] else Color.BLACK
	fill.mouse_filter = Control.MOUSE_FILTER_IGNORE
	fill.z_index = -200
	add_child(fill)
	if map_config["background"]:
		for index in range(2):
			var sprite := Sprite2D.new()
			sprite.centered = false
			sprite.texture = preload("res://assets/world2/background.png")
			sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
			sprite.z_index = -100
			add_child(sprite)
			background_sprites.append(sprite)
		background_sprite = background_sprites[0]


func _update_background() -> void:
	if not is_instance_valid(background_sprite) or not is_instance_valid(camera):
		return
	var viewport_top_left := camera.position - VIEWPORT_HALF_SIZE
	var background_origin := viewport_top_left * 0.8
	for index in range(background_sprites.size()):
		background_sprites[index].position = background_origin + Vector2(index * background_sprite.texture.get_width(), 0)


func _build_boss_area() -> void:
	var door_texture: Texture2D = preload("res://assets/world2/door.png")
	for door_position in [Vector2(4700, 440), Vector2(5310, 440)]:
		var door := Sprite2D.new()
		door.centered = false
		door.texture = door_texture
		door.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		door.position = door_position
		door.z_index = 9
		add_child(door)
		boss_doors.append(door)
	boss = SecondBossScript.new()
	_spawn_enemy(boss, Vector2(5700, 530))
	boss.boss_ready.connect(_on_boss_ready)
	boss.control_lock_requested.connect(_on_boss_control_lock_requested)
	boss.clone_requested.connect(_on_clone_requested)
	boss.boss_defeated.connect(_on_boss_defeated)


func _set_door_opening(index: int, amount: float) -> void:
	if index < 0 or index >= boss_doors.size():
		return
	boss_doors[index].position.y = 440.0 - clampf(amount, 0.0, 1.0) * 100.0


func _update_camera() -> void:
	if not is_instance_valid(camera) or not is_instance_valid(player):
		return
	if camera_locked:
		camera.position = camera_lock_position
		_update_background()
		return
	var center := player.get_center()
	if map_number == 23 and not checkpoint_active:
		camera.position = Vector2(
			clampf(center.x, VIEWPORT_HALF_SIZE.x, 4410.0),
			clampf(center.y, VIEWPORT_HALF_SIZE.y, 480.0)
		)
	else:
		camera.position = Vector2(
			clampf(center.x, VIEWPORT_HALF_SIZE.x, terrain.world_size.x - VIEWPORT_HALF_SIZE.x),
			clampf(center.y, VIEWPORT_HALF_SIZE.y, terrain.world_size.y - VIEWPORT_HALF_SIZE.y)
		)
	_update_background()


func _update_boss_hud() -> void:
	var boss_visible := false
	var displayed_boss_hp := 0
	if is_instance_valid(boss):
		boss_visible = stage_state == StageState.BOSS or (stage_state == StageState.BOSS_INTRO and boss.state == SecondStageBoss.BossState.METER_FILL)
		displayed_boss_hp = boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_boss_hp = clampi(boss.intro_meter_ticks, 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)
