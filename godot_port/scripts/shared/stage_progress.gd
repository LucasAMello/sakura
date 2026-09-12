extends Node

signal card_collected(card_id: int, total: int)
signal maximum_hp_changed(value: int)

const SAVE_VERSION := 1
const SAVE_PATH := "user://sakura_save.json"
const SAVE_TEMP_PATH := "user://sakura_save.tmp"
const LEGACY_SAVE_PATH := "user://save.sav"
const CARD_COUNT := 52
const BOSS_CARD_COUNT := 6

var carried_hp := -1
var debug_god_mode := false
var selected_weapon := 1
var lives := 5
var cards: Dictionary = {}
var boss_checkpoints: Array[bool] = [false, false, false, false, false, false]
var rematches: Array[bool] = [false, false, false, false, false, false]
var active_rematch_world := 0
var final_stage_return_position := Vector2.ZERO
var game_over_pending := false
var final_stage_reveal_pending := false
var final_stage_reveal_seen := false

var first_boss_reward: bool:
	get:
		return has_card(0)
var second_boss_reward: bool:
	get:
		return has_card(1)
var third_boss_reward: bool:
	get:
		return has_card(2)
var fourth_boss_reward: bool:
	get:
		return has_card(3)
var fifth_boss_reward: bool:
	get:
		return has_card(4)
var sixth_boss_reward: bool:
	get:
		return has_card(5)


func reset_new_game() -> void:
	carried_hp = -1
	selected_weapon = 1
	lives = 5
	cards.clear()
	clear_checkpoints()
	reset_final_stage()
	active_rematch_world = 0
	final_stage_return_position = Vector2.ZERO
	game_over_pending = false
	final_stage_reveal_pending = false
	final_stage_reveal_seen = false


func begin_stage(world_number: int) -> void:
	carried_hp = maximum_hp()
	selected_weapon = 1
	clear_checkpoints()
	game_over_pending = false
	if world_number == 7:
		reset_final_stage()


func store_hp(value: int) -> void:
	carried_hp = clampi(value, 0, maximum_hp())


func take_hp(default_value: int) -> int:
	var fallback := maximum_hp() if default_value <= 0 else mini(default_value, maximum_hp())
	var value := fallback if carried_hp < 0 else mini(carried_hp, maximum_hp())
	carried_hp = -1
	return value


func maximum_hp() -> int:
	var total := card_total()
	if total >= 52:
		return 20
	if total >= 40:
		return 19
	if total >= 30:
		return 18
	if total >= 20:
		return 17
	if total >= 10:
		return 16
	return 15


func card_total() -> int:
	return cards.size()


func has_card(card_id: int) -> bool:
	return cards.has(card_id)


func collect_card(card_id: int) -> bool:
	if card_id < 0 or card_id >= CARD_COUNT or cards.has(card_id):
		return false
	var previous_maximum := maximum_hp()
	var final_stage_was_unlocked := is_final_stage_unlocked()
	cards[card_id] = true
	if not final_stage_was_unlocked and is_final_stage_unlocked():
		final_stage_reveal_pending = true
	card_collected.emit(card_id, card_total())
	var new_maximum := maximum_hp()
	if new_maximum != previous_maximum:
		maximum_hp_changed.emit(new_maximum)
	return true


func has_boss_reward(world_index: int) -> bool:
	return world_index >= 0 and world_index < BOSS_CARD_COUNT and has_card(world_index)


func is_weapon_unlocked(weapon_id: int) -> bool:
	return weapon_id == 1 or (weapon_id >= 2 and weapon_id <= 7 and has_card(weapon_id - 2))


func is_final_stage_unlocked() -> bool:
	for card_id in range(BOSS_CARD_COUNT):
		if not has_card(card_id):
			return false
	return true


func consume_final_stage_reveal() -> bool:
	return is_final_stage_unlocked() and not final_stage_reveal_seen


func finish_final_stage_reveal() -> void:
	final_stage_reveal_pending = false
	final_stage_reveal_seen = true


func unlock_first_boss_reward() -> void:
	collect_card(0)


func unlock_second_boss_reward() -> void:
	collect_card(1)


func unlock_third_boss_reward() -> void:
	collect_card(2)


func unlock_fourth_boss_reward() -> void:
	collect_card(3)


func unlock_fifth_boss_reward() -> void:
	collect_card(4)


func unlock_sixth_boss_reward() -> void:
	collect_card(5)


func set_checkpoint(world_index: int, value: bool) -> void:
	if world_index >= 0 and world_index < boss_checkpoints.size():
		boss_checkpoints[world_index] = value


func has_checkpoint(world_index: int) -> bool:
	return world_index >= 0 and world_index < boss_checkpoints.size() and boss_checkpoints[world_index]


func clear_checkpoints() -> void:
	for index in range(boss_checkpoints.size()):
		boss_checkpoints[index] = false


func set_boss_checkpoint(value: bool) -> void:
	set_checkpoint(0, value)


func set_second_boss_checkpoint(value: bool) -> void:
	set_checkpoint(1, value)


func set_third_boss_checkpoint(value: bool) -> void:
	set_checkpoint(2, value)


func set_fourth_boss_checkpoint(value: bool) -> void:
	set_checkpoint(3, value)


func set_fifth_boss_checkpoint(value: bool) -> void:
	set_checkpoint(4, value)


func set_sixth_boss_checkpoint(value: bool) -> void:
	set_checkpoint(5, value)


var boss_checkpoint: bool:
	get:
		return has_checkpoint(0)
var second_boss_checkpoint: bool:
	get:
		return has_checkpoint(1)
var third_boss_checkpoint: bool:
	get:
		return has_checkpoint(2)
var fourth_boss_checkpoint: bool:
	get:
		return has_checkpoint(3)
var fifth_boss_checkpoint: bool:
	get:
		return has_checkpoint(4)
var sixth_boss_checkpoint: bool:
	get:
		return has_checkpoint(5)


func mark_rematch_complete(world_index: int) -> void:
	if world_index >= 0 and world_index < rematches.size():
		rematches[world_index] = true


func rematch_complete(world_index: int) -> bool:
	return world_index >= 0 and world_index < rematches.size() and rematches[world_index]


func all_rematches_complete() -> bool:
	return not rematches.has(false)


func reset_final_stage() -> void:
	for index in range(rematches.size()):
		rematches[index] = false
	active_rematch_world = 0
	final_stage_return_position = Vector2.ZERO


func begin_rematch(world_number: int, return_position: Vector2) -> void:
	active_rematch_world = world_number
	final_stage_return_position = return_position
	clear_checkpoints()
	set_checkpoint(world_number - 1, true)


func finish_rematch() -> int:
	var completed_world := active_rematch_world
	if completed_world >= 1 and completed_world <= 6:
		mark_rematch_complete(completed_world - 1)
	active_rematch_world = 0
	clear_checkpoints()
	return completed_world


func add_life() -> int:
	lives = mini(9, lives + 1)
	return lives


func lose_life() -> int:
	selected_weapon = 1
	lives -= 1
	if lives < 0:
		game_over_pending = true
		return -1
	return lives


func consume_game_over() -> bool:
	if not game_over_pending:
		return false
	game_over_pending = false
	lives = 5
	carried_hp = -1
	clear_checkpoints()
	reset_final_stage()
	return true


func save_game() -> Dictionary:
	var card_ids: Array[int] = []
	for key in cards.keys():
		card_ids.append(int(key))
	card_ids.sort()
	var payload := {"version": SAVE_VERSION, "cards": card_ids, "final_stage_reveal_seen": final_stage_reveal_seen}
	var file := FileAccess.open(SAVE_TEMP_PATH, FileAccess.WRITE)
	if file == null:
		return {"ok": false, "message": "Unable to create save file."}
	file.store_string(JSON.stringify(payload))
	file.flush()
	file.close()
	var temporary := ProjectSettings.globalize_path(SAVE_TEMP_PATH)
	var destination := ProjectSettings.globalize_path(SAVE_PATH)
	if FileAccess.file_exists(SAVE_PATH):
		var remove_error := DirAccess.remove_absolute(destination)
		if remove_error != OK:
			DirAccess.remove_absolute(temporary)
			return {"ok": false, "message": "Unable to replace save file."}
	var rename_error := DirAccess.rename_absolute(temporary, destination)
	if rename_error != OK:
		DirAccess.remove_absolute(temporary)
		return {"ok": false, "message": "Unable to finish saving."}
	var legacy_file := FileAccess.open(LEGACY_SAVE_PATH, FileAccess.WRITE)
	if legacy_file == null:
		return {"ok": false, "message": "Unable to create save.sav."}
	legacy_file.store_string(_encode_legacy_save())
	legacy_file.close()
	return {"ok": true, "message": "Game Saved"}


func load_game() -> Dictionary:
	if not FileAccess.file_exists(SAVE_PATH):
		return _load_legacy_game()
	var file := FileAccess.open(SAVE_PATH, FileAccess.READ)
	if file == null:
		return {"ok": false, "message": "Unable to read save file."}
	var parsed: Variant = JSON.parse_string(file.get_as_text())
	file.close()
	if not parsed is Dictionary:
		return {"ok": false, "message": "Save file is corrupt."}
	var data: Dictionary = parsed
	if data.get("version", 0) != SAVE_VERSION or not data.get("cards", null) is Array:
		return {"ok": false, "message": "Save file is not supported."}
	var loaded_cards: Dictionary = {}
	for value in data["cards"]:
		if not value is float and not value is int:
			return {"ok": false, "message": "Save file is corrupt."}
		var card_id := int(value)
		if card_id < 0 or card_id >= CARD_COUNT or loaded_cards.has(card_id):
			return {"ok": false, "message": "Save file is corrupt."}
		loaded_cards[card_id] = true
	reset_new_game()
	cards = loaded_cards
	final_stage_reveal_seen = bool(data.get("final_stage_reveal_seen", false))
	final_stage_reveal_pending = is_final_stage_unlocked() and not final_stage_reveal_seen
	return {"ok": true, "message": "Game Loaded"}


func _encode_legacy_save() -> String:
	var encoded := ""
	for first_card in range(0, 51, 3):
		var mask := 0
		if has_card(first_card):
			mask |= 4
		if has_card(first_card + 1):
			mask |= 2
		if has_card(first_card + 2):
			mask |= 1
		encoded += _legacy_character_for_mask(mask)
	var final_mask := 0
	if has_card(51):
		final_mask |= 4
	if final_stage_reveal_seen:
		final_mask |= 2
	encoded += _legacy_character_for_mask(final_mask)
	return encoded


func _legacy_character_for_mask(mask: int) -> String:
	return {7: "1", 6: "2", 5: "3", 3: "4", 4: "5", 2: "6", 1: "7", 0: "8"}[mask]


func _load_legacy_game() -> Dictionary:
	if not FileAccess.file_exists(LEGACY_SAVE_PATH):
		return {"ok": false, "message": "File not found."}
	var file := FileAccess.open(LEGACY_SAVE_PATH, FileAccess.READ)
	if file == null:
		return {"ok": false, "message": "Unable to read save.sav."}
	var encoded := file.get_as_text().strip_edges()
	file.close()
	if encoded.length() < 18:
		return {"ok": false, "message": "Save file is corrupt."}
	var decoded_cards: Dictionary = {}
	for group in range(17):
		var mask := _legacy_mask_for_character(encoded.substr(group, 1))
		if mask < 0:
			return {"ok": false, "message": "Save file is corrupt."}
		for offset in range(3):
			if mask & (4 >> offset):
				decoded_cards[group * 3 + offset] = true
	var final_mask := _legacy_mask_for_character(encoded.substr(17, 1))
	if final_mask < 0:
		return {"ok": false, "message": "Save file is corrupt."}
	if final_mask & 4:
		decoded_cards[51] = true
	reset_new_game()
	cards = decoded_cards
	final_stage_reveal_seen = bool(final_mask & 2)
	final_stage_reveal_pending = is_final_stage_unlocked() and not final_stage_reveal_seen
	return {"ok": true, "message": "Game Loaded"}


func _legacy_mask_for_character(value: String) -> int:
	return {"1": 7, "2": 6, "3": 5, "4": 3, "5": 4, "6": 2, "7": 1, "8": 0}.get(value, -1)
