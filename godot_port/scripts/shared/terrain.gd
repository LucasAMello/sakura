class_name SakuraTerrain
extends Node2D

const TILE_SIZE := 20

const FIRST_STAGE_SOURCE_RECTS := {
	"2": Vector2i(20, 0),
	"3": Vector2i(40, 0),
	"4": Vector2i(0, 40),
	"5": Vector2i(0, 60),
	"a": Vector2i(20, 40),
	"b": Vector2i(60, 40),
	"c": Vector2i(20, 20),
	"d": Vector2i(20, 60),
	"e": Vector2i(60, 60),
	"f": Vector2i(40, 20),
	"g": Vector2i(60, 0),
	"h": Vector2i(0, 80),
	"i": Vector2i(0, 0),
	"j": Vector2i(60, 20),
	"k": Vector2i(40, 60),
	"l": Vector2i(0, 20),
	"m": Vector2i(40, 40),
}

var cells: Array = []
var atlas: Texture2D = preload("res://assets/world1/terrain.png")
var source_rects: Dictionary = FIRST_STAGE_SOURCE_RECTS
var non_solid_tokens := PackedStringArray(["0", "1"])
var lethal_tokens := PackedStringArray(["0"])
var collision_sizes: Dictionary = {}
var map_path := "res://maps/map10.map"
var map_width := 450
var map_height := 28
var world_size := Vector2(9000, 560)


func setup(
	path: String,
	width: int,
	height: int,
	map_atlas: Texture2D = null,
	map_source_rects: Dictionary = {},
	map_non_solid_tokens: PackedStringArray = PackedStringArray(),
	map_lethal_tokens: PackedStringArray = PackedStringArray(),
	map_collision_sizes: Dictionary = {}
) -> void:
	map_path = path
	map_width = width
	map_height = height
	world_size = Vector2(map_width * TILE_SIZE, map_height * TILE_SIZE)
	if map_atlas != null:
		atlas = map_atlas
	if not map_source_rects.is_empty():
		source_rects = map_source_rects
	if not map_non_solid_tokens.is_empty():
		non_solid_tokens = map_non_solid_tokens
	if not map_lethal_tokens.is_empty() or not map_non_solid_tokens.is_empty():
		lethal_tokens = map_lethal_tokens
	collision_sizes = map_collision_sizes


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


func _draw() -> void:
	if cells.size() != map_height:
		return
	for tile_y in range(map_height):
		for tile_x in range(map_width):
			var token: String = cells[tile_y][tile_x]
			if not source_rects.has(token):
				continue
			var source := get_source_rect(token, tile_x, tile_y)
			var draw_size: Vector2 = collision_sizes.get(token, Vector2(TILE_SIZE, TILE_SIZE))
			draw_texture_rect_region(
				atlas,
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


func is_solid_cell(tile_x: int, tile_y: int) -> bool:
	if tile_x < 0 or tile_x >= map_width:
		return true
	if tile_y < 0:
		return false
	if tile_y >= map_height:
		return false
	return not non_solid_tokens.has(get_cell(tile_x, tile_y))


func is_solid_at(point: Vector2) -> bool:
	var tile_x := floori(point.x / TILE_SIZE)
	var tile_y := floori(point.y / TILE_SIZE)
	if not is_solid_cell(tile_x, tile_y):
		return false
	var token := get_cell(tile_x, tile_y)
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


func rect_hits_solid(rect: Rect2) -> bool:
	var left := floori(rect.position.x / TILE_SIZE)
	var right := floori((rect.end.x - 0.001) / TILE_SIZE)
	var top := floori(rect.position.y / TILE_SIZE)
	var bottom := floori((rect.end.y - 0.001) / TILE_SIZE)
	for tile_y in range(top, bottom + 1):
		for tile_x in range(left, right + 1):
			if is_solid_cell(tile_x, tile_y):
				var token := get_cell(tile_x, tile_y)
				if not collision_sizes.has(token) or Rect2(Vector2(tile_x, tile_y) * TILE_SIZE, collision_sizes[token]).intersects(rect):
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
