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
var segment_count := 0.0
var expanding := true
var blocking_edge := NAN
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
	set_update_interval(1)
	direction = 0 if shot_direction <= 0 else 1
	trailing = is_trailing
	_refresh_visuals()


func projectile_mask_overlap(_projectile_rect: Rect2) -> bool:
	return false


func take_projectile_hit(_damage: int) -> void:
	pass


func _update_enemy() -> void:
	timer += 1
	blocking_edge = NAN
	var should_move := not expanding or direction == 0 or trailing
	if should_move:
		_move_or_hit(-8.0 if direction == 0 else 8.0)
	if expanding:
		segment_count += 0.5
		body_size.x += 8.0
		if timer >= 17:
			segment_count += 0.25
			body_size.x += 4.0
			if is_nan(blocking_edge):
				_move_or_hit(-4.0 if direction == 0 else 4.0)
			if timer >= 20:
				expanding = false
	if is_nan(blocking_edge):
		blocking_edge = _find_blocking_edge(get_hit_rect())
	if not is_nan(blocking_edge):
		if not trailing or not expanding:
			segment_count -= 0.5
			body_size.x -= 8.0
			if segment_count <= 0:
				queue_free()
				return
		position.x = blocking_edge - body_size.x if direction == 1 else blocking_edge - (3.0 if not trailing else 0.0)
	_refresh_visuals()
	if position.x + body_size.x < 0.0 or position.x > terrain.world_size.x:
		queue_free()


func _move_or_hit(amount: float) -> bool:
	var direction_sign := signf(amount)
	for _step in range(int(absf(amount))):
		var candidate := Rect2(position + Vector2(direction_sign, 0), body_size)
		var edge := _find_blocking_edge(candidate)
		if not is_nan(edge):
			blocking_edge = edge
			return true
		position.x += direction_sign
	return false


func _find_blocking_edge(rect: Rect2) -> float:
	if direction == 0 and rect.position.x < 9360.0:
		return 9360.0
	if direction == 1 and rect.end.x > terrain.world_size.x:
		return terrain.world_size.x
	var edge := NAN
	for tile_y in range(floori(rect.position.y / 20.0), ceili(rect.end.y / 20.0)):
		for tile_x in range(floori(rect.position.x / 20.0), ceili(rect.end.x / 20.0)):
			var tile_rect := Rect2(tile_x * 20.0, tile_y * 20.0, 20.0, 20.0)
			if terrain.rect_hits_solid(rect.intersection(tile_rect)):
				var tile_edge := tile_rect.position.x if direction == 1 else tile_rect.end.x
				if is_nan(edge):
					edge = tile_edge
				else:
					edge = minf(edge, tile_edge) if direction == 1 else maxf(edge, tile_edge)
	return edge


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
	var source_tick := int(timer / 4.0)
	var frame_index := 0 if source_tick % 4 < 2 else 1
	var middle_index := source_tick % 2
	front_sprite.texture = FRONT_FRAMES[frame_index]
	end_sprite.texture = END_FRAMES[frame_index]
	front_sprite.flip_h = direction == 1
	end_sprite.flip_h = direction == 1
	for index in range(middle_sprites.size()):
		var middle := middle_sprites[index]
		middle.texture = MIDDLE_FRAMES[middle_index]
		middle.flip_h = direction == 1
		middle.visible = index < segment_count
		middle.region_enabled = true
		middle.region_rect = Rect2(0.0, 0.0, 16.0 * clampf(segment_count - index, 0.0, 1.0), middle.texture.get_height())
		middle.position = Vector2((19.0 if direction == 0 else 14.0) + index * 16.0, 6.0)
	if direction == 0:
		front_sprite.position = Vector2.ZERO
		end_sprite.position = Vector2(19.0 + segment_count * 16.0, 6.0)
	else:
		end_sprite.position = Vector2(0, 6)
		front_sprite.position = Vector2(14.0 + segment_count * 16.0, 0)
