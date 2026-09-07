extends "res://scripts/shared/stage_base.gd"

const WallTurretScript = preload("res://scripts/world3/wall_turret.gd")
const MachineScript = preload("res://scripts/world3/machine.gd")
const OrangeScript = preload("res://scripts/world3/orange_enemy.gd")
const ShockerScript = preload("res://scripts/world3/shocker.gd")
const CardHolderScript = preload("res://scripts/world3/card_holder.gd")
const CardPickupScript = preload("res://scripts/world3/card_pickup.gd")
const ThirdBossScript = preload("res://scripts/world3/third_boss.gd")
const ThirdBossRewardScript = preload("res://scripts/world3/third_boss_reward.gd")
const MachineDeathEffectScript = preload("res://scripts/world3/machine_death_effect.gd")
const STAGE3_ATLAS := preload("res://assets/world3/terrain.png")
const STAGE3_SOURCE_RECTS := {
	"2": Vector2i(0, 0),
  "3": Vector2i(20, 0),
  "4": Vector2i(40, 0),
	"5": Vector2i(60, 0),
  "6": Vector2i(80, 0),
  "7": Vector2i(20, 20),
	"8": Vector2i(40, 20),
  "9": Vector2i(60, 20),
  "a": Vector2i(0, 40),
	"b": Vector2i(20, 40),
  "c": Vector2i(0, 60),
  "d": Vector2i(20, 60),
	"e": Vector2i(40, 40),
  "f": Vector2i(60, 40),
  "g": Vector2i(40, 60),
	"h": Vector2i(60, 60),
  "i": Vector2i(80, 40),
  "j": Vector2i(100, 40),
	"k": Vector2i(80, 60),
  "l": Vector2i(100, 60),
  "m": Vector2i(100, 80),
	"n": Vector2i(120, 80),
  "o": Vector2i(100, 100),
  "p": Vector2i(120, 100),
	"q": Vector2i(120, 0),
  "r": Vector2i(120, 20),
  "s": Vector2i(120, 40),
	"t": Vector2i(100, 20),
  "u": Vector2i(100, 0),
  "v": Vector2i(0, 80),
	"w": Vector2i(0, 100),
  "x": Vector2i(20, 80),
  "y": Vector2i(20, 100),
	"z": Vector2i(0, 20),
  "/": Vector2i(80, 20),
  "!": Vector2i(40, 80),
	"@": Vector2i(60, 80),
  "#": Vector2i(80, 80),
  "$": Vector2i(40, 100),
	"%": Vector2i(60, 100),
  "*": Vector2i(80, 100),
  "+": Vector2i(120, 60),
	"<": Vector2i(0, 120),
  ">": Vector2i(20, 120),
  ":": Vector2i(40, 120),
	"-": Vector2i(60, 120),
  "_": Vector2i(80, 120),
}
const STAGE3_NON_SOLID := ["0", "1", "+"]

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
		"shockers": [[Vector2(110, 796), 2, 0], [Vector2(876, 680), 1, 0], [Vector2(876, 780), 1, -10], [Vector2(216, 1100), 3, 0], [Vector2(216, 1180), 3, -12], [Vector2(216, 1260), 3, -24], [Vector2(436, 1140), 1, -6], [Vector2(436, 1220), 1, -18], [Vector2(110, 1316), 0, -24], [Vector2(170, 1316), 0, -44], [Vector2(1276, 820), 3, 0], [Vector2(1696, 920), 3, 0]],
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

var card_holder: World3CardHolder
var boss: ThirdStageBoss
var boss_reward: ThirdBossReward
var boss_health_was_visible_on_death := false


func _first_map_number() -> int:
	return 30


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	terrain.setup(
		"res://maps/map%d.map" % map_number,
		map_config["width"],
		map_config["height"],
		STAGE3_ATLAS,
		STAGE3_SOURCE_RECTS,
		PackedStringArray(STAGE3_NON_SOLID),
		PackedStringArray(),
		{}
	)


func _configure_checkpoint() -> void:
	if map_number == 32 and progress.third_boss_checkpoint:
		player.position = Vector2(4840, 400)
		checkpoint_active = true
		camera_locked = true
		camera_lock_position = Vector2(5040, 400)


func _build_stage_boss_area() -> void:
	if map_number == 32:
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
	if map_number == 32:
		if player.position.x >= 4680.0:
			player.position.x = 4680.0
			player.x_speed = minf(player.x_speed, 0.0)
		if player.facing > 0 and player.grounded and player.get_hit_rect().intersects(Rect2(4720, 380, 30, 100), true):
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
		_set_door_opening(0, float(state_ticks) / 40.0)
	elif state_ticks <= 120:
		_set_door_opening(0, 1.0)
		player.scripted_step_right(1.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(5040, 400), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(0, 1.0 - float(state_ticks - 120) / 40.0)
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
	if player.position.x >= 5290.0:
		player.x_speed = minf(player.x_speed, 0.0)
	if player.grounded and player.facing > 0 and player.get_hit_rect().intersects(Rect2(5330, 380, 30, 100), true):
		_begin_boss_entry()


func _update_boss_entry() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		_set_door_opening(1, float(state_ticks) / 40.0)
	elif state_ticks <= 120:
		_set_door_opening(1, 1.0)
		player.scripted_step_right(1.0)
		camera_lock_position = transition_camera_start.lerp(Vector2(5600, 400), float(state_ticks - 40) / 80.0)
	elif state_ticks <= 160:
		_set_door_opening(1, 1.0 - float(state_ticks - 120) / 40.0)
	else:
		_set_door_opening(1, 0.0)
		camera_lock_position = Vector2(5600, 400)
		player.position.y = 400.0
		player.y_speed = 0.0
		player.grounded = true
		player.set_scripted_animation_active(true)
		stage_state = StageState.BOSS_INTRO
		state_ticks = 0
		boss.set_gameplay_active(false)


func _update_boss_intro() -> void:
	state_ticks += 1
	if state_ticks <= 80:
		player.scripted_step_right(2.5)
	elif state_ticks == 81:
		player.set_scripted_animation_active(false)
	elif state_ticks == 97:
		_spawn_boss_projectile(World3Projectile.Kind.BOSS_LIGHTNING, Vector2(5750, 160))
	elif state_ticks == 100:
		hud.set_boss_flash(0.5)
	elif state_ticks == 101:
		hud.set_boss_flash(1.0)
		boss.visible = true
	elif state_ticks == 102:
		hud.set_boss_flash(0.5)
	elif state_ticks == 103:
		hud.set_boss_flash(0.0)
	elif state_ticks >= 108 and state_ticks < 168:
		if (state_ticks - 108) % 2 == 0:
			get_node("/root/AudioManager").play_sfx("recuperator")
	elif state_ticks == 168:
		stage_state = StageState.BOSS
		state_ticks = 0
		player.set_scripted_animation_active(false)
		boss.set_gameplay_active(true)
		boss.start_fight()
		_set_gameplay_active(true)


func _update_boss() -> void:
	player.position.x = clampf(player.position.x, 5360.0, 5920.0)
	if player.position.x <= 5360.0:
		player.x_speed = maxf(player.x_speed, 0.0)


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
	_move_player_to_boss_departure(3)
	state_ticks += 1
	if not boss_reward_started:
		if state_ticks <= 255:
			hud.set_boss_flash(float(state_ticks) / 255.0)
			if state_ticks == 5:
				for burst in range(3):
					_spawn_boss_explosion(boss.position + Vector2(25, 25))
			if state_ticks % 7 == 3 and is_instance_valid(boss):
				_spawn_boss_explosion(boss.position + Vector2(randi_range(0, 50), randi_range(0, 50)))
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
	boss_reward = ThirdBossRewardScript.new()
	boss_reward.position = boss_reward_position
	boss_reward.z_index = 32
	add_child(boss_reward)
	boss_reward.setup(player)
	boss_reward.collected.connect(_on_boss_reward_collected)


func _on_boss_reward_collected() -> void:
	progress.collect_card(2)
	progress.unlock_third_boss_reward()
	_start_departure()


func _complete_departure() -> void:
	progress.set_third_boss_checkpoint(false)
	if get_tree().current_scene == self:
		_finish_elemental_or_rematch(3)


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


func _spawn_enemy_defeat_effect(enemy: SakuraEnemy, effect_position: Vector2) -> void:
	if enemy is World3Machine:
		get_node("/root/AudioManager").play_sfx("anim60")
		var machine_effect: World3MachineDeathEffect = MachineDeathEffectScript.new()
		machine_effect.position = effect_position
		machine_effect.z_index = 30
		add_child(machine_effect)
	else:
		_spawn_enemy_death(effect_position)


func _on_card_holder_opened(drop_position: Vector2, card_id: int) -> void:
	if not progress.has_card(card_id):
		_spawn_card(drop_position, card_id, true)


func _spawn_card(spawn_position: Vector2, card_id: int, falls: bool) -> void:
	var card: World3CardPickup = CardPickupScript.new()
	card.position = spawn_position
	card.z_index = 12
	add_child(card)
	card.setup(terrain, player, card_id, falls)


func _damage_stage_object_in_rect(rect: Rect2, damage: int, _weapon_id: int = 1) -> bool:
	if is_instance_valid(card_holder) and card_holder.projectile_mask_overlap(rect):
		card_holder.take_projectile_hit(damage)
		return true
	return false


func _before_player_death() -> void:
	boss_health_was_visible_on_death = stage_state == StageState.BOSS or stage_state == StageState.BOSS_INTRO
	hud.set_boss_flash(0.0)


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
	if stage_state == StageState.DYING:
		return
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


func _update_boss_hud() -> void:
	var boss_visible := false
	var displayed_boss_hp := 0
	if is_instance_valid(boss):
		boss_visible = stage_state == StageState.BOSS or (stage_state == StageState.BOSS_INTRO and state_ticks >= 108) or (stage_state == StageState.DYING and boss_health_was_visible_on_death)
		displayed_boss_hp = boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_boss_hp = clampi(floori(float(state_ticks - 108) / 2.0) + 1, 0, 30)
	hud.set_boss_health(displayed_boss_hp, boss_visible)
