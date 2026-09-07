extends Node2D

const FINAL_STAGE_BOULDER_POSITION := Vector2(244, 211)
const FINAL_STAGE_REVEAL_TICKS := 20

const ITEMS := [
	{"label": "WIND", "world": 1, "position": Vector2(121, 88), "texture": preload("res://assets/menu/stage_wind.png"), "complete_texture": preload("res://assets/menu/stage_wind_complete.png")},
	{"label": "WATER", "world": 4, "position": Vector2(226, 88), "texture": preload("res://assets/menu/stage_water.png"), "complete_texture": preload("res://assets/menu/stage_water_complete.png")},
	{"label": "FIRE", "world": 5, "position": Vector2(332, 88), "texture": preload("res://assets/menu/stage_fire.png"), "complete_texture": preload("res://assets/menu/stage_fire_complete.png")},
	{"label": "QUIT GAME", "world": 0, "position": Vector2(439, 88), "texture": preload("res://assets/menu/quit_game.png")},
	{"label": "FINAL STAGE", "world": 7, "position": FINAL_STAGE_BOULDER_POSITION, "texture": preload("res://assets/menu/final_stage_boulder.png")},
	{"label": "SAVE GAME", "world": -1, "position": Vector2(121, 312), "texture": preload("res://assets/menu/save_game.png")},
	{"label": "THUNDER", "world": 3, "position": Vector2(226, 312), "texture": preload("res://assets/menu/stage_thunder.png"), "complete_texture": preload("res://assets/menu/stage_thunder_complete.png")},
	{"label": "ICE", "world": 6, "position": Vector2(332, 312), "texture": preload("res://assets/menu/stage_ice.png"), "complete_texture": preload("res://assets/menu/stage_ice_complete.png")},
	{"label": "SHADOW", "world": 2, "position": Vector2(439, 312), "texture": preload("res://assets/menu/stage_shadow.png"), "complete_texture": preload("res://assets/menu/stage_shadow_complete.png")},
]

var selection_x := 0
var selection_y := 0
var selector: Sprite2D
var selector_right: Sprite2D
var message_window: Control
var message_label: Label
var message_ticks := 0
var final_stage_boulder: Sprite2D
var final_stage_reveal_ticks := -1


func _ready() -> void:
	get_node("/root/AudioManager").play_music("select")
	var progress := get_node("/root/SakuraProgress")
	var reveal_final_stage: bool = progress.consume_final_stage_reveal()
	var background := Sprite2D.new()
	background.centered = false
	background.texture = preload("res://assets/menu/stage_select.png")
	background.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(background)
	for item in ITEMS:
		var sprite := Sprite2D.new()
		sprite.centered = false
		sprite.position = item["position"]
		var item_texture: Texture2D = item["texture"]
		var world_number: int = item["world"]
		if world_number >= 1 and world_number <= 6 and progress.has_boss_reward(world_number - 1):
			item_texture = item["complete_texture"]
		sprite.texture = item_texture
		sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		if world_number == 7:
			final_stage_boulder = sprite
			sprite.visible = not progress.is_final_stage_unlocked() or reveal_final_stage
			if reveal_final_stage:
				final_stage_reveal_ticks = 0
		add_child(sprite)
	selector = Sprite2D.new()
	selector.centered = false
	selector.texture = preload("res://assets/menu/selector.png")
	selector.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(selector)
	selector_right = Sprite2D.new()
	selector_right.centered = false
	selector_right.texture = preload("res://assets/menu/selector_small.png")
	selector_right.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	selector_right.flip_h = true
	add_child(selector_right)
	_build_message_window()
	_update_selection()


func _physics_process(_delta: float) -> void:
	_update_final_stage_reveal()
	if message_ticks <= 0:
		return
	message_ticks -= 1
	if message_ticks == 0:
		message_window.visible = false


func _update_final_stage_reveal() -> void:
	if final_stage_reveal_ticks < 0 or not is_instance_valid(final_stage_boulder):
		return
	final_stage_reveal_ticks += 1
	final_stage_boulder.modulate.a = maxf(
		0.0,
		float(FINAL_STAGE_REVEAL_TICKS - final_stage_reveal_ticks) / float(FINAL_STAGE_REVEAL_TICKS)
	)
	if final_stage_reveal_ticks >= FINAL_STAGE_REVEAL_TICKS:
		final_stage_boulder.visible = false
		get_node("/root/SakuraProgress").finish_final_stage_reveal()
		final_stage_reveal_ticks = -1


func _unhandled_key_input(event: InputEvent) -> void:
	if not event.pressed or event.echo:
		return
	if final_stage_reveal_ticks >= 0:
		return
	if message_ticks > 0:
		return
	if event.physical_keycode == KEY_UP:
		selection_y = wrapi(selection_y - 1, 0, 3)
		_update_selection()
	elif event.physical_keycode == KEY_DOWN:
		selection_y = wrapi(selection_y + 1, 0, 3)
		_update_selection()
	elif event.physical_keycode == KEY_LEFT and selection_y != 1:
		selection_x = wrapi(selection_x - 1, 0, 4)
		_update_selection()
	elif event.physical_keycode == KEY_RIGHT and selection_y != 1:
		selection_x = wrapi(selection_x + 1, 0, 4)
		_update_selection()
	elif event.physical_keycode == KEY_ESCAPE:
		get_node("/root/GameFlow").open_title()
	elif event.physical_keycode == KEY_ENTER or event.physical_keycode == KEY_F:
		_activate_selection()


func _update_selection() -> void:
	if selection_y == 1:
		selector.texture = preload("res://assets/menu/selector_small.png")
		selector.position = Vector2(120, 178)
		selector_right.position = Vector2(501, 178)
		selector_right.visible = true
	else:
		selector.texture = preload("res://assets/menu/selector.png")
		selector.position = Vector2(120 + selection_x * 105.5, 87 + selection_y * 112)
		selector_right.visible = false


func _activate_selection() -> void:
	var selection := 4 if selection_y == 1 else selection_x + (5 if selection_y == 2 else 0)
	var world_number: int = ITEMS[selection]["world"]
	if world_number == 0:
		get_node("/root/GameFlow").open_title()
	elif world_number == -1:
		var result: Dictionary = get_node("/root/SakuraProgress").save_game()
		_show_message(result.get("message", "Game Saved."), not result.get("ok", false))
	elif world_number == 7 and not get_node("/root/SakuraProgress").is_final_stage_unlocked():
		get_node("/root/AudioManager").play_sfx("deny")
	else:
		get_node("/root/AudioManager").play_sfx("accept")
		get_node("/root/GameFlow").start_stage(world_number)


func _build_message_window() -> void:
	message_window = Control.new()
	message_window.visible = false
	message_window.z_index = 20
	add_child(message_window)
	var window := TextureRect.new()
	window.texture = preload("res://assets/menu/dialog_window.png")
	window.position = Vector2(240, 190)
	window.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	message_window.add_child(window)
	message_label = Label.new()
	message_label.position = Vector2(240, 218)
	message_label.size = Vector2(160, 40)
	message_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	message_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	message_label.add_theme_color_override("font_color", Color.BLACK)
	message_window.add_child(message_label)


func _show_message(text: String, denied: bool) -> void:
	message_label.text = text
	message_window.visible = true
	message_ticks = 12
	get_node("/root/AudioManager").play_sfx("deny" if denied else "accept")
