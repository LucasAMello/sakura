class_name World5FlameBurst
extends SakuraEnemy

const HORIZONTAL_FRAMES := [
	preload("res://assets/world5/flame_horizontal_1.png"),
	preload("res://assets/world5/flame_horizontal_2.png"),
	preload("res://assets/world5/flame_horizontal_3.png"),
	preload("res://assets/world5/flame_horizontal_4.png"),
	preload("res://assets/world5/flame_horizontal_5.png"),
	preload("res://assets/world5/flame_horizontal_6.png"),
	preload("res://assets/world5/flame_horizontal_7.png"),
	preload("res://assets/world5/flame_horizontal_8.png"),
	preload("res://assets/world5/flame_horizontal_9.png"),
]
const VERTICAL_FRAMES := [
	preload("res://assets/world5/flame_vertical_1.png"),
	preload("res://assets/world5/flame_vertical_2.png"),
	preload("res://assets/world5/flame_vertical_3.png"),
	preload("res://assets/world5/flame_vertical_4.png"),
	preload("res://assets/world5/flame_vertical_5.png"),
	preload("res://assets/world5/flame_vertical_6.png"),
	preload("res://assets/world5/flame_vertical_7.png"),
	preload("res://assets/world5/flame_vertical_8.png"),
	preload("res://assets/world5/flame_vertical_9.png"),
]

var vertical := false
var direction := 0
var timer := 0


func configure(is_vertical: bool, facing: int) -> void:
	set_update_interval(1)
	vertical = is_vertical
	direction = facing
	body_size = Vector2(58, 90) if vertical else Vector2(90, 58)
	hit_points = 1
	contact_damage = 3
	drops_recovery = false
	sprite.texture = VERTICAL_FRAMES[0] if vertical else HORIZONTAL_FRAMES[0]
	sprite.flip_v = vertical and direction == 0
	sprite.flip_h = not vertical and direction == 1


func _update_enemy() -> void:
	timer += 1
	var frames := VERTICAL_FRAMES if vertical else HORIZONTAL_FRAMES
	if timer >= 116:
		queue_free()
		return
	var source_tick := int(timer / 4.0)
	if timer < 108 and timer % 28 == 4:
		get_node("/root/AudioManager").play_sfx_near_player("flamethrower", position, player.position)
	if timer >= 108 and timer < 112:
		sprite.texture = frames[7]
	elif timer >= 112:
		sprite.texture = frames[8]
	else:
		sprite.texture = frames[posmod(maxi(1, source_tick) - 1, 7)]


func projectile_mask_overlap(_projectile_rect: Rect2) -> bool:
	return false
