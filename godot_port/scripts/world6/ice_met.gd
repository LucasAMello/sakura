class_name World6IceMet
extends SakuraEnemy

signal needles_requested(spawn_position: Vector2)

const FRAMES := [
	preload("res://assets/world6/ice_met_1.png"),
	preload("res://assets/world6/ice_met_2.png"),
	preload("res://assets/world6/ice_met_3.png"),
	preload("res://assets/world6/ice_met_4.png"),
]

var move_direction := -1
var timer := 0


func _ready() -> void:
	super._ready()
	body_size = Vector2(55, 43)
	hit_points = 4
	contact_damage = 2
	drops_recovery = true
	sprite.texture = FRAMES[0]


func configure(direction: int = 0) -> void:
	set_update_interval(1)
	move_direction = 1 if direction > 0 else -1
	sprite.flip_h = move_direction > 0


func _update_enemy() -> void:
	sprite.texture = FRAMES[int(timer / 8.0) % FRAMES.size()]
	timer += 1
	var movement := Vector2(move_direction * 1.0, 0)
	var candidate := Rect2(position + movement, body_size)
	var floor_left := terrain.is_solid_at(Vector2(candidate.position.x + 1, candidate.end.y + 7))
	var floor_right := terrain.is_solid_at(Vector2(candidate.end.x - 1, candidate.end.y + 7))
	if terrain.rect_hits_solid(candidate) or not floor_left or not floor_right:
		move_direction *= -1
		sprite.flip_h = move_direction > 0
	else:
		position += movement


func take_projectile_hit(damage: int) -> void:
	var defeated_now := not defeated_state and hit_points - damage <= 0
	super.take_projectile_hit(damage)
	if defeated_now:
		needles_requested.emit(position)
