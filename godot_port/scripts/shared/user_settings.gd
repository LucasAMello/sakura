extends Node

const SETTINGS_PATH := "user://sakura_settings.json"

const DEFAULT_KEYS := {
	"move_up": KEY_UP,
	"move_down": KEY_DOWN,
	"move_left": KEY_LEFT,
	"move_right": KEY_RIGHT,
	"jump": KEY_F,
	"fire": KEY_D,
	"weapon_previous": KEY_A,
	"weapon_next": KEY_S,
	"pause": KEY_ENTER,
	"quit": KEY_ESCAPE,
	"restart": KEY_R,
	"toggle_debug": KEY_F3,
	"weapon_1": KEY_1,
	"weapon_2": KEY_2,
	"weapon_3": KEY_3,
	"weapon_4": KEY_4,
	"weapon_5": KEY_5,
	"weapon_6": KEY_6,
	"weapon_7": KEY_7,
}

var music_volume := 1.0
var sfx_volume := 1.0
var keys: Dictionary = {}


func _ready() -> void:
	keys = DEFAULT_KEYS.duplicate()
	load_settings()
	apply_input_map()
	apply_audio_levels()


func load_settings() -> void:
	if not FileAccess.file_exists(SETTINGS_PATH):
		return
	var file := FileAccess.open(SETTINGS_PATH, FileAccess.READ)
	if file == null:
		return
	var parsed: Variant = JSON.parse_string(file.get_as_text())
	file.close()
	if not parsed is Dictionary:
		return
	var data: Dictionary = parsed
	music_volume = clampf(float(data.get("music_volume", 1.0)), 0.0, 1.0)
	sfx_volume = clampf(float(data.get("sfx_volume", 1.0)), 0.0, 1.0)
	var stored_keys: Variant = data.get("keys", {})
	if stored_keys is Dictionary:
		for action in DEFAULT_KEYS:
			if stored_keys.has(action):
				var keycode := int(stored_keys[action])
				if keycode > 0:
					keys[action] = keycode


func save_settings() -> void:
	var payload := {"music_volume": music_volume, "sfx_volume": sfx_volume, "keys": keys}
	var file := FileAccess.open(SETTINGS_PATH, FileAccess.WRITE)
	if file == null:
		return
	file.store_string(JSON.stringify(payload))
	file.close()


func apply_input_map() -> void:
	for action in keys:
		if not InputMap.has_action(action):
			InputMap.add_action(action)
		InputMap.action_erase_events(action)
		var event := InputEventKey.new()
		event.physical_keycode = int(keys[action]) as Key
		InputMap.action_add_event(action, event)


func set_key(action: String, keycode: Key) -> void:
	if not DEFAULT_KEYS.has(action):
		return
	keys[action] = keycode
	apply_input_map()
	save_settings()


func set_music_volume(value: float) -> void:
	music_volume = clampf(value, 0.0, 1.0)
	apply_audio_levels()
	save_settings()


func set_sfx_volume(value: float) -> void:
	sfx_volume = clampf(value, 0.0, 1.0)
	apply_audio_levels()
	save_settings()


func apply_audio_levels() -> void:
	_set_bus_volume("Music", music_volume)
	_set_bus_volume("SFX", sfx_volume)


func _set_bus_volume(bus_name: String, value: float) -> void:
	var index := AudioServer.get_bus_index(bus_name)
	if index < 0:
		return
	AudioServer.set_bus_mute(index, value <= 0.0)
	AudioServer.set_bus_volume_db(index, linear_to_db(maxf(value, 0.0001)))
