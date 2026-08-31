class_name World4WaterShot
extends SakuraEnemy

const FRONT_FRAMES := [
	preload("res://assets/world4/boss_water_front_1.png"),
	preload("res://assets/world4/boss_water_front_2.png"),
]
const MIDDLE_FRAMES := [
	preload("res://assets/world4/boss_water_middle_1.png"),
	preload("res://assets/world4/boss_water_middle_2.png"),
]
const END_FRAMES := [
	preload("res://assets/world4/boss_water_end_1.png"),
	preload("res://assets/world4/boss_water_end_2.png"),
]

var direction := 0
var trailing := false
var timer := 0
var segment_count := 0
var expanding := true
var shrinking := false
var front_sprite: Sprite2D
var end_sprite: Sprite2D
var middle_sprites: Array[Sprite2D] = []


func _ready() -> void:
	super._ready()
	body_size = Vector2(33, 30)
	hit_points = 1
	contact_damage = 3
	drops_recovery = false
	sprite.visible = false
	front_sprite = _make_piece(FRONT_FRAMES[0])
	end_sprite = _make_piece(END_FRAMES[0])
	for _index in range(11):
		middle_sprites.append(_make_piece(MIDDLE_FRAMES[0]))
	_refresh_visuals()


func configure(shot_direction: int, is_trailing: bool) -> void:
	direction = 0 if shot_direction <= 0 else 1
	trailing = is_trailing
	_refresh_visuals()


func projectile_mask_overlap(_projectile_rect: Rect2) -> bool:
	return false


func take_projectile_hit(_damage: int) -> void:
	pass


func _update_enemy() -> void:
	timer += 1
	if shrinking:
		segment_count -= 2
		if segment_count < 0:
			queue_free()
			return
		body_size.x = 33.0 + segment_count * 16.0
		_refresh_visuals()
		return
	var should_move := not expanding or direction == 0 or trailing
	if should_move and _move_or_hit(-32.0 if direction == 0 else 32.0):
		_begin_shrinking()
		return
	if expanding:
		segment_count += 2
		body_size.x += 32.0
		if segment_count >= 10:
			segment_count += 1
			body_size.x += 16.0
			expanding = false
	_refresh_visuals()
	if position.x + body_size.x < 0.0 or position.x > terrain.world_size.x:
		queue_free()


func _move_or_hit(amount: float) -> bool:
	var direction_sign := signf(amount)
	for _step in range(int(absf(amount))):
		var candidate := Rect2(position + Vector2(direction_sign, 0), body_size)
		if candidate.position.x < 0.0 or candidate.end.x > terrain.world_size.x or terrain.rect_hits_solid(candidate):
			return true
		position.x += direction_sign
	return false


func _begin_shrinking() -> void:
	shrinking = true
	expanding = false


func _make_piece(texture: Texture2D) -> Sprite2D:
	var piece := Sprite2D.new()
	piece.centered = false
	piece.texture = texture
	piece.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(piece)
	return piece


func _refresh_visuals() -> void:
	if not is_instance_valid(front_sprite):
		return
	var frame_index := 0 if timer % 4 < 2 else 1
	var middle_index := timer % 2
	front_sprite.texture = FRONT_FRAMES[frame_index]
	end_sprite.texture = END_FRAMES[frame_index]
	front_sprite.flip_h = direction == 1
	end_sprite.flip_h = direction == 1
	for index in range(middle_sprites.size()):
		var middle := middle_sprites[index]
		middle.texture = MIDDLE_FRAMES[middle_index]
		middle.flip_h = direction == 1
		middle.visible = index < segment_count
		middle.position = Vector2((19.0 if direction == 0 else 14.0) + index * 16.0, 6.0)
	if direction == 0:
		front_sprite.position = Vector2.ZERO
		end_sprite.position = Vector2(19.0 + segment_count * 16.0, 6.0)
	else:
		end_sprite.position = Vector2(0, 6)
		front_sprite.position = Vector2(14.0 + segment_count * 16.0, 0)
