class_name GhostMaskEnemy
extends SakuraEnemy

const TEXTURES := [
	preload("res://assets/world2/ghost_mask_1.png"),
	preload("res://assets/world2/ghost_mask_2.png"),
	preload("res://assets/world2/ghost_mask_3.png"),
]
const SMALL_DROP_PERCENT := 20
const EXTRA_LIFE_DROP_PERCENT := 10

var move_direction := -1
var stop_x := 0.0
var timer := 0
var y_velocity := 0.0
var horizontal_speed := 5.0
var oscillation_direction := 0
var fading := false
var fade_level := 160


func _ready() -> void:
	super._ready()
	body_size = Vector2(70, 30)
	hit_points = 2
	contact_damage = 2
	sprite.texture = TEXTURES[0]


func configure(direction: int, destination_x: float, movement_speed: float = 5.0) -> void:
	set_update_interval(1)
	move_direction = 1 if direction > 0 else -1
	stop_x = destination_x
	horizontal_speed = movement_speed
	sprite.flip_h = move_direction > 0


func _update_enemy() -> void:
	timer += 1
	if fading:
		position.x += move_direction * horizontal_speed / 4.0
		fade_level -= 5
		sprite.modulate.a = maxf(0.0, float(fade_level) / 255.0)
		if fade_level <= 0:
			queue_free()
		return
	if timer == 4:
		sprite.texture = TEXTURES[0]
	elif timer == 16:
		sprite.texture = TEXTURES[1]
	elif timer == 28:
		sprite.texture = TEXTURES[2]
	elif timer >= 40:
		sprite.texture = TEXTURES[1]
		timer = -8
	if posmod(timer, 4) == 1:
		if oscillation_direction == 0:
			if y_velocity == 2.0:
				oscillation_direction = 1
			else:
				y_velocity += 0.5
		else:
			if y_velocity == -2.0:
				oscillation_direction = 0
			else:
				y_velocity -= 0.5
	var movement := Vector2(move_direction * horizontal_speed, y_velocity) / 4.0
	var candidate := Rect2(position + movement, body_size)
	position += movement
	if terrain.rect_hits_solid(candidate):
		fading = true
	if move_direction < 0 and position.x < stop_x:
		fading = true
	elif move_direction > 0 and position.x > stop_x:
		fading = true


func _roll_drop() -> int:
	return _drop_for_roll(randi_range(0, 99))


func _drop_for_roll(roll: int) -> int:
	if roll < SMALL_DROP_PERCENT:
		return DropType.SMALL
	if roll < SMALL_DROP_PERCENT + EXTRA_LIFE_DROP_PERCENT:
		return DropType.EXTRA_LIFE
	return DropType.NONE


func _drop_position(_drop_type: int) -> Vector2:
	return position + Vector2(5, 5)
