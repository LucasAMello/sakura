class_name PumpkinEnemy
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
const PATROL_SPEED := 2.5
const CHASE_SPEED := 5.0
const STUN_DURATION_TICKS := 120
const ANIMATION_HOLD_TICKS := 8

var move_direction := -1
var timer := 0
var stun_ticks := 0


func configure(initial_direction: int) -> void:
	body_size = Vector2(24, 20)
	hit_points = 1
	contact_damage = 2
	drops_recovery = true
	move_direction = 1 if initial_direction == 1 else -1
	sprite.texture = FRAMES[0]
	sprite.flip_h = move_direction > 0


func _update_enemy() -> void:
	if stun_ticks > 0:
		stun_ticks -= 1
		return
	timer += 1
	sprite.texture = FRAMES[int((timer - 1) / float(ANIMATION_HOLD_TICKS)) % FRAMES.size()]
	var speed := PATROL_SPEED
	if is_instance_valid(player) and player.grounded:
		var aligned := is_equal_approx(player.position.y + 60.0, position.y)
		var nearby := absf(player.position.x - position.x) < 240.0
		if aligned and nearby:
			speed = CHASE_SPEED
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
	stun_ticks = STUN_DURATION_TICKS
	var source_tick := int((timer + 3) / 4.0)
	sprite.texture = STUN_FRAMES[1] if source_tick % 6 < 4 else STUN_FRAMES[0]
