class_name World5Flamemet
extends SakuraEnemy

signal falling_fire_requested(spawn_position: Vector2)

const FRAMES := [
	preload("res://assets/world5/flamemet_1.png"),
	preload("res://assets/world5/flamemet_2.png"),
	preload("res://assets/world5/flamemet_3.png"),
	preload("res://assets/world5/flamemet_4.png"),
]
var SOURCE_EMPTY_TOKENS := PackedStringArray([
	"1", "A", "B", "C", "D", "E", "F",
	"U", "V", "W", "X", "Y", "Z", "I", "J",
])

var direction := 0
var ceiling := false
var timer := 0


func configure(facing: int, walks_on_ceiling: bool) -> void:
	set_update_interval(1)
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


func take_weapon_hit(damage: int, weapon_id: int) -> void:
	take_projectile_hit(3 if weapon_id == 5 else damage)


func take_water_splash_hit() -> void:
	take_projectile_hit(1 if ceiling else 3)


func _update_enemy() -> void:
	sprite.texture = FRAMES[int(timer / 8.0) % FRAMES.size()]
	if ceiling and timer % 280 == 279:
		falling_fire_requested.emit(position + Vector2(9, -2))
	timer += 1
	var movement := 1.0 if direction == 1 else -1.0
	if not _move_horizontally(movement):
		_turn_around()
		return
	var probe_x := position.x + 40.0 if direction == 1 else position.x
	var probe_y := position.y - 10.0 if ceiling else position.y + 50.0
	var probe_cell := terrain.get_cell(floori(probe_x / SakuraTerrain.TILE_SIZE), floori(probe_y / SakuraTerrain.TILE_SIZE))
	if SOURCE_EMPTY_TOKENS.has(probe_cell):
		if direction == 1:
			position.x = floorf(position.x / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE
		else:
			position.x = floorf((position.x + SakuraTerrain.TILE_SIZE) / SakuraTerrain.TILE_SIZE) * SakuraTerrain.TILE_SIZE
		_turn_around()


func _move_horizontally(amount: float) -> bool:
	var remaining := absf(amount)
	while remaining > 0.0:
		var step := signf(amount) * minf(1.0, remaining)
		var candidate := Rect2(position + Vector2(step, 0), body_size)
		if terrain.rect_hits_solid(candidate):
			return false
		position.x += step
		remaining -= absf(step)
	return true


func _turn_around() -> void:
	direction = 1 - direction
	sprite.flip_h = not ceiling and direction == 1
