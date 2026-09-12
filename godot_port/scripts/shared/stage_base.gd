class_name StageBase
extends Node2D

const TerrainScript = preload("res://scripts/shared/terrain.gd")
const PlayerScript = preload("res://scripts/player/player.gd")
const ProjectileScript = preload("res://scripts/player/projectile.gd")
const WeaponProjectileScript = preload("res://scripts/player/weapon_projectile.gd")
const RecoveryScript = preload("res://scripts/shared/recovery.gd")
const HUDScript = preload("res://scripts/hud/hud.gd")
const PlayerDeathEffectScript = preload("res://scripts/player/death_effect.gd")
const EnemyDeathEffectScript = preload("res://scripts/shared/enemy_death_effect.gd")
const BossExplosionScript = preload("res://scripts/world1/turret_shot_explosion.gd")
const BossLightFlashesScript = preload("res://scripts/shared/boss_light_flashes.gd")

const VIEWPORT_HALF_SIZE := Vector2(320.0, 240.0)

enum StageState {
	ENTRY,
	PLAYING,
	EXITING,
	COMPLETE,
	DYING,
	CHECKPOINT_ENTRY,
	CHECKPOINT,
	BOSS_ENTRY,
	INTERMISSION_ENTRY,
	INTERMISSION,
	BOSS_INTRO,
	BOSS,
	VICTORY,
}

@export var map_number := 0

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
var checkpoint_active := false
var boss_room_active := false
var camera_locked := false
var camera_lock_position := Vector2.ZERO
var transition_camera_start := Vector2.ZERO
var boss_doors: Array[Sprite2D] = []
var boss_reward_position := Vector2.ZERO
var boss_reward_started := false
var boss_reward_homing := false
var departure_ticks := 0
var departure_back: Sprite2D
var departure_front: Sprite2D
var departure_player: Sprite2D
var departure_portal_center := Vector2.ZERO
var departure_target_player_position := Vector2.ZERO
var departure_walk_direction := 1
var pause_column := 0
var pause_row := 0
var pause_page := 0
var pause_option_selection := 0
var pause_binding_index := -1
var victory_target := Vector2.ZERO
var victory_target_set := false

const PAUSE_BINDING_ACTIONS := [
	"move_up", "move_down", "move_right", "move_left", "jump",
	"fire", "weapon_next", "weapon_previous", "pause", "quit",
]


func _init() -> void:
	child_entered_tree.connect(_on_stage_child_entered_tree)


func _on_stage_child_entered_tree(node: Node) -> void:
	if node.process_mode == Node.PROCESS_MODE_INHERIT:
		node.process_mode = Node.PROCESS_MODE_PAUSABLE


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS
	randomize()
	progress = get_node("/root/SakuraProgress")
	_install_input_actions()
	map_config = _map_configs()[map_number]
	_build_background()
	terrain = TerrainScript.new()
	_setup_terrain()
	terrain.z_index = 0
	add_child(terrain)
	player = PlayerScript.new()
	player.name = "Player"
	player.position = map_config["start"]
	_configure_checkpoint()
	player.z_index = 20
	add_child(player)
	player.setup(terrain, progress.maximum_hp())
	player.hp = progress.take_hp(progress.maximum_hp())
	player.lives = progress.lives
	player.set_presentation_hidden(true)
	player.shot_requested.connect(_on_shot_requested)
	player.died.connect(_on_player_died)
	progress.maximum_hp_changed.connect(_on_maximum_hp_changed)
	_spawn_stage_objects()
	_build_entry_portal()
	_build_stage_boss_area()
	_build_camera()
	hud = HUDScript.new()
	add_child(hud)
	hud.update_status(player, _stage_state_label(), enemies.size(), map_number, terrain.world_size)
	hud.set_ready_visible(false)
	_set_gameplay_active(false)
	if (map_number == 80):
		get_node("/root/AudioManager").play_music("memory", true)
	else:
		var music_world := 7 if map_number >= 74 and map_number <= 79 else _world_number()
		get_node("/root/AudioManager").play_music("world%d" % music_world)


func _handle_global_input() -> bool:
	if get_node("/root/GameFlow").transitioning:
		return true
	if Input.is_action_just_pressed("quit") and stage_state != StageState.DYING and not get_tree().paused:
		if _world_number() == 7:
			get_node("/root/GameFlow").leave_final_stage()
		else:
			get_node("/root/GameFlow").complete_elemental_stage(_world_number())
		return true
	if Input.is_action_just_pressed("pause") and stage_state != StageState.DYING and not get_tree().paused:
		pause_column = 0
		pause_row = 0
		pause_page = 0
		pause_option_selection = 0
		pause_binding_index = -1
		_set_paused(not get_tree().paused)
		return true
	if get_tree().paused:
		_handle_pause_input()
		return true
	if Input.is_action_just_pressed("restart"):
		get_tree().reload_current_scene()
		return true
	if Input.is_action_just_pressed("toggle_debug"):
		hud.toggle_debug()
	if OS.is_debug_build() and Input.is_action_just_pressed("toggle_god_mode") and is_instance_valid(progress) and is_instance_valid(player) and not player.dead:
		progress.debug_god_mode = not progress.debug_god_mode
	return false


func _handle_pause_input() -> void:
	if pause_binding_index >= 0:
		return
	if Input.is_action_just_pressed("pause"):
		_set_paused(false)
		return
	if pause_page == 1:
		if Input.is_action_just_pressed("jump") or Input.is_action_just_pressed("quit"):
			pause_page = 0
	elif pause_page == 2:
		_handle_pause_options()
	else:
		_handle_pause_grid()
	if not is_inside_tree() or not get_tree().paused:
		return
	hud.set_pause_selection(pause_column, pause_row, pause_page, pause_option_selection, pause_binding_index, player, get_node("/root/SakuraSettings"), progress)


func _handle_pause_grid() -> void:
	if Input.is_action_just_pressed("move_up"):
		pause_row = wrapi(pause_row - 1, 0, 6)
		_pause_skip_locked(-1)
	elif Input.is_action_just_pressed("move_down"):
		pause_row = wrapi(pause_row + 1, 0, 6)
		_pause_skip_locked(1)
	elif Input.is_action_just_pressed("move_left") and pause_row != 4:
		pause_column = 1 - pause_column
		_pause_skip_locked(-1)
	elif Input.is_action_just_pressed("move_right") and pause_row != 4:
		pause_column = 1 - pause_column
		_pause_skip_locked(1)
	elif Input.is_action_just_pressed("jump"):
		_activate_pause_cell()


func _pause_skip_locked(direction: int) -> void:
	if pause_row == 4:
		pause_column = 0
	var attempts := 0
	while not _pause_cell_available(pause_column, pause_row) and attempts < 12:
		pause_row = wrapi(pause_row + direction, 0, 6)
		if pause_row == 4:
			pause_column = 0
		attempts += 1


func _pause_cell_available(column: int, row: int) -> bool:
	if row >= 4:
		return true
	var weapons := [[1, 2], [4, 5], [7, 6], [3, 0]]
	var weapon_id: int = weapons[row][column]
	return weapon_id == 0 or progress.is_weapon_unlocked(weapon_id)


func _activate_pause_cell() -> void:
	get_node("/root/AudioManager").play_sfx("accept")
	if pause_row < 4:
		var weapons := [[1, 2], [4, 5], [7, 6], [3, 0]]
		var weapon_id: int = weapons[pause_row][pause_column]
		if weapon_id > 0:
			player.select_weapon(weapon_id)
		else:
			_set_paused(false)
			if _world_number() == 7:
				get_node("/root/GameFlow").leave_final_stage()
			else:
				get_node("/root/GameFlow").complete_elemental_stage(_world_number())
	elif pause_row == 4:
		pause_page = 2
		pause_option_selection = 0
	elif pause_column == 0:
		_set_paused(false)
	else:
		pause_page = 1


func _handle_pause_options() -> void:
	if Input.is_action_just_pressed("move_up"):
		pause_option_selection = wrapi(pause_option_selection - 1, 0, 4)
	elif Input.is_action_just_pressed("move_down"):
		pause_option_selection = wrapi(pause_option_selection + 1, 0, 4)
	elif Input.is_action_just_pressed("move_left"):
		_adjust_pause_option(-1)
	elif Input.is_action_just_pressed("move_right"):
		_adjust_pause_option(1)
	elif Input.is_action_just_pressed("quit"):
		pause_page = 0
	elif Input.is_action_just_pressed("jump"):
		if pause_option_selection == 2:
			pause_binding_index = 0
		elif pause_option_selection == 3:
			pause_page = 0


func _adjust_pause_option(direction: int) -> void:
	var settings := get_node("/root/SakuraSettings")
	if pause_option_selection == 0:
		settings.set_music_volume(clampf(settings.music_volume + direction, 0.0, 1.0))
	elif pause_option_selection == 1:
		settings.set_sfx_volume(settings.sfx_volume + direction / 255.0)


func _unhandled_key_input(event: InputEvent) -> void:
	if not get_tree().paused or pause_binding_index < 0 or not event.pressed or event.echo:
		return
	get_node("/root/SakuraSettings").set_key(PAUSE_BINDING_ACTIONS[pause_binding_index], event.physical_keycode)
	pause_binding_index += 1
	if pause_binding_index >= PAUSE_BINDING_ACTIONS.size():
		pause_binding_index = -1
	hud.set_pause_selection(pause_column, pause_row, pause_page, pause_option_selection, pause_binding_index, player, get_node("/root/SakuraSettings"), progress)
	get_viewport().set_input_as_handled()


func _finish_physics_tick() -> void:
	_prune_enemies()
	_update_camera()
	_update_hud()


func _update_entry() -> void:
	state_ticks += 1
	_update_entry_visual()
	hud.set_ready_visible(_entry_should_show_ready() and state_ticks > 5 and state_ticks < 128)
	var has_portal := _entry_has_portal()
	if state_ticks >= 130 or (not has_portal and state_ticks >= 86):
		portal_back.visible = false
		portal_front.visible = false
		entry_effect.visible = false
		entry_player.visible = false
		player.set_presentation_hidden(false)
		hud.set_ready_visible(false)
		stage_state = _entry_complete_state()
		state_ticks = 0
		_set_gameplay_active(stage_state != StageState.BOSS_INTRO)


func _update_exit() -> void:
	state_ticks += 1
	if state_ticks <= 40:
		player.scripted_step_right(2.0)
		if not player.grounded:
			player.set_scripted_frame(2)
		return
	var next_map: int = map_config["next"]
	stage_state = StageState.COMPLETE
	if next_map > 0:
		progress.store_hp(player.hp)
		get_tree().change_scene_to_file("res://scenes/map%d.tscn" % next_map)
	else:
		hud.show_message(_stage_complete_message())


func _update_death() -> void:
	state_ticks += 1
	if state_ticks < 100 and state_ticks % 20 == 0:
		get_node("/root/AudioManager").play_sfx("die")
	if state_ticks >= 100:
		if progress.game_over_pending:
			get_node("/root/GameFlow").game_over()
		else:
			get_tree().reload_current_scene()


func _start_departure(direction: int = 0) -> void:
	departure_ticks = 1
	departure_walk_direction = player.facing if direction == 0 else direction
	departure_walk_direction = -1 if departure_walk_direction < 0 else 1
	player.facing = departure_walk_direction
	departure_portal_center = player.get_center() + Vector2(departure_walk_direction * 40.0, 0.0)
	var texture_width := player.get_normal_frame_texture(0).get_width()
	var sprite_offset_x := -10.0 if departure_walk_direction < 0 else 0.0
	var target_x := departure_portal_center.x - sprite_offset_x
	if departure_walk_direction < 0:
		target_x -= texture_width
	departure_target_player_position = Vector2(target_x, player.position.y)
	player.set_scripted_animation_active(true)
	departure_back = Sprite2D.new()
	departure_back.centered = false
	departure_back.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	departure_back.z_index = 18
	departure_back.visible = false
	add_child(departure_back)
	departure_player = Sprite2D.new()
	departure_player.centered = false
	departure_player.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	departure_player.z_index = 20
	departure_player.visible = false
	departure_player.region_enabled = true
	add_child(departure_player)
	departure_front = Sprite2D.new()
	departure_front.centered = false
	departure_front.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	departure_front.z_index = 22
	departure_front.visible = false
	add_child(departure_front)


func _move_player_to_boss_departure(world_number: int) -> void:
	if departure_ticks > 0:
		return
	if not victory_target_set:
		victory_target_set = true
		match world_number:
			1:
				if player.position.x >= 3120.0 and player.position.x < 3280.0:
					victory_target = Vector2(3200, 180)
				elif player.position.x >= 3440.0 and player.position.x < 3600.0:
					victory_target = Vector2(3520, 180)
				else:
					victory_target = Vector2(3360, 300)
			2:
				victory_target = Vector2(5480, 460)
			3:
				victory_target = Vector2(5460, 400)
			4:
				victory_target = Vector2(9580, 560)
			5:
				victory_target = Vector2(5420, 2220)
			6:
				if player.position.x >= 3400.0 and player.position.x < 3500.0:
					victory_target = Vector2(3450, 990)
				elif player.position.x >= 3720.0 and player.position.x < 3820.0:
					victory_target = Vector2(3770, 990)
				else:
					victory_target = Vector2(3600, 1020)
	player.position.y = move_toward(player.position.y, victory_target.y, 5.0)
	var distance := victory_target.x - player.position.x
	if absf(distance) >= 4.0:
		player.set_scripted_animation_active(true)
		player.scripted_step(1 if distance > 0.0 else -1, 4.0)
	else:
		player.position.x = victory_target.x
		player.x_speed = 0.0
	if player.position == victory_target:
		player.y_speed = 0.0
		player.grounded = true
		player.walk_tick = 0
		player.set_scripted_animation_active(false)


func _update_departure() -> void:
	departure_ticks += 1
	if departure_ticks < 16:
		_set_departure_portal_frame(preload("res://assets/player/portal_3.png"))
	elif departure_ticks < 24:
		_set_departure_portal_frame(preload("res://assets/player/portal_4.png"))
	elif departure_ticks < 32:
		_set_departure_portal_frame(preload("res://assets/player/portal_5.png"))
	elif departure_ticks < 40:
		_set_departure_portal_frame(preload("res://assets/player/portal_6.png"))
	elif departure_ticks < 87:
		_show_departure_portal()
		_update_departure_player()
	elif departure_ticks < 95:
		_set_departure_portal_frame(preload("res://assets/player/portal_6.png"))
	elif departure_ticks < 103:
		_set_departure_portal_frame(preload("res://assets/player/portal_5.png"))
	elif departure_ticks < 111:
		_set_departure_portal_frame(preload("res://assets/player/portal_4.png"))
	elif departure_ticks < 119:
		_set_departure_portal_frame(preload("res://assets/player/portal_3.png"))
	elif departure_ticks < 136:
		departure_front.visible = false
		departure_back.visible = false
		departure_player.visible = false
		hud.set_completion_fade(float(departure_ticks - 119) / 16.0)
	else:
		stage_state = StageState.COMPLETE
		hud.set_completion_fade(1.0)
		_complete_departure()


func _update_departure_player() -> void:
	player.set_presentation_hidden(true)
	var remaining := (departure_target_player_position.x - player.position.x) * departure_walk_direction
	if remaining > 0.0:
		player.scripted_step(departure_walk_direction, minf(2.0, remaining))
	else:
		player.position.x = departure_target_player_position.x
		player.set_scripted_animation_active(false)
	var sequence_index := int(player.walk_tick / float(SakuraPlayer.ANIMATION_SPEED))
	var frame_index: int = SakuraPlayer.WALK_SEQUENCE[sequence_index]
	departure_player.texture = player.get_normal_frame_texture(frame_index)
	departure_player.flip_h = departure_walk_direction < 0
	var texture_size := departure_player.texture.get_size()
	var sprite_offset_x := -10.0 if departure_walk_direction < 0 else 0.0
	var visual_left := player.position.x + sprite_offset_x
	var visual_right := visual_left + texture_size.x
	var visible_width := 0.0
	var draw_x := visual_left
	if departure_walk_direction > 0:
		visible_width = clampf(departure_portal_center.x - visual_left, 0.0, texture_size.x)
	else:
		visible_width = clampf(visual_right - departure_portal_center.x, 0.0, texture_size.x)
		draw_x = visual_right - visible_width
	departure_player.position = Vector2(draw_x, player.position.y)
	departure_player.region_rect = Rect2(0.0, 0.0, visible_width, texture_size.y)
	departure_player.visible = visible_width > 0.0


func _show_departure_portal() -> void:
	departure_back.visible = true
	departure_front.visible = true
	departure_back.texture = preload("res://assets/player/portal_1.png")
	departure_front.texture = preload("res://assets/player/portal_2.png")
	departure_back.position = departure_portal_center - departure_back.texture.get_size() * 0.5
	departure_front.position = departure_back.position
	departure_back.flip_h = departure_walk_direction > 0
	departure_front.flip_h = departure_walk_direction > 0


func _set_departure_portal_frame(texture: Texture2D) -> void:
	departure_back.visible = false
	departure_player.visible = false
	departure_front.visible = true
	departure_front.texture = texture
	departure_front.position = departure_portal_center - texture.get_size() * 0.5
	departure_front.flip_h = departure_walk_direction > 0


func _begin_checkpoint_entry() -> void:
	stage_state = StageState.CHECKPOINT_ENTRY
	state_ticks = 0
	checkpoint_active = true
	camera_locked = true
	transition_camera_start = camera.position
	camera_lock_position = transition_camera_start
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _begin_boss_entry() -> void:
	stage_state = StageState.BOSS_ENTRY
	state_ticks = 0
	boss_room_active = true
	camera_locked = true
	transition_camera_start = camera.position
	camera_lock_position = transition_camera_start
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _spawn_enemy(enemy: SakuraEnemy, spawn_position: Vector2) -> void:
	enemy.position = spawn_position
	enemy.z_index = 10
	add_child(enemy)
	enemy.setup(terrain, player)
	var update_interval := _enemy_update_interval()
	if update_interval > 1:
		enemy.set_update_interval(update_interval)
	_register_enemy(enemy)


func _register_enemy(enemy: SakuraEnemy) -> void:
	enemies.append(enemy)
	enemy.defeated.connect(_on_enemy_defeated)


func _on_enemy_defeated(enemy: SakuraEnemy, effect_position: Vector2, _drop_position: Vector2, drop_type: int) -> void:
	enemies.erase(enemy)
	_spawn_enemy_defeat_effect(enemy, effect_position)
	if drop_type != SakuraEnemy.DropType.NONE:
		var recovery: RecoveryPickup = RecoveryScript.new()
		recovery.vertical_speed = _recovery_fall_speed()
		recovery.z_index = 12
		add_child(recovery)
		recovery.setup(terrain, player, drop_type)
		recovery.position = enemy.position + (enemy.body_size - recovery.body_size) * 0.5


func _spawn_recovery(spawn_position: Vector2, drop_type: int) -> void:
	var recovery: RecoveryPickup = RecoveryScript.new()
	recovery.vertical_speed = _recovery_fall_speed()
	recovery.position = spawn_position
	recovery.z_index = 12
	add_child(recovery)
	recovery.setup(terrain, player, drop_type)


func _recovery_fall_speed() -> float:
	return RecoveryPickup.FALL_SPEED


func _on_shot_requested(origin: Vector2, direction: int, weapon_id: int) -> void:
	var shot_volume := 205.0 / 255.0 if weapon_id == 1 else 1.0
	get_node("/root/AudioManager").play_sfx("tiro%d" % weapon_id, 1.0, shot_volume)
	if (weapon_id == 1):
		var projectile: ProjectileScript = ProjectileScript.new()
		projectile.position = origin
		projectile.z_index = 15
		add_child(projectile)
		projectile.setup(terrain, player, self, direction)
		projectile.finished.connect(player.projectile_ended.bind(weapon_id), CONNECT_ONE_SHOT)
	else:
		var projectile: WeaponProjectileScript = WeaponProjectileScript.new()
		projectile.position = origin
		projectile.z_index = 15
		add_child(projectile)
		projectile.setup(terrain, player, self, direction, weapon_id)
		if weapon_id != 2:
			projectile.finished.connect(player.projectile_ended.bind(weapon_id), CONNECT_ONE_SHOT)


func _on_maximum_hp_changed(value: int) -> void:
	player.set_maximum_hp(value)
	hud.show_maximum_hp_sparkle(value)
	get_node("/root/AudioManager").play_sfx("sparkle")


func projectile_hits_solid(rect: Rect2) -> bool:
	if terrain.rect_hits_solid(rect):
		return true
	for door in boss_doors:
		if is_instance_valid(door) and door.visible and door.texture != null:
			if Rect2(door.position, door.texture.get_size()).intersects(rect):
				return true
	return false


func damage_enemy_in_rect(rect: Rect2, damage: int, weapon_id: int = 1, water_splash: bool = false) -> bool:
	if weapon_id != 2:
		for projectile in get_tree().get_nodes_in_group("enemy_projectile_blockers"):
			if projectile.get_parent() == self and projectile.blocks_player_projectile(rect, weapon_id, water_splash):
				return true
	if _damage_stage_object_in_rect(rect, damage, weapon_id):
		return true
	for enemy in enemies:
		if is_instance_valid(enemy) and not enemy.defeated_state and enemy.accepts_weapon_hit(weapon_id) and enemy.projectile_mask_overlap(rect):
			if water_splash:
				enemy.take_water_splash_hit()
			else:
				enemy.take_weapon_hit(damage, weapon_id)
			return true
	return false


func damage_enemies_in_rect_once(rect: Rect2, damage: int, weapon_id: int, hit_enemy_ids: Dictionary) -> void:
	_damage_stage_object_in_rect(rect, damage, weapon_id)
	for enemy in enemies.duplicate():
		if not is_instance_valid(enemy) or enemy.defeated_state:
			continue
		var enemy_id: int = enemy.get_instance_id()
		if hit_enemy_ids.has(enemy_id) or not enemy.accepts_weapon_hit(weapon_id):
			continue
		if enemy.projectile_mask_overlap(rect):
			hit_enemy_ids[enemy_id] = true
			enemy.take_weapon_hit(damage, weapon_id)


func _on_player_died() -> void:
	get_node("/root/AudioManager").play_sfx("die")
	_before_player_death()
	stage_state = StageState.DYING
	state_ticks = 0
	_set_gameplay_active(false)
	hud.set_ready_visible(false)
	var effect: PlayerDeathEffect = PlayerDeathEffectScript.new()
	effect.position = player.get_center()
	effect.z_index = 30
	add_child(effect)


func _spawn_enemy_death(effect_position: Vector2) -> void:
	get_node("/root/AudioManager").play_sfx("anim40")
	var effect: EnemyDeathEffect = EnemyDeathEffectScript.new()
	effect.position = effect_position
	effect.z_index = 30
	add_child(effect)


func _spawn_boss_light_flashes(effect_position: Vector2, lifetime_ticks: int = 262) -> void:
	var effect := BossLightFlashesScript.new()
	effect.position = effect_position
	effect.lifetime_ticks = lifetime_ticks
	effect.z_index = 29
	add_child(effect)


func _spawn_boss_explosion(effect_position: Vector2) -> void:
	get_node("/root/AudioManager").play_sfx("anim13")
	var effect: TurretShotExplosion = BossExplosionScript.new()
	effect.position = effect_position - Vector2(TurretShotExplosion.FRAMES[0].get_size()) * 0.5
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
	var has_portal := _entry_has_portal()
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
	return _entry_has_portal()


func _set_entry_player(frame_index: int, revealing: bool) -> void:
	entry_player.visible = true
	entry_player.texture = player.get_normal_frame_texture(frame_index)
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


func _update_hud() -> void:
	hud.update_status(player, _stage_state_label(), enemies.size(), map_number, terrain.world_size)
	_update_boss_hud()


func _stage_state_label() -> String:
	match stage_state:
		StageState.PLAYING:
			return "PLAY"
		StageState.EXITING:
			return "EXIT"
		StageState.COMPLETE:
			return "COMPLETE"
		StageState.DYING:
			return "DEFEATED"
		StageState.CHECKPOINT_ENTRY, StageState.INTERMISSION_ENTRY:
			return "CHECKPOINT ENTRY"
		StageState.CHECKPOINT, StageState.INTERMISSION:
			return "CHECKPOINT"
		StageState.BOSS_ENTRY:
			return "BOSS ENTRY"
		StageState.BOSS_INTRO:
			return "BOSS INTRO"
		StageState.BOSS:
			return "BOSS"
		StageState.VICTORY:
			return "VICTORY"
	return "ENTRY"


func _set_paused(value: bool) -> void:
	if not value and get_tree().paused and Input.is_action_pressed("jump"):
		player.block_jump_until_release()
	get_tree().paused = value
	hud.set_paused(value)
	if value:
		hud.set_pause_selection(pause_column, pause_row, pause_page, pause_option_selection, pause_binding_index, player, get_node("/root/SakuraSettings"), progress)


func _install_input_actions() -> void:
	_bind_key("move_left", KEY_LEFT)
	_bind_key("move_right", KEY_RIGHT)
	_bind_key("jump", KEY_F)
	_bind_key("fire", KEY_D)
	_bind_key("pause", KEY_ENTER)
	_bind_key("restart", KEY_R)
	_bind_key("toggle_debug", KEY_F3)
	if OS.is_debug_build():
		_bind_key("toggle_god_mode", KEY_G)
	_bind_key("quit", KEY_ESCAPE)


func _bind_key(action: StringName, key: Key) -> void:
	if not InputMap.has_action(action):
		InputMap.add_action(action)
	var event := InputEventKey.new()
	event.physical_keycode = key
	if not InputMap.action_has_event(action, event):
		InputMap.action_add_event(action, event)


func _world_number() -> int:
	return clampi(int(map_number / 10.0), 1, 7)


func _is_active_rematch() -> bool:
	return progress.active_rematch_world == _world_number() or progress.has_boss_reward(_world_number() - 1)


func _finish_elemental_or_rematch(world_number: int) -> void:
	if progress.active_rematch_world == world_number:
		progress.store_hp(player.hp)
		get_node("/root/GameFlow").finish_active_rematch()
	else:
		get_node("/root/GameFlow").complete_elemental_stage(world_number)


func _first_map_number() -> int:
	return 0


func _map_configs() -> Dictionary:
	return {}


func _setup_terrain() -> void:
	pass


func _configure_checkpoint() -> void:
	pass


func _spawn_stage_objects() -> void:
	pass


func _build_stage_boss_area() -> void:
	pass


func _build_background() -> void:
	pass


func _update_background() -> void:
	pass


func _update_camera() -> void:
	pass


func _update_boss_hud() -> void:
	pass


func _entry_has_checkpoint() -> bool:
	return checkpoint_active


func _entry_has_portal() -> bool:
	return map_number == _first_map_number() or _entry_has_checkpoint()


func _entry_complete_state() -> StageState:
	return StageState.CHECKPOINT if _entry_has_checkpoint() else StageState.PLAYING


func _stage_complete_message() -> String:
	return "STAGE COMPLETE"


func _enemy_update_interval() -> int:
	return 1


func _spawn_enemy_defeat_effect(_enemy: SakuraEnemy, effect_position: Vector2) -> void:
	_spawn_enemy_death(effect_position)


func _damage_stage_object_in_rect(_rect: Rect2, _damage: int, _weapon_id: int = 1) -> bool:
	return false


func _before_player_death() -> void:
	pass


func _complete_departure() -> void:
	pass
