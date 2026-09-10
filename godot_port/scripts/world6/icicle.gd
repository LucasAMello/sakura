class_name World6Icicle
extends SakuraEnemy

const TEXTURES := [
	preload("res://assets/world6/icicle_1.png"),
	preload("res://assets/world6/icicle_2.png"),
]
const SIZES := [Vector2(12, 30), Vector2(16, 32)]

var falling := false
var landed := false
var timer := 0
var vertical_speed := 2.0


func _ready() -> void:
	super._ready()
	hit_points = 1
	contact_damage = 3


func configure(variant: int) -> void:
	set_update_interval(1)
	var index := clampi(variant, 0, 1)
	body_size = SIZES[index]
	sprite.texture = TEXTURES[index]


func _update_enemy() -> void:
	if landed:
		timer += 1
		if timer >= 8:
			queue_free()
		return
	if not falling:
		var horizontal_distance := player.position.x - position.x
		var vertical_distance := player.position.y - position.y
		if horizontal_distance > -140.0 and horizontal_distance < 100.0 and vertical_distance > 0.0 and vertical_distance < 300.0:
			falling = true
			get_node("/root/AudioManager").play_sfx("icefall")
		return
	if timer % 4 == 0 and vertical_speed < 39.0:
		vertical_speed += 4.0
	timer += 1
	if timer <= 20:
		position.y += vertical_speed * 0.25
		return
	if not _move_down(vertical_speed * 0.25):
		landed = true
		timer = 0


func _move_down(amount: float) -> bool:
	var remaining := amount
	while remaining > 0.0:
		var step := minf(1.0, remaining)
		if terrain.rect_hits_solid(Rect2(position + Vector2(0, step), body_size)):
			position.y = floorf((position.y + step + body_size.y) / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE - body_size.y
			return false
		position.y += step
		remaining -= step
	return true
