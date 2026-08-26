extends Node

var failures := 0


func _ready() -> void:
	call_deferred("_run")


func _run() -> void:
	var progress = get_node("/root/SakuraProgress")
	progress.boss_checkpoint = false
	await _check_global_and_world1(progress)
	await _check_world2()
	if failures == 0:
		print("TUNING_SMOKE_OK")
	get_tree().quit(failures)


func _check_global_and_world1(progress: Node) -> void:
	var between_stage = load("res://scenes/map11.tscn").instantiate()
	add_child(between_stage)
	await get_tree().process_frame
	between_stage.set_physics_process(false)
	_check(not between_stage.hud.ready_image.visible, "no READY graphic between World 1 maps")
	between_stage.player.take_damage(1)
	_check(between_stage.player.immunity_ticks == 80, "damage immunity duration")
	var turret_extra_lives := 0
	var turret_medium_drops := 0
	var drop_turret := GreenTurretEnemy.new()
	for roll in range(100):
		var drop_type := drop_turret._drop_for_roll(roll)
		if drop_type == SakuraEnemy.DropType.EXTRA_LIFE:
			turret_extra_lives += 1
		elif drop_type == SakuraEnemy.DropType.MEDIUM:
			turret_medium_drops += 1
	_check(turret_extra_lives == 10 and turret_medium_drops == 25, "turret drop percentages")
	drop_turret.free()
	var portal_texture_count := 0
	for child in between_stage.get_children():
		if child is Sprite2D and (child.texture == between_stage.portal_back.texture or child.texture == between_stage.portal_front.texture):
			portal_texture_count += 1
	_check(portal_texture_count == 2, "no ordinary exit portal marker")
	var enemy: SakuraEnemy = between_stage.enemies[0]
	between_stage._on_enemy_defeated(enemy, enemy.position, enemy.position, SakuraEnemy.DropType.SMALL)
	var recovery: RecoveryPickup
	for child in between_stage.get_children():
		if child is RecoveryPickup:
			recovery = child
	var expected_drop_position := enemy.position + (enemy.body_size - recovery.body_size) * 0.5
	_check(recovery.position == expected_drop_position, "centered enemy recovery")
	_check(is_equal_approx(recovery.FALL_SPEED, 7.5), "recovery fall speed")
	between_stage.player.position = between_stage.map_config["exit"].position
	between_stage.player.grounded = true
	between_stage._update_playing()
	_check(between_stage.stage_state == between_stage.StageState.EXITING and between_stage.player.scripted_animation_active, "animated ordinary map exit")
	remove_child(between_stage)
	between_stage.free()
	await get_tree().process_frame
	var card_specs := {10: [1, true], 11: [1, false], 12: [1, true], 13: [2, false], 14: [1, false]}
	for map_number in card_specs:
		var card_stage = load("res://scenes/map%d.tscn" % map_number).instantiate()
		add_child(card_stage)
		await get_tree().process_frame
		card_stage.set_physics_process(false)
		_check(_count_children(card_stage, World1CardPickup) == card_specs[map_number][0], "map%d card count" % map_number)
		_check(is_instance_valid(card_stage.card_holder) == card_specs[map_number][1], "map%d card holder" % map_number)
		if map_number == 10:
			var animated_card: World1CardPickup
			for child in card_stage.get_children():
				if child is World1CardPickup:
					animated_card = child
					break
			animated_card.set_physics_process(false)
			animated_card.timer = 0
			animated_card.vertical_speed = 0.0
			animated_card.sprite.texture = animated_card.TEXTURES[0]
			for tick in range(2):
				animated_card._physics_process(0.0)
			_check(animated_card.sprite.texture == animated_card.TEXTURES[0], "card animation first-frame hold")
			for tick in range(2):
				animated_card._physics_process(0.0)
			_check(animated_card.sprite.texture == animated_card.TEXTURES[1], "card animation half speed")
			card_stage.card_holder.take_projectile_hit(1)
			_check(_count_children(card_stage, World1CardPickup) == 2, "map10 holder card release")
		remove_child(card_stage)
		card_stage.free()
		await get_tree().process_frame

	var stage = load("res://scenes/map14.tscn").instantiate()
	add_child(stage)
	await get_tree().process_frame
	stage.set_physics_process(false)
	stage.state_ticks = 50
	stage._update_entry_visual()
	_check(not stage.portal_back.visible and not stage.portal_front.visible, "no normal map14 entry portal")
	stage.intermission_active = true
	stage._update_entry_visual()
	_check(stage.portal_back.visible and stage.portal_front.visible, "checkpoint revival portal")
	stage.intermission_active = false
	stage._begin_intermission_entry()
	for tick in range(10):
		stage._update_intermission_entry()
	_check(is_equal_approx(stage.boss_doors[0].position.y, 230.0), "half-open boss door after ten ticks")
	for tick in range(10):
		stage._update_intermission_entry()
	_check(is_equal_approx(stage.boss_doors[0].position.y, 180.0), "fully open boss door after twenty ticks")
	for tick in range(61):
		stage._update_intermission_entry()
	_check(stage.stage_state == stage.StageState.INTERMISSION and progress.boss_checkpoint, "first boss checkpoint door completion")
	_check(stage.camera_lock_position == Vector2(2440, 320), "lower first boss checkpoint camera")
	stage.player.position = Vector2(2690, 300)
	stage._begin_boss_intro()
	for tick in range(255):
		stage._update_boss_intro()
	stage._update_camera()
	_check(stage.player.position == Vector2(3120, 300) and stage.camera.position == Vector2(3140, 320), "first boss camera handoff")
	var turret_shot := EnemyProjectile.new()
	turret_shot.position = Vector2(3200, 100)
	turret_shot.lifetime = 1
	turret_shot.setup(stage.terrain, stage.player, 1)
	stage.add_child(turret_shot)
	turret_shot.set_physics_process(false)
	turret_shot._physics_process(0.0)
	_check(turret_shot.exploded and _count_children(stage, TurretShotExplosion) == 1, "turret shot limit explosion")
	var hit_shot := EnemyProjectile.new()
	hit_shot.position = stage.player.position
	hit_shot.setup(stage.terrain, stage.player, 1)
	stage.add_child(hit_shot)
	hit_shot.set_physics_process(false)
	hit_shot._physics_process(0.0)
	_check(hit_shot.exploded and _count_children(stage, TurretShotExplosion) == 2, "turret shot hit explosion")
	var slow_explosion := TurretShotExplosion.new()
	stage.add_child(slow_explosion)
	slow_explosion.set_physics_process(false)
	slow_explosion._physics_process(0.0)
	_check(slow_explosion.sprite.texture == slow_explosion.FRAMES[0], "turret explosion first-frame hold")
	slow_explosion._physics_process(0.0)
	_check(slow_explosion.sprite.texture == slow_explosion.FRAMES[1], "turret explosion second frame timing")
	for tick in range(4):
		slow_explosion._physics_process(0.0)
	_check(slow_explosion.sprite.texture == slow_explosion.FRAMES[2], "turret explosion third frame timing")
	stage.remove_child(slow_explosion)
	slow_explosion.free()
	var range_shot := DefaultProjectile.new()
	range_shot.position = stage.player.position + Vector2(472, -200)
	range_shot.setup(stage.terrain, stage.player, stage, 1)
	stage.add_child(range_shot)
	range_shot.set_physics_process(false)
	range_shot._physics_process(0.0)
	_check(range_shot.ending and range_shot.MAX_PLAYER_DISTANCE == 480.0, "player shot 480-pixel range")
	var falling_block := BossRoomBlock.new()
	falling_block.position = Vector2(3000, 380)
	stage.add_child(falling_block)
	falling_block.configure(false)
	falling_block.set_physics_process(false)
	falling_block.activate(0)
	for tick in range(8):
		falling_block._physics_process(0.0)
	_check(falling_block.position.y == 404.0 and _count_children(stage, TurretShotExplosion) == 4, "slower boss blocks with turret explosions")
	var fill_boss := FirstStageBoss.new()
	stage.add_child(fill_boss)
	fill_boss.configure()
	fill_boss.set_physics_process(false)
	fill_boss.state = FirstStageBoss.BossState.HOVERING
	stage.boss = fill_boss
	stage.boss_spawn_started = true
	stage.boss_meter_ticks = 0
	stage.boss_meter_fill_phase = 0
	for tick in range(59):
		stage._update_boss_intro()
	_check(stage.boss_meter_ticks == 29, "first boss health fill half speed")
	stage._update_boss_intro()
	_check(stage.boss_meter_ticks == 30, "first boss health fill completion")
	stage.remove_child(fill_boss)
	fill_boss.free()
	stage.boss = null
	var boss := FirstStageBoss.new()
	boss.position = Vector2(3000, 100)
	stage.add_child(boss)
	boss.configure()
	boss.set_physics_process(false)
	boss.state = FirstStageBoss.BossState.DASHING
	boss.dash_direction = 1
	boss._update_enemy()
	_check(is_equal_approx(boss.position.x, 3010.0) and boss.sprite.texture == boss.FLY_TEXTURE, "first boss dash speed and single flight sprite")
	stage.boss = boss
	stage.boss_spawn_started = true
	stage.stage_state = stage.StageState.DYING
	stage._update_hud()
	_check(stage.hud.boss_meter.visible, "boss meter visible on player death")
	var feather := BossFeather.new()
	feather.position = Vector2(3200, 100)
	feather.setup(stage.terrain, stage.player, 1)
	stage.add_child(feather)
	feather.set_physics_process(false)
	_check(boss.process_mode == Node.PROCESS_MODE_PAUSABLE and feather.process_mode == Node.PROCESS_MODE_PAUSABLE, "first boss and feathers pause with tree")
	var feather_start_x := feather.position.x
	feather._physics_process(0.0)
	_check(absf(feather.position.x - feather_start_x - 40.0 / 3.0) < 0.01, "first boss feather speed")
	stage.player.position = Vector2(3200, 300)
	stage.player.facing = -1
	stage.player.visible = true
	stage._on_boss_reward_collected()
	_check(stage.departure_target_player_position == Vector2(3160, 300), "first boss portal follows facing at close range")
	stage.departure_ticks = 39
	var departure_start_x: float = stage.player.position.x
	stage._update_departure()
	_check(is_equal_approx(stage.player.position.x, departure_start_x - 2.0) and stage.player.visible, "player walks into first boss portal")
	stage._on_player_died()
	var death_effect: PlayerDeathEffect
	for child in stage.get_children():
		if child is PlayerDeathEffect:
			death_effect = child
	_check(death_effect.position == stage.player.get_center(), "centered player death effect")
	var shot := DefaultProjectile.new()
	shot.position = Vector2(100, 100)
	stage.add_child(shot)
	shot.set_physics_process(false)
	shot._end()
	_check(shot.ending and shot.position == Vector2(95, 95) and shot.sprite.texture == shot.HIT_TEXTURES[0], "player shot impact animation")
	remove_child(stage)
	stage.free()
	await get_tree().process_frame

	var bird := PirikitoEnemy.new()
	add_child(bird)
	bird.configure()
	bird.set_physics_process(false)
	var bird_start_y := bird.position.y
	bird._update_enemy()
	_check(is_equal_approx(bird.position.y - bird_start_y, 0.1875), "pirikito speed")
	for tick in range(44):
		bird._update_enemy()
	var descent_end_y := bird.position.y
	bird._update_enemy()
	var first_rise_y := bird.position.y
	bird._update_enemy()
	_check(first_rise_y < descent_end_y and bird.position.y < first_rise_y, "pirikito rising cycle")
	for tick in range(29):
		bird._update_enemy()
	_check(bird.timer == 0 and is_equal_approx(bird.position.y, bird.base_y), "pirikito cycle reset")
	remove_child(bird)
	bird.free()
	var pumpkin := PumpkinEnemy.new()
	add_child(pumpkin)
	pumpkin.configure(0)
	pumpkin.set_physics_process(false)
	pumpkin.take_projectile_hit(1)
	_check(pumpkin.hit_points == 1 and pumpkin.hit_flash_ticks == 0, "pumpkin stun without damage flash")
	remove_child(pumpkin)
	pumpkin.free()
	progress.boss_checkpoint = false


func _check_world2() -> void:
	var stage = load("res://scenes/map20.tscn").instantiate()
	add_child(stage)
	await get_tree().process_frame
	stage.set_physics_process(false)
	_check(stage.STAGE2_ATLAS.get_size() == Vector2(120, 60), "world2 terrain atlas")
	_check(stage.hud.ready_image.visible, "READY graphic at World 2 entrance")
	var ghost: GhostEnemy = stage.enemies[0]
	ghost.set_physics_process(false)
	_check(ghost.update_interval_ticks == 2, "world2 half-rate enemy updates")
	stage.player.position = ghost.position + Vector2(100, 0)
	ghost.set_gameplay_active(true)
	ghost._physics_process(0.0)
	_check(ghost.action_state == 0, "world2 skipped update tick")
	ghost._physics_process(0.0)
	_check(ghost.action_state == 1, "world2 active update tick")
	remove_child(stage)
	stage.free()
	var between_stage = load("res://scenes/map21.tscn").instantiate()
	add_child(between_stage)
	await get_tree().process_frame
	between_stage.set_physics_process(false)
	_check(not between_stage.hud.ready_image.visible, "no READY graphic between World 2 maps")
	remove_child(between_stage)
	between_stage.free()


func _count_children(parent: Node, script_class: Variant) -> int:
	var count := 0
	for child in parent.get_children():
		if is_instance_of(child, script_class):
			count += 1
	return count


func _check(condition: bool, label: String) -> void:
	if not condition:
		failures += 1
		push_error("TUNING_SMOKE_FAILED: %s" % label)
