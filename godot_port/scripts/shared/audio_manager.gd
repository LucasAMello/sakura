extends Node

const MUSIC_PATH := "res://assets/audio/music/%s.ogg"
const SFX_PATH := "res://assets/audio/sfx/%s.wav"
const SFX_PROXIMITY_HALF_EXTENTS := Vector2(520.0, 380.0)
const TRACK_NAMES := {
	"title": "title",
	"intro": "intro",
	"select": "cselect",
	"world1": "tek",
	"world2": "wkn",
	"world3": "emr",
	"world4": "ask",
	"world5": "ce",
	"world6": "myk",
	"world7": "rrk",
	"memory": "omoide",
	"ending": "ending",
}
const MUSIC_LOOP_OFFSETS := {
	"title": 1632639.0 / 44100.0,
	"select": 2928777.0 / 44100.0,
	"world1": 157970.0 / 44100.0,
	"world2": 157970.0 / 44100.0,
	"world3": 1400822.0 / 44100.0,
	"world4": 3608178.0 / 44100.0,
	"world5": 789850.0 / 44100.0,
	"world6": 473910.0 / 44100.0,
	"world7": 2073357.0 / 44100.0,
	"memory": 565908.0 / 44100.0,
}

var music_player: AudioStreamPlayer
var current_track := ""
var sfx_tick := -1
var sfx_started_this_tick: Dictionary = {}


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS
	music_player = AudioStreamPlayer.new()
	music_player.bus = "Music"
	add_child(music_player)
	get_node("/root/SakuraProgress").card_collected.connect(_on_card_collected)


func play_music(track_id: String, restart: bool = false, start_position: float = 0.0) -> void:
	if current_track == track_id and music_player.playing and not restart:
		return
	if not TRACK_NAMES.has(track_id):
		stop_music()
		return
	var file_name: String = TRACK_NAMES[track_id]
	var loop := MUSIC_LOOP_OFFSETS.has(track_id)
	var loop_offset: float = MUSIC_LOOP_OFFSETS.get(track_id, 0.0)
	var loaded := _load_music_stream(file_name, loop, loop_offset)
	if loaded == null:
		return
	music_player.stream = loaded
	current_track = track_id
	music_player.play(start_position)


func cycle_cheat_music(direction: int) -> void:
	var tracks := ["world1", "world2", "world3", "world4", "world5", "world6", "world7", "memory", "title", "select", "ending"]
	var index := tracks.find(current_track)
	play_music(tracks[wrapi(index + direction, 0, tracks.size())], true)


func stop_music() -> void:
	music_player.stop()
	music_player.stream = null
	current_track = ""


func play_sfx(effect_id: String, pitch_scale: float = 1.0, volume_scale: float = 1.0) -> void:
	var path := SFX_PATH % effect_id.to_lower()
	if not ResourceLoader.exists(path):
		return
	var tick := Engine.get_physics_frames()
	if tick != sfx_tick:
		sfx_tick = tick
		sfx_started_this_tick.clear()
	var key := "%s:%s" % [path, pitch_scale]
	var volume := clampf(volume_scale, 0.0, 1.0)
	var existing: AudioStreamPlayer = sfx_started_this_tick.get(key)
	if is_instance_valid(existing):
		existing.volume_linear = maxf(existing.volume_linear, volume)
		return
	var player := AudioStreamPlayer.new()
	player.bus = "SFX"
	player.stream = load(path)
	player.pitch_scale = pitch_scale
	player.volume_linear = volume
	add_child(player)
	player.finished.connect(player.queue_free)
	sfx_started_this_tick[key] = player
	player.play()


func play_sfx_near_player(effect_id: String, source_position: Vector2, player_position: Vector2, pitch_scale: float = 1.0, volume_scale: float = 1.0) -> void:
	var offset := source_position - player_position
	if offset.x <= -SFX_PROXIMITY_HALF_EXTENTS.x or offset.x >= SFX_PROXIMITY_HALF_EXTENTS.x:
		return
	if offset.y <= -SFX_PROXIMITY_HALF_EXTENTS.y or offset.y >= SFX_PROXIMITY_HALF_EXTENTS.y:
		return
	play_sfx(effect_id, pitch_scale, volume_scale)


func _load_music_stream(file_name: String, loop: bool, loop_offset: float = 0.0) -> AudioStream:
	var path := MUSIC_PATH % file_name
	if not ResourceLoader.exists(path):
		return null
	var loaded: AudioStream = load(path)
	if loaded is AudioStreamOggVorbis:
		loaded.loop = loop
		loaded.loop_offset = loop_offset
	return loaded


func _on_card_collected(_card_id: int, _total: int) -> void:
	play_sfx("cardget")
