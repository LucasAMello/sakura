extends "res://scripts/world7/stage7.gd"

const FinalBossScript = preload("res://scripts/world7/final_boss.gd")
const FinalProjectileScript = preload("res://scripts/world7/final_boss_projectile.gd")
const FINAL_CONFIGS := {80: {"width": 125, "height": 30, "start": Vector2(930, 260), "exit": Rect2(), "next": 0}}

var boss: SakuraFinalBoss
var intro_started := false
var victory_ticks := 0


func _first_map_number() -> int:
	return -1


func _map_configs() -> Dictionary:
	return FINAL_CONFIGS


func _entry_complete_state() -> int:
	return StageState.BOSS_INTRO


func _ready() -> void:
	super._ready()
	hud.set_completion_fade(1.0)


func _build_stage_boss_area() -> void:
	boss = FinalBossScript.new()
	_spawn_enemy(boss, Vector2(1215, 276))
	boss.attack_requested.connect(_on_boss_attack_requested)
	boss.flash_requested.connect(_on_boss_flash_requested)
	boss.boss_defeated.connect(_on_boss_defeated)
	boss.set_gameplay_active(false)


func _physics_process(_delta: float) -> void:
	if _handle_global_input():
		return
	match stage_state:
		StageState.ENTRY:
			_update_entry()
		StageState.BOSS_INTRO:
			_update_boss_intro()
		StageState.BOSS:
			player.position.x = clampf(player.position.x, 860.0, 1600.0)
		StageState.VICTORY:
			_update_victory()
		StageState.DYING:
			_update_death()
	_finish_physics_tick()


func _update_boss_intro() -> void:
	state_ticks += 1
	camera_locked = true
	camera_lock_position = Vector2(1250, 300)
	if not intro_started:
		intro_started = true
		get_node("/root/AudioManager").play_music("memory", true)
		boss.set_gameplay_active(true)
		boss.begin_intro()
	if state_ticks <= 64:
		hud.set_completion_fade(1.0 - float(state_ticks) / 64.0)
	elif state_ticks <= 128:
		boss.sprite.modulate.a = 1.0 - float(state_ticks - 64) / 64.0
	elif state_ticks <= 158:
		get_node("/root/AudioManager").play_sfx("recuperator")
	if state_ticks >= 158:
		hud.set_completion_fade(0.0)
		boss.begin_fight()
		stage_state = StageState.BOSS
		_set_gameplay_active(true)


func _on_boss_attack_requested(kind: int, origin: Vector2, direction: int, variant: int) -> void:
	match kind:
		75:
			get_node("/root/AudioManager").play_sfx("lasts")
		77, 78:
			get_node("/root/AudioManager").play_sfx("fireyflame")
		76:
			get_node("/root/AudioManager").play_sfx("thundersound")
		79:
			get_node("/root/AudioManager").play_sfx("tiro7")
	var projectile: FinalBossProjectile = FinalProjectileScript.new()
	projectile.position = origin
	projectile.z_index = 14
	add_child(projectile)
	projectile.configure(player, terrain, kind, direction, variant)


func _on_boss_flash_requested(alpha: float) -> void:
	hud.set_boss_flash(alpha)


func _on_boss_defeated() -> void:
	enemies.erase(boss)
	for projectile in get_tree().get_nodes_in_group("final_boss_projectiles"):
		if is_instance_valid(projectile):
			projectile.queue_free()
	stage_state = StageState.VICTORY
	victory_ticks = 0
	_set_gameplay_active(false)
	hud.set_boss_health(0, false)


func _update_victory() -> void:
	victory_ticks += 1
	_settle_player_for_victory()
	if victory_ticks == 5:
		for _burst in range(3):
			_spawn_boss_explosion(boss.position + Vector2(40, 60))
	if victory_ticks % 7 == 3 and victory_ticks < 210:
		_spawn_boss_explosion(boss.position + Vector2(randi_range(-20, 90), randi_range(-10, 120)))
	if victory_ticks < 255:
		hud.set_boss_flash(float(victory_ticks) / 255.0)
	elif victory_ticks < 315:
		hud.set_boss_flash(1.0)
		if is_instance_valid(boss):
			boss.queue_free()
	else:
		get_node("/root/GameFlow").play_ending()


func _settle_player_for_victory() -> void:
	var target_y := 260.0
	if player.position.x > 1180.0 and player.position.x < 1280.0:
		target_y = 300.0
	elif (player.position.x > 1040.0 and player.position.x < 1140.0) or (player.position.x > 1320.0 and player.position.x < 1420.0):
		target_y = 380.0
	elif (player.position.x > 1080.0 and player.position.x < 1180.0) or (player.position.x > 1280.0 and player.position.x < 1380.0):
		target_y = 140.0
	player.position.y = move_toward(player.position.y, target_y, 5.0)


func _build_background() -> void:
	var fill := ColorRect.new()
	fill.size = Vector2(2500, 600)
	fill.color = Color8(20, 15, 60)
	fill.z_index = -200
	add_child(fill)
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.texture = preload("res://assets/world7/background_final.png")
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite.position = Vector2(865, 0)
	sprite.z_index = -100
	add_child(sprite)
	background_sprite = sprite


func _update_background() -> void:
	pass


func _update_camera() -> void:
	if camera_locked:
		camera.position = camera_lock_position
	else:
		camera.position = Vector2(1250, 300)


func _update_boss_hud() -> void:
	if is_instance_valid(boss):
		var displayed_hp := boss.hit_points
		if stage_state == StageState.BOSS_INTRO:
			displayed_hp = clampi(state_ticks - 128, 0, 30)
		hud.set_boss_health(displayed_hp, stage_state == StageState.BOSS or (stage_state == StageState.BOSS_INTRO and state_ticks >= 129))
