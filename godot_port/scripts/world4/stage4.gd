extends "res://scripts/shared/stage_base.gd"

const ResettiScript = preload("res://scripts/world4/resetti.gd")
const SeahorseScript = preload("res://scripts/world4/seahorse.gd")
const SeahorseSpawnerScript = preload("res://scripts/world4/seahorse_spawner.gd")
const FishScript = preload("res://scripts/world4/fish.gd")
const OysterScript = preload("res://scripts/world4/oyster.gd")
const OysterLowerScript = preload("res://scripts/world4/oyster_lower.gd")
const OysterPearlScript = preload("res://scripts/world4/oyster_pearl.gd")
const SandMoundScript = preload("res://scripts/world4/sand_mound.gd")
const CardPickupScript = preload("res://scripts/world4/card_pickup.gd")
const WaterLayerScript = preload("res://scripts/world4/water_layer.gd")
const FourthBossScript = preload("res://scripts/world4/fourth_boss.gd")
const WaterShotScript = preload("res://scripts/world4/water_shot.gd")
const FourthBossRewardScript = preload("res://scripts/world4/fourth_boss_reward.gd")
const WaterBubbleScript = preload("res://scripts/world4/water_bubble.gd")
const WaterSplashScript = preload("res://scripts/world4/water_splash.gd")
const STAGE4_ATLAS := preload("res://assets/world4/terrain.png")
const STAGE4_BACKGROUND := preload("res://assets/world4/background.png")
const STAGE4_SOURCE_RECTS := {
	"5": Vector2i(0, 20), "6": Vector2i(20, 20), "7": Vector2i(40, 20),
	"A": Vector2i(0, 20), "S": Vector2i(20, 20), "D": Vector2i(40, 20),
	"9": Vector2i(40, 20), "h": Vector2i(0, 40), "i": Vector2i(0, 40),
	"m": Vector2i(0, 60), "n": Vector2i(0, 60), "q": Vector2i(120, 40),
	"r": Vector2i(120, 60), "s": Vector2i(80, 60), "t": Vector2i(100, 60),
	"u": Vector2i(0, 80), "v": Vector2i(20, 80), "w": Vector2i(40, 80),
	"x": Vector2i(60, 80), ",": Vector2i(60, 20), ".": Vector2i(100, 20),
	"[": Vector2i(0, 40), "]": Vector2i(40, 40), "}": Vector2i(0, 60),
	"{": Vector2i(40, 60),
}
const STAGE4_FOREGROUND_SOURCE_RECTS := {
	"2": Vector2i(0, 0), "3": Vector2i(20, 0), "4": Vector2i(40, 0),
	"8": Vector2i(40, 20), "a": Vector2i(60, 0), "b": Vector2i(60, 20),
	"c": Vector2i(80, 40), "d": Vector2i(80, 0), "e": Vector2i(100, 20),
	"f": Vector2i(100, 40), "g": Vector2i(100, 0), "i": Vector2i(20, 40),
	"j": Vector2i(40, 40), "k": Vector2i(60, 40), "l": Vector2i(120, 0),
	"n": Vector2i(20, 60), "o": Vector2i(40, 60), "p": Vector2i(60, 60),
	",": Vector2i(80, 20), ".": Vector2i(120, 20), "[": Vector2i(20, 40),
	"]": Vector2i(0, 40), "}": Vector2i(20, 60), "{": Vector2i(0, 60),
}
const STAGE4_NON_SOLID := [
	"0", "1", "2", "3", "4", "A", "S", "D", "a", "b", "c", "d",
	"e", "f", "g", "j", "k", "l", "o", "p",
]
const STAGE4_LETHAL := ["0"]
const ALL_TOKENS_NON_SOLID := [
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "S", "D",
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
	"o", "p", "q", "r", "s", "t", "u", "v", "w", "x", ",", ".", "[", "]", "}", "{",
]

const MAP_CONFIGS := {
	40: {
		"width": 450, "height": 40, "start": Vector2(380, 220),
		"exit": Rect2(8960, 360, 80, 200), "next": 41,
		"water_surface": 420.0, "starts_in_water": false,
		"background_rows": [20.0, 180.0],
		"resettis": [Vector2(700, 300), Vector2(1440, 380), Vector2(6270, 380)],
		"seahorse_spawners": [Vector2(3860, 600), Vector2(8540, 540)],
		"fish": [Vector2(3170, 480), Vector2(3220, 450), Vector2(3190, 500), Vector2(3230, 485), Vector2(3185, 445), Vector2(5280, 470), Vector2(5300, 485), Vector2(5270, 515), Vector2(5285, 500), Vector2(8200, 480)],
		"oysters": [
			[Vector2(2046, 446), Vector2(2040, 433), 0],
			[Vector2(4696, 506), Vector2(4690, 493), 0],
			[Vector2(5926, 486), Vector2(5920, 473), 0],
			[Vector2(6996, 386), Vector2(6990, 373), 0],
			[Vector2(7561, 426), Vector2(7560, 413), 1],
		],
		"cards": [[Vector2(20, 220), 50, false], [Vector2(3220, 470), 8, false]],
		"sand_mounds": [[Vector2(7290, 344), 34]],
	},
	41: {
		"width": 450, "height": 40, "start": Vector2(0, 320),
		"exit": Rect2(8960, 0, 80, 200), "next": 42,
		"water_surface": 200.0, "starts_in_water": true,
		"background_rows": [-40.0],
		"resettis": [Vector2(7120, 200)],
		"seahorse_spawners": [Vector2(2050, 620), Vector2(2940, 560), Vector2(3140, 560), Vector2(5740, 320), Vector2(8480, 380)],
		"fish": [Vector2(770, 280), Vector2(870, 320), Vector2(800, 320), Vector2(830, 290), Vector2(786, 300), Vector2(1770, 480), Vector2(1870, 460), Vector2(1700, 490), Vector2(1740, 500), Vector2(3320, 420), Vector2(3300, 440), Vector2(3335, 405), Vector2(3785, 385), Vector2(3805, 355), Vector2(4660, 285), Vector2(4685, 275), Vector2(4670, 305), Vector2(7900, 220), Vector2(7920, 225), Vector2(7960, 235), Vector2(7970, 255), Vector2(8000, 220)],
		"oysters": [
			[Vector2(2656, 546), Vector2(2650, 533), 0],
			[Vector2(4006, 466), Vector2(4000, 453), 0],
			[Vector2(4186, 406), Vector2(4180, 393), 0],
			[Vector2(6606, 246), Vector2(6600, 233), 0],
			[Vector2(1361, 606), Vector2(1360, 593), 1],
			[Vector2(7281, 246), Vector2(7280, 233), 1],
		],
		"cards": [[Vector2(810, 310), 36, false], [Vector2(8660, 80), 30, false]],
		"sand_mounds": [[Vector2(6980, 164), 40]],
	},
	42: {
		"width": 500, "height": 40, "start": Vector2(0, 260),
		"exit": Rect2(), "next": 0,
		"water_surface": 300.0, "starts_in_water": false,
		"background_rows": [60.0],
		"resettis": [Vector2(1790, 260), Vector2(2170, 240)],
		"seahorse_spawners": [Vector2(1160, 400), Vector2(4210, 420), Vector2(5720, 620), Vector2(5755, 620), Vector2(8180, 580), Vector2(8220, 580), Vector2(8260, 580)],
		"fish": [Vector2(960, 275), Vector2(930, 320), Vector2(3560, 320), Vector2(3550, 300), Vector2(3580, 340), Vector2(3560, 355), Vector2(3980, 300), Vector2(3900, 325), Vector2(5270, 460), Vector2(5200, 465), Vector2(5370, 470), Vector2(5250, 430), Vector2(5320, 480), Vector2(5235, 475), Vector2(7450, 460), Vector2(7400, 480), Vector2(7510, 500), Vector2(7465, 493), Vector2(7710, 460), Vector2(7765, 435)],
		"oysters": [
			[Vector2(2686, 226), Vector2(2680, 213), 0],
			[Vector2(4706, 486), Vector2(4700, 473), 0],
			[Vector2(6446, 526), Vector2(6440, 513), 0],
			[Vector2(2301, 226), Vector2(2300, 213), 1],
			[Vector2(7041, 506), Vector2(7040, 493), 1],
		],
		"cards": [[Vector2(5480, 480), 30, true], [Vector2(3550, 330), 36, true]],
		"sand_mounds": [[Vector2(2510, 204), 11]],
	},
}

var foreground_terrain: SakuraTerrain
var water_layer: World4WaterLayer
var seahorse_spawners: Array[World4SeahorseSpawner] = []
var oyster_pearls: Array[World4OysterPearl] = []
var sand_mounds: Array[World4SandMound] = []
var cards: Array[World4CardPickup] = []
var boss: FourthStageBoss
var boss_reward: FourthBossReward
var boss_health_was_visible_on_death := false
var bubble_ticks := 0
var water_effects: Array[Node2D] = []


func _first_map_number() -> int:
	return 40


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE4_ATLAS,
		STAGE4_SOURCE_RECTS,
		PackedStringArray(STAGE4_NON_SOLID),
		PackedStringArray(STAGE4_LETHAL),
		{}
	)
	terrain.set_alpha_collision_tokens(PackedStringArray(["i", "n", ",", ".", "[", "]", "{", "}"]))


func _configure_checkpoint() -> void:
	if map_number == 42 and progress.fourth_boss_checkpoint:
		player.position = Vector2(8800, 560)
		checkpoint_active = true
		camera_locked = true
		camera_lock_position = Vector2(9040, 520)
	player.set_water_surface(map_config["water_surface"], map_config["starts_in_water"])
	player.water_state_changed.connect(_on_player_water_state_changed)


func _build_stage_boss_area() -> void:
	terrain.z_index = 24
	foreground_terrain = TerrainScript.new()
	foreground_terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE4_ATLAS,
		STAGE4_FOREGROUND_SOURCE_RECTS,
		PackedStringArray(ALL_TOKENS_NON_SOLID),
		PackedStringArray(),
		{}
	)
	foreground_terrain.z_index = 25
	add_child(foreground_terrain)
	water_layer = WaterLayerScript.new()
	water_layer.z_index = 30
	add_child(water_layer)
	water_layer.setup(terrain.world_size, map_config["water_surface"])
	if map_number == 42:
		_build_boss_area()


func _enemy_update_interval() -> int:
	return 1


func _recovery_fall_speed() -> float:
	return 3.75


func _spawn_enemy_death(effect_position: Vector2) -> void:
	get_node("/root/AudioManager").play_sfx("anim40")
	var effect: EnemyDeathEffect = EnemyDeathEffectScript.new()
	effect.frame_hold_ticks = 8
	effect.position = effect_position
	effect.z_index = 30
	add_child(effect)


func _build_entry_portal() -> void:
	super._build_entry_portal()
	portal_back.z_index = player.z_index - 2
	entry_player.z_index = player.z_index
	entry_effect.z_index = player.z_index - 1
	portal_front.z_index = 22


func _start_departure(direction: int = 0) -> void:
	super._start_departure(direction)
	departure_back.z_index = player.z_index - 2
	departure_player.z_index = player.z_index
	departure_front.z_index = 22


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
	_update_water_effects()
	_finish_physics_tick()


func _update_water_effects() -> void:
	for index in range(water_effects.size() - 1, -1, -1):
		if not is_instance_valid(water_effects[index]):
			water_effects.remove_at(index)
	if not player.gameplay_active:
		return
	if not player.in_water:
		bubble_ticks = 0
		return
	bubble_ticks += 1
	if bubble_ticks >= 160:
		bubble_ticks = 0
		var bubble: World4WaterBubble = WaterBubbleScript.new()
		bubble.position = player.position + Vector2(30.0 if player.facing > 0 else 4.0, 15.0)
		bubble.z_index = 21
		add_child(bubble)
		bubble.setup(map_config["water_surface"], player.facing)
		water_effects.append(bubble)


func _on_player_water_state_changed(_entered_water: bool) -> void:
	get_node("/root/AudioManager").play_sfx("splash")
	var splash: World4WaterSplash = WaterSplashScript.new()
	splash.position = Vector2(player.position.x - 4.0, float(map_config["water_surface"]) - 14.0)
	splash.z_index = 31
	add_child(splash)
	water_effects.append(splash)


func _update_playing() -> void:
	if map_number == 42 and player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(8720, 540, 30, 100), true):
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
	player.position.y = move_toward(player.position.y, 560.0, 10.0)
	if player.position.y == 560.0:
		player.y_speed = 0.0
		player.grounded = true
	if state_ticks <= 40:
		_set_door_opening(0, float(state_ticks) / 40.0)
		player.set_scripted_frame(0)
	elif state_ticks <= 120:
		_set_door_opening(0, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(9040, 520), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(0, 1.0 - float(state_ticks - 120) / 40.0)
		player.set_scripted_frame(0)
	else:
		_set_door_opening(0, 0.0)
		camera_lock_position = Vector2(9040, 520)
		progress.set_fourth_boss_checkpoint(true)
		stage_state = StageState.CHECKPOINT
		state_ticks = 0
		player.set_scripted_animation_active(false)
		_set_gameplay_active(true)


func _update_checkpoint() -> void:
	player.position.x = clampf(player.position.x, 8750.0, 9290.0)
	if player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(9330, 540, 30, 100), true):
		_begin_boss_entry()


func _update_boss_entry() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		_set_door_opening(1, float(state_ticks) / 40.0)
		player.set_scripted_frame(0)
	elif state_ticks <= 120:
		_set_door_opening(1, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(9650, 520), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(1, 1.0 - float(state_ticks - 120) / 40.0)
		player.set_scripted_frame(0)
	else:
		_set_door_opening(1, 0.0)
		camera_lock_position = Vector2(9650, 520)
		player.position.y = 560.0
		player.y_speed = 0.0
		player.grounded = true
		player.set_scripted_animation_active(false)
		stage_state = StageState.BOSS_INTRO
		state_ticks = 0
		boss.set_gameplay_active(true)
		boss.start_intro()


func _update_boss_intro() -> void:
	state_ticks += 1
	if state_ticks >= 44 and state_ticks <= 160 and state_ticks % 4 == 0:
		get_node("/root/AudioManager").play_sfx("recuperator")
	if state_ticks >= 164:
		stage_state = StageState.BOSS
		state_ticks = 0
		boss.start_fight()
		_set_gameplay_active(true)


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 9360.0, 9960.0)


func _on_boss_water_shot_requested(spawn_position: Vector2, direction: int, trailing: bool) -> void:
	get_node("/root/AudioManager").play_sfx("turtlejato")
	var shot: World4WaterShot = WaterShotScript.new()
	_spawn_enemy(shot, spawn_position)
	shot.z_index = 9
	shot.configure(direction, trailing)
	shot.set_gameplay_active(true)


func _on_boss_defeated() -> void:
	boss_reward_position = boss.position + boss.body_size * 0.5 - Vector2(11, 18)
	enemies.erase(boss)
	for index in range(enemies.size() - 1, -1, -1):
		var enemy := enemies[index]
		if is_instance_valid(enemy) and enemy is World4WaterShot:
			enemies.remove_at(index)
			enemy.hide()
			enemy.queue_free()
	stage_state = StageState.VICTORY
	state_ticks = 0
	_set_gameplay_active(false)
	player.immunity_ticks = 0
	hud.set_boss_health(0, false)
	boss_reward_started = false
	boss_reward_homing = false
	hud.set_boss_flash(0.0)


func _update_victory() -> void:
	if boss_landing_pending:
		_update_boss_landing()
		return
	if departure_ticks > 0:
		_update_departure()
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 24:
				_spawn_boss_light_flashes(boss.position + Vector2(55, 30))
			for _explosion in range(preload("res://scripts/shared/boss_explosion_timing.gd").due_count(self, state_ticks) if is_instance_valid(boss) else 0):
				_spawn_boss_explosion(boss.position + Vector2(randi_range(0, 127) - 6, randi_range(0, 59) - 6))
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
				_begin_boss_landing()


func _spawn_boss_reward() -> void:
	boss_reward_started = true
	if _is_active_rematch():
		return
	boss_reward = FourthBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = water_layer.z_index - 1
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(3)
	progress.unlock_fourth_boss_reward()
	_begin_boss_landing()


func _complete_departure() -> void:
	progress.set_fourth_boss_checkpoint(false)
	if get_tree().current_scene == self:
		_finish_elemental_or_rematch(4)


func _spawn_stage_objects() -> void:
	for spawn_position in map_config["resettis"]:
		var resetti: World4Resetti = ResettiScript.new()
		_spawn_enemy(resetti, spawn_position)
		resetti.configure()
	for spawn_position in map_config["seahorse_spawners"]:
		var spawner: World4SeahorseSpawner = SeahorseSpawnerScript.new()
		spawner.position = spawn_position
		add_child(spawner)
		spawner.setup(player)
		spawner.spawn_requested.connect(_on_seahorse_requested)
		seahorse_spawners.append(spawner)
	for spawn_position in map_config["fish"]:
		var fish: World4Fish = FishScript.new()
		_spawn_enemy(fish, spawn_position)
		fish.configure(map_config["water_surface"])
	for data in map_config["oysters"]:
		var lower: World4OysterLower = OysterLowerScript.new()
		_spawn_enemy(lower, data[0])
		lower.configure(data[2])
		var upper: World4Oyster = OysterScript.new()
		_spawn_enemy(upper, data[1])
		upper.configure(data[2])
		upper.pearl_requested.connect(_on_oyster_pearl_requested)
	for data in map_config["cards"]:
		if not progress.has_card(data[1]):
			_spawn_card(data[0], data[1], data[2])
	for data in map_config["sand_mounds"]:
		var mound: World4SandMound = SandMoundScript.new()
		mound.position = data[0]
		mound.z_index = 10
		add_child(mound)
		mound.configure(data[1])
		mound.opened.connect(_on_sand_mound_opened)
		sand_mounds.append(mound)


func _on_seahorse_requested(spawn_position: Vector2) -> void:
	var seahorse: World4Seahorse = SeahorseScript.new()
	_spawn_enemy(seahorse, spawn_position)
	seahorse.configure(map_config["water_surface"])
	seahorse.set_gameplay_active(true)


func _on_oyster_pearl_requested(spawn_position: Vector2, shot_direction: int) -> void:
	var pearl: World4OysterPearl = OysterPearlScript.new()
	pearl.position = spawn_position
	pearl.z_index = 9
	add_child(pearl)
	pearl.setup(terrain, player, shot_direction)
	pearl.set_gameplay_active(true)
	oyster_pearls.append(pearl)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: World4CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)
	cards.append(card)


func _on_sand_mound_opened(spawn_position: Vector2, card_id: int) -> void:
	if not progress.has_card(card_id):
		_spawn_card(spawn_position, card_id, true)


func _damage_stage_object_in_rect(rect: Rect2, damage: int, weapon_id: int = 1) -> bool:
	if weapon_id != 2:
		return false
	for mound in sand_mounds:
		if is_instance_valid(mound) and mound.projectile_mask_overlap(rect):
			var hit_from_right := rect.get_center().x > mound.position.x + World4SandMound.BODY_SIZE.x * 0.5
			mound.take_projectile_hit(damage, -1 if hit_from_right else 1)
			return true
	return false


func _set_gameplay_active(value: bool) -> void:
	super._set_gameplay_active(value)
	for mound in sand_mounds:
		if is_instance_valid(mound):
			mound.set_gameplay_active(value)
	for spawner in seahorse_spawners:
		if is_instance_valid(spawner):
			spawner.set_gameplay_active(value)
	for pearl in oyster_pearls:
		if is_instance_valid(pearl):
			pearl.set_gameplay_active(value)
	for effect in water_effects:
		if is_instance_valid(effect) and effect.has_method("set_gameplay_active"):
			effect.set_gameplay_active(value)


func _before_player_death() -> void:
	boss_health_was_visible_on_death = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO


func _build_boss_area() -> void:
	var door_texture: Texture2D = preload("res://assets/world4/door.png")
	for door_position in [Vector2(8720, 540), Vector2(9330, 540)]:
		var door := Sprite2D.new()
		door.centered = false
		door.texture = door_texture
		door.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		door.position = door_position
		door.z_index = 9
		add_child(door)
		boss_doors.append(door)
	boss = FourthBossScript.new()
	_spawn_enemy(boss, Vector2(9770, 570))
	boss.water_shot_requested.connect(_on_boss_water_shot_requested)
	boss.boss_defeated.connect(_on_boss_defeated)


func _set_door_opening(index: int, amount: float) -> void:
	if index < 0 or index >= boss_doors.size():
		return
	_set_retracting_door_opening(index, amount)


func _build_background() -> void:
	var backdrop := ColorRect.new()
	backdrop.position = Vector2(-1000, -1000)
	backdrop.size = Vector2(12000, 3000)
	backdrop.color = Color8(0, 0, 161)
	backdrop.z_index = -30
	add_child(backdrop)
	for index in range(6):
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = STAGE4_BACKGROUND
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		sprite.z_index = -20
		add_child(sprite)
		background_sprites.append(sprite)
	background_sprite = background_sprites[0]


func _update_background() -> void:
	if not is_instance_valid(background_sprite) or not is_instance_valid(camera):
		return
	var viewport_top_left := camera.position - VIEWPORT_HALF_SIZE
	var sampled_x := viewport_top_left.x / 5.0
	var world_offset_x := viewport_top_left.x - sampled_x
	var texture_width := background_sprite.texture.get_width()
	var rows: Array = map_config["background_rows"]
	for index in range(background_sprites.size()):
		var row_index := int(index / 3.0)
		background_sprites[index].visible = row_index < rows.size()
		if row_index < rows.size():
			var row_offset := -100.0 if map_number == 40 and row_index == 0 else 0.0
			var source_x := floorf((sampled_x - row_offset) / texture_width) * texture_width + row_offset
			background_sprites[index].position = Vector2(
				world_offset_x + source_x + (index % 3) * texture_width,
				rows[row_index]
			)


func _update_camera() -> void:
	if not is_instance_valid(camera) or not is_instance_valid(player):
		return
	if camera_locked:
		camera.position = camera_lock_position
		_update_background()
		return
	var center := player.get_center()
	var right_limit := terrain.world_size.x
	if map_number == 42 and not checkpoint_active:
		right_limit = 8750.0
	camera.position = Vector2(
		clampf(center.x, VIEWPORT_HALF_SIZE.x, right_limit - VIEWPORT_HALF_SIZE.x),
		clampf(center.y, VIEWPORT_HALF_SIZE.y, terrain.world_size.y - VIEWPORT_HALF_SIZE.y)
	)
	_update_background()


func _update_boss_hud() -> void:
	var boss_visible := false
	var displayed_boss_hp := 0
	if is_instance_valid(boss):
		boss_visible = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO or (stage_state == StageState.DYING and boss_health_was_visible_on_death)
		displayed_boss_hp = boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_boss_hp = clampi(int((state_ticks - 40) / 4.0), 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)


func _stage_complete_message() -> String:
	return "FOURTH STAGE COMPLETE\n\nPRESS R TO REPLAY"
