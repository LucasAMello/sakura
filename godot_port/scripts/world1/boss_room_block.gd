class_name BossRoomBlock
extends Node2D

const WIDE_TEXTURE := preload("res://assets/world1/boss_block_wide.png")
const SMALL_TEXTURE := preload("res://assets/world1/boss_block_small.png")
const ExplosionScript = preload("res://scripts/world1/turret_shot_explosion.gd")
const FALL_SPEED_PER_TICK := 3.0
const EXPLOSION_INTERVAL_TICKS := 16

var sprite: Sprite2D
var delay_ticks := 0
var falling := false
var wide_block := false
var fall_ticks := 0


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture = SMALL_TEXTURE
	add_child(sprite)


func configure(wide: bool) -> void:
	wide_block = wide
	sprite.texture = WIDE_TEXTURE if wide else SMALL_TEXTURE


func activate(delay: int) -> void:
	delay_ticks = delay
	falling = true


func _physics_process(_delta: float) -> void:
	if not falling:
		return
	if delay_ticks > 0:
		delay_ticks -= 1
		return
	if fall_ticks % EXPLOSION_INTERVAL_TICKS == 4:
		_spawn_explosion(Vector2(-5, -7))
		_spawn_explosion(Vector2(65, -7) if wide_block else Vector2(15, -7))
	position.y += FALL_SPEED_PER_TICK
	var screen_rect := sprite.get_global_transform_with_canvas() * sprite.get_rect()
	if screen_rect.position.y >= get_viewport_rect().end.y:
		queue_free()
	fall_ticks += 1


func _spawn_explosion(offset: Vector2) -> void:
	get_node("/root/AudioManager").play_sfx("anim13")
	var explosion: TurretShotExplosion = ExplosionScript.new()
	explosion.position = position + offset
	explosion.z_index = 30
	get_parent().add_child(explosion)
