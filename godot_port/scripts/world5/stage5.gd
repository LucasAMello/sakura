extends "res://scripts/shared/stage_base.gd"

const FlamethrowerScript = preload("res://scripts/world5/flamethrower.gd")
const FlameBurstScript = preload("res://scripts/world5/flame_burst.gd")
const FlamemetScript = preload("res://scripts/world5/flamemet.gd")
const FallingFireScript = preload("res://scripts/world5/falling_fire.gd")
const LavaStripScript = preload("res://scripts/world5/lava_strip.gd")
const SquidScript = preload("res://scripts/world5/squid.gd")
const CardPickupScript = preload("res://scripts/world5/card_pickup.gd")
const CardHolderScript = preload("res://scripts/world5/card_holder.gd")
const FifthBossScript = preload("res://scripts/world5/fifth_boss.gd")
const BossProjectileScript = preload("res://scripts/world5/boss_projectile.gd")
const FifthBossRewardScript = preload("res://scripts/world5/fifth_boss_reward.gd")
const STAGE5_ATLAS := preload("res://assets/world5/terrain.png")
const STAGE5_BACKGROUND := preload("res://assets/world5/background.png")

const STAGE5_SOURCE_RECTS := {
	"2": Vector2i(20, 20), "6": Vector2i(140, 60), "0": Vector2i(60, 20),
	"a": Vector2i(100, 0), "e": Vector2i(100, 40),
	"i": Vector2i(20, 0), "j": Vector2i(40, 0), "k": Vector2i(60, 0),
	"l": Vector2i(20, 80), "m": Vector2i(40, 80), "n": Vector2i(60, 80),
	"o": Vector2i(0, 0), "O": Vector2i(0, 0),
	"p": Vector2i(0, 20), "P": Vector2i(0, 20), ">": Vector2i(0, 20),
	"q": Vector2i(0, 40), "r": Vector2i(0, 60),
	"s": Vector2i(0, 80), "S": Vector2i(0, 80),
	"t": Vector2i(80, 0), "T": Vector2i(80, 0),
	"u": Vector2i(80, 20), "@": Vector2i(80, 20), "<": Vector2i(80, 20),
	"v": Vector2i(80, 40), "w": Vector2i(80, 60),
	"x": Vector2i(80, 80), "!": Vector2i(80, 80),
	"y": Vector2i(20, 60), "z": Vector2i(140, 0),
	"(": Vector2i(60, 40), ")": Vector2i(60, 60),
	"A": Vector2i(180, 0), "B": Vector2i(160, 20), "C": Vector2i(180, 20),
	"D": Vector2i(200, 0), "E": Vector2i(220, 20), "F": Vector2i(200, 20),
	"U": Vector2i(180, 60), "V": Vector2i(160, 40), "W": Vector2i(180, 40),
	"X": Vector2i(200, 60), "Y": Vector2i(220, 40), "Z": Vector2i(200, 40),
	"I": Vector2i(20, 60), "J": Vector2i(40, 60),
	"L": Vector2i(100, 80), "M": Vector2i(120, 80), "N": Vector2i(180, 80),
	"]": Vector2i(220, 80), "[": Vector2i(200, 80), ".": Vector2i(160, 0),
}
const STAGE5_UNDERLAY_SOURCE_RECTS := {
	"O": Vector2i(20, 60), "P": Vector2i(20, 60), "S": Vector2i(20, 60),
	"T": Vector2i(20, 60), "@": Vector2i(20, 60), "!": Vector2i(20, 60),
	">": Vector2i(100, 80), "<": Vector2i(100, 80),
}
const STAGE5_NON_SOLID := [
	"1", "2", "6", "a", "e", "A", "B", "C", "D", "E", "F",
	"U", "V", "W", "X", "Y", "Z", "I", "J", "<", ">",
]
const STAGE5_DRAW_SIZES := {
	"2": Vector2(40, 40), "6": Vector2(40, 40),
	"a": Vector2(40, 40), "e": Vector2(40, 40),
}

const MAP_CONFIGS := {
	50: {
		"width": 40, "height": 80, "start": Vector2(40, 100),
		"exit": Rect2(760, 1300, 80, 200), "next": 51,
		"horizontal_flamethrowers": [[Vector2(496, 200), 1, 0], [Vector2(184, 360), 0, -15]],
		"vertical_flamethrowers": [[Vector2(480, 940), 1, 0]],
		"flamemets": [[Vector2(320, 1147), 0, false]],
		"lava": [[Vector2(220, 1540), 140], [Vector2(440, 1540), 220]],
		"squids": [], "cards": [[Vector2(535, 850), 29, false]], "holder": [],
	},
	51: {
		"width": 360, "height": 36, "start": Vector2(0, 340),
		"exit": Rect2(7160, 340, 80, 200), "next": 52,
		"horizontal_flamethrowers": [[Vector2(4900, 320), 0, 0], [Vector2(5180, 380), 1, -10], [Vector2(4900, 440), 0, -20]],
		"vertical_flamethrowers": [
			[Vector2(2340, 500), 1, 0], [Vector2(2400, 260), 0, -40],
			[Vector2(2460, 500), 1, 0], [Vector2(2520, 260), 0, -40],
			[Vector2(2580, 500), 1, 0], [Vector2(2640, 260), 0, -40],
			[Vector2(6040, 300), 0, 0], [Vector2(6040, 580), 1, 0],
			[Vector2(6400, 300), 0, -40], [Vector2(6400, 580), 1, -40],
			[Vector2(6840, 300), 0, 0], [Vector2(6840, 580), 1, 0],
		],
		"flamemets": [
			[Vector2(610, 467), 0, false], [Vector2(1840, 587), 0, false],
			[Vector2(2080, 547), 0, false], [Vector2(4280, 227), 0, false],
			[Vector2(5800, 340), 0, true], [Vector2(6160, 340), 0, true],
			[Vector2(6320, 340), 1, true], [Vector2(6520, 340), 0, true],
			[Vector2(6680, 340), 0, true],
		],
		"lava": [[Vector2(860, 520), 160], [Vector2(1140, 520), 160], [Vector2(3060, 520), 480], [Vector2(4060, 300), 160], [Vector2(4380, 300), 200]],
		"squids": [Vector2(1200, 540), Vector2(4120, 320), Vector2(4440, 320)],
		"cards": [[Vector2(3460, 320), 33, false], [Vector2(7060, 420), 15, false]], "holder": [],
	},
	52: {
		"width": 60, "height": 80, "start": Vector2(0, 1420),
		"exit": Rect2(1160, 180, 80, 200), "next": 53,
		"horizontal_flamethrowers": [[Vector2(260, 1160), 0, 0], [Vector2(20, 360), 0, -30], [Vector2(140, 440), 0, 0]],
		"vertical_flamethrowers": [],
		"flamemets": [
			[Vector2(140, 1027), 0, false], [Vector2(860, 1387), 0, false],
			[Vector2(620, 867), 0, false], [Vector2(560, 547), 0, false],
			[Vector2(760, 460), 0, true],
		],
		"lava": [[Vector2(700, 320), 280]],
		"squids": [Vector2(740, 340), Vector2(800, 340), Vector2(860, 340)],
		"cards": [[Vector2(880, 80), 7, false]], "holder": [],
	},
	53: {
		"width": 300, "height": 120, "start": Vector2(0, 140),
		"exit": Rect2(), "next": 0,
		"horizontal_flamethrowers": [
			[Vector2(2980, 320), 0, 0], [Vector2(3180, 320), 1, -40],
			[Vector2(540, 800), 0, 0], [Vector2(540, 840), 0, -10], [Vector2(540, 880), 0, -20],
			[Vector2(780, 800), 1, -30], [Vector2(780, 840), 1, -40], [Vector2(780, 880), 1, -50],
		],
		"vertical_flamethrowers": [
			[Vector2(4200, 300), 1, 0], [Vector2(3040, 740), 1, 0], [Vector2(3720, 740), 1, 0],
			[Vector2(2560, 1540), 1, 0], [Vector2(2620, 1540), 1, -40], [Vector2(2680, 1540), 1, 0],
		],
		"flamemets": [
			[Vector2(1220, 267), 0, false], [Vector2(3660, 347), 0, false],
			[Vector2(4060, 347), 0, false], [Vector2(3860, 347), 1, false],
			[Vector2(4440, 347), 0, false], [Vector2(1400, 1347), 0, false],
			[Vector2(1940, 1347), 0, false], [Vector2(3640, 1427), 0, false],
			[Vector2(4200, 1427), 0, false],
			[Vector2(3760, 140), 0, true], [Vector2(4040, 140), 1, true],
			[Vector2(2900, 620), 0, true], [Vector2(3260, 620), 1, true],
			[Vector2(3660, 620), 0, true], [Vector2(4000, 620), 1, true],
		],
		"lava": [
			[Vector2(980, 320), 120], [Vector2(1500, 320), 160], [Vector2(1740, 320), 200],
			[Vector2(2020, 320), 400], [Vector2(4760, 760), 1060], [Vector2(2140, 760), 240],
			[Vector2(1700, 760), 160], [Vector2(1260, 760), 160], [Vector2(1060, 760), 120],
			[Vector2(5300, 2320), 80], [Vector2(5540, 2320), 140], [Vector2(5840, 2320), 60],
		],
		"squids": [Vector2(1600, 340), Vector2(2100, 340), Vector2(2360, 340), Vector2(1760, 780), Vector2(1100, 780)],
		"cards": [[Vector2(3110, 320), 45, true], [Vector2(5860, 680), 19, true]],
		"holder": [Vector2(2820, 1200), 9],
	},
}

var underlay_terrain: SakuraTerrain
var lava_strips: Array[World5LavaStrip] = []
var card_holder: World5CardHolder
var boss: FifthStageBoss
var boss_reward: FifthBossReward
var boss_fall_speed := 0.0
var boss_health_was_visible_on_death := false
var background_base_positions: Array[Vector2] = []


func _first_map_number() -> int:
	return 50


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE5_ATLAS,
		STAGE5_SOURCE_RECTS,
		PackedStringArray(STAGE5_NON_SOLID),
		PackedStringArray(),
		STAGE5_DRAW_SIZES
	)


func _configure_checkpoint() -> void:
	if map_number == 53 and progress.fifth_boss_checkpoint:
		player.position = Vector2(5160, 1340)
		checkpoint_active = true


func _build_stage_boss_area() -> void:
	underlay_terrain = TerrainScript.new()
	underlay_terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE5_ATLAS,
		STAGE5_UNDERLAY_SOURCE_RECTS,
		PackedStringArray(STAGE5_UNDERLAY_SOURCE_RECTS.keys()),
		PackedStringArray(),
		{}
	)
	underlay_terrain.z_index = -1
	add_child(underlay_terrain)
	if map_number == 53:
		boss = FifthBossScript.new()
		_spawn_enemy(boss, Vector2(5700, 2205))
		boss.projectile_requested.connect(_on_boss_projectile_requested)
		boss.boss_defeated.connect(_on_boss_defeated)


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
	if map_number == 53:
		if player.get_hit_rect().intersects(Rect2(4980, 1300, 360, 40)):
			_begin_world5_checkpoint()
		return
	if map_config["exit"].intersects(player.get_hit_rect()):
		stage_state = StageState.EXITING
		state_ticks = 0
		_set_gameplay_active(false)
		player.set_scripted_animation_active(true)


func _begin_world5_checkpoint() -> void:
	checkpoint_active = true
	progress.set_fifth_boss_checkpoint(true)
	stage_state = StageState.CHECKPOINT
	state_ticks = 0


func _update_checkpoint() -> void:
	if player.position.x >= 5460.0 or player.get_hit_rect().intersects(Rect2(5420, 1460, 360, 40)):
		player.position.x = minf(player.position.x, 5460.0)
		player.x_speed = 0.0
		player.y_speed = 0.0
		player.facing = 1
		_begin_boss_entry()
		boss_fall_speed = 0.0
		player.grounded = false
		player.set_scripted_frame(2)


func _update_boss_entry() -> void:
	state_ticks += 1
	_update_scripted_boss_fall()
	camera_lock_position.y = clampf(player.get_center().y, VIEWPORT_HALF_SIZE.y, 2160.0)
	if state_ticks <= 128:
		if player.position.x < 5460.0 and not player.grounded:
			player.position.x = move_toward(player.position.x, 5460.0, 1.0)
	elif state_ticks <= 132:
		player.facing = 1
	elif state_ticks <= 212:
		camera_lock_position.x = lerpf(transition_camera_start.x, 5600.0, float(state_ticks - 132) / 80.0)
	else:
		camera_lock_position = Vector2(5600, 2160)
		stage_state = StageState.BOSS_INTRO
		state_ticks = 0
		boss.start_intro()
		boss.set_gameplay_active(true)


func _update_boss_intro() -> void:
	state_ticks += 1
	_update_scripted_boss_fall()
	if state_ticks >= 96 and state_ticks <= 212 and state_ticks % 4 == 0:
		get_node("/root/AudioManager").play_sfx("recuperator")
	if state_ticks >= 216:
		player.position.y = 2220.0
		player.y_speed = 0.0
		player.grounded = true
		player.set_scripted_animation_active(false)
		stage_state = StageState.BOSS
		state_ticks = 0
		boss.start_fight()
		_set_gameplay_active(true)


func _update_scripted_boss_fall() -> void:
	if player.position.y < 2220.0:
		boss_fall_speed = minf(10.0, boss_fall_speed + 0.5)
		player.position.y = minf(2220.0, player.position.y + boss_fall_speed)
	player.grounded = player.position.y >= 2220.0
	if player.grounded:
		player.y_speed = 0.0
		player.facing = 1
	player.set_scripted_frame(0 if player.grounded else 2)


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 5280.0, 5880.0)


func _on_boss_defeated() -> void:
	boss_reward_position = boss.position + Vector2(53, 35)
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
	if boss_landing_pending:
		_update_boss_landing()
		return
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 24:
				_spawn_boss_light_flashes(boss.position + Vector2(64, 53))
			for _explosion in range(preload("res://scripts/shared/boss_explosion_timing.gd").due_count(self, state_ticks) if is_instance_valid(boss) else 0):
				_spawn_boss_explosion(boss.position + Vector2(randi_range(0, 128), randi_range(0, 60)))
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
	if _is_active_rematch():
		return
	boss_reward = FifthBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(4)
	progress.unlock_fifth_boss_reward()
	_begin_boss_landing()


func _complete_departure() -> void:
	progress.set_fifth_boss_checkpoint(false)
	if get_tree().current_scene == self:
		_finish_elemental_or_rematch(5)


func _spawn_stage_objects() -> void:
	for data in map_config["horizontal_flamethrowers"]:
		_spawn_flamethrower(data, false)
	for data in map_config["vertical_flamethrowers"]:
		_spawn_flamethrower(data, true)
	for data in map_config["flamemets"]:
		var flamemet: World5Flamemet = FlamemetScript.new()
		_spawn_enemy(flamemet, data[0])
		flamemet.configure(data[1], data[2])
		flamemet.falling_fire_requested.connect(_on_falling_fire_requested)
	for data in map_config["lava"]:
		var lava: World5LavaStrip = LavaStripScript.new()
		lava.position = data[0]
		lava.z_index = 10
		add_child(lava)
		lava.setup(player, data[1])
		lava_strips.append(lava)
		var lava_foreground: World5LavaStrip = LavaStripScript.new()
		lava_foreground.position = data[0]
		lava_foreground.z_index = 25
		add_child(lava_foreground)
		lava_foreground.setup(player, data[1], true)
		lava_strips.append(lava_foreground)
	for spawn_position in map_config["squids"]:
		var squid: World5Squid = SquidScript.new()
		_spawn_enemy(squid, spawn_position)
		squid.configure()
	for data in map_config["cards"]:
		if not progress.has_card(data[1]):
			_spawn_card(data[0], data[1], data[2])
	if not map_config["holder"].is_empty() and not progress.has_card(map_config["holder"][1]):
		card_holder = CardHolderScript.new()
		card_holder.position = map_config["holder"][0]
		card_holder.z_index = 10
		add_child(card_holder)
		card_holder.card_id = map_config["holder"][1]
		card_holder.opened.connect(_on_card_holder_opened)


func _spawn_flamethrower(data: Array, vertical: bool) -> void:
	var flamethrower: World5Flamethrower = FlamethrowerScript.new()
	_spawn_enemy(flamethrower, data[0])
	flamethrower.configure(vertical, data[1], data[2])
	flamethrower.flame_requested.connect(_on_flame_requested)


func _on_flame_requested(vertical: bool, spawn_position: Vector2, direction: int) -> void:
	var flame: World5FlameBurst = FlameBurstScript.new()
	_spawn_enemy(flame, spawn_position)
	flame.configure(vertical, direction)
	flame.set_gameplay_active(true)


func _on_falling_fire_requested(spawn_position: Vector2) -> void:
	var fire: World5FallingFire = FallingFireScript.new()
	_spawn_enemy(fire, spawn_position)
	fire.configure()
	fire.set_gameplay_active(true)


func _on_boss_projectile_requested(kind: int, spawn_position: Vector2, direction: int) -> void:
	match kind:
		World5BossProjectile.Kind.SPRAY:
			get_node("/root/AudioManager").play_sfx("fireyflame")
		World5BossProjectile.Kind.SLASH_STRAIGHT, World5BossProjectile.Kind.SLASH_RISING:
			get_node("/root/AudioManager").play_sfx("fireslash")
	var projectile: World5BossProjectile = BossProjectileScript.new()
	_spawn_enemy(projectile, spawn_position)
	projectile.z_index = 9 if kind == World5BossProjectile.Kind.SPRAY or kind == World5BossProjectile.Kind.HADOUKEN else 10
	projectile.configure(kind, direction)
	projectile.set_gameplay_active(true)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: World5CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)


func _on_card_holder_opened(spawn_position: Vector2, card_id: int) -> void:
	if not progress.has_card(card_id):
		_spawn_card(spawn_position, card_id, true)


func _damage_stage_object_in_rect(rect: Rect2, damage: int, _weapon_id: int = 1) -> bool:
	if is_instance_valid(card_holder) and card_holder.projectile_mask_overlap(rect):
		card_holder.take_projectile_hit(damage)
		return true
	return false


func _set_gameplay_active(value: bool) -> void:
	super._set_gameplay_active(value)
	for lava in lava_strips:
		if is_instance_valid(lava):
			lava.set_gameplay_active(value)


func _before_player_death() -> void:
	boss_health_was_visible_on_death = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO


func _build_background() -> void:
	var fill := ColorRect.new()
	fill.position = Vector2.ZERO
	fill.size = Vector2(map_config["width"] * 20, map_config["height"] * 20)
	fill.color = Color8(47, 128, 255) if map_number == 50 else Color8(48, 16, 31)
	fill.mouse_filter = Control.MOUSE_FILTER_IGNORE
	fill.z_index = -200
	add_child(fill)
	var positions: Array[Vector2] = []
	match map_number:
		50:
			positions = [Vector2(-100, 0), Vector2(-100, 520), Vector2(-100, 1040)]
		51:
			positions = [Vector2(-600, 0)]
		52:
			positions = [Vector2(0, -80)]
	for sprite_position in positions:
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = STAGE5_BACKGROUND
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
			displayed_boss_hp = clampi(int((state_ticks - 92) / 4.0), 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)


func _stage_complete_message() -> String:
	return "FIFTH STAGE COMPLETE\n\nPRESS R TO REPLAY"
