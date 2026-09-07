extends "res://scripts/shared/stage_base.gd"

const IceMetScript = preload("res://scripts/world6/ice_met.gd")
const IceNeedleScript = preload("res://scripts/world6/ice_needle.gd")
const IcicleScript = preload("res://scripts/world6/icicle.gd")
const IceSpikeScript = preload("res://scripts/world6/ice_spike.gd")
const IcePumpkinScript = preload("res://scripts/world6/ice_pumpkin.gd")
const IceHolderScript = preload("res://scripts/world6/ice_holder.gd")
const CardHolderScript = preload("res://scripts/world6/card_holder.gd")
const CardPickupScript = preload("res://scripts/world6/card_pickup.gd")
const IcyBossScript = preload("res://scripts/world6/icy_boss.gd")
const IcyAttackScript = preload("res://scripts/world6/icy_attack.gd")
const SixthBossRewardScript = preload("res://scripts/world6/sixth_boss_reward.gd")
const STAGE6_ATLAS := preload("res://assets/world6/terrain.png")
const STAGE6_BACKGROUND := preload("res://assets/world6/background.png")

const STAGE6_SOURCE_RECTS := {
	"2": Vector2i(20, 0), "3": Vector2i(40, 0), "4": Vector2i(60, 0),
	"5": Vector2i(20, 20), "6": Vector2i(40, 20), "7": Vector2i(60, 20),
	"8": Vector2i(20, 40), "9": Vector2i(40, 40), "-": Vector2i(60, 40),
	"a": Vector2i(0, 0), "A": Vector2i(0, 0), "b": Vector2i(0, 20),
	"B": Vector2i(140, 0), "c": Vector2i(0, 40), "C": Vector2i(140, 20),
	"d": Vector2i(0, 60), "D": Vector2i(0, 60), "e": Vector2i(80, 0),
	"E": Vector2i(80, 0), "f": Vector2i(80, 20), "F": Vector2i(160, 0),
	"g": Vector2i(80, 40), "G": Vector2i(160, 20), "h": Vector2i(80, 60),
	"H": Vector2i(80, 60), "i": Vector2i(20, 60), "I": Vector2i(120, 60),
	"j": Vector2i(40, 60), "J": Vector2i(140, 60), "k": Vector2i(60, 60),
	"K": Vector2i(160, 60), "l": Vector2i(120, 40), "L": Vector2i(160, 80),
	"m": Vector2i(120, 0), "M": Vector2i(160, 100), "n": Vector2i(120, 20),
	"N": Vector2i(160, 120), "o": Vector2i(20, 80), "O": Vector2i(20, 100),
	"p": Vector2i(20, 120), "P": Vector2i(0, 120), "q": Vector2i(0, 100),
	"Q": Vector2i(0, 80), "r": Vector2i(40, 80), "R": Vector2i(40, 100),
	"s": Vector2i(40, 120), "S": Vector2i(60, 120), "t": Vector2i(60, 100),
	"T": Vector2i(60, 80), "u": Vector2i(100, 120), "U": Vector2i(100, 100),
	"v": Vector2i(100, 80), "V": Vector2i(80, 80), "w": Vector2i(80, 100),
	"W": Vector2i(80, 120), "x": Vector2i(120, 120), "X": Vector2i(120, 100),
	"y": Vector2i(120, 80), "Y": Vector2i(140, 80), "z": Vector2i(140, 100),
	"Z": Vector2i(140, 120), "(": Vector2i(100, 0), ")": Vector2i(100, 20),
	",": Vector2i(100, 40), ">": Vector2i(140, 40), ".": Vector2i(100, 60),
	"<": Vector2i(160, 40),
}
const STAGE6_OVERLAY_SOURCE_RECTS := {
	"A": Vector2i(120, 40), "D": Vector2i(120, 40),
	"E": Vector2i(120, 40), "H": Vector2i(120, 40),
}
const STAGE6_NON_SOLID := [
	"0", "1", "5", "6", "7", "8", "9", "-", "l", "L",
	"o", "O", "p", "P", "q", "Q", "r", "R", "s", "S", "t", "T",
	"u", "U", "v", "V", "w", "W", "x", "X", "y", "Y", "z", "Z",
]

const MAP_CONFIGS := {
	60: {
		"width": 400, "height": 34, "start": Vector2(60, 160),
		"exit": Rect2(7960, 300, 80, 260), "next": 61,
		"ice_mets": [Vector2(1140, 277), Vector2(2500, 357), Vector2(3540, 477), Vector2(4880, 517), Vector2(7460, 397)],
		"icicles": [[Vector2(4184, 281), 0], [Vector2(4219, 282), 1], [Vector2(5624, 361), 0], [Vector2(5659, 362), 1], [Vector2(6404, 281), 0], [Vector2(6439, 282), 1]],
		"spikes": [[Vector2(7140, 492), 140.0]], "pumpkins": [],
		"cards": [[Vector2(6180, 460), 14, true]],
		"card_holders": [[Vector2(3380, 120), 41]], "ice_holders": [[Vector2(1840, 390), 51]],
		"ice_blocks": [],
	},
	61: {
		"width": 400, "height": 50, "start": Vector2(0, 740),
		"exit": Rect2(7960, 580, 80, 120), "next": 62,
		"ice_mets": [Vector2(1320, 877), Vector2(1760, 577), Vector2(2760, 517), Vector2(3630, 517), Vector2(6120, 337), Vector2(5320, 817), Vector2(7740, 737)],
		"icicles": [[Vector2(544, 541), 0], [Vector2(579, 542), 1], [Vector2(1804, 341), 0], [Vector2(1839, 342), 1], [Vector2(4384, 141), 0], [Vector2(4419, 142), 1], [Vector2(6024, 721), 0], [Vector2(6059, 722), 1], [Vector2(7464, 561), 0], [Vector2(7499, 562), 1]],
		"spikes": [[Vector2(3000, 652), 200.0], [Vector2(5320, 352), 140.0], [Vector2(6280, 472), 240.0]],
		"pumpkins": [Vector2(1500, 680), Vector2(4520, 400)],
		"cards": [[Vector2(6540, 280), 49, false], [Vector2(5780, 720), 18, true]],
		"card_holders": [], "ice_holders": [[Vector2(7460, 810), 44]], "ice_blocks": [],
	},
	62: {
		"width": 200, "height": 60, "start": Vector2(0, 140),
		"exit": Rect2(), "next": 0,
		"ice_mets": [Vector2(660, 257), Vector2(1580, 337), Vector2(3440, 377), Vector2(1660, 617), Vector2(2340, 617), Vector2(3020, 617), Vector2(880, 1097), Vector2(1620, 1017)],
		"icicles": [[Vector2(1384, 81), 0], [Vector2(1419, 82), 1], [Vector2(2104, 161), 0], [Vector2(2139, 162), 1], [Vector2(784, 521), 0], [Vector2(819, 522), 1]],
		"spikes": [[Vector2(1220, 392), 260.0], [Vector2(1940, 432), 500.0], [Vector2(2600, 432), 200.0], [Vector2(1400, 712), 140.0]],
		"pumpkins": [Vector2(2140, 300)],
		"cards": [[Vector2(840, 880), 23, false], [Vector2(2140, 260), 31, false]],
		"card_holders": [], "ice_holders": [[Vector2(1980, 1010), 46]],
		"ice_blocks": [[Vector2(3440, 990), 1], [Vector2(3460, 990), 2], [Vector2(3480, 990), 1], [Vector2(3760, 990), 2], [Vector2(3780, 990), 1], [Vector2(3800, 990), 2]],
	},
}

var overlay_terrain: SakuraTerrain
var card_holders: Array[World6CardHolder] = []
var ice_holders: Array[World6IceHolder] = []
var background_base_positions: Array[Vector2] = []
var boss: SixthStageBoss
var boss_reward: SixthBossReward
var boss_intro_ready := false
var boss_meter_ticks := 0
var boss_health_was_visible_on_death := false


func _first_map_number() -> int:
	return 60


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE6_ATLAS,
		STAGE6_SOURCE_RECTS,
		PackedStringArray(STAGE6_NON_SOLID),
		PackedStringArray(),
		{}
	)


func _configure_checkpoint() -> void:
	if map_number == 62 and progress.sixth_boss_checkpoint:
		player.position = Vector2(2940, 1020)
		checkpoint_active = true
		camera_locked = true
		camera_lock_position = Vector2(3060, 960)


func _build_stage_boss_area() -> void:
	overlay_terrain = TerrainScript.new()
	overlay_terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE6_ATLAS,
		STAGE6_OVERLAY_SOURCE_RECTS,
		PackedStringArray(STAGE6_OVERLAY_SOURCE_RECTS.keys()),
		PackedStringArray(),
		{}
	)
	overlay_terrain.z_index = -1
	add_child(overlay_terrain)
	for data in map_config["ice_blocks"]:
		var block := Sprite2D.new()
		block.centered = false
		block.position = data[0]
		block.texture = preload("res://assets/world6/ice_block_1.png") if data[1] == 1 else preload("res://assets/world6/ice_block_2.png")
		block.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		block.z_index = 2
		add_child(block)
	if map_number == 62:
		_build_boss_area()


func _enemy_update_interval() -> int:
	return 2


func _physics_process(_delta: float) -> void:
	if _handle_global_input():
		return
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
			_update_victory()
	_finish_physics_tick()


func _update_playing() -> void:
	if map_number == 62 and player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(2740, 960, 30, 140), true):
		_begin_checkpoint_entry()
		return
	var exit_rect: Rect2 = map_config["exit"]
	if exit_rect.has_area() and exit_rect.intersects(player.get_hit_rect()):
		stage_state = StageState.EXITING
		state_ticks = 0
		_set_gameplay_active(false)
		player.set_scripted_animation_active(true)


func _update_checkpoint_entry() -> void:
	state_ticks += 1
	player.position.y = move_toward(player.position.y, 1020.0, 10.0)
	if player.position.y == 1020.0:
		player.y_speed = 0.0
		player.grounded = true
	if state_ticks <= 40:
		_set_door_opening(0, float(state_ticks) / 40.0)
	elif state_ticks <= 120:
		_set_door_opening(0, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(3060, 960), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(0, 1.0 - float(state_ticks - 120) / 40.0)
	else:
		_set_door_opening(0, 0.0)
		camera_lock_position = Vector2(3060, 960)
		progress.set_sixth_boss_checkpoint(true)
		stage_state = StageState.CHECKPOINT
		state_ticks = 0
		player.set_scripted_animation_active(false)
		_set_gameplay_active(true)


func _update_checkpoint() -> void:
	player.position.x = clampf(player.position.x, 2770.0, 3310.0)
	if player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(3350, 960, 30, 140), true):
		_begin_boss_entry()


func _update_boss_entry() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		_set_door_opening(1, float(state_ticks) / 40.0)
	elif state_ticks <= 108:
		_set_door_opening(1, 1.0)
		player.scripted_step_right(2.5)
		camera_lock_position = transition_camera_start.lerp(Vector2(3630, 960), float(state_ticks - 40) / 68.0)
	elif state_ticks <= 148:
		_set_door_opening(1, 1.0 - float(state_ticks - 108) / 40.0)
	else:
		_set_door_opening(1, 0.0)
		camera_lock_position = Vector2(3630, 960)
		player.position.y = 1020.0
		player.y_speed = 0.0
		player.grounded = true
		player.set_scripted_animation_active(false)
		stage_state = StageState.BOSS_INTRO
		state_ticks = 0
		boss_intro_ready = false
		boss_meter_ticks = 0
		boss.visible = true
		boss.set_gameplay_active(true)
		boss.begin_intro()


func _on_boss_intro_finished() -> void:
	boss_intro_ready = true
	boss_meter_ticks = 0


func _update_boss_intro() -> void:
	state_ticks += 1
	if not boss_intro_ready:
		return
	boss_meter_ticks += 1
	if boss_meter_ticks % 2 == 0:
		get_node("/root/AudioManager").play_sfx("recuperator")
	if boss_meter_ticks >= 60:
		stage_state = StageState.BOSS
		state_ticks = 0
		boss.start_fight()
		_set_gameplay_active(true)


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 3310.0, 3960.0)


func _on_boss_attack_requested(spawn_position: Vector2, variant: int, direction: int) -> void:
	get_node("/root/AudioManager").play_sfx("tiro7")
	var attack: World6IcyAttack = IcyAttackScript.new()
	_spawn_enemy(attack, spawn_position)
	attack.configure(variant, direction)
	attack.set_gameplay_active(true)


func _on_boss_defeated() -> void:
	boss_reward_position = boss.position + boss.body_size * 0.5 - Vector2(11, 18)
	enemies.erase(boss)
	stage_state = StageState.VICTORY
	state_ticks = 0
	_set_gameplay_active(false)
	player.immunity_ticks = 0
	hud.set_boss_health(0, false)
	boss_reward_started = false
	boss_reward_homing = false
	hud.set_boss_flash(0.0)


func _update_victory() -> void:
	_move_player_to_boss_departure(6)
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 5:
				for _burst in range(3):
					_spawn_boss_explosion(boss.position + Vector2(60, 70))
			if state_ticks % 7 == 3 and is_instance_valid(boss):
				_spawn_boss_explosion(boss.position + Vector2(randi_range(0, 120), randi_range(0, 140)))
			return
		if state_ticks <= 285:
			hud.set_boss_flash(1.0)
			return
		if is_instance_valid(boss):
			boss.queue_free()
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
	if departure_ticks > 0:
		_update_departure()


func _spawn_boss_reward() -> void:
	boss_reward_started = true
	if _is_active_rematch():
		return
	boss_reward = SixthBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(5)
	progress.unlock_sixth_boss_reward()
	_start_departure()


func _complete_departure() -> void:
	progress.set_sixth_boss_checkpoint(false)
	_finish_elemental_or_rematch(6)


func _spawn_stage_objects() -> void:
	for spawn_position in map_config["ice_mets"]:
		var ice_met: World6IceMet = IceMetScript.new()
		_spawn_enemy(ice_met, spawn_position)
		ice_met.configure()
		ice_met.needles_requested.connect(_on_ice_needles_requested)
	for data in map_config["icicles"]:
		var icicle: World6Icicle = IcicleScript.new()
		_spawn_enemy(icicle, data[0])
		icicle.configure(data[1])
	for data in map_config["spikes"]:
		var spike: World6IceSpike = IceSpikeScript.new()
		_spawn_enemy(spike, data[0])
		spike.configure(data[1])
	for spawn_position in map_config["pumpkins"]:
		var pumpkin: World6IcePumpkin = IcePumpkinScript.new()
		_spawn_enemy(pumpkin, spawn_position)
		pumpkin.configure()
	for data in map_config["cards"]:
		if not progress.has_card(data[1]):
			_spawn_card(data[0], data[1], data[2])
	for data in map_config["card_holders"]:
		if not progress.has_card(data[1]):
			var holder: World6CardHolder = CardHolderScript.new()
			holder.position = data[0]
			holder.z_index = 10
			holder.card_id = data[1]
			add_child(holder)
			holder.opened.connect(_on_holder_opened)
			card_holders.append(holder)
	for data in map_config["ice_holders"]:
		if not progress.has_card(data[1]):
			var holder: World6IceHolder = IceHolderScript.new()
			holder.position = data[0]
			holder.z_index = 10
			holder.card_id = data[1]
			add_child(holder)
			holder.opened.connect(_on_holder_opened)
			ice_holders.append(holder)


func _on_ice_needles_requested(origin: Vector2) -> void:
	var data := [
		[Vector2(0, 22), 0, 0], [Vector2(3, 9), 1, 0], [Vector2(12, 1), 2, 0],
		[Vector2(22, -1), 3, 0], [Vector2(34, 1), 2, 1], [Vector2(41, 9), 1, 1],
		[Vector2(46, 22), 0, 1],
	]
	for needle_data in data:
		var needle: World6IceNeedle = IceNeedleScript.new()
		_spawn_enemy(needle, origin + needle_data[0])
		needle.configure(needle_data[1], needle_data[2])
		needle.set_gameplay_active(true)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: World6CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)


func _on_holder_opened(spawn_position: Vector2, card_id: int) -> void:
	if not progress.has_card(card_id):
		_spawn_card(spawn_position, card_id, true)


func _damage_stage_object_in_rect(rect: Rect2, damage: int, _weapon_id: int = 1) -> bool:
	for holder in card_holders:
		if is_instance_valid(holder) and holder.projectile_mask_overlap(rect):
			holder.take_projectile_hit(damage)
			return true
	for holder in ice_holders:
		if is_instance_valid(holder) and holder.projectile_mask_overlap(rect):
			holder.take_projectile_hit(damage)
			return true
	return false


func _before_player_death() -> void:
	boss_health_was_visible_on_death = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO


func _build_boss_area() -> void:
	for data in [[Vector2(2740, 960), preload("res://assets/world6/boss_floor_right.png")], [Vector2(3320, 960), preload("res://assets/world6/boss_floor_left.png")]]:
		var floor_cap := Sprite2D.new()
		floor_cap.centered = false
		floor_cap.position = data[0]
		floor_cap.texture = data[1]
		floor_cap.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		floor_cap.z_index = 8
		add_child(floor_cap)
	var door_texture: Texture2D = preload("res://assets/world6/door.png")
	for door_position in [Vector2(2740, 960), Vector2(3350, 960)]:
		var door := Sprite2D.new()
		door.centered = false
		door.texture = door_texture
		door.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		door.position = door_position
		door.z_index = 9
		add_child(door)
		boss_doors.append(door)
	boss = IcyBossScript.new()
	_spawn_enemy(boss, Vector2(3980, 1120))
	boss.visible = false
	boss.intro_finished.connect(_on_boss_intro_finished)
	boss.attack_requested.connect(_on_boss_attack_requested)
	boss.boss_defeated.connect(_on_boss_defeated)


func _set_door_opening(index: int, amount: float) -> void:
	if index < 0 or index >= boss_doors.size():
		return
	boss_doors[index].position.y = 960.0 - clampf(amount, 0.0, 1.0) * 140.0


func _build_background() -> void:
	var fill := ColorRect.new()
	fill.position = Vector2.ZERO
	fill.size = Vector2(map_config["width"] * 20, map_config["height"] * 20)
	fill.color = Color8(0, 16, 63) if map_number == 62 or map_number == 74 else Color8(111, 200, 239)
	fill.mouse_filter = Control.MOUSE_FILTER_IGNORE
	fill.z_index = -200
	add_child(fill)
	var positions: Array[Vector2] = []
	if map_number == 60:
		positions = [Vector2(0, 0), Vector2(640, 0), Vector2(1280, 0), Vector2(1920, 0)]
	elif map_number == 61:
		positions = [Vector2(640, -20), Vector2(1280, -20), Vector2(1920, -20), Vector2(2560, -20)]
	for sprite_position in positions:
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = STAGE6_BACKGROUND
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		sprite.position = sprite_position
		sprite.z_index = -100
		add_child(sprite)
		background_sprites.append(sprite)
		background_base_positions.append(sprite_position)
	if not background_sprites.is_empty():
		background_sprite = background_sprites[0]


func _update_camera() -> void:
	if not is_instance_valid(camera) or not is_instance_valid(player):
		return
	if camera_locked:
		camera.position = camera_lock_position
		_update_background()
		return
	var center := player.get_center()
	camera.position = Vector2(
		clampf(center.x, VIEWPORT_HALF_SIZE.x, terrain.world_size.x - VIEWPORT_HALF_SIZE.x),
		clampf(center.y, VIEWPORT_HALF_SIZE.y, terrain.world_size.y - VIEWPORT_HALF_SIZE.y)
	)
	_update_background()


func _update_background() -> void:
	if not is_instance_valid(camera):
		return
	var viewport_top_left := camera.position - VIEWPORT_HALF_SIZE
	var sampled_origin := viewport_top_left / 5.0
	var world_offset := viewport_top_left - sampled_origin
	for index in range(background_sprites.size()):
		background_sprites[index].position = world_offset + background_base_positions[index]


func _update_boss_hud() -> void:
	var boss_visible := false
	var displayed_boss_hp := 0
	if is_instance_valid(boss):
		boss_visible = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO or (stage_state == StageState.DYING and boss_health_was_visible_on_death)
		displayed_boss_hp = boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_boss_hp = clampi(int(boss_meter_ticks / 2.0), 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)


func _stage_complete_message() -> String:
	return "SIXTH STAGE COMPLETE\n\nPRESS R TO REPLAY"
