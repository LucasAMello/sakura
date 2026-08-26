extends Node2D

const TerrainScript = preload("res://scripts/shared/terrain.gd")
const PlayerScript = preload("res://scripts/player/player.gd")
const WallTurretScript = preload("res://scripts/world3/wall_turret.gd")
const MachineScript = preload("res://scripts/world3/machine.gd")
const OrangeScript = preload("res://scripts/world3/orange_enemy.gd")
const ShockerScript = preload("res://scripts/world3/shocker.gd")
const CardHolderScript = preload("res://scripts/world3/card_holder.gd")
const CardPickupScript = preload("res://scripts/world3/card_pickup.gd")
const ProjectileScript = preload("res://scripts/player/projectile.gd")
const RecoveryScript = preload("res://scripts/shared/recovery.gd")
const HUDScript = preload("res://scripts/hud/hud.gd")
const ThirdBossScript = preload("res://scripts/world3/third_boss.gd")
const ThirdBossRewardScript = preload("res://scripts/world3/third_boss_reward.gd")
const MachineDeathEffectScript = preload("res://scripts/world3/machine_death_effect.gd")
const PlayerDeathEffectScript = preload("res://scripts/player/death_effect.gd")
const EnemyDeathEffectScript = preload("res://scripts/shared/enemy_death_effect.gd")

const VIEWPORT_HALF_SIZE := Vector2(320, 240)
const STAGE3_ATLAS := preload("res://assets/world3/terrain.png")
const STAGE3_SOURCE_RECTS := {
	"2": Vector2i(0, 0), "3": Vector2i(20, 0), "4": Vector2i(40, 0),
	"5": Vector2i(60, 0), "6": Vector2i(80, 0), "7": Vector2i(20, 20),
	"8": Vector2i(40, 20), "9": Vector2i(60, 20), "a": Vector2i(0, 40),
	"b": Vector2i(20, 40), "c": Vector2i(0, 60), "d": Vector2i(20, 60),
	"e": Vector2i(40, 40), "f": Vector2i(60, 40), "g": Vector2i(40, 60),
	"h": Vector2i(60, 60), "i": Vector2i(80, 40), "j": Vector2i(100, 40),
	"k": Vector2i(80, 60), "l": Vector2i(100, 60), "m": Vector2i(100, 80),
	"n": Vector2i(120, 80), "o": Vector2i(100, 100), "p": Vector2i(120, 100),
	"q": Vector2i(120, 0), "r": Vector2i(120, 20), "s": Vector2i(120, 40),
	"t": Vector2i(100, 20), "u": Vector2i(100, 0), "v": Vector2i(0, 80),
	"w": Vector2i(0, 100), "x": Vector2i(20, 80), "y": Vector2i(20, 100),
	"z": Vector2i(0, 20), "/": Vector2i(80, 20), "!": Vector2i(40, 80),
	"@": Vector2i(60, 80), "#": Vector2i(80, 80), "$": Vector2i(40, 100),
	"%": Vector2i(60, 100), "*": Vector2i(80, 100), "+": Vector2i(120, 60),
	"<": Vector2i(0, 120), ">": Vector2i(20, 120), ":": Vector2i(40, 120),
	"-": Vector2i(60, 120), "_": Vector2i(80, 120),
}
const STAGE3_NON_SOLID := ["0", "1"]

const MAP_CONFIGS := {
	30: {
		"width": 500, "height": 30, "start": Vector2(60, 400),
		"exit": Rect2(9960, 220, 80, 200), "next": 31,
		"wall_turrets": [[Vector2(900, 260), 0, 5], [Vector2(1380, 100), 0, 10], [Vector2(1480, 340), 1, 0], [Vector2(4080, 300), 1, 0], [Vector2(4260, 300), 2, 0], [Vector2(6740, 340), 1, 0]],
		"machines": [Vector2(4580, 450), Vector2(5620, 310), Vector2(8760, 370)],
		"oranges": [[Vector2(2770, 260), 0], [Vector2(6200, 140), 0], [Vector2(7150, 280), 0], [Vector2(7670, 240), 0], [Vector2(5140, 210), 0]],
		"shockers": [[Vector2(3180, 116), 0, 0], [Vector2(3330, 356), 2, 0], [Vector2(4716, 260), 3, 0], [Vector2(5760, 56), 0, 0], [Vector2(9160, 196), 0, 0], [Vector2(9360, 336), 2, 0]],
		"cards": [[Vector2(2230, 310), false, 25], [Vector2(6300, 260), false, 21]],
		"holder": [Vector2(8540, 100), 38],
	},
	31: {
		"width": 100, "height": 80, "start": Vector2(0, 140),
		"exit": Rect2(1960, 140, 80, 200), "next": 32,
		"wall_turrets": [[Vector2(820, 280), 2, 0], [Vector2(240, 380), 0, 0], [Vector2(430, 380), 0, 15], [Vector2(620, 380), 0, 0], [Vector2(720, 920), 1, 0], [Vector2(880, 1340), 0, 0]],
		"machines": [Vector2(560, 150), Vector2(930, 1470), Vector2(1740, 490), Vector2(1840, 230)],
		"oranges": [[Vector2(1660, 1200), 0], [Vector2(1240, 1000), 0], [Vector2(1240, 220), 0]],
		"shockers": [[Vector2(110, 796), 2, -10], [Vector2(876, 680), 1, 0], [Vector2(876, 780), 1, -10], [Vector2(216, 1100), 3, 0], [Vector2(216, 1180), 3, -12], [Vector2(216, 1260), 3, -24], [Vector2(436, 1140), 1, -6], [Vector2(436, 1220), 1, -18], [Vector2(110, 1316), 0, -24], [Vector2(170, 1316), 0, -44], [Vector2(1276, 820), 3, 0], [Vector2(1696, 920), 3, 0]],
		"cards": [[Vector2(80, 1480), false, 6], [Vector2(1760, 400), false, 17]],
		"holder": [],
	},
	32: {
		"width": 300, "height": 32, "start": Vector2(0, 320),
		"exit": Rect2(),
		"next": 0,
		"wall_turrets": [[Vector2(1110, 240), 0, 0], [Vector2(1350, 240), 0, 0], [Vector2(1590, 240), 0, 15], [Vector2(3760, 300), 1, 0], [Vector2(3760, 380), 1, 20], [Vector2(3760, 460), 1, 10]],
		"machines": [Vector2(1000, 450), Vector2(3260, 290), Vector2(4600, 410)],
		"oranges": [[Vector2(2160, 140), 0], [Vector2(3140, 100), 0]],
		"shockers": [[Vector2(1111, 556), 2, -10], [Vector2(1351, 556), 2, -50], [Vector2(1591, 556), 2, -20], [Vector2(1232, 156), 0, -40], [Vector2(1472, 156), 0, 0], [Vector2(1712, 156), 0, -30]],
		"cards": [[Vector2(4020, 220), false, 26], [Vector2(1520, 360), false, 48]],
		"holder": [],
	},
}

enum StageState { ENTRY, PLAYING, EXITING, COMPLETE, DYING, CHECKPOINT_ENTRY, CHECKPOINT, BOSS_ENTRY, BOSS_INTRO, BOSS, VICTORY }

@export var map_number := 30

var map_config: Dictionary
var progress: Variant
var terrain: SakuraTerrain
var player: SakuraPlayer
var camera: Camera2D
var hud: SakuraHUD
var enemies: Array[SakuraEnemy] = []
var stage_state := StageState.ENTRY
var state_ticks := 0
var portal_back: Sprite2D
var portal_front: Sprite2D
var entry_effect: Sprite2D
var entry_player: Sprite2D
var background_sprite: Sprite2D
var background_sprites: Array[Sprite2D] = []
var card_holder: World3CardHolder
var checkpoint_active := false
var boss_room_active := false
var camera_locked := false
var camera_lock_position := Vector2.ZERO
var transition_camera_start := Vector2.ZERO
var boss_doors: Array[Sprite2D] = []
var boss: ThirdStageBoss
var boss_reward: ThirdBossReward
var boss_reward_position := Vector2.ZERO
var boss_reward_started := false
var boss_reward_homing := false
var departure_ticks := 0
var departure_back: Sprite2D
var departure_front: Sprite2D
var boss_health_was_visible_on_death := false


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
		STAGE3_ATLAS,
		STAGE3_SOURCE_RECTS,
		PackedStringArray(STAGE3_NON_SOLID),
		PackedStringArray(),
		{"+": Vector2(1, 20)}
	)
	terrain.z_index = 0
	add_child(terrain)
	player = PlayerScript.new()
	player.name = "Player"
	player.position = map_config["start"]
	if map_number == 32 and progress.third_boss_checkpoint:
		player.position = Vector2(4840, 400)
		checkpoint_active = true
		camera_locked = true
		camera_lock_position = Vector2(5040, 400)
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
	if map_number == 32:
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
	if map_number == 32:
		if player.facing > 0 and player.grounded and player.get_hit_rect().intersects(Rect2(4720, 380, 30, 100)):
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
		camera_lock_position = transition_camera_start.lerp(Vector2(5040, 400), float(state_ticks - 20) / 40.0)
	elif state_ticks <= 80:
		_set_door_opening(0, 1.0 - float(state_ticks - 60) / 20.0)
	else:
		_set_door_opening(0, 0.0)
		camera_lock_position = Vector2(5040, 400)
		progress.set_third_boss_checkpoint(true)
		stage_state = StageState.CHECKPOINT
		state_ticks = 0
		player.set_scripted_animation_active(false)
		_set_gameplay_active(true)


func _update_checkpoint() -> void:
	player.position.x = clampf(player.position.x, 4750.0, 5290.0)
	if player.facing > 0 and player.get_hit_rect().intersects(Rect2(5330, 380, 30, 100), true):
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
		camera_lock_position = transition_camera_start.lerp(Vector2(5600, 400), float(state_ticks - 20) / 40.0)
	elif state_ticks <= 80:
		_set_door_opening(1, 1.0 - float(state_ticks - 60) / 20.0)
	else:
		_set_door_opening(1, 0.0)
		camera_lock_position = Vector2(5600, 400)
		player.position.y = 400.0
		player.y_speed = 0.0
		player.grounded = true
		player.set_scripted_animation_active(false)
		stage_state = StageState.BOSS_INTRO
		state_ticks = 0
		boss.set_gameplay_active(false)


func _update_boss_intro() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		player.scripted_step_right(5.0)
	elif state_ticks == 57:
		_spawn_boss_projectile(World3Projectile.Kind.BOSS_LIGHTNING, Vector2(5750, 160))
	elif state_ticks == 60:
		hud.set_boss_flash(0.5)
	elif state_ticks == 61:
		hud.set_boss_flash(1.0)
		boss.visible = true
	elif state_ticks == 62:
		hud.set_boss_flash(0.5)
	elif state_ticks == 63:
		hud.set_boss_flash(0.0)
	elif state_ticks >= 68 and state_ticks < 98:
		pass
	elif state_ticks == 98:
		stage_state = StageState.BOSS
		state_ticks = 0
		player.set_scripted_animation_active(false)
		boss.set_gameplay_active(true)
		boss.start_fight()
		_set_gameplay_active(true)


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 5340.0, 5920.0)


func _on_boss_defeated() -> void:
	boss_reward_position = boss.position + Vector2(38, 16)
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
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 5:
				for burst in range(3):
					_spawn_enemy_death(boss.position + Vector2(25, 25))
			if state_ticks % 7 == 3 and is_instance_valid(boss):
				_spawn_enemy_death(boss.position + Vector2(randi_range(0, 50), randi_range(0, 50)))
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
	boss_reward = ThirdBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(2)
	progress.unlock_third_boss_reward()
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
		progress.set_third_boss_checkpoint(false)
		hud.set_completion_fade(1.0)
		hud.show_message("THIRD STAGE COMPLETE\n\nPRESS R TO REPLAY")


func _set_departure_frame(texture: Texture2D, offset: Vector2, flipped: bool = false) -> void:
	departure_back.visible = false
	departure_front.visible = true
	departure_front.texture = texture
	departure_front.position = player.position + offset
	departure_front.flip_h = flipped


func _spawn_stage_objects() -> void:
	for data in map_config["wall_turrets"]:
		var turret: World3WallTurret = WallTurretScript.new()
		_spawn_enemy(turret, data[0])
		turret.configure(data[1], data[2])
	for spawn_position in map_config["machines"]:
		var machine: World3Machine = MachineScript.new()
		_spawn_enemy(machine, spawn_position)
		machine.configure()
	for data in map_config["oranges"]:
		var orange: World3Orange = OrangeScript.new()
		_spawn_enemy(orange, data[0])
		orange.configure(data[1])
	for data in map_config["shockers"]:
		var shocker: World3Shocker = ShockerScript.new()
		_spawn_enemy(shocker, data[0])
		shocker.configure(data[1], data[2])
	for data in map_config["cards"]:
		if not progress.has_card(data[2]):
			_spawn_card(data[0], data[2], data[1])
	if not map_config["holder"].is_empty() and not progress.has_card(map_config["holder"][1]):
		card_holder = CardHolderScript.new()
		card_holder.position = map_config["holder"][0]
		card_holder.z_index = 10
		add_child(card_holder)
		card_holder.card_id = map_config["holder"][1]
		card_holder.opened.connect(_on_card_holder_opened)


func _spawn_enemy(enemy: SakuraEnemy, spawn_position: Vector2) -> void:
	enemy.position = spawn_position
	enemy.z_index = 10
	add_child(enemy)
	enemy.setup(terrain, player)
	_register_enemy(enemy)


func _register_enemy(enemy: SakuraEnemy) -> void:
	enemies.append(enemy)
	enemy.defeated.connect(_on_enemy_defeated)


func _on_enemy_defeated(enemy: SakuraEnemy, effect_position: Vector2, _drop_position: Vector2, drop_type: int) -> void:
	enemies.erase(enemy)
	if enemy is World3Machine:
		var machine_effect: World3MachineDeathEffect = MachineDeathEffectScript.new()
		machine_effect.position = effect_position
		machine_effect.z_index = 30
		add_child(machine_effect)
	else:
		_spawn_enemy_death(effect_position)
	if drop_type != SakuraEnemy.DropType.NONE:
		var recovery: RecoveryPickup = RecoveryScript.new()
		recovery.z_index = 12
		add_child(recovery)
		recovery.setup(terrain, player, drop_type)
		recovery.position = enemy.position + (enemy.body_size - recovery.body_size) * 0.5


func _on_card_holder_opened(drop_position: Vector2, card_id: int) -> void:
	if not progress.has_card(card_id):
		_spawn_card(drop_position, card_id, true)


func _spawn_recovery(spawn_position: Vector2, drop_type: int) -> void:
	var recovery: RecoveryPickup = RecoveryScript.new()
	recovery.position = spawn_position
	recovery.z_index = 12
	add_child(recovery)
	recovery.setup(terrain, player, drop_type)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: World3CardPickup = CardPickupScript.new()
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
	if is_instance_valid(card_holder) and card_holder.projectile_mask_overlap(rect):
		card_holder.take_projectile_hit(damage)
		return true
	for enemy in enemies:
		if is_instance_valid(enemy) and not enemy.defeated_state and enemy.projectile_mask_overlap(rect):
			enemy.take_projectile_hit(damage)
			return true
	return false


func _on_player_died() -> void:
	boss_health_was_visible_on_death = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO
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
	fill.color = Color8(15, 0, 0)
	fill.mouse_filter = Control.MOUSE_FILTER_IGNORE
	fill.z_index = -200
	add_child(fill)
	for index in range(4):
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = preload("res://assets/world3/background.png")
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		sprite.z_index = -100
		add_child(sprite)
		background_sprites.append(sprite)
	background_sprite = background_sprites[0]


func _update_background() -> void:
	if not is_instance_valid(background_sprite) or not is_instance_valid(camera):
		return
	var viewport_top_left := camera.position - VIEWPORT_HALF_SIZE
	var texture_size := background_sprite.texture.get_size()
	var sampled_origin := viewport_top_left / 5.0
	var world_offset := viewport_top_left - sampled_origin
	var source_x := floorf(sampled_origin.x / texture_size.x) * texture_size.x
	if map_number == 30:
		for index in range(background_sprites.size()):
			background_sprites[index].visible = index < 2
			background_sprites[index].position = world_offset + Vector2(source_x + index * texture_size.x, 60)
	else:
		var source_y := floorf(sampled_origin.y / texture_size.y) * texture_size.y
		for index in range(background_sprites.size()):
			background_sprites[index].visible = true
			background_sprites[index].position = world_offset + Vector2(source_x + index % 2 * texture_size.x, source_y + int(index / 2.0) * texture_size.y)


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
	var has_portal := map_number == 30 or checkpoint_active
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
	return map_number == 30 or checkpoint_active


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
	var door_texture: Texture2D = preload("res://assets/world3/door.png")
	for door_position in [Vector2(4720, 380), Vector2(5330, 380)]:
		var door := Sprite2D.new()
		door.centered = false
		door.texture = door_texture
		door.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		door.position = door_position
		door.z_index = 9
		add_child(door)
		boss_doors.append(door)
	boss = ThirdBossScript.new()
	_spawn_enemy(boss, Vector2(5720, 411))
	boss.visible = false
	boss.flash_requested.connect(_on_boss_flash_requested)
	boss.lightning_requested.connect(_on_boss_lightning_requested)
	boss.ball_requested.connect(_on_boss_ball_requested)
	boss.beam_requested.connect(_on_boss_beam_requested)
	boss.boss_defeated.connect(_on_boss_defeated)


func _on_boss_flash_requested(alpha: float) -> void:
	hud.set_boss_flash(alpha)


func _on_boss_lightning_requested(spawn_position: Vector2) -> void:
	_spawn_boss_projectile(World3Projectile.Kind.BOSS_LIGHTNING, spawn_position)


func _on_boss_ball_requested(spawn_position: Vector2, direction: int) -> void:
	_spawn_boss_projectile(World3Projectile.Kind.SHOCK_BALL, spawn_position, direction)


func _on_boss_beam_requested(spawn_position: Vector2) -> void:
	_spawn_boss_projectile(World3Projectile.Kind.BOSS_BEAM, spawn_position)


func _spawn_boss_projectile(kind: int, spawn_position: Vector2, direction: int = 0) -> void:
	var projectile := World3Projectile.new()
	projectile.position = spawn_position
	projectile.z_index = 14
	add_child(projectile)
	projectile.setup(kind, terrain, player, direction)


func _set_door_opening(index: int, amount: float) -> void:
	if index < 0 or index >= boss_doors.size():
		return
	boss_doors[index].position.y = 380.0 - clampf(amount, 0.0, 1.0) * 100.0


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
	if map_number == 32 and not checkpoint_active:
		camera.position = Vector2(
			clampf(center.x, VIEWPORT_HALF_SIZE.x, 4430.0),
			clampf(center.y, VIEWPORT_HALF_SIZE.y, 400.0)
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
		boss_visible = stage_state == StageState.BOSS or (stage_state == StageState.BOSS_INTRO and state_ticks >= 68) or (stage_state == StageState.DYING and boss_health_was_visible_on_death)
		displayed_boss_hp = boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_boss_hp = clampi(state_ticks - 67, 0, 30)
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
