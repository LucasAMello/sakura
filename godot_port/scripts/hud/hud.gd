class_name SakuraHUD
extends CanvasLayer

const LIFE_BAR := preload("res://assets/hud/hud_life_bar.png")
const CARD_NAME_TEXTURES := [
	preload("res://assets/menu/card_windy.png"), preload("res://assets/menu/card_shadow.png"), preload("res://assets/menu/card_thunder.png"),
	preload("res://assets/menu/card_watery.png"), preload("res://assets/menu/card_firey.png"), preload("res://assets/menu/card_freeze.png"),
	preload("res://assets/menu/card_arrow.png"), preload("res://assets/menu/card_big.png"), preload("res://assets/menu/card_bubbles.png"),
	preload("res://assets/menu/card_change.png"), preload("res://assets/menu/card_cloud.png"), preload("res://assets/menu/card_create.png"),
	preload("res://assets/menu/card_dark.png"), preload("res://assets/menu/card_dash.png"), preload("res://assets/menu/card_dream.png"),
	preload("res://assets/menu/card_earthy.png"), preload("res://assets/menu/card_erase.png"), preload("res://assets/menu/card_fight.png"),
	preload("res://assets/menu/card_float.png"), preload("res://assets/menu/card_flower.png"), preload("res://assets/menu/card_fly.png"),
	preload("res://assets/menu/card_glow.png"), preload("res://assets/menu/card_illusion.png"), preload("res://assets/menu/card_jump.png"),
	preload("res://assets/menu/card_libra.png"), preload("res://assets/menu/card_light.png"), preload("res://assets/menu/card_little.png"),
	preload("res://assets/menu/card_lock.png"), preload("res://assets/menu/card_loop.png"), preload("res://assets/menu/card_maze.png"),
	preload("res://assets/menu/card_mirror.png"), preload("res://assets/menu/card_mist.png"), preload("res://assets/menu/card_move.png"),
	preload("res://assets/menu/card_power.png"), preload("res://assets/menu/card_rain.png"), preload("res://assets/menu/card_return.png"),
	preload("res://assets/menu/card_sand.png"), preload("res://assets/menu/card_shield.png"), preload("res://assets/menu/card_shot.png"),
	preload("res://assets/menu/card_silent.png"), preload("res://assets/menu/card_sleep.png"), preload("res://assets/menu/card_snow.png"),
	preload("res://assets/menu/card_song.png"), preload("res://assets/menu/card_storm.png"), preload("res://assets/menu/card_sweet.png"),
	preload("res://assets/menu/card_sword.png"), preload("res://assets/menu/card_through.png"), preload("res://assets/menu/card_time.png"),
	preload("res://assets/menu/card_twin.png"), preload("res://assets/menu/card_voice.png"), preload("res://assets/menu/card_wave.png"),
	preload("res://assets/menu/card_wood.png"),
]
const CARD_RANKS := [50, 33, 44, 48, 12, 16, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 49, 51]
const CARD_WORD_POSITIONS := [
	Vector2(532, 343), Vector2(394, 243), Vector2(529, 193), Vector2(532, 294), Vector2(115, 369), Vector2(254, 144),
	Vector2(114, 69), Vector2(115, 94), Vector2(115, 118), Vector2(115, 143), Vector2(115, 168), Vector2(115, 194),
	Vector2(115, 218), Vector2(115, 243), Vector2(115, 269), Vector2(115, 293), Vector2(115, 319), Vector2(115, 343),
	Vector2(254, 68), Vector2(254, 93), Vector2(254, 118), Vector2(254, 168), Vector2(254, 193), Vector2(254, 219),
	Vector2(254, 243), Vector2(254, 268), Vector2(254, 293), Vector2(254, 318), Vector2(254, 344), Vector2(254, 369),
	Vector2(394, 69), Vector2(394, 94), Vector2(394, 119), Vector2(394, 144), Vector2(394, 169), Vector2(394, 194),
	Vector2(394, 218), Vector2(394, 268), Vector2(394, 293), Vector2(394, 318), Vector2(394, 343), Vector2(394, 369),
	Vector2(533, 69), Vector2(533, 94), Vector2(533, 119), Vector2(533, 143), Vector2(529, 168), Vector2(533, 219),
	Vector2(533, 244), Vector2(532, 269), Vector2(532, 319), Vector2(532, 368),
]

var debug_label: Label
var center_label: Label
var ready_image: TextureRect
var pause_panel: Control
var pause_label: Label
var player_bars: Array[Sprite2D] = []
var player_meter_extension: Sprite2D
var boss_bars: Array[Sprite2D] = []
var boss_meter: Sprite2D
var boss_flash: ColorRect
var completion_fade: ColorRect
var debug_visible := false
var maximum_hp_sparkle: Sprite2D
var maximum_hp_sparkle_ticks := 0
var last_maximum_hp := 15
var pause_main_page: Control
var pause_card_page: Control
var pause_options_page: Control
var pause_selector: Sprite2D
var pause_option_cursor: Sprite2D
var pause_music_bar: ColorRect
var pause_sound_bar: ColorRect
var pause_binding_window: Control
var pause_binding_label: Label
var pause_weapon_windows: Array[Sprite2D] = []
var pause_weapon_icons: Array[Sprite2D] = []
var pause_weapon_names: Array[Sprite2D] = []
var pause_life_name: Sprite2D
var pause_life_count: Sprite2D
var pause_card_the_sprites: Array[Sprite2D] = []
var pause_card_word_sprites: Array[Sprite2D] = []


func _ready() -> void:
	var player_meter := _make_sprite(preload("res://assets/hud/hud_player_meter.png"), Vector2(10, 180))
	add_child(player_meter)
	player_meter_extension = _make_sprite(preload("res://assets/hud/hud_player_meter_extended.png"), Vector2(10, 175))
	player_meter_extension.visible = false
	add_child(player_meter_extension)
	for index in range(SakuraPlayer.MAX_SUPPORTED_HP):
		var bar := _make_sprite(LIFE_BAR, Vector2(13, 259 - index * 5))
		add_child(bar)
		player_bars.append(bar)
	maximum_hp_sparkle = _make_sprite(preload("res://assets/hud/sparkle_1.png"), Vector2.ZERO)
	maximum_hp_sparkle.visible = false
	add_child(maximum_hp_sparkle)
	boss_meter = _make_sprite(preload("res://assets/hud/hud_boss_meter.png"), Vector2(610, 100))
	boss_meter.visible = false
	add_child(boss_meter)
	for index in range(30):
		var bar := _make_sprite(LIFE_BAR, Vector2(613, 254 - index * 5))
		bar.visible = false
		add_child(bar)
		boss_bars.append(bar)
	boss_flash = ColorRect.new()
	boss_flash.position = Vector2.ZERO
	boss_flash.size = Vector2(640, 480)
	boss_flash.color = Color(1, 1, 1, 0)
	boss_flash.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(boss_flash)
	debug_label = Label.new()
	debug_label.position = Vector2(36, 8)
	debug_label.size = Vector2(420, 130)
	debug_label.add_theme_color_override("font_color", Color(0.85, 1.0, 0.85))
	debug_label.add_theme_color_override("font_shadow_color", Color.BLACK)
	debug_label.add_theme_constant_override("shadow_offset_x", 1)
	debug_label.add_theme_constant_override("shadow_offset_y", 1)
	debug_label.visible = false
	add_child(debug_label)
	ready_image = TextureRect.new()
	ready_image.texture = preload("res://assets/hud/ready.png")
	ready_image.position = Vector2(241, 200)
	ready_image.size = Vector2(158, 43)
	ready_image.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	ready_image.stretch_mode = TextureRect.STRETCH_KEEP
	ready_image.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(ready_image)
	pause_panel = Control.new()
	pause_panel.position = Vector2.ZERO
	pause_panel.visible = false
	add_child(pause_panel)
	_build_pause_menu()
	pause_label = Label.new()
	pause_label.visible = false
	add_child(pause_label)
	completion_fade = ColorRect.new()
	completion_fade.position = Vector2.ZERO
	completion_fade.size = Vector2(640, 480)
	completion_fade.color = Color(0, 0, 0, 0)
	completion_fade.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(completion_fade)
	center_label = Label.new()
	center_label.position = Vector2(70, 180)
	center_label.size = Vector2(500, 120)
	center_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	center_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	center_label.add_theme_font_size_override("font_size", 24)
	center_label.add_theme_color_override("font_color", Color.WHITE)
	center_label.add_theme_color_override("font_shadow_color", Color(0.25, 0.0, 0.15))
	center_label.add_theme_constant_override("shadow_offset_x", 2)
	center_label.add_theme_constant_override("shadow_offset_y", 2)
	center_label.visible = false
	add_child(center_label)


func _make_sprite(texture: Texture2D, sprite_position: Vector2) -> Sprite2D:
	var result := Sprite2D.new()
	result.centered = false
	result.texture = texture
	result.position = sprite_position
	result.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	return result


func _build_pause_menu() -> void:
	pause_main_page = Control.new()
	pause_panel.add_child(pause_main_page)
	var main_background := _make_pause_background(0)
	pause_main_page.add_child(main_background)
	var weapon_cells := [Vector2(63, 92), Vector2(353, 92), Vector2(63, 152), Vector2(353, 152), Vector2(63, 212), Vector2(353, 212), Vector2(63, 272)]
	for cell in weapon_cells:
		var window := _make_sprite(preload("res://assets/menu/menuwindow2.png"), cell)
		window.visible = false
		pause_main_page.add_child(window)
		pause_weapon_windows.append(window)
	pause_selector = _make_sprite(preload("res://assets/menu/menuwindow.png"), Vector2(63, 92))
	pause_main_page.add_child(pause_selector)
	var icon_data := [
		[preload("res://assets/player/default_shot.png"), Vector2(89, 109)],
		[preload("res://assets/menu/menuwindy.png"), Vector2(359, 103)],
		[preload("res://assets/player/thunder_shot_1.png"), Vector2(83, 159)],
		[preload("res://assets/player/water_shot.png"), Vector2(370, 160)],
		[preload("res://assets/world6/boss_attack_4.png"), Vector2(71, 225)],
		[preload("res://assets/player/fire_shot_1.png"), Vector2(366, 222)],
		[preload("res://assets/player/shadow_shot.png"), Vector2(80, 279)],
	]
	for data in icon_data:
		var icon := _make_sprite(data[0], data[1])
		pause_main_page.add_child(icon)
		pause_weapon_icons.append(icon)
	var name_textures := [
		preload("res://assets/menu/menu_ma2.png"), preload("res://assets/menu/menu_wi.png"),
		preload("res://assets/menu/menu_th.png"), preload("res://assets/menu/menu_wa.png"),
		preload("res://assets/menu/menu_fr.png"), preload("res://assets/menu/menu_fi.png"),
		preload("res://assets/menu/menu_sh.png"),
	]
	var name_positions := [Vector2(140, 104), Vector2(429, 104), Vector2(140, 164), Vector2(429, 164), Vector2(140, 224), Vector2(429, 224), Vector2(140, 284)]
	for index in range(name_textures.size()):
		var name_sprite := _make_sprite(name_textures[index], name_positions[index])
		pause_main_page.add_child(name_sprite)
		pause_weapon_names.append(name_sprite)
	pause_main_page.add_child(_make_sprite(preload("res://assets/menu/exit.png"), Vector2(360, 284)))
	pause_life_name = _make_sprite(preload("res://assets/menu/vida.png"), Vector2(364, 341))
	pause_main_page.add_child(pause_life_name)
	pause_life_count = _make_sprite(preload("res://assets/menu/v5.png"), Vector2(421, 349))
	pause_main_page.add_child(pause_life_count)
	pause_card_page = Control.new()
	pause_panel.add_child(pause_card_page)
	pause_card_page.add_child(_make_pause_background(640))
	var the_texture := preload("res://assets/menu/card_the.png")
	for card_id in range(CARD_NAME_TEXTURES.size()):
		var rank: int = CARD_RANKS[card_id]
		var the_sprite := _make_sprite(the_texture, Vector2([71, 210, 350, 489][int(rank / 13.0)], 68 + (rank % 13) * 25))
		pause_card_page.add_child(the_sprite)
		pause_card_the_sprites.append(the_sprite)
		var word_sprite := _make_sprite(CARD_NAME_TEXTURES[card_id], CARD_WORD_POSITIONS[card_id])
		pause_card_page.add_child(word_sprite)
		pause_card_word_sprites.append(word_sprite)
	pause_card_page.visible = false
	_build_pause_options_page()


func _make_pause_background(source_x: int) -> Sprite2D:
	var sprite := _make_sprite(preload("res://assets/menu/menu.png"), Vector2.ZERO)
	sprite.region_enabled = true
	sprite.region_rect = Rect2(source_x, 0, 640, 480)
	return sprite


func _build_pause_options_page() -> void:
	pause_options_page = Control.new()
	pause_options_page.visible = false
	pause_panel.add_child(pause_options_page)
	pause_options_page.add_child(_make_sprite(preload("res://assets/menu/options.png"), Vector2.ZERO))
	pause_option_cursor = _make_sprite(preload("res://assets/menu/pisk.png"), Vector2(132, 158))
	pause_options_page.add_child(pause_option_cursor)
	pause_music_bar = ColorRect.new()
	pause_music_bar.position = Vector2(381, 152)
	pause_music_bar.color = Color8(98, 78, 253)
	pause_options_page.add_child(pause_music_bar)
	pause_sound_bar = ColorRect.new()
	pause_sound_bar.position = Vector2(381, 207)
	pause_sound_bar.color = Color8(98, 78, 253)
	pause_options_page.add_child(pause_sound_bar)
	pause_binding_window = Control.new()
	pause_binding_window.visible = false
	pause_options_page.add_child(pause_binding_window)
	pause_binding_window.add_child(_make_sprite(preload("res://assets/menu/dialog_window.png"), Vector2(240, 190)))
	pause_binding_label = Label.new()
	pause_binding_label.position = Vector2(245, 218)
	pause_binding_label.size = Vector2(150, 42)
	pause_binding_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	pause_binding_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	pause_binding_label.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
	pause_binding_label.add_theme_font_size_override("font_size", 11)
	pause_binding_label.add_theme_color_override("font_color", Color.BLACK)
	pause_binding_window.add_child(pause_binding_label)


func _pause_selector_position(column: int, row: int) -> Vector2:
	if row < 4:
		pause_selector.texture = preload("res://assets/menu/menuwindow.png")
		return Vector2(63 if column == 0 else 353, 92 + row * 60)
	if row == 4:
		pause_selector.texture = preload("res://assets/menu/menuoptions.png")
		return Vector2(67, 347)
	pause_selector.texture = preload("res://assets/menu/menuback.png") if column == 0 else preload("res://assets/menu/arrow_next.png")
	return Vector2(179, 425) if column == 0 else Vector2(513, 404)


func _update_pause_weapons(player: SakuraPlayer, progress: Node) -> void:
	var weapon_ids := [1, 2, 4, 5, 7, 6, 3]
	var selected_textures := [
		preload("res://assets/menu/menu_ma2.png"), preload("res://assets/menu/menu_wi2.png"),
		preload("res://assets/menu/menu_th2.png"), preload("res://assets/menu/menu_wa2.png"),
		preload("res://assets/menu/menu_fr2.png"), preload("res://assets/menu/menu_fi2.png"),
		preload("res://assets/menu/menu_sh2.png"),
	]
	var normal_textures := [
		null, preload("res://assets/menu/menu_wi.png"),
		preload("res://assets/menu/menu_th.png"), preload("res://assets/menu/menu_wa.png"),
		preload("res://assets/menu/menu_fr.png"), preload("res://assets/menu/menu_fi.png"),
		preload("res://assets/menu/menu_sh.png"),
	]
	for index in range(weapon_ids.size()):
		var unlocked: bool = progress.is_weapon_unlocked(weapon_ids[index])
		pause_weapon_windows[index].visible = unlocked and weapon_ids[index] != 1
		pause_weapon_icons[index].visible = unlocked
		pause_weapon_names[index].visible = unlocked and (weapon_ids[index] != 1 or player.current_weapon == 1)
		pause_weapon_names[index].texture = selected_textures[index] if player.current_weapon == weapon_ids[index] else normal_textures[index]
	var life_textures := [
		preload("res://assets/menu/vida.png"), preload("res://assets/menu/vidaa.png"), preload("res://assets/menu/vidab.png"),
		preload("res://assets/menu/vidac.png"), preload("res://assets/menu/vidad.png"), preload("res://assets/menu/vidae.png"), preload("res://assets/menu/vidaf.png"),
	]
	pause_life_name.texture = life_textures[player.current_weapon - 1]
	var life_textures_count := [
		preload("res://assets/menu/v0.png"), preload("res://assets/menu/v1.png"), preload("res://assets/menu/v2.png"), preload("res://assets/menu/v3.png"), preload("res://assets/menu/v4.png"),
		preload("res://assets/menu/v5.png"), preload("res://assets/menu/v6.png"), preload("res://assets/menu/v7.png"), preload("res://assets/menu/v8.png"), preload("res://assets/menu/v9.png"),
	]
	pause_life_count.texture = life_textures_count[clampi(player.lives, 0, 9)]


func _update_pause_cards(progress: Node) -> void:
	for card_id in range(52):
		var collected: bool = progress.has_card(card_id)
		pause_card_the_sprites[card_id].visible = collected
		pause_card_word_sprites[card_id].visible = collected


func update_status(player: SakuraPlayer, _stage_state: String, enemy_count: int, map_number: int, world_size: Vector2) -> void:
	last_maximum_hp = player.maximum_hp
	player_meter_extension.visible = player.maximum_hp > 15
	player_meter_extension.position.y = 180.0 - float(player.maximum_hp - 15) * 5.0
	for index in range(player_bars.size()):
		player_bars[index].visible = index < player.hp
	_update_maximum_hp_sparkle()
	debug_label.text = "F3 compatibility view\nmap: %d  position: (%d, %d) / (%d, %d)\nvelocity: (%.2f, %.2f)  grounded: %s\nimmunity: %d  lives: %d  enemies: %d  tick rate: 60 Hz" % [map_number, int(player.position.x), int(player.position.y), int(world_size.x), int(world_size.y), player.x_speed, player.y_speed, str(player.grounded), player.immunity_ticks, player.lives, enemy_count]


func show_maximum_hp_sparkle(maximum_hp: int) -> void:
	last_maximum_hp = maximum_hp
	maximum_hp_sparkle_ticks = 1


func _update_maximum_hp_sparkle() -> void:
	if maximum_hp_sparkle_ticks <= 0:
		maximum_hp_sparkle.visible = false
		return
	var frame := mini(int((maximum_hp_sparkle_ticks - 1) / 8.0), 3)
	maximum_hp_sparkle.texture = [
		preload("res://assets/hud/sparkle_1.png"),
		preload("res://assets/hud/sparkle_2.png"),
		preload("res://assets/hud/sparkle_3.png"),
		preload("res://assets/hud/sparkle_4.png"),
	][frame]
	maximum_hp_sparkle.position = Vector2(0, 185 - 5 * (last_maximum_hp - 15))
	maximum_hp_sparkle.visible = true
	maximum_hp_sparkle_ticks += 1
	if maximum_hp_sparkle_ticks >= 33:
		maximum_hp_sparkle_ticks = 0


func set_boss_health(current_hp: int, show_boss_health: bool) -> void:
	boss_meter.visible = show_boss_health
	for index in range(boss_bars.size()):
		boss_bars[index].visible = show_boss_health and index < current_hp


func set_ready_visible(value: bool) -> void:
	ready_image.visible = value


func set_paused(value: bool) -> void:
	pause_panel.visible = value
	pause_label.visible = false


func set_pause_selection(column: int, row: int, page: int, option_selection: int, binding_index: int, player: SakuraPlayer, settings: Node, progress: Node) -> void:
	pause_main_page.visible = page == 0
	pause_card_page.visible = page == 1
	pause_options_page.visible = page == 2
	if page == 0:
		pause_selector.position = _pause_selector_position(column, row)
		_update_pause_weapons(player, progress)
	elif page == 1:
		_update_pause_cards(progress)
	else:
		var cursor_positions := [Vector2(132, 158), Vector2(132, 215), Vector2(132, 268), Vector2(216, 332)]
		pause_option_cursor.position = cursor_positions[option_selection]
		pause_music_bar.size = Vector2(roundi(settings.music_volume * 100.0), 19)
		pause_sound_bar.size = Vector2(roundi(settings.sfx_volume * 100.0), 19)
		pause_binding_window.visible = binding_index >= 0
		if binding_index >= 0:
			pause_binding_label.text = [
				"Press Up Key", "Press Down Key", "Press Right Key", "Press Left Key", "Press Jump Key",
				"Press Fire Key", "Press Card Change (Right) Key", "Press Card Change (Left) Key", "Press Start Key", "Press Quit Key",
			][binding_index]


func set_completion_fade(alpha: float) -> void:
	completion_fade.color.a = clampf(alpha, 0.0, 1.0)


func set_boss_flash(alpha: float) -> void:
	boss_flash.color.a = clampf(alpha, 0.0, 1.0)


func show_message(text: String) -> void:
	center_label.text = text
	center_label.visible = true


func hide_message() -> void:
	center_label.visible = false


func toggle_debug() -> void:
	debug_visible = not debug_visible
	debug_label.visible = debug_visible
