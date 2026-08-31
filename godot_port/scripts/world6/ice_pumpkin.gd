class_name World6IcePumpkin
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world1/pumpkin_1.png"),
	preload("res://assets/world1/pumpkin_2.png"),
	preload("res://assets/world1/pumpkin_3.png"),
]
const STUN_FRAMES := [
	preload("res://assets/world1/pumpkin_4.png"),
	preload("res://assets/world1/pumpkin_5.png"),
]

var move_direction := -1
var timer := 0
var stun_ticks := 0


func _ready() -> void:
	super._ready()
	body_size = Vector2(24, 20)
	hit_points = 1
	contact_damage = 2
	drops_recovery = true
	sprite.texture = FRAMES[0]


func configure(direction: int = 0) -> void:
	move_direction = 1 if direction > 0 else -1
	sprite.flip_h = move_direction > 0


func _update_enemy() -> void:
	if stun_ticks > 0:
		stun_ticks -= 1
		return
	timer += 1
	sprite.texture = FRAMES[int(((timer - 1) % 6) / 2.0)]
	var speed := 10.0
	if player.grounded and is_equal_approx(player.position.y + 60.0, position.y) and absf(player.position.x - position.x) < 240.0:
		speed = 20.0
	var candidate := Rect2(position + Vector2(move_direction * speed, 0), body_size)
	var floor_left := terrain.is_solid_at(Vector2(candidate.position.x + 1, candidate.end.y))
	var floor_right := terrain.is_solid_at(Vector2(candidate.end.x - 1, candidate.end.y))
	if terrain.rect_hits_solid(candidate) or not floor_left or not floor_right:
		move_direction *= -1
		sprite.flip_h = move_direction > 0
	else:
		position.x = candidate.position.x


func take_projectile_hit(_damage: int) -> void:
	if defeated_state:
		return
	stun_ticks = 30
	sprite.texture = STUN_FRAMES[1] if timer % 6 < 4 else STUN_FRAMES[0]

