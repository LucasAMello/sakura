extends Node2D

enum Phase { START_DELAY, TEXT, TEXT_FADE_OUT, FALL_FADE_IN, FALL, FALL_FADE_OUT, FINISH_WAIT }

const INTRO_1 := preload("res://assets/intro/intro1.png")
const INTRO_2 := preload("res://assets/intro/intro2.png")
const INTRO_3 := preload("res://assets/intro/intro3.png")
const SAKURA_FALLING := preload("res://assets/intro/intro4.png")
const ISLAND := preload("res://assets/intro/intro5.png")
const START_DELAY_TICKS := 120
const FADE_PHASE_TICKS := 100
const FINISH_WAIT_TICKS := 300
const MUSIC_START_SECONDS := 3.0

var phase := Phase.START_DELAY
var phase_ticks := 0
var text_timer := 1.0
var text_darkness := 255.0
var pivot_angle := 0
var falling_scale := 6.0
var background_rect: ColorRect
var intro_1_sprite: Sprite2D
var intro_2_sprite: Sprite2D
var intro_3_sprite: Sprite2D
var island_sprite: Sprite2D
var falling_sprite: Sprite2D
var fade_rect: ColorRect
var leaving := false


func _ready() -> void:
	get_node("/root/AudioManager").stop_music()
	_build_scene()
	_show_text()
	_update_text_sprites()


func _physics_process(_delta: float) -> void:
	if leaving:
		return
	phase_ticks += 1
	match phase:
		Phase.START_DELAY:
			if phase_ticks >= START_DELAY_TICKS and not _skip_is_held():
				phase = Phase.TEXT
				phase_ticks = 0
				get_node("/root/AudioManager").play_music("intro", true, MUSIC_START_SECONDS)
		Phase.TEXT:
			text_timer += 1.5
			text_darkness = maxf(0.0, text_darkness - 0.75)
			if int(text_timer) > 0 and int(text_timer) % 501 == 1:
				text_darkness = 255.0
			_update_text_sprites()
			if int(text_timer) >= 1701:
				phase = Phase.TEXT_FADE_OUT
				phase_ticks = 0
		Phase.TEXT_FADE_OUT:
			fade_rect.color.a = clampf(float(phase_ticks) / 20.0, 0.0, 1.0)
			if phase_ticks >= FADE_PHASE_TICKS:
				phase = Phase.FALL_FADE_IN
				phase_ticks = 0
				_show_fall()
		Phase.FALL_FADE_IN:
			fade_rect.color.a = clampf(float(20 - phase_ticks) / 20.0, 0.0, 1.0)
			if phase_ticks >= FADE_PHASE_TICKS:
				phase = Phase.FALL
				phase_ticks = 0
				fade_rect.color.a = 0.0
		Phase.FALL:
			pivot_angle += 3
			if pivot_angle % 24 == 0:
				falling_scale -= 0.1
			_update_falling_sprite()
			if falling_scale < 0.0:
				phase = Phase.FALL_FADE_OUT
				phase_ticks = 0
		Phase.FALL_FADE_OUT:
			fade_rect.color.a = clampf(float(phase_ticks) / 20.0, 0.0, 1.0)
			if phase_ticks >= FADE_PHASE_TICKS:
				phase = Phase.FINISH_WAIT
				phase_ticks = 0
				fade_rect.color.a = 1.0
		Phase.FINISH_WAIT:
			if phase_ticks >= FINISH_WAIT_TICKS:
				_finish_intro()


func _unhandled_key_input(event: InputEvent) -> void:
	if leaving or phase == Phase.START_DELAY or not event.pressed or event.echo:
		return
	if event.physical_keycode == KEY_ENTER or event.physical_keycode == KEY_F:
		_finish_intro()


func _build_scene() -> void:
	background_rect = ColorRect.new()
	background_rect.size = Vector2(640, 480)
	background_rect.color = Color.BLACK
	add_child(background_rect)
	intro_1_sprite = _make_sprite(INTRO_1, Vector2(160, 330), 1)
	intro_2_sprite = _make_sprite(INTRO_2, Vector2(30, 100), 1)
	intro_3_sprite = _make_sprite(INTRO_3, Vector2(320, 230), 1)
	island_sprite = _make_sprite(ISLAND, Vector2(20, 150), 1)
	island_sprite.scale = Vector2(1.5, 1.5)
	falling_sprite = _make_sprite(SAKURA_FALLING, Vector2(320, 215), 2)
	falling_sprite.offset = Vector2(20, 20)
	falling_sprite.visible = false
	fade_rect = ColorRect.new()
	fade_rect.size = Vector2(640, 480)
	fade_rect.color = Color.BLACK
	fade_rect.z_index = 10
	fade_rect.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(fade_rect)


func _make_sprite(texture: Texture2D, sprite_position: Vector2, layer: int) -> Sprite2D:
	var sprite := Sprite2D.new()
	sprite.centered = false
	sprite.texture = texture
	sprite.position = sprite_position
	sprite.z_index = layer
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)
	return sprite


func _show_text() -> void:
	background_rect.color = Color.BLACK
	intro_1_sprite.visible = true
	intro_2_sprite.visible = true
	intro_3_sprite.visible = true
	island_sprite.visible = false
	falling_sprite.visible = false
	fade_rect.color.a = 0.0


func _show_fall() -> void:
	background_rect.color = Color8(48, 113, 176)
	intro_1_sprite.visible = false
	intro_2_sprite.visible = false
	intro_3_sprite.visible = false
	island_sprite.visible = true
	falling_sprite.visible = false
	fade_rect.color.a = 1.0


func _update_text_sprites() -> void:
	var completed_light := 1.0 - 10.0 / 255.0
	var current_light := 1.0 - text_darkness / 255.0
	intro_1_sprite.modulate = Color(current_light, current_light, current_light, 1.0)
	intro_2_sprite.modulate = Color(current_light, current_light, current_light, 1.0)
	intro_3_sprite.modulate = Color(current_light, current_light, current_light, 1.0)
	intro_1_sprite.visible = text_timer > 0.0
	intro_2_sprite.visible = int(text_timer) > 501
	intro_3_sprite.visible = int(text_timer) > 1002
	if int(text_timer) > 501:
		intro_1_sprite.modulate = Color(completed_light, completed_light, completed_light, 1.0)
	if int(text_timer) > 1002:
		intro_2_sprite.modulate = Color(completed_light, completed_light, completed_light, 1.0)
	if int(text_timer) > 1503:
		intro_3_sprite.modulate = Color(completed_light, completed_light, completed_light, 1.0)


func _update_falling_sprite() -> void:
	falling_sprite.visible = pivot_angle > 0 and falling_scale >= 0.0
	falling_sprite.rotation = float(pivot_angle) * TAU / 256.0
	falling_sprite.scale = Vector2(falling_scale, falling_scale)


func _skip_is_held() -> bool:
	return Input.is_physical_key_pressed(KEY_ENTER) or Input.is_physical_key_pressed(KEY_F)


func _finish_intro() -> void:
	leaving = true
	get_node("/root/GameFlow").open_stage_select()
