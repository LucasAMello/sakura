class_name World6Icicle
extends SakuraEnemy

const TEXTURES := [
	preload("res://assets/world6/icicle_1.png"),
	preload("res://assets/world6/icicle_2.png"),
]
const SIZES := [Vector2(12, 30), Vector2(16, 32)]

var falling := false
var timer := 0
var vertical_speed := 2.0


func _ready() -> void:
	super._ready()
	hit_points = 1
	contact_damage = 3


func configure(variant: int) -> void:
	var index := clampi(variant, 0, 1)
	body_size = SIZES[index]
	sprite.texture = TEXTURES[index]


func _update_enemy() -> void:
	if not falling:
		var horizontal_distance := player.position.x - position.x
		var vertical_distance := player.position.y - position.y
		if horizontal_distance > -140.0 and horizontal_distance < 100.0 and vertical_distance > 0.0 and vertical_distance < 300.0:
			falling = true
		return
	timer += 1
	vertical_speed = minf(39.0, vertical_speed + 4.0)
	if timer <= 5:
		position.y += vertical_speed
		return
	if not _move_down(vertical_speed):
		queue_free()


func _move_down(amount: float) -> bool:
	var remaining := amount
	while remaining > 0.0:
		var step := minf(1.0, remaining)
		if terrain.rect_hits_solid(Rect2(position + Vector2(0, step), body_size)):
			return false
		position.y += step
		remaining -= step
	return true

