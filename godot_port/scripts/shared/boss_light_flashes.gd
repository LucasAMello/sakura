extends Node2D

const FRAME_HOLD_TICKS := 8
const RAY_COLOR := Color(1.0, 1.0, 20.0 / 255.0)

var lifetime_ticks := 262
var elapsed_ticks := 0
var rays: Array[PackedVector2Array] = []
var random := RandomNumberGenerator.new()


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_PAUSABLE
	random.randomize()
	_refresh_rays()


func _physics_process(_delta: float) -> void:
	elapsed_ticks += 1
	if elapsed_ticks >= lifetime_ticks:
		queue_free()
		return
	if elapsed_ticks % FRAME_HOLD_TICKS == 0:
		_refresh_rays()


func _refresh_rays() -> void:
	rays.clear()
	for _ray in range(3):
		var direction := random.randi_range(0, 11)
		var origin := Vector2.ZERO
		var edge_a := Vector2.ZERO
		var edge_b := Vector2.ZERO
		if direction < 8:
			var quadrant := direction % 4
			var x_sign := 1.0 if quadrant < 2 else -1.0
			var y_sign := 1.0 if quadrant % 2 == 0 else -1.0
			origin = Vector2(x_sign * random.randi_range(3, 5), y_sign * random.randi_range(3, 5))
			var x_min := 150 if direction < 4 else 45
			var x_max := 249 if direction < 4 else 74
			var y_min := 45 if direction < 4 else 150
			var y_max := 74 if direction < 4 else 249
			edge_a = Vector2(x_sign * random.randi_range(x_min, x_max), y_sign * random.randi_range(y_min, y_max))
			edge_b = Vector2(x_sign * random.randi_range(x_min, x_max), y_sign * random.randi_range(y_min, y_max))
		elif direction < 10:
			var side := 1.0 if direction == 8 else -1.0
			origin.x = side * random.randi_range(5, 6)
			edge_a = Vector2(side * random.randi_range(150, 249), -random.randi_range(5, 19))
			edge_b = Vector2(side * random.randi_range(150, 249), random.randi_range(5, 19))
		else:
			var side := 1.0 if direction == 10 else -1.0
			origin.y = side * random.randi_range(5, 6)
			edge_a = Vector2(-random.randi_range(5, 19), side * random.randi_range(150, 249))
			edge_b = Vector2(random.randi_range(5, 19), side * random.randi_range(150, 249))
		if not is_zero_approx((edge_a - origin).cross(edge_b - origin)):
			rays.append(PackedVector2Array([origin, edge_a, edge_b]))
	queue_redraw()


func _draw() -> void:
	for ray in rays:
		draw_colored_polygon(ray, RAY_COLOR)
