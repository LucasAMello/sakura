class_name World5LavaStrip
extends Node2D

const FRAMES := [
	preload("res://assets/world5/lava_1.png"),
	preload("res://assets/world5/lava_2.png"),
	preload("res://assets/world5/lava_3.png"),
]

var player: SakuraPlayer
var strip_width := 60
var timer := 0
var gameplay_active := false
var foreground := false


func _ready() -> void:
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST


func setup(target_player: SakuraPlayer, width: int, draws_foreground: bool = false) -> void:
	player = target_player
	strip_width = width
	foreground = draws_foreground
	queue_redraw()


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func _physics_process(_delta: float) -> void:
	if not gameplay_active:
		return
	timer += 1
	if timer % 15 == 0:
		queue_redraw()
	if not foreground and is_instance_valid(player) and Rect2(position, Vector2(strip_width, 20)).intersects(player.get_hit_rect()):
		player.take_damage(4)


func _draw() -> void:
	var texture: Texture2D = FRAMES[int(timer / 15.0) % FRAMES.size()]
	var source_y := 10 if foreground else 0
	var offset := 0
	while offset < strip_width:
		var width := mini(60, strip_width - offset)
		draw_texture_rect_region(texture, Rect2(offset, source_y, width, 10), Rect2(0, source_y, width, 10))
		offset += 60
