extends Node2D

const PRELUDE_SILENCE_TICK := 300
const PRELUDE_END_TICK := 600
const PANEL_FADE_TICKS := 255
const PANEL_FADE_OUT_START := 1400
const PANEL_DURATION := 1655
const BACKGROUNDS := [
	preload("res://assets/world1/background.png"), preload("res://assets/world2/background.png"),
	preload("res://assets/world3/background.png"), preload("res://assets/world4/background.png"),
	preload("res://assets/world5/background.png"), preload("res://assets/world6/background.png"),
]
const PANELS := [
	preload("res://assets/ending/ending1.png"), preload("res://assets/ending/ending2.png"),
	preload("res://assets/ending/ending3.png"), preload("res://assets/ending/ending4.png"),
	preload("res://assets/ending/ending5.png"), preload("res://assets/ending/ending6.png"),
]
const CREDITS := [
	preload("res://assets/ending/credits1.png"), preload("res://assets/ending/credits2.png"),
	preload("res://assets/ending/credits3.png"), preload("res://assets/ending/credits4.png"),
	preload("res://assets/ending/credits5.png"), preload("res://assets/ending/credits6.png"),
]
const PLAYER_FRAMES := [
	preload("res://assets/player/player_idle.png"), preload("res://assets/player/player_walk2.png"),
	preload("res://assets/player/player_jump.png"), preload("res://assets/player/player_walk2.png"),
	preload("res://assets/player/player_idle.png"), preload("res://assets/player/player_walk4.png"),
	preload("res://assets/player/player_walk5.png"), preload("res://assets/player/player_walk4.png"),
]

var background_a: Sprite2D
var background_b: Sprite2D
var reflection_a: Sprite2D
var reflection_b: Sprite2D
var ground_sprites: Array[Sprite2D] = []
var player_sprite: Sprite2D
var credit_sprite: Sprite2D
var fade: ColorRect
var final_layer: Control
var panel_index := 0
var panel_ticks := 0
var prelude_ticks := 0
var scroll_x := 0.0
var player_walk_ticks := 0
var finished := false
var credits_started := false
var panel_hold_ticks := 0
var final_hold_ticks := 0


func _ready() -> void:
	_build_scene()
	_show_panel(0)


func _physics_process(_delta: float) -> void:
	if finished:
		return
	if prelude_ticks < PRELUDE_END_TICK:
		prelude_ticks += 1
		if prelude_ticks == PRELUDE_SILENCE_TICK:
			get_node("/root/AudioManager").stop_music()
		elif prelude_ticks == PRELUDE_END_TICK:
			get_node("/root/AudioManager").play_music("ending", true)
		return
	if final_hold_ticks > 0:
		final_hold_ticks -= 1
		if final_hold_ticks == 0:
			_show_final()
		return
	if panel_hold_ticks > 0:
		panel_hold_ticks -= 1
		return
	panel_ticks += 1
	scroll_x += 1.0
	player_walk_ticks += 1
	var background_offset := -160.0 + float(panel_ticks * 2) / 20.0
	background_a.position.x = background_offset
	background_b.position.x = background_offset + background_a.texture.get_width()
	reflection_a.position.x = background_a.position.x
	reflection_b.position.x = background_b.position.x
	var tile_width := 120.0 if panel_index == 5 else 160.0
	var ground_offset := fmod(scroll_x, tile_width) - tile_width
	for index in range(ground_sprites.size()):
		ground_sprites[index].position.x = ground_offset + index * tile_width
	if player_walk_ticks % 8 == 0:
		player_sprite.texture = PLAYER_FRAMES[int(player_walk_ticks / 8.0) % PLAYER_FRAMES.size()]
	if panel_ticks % 20 == 0:
		player_sprite.position.x -= 1.0
	if panel_ticks >= 300:
		credits_started = true
	if credits_started:
		if panel_ticks < 1300:
			credit_sprite.modulate.a = minf(1.0, credit_sprite.modulate.a + 1.0 / 255.0)
		else:
			credit_sprite.modulate.a = maxf(0.0, credit_sprite.modulate.a - 1.0 / 255.0)
	if panel_ticks < PANEL_FADE_TICKS:
		fade.color.a = 1.0 - float(panel_ticks) / PANEL_FADE_TICKS
	elif panel_ticks >= PANEL_FADE_OUT_START:
		fade.color.a = float(panel_ticks - PANEL_FADE_OUT_START) / PANEL_FADE_TICKS
	else:
		fade.color.a = 0.0
	if panel_ticks >= PANEL_DURATION:
		panel_index += 1
		if panel_index >= PANELS.size():
			_begin_final_hold()
		else:
			_show_panel(panel_index, 60)


func _unhandled_key_input(event: InputEvent) -> void:
	if not event.pressed or event.echo or not finished:
		return
	if event.physical_keycode == KEY_ENTER:
		get_node("/root/GameFlow").open_title()


func _build_scene() -> void:
	var fill := ColorRect.new()
	fill.size = Vector2(640, 480)
	fill.color = Color8(15, 0, 0)
	add_child(fill)
	background_a = _make_sprite(Vector2.ZERO, -20)
	background_b = _make_sprite(Vector2(640, 0), -20)
	reflection_a = _make_sprite(Vector2(0, 150), -19)
	reflection_b = _make_sprite(Vector2(640, 150), -19)
	reflection_a.flip_h = true
	reflection_b.flip_h = true
	add_child(background_a)
	add_child(background_b)
	add_child(reflection_a)
	add_child(reflection_b)
	for index in range(7):
		var ground := _make_sprite(Vector2(index * 160, 380), 0)
		add_child(ground)
		ground_sprites.append(ground)
	player_sprite = _make_sprite(Vector2(540, 300), 5)
	player_sprite.flip_h = true
	add_child(player_sprite)
	credit_sprite = _make_sprite(Vector2.ZERO, 10)
	add_child(credit_sprite)
	final_layer = Control.new()
	final_layer.visible = false
	final_layer.z_index = 20
	add_child(final_layer)
	var thanks := TextureRect.new()
	thanks.texture = preload("res://assets/ending/thanks.png")
	thanks.position = Vector2(125, 180)
	thanks.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	final_layer.add_child(thanks)
	var the_end := TextureRect.new()
	the_end.texture = preload("res://assets/ending/theend.png")
	the_end.position = Vector2(458, 439)
	the_end.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	final_layer.add_child(the_end)
	fade = ColorRect.new()
	fade.size = Vector2(640, 480)
	fade.color = Color.BLACK
	fade.z_index = 30
	add_child(fade)


func _make_sprite(sprite_position: Vector2, layer: int) -> Sprite2D:
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.position = sprite_position
	sprite.z_index = layer
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	return sprite


func _show_panel(index: int, hold_ticks: int = 0) -> void:
	panel_ticks = 0
	panel_hold_ticks = hold_ticks
	scroll_x = 0.0
	credits_started = false
	background_a.texture = BACKGROUNDS[index]
	background_b.texture = BACKGROUNDS[index]
	reflection_a.texture = BACKGROUNDS[index]
	reflection_b.texture = BACKGROUNDS[index]
	reflection_a.visible = index == 3
	reflection_b.visible = index == 3
	for ground in ground_sprites:
		ground.texture = PANELS[index]
		ground.position.y = 360.0 if index == 3 else 380.0
	credit_sprite.texture = CREDITS[index]
	credit_sprite.position = Vector2((640.0 - credit_sprite.texture.get_width()) * 0.5, 60)
	credit_sprite.modulate.a = 0.0
	player_sprite.position = Vector2(540, 300)
	player_sprite.visible = true
	fade.color.a = 1.0


func _begin_final_hold() -> void:
	background_a.visible = false
	background_b.visible = false
	reflection_a.visible = false
	reflection_b.visible = false
	for ground in ground_sprites:
		ground.visible = false
	player_sprite.visible = false
	credit_sprite.visible = false
	final_layer.visible = false
	fade.color.a = 1.0
	final_hold_ticks = 60


func _show_final() -> void:
	finished = true
	background_a.visible = false
	background_b.visible = false
	reflection_a.visible = false
	reflection_b.visible = false
	for ground in ground_sprites:
		ground.visible = false
	player_sprite.visible = false
	credit_sprite.visible = false
	final_layer.visible = true
	fade.color.a = 0.0
