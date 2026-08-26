extends Node

var failures := 0


func _ready() -> void:
	call_deferred("_run")


func _run() -> void:
	var progress = get_node("/root/SakuraProgress")
	progress.cards.clear()
	progress.third_boss_checkpoint = false
	var specs := {
		30: [Vector2(10000, 600), 20],
		31: [Vector2(2000, 1600), 25],
		32: [Vector2(6000, 640), 18],
	}
	for map_number in specs:
		var stage = load("res://scenes/map%d.tscn" % map_number).instantiate()
		add_child(stage)
		await get_tree().process_frame
		stage.set_physics_process(false)
		_check(stage.terrain.world_size == specs[map_number][0], "map%d world size" % map_number)
		_check(stage.terrain.cells.size() == stage.map_config["height"], "map%d row count" % map_number)
		for child in stage.get_children():
			if child is World3CardPickup:
				_check(child.ANIMATION_TICK_SCALE == 2, "map%d card animation scale" % map_number)
				break
		_check(stage.enemies.size() == specs[map_number][1], "map%d enemy count" % map_number)
		_check(_count_children(stage, World3CardPickup) == 2, "map%d card count" % map_number)
		_check(stage.background_sprites.size() == 4, "map%d background grid" % map_number)
		_check(stage.hud.ready_image.visible == (map_number == 30), "map%d READY visibility" % map_number)
		if map_number == 30:
			_check(is_instance_valid(stage.card_holder), "map30 card holder")
			stage.state_ticks = 20
			stage._update_entry_visual()
			_check(stage.entry_effect.visible, "map30 entrance portal")
		else:
			stage.state_ticks = 20
			stage._update_entry_visual()
			_check(not stage.entry_effect.visible, "map%d no between-map portal" % map_number)
		remove_child(stage)
		stage.free()
		await get_tree().process_frame
	await _check_ordinary_behaviors(progress)
	await _check_boss_flow(progress)
	if failures == 0:
		print("STAGE3_SMOKE_OK")
	get_tree().quit(failures)


func _check_ordinary_behaviors(progress: Node) -> void:
	progress.cards.clear()
	var stage = load("res://scenes/map30.tscn").instantiate()
	add_child(stage)
	await get_tree().process_frame
	stage.set_physics_process(false)
	var turret: World3WallTurret
	var machine: World3Machine
	var orange: World3Orange
	var shocker: World3Shocker
	for enemy in stage.enemies:
		if enemy is World3WallTurret and turret == null:
			turret = enemy
		elif enemy is World3Machine and machine == null:
			machine = enemy
		elif enemy is World3Orange and orange == null:
			orange = enemy
		elif enemy is World3Shocker and shocker == null:
			shocker = enemy
	var projectile_count := _count_children(stage, World3Projectile)
	turret.timer = 50
	turret._update_enemy()
	_check(_count_children(stage, World3Projectile) == projectile_count + 2, "wall turret paired shots")
	projectile_count = _count_children(stage, World3Projectile)
	machine.timer = 50
	machine._update_enemy()
	_check(_count_children(stage, World3Projectile) >= projectile_count + 1, "machine attack")
	projectile_count = _count_children(stage, World3Projectile)
	shocker.timer = 15
	shocker._update_enemy()
	_check(_count_children(stage, World3Projectile) == projectile_count + 1, "shocker charge")
	var charge: World3Projectile
	for child in stage.get_children():
		if child is World3Projectile and child.kind == World3Projectile.Kind.SHOCK_CHARGE:
			charge = child
	charge.timer = 15
	charge._physics_process(0.0)
	_check(_has_projectile_kind(stage, World3Projectile.Kind.SHOCK_BALL), "shocker moving ball")
	stage.player.position = orange.position + Vector2(100, 0)
	orange.timer = 8
	projectile_count = _count_children(stage, World3Projectile)
	orange._update_enemy()
	_check(_count_children(stage, World3Projectile) == projectile_count + 1, "orange aimed shot")
	stage.card_holder.take_projectile_hit(1)
	_check(stage.card_holder.opened_state and _count_children(stage, World3CardPickup) == 3, "card holder release")
	var plus_position := _find_token(stage.terrain, "+")
	if plus_position.x >= 0:
		_check(stage.terrain.rect_hits_solid(Rect2(plus_position, Vector2(1, 20))), "thin wall collision")
		_check(not stage.terrain.rect_hits_solid(Rect2(plus_position + Vector2(2, 0), Vector2(17, 20))), "thin wall width")
	remove_child(stage)
	stage.free()


func _check_boss_flow(progress: Node) -> void:
	progress.cards.clear()
	progress.third_boss_checkpoint = false
	progress.third_boss_reward = false
	var stage = load("res://scenes/map32.tscn").instantiate()
	add_child(stage)
	await get_tree().process_frame
	stage.set_physics_process(false)
	stage._begin_checkpoint_entry()
	for tick in range(81):
		stage._update_checkpoint_entry()
	_check(stage.stage_state == stage.StageState.CHECKPOINT, "map32 checkpoint entry")
	_check(progress.third_boss_checkpoint, "map32 checkpoint persistence")
	stage.player.position = Vector2(5290, 400)
	stage.player.facing = 1
	stage._update_checkpoint()
	_check(stage.stage_state == stage.StageState.BOSS_ENTRY, "map32 second door trigger")
	for tick in range(81):
		stage._update_boss_entry()
	_check(stage.stage_state == stage.StageState.BOSS_INTRO, "map32 boss-room entry")
	for tick in range(98):
		stage._update_boss_intro()
	_check(stage.stage_state == stage.StageState.BOSS, "thunder boss intro")
	_check(stage.boss.state == ThirdStageBoss.BossState.FLICKER, "thunder boss activation")
	for tick in range(110):
		stage.boss._update_enemy()
		if stage.boss.state == ThirdStageBoss.BossState.HIGH_ATTACK:
			break
	_check(stage.boss.state == ThirdStageBoss.BossState.HIGH_ATTACK, "thunder dash and takeoff cycle")
	stage.boss.state = ThirdStageBoss.BossState.TAKEOFF
	stage.boss.timer = 33
	stage.boss.hit_points = 16
	stage.boss._update_enemy()
	_check(stage.boss.state == ThirdStageBoss.BossState.HIGH_ATTACK, "thunder high-health attack selection")
	var projectile_count := _count_children(stage, World3Projectile)
	for tick in range(25):
		stage.boss._update_enemy()
	_check(_count_children(stage, World3Projectile) >= projectile_count + 5, "thunder lightning and shock balls")
	stage.boss.state = ThirdStageBoss.BossState.LOW_ATTACK
	stage.boss.timer = 25
	projectile_count = _count_children(stage, World3Projectile)
	stage.boss._update_enemy()
	_check(_count_children(stage, World3Projectile) == projectile_count + 2, "thunder low-health beam pair")
	stage.boss.state = ThirdStageBoss.BossState.FLICKER
	stage.boss.hit_points = 1
	stage.boss.take_projectile_hit(1)
	_check(stage.stage_state == stage.StageState.VICTORY, "thunder boss defeat")
	stage._spawn_boss_reward()
	stage._on_boss_reward_collected()
	for tick in range(136):
		stage._update_departure()
	_check(progress.has_card(2), "third boss reward card")
	_check(progress.third_boss_reward, "third boss reward persistence")
	_check(not progress.third_boss_checkpoint, "third boss checkpoint cleared")
	_check(stage.stage_state == stage.StageState.COMPLETE, "third stage completion")
	remove_child(stage)
	stage.free()


func _has_projectile_kind(parent: Node, kind: int) -> bool:
	for child in parent.get_children():
		if child is World3Projectile and child.kind == kind:
			return true
	return false


func _find_token(terrain: SakuraTerrain, token: String) -> Vector2:
	for y in range(terrain.cells.size()):
		for x in range(terrain.cells[y].size()):
			if terrain.cells[y][x] == token:
				return Vector2(x, y) * SakuraTerrain.TILE_SIZE
	return Vector2(-1, -1)


func _count_children(parent: Node, script_class: Variant) -> int:
	var count := 0
	for child in parent.get_children():
		if is_instance_of(child, script_class):
			count += 1
	return count


func _check(condition: bool, label: String) -> void:
	if not condition:
		failures += 1
		push_error("STAGE3_SMOKE_FAILED: %s" % label)
