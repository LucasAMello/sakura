extends Node

var failures := 0


func _ready() -> void:
	call_deferred("_run")


func _run() -> void:
	var progress = get_node("/root/SakuraProgress")
	progress.cards.clear()
	progress.second_boss_checkpoint = false
	var specs := {
		20: [Vector2(2000, 480), 1, 1, 0, 0],
		21: [Vector2(4200, 560), 6, 1, 0, 1],
		22: [Vector2(2400, 1400), 8, 2, 6, 0],
		23: [Vector2(6000, 720), 9, 1, 1, 0],
	}
	for map_number in specs:
		var stage = load("res://scenes/map%d.tscn" % map_number).instantiate()
		add_child(stage)
		await get_tree().process_frame
		stage.set_physics_process(false)
		var expected: Array = specs[map_number]
		_check(stage.terrain.world_size == expected[0], "map%d world size" % map_number)
		_check(stage.terrain.cells.size() == stage.map_config["height"], "map%d row count" % map_number)
		_check(stage.terrain.non_solid_tokens.has("6"), "map%d decorative token collision" % map_number)
		_check(stage.terrain.get_source_rect("6", 0, 0) == Vector2i(80, 40), "map%d even wall background" % map_number)
		_check(stage.terrain.get_source_rect("6", 1, 0) == Vector2i(60, 40), "map%d odd wall background" % map_number)
		_check(stage.enemies.size() == expected[1], "map%d enemy count" % map_number)
		_check(_count_children(stage, CardPickup) == expected[2], "map%d card count" % map_number)
		_check(_count_children(stage, ShadowSpike) == expected[3], "map%d spike count" % map_number)
		_check(_count_children(stage, Stage2Painting) == expected[4], "map%d painting count" % map_number)
		_check(stage.hud.ready_image.visible == (map_number == 20), "map%d READY visibility" % map_number)
		_check(is_instance_valid(stage.background_sprite) == (map_number == 20), "map%d background visibility" % map_number)
		remove_child(stage)
		stage.free()
		await get_tree().process_frame
	await _check_ordinary_behaviors(progress)
	await _check_boss_flow(progress)
	if failures == 0:
		print("STAGE2_SMOKE_OK")
	get_tree().quit(failures)


func _check_ordinary_behaviors(progress: Node) -> void:
	progress.cards.clear()
	var stage = load("res://scenes/map21.tscn").instantiate()
	add_child(stage)
	await get_tree().process_frame
	stage.set_physics_process(false)
	var ghost: GhostEnemy
	var armor: Stage2Armor
	for enemy in stage.enemies:
		if enemy is GhostEnemy and ghost == null:
			ghost = enemy
		elif enemy is Stage2Armor and armor == null:
			armor = enemy
	_check(not is_instance_valid(stage.background_sprite) and stage.background_sprites.is_empty(), "map21 has no background")
	_check(armor.z_index < ghost.z_index, "armor behind enemies")
	stage.player.position = ghost.position + Vector2(100, 0)
	ghost._update_enemy()
	for tick in range(5):
		ghost._update_enemy()
	_check(ghost.action_state == 1 and ghost.position != Vector2(510, 220), "ghost activation and pursuit")
	stage.player.position = ghost.position + Vector2(500, 0)
	var ghost_position := ghost.position
	ghost._update_enemy()
	_check(ghost.position != ghost_position, "ghost momentum while fading")
	stage.player.position = Vector2(0, 300)
	stage.mask_spawners[0]["timer"] = 100
	stage._update_mask_spawners()
	_check(_count_children(stage, GhostMaskEnemy) == 1, "ghost-mask emission")
	var mask: GhostMaskEnemy
	for child in stage.get_children():
		if child is GhostMaskEnemy:
			mask = child
	_check(mask.gameplay_active, "spawned ghost-mask gameplay activation")
	var mask_extra_lives := 0
	var mask_small_drops := 0
	for roll in range(100):
		var drop_type := mask._drop_for_roll(roll)
		if drop_type == SakuraEnemy.DropType.EXTRA_LIFE:
			mask_extra_lives += 1
		elif drop_type == SakuraEnemy.DropType.SMALL:
			mask_small_drops += 1
	_check(mask_extra_lives == 10 and mask_small_drops == 20, "ghost-mask drop percentages")
	var mask_start_x := mask.position.x
	mask._physics_process(0.0)
	mask._physics_process(0.0)
	_check(mask.position.x < mask_start_x, "left-spawned ghost-mask movement")
	for tick in range(4):
		mask._update_enemy()
	_check(mask.sprite.texture == mask.TEXTURES[1], "ghost-mask held animation")
	var recovery_count := _count_children(stage, RecoveryPickup)
	armor.take_projectile_hit(1)
	for tick in range(12):
		armor._update_enemy()
	_check(_count_children(stage, RecoveryPickup) == recovery_count + 1, "armor recovery release")
	for tick in range(6):
		armor._update_enemy()
	_check(armor.action_state == 4 and not armor.projectile_mask_overlap(Rect2(armor.position, armor.body_size)), "armor inert shell")
	var painting: Stage2Painting
	var card: CardPickup
	for child in stage.get_children():
		if child is Stage2Painting:
			painting = child
		elif child is CardPickup:
			card = child
	_check(card.ANIMATION_TICK_SCALE == 2, "World 2 card animation scale")
	stage.player.position = painting.position + Vector2(-21, 0)
	painting._physics_process(0.0)
	_check(not painting.reveal_started and painting.reveal_sprite.region_rect.size.x == 0.0, "painting reveal trigger")
	stage.player.position = painting.position + Vector2(-20, 0)
	painting._physics_process(0.0)
	_check(painting.reveal_started and painting.reveal_sprite.region_rect.size.x == SakuraPlayer.MAX_X_SPEED, "painting reveal speed")
	stage.player.position = painting.position + Vector2(-200, 0)
	for tick in range(24):
		painting._physics_process(0.0)
	_check(painting.reveal_complete and painting.reveal_sprite.region_rect.size.x == 100.0, "painting settled reveal")
	painting._physics_process(0.0)
	_check(painting.reveal_sprite.region_rect.size.x == 100.0, "painting persistent reveal")
	stage.player.position = card.position
	card._physics_process(0.0)
	for tick in range(18):
		card._physics_process(0.0)
	_check(progress.has_card(16), "card fade and persistence")
	remove_child(stage)
	stage.free()
	await get_tree().process_frame
	var spike_stage = load("res://scenes/map22.tscn").instantiate()
	add_child(spike_stage)
	await get_tree().process_frame
	spike_stage.set_physics_process(false)
	var spike: ShadowSpike
	for child in spike_stage.get_children():
		if child is ShadowSpike:
			spike = child
			break
	spike_stage.player.position = spike.position
	spike._physics_process(0.0)
	_check(spike_stage.player.dead, "shadow-spike lethal damage")
	remove_child(spike_stage)
	spike_stage.free()


func _check_boss_flow(progress: Node) -> void:
	progress.cards.clear()
	progress.second_boss_checkpoint = false
	progress.second_boss_reward = false
	var stage = load("res://scenes/map23.tscn").instantiate()
	add_child(stage)
	await get_tree().process_frame
	stage.set_physics_process(false)
	stage.player.position = Vector2(4680, 460)
	stage.player.grounded = true
	stage._begin_checkpoint_entry()
	for tick in range(81):
		stage._update_checkpoint_entry()
	_check(stage.stage_state == stage.StageState.CHECKPOINT, "map23 checkpoint entry")
	_check(progress.second_boss_checkpoint, "map23 checkpoint persistence")
	stage.player.position = Vector2(5270, 460)
	stage.player.facing = 1
	stage._update_checkpoint()
	_check(stage.stage_state == stage.StageState.BOSS_ENTRY, "map23 second door edge trigger")
	for tick in range(81):
		stage._update_boss_entry()
	_check(stage.stage_state == stage.StageState.BOSS_INTRO, "map23 boss-room entry")
	for tick in range(100):
		stage.boss._update_enemy()
		if stage.stage_state == stage.StageState.BOSS:
			break
	_check(stage.stage_state == stage.StageState.BOSS, "second boss intro")
	stage.boss.hit_points = 16
	stage.boss.state = SecondStageBoss.BossState.ACTIVE
	stage.boss.position = Vector2(5700, 250)
	stage.boss.take_projectile_hit(1)
	stage.boss._update_enemy()
	for tick in range(37):
		stage.boss._update_enemy()
	_check(get_tree().get_nodes_in_group("second_boss_clones").size() == 1, "second boss split")
	_check(stage.boss.state == SecondStageBoss.BossState.ACTIVE_SPLIT, "second boss split completion")
	var clone: ShadowClone = get_tree().get_first_node_in_group("second_boss_clones")
	clone.take_projectile_hit(15)
	_check(stage.stage_state == stage.StageState.VICTORY, "second boss defeat")
	stage._spawn_boss_reward()
	stage._on_boss_reward_collected()
	for tick in range(136):
		stage._update_departure()
	_check(progress.has_card(1), "second boss reward card")
	_check(progress.second_boss_reward, "second boss reward persistence")
	_check(not progress.second_boss_checkpoint, "second boss checkpoint cleared")
	_check(stage.stage_state == stage.StageState.COMPLETE, "second stage completion")
	remove_child(stage)
	stage.free()


func _count_children(parent: Node, script_class: Variant) -> int:
	var count := 0
	for child in parent.get_children():
		if is_instance_of(child, script_class):
			count += 1
	return count


func _check(condition: bool, label: String) -> void:
	if not condition:
		failures += 1
		push_error("STAGE2_SMOKE_FAILED: %s" % label)
