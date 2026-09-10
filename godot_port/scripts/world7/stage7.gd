extends "res://scripts/shared/stage_base.gd"

const RedBallScript = preload("res://scripts/world1/red_ball.gd")
const GreenTurretScript = preload("res://scripts/world1/green_turret.gd")
const PirikitoScript = preload("res://scripts/world1/pirikito.gd")
const TurretDeathEffectScript = preload("res://scripts/world1/turret_death_effect.gd")
const GhostScript = preload("res://scripts/world2/ghost.gd")
const GhostMaskScript = preload("res://scripts/world2/ghost_mask.gd")
const MachineScript = preload("res://scripts/world3/machine.gd")
const OrangeScript = preload("res://scripts/world3/orange_enemy.gd")
const MachineDeathEffectScript = preload("res://scripts/world3/machine_death_effect.gd")
const OysterScript = preload("res://scripts/world4/oyster.gd")
const OysterLowerScript = preload("res://scripts/world4/oyster_lower.gd")
const OysterPearlScript = preload("res://scripts/world4/oyster_pearl.gd")
const FlamemetScript = preload("res://scripts/world5/flamemet.gd")
const FallingFireScript = preload("res://scripts/world5/falling_fire.gd")
const IceMetScript = preload("res://scripts/world6/ice_met.gd")
const IceNeedleScript = preload("res://scripts/world6/ice_needle.gd")
const IcePumpkinScript = preload("res://scripts/world6/ice_pumpkin.gd")
const SeahorseSpawnerScript = preload("res://scripts/world4/seahorse_spawner.gd")
const SeahorseScript = preload("res://scripts/world4/seahorse.gd")
const STAGE7_ATLAS := preload("res://assets/world7/terrain.png")
const STAGE7_FINAL_ATLAS := preload("res://assets/world7/terrain_final.png")
const STAGE7_BACKGROUND := preload("res://assets/world7/background.png")
const PORTAL_LABELS := [
	preload("res://assets/world7/portal_label_1.png"), preload("res://assets/world7/portal_label_2.png"),
	preload("res://assets/world7/portal_label_3.png"), preload("res://assets/world7/portal_label_4.png"),
	preload("res://assets/world7/portal_label_5.png"), preload("res://assets/world7/portal_label_6.png"),
]

const SOURCE_RECTS := {
	"2": Vector2i(0, 0), "3": Vector2i(20, 0), "4": Vector2i(40, 0), "5": Vector2i(60, 0), "6": Vector2i(80, 0), "7": Vector2i(100, 0), "8": Vector2i(120, 0), "9": Vector2i(140, 0), "\"": Vector2i(160, 0), "-": Vector2i(180, 0),
	"q": Vector2i(0, 20), "w": Vector2i(20, 20), "e": Vector2i(40, 20), "r": Vector2i(60, 20), "t": Vector2i(80, 20), "y": Vector2i(100, 20), "u": Vector2i(120, 20), "i": Vector2i(140, 20), "o": Vector2i(160, 20), "p": Vector2i(180, 20),
	"a": Vector2i(0, 40), "s": Vector2i(20, 40), "d": Vector2i(40, 40), "f": Vector2i(60, 40), "g": Vector2i(80, 40), "h": Vector2i(100, 40), "j": Vector2i(120, 40), "k": Vector2i(140, 40), "l": Vector2i(160, 40), "n": Vector2i(180, 40),
	"z": Vector2i(0, 60), "x": Vector2i(20, 60), "c": Vector2i(40, 60), "v": Vector2i(60, 60), "b": Vector2i(80, 60), "H": Vector2i(100, 60), "J": Vector2i(120, 60), "K": Vector2i(140, 60), "L": Vector2i(160, 60), "N": Vector2i(180, 60),
	",": Vector2i(0, 80), "<": Vector2i(20, 80), ">": Vector2i(40, 80), ":": Vector2i(60, 80), ".": Vector2i(80, 80), "Y": Vector2i(100, 80), "U": Vector2i(120, 80), "I": Vector2i(140, 80), "O": Vector2i(160, 80), "P": Vector2i(180, 80),
	"!": Vector2i(0, 100), "@": Vector2i(20, 100), "#": Vector2i(40, 100), "$": Vector2i(60, 100), "%": Vector2i(80, 100), "(": Vector2i(100, 100), ")": Vector2i(120, 100), "_": Vector2i(140, 100),
	"Q": Vector2i(0, 120), "W": Vector2i(20, 120), "E": Vector2i(40, 120), "R": Vector2i(60, 120), "T": Vector2i(80, 120), "{": Vector2i(100, 120), "}": Vector2i(120, 120), "+": Vector2i(140, 120),
	"A": Vector2i(0, 140), "S": Vector2i(20, 140), "D": Vector2i(40, 140), "F": Vector2i(60, 140), "G": Vector2i(80, 140), ";": Vector2i(100, 140), "*": Vector2i(120, 140), "=": Vector2i(140, 140),
	"Z": Vector2i(0, 160), "X": Vector2i(20, 160), "C": Vector2i(40, 160), "V": Vector2i(60, 160), "B": Vector2i(80, 160), "&": Vector2i(100, 160), "|": Vector2i(120, 160), "`": Vector2i(140, 160),
	"[": Vector2i(0, 180), "^": Vector2i(20, 180), "?": Vector2i(40, 180), "/": Vector2i(60, 180), "]": Vector2i(80, 180), "~": Vector2i(100, 180), "m": Vector2i(120, 180), "M": Vector2i(140, 180),
}
const SOLID_TOKENS := ["2", "3", "4", "5", "6", "7", "8", "9", "\"", "-", "s", "d", "f", "x", "c", "v", "!", "@", "#", "$", "%", "S", "D", "F", "X", "C", "V", "j", "k", "l", "J", "K", "L", "(", ")", "_", ";", "*", "=", "&", "|", "`"]
const MAP_CONFIGS := {
	70: {"width": 500, "height": 36, "start": Vector2(100, 460), "exit": Rect2(9920, 120, 80, 480), "next": 71},
	71: {"width": 500, "height": 40, "start": Vector2(0, 280), "exit": Rect2(9920, 160, 80, 480), "next": 72},
	72: {"width": 750, "height": 40, "start": Vector2(0, 480), "exit": Rect2(14920, 80, 80, 520), "next": 73},
	73: {"width": 150, "height": 80, "start": Vector2(0, 240), "exit": Rect2(), "next": 0},
}
const SPAWNS := {
	70: [[14,1380,340,0],[14,1460,300,-15],[14,2700,240,0],[10,1660,460,0],[10,1920,460,1],[12,2100,320,0],[15,5200,300,0],[15,5820,200,0],[15,6280,620,0],[21,7520,510,0],[21,8420,390,0],[21,9820,310,0],[23,7600,300,0],[23,7820,300,0],[23,9060,180,0],[23,9420,100,0]],
	71: [[23,820,140,0],[23,1160,140,0],[21,1460,450,0],[33,2200,573,0],[33,3100,653,0],[33,4570,573,0],[33,4630,533,0],[33,3960,613,1],[41,5700,407,0],[41,6020,487,0],[41,6800,567,0],[42,6900,320,0],[42,7150,320,1],[42,7500,320,0],[42,7740,320,1],[50,8440,557,0],[55,8840,540,0],[50,9200,557,0]],
	72: [[55,780,580,0],[50,1080,477,0],[55,1400,540,0],[14,2240,420,0],[14,2880,290,0],[14,2960,290,-10],[10,2660,480,0],[10,3100,480,0],[12,3500,340,0],[15,4640,620,0],[15,5590,480,0],[15,6300,340,0],[23,7000,260,0],[23,7560,160,0],[23,8660,300,0],[21,7340,450,0],[21,8540,530,0],[33,10010,693,0],[33,10190,653,0],[33,9330,693,1],[41,11760,527,0],[41,12900,527,1],[41,13200,567,0],[42,11950,440,0],[42,12300,440,1],[42,12660,440,0],[42,12940,440,1],[50,13600,517,0],[50,14000,437,1],[55,14360,360,0]],
}
const PORTALS := [
	[Vector2(60, 1140), 6, 74], [Vector2(540, 1260), 1, 75], [Vector2(1140, 1460), 2, 76],
	[Vector2(1795, 1460), 3, 77], [Vector2(2395, 1260), 4, 78], [Vector2(2875, 1140), 5, 79],
]
const SEAHORSE_SPAWNERS := {
	71: [Vector2(2660, 800), Vector2(3320, 800), Vector2(4400, 800)],
	72: [Vector2(9730, 800), Vector2(10600, 800), Vector2(10680, 800)],
}
const GHOST_MASK_SPAWNERS := {
	70: [{"position": Vector2(5280, 380), "destination": 2600.0, "span": 170}],
	72: [{"position": Vector2(6340, 400), "destination": 4020.0, "span": 200}],
}
const ATLAS_TOGGLE_TOKENS := ["_", "+", "=", "`", "M"]

var portal_sprites: Array[Sprite2D] = []
var seahorse_spawners: Array[World4SeahorseSpawner] = []
var ghost_mask_spawners: Array[Dictionary] = []
var oyster_pearls: Array[World4OysterPearl] = []
var logic_phase := 0
var active_rematch_portal: Sprite2D
var rematch_portal_world := 0
var rematch_return_position := Vector2.ZERO


func _first_map_number() -> int:
	return 70


func _map_configs() -> Dictionary:
	return MAP_CONFIGS


func _setup_terrain() -> void:
	var non_solid := PackedStringArray(["0", "1"])
	for token in SOURCE_RECTS.keys():
		if not SOLID_TOKENS.has(token):
			non_solid.append(token)
	if map_number == 80:
		non_solid.append("2")
		non_solid.append("3")
	terrain.setup("res://maps/map%d.map" % map_number, map_config["width"], map_config["height"], STAGE7_ATLAS, SOURCE_RECTS, non_solid, PackedStringArray(["0"]), {})
	match map_number:
		71:
			terrain.configure_atlas_switching([STAGE7_ATLAS, STAGE7_FINAL_ATLAS], 0, PackedStringArray(ATLAS_TOGGLE_TOKENS), {97: 1})
		72:
			terrain.configure_atlas_switching([STAGE7_ATLAS, STAGE7_FINAL_ATLAS], 1, PackedStringArray(ATLAS_TOGGLE_TOKENS), {97: 0, 445: 1})
		73:
			terrain.configure_atlas_switching([STAGE7_ATLAS, STAGE7_FINAL_ATLAS], 1, PackedStringArray(ATLAS_TOGGLE_TOKENS), {25: 0, 100: 1})
		80:
			terrain.configure_atlas_switching([STAGE7_ATLAS, STAGE7_FINAL_ATLAS], 0, PackedStringArray(), {}, {"2": 0, "3": 1}, PackedStringArray(["2", "3"]))


func _configure_checkpoint() -> void:
	if map_number == 73 and progress.final_stage_return_position != Vector2.ZERO:
		player.position = progress.final_stage_return_position
		progress.final_stage_return_position = Vector2.ZERO


func _enemy_update_interval() -> int:
	return 2


func _spawn_stage_objects() -> void:
	for data in SPAWNS.get(map_number, []):
		_spawn_reused_enemy(data)
	for spawn_position in SEAHORSE_SPAWNERS.get(map_number, []):
		var spawner: World4SeahorseSpawner = SeahorseSpawnerScript.new()
		spawner.position = spawn_position
		add_child(spawner)
		spawner.setup(player)
		spawner.spawn_requested.connect(_on_seahorse_requested)
		seahorse_spawners.append(spawner)
	for source_data in GHOST_MASK_SPAWNERS.get(map_number, []):
		ghost_mask_spawners.append({
			"position": source_data["position"],
			"destination": source_data["destination"],
			"span": source_data["span"],
			"timer": 40,
		})
	if map_number == 73:
		_build_portals()
		_spawn_recovery(Vector2(1500, 1260), SakuraEnemy.DropType.MEDIUM)


func _on_seahorse_requested(spawn_position: Vector2) -> void:
	var seahorse: World4Seahorse = SeahorseScript.new()
	_spawn_enemy(seahorse, spawn_position)
	seahorse.configure(-1000.0)
	seahorse.set_gameplay_active(true)


func _set_gameplay_active(value: bool) -> void:
	super._set_gameplay_active(value)
	for spawner in seahorse_spawners:
		if is_instance_valid(spawner):
			spawner.set_gameplay_active(value)
	for pearl in oyster_pearls:
		if is_instance_valid(pearl):
			pearl.set_gameplay_active(value)


func _spawn_reused_enemy(data: Array) -> void:
	var enemy: SakuraEnemy
	match int(data[0]):
		10:
			enemy = RedBallScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])
		12:
			enemy = GreenTurretScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])
		14:
			enemy = PirikitoScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])
		15:
			enemy = GhostScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
		21:
			enemy = MachineScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])
		23:
			enemy = OrangeScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])
		33:
			var lower: World4OysterLower = OysterLowerScript.new()
			var lower_offset := Vector2(6, 13) if int(data[3]) == 0 else Vector2(1, 13)
			_spawn_enemy(lower, Vector2(data[1], data[2]) + lower_offset)
			lower.configure(data[3])
			var upper: World4Oyster = OysterScript.new()
			_spawn_enemy(upper, Vector2(data[1], data[2]))
			upper.configure(data[3])
			upper.pearl_requested.connect(_on_oyster_pearl_requested)
		41:
			enemy = FlamemetScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3], false)
		42:
			enemy = FlamemetScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3], true)
			enemy.falling_fire_requested.connect(_on_falling_fire_requested)
		50:
			enemy = IceMetScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])
			enemy.needles_requested.connect(_on_ice_needles_requested)
		55:
			enemy = IcePumpkinScript.new()
			_spawn_enemy(enemy, Vector2(data[1], data[2]))
			enemy.configure(data[3])


func _build_portals() -> void:
	for portal_index in range(PORTALS.size()):
		var data: Array = PORTALS[portal_index]
		if progress.rematch_complete(data[1] - 1):
			continue
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = preload("res://assets/player/portal_2.png")
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		sprite.position = data[0]
		sprite.flip_h = portal_index >= 3
		sprite.set_meta("world", data[1])
		sprite.set_meta("map", data[2])
		sprite.set_meta("walk_direction", -1 if portal_index < 3 else 1)
		sprite.z_index = 8
		add_child(sprite)
		portal_sprites.append(sprite)
		var label := Sprite2D.new()
		label.centered = false
		label.texture = PORTAL_LABELS[portal_index]
		label.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		label.position = data[0] + (Vector2(-29, 0) if portal_index < 3 else Vector2(32, 0))
		label.z_index = 9
		add_child(label)


func _physics_process(_delta: float) -> void:
	if _handle_global_input():
		return
	logic_phase = (logic_phase + 1) % 2
	match stage_state:
		StageState.ENTRY:
			_update_entry()
		StageState.PLAYING:
			_update_playing()
		StageState.EXITING:
			_update_exit()
		StageState.DYING:
			_update_death()
	_finish_physics_tick()


func _update_playing() -> void:
	if logic_phase != 0:
		return
	if is_instance_valid(active_rematch_portal):
		_update_rematch_portal_entry()
		return
	_update_ghost_mask_spawners()
	if map_number == 73:
		if progress.all_rematches_complete():
			progress.carried_hp = player.hp
			get_tree().change_scene_to_file("res://scenes/map80.tscn")
			return
		for portal in portal_sprites:
			if is_instance_valid(portal) and Rect2(portal.position, Vector2(70, 100)).intersects(player.get_hit_rect()):
				_begin_rematch_portal_entry(portal)
				return
		return
	var exit_rect: Rect2 = map_config["exit"]
	if exit_rect.intersects(player.get_hit_rect()):
		stage_state = StageState.EXITING
		state_ticks = 0
		_set_gameplay_active(false)
		player.set_scripted_animation_active(true)


func _update_ghost_mask_spawners() -> void:
	for index in range(ghost_mask_spawners.size()):
		var data: Dictionary = ghost_mask_spawners[index]
		if player.position.x >= data["position"].x - 350.0:
			continue
		data["timer"] += 1
		if data["timer"] >= randi_range(41, 50):
			var mask: GhostMaskEnemy = GhostMaskScript.new()
			var spawn_position: Vector2 = data["position"] + Vector2(0, randi_range(0, int(data["span"]) - 1))
			_spawn_enemy(mask, spawn_position)
			mask.configure(-1, data["destination"], 5.0)
			mask.set_gameplay_active(true)
			data["timer"] = 0
		ghost_mask_spawners[index] = data


func _begin_rematch_portal_entry(portal: Sprite2D) -> void:
	active_rematch_portal = portal
	rematch_portal_world = int(portal.get_meta("world"))
	rematch_return_position = portal.position + Vector2(0, 20)
	_set_gameplay_active(false)
	player.set_scripted_animation_active(true)


func _update_rematch_portal_entry() -> void:
	var walk_direction := int(active_rematch_portal.get_meta("walk_direction"))
	var target_x := active_rematch_portal.position.x - 10.0 if walk_direction < 0 else active_rematch_portal.position.x + 35.0
	var difference := target_x - player.position.x
	if absf(difference) > 2.0:
		player.scripted_step(-1 if difference < 0.0 else 1, minf(2.0, absf(difference)))
		return
	player.position.x = target_x
	player.set_scripted_animation_active(false)
	get_node("/root/GameFlow").launch_rematch(rematch_portal_world, rematch_return_position)


func _on_falling_fire_requested(spawn_position: Vector2) -> void:
	var fire: World5FallingFire = FallingFireScript.new()
	_spawn_enemy(fire, spawn_position)
	fire.configure()
	fire.set_gameplay_active(true)


func _on_oyster_pearl_requested(spawn_position: Vector2, shot_direction: int) -> void:
	var pearl: World4OysterPearl = OysterPearlScript.new()
	pearl.position = spawn_position
	pearl.z_index = 9
	add_child(pearl)
	pearl.setup(terrain, player, shot_direction)
	pearl.set_gameplay_active(true)
	oyster_pearls.append(pearl)


func _on_ice_needles_requested(origin: Vector2) -> void:
	var needle_data := [
		[Vector2(0, 22), 0, 0], [Vector2(3, 9), 1, 0], [Vector2(12, 1), 2, 0],
		[Vector2(22, -1), 3, 0], [Vector2(34, 1), 2, 1], [Vector2(41, 9), 1, 1],
		[Vector2(46, 22), 0, 1],
	]
	for data in needle_data:
		var needle: World6IceNeedle = IceNeedleScript.new()
		_spawn_enemy(needle, origin + data[0])
		needle.configure(data[1], data[2])
		needle.set_gameplay_active(true)


func _spawn_enemy_defeat_effect(enemy: SakuraEnemy, effect_position: Vector2) -> void:
	if enemy is GreenTurretEnemy:
		get_node("/root/AudioManager").play_sfx("anim60")
		var turret_effect: TurretDeathEffect = TurretDeathEffectScript.new()
		turret_effect.flip_h = enemy.sprite.flip_h
		turret_effect.position = effect_position
		turret_effect.z_index = 30
		add_child(turret_effect)
	elif enemy is World3Machine:
		get_node("/root/AudioManager").play_sfx("anim60")
		var machine_effect: World3MachineDeathEffect = MachineDeathEffectScript.new()
		machine_effect.position = effect_position
		machine_effect.z_index = 30
		add_child(machine_effect)
	else:
		_spawn_enemy_death(effect_position)


func _build_background() -> void:
	var fill := ColorRect.new()
	fill.size = Vector2(map_config["width"] * 20, map_config["height"] * 20)
	fill.color = Color.BLACK
	fill.z_index = -200
	add_child(fill)
	for index in range(4):
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.texture = STAGE7_BACKGROUND
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		sprite.z_index = -100
		add_child(sprite)
		background_sprites.append(sprite)
	background_sprite = background_sprites[0]


func _update_background() -> void:
	if not is_instance_valid(camera):
		return
	var top_left := camera.position - VIEWPORT_HALF_SIZE
	var sampled := top_left / 5.0
	for index in range(background_sprites.size()):
		background_sprites[index].position = top_left - sampled + Vector2(floorf(sampled.x / 640.0) * 640.0 + index % 2 * 640.0, floorf(sampled.y / 480.0) * 480.0 + int(index / 2.0) * 480.0)


func _update_camera() -> void:
	if not is_instance_valid(camera) or not is_instance_valid(player):
		return
	var center := player.get_center()
	camera.position = Vector2(clampf(center.x, 320.0, maxf(320.0, terrain.world_size.x - 320.0)), clampf(center.y, 240.0, maxf(240.0, terrain.world_size.y - 240.0)))
	_update_background()
