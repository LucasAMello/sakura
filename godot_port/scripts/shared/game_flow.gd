extends Node

signal stage_start_failed(message: String)

const STAGE_FADE_SECONDS := 0.25
const TITLE_SCENE := "res://scenes/main.tscn"
const INTRO_SCENE := "res://scenes/intro.tscn"
const STAGE_SELECT_SCENE := "res://scenes/stage_select.tscn"
const ENDING_SCENE := "res://scenes/ending.tscn"

const STAGE_STARTS := {
	1: "res://scenes/map10.tscn",
	2: "res://scenes/map20.tscn",
	3: "res://scenes/map30.tscn",
	4: "res://scenes/map40.tscn",
	5: "res://scenes/map50.tscn",
	6: "res://scenes/map60.tscn",
	7: "res://scenes/map80.tscn",
}

var transitioning := false
var transition_overlay: ColorRect


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_ALWAYS
	var layer := CanvasLayer.new()
	layer.layer = 100
	add_child(layer)
	transition_overlay = ColorRect.new()
	transition_overlay.color = Color.BLACK
	transition_overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
	transition_overlay.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	transition_overlay.hide()
	layer.add_child(transition_overlay)


func open_title() -> void:
	get_tree().paused = false
	get_tree().change_scene_to_file(TITLE_SCENE)


func start_new_game() -> void:
	get_node("/root/SakuraProgress").reset_new_game()
	get_tree().paused = false
	get_tree().change_scene_to_file(INTRO_SCENE)


func load_game(open_after_load: bool = true) -> Dictionary:
	var result: Dictionary = get_node("/root/SakuraProgress").load_game()
	if result.get("ok", false) and open_after_load:
		open_stage_select()
	return result


func open_stage_select() -> void:
	get_tree().paused = false
	get_tree().change_scene_to_file(STAGE_SELECT_SCENE)


func start_stage(world_number: int) -> bool:
	if transitioning or not STAGE_STARTS.has(world_number):
		return false
	var progress := get_node("/root/SakuraProgress")
	if world_number == 7 and not progress.is_final_stage_unlocked():
		return false
	transitioning = true
	_transition_to_stage(world_number)
	return true


func _transition_to_stage(world_number: int) -> void:
	transition_overlay.modulate.a = 0.0
	transition_overlay.show()
	await _fade_stage_overlay(1.0)
	await RenderingServer.frame_post_draw
	var path: String = STAGE_STARTS[world_number]
	var error := ResourceLoader.load_threaded_request(path, "PackedScene")
	if error != OK:
		await _fail_stage_transition()
		return
	var status := ResourceLoader.load_threaded_get_status(path)
	while status == ResourceLoader.THREAD_LOAD_IN_PROGRESS:
		await get_tree().process_frame
		status = ResourceLoader.load_threaded_get_status(path)
	if status != ResourceLoader.THREAD_LOAD_LOADED:
		await _fail_stage_transition()
		return
	var scene := ResourceLoader.load_threaded_get(path) as PackedScene
	if scene == null:
		await _fail_stage_transition()
		return
	get_node("/root/SakuraProgress").begin_stage(world_number)
	get_tree().paused = true
	error = get_tree().change_scene_to_packed(scene)
	if error != OK:
		await _fail_stage_transition()
		return
	await get_tree().scene_changed
	await RenderingServer.frame_post_draw
	await _fade_stage_overlay(0.0)
	transition_overlay.hide()
	transitioning = false
	get_tree().paused = false


func _fade_stage_overlay(alpha: float) -> void:
	var tween := create_tween().set_pause_mode(Tween.TWEEN_PAUSE_PROCESS)
	tween.tween_property(transition_overlay, "modulate:a", alpha, STAGE_FADE_SECONDS)
	await tween.finished


func _fail_stage_transition() -> void:
	await _fade_stage_overlay(0.0)
	transition_overlay.hide()
	transitioning = false
	get_tree().paused = false
	stage_start_failed.emit("Could not load stage.")


func complete_elemental_stage(_world_number: int) -> void:
	var progress := get_node("/root/SakuraProgress")
	progress.carried_hp = -1
	progress.clear_checkpoints()
	open_stage_select()


func return_from_rematch(world_index: int) -> void:
	get_node("/root/SakuraProgress").mark_rematch_complete(world_index)
	get_tree().change_scene_to_file("res://scenes/map73.tscn")


func launch_rematch(world_number: int, return_position: Vector2) -> void:
	var progress := get_node("/root/SakuraProgress")
	progress.begin_rematch(world_number, return_position)
	var rematch_maps := {1: 75, 2: 76, 3: 77, 4: 78, 5: 79, 6: 74}
	get_tree().change_scene_to_file("res://scenes/map%d.tscn" % rematch_maps[world_number])


func finish_active_rematch() -> void:
	var progress := get_node("/root/SakuraProgress")
	progress.finish_rematch()
	if progress.all_rematches_complete():
		get_tree().change_scene_to_file("res://scenes/map80.tscn")
	else:
		get_tree().change_scene_to_file("res://scenes/map73.tscn")


func leave_final_stage() -> void:
	get_node("/root/SakuraProgress").reset_final_stage()
	open_stage_select()


func game_over() -> void:
	get_node("/root/SakuraProgress").consume_game_over()
	open_stage_select()


func play_ending() -> void:
	get_tree().paused = false
	get_tree().change_scene_to_file(ENDING_SCENE)
