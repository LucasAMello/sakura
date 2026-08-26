extends Node2D

const TerrainScript = preload("res://scripts/shared/terrain.gd")
const PlayerScript = preload("res://scripts/player/player.gd")
const GhostScript = preload("res://scripts/world2/ghost.gd")
const GhostMaskScript = preload("res://scripts/world2/ghost_mask.gd")
const ShadowSpikeScript = preload("res://scripts/world2/shadow_spike.gd")
const PaintingScript = preload("res://scripts/world2/stage2_painting.gd")
const ArmorScript = preload("res://scripts/world2/stage2_armor.gd")
const CardPickupScript = preload("res://scripts/world2/card_pickup.gd")
const ProjectileScript = preload("res://scripts/player/projectile.gd")
const RecoveryScript = preload("res://scripts/shared/recovery.gd")
const HUDScript = preload("res://scripts/hud/hud.gd")
const SecondBossScript = preload("res://scripts/world2/second_boss.gd")
const ShadowCloneScript = preload("res://scripts/world2/shadow_clone.gd")
const SecondBossRewardScript = preload("res://scripts/world2/second_boss_reward.gd")
const PlayerDeathEffectScript = preload("res://scripts/player/death_effect.gd")
const EnemyDeathEffectScript = preload("res://scripts/shared/enemy_death_effect.gd")

const VIEWPORT_HALF_SIZE := Vector2(320, 240)
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

enum StageState { ENTRY, PLAYING, EXITING, COMPLETE, DYING, CHECKPOINT_ENTRY, CHECKPOINT, BOSS_ENTRY, BOSS_INTRO, BOSS, VICTORY }

@export var map_number := 21

var map_config: Dictionary
var progress: Variant
var terrain: SakuraTerrain
var player: SakuraPlayer
var camera: Camera2D
var hud: SakuraHUD
var enemies: Array[SakuraEnemy] = []
var mask_spawners: Array[Dictionary] = []
var stage_state := StageState.ENTRY
var state_ticks := 0
var portal_back: Sprite2D
var portal_front: Sprite2D
var entry_effect: Sprite2D
var entry_player: Sprite2D
var background_sprite: Sprite2D
var background_sprites: Array[Sprite2D] = []
var checkpoint_active := false
var boss_room_active := false
var camera_locked := false
var camera_lock_position := Vector2.ZERO
var transition_camera_start := Vector2.ZERO
var boss_doors: Array[Sprite2D] = []
var boss: SecondStageBoss
var boss_reward: SecondBossReward
var boss_reward_position := Vector2.ZERO
var boss_reward_started := false
var boss_reward_homing := false
var defeated_clone_positions: Array[Vector2] = []
var departure_ticks := 0
var departure_back: Sprite2D
var departure_front: Sprite2D
var world2_tick_phase := 0


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS
	randomize()
	progress = get_node("/root/SakuraProgress")
	_install_input_actions()
	map_config = MAP_CONFIGS[map_number]
	_build_background()
	terrain = TerrainScript.new()
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE2_ATLAS,
		STAGE2_SOURCE_RECTS,
		PackedStringArray(STAGE2_NON_SOLID),
		PackedStringArray()
	)
	terrain.z_index = 0
	add_child(terrain)
	player = PlayerScript.new()
	player.name = "Player"
	player.position = map_config["start"]
	if map_number == 23 and progress.second_boss_checkpoint:
		player.position = Vector2(4840, 460)
		checkpoint_active = true
		camera_locked = true
		camera_lock_position = Vector2(5020, 380)
	player.z_index = 20
	add_child(player)
	player.setup(terrain)
	player.hp = progress.take_hp(SakuraPlayer.MAX_HP)
	player.lives = progress.lives
	player.set_presentation_hidden(true)
	player.shot_requested.connect(_on_shot_requested)
	player.died.connect(_on_player_died)
	_spawn_stage_objects()
	_build_entry_portal()
	if map_number == 23:
		_build_boss_area()
	_build_camera()
	hud = HUDScript.new()
	add_child(hud)
	hud.set_ready_visible(_entry_should_show_ready())
	_set_gameplay_active(false)


func _physics_process(_delta: float) -> void:
	if Input.is_action_just_pressed("pause") and stage_state != StageState.DYING:
		_set_paused(not get_tree().paused)
		return
	if get_tree().paused:
		if Input.is_action_just_pressed("restart"):
			_set_paused(false)
			get_tree().reload_current_scene()
		elif Input.is_action_just_pressed("quit"):
			get_tree().quit()
		return
	if Input.is_action_just_pressed("quit"):
		get_tree().quit()
	if Input.is_action_just_pressed("restart"):
		get_tree().reload_current_scene()
		return
	if Input.is_action_just_pressed("toggle_debug"):
		hud.toggle_debug()
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
			if world2_logic_tick:
				_update_victory()
	if world2_logic_tick and (stage_state == StageState.PLAYING or stage_state == StageState.CHECKPOINT):
		_update_mask_spawners()
	_prune_enemies()
	_update_camera()
	_update_hud()


func _update_entry() -> void:
	state_ticks += 1
	_update_entry_visual()
	hud.set_ready_visible(_entry_should_show_ready() and state_ticks > 5 and state_ticks < 128)
	if state_ticks >= 130:
		portal_back.visible = false
		portal_front.visible = false
		entry_effect.visible = false
		entry_player.visible = false
		player.set_presentation_hidden(false)
		hud.set_ready_visible(false)
		stage_state = StageState.CHECKPOINT if checkpoint_active else StageState.PLAYING
		state_ticks = 0
		_set_gameplay_active(true)


func _update_playing() -> void:
	if map_number == 23:
		if player.facing > 0 and player.grounded and player.get_hit_rect().intersects(Rect2(4700, 440, 30, 100)):
			_begin_checkpoint_entry()
		return
	if player.grounded and player.get_hit_rect().intersects(map_config["exit"]):
		stage_state = StageState.EXITING
		state_ticks = 0
		_set_gameplay_active(false)
		player.set_scripted_animation_active(true)


func _update_exit() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		player.scripted_step_right(2.0)
		return
	var next_map: int = map_config["next"]
	stage_state = StageState.COMPLETE
	progress.store_hp(player.hp)
	get_tree().change_scene_to_file("res://scenes/map%d.tscn" % next_map)


func _update_death() -> void:
	state_ticks += 1
	if state_ticks >= 100:
		get_tree().reload_current_scene()


func _begin_checkpoint_entry() -> void:
	stage_state = StageState.CHECKPOINT_ENTRY
	state_ticks = 0
	checkpoint_active = true
	camera_locked = true
	transition_camera_start = camera.position
	camera_lock_position = transition_camera_start
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _update_checkpoint_entry() -> void:
	state_ticks += 1
	if state_ticks <= 20:
		_set_door_opening(0, float(state_ticks) / 20.0)
	elif state_ticks <= 60:
		_set_door_opening(0, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(5020, 380), float(state_ticks - 20) / 40.0)
	elif state_ticks <= 80:
		_set_door_opening(0, 1.0 - float(state_ticks - 60) / 20.0)
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
	if player.facing > 0 and player.get_hit_rect().intersects(Rect2(5310, 440, 30, 100), true):
		_begin_boss_entry()


func _begin_boss_entry() -> void:
	stage_state = StageState.BOSS_ENTRY
	state_ticks = 0
	boss_room_active = true
	camera_locked = true
	transition_camera_start = camera.position
	camera_lock_position = transition_camera_start
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _update_boss_entry() -> void:
	state_ticks += 1
	if state_ticks <= 20:
		_set_door_opening(1, float(state_ticks) / 20.0)
	elif state_ticks <= 60:
		_set_door_opening(1, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(5640, 380), float(state_ticks - 20) / 40.0)
	elif state_ticks <= 80:
		_set_door_opening(1, 1.0 - float(state_ticks - 60) / 20.0)
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
			clone.queue_free()
	stage_state = StageState.VICTORY
	state_ticks = 0
	_set_gameplay_active(false)
	player.immunity_ticks = 0
	hud.set_boss_health(0, false)
	boss_reward_started = false
	boss_reward_homing = false
	hud.set_boss_flash(0.0)


func _update_victory() -> void:
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 5:
				for burst in range(3):
					_spawn_enemy_death(boss.position + Vector2(25, 25))
					for clone_position in defeated_clone_positions:
						_spawn_enemy_death(clone_position + Vector2(25, 25))
			if state_ticks % 7 == 3 and is_instance_valid(boss):
				_spawn_enemy_death(boss.position + Vector2(randi_range(0, 50), randi_range(0, 50)))
			if state_ticks % 7 == 6:
				for clone_position in defeated_clone_positions:
					_spawn_enemy_death(clone_position + Vector2(randi_range(0, 46), randi_range(0, 46)))
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
	if departure_ticks > 0:
		_update_departure()


func _spawn_boss_reward() -> void:
	boss_reward_started = true
	boss_reward = SecondBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(1)
	progress.unlock_second_boss_reward()
	departure_ticks = 1
	departure_back = Sprite2D.new()
	departure_back.centered = false
	departure_back.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	departure_back.z_index = 18
	departure_back.visible = false
	add_child(departure_back)
	departure_front = Sprite2D.new()
	departure_front.centered = false
	departure_front.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	departure_front.z_index = 22
	add_child(departure_front)


func _update_departure() -> void:
	departure_ticks += 1
	if departure_ticks < 16:
		_set_departure_frame(preload("res://assets/player/portal_3.png"), Vector2(45, 34))
	elif departure_ticks < 24:
		_set_departure_frame(preload("res://assets/player/portal_4.png"), Vector2(39, 32))
	elif departure_ticks < 32:
		_set_departure_frame(preload("res://assets/player/portal_5.png"), Vector2(34, 23))
	elif departure_ticks < 40:
		_set_departure_frame(preload("res://assets/player/portal_6.png"), Vector2(28, 3), true)
	elif departure_ticks < 87:
		departure_back.visible = true
		departure_front.visible = true
		departure_back.texture = preload("res://assets/player/portal_1.png")
		departure_front.texture = preload("res://assets/player/portal_2.png")
		departure_back.position = player.position + Vector2(17, -20)
		departure_front.position = departure_back.position
		departure_back.flip_h = true
		departure_front.flip_h = true
		if departure_ticks >= 47:
			player.visible = false
	elif departure_ticks < 95:
		_set_departure_frame(preload("res://assets/player/portal_6.png"), Vector2(28, 3), true)
	elif departure_ticks < 103:
		_set_departure_frame(preload("res://assets/player/portal_5.png"), Vector2(34, 23))
	elif departure_ticks < 111:
		_set_departure_frame(preload("res://assets/player/portal_4.png"), Vector2(39, 32))
	elif departure_ticks < 119:
		_set_departure_frame(preload("res://assets/player/portal_3.png"), Vector2(45, 34))
	elif departure_ticks < 136:
		departure_front.visible = false
		departure_back.visible = false
		hud.set_completion_fade(float(departure_ticks - 119) / 16.0)
	else:
		stage_state = StageState.COMPLETE
		progress.set_second_boss_checkpoint(false)
		hud.set_completion_fade(1.0)
		if get_tree().current_scene == self:
			progress.store_hp(player.hp)
			get_tree().change_scene_to_file("res://scenes/map30.tscn")


func _set_departure_frame(texture: Texture2D, offset: Vector2, flipped: bool = false) -> void:
	departure_back.visible = false
	departure_front.visible = true
	departure_front.texture = texture
	departure_front.position = player.position + offset
	departure_front.flip_h = flipped


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
		if data["timer"] >= randi_range(41, 50):
			var mask: GhostMaskEnemy = GhostMaskScript.new()
			var spawn_position: Vector2 = data["position"] + Vector2(0, randi_range(0, int(data["span"]) - 1))
			_spawn_enemy(mask, spawn_position)
			mask.configure(data["direction"], data["stop_x"])
			mask.set_gameplay_active(true)
			data["timer"] = 0
		mask_spawners[index] = data


func _spawn_enemy(enemy: SakuraEnemy, spawn_position: Vector2) -> void:
	enemy.position = spawn_position
	enemy.z_index = 10
	add_child(enemy)
	enemy.setup(terrain, player)
	enemy.set_update_interval(2)
	_register_enemy(enemy)


func _register_enemy(enemy: SakuraEnemy) -> void:
	enemies.append(enemy)
	enemy.defeated.connect(_on_enemy_defeated)


func _on_enemy_defeated(enemy: SakuraEnemy, effect_position: Vector2, _drop_position: Vector2, drop_type: int) -> void:
	enemies.erase(enemy)
	_spawn_enemy_death(effect_position)
	if drop_type != SakuraEnemy.DropType.NONE:
		var recovery: RecoveryPickup = RecoveryScript.new()
		recovery.z_index = 12
		add_child(recovery)
		recovery.setup(terrain, player, drop_type)
		recovery.position = enemy.position + (enemy.body_size - recovery.body_size) * 0.5


func _on_armor_opened(drop_position: Vector2, card_id: int) -> void:
	if card_id == 0:
		_spawn_recovery(drop_position, SakuraEnemy.DropType.SMALL)
	elif not progress.has_card(card_id):
		_spawn_card(drop_position, card_id, true)


func _spawn_recovery(spawn_position: Vector2, drop_type: int) -> void:
	var recovery: RecoveryPickup = RecoveryScript.new()
	recovery.position = spawn_position
	recovery.z_index = 12
	add_child(recovery)
	recovery.setup(terrain, player, drop_type)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)


func _on_shot_requested(origin: Vector2, direction: int) -> void:
	var projectile: DefaultProjectile = ProjectileScript.new()
	projectile.position = origin
	projectile.z_index = 15
	add_child(projectile)
	projectile.setup(terrain, player, self, direction)
	projectile.finished.connect(player.projectile_ended, CONNECT_ONE_SHOT)


func damage_enemy_in_rect(rect: Rect2, damage: int) -> bool:
	for enemy in enemies:
		if is_instance_valid(enemy) and not enemy.defeated_state and enemy.projectile_mask_overlap(rect):
			enemy.take_projectile_hit(damage)
			return true
	return false


func _on_player_died() -> void:
	stage_state = StageState.DYING
	state_ticks = 0
	_set_gameplay_active(false)
	hud.set_ready_visible(false)
	var effect: PlayerDeathEffect = PlayerDeathEffectScript.new()
	effect.position = player.get_center()
	effect.z_index = 30
	add_child(effect)


func _spawn_enemy_death(effect_position: Vector2) -> void:
	var effect: EnemyDeathEffect = EnemyDeathEffectScript.new()
	effect.position = effect_position
	effect.z_index = 30
	add_child(effect)


func _prune_enemies() -> void:
	for index in range(enemies.size() - 1, -1, -1):
		if not is_instance_valid(enemies[index]):
			enemies.remove_at(index)


func _set_gameplay_active(value: bool) -> void:
	player.set_gameplay_active(value)
	for enemy in enemies:
		if is_instance_valid(enemy):
			enemy.set_gameplay_active(value)


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


func _build_entry_portal() -> void:
	portal_back = Sprite2D.new()
	portal_back.centered = false
	portal_back.texture = preload("res://assets/player/portal_1.png")
	portal_back.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	portal_back.z_index = 18
	portal_back.visible = false
	add_child(portal_back)
	portal_front = Sprite2D.new()
	portal_front.centered = false
	portal_front.texture = preload("res://assets/player/portal_2.png")
	portal_front.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	portal_front.z_index = 22
	portal_front.visible = false
	add_child(portal_front)
	entry_effect = Sprite2D.new()
	entry_effect.centered = false
	entry_effect.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	entry_effect.z_index = 21
	entry_effect.visible = false
	add_child(entry_effect)
	entry_player = Sprite2D.new()
	entry_player.centered = false
	entry_player.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	entry_player.z_index = 21
	entry_player.visible = false
	add_child(entry_player)


func _update_entry_visual() -> void:
	portal_back.visible = false
	portal_front.visible = false
	entry_effect.visible = false
	entry_effect.region_enabled = false
	entry_player.visible = false
	entry_player.region_enabled = false
	var has_portal := map_number == 20 or checkpoint_active
	if state_ticks >= 16 and state_ticks <= 23 and has_portal:
		_set_entry_effect(preload("res://assets/player/portal_3.png"), Vector2(-5, 34))
	elif state_ticks >= 24 and state_ticks <= 30 and has_portal:
		_set_entry_effect(preload("res://assets/player/portal_4.png"), Vector2(-11, 32))
	elif state_ticks >= 31 and state_ticks <= 38 and has_portal:
		_set_entry_effect(preload("res://assets/player/portal_5.png"), Vector2(-16, 23))
	elif state_ticks >= 39 and state_ticks <= 46 and has_portal:
		_set_entry_effect(preload("res://assets/player/portal_6.png"), Vector2(-22, 3))
	elif state_ticks >= 47 and state_ticks <= 86:
		_set_entry_player(_entry_player_frame(), true)
		if has_portal:
			_show_entry_portal()
	elif state_ticks >= 87 and state_ticks <= 94:
		_set_entry_player(0, false)
		if has_portal:
			_show_entry_portal()
	elif state_ticks >= 95 and state_ticks <= 102:
		_set_entry_player(0, false)
		if has_portal:
			_set_entry_effect(preload("res://assets/player/portal_6.png"), Vector2(-22, 3))
	elif state_ticks >= 103 and state_ticks <= 110:
		_set_entry_player(0, false)
		if has_portal:
			_set_entry_effect(preload("res://assets/player/portal_5.png"), Vector2(-16, 23))
	elif state_ticks >= 111 and state_ticks <= 118:
		_set_entry_player(0, false)
		if has_portal:
			_set_entry_effect(preload("res://assets/player/portal_4.png"), Vector2(-11, 32))
	elif state_ticks >= 119 and state_ticks <= 129:
		_set_entry_player(0, false)
		if has_portal:
			_set_entry_effect(preload("res://assets/player/portal_3.png"), Vector2(-5, 34))


func _entry_player_frame() -> int:
	var sequence := [1, 2, 1, 0, 3, 4, 3]
	return sequence[mini(int((state_ticks - 47) / 6.0), sequence.size() - 1)]


func _entry_should_show_ready() -> bool:
	return map_number == 20 or checkpoint_active


func _set_entry_player(frame_index: int, revealing: bool) -> void:
	entry_player.visible = true
	entry_player.texture = SakuraPlayer.NORMAL_TEXTURES[frame_index]
	entry_player.position = player.position
	if revealing:
		var reveal_step := state_ticks - 46
		var source_x := maxi(0, 40 - reveal_step)
		var reveal_width := mini(entry_player.texture.get_width() - source_x, reveal_step * 2)
		entry_player.region_enabled = true
		entry_player.region_rect = Rect2(source_x, 0, reveal_width, 80)


func _show_entry_portal() -> void:
	portal_back.position = player.position + Vector2(-33, -20)
	portal_front.position = portal_back.position
	portal_back.visible = true
	portal_front.visible = true


func _set_entry_effect(texture: Texture2D, offset: Vector2) -> void:
	entry_effect.visible = true
	entry_effect.texture = texture
	entry_effect.position = player.position + offset


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


func _build_camera() -> void:
	camera = Camera2D.new()
	camera.enabled = true
	camera.position_smoothing_enabled = false
	camera.limit_left = 0
	camera.limit_top = 0
	camera.limit_right = int(terrain.world_size.x)
	camera.limit_bottom = int(terrain.world_size.y)
	add_child(camera)
	_update_camera()


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


func _update_hud() -> void:
	var label := "ENTRY"
	match stage_state:
		StageState.PLAYING:
			label = "PLAY"
		StageState.EXITING:
			label = "EXIT"
		StageState.COMPLETE:
			label = "COMPLETE"
		StageState.DYING:
			label = "DEFEATED"
		StageState.CHECKPOINT_ENTRY:
			label = "CHECKPOINT ENTRY"
		StageState.CHECKPOINT:
			label = "CHECKPOINT"
		StageState.BOSS_ENTRY:
			label = "BOSS ENTRY"
		StageState.BOSS_INTRO:
			label = "BOSS INTRO"
		StageState.BOSS:
			label = "BOSS"
		StageState.VICTORY:
			label = "VICTORY"
	hud.update_status(player, label, enemies.size(), map_number, terrain.world_size)
	var boss_visible := false
	var displayed_boss_hp := 0
	if is_instance_valid(boss):
		boss_visible = stage_state == StageState.BOSS or (stage_state == StageState.BOSS_INTRO and boss.state == SecondStageBoss.BossState.METER_FILL)
		displayed_boss_hp = boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_boss_hp = clampi(boss.intro_meter_ticks, 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)


func _set_paused(value: bool) -> void:
	get_tree().paused = value
	hud.set_paused(value)


func _install_input_actions() -> void:
	_bind_key("move_left", KEY_LEFT)
	_bind_key("move_right", KEY_RIGHT)
	_bind_key("jump", KEY_F)
	_bind_key("fire", KEY_D)
	_bind_key("pause", KEY_ENTER)
	_bind_key("restart", KEY_R)
	_bind_key("toggle_debug", KEY_F3)
	_bind_key("quit", KEY_ESCAPE)


func _bind_key(action: StringName, key: Key) -> void:
	if not InputMap.has_action(action):
		InputMap.add_action(action)
	var event := InputEventKey.new()
	event.physical_keycode = key
	if not InputMap.action_has_event(action, event):
		InputMap.action_add_event(action, event)
