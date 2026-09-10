class_name World4WaterLayer
extends Node2D

const TOP_TEXTURES := [
	preload("res://assets/world4/water_top_1.png"),
	preload("res://assets/world4/water_top_2.png"),
	preload("res://assets/world4/water_top_3.png"),
]
const WATER_OPACITY := 0.5
const WATER_COLOR := Color(0.0, 0.0, 1.0, WATER_OPACITY)

var surface_y := 0.0
var world_size := Vector2.ZERO
var animation_ticks := 0


func setup(stage_world_size: Vector2, stage_surface_y: float) -> void:
	world_size = stage_world_size
	surface_y = stage_surface_y
	queue_redraw()


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_PAUSABLE
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST


func _physics_process(_delta: float) -> void:
	animation_ticks = (animation_ticks + 1) % 60
	if animation_ticks % 20 == 0:
		queue_redraw()


func _draw() -> void:
	if world_size.x <= 0.0 or world_size.y <= surface_y:
		return
	var texture: Texture2D = TOP_TEXTURES[2 - int(animation_ticks / 20.0)]
	var body_top := surface_y + texture.get_height()
	if body_top < world_size.y:
		draw_rect(Rect2(0.0, body_top, world_size.x, world_size.y - body_top), WATER_COLOR)
	for x in range(0, ceili(world_size.x), 20):
		draw_texture(texture, Vector2(x, surface_y), Color(1.0, 1.0, 1.0, WATER_OPACITY))
