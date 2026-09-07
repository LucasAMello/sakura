class_name WeaponImpactParticle
extends Node2D

enum Kind { WATER_UP, WATER_DOWN, ICE }

var terrain: SakuraTerrain
var stage: Node
var sprite: Sprite2D
var kind := Kind.WATER_UP
var velocity := Vector2.ZERO
var update_phase := 0
var source_ticks := 0


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_PAUSABLE
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func configure(map_terrain: SakuraTerrain, owner_stage: Node, particle_kind: WeaponImpactParticle.Kind, horizontal_speed: float = 0.0) -> void:
	terrain = map_terrain
	stage = owner_stage
	kind = particle_kind
	if kind == Kind.WATER_UP:
		sprite.texture = preload("res://assets/player/water_particle.png")
		velocity = Vector2(horizontal_speed, -4.0)
	elif kind == Kind.WATER_DOWN:
		sprite.texture = preload("res://assets/player/water_particle.png")
		velocity = Vector2(horizontal_speed, 10.0)
	else:
		sprite.texture = preload("res://assets/player/ice_particle.png")
		velocity = Vector2(horizontal_speed, -float(randi_range(4, 10)))


func _physics_process(_delta: float) -> void:
	update_phase = (update_phase + 1) % 2
	if update_phase != 0:
		return
	source_ticks += 1
	if kind == Kind.WATER_UP:
		if _move_water_splash(velocity):
			return
		velocity.y += 1.0
	elif kind == Kind.WATER_DOWN:
		if source_ticks % 2 == 0:
			velocity.x = move_toward(velocity.x, 0.0, 1.0)
		if _move_water_splash(velocity):
			return
		velocity.y += 0.5
	else:
		position += velocity * 2.0
		velocity.y += 1.0
	if terrain.rect_hits_solid(Rect2(position, Vector2(14, 14))) or position.y > terrain.world_size.y or position.y < 0.0:
		queue_free()


func _move_water_splash(amount: Vector2) -> bool:
	var steps := maxi(1, ceili(amount.length() / 2.0))
	var step := amount / float(steps)
	for _index in range(steps):
		position += step
		var rect := Rect2(position, Vector2(14, 14))
		if stage.projectile_hits_solid(rect) or stage.damage_enemy_in_rect(rect, 1, 5, true):
			queue_free()
			return true
	return false
