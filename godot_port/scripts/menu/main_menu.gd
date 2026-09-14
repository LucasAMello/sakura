extends Node2D

enum Screen { TITLE, MENU, OPTIONS }

const MENU_ITEMS := ["NEW GAME", "LOAD GAME", "OPTIONS", "QUIT"]
const MENU_POSITIONS := [Vector2(220, 65), Vector2(220, 160), Vector2(220, 255), Vector2(220, 350)]
const MENU_CARD_FRAMES := [
	[preload("res://assets/menu/new_game_1.png"), preload("res://assets/menu/new_game_2.png"), preload("res://assets/menu/new_game_3.png"), preload("res://assets/menu/new_game_4.png")],
	[preload("res://assets/menu/load_game_1.png"), preload("res://assets/menu/load_game_2.png"), preload("res://assets/menu/load_game_3.png"), preload("res://assets/menu/load_game_4.png")],
	[preload("res://assets/menu/options_1.png"), preload("res://assets/menu/options_2.png"), preload("res://assets/menu/options_3.png"), preload("res://assets/menu/options_4.png")],
	[preload("res://assets/menu/quit_1.png"), preload("res://assets/menu/quit_2.png"), preload("res://assets/menu/quit_3.png"), preload("res://assets/menu/quit_4.png")],
]
const CARD_BACK_FRAMES := [
	preload("res://assets/menu/card_back_1.png"),
	preload("res://assets/menu/card_back_2.png"),
	preload("res://assets/menu/card_back_3.png"),
]
const CONTROL_ACTIONS := [
	["Press Up Key", "move_up"], ["Press Down Key", "move_down"],
	["Press Right Key", "move_right"], ["Press Left Key", "move_left"],
	["Press Jump Key", "jump"], ["Press Fire Key", "fire"],
	["Press Card Change (Right) Key", "weapon_next"], ["Press Card Change (Left) Key", "weapon_previous"],
	["Press Start Key", "pause"], ["Press Quit Key", "quit"],
]

var screen := Screen.TITLE
var selection := 0
var background: Sprite2D
var menu_cards: Array[Sprite2D] = []
var left_staff: Sprite2D
var right_staff: Sprite2D
var message_label: Label
var options_panel: Control
var music_slider: HSlider
var sfx_slider: HSlider
var option_selection := 0
var option_labels: Array[Label] = []
var binding_action := ""
var binding_index := -1
var option_cursor: Sprite2D
var music_bar: ColorRect
var sound_bar: ColorRect
var binding_window: Control
var binding_label: Label
var load_error_window: Control
var load_error_label: Label
var load_error_visible := false
var load_success_ticks := 0
var card_timer := 0


func _ready() -> void:
	get_node("/root/AudioManager").play_music("title")
	_build_background()
	_build_menu()
	_build_options()
	_show_title()


func _physics_process(_delta: float) -> void:
	if screen != Screen.MENU:
		return
	if load_success_ticks > 0:
		load_success_ticks -= 1
		if load_success_ticks == 0:
			get_node("/root/GameFlow").open_stage_select()
		return
	card_timer += 1
	if card_timer == 105:
		card_timer = -90
	_update_card_textures()


func _unhandled_key_input(event: InputEvent) -> void:
	if not event.pressed or event.echo:
		return
	if load_success_ticks > 0:
		return
	if load_error_visible:
		if event.physical_keycode == KEY_ENTER or event.physical_keycode == KEY_F:
			load_error_visible = false
			load_error_window.visible = false
		return
	if screen == Screen.TITLE:
		if event.physical_keycode == KEY_ENTER or event.physical_keycode == KEY_F:
			get_node("/root/AudioManager").play_sfx("accept")
			_show_menu()
		return
	if screen == Screen.OPTIONS:
		if binding_action != "":
			if event.physical_keycode == KEY_ESCAPE:
				binding_action = ""
				binding_index = -1
			else:
				get_node("/root/SakuraSettings").set_key(binding_action, event.physical_keycode)
				get_node("/root/AudioManager").play_sfx("accept")
				binding_index += 1
				if binding_index < CONTROL_ACTIONS.size():
					binding_action = CONTROL_ACTIONS[binding_index][1]
				else:
					binding_action = ""
					binding_index = -1
			_update_options()
			return
		get_node("/root/SakuraProgress").enter_cheat_code(event.physical_keycode)
		if event.physical_keycode == KEY_ESCAPE:
			_show_menu()
		elif event.physical_keycode == KEY_UP:
			option_selection = wrapi(option_selection - 1, 0, 4)
			_update_options()
		elif event.physical_keycode == KEY_DOWN:
			option_selection = wrapi(option_selection + 1, 0, 4)
			_update_options()
		elif event.physical_keycode == KEY_LEFT:
			_adjust_option(-1)
		elif event.physical_keycode == KEY_RIGHT:
			_adjust_option(1)
		elif event.physical_keycode == KEY_ENTER or event.physical_keycode == KEY_F:
			_activate_option()
		return
	if event.physical_keycode == KEY_UP:
		selection = wrapi(selection - 1, 0, MENU_ITEMS.size())
		card_timer = 0
		_update_selection()
	elif event.physical_keycode == KEY_DOWN:
		selection = wrapi(selection + 1, 0, MENU_ITEMS.size())
		card_timer = 0
		_update_selection()
	elif event.physical_keycode == KEY_ENTER or event.physical_keycode == KEY_F:
		_activate_selection()


func _build_background() -> void:
	background = Sprite2D.new()
	background.centered = false
	background.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(background)


func _build_menu() -> void:
	for index in range(MENU_ITEMS.size()):
		var card := Sprite2D.new()
		card.centered = false
		card.position = MENU_POSITIONS[index]
		card.texture = MENU_CARD_FRAMES[index][0]
		card.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
		add_child(card)
		menu_cards.append(card)
	left_staff = _make_staff(false)
	right_staff = _make_staff(true)
	message_label = Label.new()
	message_label.position = Vector2(0, 454)
	message_label.size = Vector2(640, 22)
	message_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	message_label.add_theme_font_size_override("font_size", 12)
	message_label.add_theme_color_override("font_color", Color.WHITE)
	message_label.add_theme_color_override("font_shadow_color", Color.BLACK)
	message_label.add_theme_constant_override("shadow_offset_x", 1)
	message_label.add_theme_constant_override("shadow_offset_y", 1)
	add_child(message_label)
	load_error_window = Control.new()
	load_error_window.visible = false
	load_error_window.z_index = 20
	add_child(load_error_window)
	var load_dialog := TextureRect.new()
	load_dialog.texture = preload("res://assets/menu/dialog_window.png")
	load_dialog.position = Vector2(240, 190)
	load_dialog.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	load_error_window.add_child(load_dialog)
	load_error_label = Label.new()
	load_error_label.position = Vector2(245, 218)
	load_error_label.size = Vector2(150, 42)
	load_error_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	load_error_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	load_error_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	load_error_label.add_theme_color_override("font_color", Color.BLACK)
	load_error_window.add_child(load_error_label)


func _make_staff(flipped: bool) -> Sprite2D:
	var staff := Sprite2D.new()
	staff.centered = false
	staff.texture = preload("res://assets/menu/menu_staff.png")
	staff.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	staff.flip_h = flipped
	staff.position = Vector2(461 if flipped else 70, MENU_POSITIONS[selection].y)
	add_child(staff)
	return staff


func _build_options() -> void:
	options_panel = Control.new()
	options_panel.visible = false
	add_child(options_panel)
	var options_background := TextureRect.new()
	options_background.texture = preload("res://assets/menu/options.png")
	options_background.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	options_panel.add_child(options_background)
	option_cursor = _make_menu_sprite(preload("res://assets/menu/pisk.png"), Vector2(132, 158))
	options_panel.add_child(option_cursor)
	music_bar = ColorRect.new()
	music_bar.position = Vector2(381, 152)
	music_bar.color = Color8(98, 78, 253)
	options_panel.add_child(music_bar)
	sound_bar = ColorRect.new()
	sound_bar.position = Vector2(381, 207)
	sound_bar.color = Color8(98, 78, 253)
	options_panel.add_child(sound_bar)
	binding_window = Control.new()
	binding_window.visible = false
	binding_window.z_index = 10
	options_panel.add_child(binding_window)
	var dialog := TextureRect.new()
	dialog.texture = preload("res://assets/menu/dialog_window.png")
	dialog.position = Vector2(240, 190)
	dialog.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	binding_window.add_child(dialog)
	binding_label = Label.new()
	binding_label.position = Vector2(245, 218)
	binding_label.size = Vector2(150, 42)
	binding_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	binding_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	binding_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	binding_label.add_theme_font_size_override("font_size", 11)
	binding_label.add_theme_color_override("font_color", Color.BLACK)
	binding_window.add_child(binding_label)


func _make_menu_sprite(texture: Texture2D, sprite_position: Vector2) -> Sprite2D:
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.texture = texture
	sprite.position = sprite_position
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	return sprite


func _make_option_label(text: String, position_value: Vector2, size_value: Vector2, font_size: int) -> Label:
	var label := Label.new()
	label.text = text
	label.position = position_value
	label.size = size_value
	label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	label.add_theme_font_size_override("font_size", font_size)
	label.add_theme_color_override("font_color", Color.WHITE)
	return label


func _make_slider(position_value: Vector2, value: float) -> HSlider:
	var slider := HSlider.new()
	slider.position = position_value
	slider.size = Vector2(220, 28)
	slider.min_value = 0.0
	slider.max_value = 1.0
	slider.step = 0.01
	slider.value = value
	return slider


func _show_title() -> void:
	screen = Screen.TITLE
	background.texture = preload("res://assets/menu/title.png")
	for card in menu_cards:
		card.visible = false
	left_staff.visible = false
	right_staff.visible = false
	message_label.visible = false
	options_panel.visible = false
	load_error_visible = false
	load_error_window.visible = false


func _show_menu() -> void:
	screen = Screen.MENU
	background.texture = preload("res://assets/menu/main_menu.png")
	for card in menu_cards:
		card.visible = true
	left_staff.visible = true
	right_staff.visible = true
	message_label.visible = true
	message_label.text = ""
	options_panel.visible = false
	load_error_visible = false
	load_error_window.visible = false
	card_timer = 0
	_update_selection()


func _show_options() -> void:
	get_node("/root/SakuraProgress").cheat_code_index = 0
	screen = Screen.OPTIONS
	for card in menu_cards:
		card.visible = false
	left_staff.visible = false
	right_staff.visible = false
	message_label.visible = false
	options_panel.visible = true
	option_selection = 0
	binding_action = ""
	binding_index = -1
	_update_options()


func _adjust_option(direction: int) -> void:
	var settings := get_node("/root/SakuraSettings")
	if option_selection == 0:
		settings.set_music_volume(clampf(settings.music_volume + direction, 0.0, 1.0))
	elif option_selection == 1:
		settings.set_sfx_volume(settings.sfx_volume + direction / 255.0)
	_update_options()


func _activate_option() -> void:
	if option_selection == 2:
		binding_index = 0
		binding_action = CONTROL_ACTIONS[0][1]
		_update_options()
	elif option_selection == 3:
		_show_menu()


func _update_options() -> void:
	var settings := get_node("/root/SakuraSettings")
	var cursor_positions := [Vector2(132, 158), Vector2(132, 215), Vector2(132, 268), Vector2(216, 332)]
	option_cursor.position = cursor_positions[option_selection]
	music_bar.size = Vector2(roundi(settings.music_volume * 100.0), 19)
	sound_bar.size = Vector2(roundi(settings.sfx_volume * 100.0), 19)
	binding_window.visible = binding_action != ""
	if binding_index >= 0:
		binding_label.text = CONTROL_ACTIONS[binding_index][0]


func _update_selection() -> void:
	left_staff.position.y = MENU_POSITIONS[selection].y
	right_staff.position.y = MENU_POSITIONS[selection].y
	_update_card_textures()


func _update_card_textures() -> void:
	for index in range(menu_cards.size()):
		menu_cards[index].texture = _selected_card_texture(index) if index == selection else MENU_CARD_FRAMES[index][0]


func _selected_card_texture(index: int) -> Texture2D:
	if card_timer < 50:
		return MENU_CARD_FRAMES[index][0]
	if card_timer < 55:
		return MENU_CARD_FRAMES[index][1]
	if card_timer < 60:
		return MENU_CARD_FRAMES[index][2]
	if card_timer < 65:
		return MENU_CARD_FRAMES[index][3]
	if card_timer < 70:
		return CARD_BACK_FRAMES[2]
	if card_timer < 75:
		return CARD_BACK_FRAMES[1]
	if card_timer < 80:
		return CARD_BACK_FRAMES[0]
	if card_timer < 85:
		return CARD_BACK_FRAMES[1]
	if card_timer < 90:
		return CARD_BACK_FRAMES[2]
	if card_timer < 95:
		return MENU_CARD_FRAMES[index][3]
	if card_timer < 100:
		return MENU_CARD_FRAMES[index][2]
	return MENU_CARD_FRAMES[index][1]


func _activate_selection() -> void:
	get_node("/root/AudioManager").play_sfx("accept")
	match selection:
		0:
			get_node("/root/GameFlow").start_new_game()
		1:
			var result: Dictionary = get_node("/root/GameFlow").load_game(false)
			if result.get("ok", false):
				load_error_label.text = result.get("message", "Game Loaded")
				load_error_window.visible = true
				load_success_ticks = 60
			else:
				get_node("/root/AudioManager").play_sfx("deny")
				load_error_label.text = result.get("message", "File not found.")
				load_error_visible = true
				load_error_window.visible = true
		2:
			_show_options()
		3:
			get_tree().quit()
