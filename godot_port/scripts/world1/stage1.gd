extends "res://scripts/shared/stage_base.gd"

const RedBallScript = preload("res://scripts/world1/red_ball.gd")
const HappySpringScript = preload("res://scripts/world1/happy_spring.gd")
const GreenTurretScript = preload("res://scripts/world1/green_turret.gd")
const PirikitoScript = preload("res://scripts/world1/pirikito.gd")
const PumpkinScript = preload("res://scripts/world1/pumpkin.gd")
const FirstBossScript = preload("res://scripts/world1/first_boss.gd")
const TurretDeathEffectScript = preload("res://scripts/world1/turret_death_effect.gd")
const BossRoomBlockScript = preload("res://scripts/world1/boss_room_block.gd")
const BossRewardScript = preload("res://scripts/world1/boss_reward.gd")
const CardPickupScript = preload("res://scripts/world1/card_pickup.gd")
const CardHolderScript = preload("res://scripts/world1/card_holder.gd")
const STAGE1_ATLAS := preload("res://assets/world1/terrain.png")
const STAGE1_SOURCE_RECTS := {
	"2": Vector2i(20, 0),
	"3": Vector2i(40, 0),
	"4": Vector2i(0, 40),
	"5": Vector2i(0, 60),
	"a": Vector2i(20, 40),
	"b": Vector2i(60, 40),
	"c": Vector2i(20, 20),
	"d": Vector2i(20, 60),
	"e": Vector2i(60, 60),
	"f": Vector2i(40, 20),
	"g": Vector2i(60, 0),
	"h": Vector2i(0, 80),
	"i": Vector2i(0, 0),
	"j": Vector2i(60, 20),
	"k": Vector2i(40, 60),
	"l": Vector2i(0, 20),
	"m": Vector2i(40, 40),
}
const STAGE1_NON_SOLID := ["0", "1"]
const STAGE1_LETHAL := ["0"]

const BACKGROUND_WIDTH := 1000.0
const BACKGROUND_HEIGHT := 520.0
const BACKGROUND_COLUMNS := 2
const BACKGROUND_SPRITE_COUNT := 4
const BACKGROUND_PARALLAX_FACTOR := 0.85
const FIRST_BOSS_CAMERA_POSITION := Vector2(3220.0, 320.0)
const BOSS_BLOCK_DELAY_SCALE := 4
const BOSS_BLOCK_SEQUENCE_TICKS := 120
const BOSS_METER_FILL_INTERVAL := 4

const MAP_CONFIGS := {
	10: {
		"width": 450,
		"height": 28,
		"start": Vector2(60, 200),
		"exit": Rect2(8960, 280, 80, 200),
		"next": 11,
		"red_balls": [
			[Vector2(800, 320), 0], [Vector2(1480, 320), 0],
			[Vector2(1780, 240), 1], [Vector2(2920, 120), 0],
			[Vector2(3220, 120), 0], [Vector2(3680, 280), 0],
			[Vector2(5140, 400), 0], [Vector2(5500, 340), 0],
			[Vector2(5800, 280), 0], [Vector2(7060, 420), 0],
			[Vector2(7480, 240), 0], [Vector2(7700, 160), 0],
			[Vector2(7900, 120), 0],
		],
		"springs": [[Vector2(2720, 220), 0], [Vector2(6480, 380), 0], [Vector2(7060, 400), 0]],
		"turrets": [],
		"birds": [[Vector2(4320, 120), 0], [Vector2(6100, 160), 0], [Vector2(6180, 160), -10]],
		"pumpkins": [],
		"cards": [[Vector2(4052, 260), true, 32]],
		"holder": [Vector2(6470, 120), 43],
	},
	11: {
		"width": 40,
		"height": 100,
		"start": Vector2(0, 60),
		"exit": Rect2(760, 1820, 80, 200),
		"next": 12,
		"red_balls": [
			[Vector2(300, 180), 0], [Vector2(180, 560), 0],
			[Vector2(180, 1200), 0], [Vector2(420, 1440), 0],
			[Vector2(480, 1720), 1], [Vector2(380, 1720), 0],
		],
		"springs": [[Vector2(480, 420), 0], [Vector2(460, 1100), 0], [Vector2(280, 1540), 0]],
		"turrets": [[Vector2(340, 880), 0], [Vector2(400, 880), 1], [Vector2(620, 1860), 0]],
		"birds": [],
		"pumpkins": [],
		"cards": [[Vector2(612, 740), true, 42]],
		"holder": [],
	},
	12: {
		"width": 420,
		"height": 30,
		"background_y": 80.0,
		"start": Vector2(0, 400),
		"exit": Rect2(8360, 420, 80, 200),
		"next": 13,
		"red_balls": [
			[Vector2(680, 360), 0], [Vector2(1860, 400), 0],
			[Vector2(2440, 120), 0], [Vector2(4720, 280), 0],
			[Vector2(7240, 300), 0],
		],
		"springs": [
			[Vector2(880, 340), 0], [Vector2(4180, 380), 0],
			[Vector2(4240, 380), -20], [Vector2(6760, 360), 0],
			[Vector2(6805, 360), -5], [Vector2(6850, 360), -10],
		],
		"turrets": [
			[Vector2(980, 500), 0], [Vector2(2420, 440), 0],
			[Vector2(5710, 240), 0], [Vector2(7480, 420), 1],
		],
		"birds": [[Vector2(4030, 50), 0], [Vector2(4880, 180), 0], [Vector2(6080, 100), 0]],
		"pumpkins": [[Vector2(3440, 320), 0], [Vector2(6240, 240), 0], [Vector2(5080, 240), 0]],
		"cards": [[Vector2(2559, 380), true, 10]],
		"holder": [Vector2(7180, 80), 37],
	},
	13: {
		"width": 40,
		"height": 90,
		"start": Vector2(0, 1680),
		"exit": Rect2(760, 40, 80, 200),
		"next": 14,
		"red_balls": [
			[Vector2(500, 1200), 0], [Vector2(380, 940), 0],
			[Vector2(300, 120), 0], [Vector2(480, 120), 1],
		],
		"springs": [[Vector2(340, 1600), 0], [Vector2(310, 360), 0]],
		"turrets": [[Vector2(470, 700), 0]],
		"birds": [],
		"pumpkins": [[Vector2(600, 1740), 0], [Vector2(320, 1120), 0], [Vector2(400, 580), 0]],
		"cards": [[Vector2(562, 1720), true, 28], [Vector2(620, 240), true, 13]],
		"holder": [],
	},
	14: {
		"width": 200,
		"height": 28,
		"start": Vector2(0, 380),
		"exit": Rect2(2120, 280, 80, 200),
		"next": 0,
		"red_balls": [[Vector2(580, 380), 0], [Vector2(1380, 360), 0]],
		"springs": [],
		"turrets": [],
		"birds": [[Vector2(1170, 160), 0], [Vector2(1250, 180), -10], [Vector2(1540, 260), 0]],
		"pumpkins": [],
		"cards": [[Vector2(1720, 280), true, 20]],
		"holder": [],
	},
}

var card_holder: World1CardHolder
var boss: FirstStageBoss
var intermission_active := false
var boss_blocks: Array[BossRoomBlock] = []
var transition_player_start_x := 0.0
var boss_blocks_started := false
var boss_block_sequence_ticks := 0
var boss_spawn_started := false
var boss_meter_ticks := 0
var boss_meter_fill_phase := 0
var boss_reward: BossReward


func _first_map_number() -> int:
	return 10


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE1_ATLAS,
		STAGE1_SOURCE_RECTS,
		PackedStringArray(STAGE1_NON_SOLID),
		PackedStringArray(STAGE1_LETHAL),
		{}
	)


func _configure_checkpoint() -> void:
	if map_number == 14 and progress.boss_checkpoint:
		player.position = Vector2(2300, 300)
		intermission_active = true
		camera_locked = true
		camera_lock_position = Vector2(2440, 320)


func _build_stage_boss_area() -> void:
	if map_number == 14:
		_build_boss_room()


func _entry_has_checkpoint() -> bool:
	return intermission_active


func _entry_complete_state() -> int:
	return StageState.INTERMISSION if intermission_active else StageState.PLAYING


func _stage_complete_message() -> String:
	return "FIRST STAGE COMPLETE\n\nPress R to replay map14"


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
		StageState.INTERMISSION_ENTRY:
			_update_intermission_entry()
		StageState.INTERMISSION:
			_update_intermission()
		StageState.BOSS_INTRO:
			_update_boss_intro()
		StageState.BOSS:
			_update_boss()
		StageState.VICTORY:
			_update_victory()
	_finish_physics_tick()


func _update_playing() -> void:
	if player.grounded and player.get_hit_rect().intersects(map_config["exit"]):
		if map_number == 14:
			_begin_intermission_entry()
			return
		stage_state = StageState.EXITING
		state_ticks = 0
		_set_gameplay_active(false)
		player.set_scripted_animation_active(true)


func _begin_intermission_entry() -> void:
	stage_state = StageState.INTERMISSION_ENTRY
	state_ticks = 0
	intermission_active = true
	camera_locked = true
	transition_camera_start = camera.position
	camera_lock_position = transition_camera_start
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _update_intermission_entry() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		_set_boss_door_opening(0, float(state_ticks) / 40.0)
	elif state_ticks <= 120:
		_set_boss_door_opening(0, 1.0)
		player.scripted_step_right(2.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(2440, 320), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_boss_door_opening(0, 1.0 - float(state_ticks - 120) / 40.0)
	else:
		_set_boss_door_opening(0, 0.0)
		camera_lock_position = Vector2(2440, 320)
		progress.set_boss_checkpoint(true)
		stage_state = StageState.INTERMISSION
		state_ticks = 0
		player.set_scripted_animation_active(false)
		_set_gameplay_active(true)


func _update_intermission() -> void:
	player.position.x = clampf(player.position.x, 2160.0, 2690.0)
	if player.grounded and player.get_hit_rect().end.x >= 2730.0:
		_begin_boss_intro()


func _begin_boss_intro() -> void:
	stage_state = StageState.BOSS_INTRO
	state_ticks = 0
	camera_locked = true
	transition_camera_start = camera.position
	transition_player_start_x = player.position.x
	camera_lock_position = transition_camera_start
	boss_room_active = true
	boss_blocks_started = false
	boss_block_sequence_ticks = 0
	boss_spawn_started = false
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _update_boss_intro() -> void:
	state_ticks += 1
	if boss_spawn_started and is_instance_valid(boss) and boss.state != FirstStageBoss.BossState.ENTERING and boss_meter_ticks < boss.hit_points:
		boss_meter_fill_phase += 1
		if boss_meter_fill_phase >= BOSS_METER_FILL_INTERVAL:
			boss_meter_fill_phase = 0
			boss_meter_ticks += 1
			get_node("/root/AudioManager").play_sfx("recuperator")
	if state_ticks <= 40:
		_set_boss_door_opening(1, float(state_ticks) / 40.0)
		return
	if state_ticks <= 80:
		_set_boss_door_opening(1, 1.0)
		player.scripted_step_right(2.0)
		_update_boss_intro_camera()
		return
	if state_ticks <= 120:
		_set_boss_door_opening(1, 1.0 - float(state_ticks - 80) / 40.0)
		return
	_set_boss_door_opening(1, 0.0)
	camera_lock_position = FIRST_BOSS_CAMERA_POSITION
	if state_ticks == 121:
		player.position.y = 300.0
		player.y_speed = 0.0
		player.grounded = true
	if player.position.x < 3200.0:
		player.scripted_step_right(2.0)
		_update_boss_intro_camera()
		return
	player.position.x = 3200.0
	player.position.y = 300.0
	player.grounded = true
	player.set_scripted_animation_active(false)
	if not boss_blocks_started:
		boss_blocks_started = true
		for index in range(boss_blocks.size()):
			if is_instance_valid(boss_blocks[index]):
				boss_blocks[index].activate((1 + index * 2) * BOSS_BLOCK_DELAY_SCALE)
	if not boss_spawn_started:
		boss_block_sequence_ticks += 1
		if boss_block_sequence_ticks < BOSS_BLOCK_SEQUENCE_TICKS:
			return
		boss_spawn_started = true
		boss_meter_ticks = 0
		boss_meter_fill_phase = 0
		boss = FirstBossScript.new()
		_spawn_enemy(boss, Vector2(3180, -100))
		boss.configure()
		boss.boss_defeated.connect(_on_boss_defeated)
		boss.set_gameplay_active(true)
	if is_instance_valid(boss) and boss.vulnerable:
		stage_state = StageState.BOSS
		state_ticks = 0
		camera_locked = false
		_set_gameplay_active(true)


func _set_boss_door_opening(index: int, amount: float) -> void:
	if index < 0 or index >= boss_doors.size():
		return
	boss_doors[index].position.y = 280.0 - clampf(amount, 0.0, 1.0) * 100.0


func _update_boss_intro_camera() -> void:
	var travel := maxf(1.0, 3200.0 - transition_player_start_x)
	var amount := clampf((player.position.x - transition_player_start_x) / travel, 0.0, 1.0)
	camera_lock_position = transition_camera_start.lerp(FIRST_BOSS_CAMERA_POSITION, amount)


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 2760.0, 3940.0)


func _on_boss_defeated() -> void:
	boss_reward_position = Vector2(2440, 220)
	if is_instance_valid(boss):
		enemies.erase(boss)
		boss_reward_position = boss.position + boss.body_size * 0.5 - Vector2(11, 18)
		for offset in [Vector2(0, 0), Vector2(35, 20), Vector2(-30, 40), Vector2(20, 70)]:
			_spawn_boss_explosion(boss.position + boss.body_size * 0.5 + offset)
	for projectile in get_tree().get_nodes_in_group("boss_projectiles"):
		projectile.queue_free()
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
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 24 and is_instance_valid(boss):
				_spawn_boss_light_flashes(boss.position + boss.body_size * 0.5)
			if preload("res://scripts/shared/boss_explosion_timing.gd").is_due(self, state_ticks) and is_instance_valid(boss):
				_spawn_boss_explosion(boss.position + Vector2(randi_range(0, int(boss.body_size.x)), randi_range(0, int(boss.body_size.y))))
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
	if departure_ticks > 0:
		_update_departure()


func _spawn_boss_reward() -> void:
	boss_reward_started = true
	if _is_active_rematch() or progress.has_boss_reward(0):
		return
	boss_reward = BossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.unlock_first_boss_reward()
	_begin_boss_landing()


func _complete_departure() -> void:
	progress.set_boss_checkpoint(false)
	_finish_elemental_or_rematch(1)


func _spawn_stage_objects() -> void:
	for data in map_config["red_balls"]:
		var enemy: RedBallEnemy = RedBallScript.new()
		_spawn_enemy(enemy, data[0])
		enemy.configure(data[1])
	for data in map_config["springs"]:
		var enemy: HappySpringEnemy = HappySpringScript.new()
		_spawn_enemy(enemy, data[0])
		enemy.configure(data[1])
	for data in map_config["turrets"]:
		var enemy: GreenTurretEnemy = GreenTurretScript.new()
		_spawn_enemy(enemy, data[0])
		enemy.configure(data[1])
	for data in map_config["birds"]:
		var enemy: PirikitoEnemy = PirikitoScript.new()
		_spawn_enemy(enemy, data[0])
		enemy.configure(data[1])
	for data in map_config["pumpkins"]:
		var enemy: PumpkinEnemy = PumpkinScript.new()
		_spawn_enemy(enemy, data[0])
		enemy.configure(data[1])
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


func _spawn_enemy_defeat_effect(enemy: SakuraEnemy, effect_position: Vector2) -> void:
	if enemy is GreenTurretEnemy:
		_spawn_turret_death(effect_position, enemy.sprite.flip_h)
	else:
		_spawn_enemy_death(effect_position)


func _damage_stage_object_in_rect(rect: Rect2, damage: int, _weapon_id: int = 1) -> bool:
	if is_instance_valid(card_holder) and card_holder.projectile_mask_overlap(rect):
		card_holder.take_projectile_hit(damage)
		return true
	return false


func _on_card_holder_opened(spawn_position: Vector2, card_id: int) -> void:
	if not progress.has_card(card_id):
		_spawn_card(spawn_position, card_id, true)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	if progress.has_card(card_id):
		return
	var card: World1CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)


func _recovery_fall_speed() -> float:
	return 3.75


func _spawn_enemy_death(effect_position: Vector2) -> void:
	get_node("/root/AudioManager").play_sfx("anim40")
	var effect: EnemyDeathEffect = EnemyDeathEffectScript.new()
	effect.frame_hold_ticks = 8
	effect.position = effect_position
	effect.z_index = 30
	add_child(effect)


func _spawn_turret_death(effect_position: Vector2, flip_h: bool) -> void:
	get_node("/root/AudioManager").play_sfx("anim60")
	var effect: TurretDeathEffect = TurretDeathEffectScript.new()
	effect.flip_h = flip_h
	effect.position = effect_position
	effect.z_index = 30
	add_child(effect)


func _build_background() -> void:
	var texture: Texture2D = preload("res://assets/world1/background.png")
	for repeat_index in range(BACKGROUND_SPRITE_COUNT):
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = texture
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		sprite.position = Vector2(repeat_index * BACKGROUND_WIDTH, 0)
		sprite.z_index = -100
		add_child(sprite)
		background_sprites.append(sprite)


func _update_background() -> void:
	if not is_inside_tree() or not is_instance_valid(camera):
		return
	var viewport_top_left := camera.position - VIEWPORT_HALF_SIZE
	var background_y := float(map_config.get("background_y", 0.0))
	var sampled_origin := viewport_top_left * BACKGROUND_PARALLAX_FACTOR - Vector2(0.0, background_y)
	var world_offset := viewport_top_left - sampled_origin
	var first_column := floori(sampled_origin.x / BACKGROUND_WIDTH)
	var first_row := floori(sampled_origin.y / BACKGROUND_HEIGHT)
	for sprite_index in range(background_sprites.size()):
		var column := sprite_index % BACKGROUND_COLUMNS
		var row := floori(float(sprite_index) / float(BACKGROUND_COLUMNS))
		background_sprites[sprite_index].position = world_offset + Vector2(
			(first_column + column) * BACKGROUND_WIDTH,
			(first_row + row) * BACKGROUND_HEIGHT
		)


func _build_boss_room() -> void:
	var texture: Texture2D = preload("res://assets/world1/boss_door.png")
	for door_position in [Vector2(2120, 280), Vector2(2730, 280)]:
		var door := Sprite2D.new()
		door.centered = false
		door.texture = texture
		door.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		door.position = door_position
		door.z_index = 9
		add_child(door)
		boss_doors.append(door)
	for data in [[Vector2(2760, 380), false], [Vector2(2780, 380), true], [Vector2(2860, 380), true], [Vector2(2940, 380), true], [Vector2(3020, 380), true]]:
		var block: BossRoomBlock = BossRoomBlockScript.new()
		block.position = data[0]
		block.z_index = 8
		add_child(block)
		block.configure(data[1])
		boss_blocks.append(block)


func _update_camera() -> void:
	if not is_instance_valid(camera) or not is_instance_valid(player):
		return
	if camera_locked:
		camera.position = camera_lock_position
		_update_background()
		return
	var center := player.get_center()
	if map_number == 14 and not intermission_active and not boss_room_active:
		camera.position = Vector2(
			clampf(center.x, VIEWPORT_HALF_SIZE.x, 1830.0),
			clampf(center.y, VIEWPORT_HALF_SIZE.y, terrain.world_size.y - VIEWPORT_HALF_SIZE.y)
		)
		_update_background()
		return
	if boss_room_active:
		camera.position = Vector2(
			clampf(center.x, 3060.0, 3680.0),
			clampf(center.y, VIEWPORT_HALF_SIZE.y, terrain.world_size.y - VIEWPORT_HALF_SIZE.y)
		)
		_update_background()
		return
	camera.position = Vector2(
		clampf(center.x, VIEWPORT_HALF_SIZE.x, terrain.world_size.x - VIEWPORT_HALF_SIZE.x),
		clampf(center.y, VIEWPORT_HALF_SIZE.y, terrain.world_size.y - VIEWPORT_HALF_SIZE.y)
	)
	_update_background()


func _update_boss_hud() -> void:
	var boss_visible := stage_state == StageState.BOSS or (stage_state == StageState.BOSS_INTRO and boss_spawn_started) or (stage_state == StageState.DYING and boss_spawn_started and is_instance_valid(boss))
	var displayed_boss_hp := boss.hit_points if is_instance_valid(boss) else 0
	if stage_state == StageState.BOSS_INTRO:
		displayed_boss_hp = clampi(boss_meter_ticks, 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)
