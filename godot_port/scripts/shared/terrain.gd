class_name SakuraTerrain
extends Node2D

const TILE_SIZE := 20

var cells: Array = []
var solid_sprites: Array[Sprite2D] = []
var one_way_sprites: Array[Sprite2D] = []
var atlas: Texture2D
var source_rects: Dictionary = {}
var non_solid_tokens := PackedStringArray()
var lethal_tokens := PackedStringArray()
var collision_sizes: Dictionary = {}
var alpha_collision_tokens := PackedStringArray()
var atlas_image: Image
var atlases: Array[Texture2D] = []
var atlas_images: Array[Image] = []
var cell_atlas_indices: Array = []
var row_start_atlas_index := 0
var toggle_atlas_tokens := PackedStringArray()
var forced_atlas_after_columns: Dictionary = {}
var atlas_set_tokens: Dictionary = {}
var hidden_tokens := PackedStringArray()
var map_path := ""
var map_width := 0
var map_height := 0
var world_size := Vector2.ZERO


func setup(
	path: String,
	width: int,
	height: int,
	map_atlas: Texture2D,
	map_source_rects: Dictionary,
	map_non_solid_tokens: PackedStringArray,
	map_lethal_tokens: PackedStringArray,
	map_collision_sizes: Dictionary
) -> void:
	map_path = path
	map_width = width
	map_height = height
	world_size = Vector2(map_width * TILE_SIZE, map_height * TILE_SIZE)
	atlas = map_atlas
	atlas_image = atlas.get_image()
	atlases = [map_atlas]
	atlas_images = [atlas_image]
	source_rects = map_source_rects
	non_solid_tokens = map_non_solid_tokens
	lethal_tokens = map_lethal_tokens
	collision_sizes = map_collision_sizes


func configure_atlas_switching(
	map_atlases: Array,
	starting_atlas_index: int,
	toggle_tokens: PackedStringArray,
	forced_after_columns: Dictionary,
	set_tokens: Dictionary = {},
	map_hidden_tokens: PackedStringArray = PackedStringArray()
) -> void:
	atlases.clear()
	atlas_images.clear()
	for map_atlas in map_atlases:
		atlases.append(map_atlas)
		atlas_images.append(map_atlas.get_image())
	row_start_atlas_index = starting_atlas_index
	toggle_atlas_tokens = toggle_tokens
	forced_atlas_after_columns = forced_after_columns
	atlas_set_tokens = set_tokens
	hidden_tokens = map_hidden_tokens


func set_alpha_collision_tokens(tokens: PackedStringArray) -> void:
	alpha_collision_tokens = tokens


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	_load_map(map_path)
	queue_redraw()


func _load_map(path: String) -> void:
	var text := FileAccess.get_file_as_string(path).replace("\r", "")
	var lines := text.split("\n", false)
	for line in lines:
		var tokens := line.strip_edges().split(" ", false)
		if tokens.size() == map_width:
			cells.append(tokens)
	assert(cells.size() == map_height, "%s must contain %d rows of %d tokens" % [map_path, map_height, map_width])
	_build_cell_atlas_indices()


func _build_cell_atlas_indices() -> void:
	cell_atlas_indices.clear()
	for tile_y in range(map_height):
		var row_indices: Array[int] = []
		var current_atlas := row_start_atlas_index
		for tile_x in range(map_width):
			var token: String = cells[tile_y][tile_x]
			if atlas_set_tokens.has(token):
				current_atlas = int(atlas_set_tokens[token])
			row_indices.append(clampi(current_atlas, 0, atlases.size() - 1))
			if toggle_atlas_tokens.has(token) and atlases.size() > 1:
				current_atlas = 1 - current_atlas
			if forced_atlas_after_columns.has(tile_x):
				current_atlas = int(forced_atlas_after_columns[tile_x])
		cell_atlas_indices.append(row_indices)


func _draw() -> void:
	if cells.size() != map_height:
		return
	for tile_y in range(map_height):
		for tile_x in range(map_width):
			var token: String = cells[tile_y][tile_x]
			if not source_rects.has(token) or hidden_tokens.has(token):
				continue
			var source := get_source_rect(token, tile_x, tile_y)
			var draw_size: Vector2 = collision_sizes.get(token, Vector2(TILE_SIZE, TILE_SIZE))
			var tile_atlas: Texture2D = atlases[_get_atlas_index(tile_x, tile_y)]
			draw_texture_rect_region(
				tile_atlas,
				Rect2(Vector2(tile_x, tile_y) * TILE_SIZE, draw_size),
				Rect2(Vector2(source), draw_size)
			)


func get_source_rect(token: String, tile_x: int, tile_y: int) -> Vector2i:
	var source: Variant = source_rects[token]
	if source is Array:
		return source[posmod(tile_x + tile_y, source.size())]
	return source


func get_cell(tile_x: int, tile_y: int) -> String:
	if tile_x < 0 or tile_x >= map_width or tile_y < 0 or tile_y >= map_height:
		return ""
	return cells[tile_y][tile_x]


func _get_atlas_index(tile_x: int, tile_y: int) -> int:
	if tile_y < 0 or tile_y >= cell_atlas_indices.size():
		return 0
	var row: Array = cell_atlas_indices[tile_y]
	if tile_x < 0 or tile_x >= row.size():
		return 0
	return int(row[tile_x])


func is_solid_cell(tile_x: int, tile_y: int) -> bool:
	if tile_x < 0 or tile_x >= map_width:
		return true
	if tile_y < 0:
		return false
	if tile_y >= map_height:
		return false
	return not non_solid_tokens.has(get_cell(tile_x, tile_y))


func is_solid_at(point: Vector2) -> bool:
	for solid_sprite in solid_sprites:
		if is_instance_valid(solid_sprite) and solid_sprite.visible and Rect2(solid_sprite.position, solid_sprite.texture.get_size()).has_point(point):
			return true
	var tile_x := floori(point.x / TILE_SIZE)
	var tile_y := floori(point.y / TILE_SIZE)
	if not is_solid_cell(tile_x, tile_y):
		return false
	var token := get_cell(tile_x, tile_y)
	if alpha_collision_tokens.has(token):
		return _alpha_collision_at(token, tile_x, tile_y, point)
	if collision_sizes.has(token):
		var local_point := point - Vector2(tile_x * TILE_SIZE, tile_y * TILE_SIZE)
		return Rect2(Vector2.ZERO, collision_sizes[token]).has_point(local_point)
	return true


func is_lethal_at(point: Vector2) -> bool:
	var tile_x := floori(point.x / TILE_SIZE)
	var tile_y := floori(point.y / TILE_SIZE)
	if tile_y >= map_height:
		return true
	return lethal_tokens.has(get_cell(tile_x, tile_y))


func one_way_landing_y(previous_rect: Rect2, next_rect: Rect2) -> float:
	var landing_y := INF
	if next_rect.end.y <= previous_rect.end.y:
		return landing_y
	for platform in one_way_sprites:
		if not is_instance_valid(platform) or not platform.visible:
			continue
		var platform_rect := Rect2(platform.position, platform.texture.get_size())
		if next_rect.end.x <= platform_rect.position.x or next_rect.position.x >= platform_rect.end.x:
			continue
		if previous_rect.end.y <= platform_rect.position.y + 0.001 and next_rect.end.y >= platform_rect.position.y:
			landing_y = minf(landing_y, platform_rect.position.y)
	return landing_y


func rect_hits_solid(rect: Rect2) -> bool:
	for solid_sprite in solid_sprites:
		if is_instance_valid(solid_sprite) and solid_sprite.visible and Rect2(solid_sprite.position, solid_sprite.texture.get_size()).intersects(rect):
			return true
	var left := floori(rect.position.x / TILE_SIZE)
	var right := floori((rect.end.x - 0.001) / TILE_SIZE)
	var top := floori(rect.position.y / TILE_SIZE)
	var bottom := floori((rect.end.y - 0.001) / TILE_SIZE)
	for tile_y in range(top, bottom + 1):
		for tile_x in range(left, right + 1):
			if is_solid_cell(tile_x, tile_y):
				var token := get_cell(tile_x, tile_y)
				if alpha_collision_tokens.has(token):
					if _rect_hits_alpha_tile(rect, token, tile_x, tile_y):
						return true
				elif not collision_sizes.has(token) or Rect2(Vector2(tile_x, tile_y) * TILE_SIZE, collision_sizes[token]).intersects(rect):
					return true
	return false


func _alpha_collision_at(token: String, tile_x: int, tile_y: int, point: Vector2) -> bool:
	var tile_atlas_image: Image = atlas_images[_get_atlas_index(tile_x, tile_y)]
	if tile_atlas_image == null:
		return true
	var local := Vector2i(floori(point.x) - tile_x * TILE_SIZE, floori(point.y) - tile_y * TILE_SIZE)
	if local.x < 0 or local.x >= TILE_SIZE or local.y < 0 or local.y >= TILE_SIZE:
		return false
	var source := get_source_rect(token, tile_x, tile_y)
	return tile_atlas_image.get_pixel(source.x + local.x, source.y + local.y).a > 0.01


func rect_hits_slope(rect: Rect2) -> bool:
	for tile_y in range(floori(rect.position.y / TILE_SIZE), floori((rect.end.y - 0.001) / TILE_SIZE) + 1):
		for tile_x in range(floori(rect.position.x / TILE_SIZE), floori((rect.end.x - 0.001) / TILE_SIZE) + 1):
			var token := get_cell(tile_x, tile_y)
			if alpha_collision_tokens.has(token) and _rect_hits_alpha_tile(rect, token, tile_x, tile_y):
				return true
	return false


func _rect_hits_alpha_tile(rect: Rect2, token: String, tile_x: int, tile_y: int) -> bool:
	var tile_rect := Rect2(Vector2(tile_x, tile_y) * TILE_SIZE, Vector2(TILE_SIZE, TILE_SIZE))
	var overlap := rect.intersection(tile_rect)
	for world_y in range(floori(overlap.position.y), ceili(overlap.end.y)):
		for world_x in range(floori(overlap.position.x), ceili(overlap.end.x)):
			if _alpha_collision_at(token, tile_x, tile_y, Vector2(world_x, world_y)):
				return true
	return false


func rect_touches_lethal_floor(rect: Rect2) -> bool:
	var y := rect.end.y - 1.0
	for x_offset in [0.0, rect.size.x * 0.5, rect.size.x - 1.0]:
		if is_lethal_at(Vector2(rect.position.x + x_offset, y)):
			return true
	return false


func has_solid_below(point: Vector2, maximum_drop: int) -> bool:
	for distance in range(1, maximum_drop + 1):
		if is_solid_at(point + Vector2(0, distance)):
			return true
	return false
