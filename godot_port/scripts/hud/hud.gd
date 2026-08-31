class_name SakuraHUD
extends CanvasLayer

const LIFE_BAR := preload("res://assets/hud/hud_life_bar.png")

var debug_label: Label
var center_label: Label
var ready_image: TextureRect
var pause_panel: ColorRect
var pause_label: Label
var player_bars: Array[Sprite2D] = []
var boss_bars: Array[Sprite2D] = []
var boss_meter: Sprite2D
var boss_flash: ColorRect
var completion_fade: ColorRect
var debug_visible := false


func _ready() -> void:
	var player_meter := _make_sprite(preload("res://assets/hud/hud_player_meter.png"), Vector2(10, 80))
	add_child(player_meter)
	for index in range(SakuraPlayer.MAX_HP):
		var bar := _make_sprite(LIFE_BAR, Vector2(13, 159 - index * 5))
		add_child(bar)
		player_bars.append(bar)
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
	pause_panel = ColorRect.new()
	pause_panel.position = Vector2.ZERO
	pause_panel.size = Vector2(640, 480)
	pause_panel.color = Color(0.04, 0.01, 0.06, 0.72)
	pause_panel.visible = false
	add_child(pause_panel)
	pause_label = Label.new()
	pause_label.position = Vector2(70, 170)
	pause_label.size = Vector2(500, 140)
	pause_label.text = "PAUSED\n\nENTER  RESUME     R  RESTART     ESC  QUIT"
	pause_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	pause_label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	pause_label.add_theme_font_size_override("font_size", 20)
	pause_label.add_theme_color_override("font_color", Color.WHITE)
	pause_label.add_theme_color_override("font_shadow_color", Color(0.25, 0.0, 0.15))
	pause_label.add_theme_constant_override("shadow_offset_x", 2)
	pause_label.add_theme_constant_override("shadow_offset_y", 2)
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


func update_status(player: SakuraPlayer, _stage_state: String, enemy_count: int, map_number: int, world_size: Vector2) -> void:
	for index in range(player_bars.size()):
		player_bars[index].visible = index < player.hp
	debug_label.text = "F3 compatibility view\nmap: %d  position: (%d, %d) / (%d, %d)\nvelocity: (%.2f, %.2f)  grounded: %s\nimmunity: %d  lives: %d  enemies: %d  tick rate: 60 Hz" % [map_number, int(player.position.x), int(player.position.y), int(world_size.x), int(world_size.y), player.x_speed, player.y_speed, str(player.grounded), player.immunity_ticks, player.lives, enemy_count]


func set_boss_health(current_hp: int, show_boss_health: bool) -> void:
	boss_meter.visible = show_boss_health
	for index in range(boss_bars.size()):
		boss_bars[index].visible = show_boss_health and index < current_hp


func set_ready_visible(value: bool) -> void:
	ready_image.visible = value


func set_paused(value: bool) -> void:
	pause_panel.visible = value
	pause_label.visible = value


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
