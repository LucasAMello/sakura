class_name World5Flamemet
extends SakuraEnemy

signal falling_fire_requested(spawn_position: Vector2)

const FRAMES := [
	preload("res://assets/world5/flamemet_1.png"),
	preload("res://assets/world5/flamemet_2.png"),
	preload("res://assets/world5/flamemet_3.png"),
	preload("res://assets/world5/flamemet_4.png"),
]

var direction := 0
var ceiling := false
var timer := 0


func configure(facing: int, walks_on_ceiling: bool) -> void:
	direction = facing
	ceiling = walks_on_ceiling
	body_size = Vector2(42, 33)
	hit_points = 5
	contact_damage = 2
	drops_recovery = true
	sprite.texture = FRAMES[0]
	sprite.flip_v = ceiling
	sprite.position.y = -3.0 if ceiling else 0.0
	sprite.flip_h = not ceiling and direction == 1


func _update_enemy() -> void:
	sprite.texture = FRAMES[int(timer / 2.0) % FRAMES.size()]
	if ceiling and timer % 70 == 69:
		falling_fire_requested.emit(position + Vector2(9, -2))
	timer += 1
	var movement := 2.0 if direction == 1 else -2.0
	var candidate := Rect2(position + Vector2(movement, 0), body_size)
	if terrain.rect_hits_solid(candidate):
		direction = 1 - direction
		sprite.flip_h = not ceiling and direction == 1
		return
	var probe_x := candidate.position.x + 40.0 if direction == 1 else candidate.position.x
	var probe_y := candidate.position.y - 10.0 if ceiling else candidate.position.y + 50.0
	var probe_cell := terrain.get_cell(floori(probe_x / SakuraTerrain.TILE_SIZE), floori(probe_y / SakuraTerrain.TILE_SIZE))
	if probe_cell == "1":
		if direction == 1:
			position.x = floorf(position.x / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE
		else:
			position.x = floorf((position.x + SakuraTerrain.TILE_SIZE) / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE
		direction = 1 - direction
		sprite.flip_h = not ceiling and direction == 1
		return
	position.x += movement
