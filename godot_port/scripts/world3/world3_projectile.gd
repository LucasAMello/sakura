class_name World3Projectile
extends Node2D

enum Kind { WALL_SHOT, MISSILE, SHOCK_CHARGE, SHOCK_BALL, BOSS_LIGHTNING, BOSS_BEAM, MACHINE_SHOT, ORANGE_SHOT }
enum ShotDirection { LEFT, RIGHT, DOWN, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT }

const WALL_TEXTURES := [
	preload("res://assets/world3/wall_shot_1.png"),
	preload("res://assets/world3/wall_shot_2.png"),
	preload("res://assets/world3/wall_shot_3.png"),
]
const MISSILE_TEXTURE := preload("res://assets/world3/missile.png")
const CHARGE_TEXTURES := [
	preload("res://assets/world3/shocker_charge_1.png"),
	preload("res://assets/world3/shocker_charge_2.png"),
	preload("res://assets/world3/shocker_charge_3.png"),
	preload("res://assets/world3/shocker_charge_4.png"),
	preload("res://assets/world3/shocker_charge_5.png"),
]
const BALL_TEXTURES := [
	preload("res://assets/world3/shocker_ball_1.png"),
	preload("res://assets/world3/shocker_ball_2.png"),
	preload("res://assets/world3/shocker_ball_3.png"),
	preload("res://assets/world3/shocker_ball_4.png"),
]
const LIGHTNING_TEXTURES := [
	preload("res://assets/world3/boss_lightning_1.png"),
	preload("res://assets/world3/boss_lightning_2.png"),
	preload("res://assets/world3/boss_lightning_3.png"),
	preload("res://assets/world3/boss_lightning_4.png"),
]
const BEAM_TEXTURES := [
	preload("res://assets/world3/boss_beam_1.png"),
	preload("res://assets/world3/boss_beam_2.png"),
	preload("res://assets/world3/boss_beam_3.png"),
]

var terrain: SakuraTerrain
var player: SakuraPlayer
var charge_source: SakuraEnemy
var kind := Kind.WALL_SHOT
var direction := 0
var velocity := Vector2.ZERO
var body_size := Vector2(8, 8)
var damage := 0
var timer := 0
var ending := false
var sprite: Sprite2D
var beam_segments: Array[Sprite2D] = []


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(projectile_kind: Kind, map_terrain: SakuraTerrain, target_player: SakuraPlayer, projectile_direction: int = 0) -> void:
	kind = projectile_kind
	terrain = map_terrain
	player = target_player
	direction = projectile_direction
	match kind:
		Kind.WALL_SHOT, Kind.MACHINE_SHOT, Kind.ORANGE_SHOT:
			get_node("/root/AudioManager").play_sfx_near_player("wts", position, player.position, 1.0, 100.0 / 255.0)
			sprite.texture = WALL_TEXTURES[0]
			velocity = _wall_velocity(direction, kind)
			damage = 2
		Kind.MISSILE:
			get_node("/root/AudioManager").play_sfx_near_player("ewulmissile", position, player.position)
			sprite.texture = MISSILE_TEXTURE
			sprite.region_enabled = true
			sprite.region_rect = Rect2(0, 0, 8, 11)
			body_size = Vector2(25, 13)
			velocity = Vector2(-8, 0)
			damage = 4
		Kind.SHOCK_CHARGE:
			sprite.texture = CHARGE_TEXTURES[0]
			body_size = Vector2.ZERO
			_apply_direction_transform(sprite, direction)
		Kind.SHOCK_BALL:
			get_node("/root/AudioManager").play_sfx_near_player("tiro4", position, player.position)
			sprite.texture = BALL_TEXTURES[0]
			sprite.position = Vector2(-5, -8)
			body_size = Vector2(16, 16)
			velocity = [Vector2(0, 10), Vector2(-10, 0), Vector2(0, -10), Vector2(10, 0)][direction]
			damage = 3
		Kind.BOSS_LIGHTNING:
			get_node("/root/AudioManager").play_sfx("bigthunder")
			sprite.texture = LIGHTNING_TEXTURES[0]
			body_size = Vector2.ZERO
		Kind.BOSS_BEAM:
			get_node("/root/AudioManager").play_sfx("thundersound")
			body_size = Vector2(34, 512)
			damage = 3
			_resolve_beam_strike()
			_build_beam()


func _physics_process(_delta: float) -> void:
	timer += 1
	match kind:
		Kind.WALL_SHOT, Kind.MACHINE_SHOT, Kind.ORANGE_SHOT:
			_update_wall_shot()
		Kind.MISSILE:
			_update_missile()
		Kind.SHOCK_CHARGE:
			_update_charge()
		Kind.SHOCK_BALL:
			_update_ball()
		Kind.BOSS_LIGHTNING:
			_update_lightning()
		Kind.BOSS_BEAM:
			_update_beam()


func _update_wall_shot() -> void:
	if ending:
		if timer == 8:
			sprite.texture = WALL_TEXTURES[2]
		elif timer >= 16:
			queue_free()
		return
	if _move_and_hit(velocity / 4.0):
		_end_wall_shot()
	elif timer >= 120:
		_end_wall_shot()


func _update_missile() -> void:
	if timer < 8:
		sprite.region_rect.size.x = 8.0
	elif timer < 16:
		sprite.region_rect.size.x = 16.0
	else:
		sprite.region_enabled = false
	if timer == 41:
		velocity.x = -22.0
	if timer > 4 and _move_and_hit(velocity / 4.0):
		_end_missile()
	elif timer >= 120:
		_end_missile()


func _end_missile() -> void:
	var explosion := TurretShotExplosion.new()
	explosion.position = position + Vector2(10, -7)
	explosion.z_index = z_index
	explosion.setup(player, -1)
	get_parent().add_child(explosion)
	queue_free()


func _update_charge() -> void:
	if not is_instance_valid(charge_source) or charge_source.defeated_state or charge_source.is_queued_for_deletion():
		queue_free()
		return
	sprite.texture = CHARGE_TEXTURES[int(timer / 4.0) % CHARGE_TEXTURES.size()]
	if timer >= 64:
		var ball := World3Projectile.new()
		ball.position = position + _charge_ball_offset(direction)
		ball.z_index = z_index
		get_parent().add_child(ball)
		ball.setup(Kind.SHOCK_BALL, terrain, player, direction)
		ball.velocity = ball.velocity.normalized() * 20.0
		queue_free()


func _update_ball() -> void:
	sprite.texture = BALL_TEXTURES[timer % BALL_TEXTURES.size()]
	if _move_and_hit(velocity / 4.0) or timer >= 240:
		queue_free()


func _update_lightning() -> void:
	if timer == 4:
		position.x -= 4.0
		sprite.texture = LIGHTNING_TEXTURES[1]
	elif timer == 8:
		position.x -= 14.0
		sprite.texture = LIGHTNING_TEXTURES[2]
	elif timer == 12:
		position.x -= 2.0
		sprite.texture = LIGHTNING_TEXTURES[3]
	elif timer >= 16:
		queue_free()


func _update_beam() -> void:
	if timer == 5:
		_set_beam_texture(BEAM_TEXTURES[1])
	elif timer == 9:
		_set_beam_texture(BEAM_TEXTURES[2])
	elif timer >= 13:
		queue_free()


func _resolve_beam_strike() -> void:
	var stage := get_parent() as StageBase
	for height in range(int(body_size.y)):
		var row := Rect2(position + Vector2(0, height), Vector2(body_size.x, 1))
		var hits_solid := stage.projectile_hits_solid(row) if stage != null else terrain.rect_hits_solid(row)
		if hits_solid:
			body_size.y = height
			break
	if is_instance_valid(player) and Rect2(position, body_size).intersects(player.get_hit_rect()):
		body_size.y = maxf(0.0, player.position.y - position.y)
		player.take_damage(damage)


func _move_and_hit(amount: Vector2) -> bool:
	var steps := maxi(1, ceili(maxf(absf(amount.x), absf(amount.y))))
	var step := amount / float(steps)
	var stage := get_parent() as StageBase
	for _index in range(steps):
		var candidate := Rect2(position + step, body_size)
		var hits_solid := stage.projectile_hits_solid(candidate) if stage != null else terrain.rect_hits_solid(candidate)
		if hits_solid:
			return true
		position += step
		if is_instance_valid(player) and Rect2(position, body_size).intersects(player.get_hit_rect()):
			player.take_damage(damage)
			return true
	return false


func _end_wall_shot() -> void:
	if ending:
		return
	ending = true
	timer = 0
	sprite.texture = WALL_TEXTURES[1]


func _wall_velocity(projectile_direction: int, projectile_kind: Kind) -> Vector2:
	match projectile_kind:
		Kind.WALL_SHOT:
			return {
				ShotDirection.UP_LEFT: Vector2(-15, -15),
				ShotDirection.UP_RIGHT: Vector2(15, -15),
				ShotDirection.DOWN_LEFT: Vector2(-15, 15),
				ShotDirection.DOWN_RIGHT: Vector2(15, 15),
			}.get(projectile_direction, Vector2.ZERO)
		Kind.MACHINE_SHOT:
			return {
				ShotDirection.LEFT: Vector2(-24, 0),
				ShotDirection.RIGHT: Vector2(24, 0),
			}.get(projectile_direction, Vector2.ZERO)
		Kind.ORANGE_SHOT:
			return {
				ShotDirection.DOWN_LEFT: Vector2(-15, 15),
				ShotDirection.DOWN: Vector2(0, 18),
				ShotDirection.DOWN_RIGHT: Vector2(15, 15),
			}.get(projectile_direction, Vector2.ZERO)
	return Vector2.ZERO


func _apply_direction_transform(target: Sprite2D, projectile_direction: int) -> void:
	if projectile_direction == 1:
		target.rotation = PI * 0.5
	elif projectile_direction == 2:
		target.flip_v = true
	elif projectile_direction == 3:
		target.rotation = -PI * 0.5
	if projectile_direction == 1 or projectile_direction == 3:
		var half_size := target.texture.get_size() * 0.5
		target.position = Vector2(-3, 2) + half_size - half_size.rotated(target.rotation)


func _charge_ball_offset(projectile_direction: int) -> Vector2:
	return [Vector2(4, 3), Vector2(-2, 4), Vector2(4, -2), Vector2(3, 2)][projectile_direction]


func _build_beam() -> void:
	sprite.visible = false
	for index in range(4):
		var segment_height := minf(128.0, body_size.y - index * 128.0)
		if segment_height <= 0.0:
			break
		var segment := Sprite2D.new()
		segment.centered = false
		segment.position = Vector2(0, index * 128)
		segment.texture = BEAM_TEXTURES[0]
		segment.region_enabled = true
		segment.region_rect = Rect2(0, 0, 34, segment_height)
		segment.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		add_child(segment)
		beam_segments.append(segment)


func _set_beam_texture(texture: Texture2D) -> void:
	for segment in beam_segments:
		segment.texture = texture
