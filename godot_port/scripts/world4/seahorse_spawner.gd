class_name World4SeahorseSpawner
extends Node2D

signal spawn_requested(spawn_position: Vector2)

const ACTIVATION_DISTANCE := 140.0
const COOLDOWN_TICKS := 90

var player: SakuraPlayer
var gameplay_active := false
var cooldown := 0


func setup(target_player: SakuraPlayer) -> void:
	player = target_player


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func _physics_process(_delta: float) -> void:
	if not gameplay_active or not is_instance_valid(player):
		return
	if cooldown > 0:
		cooldown -= 1
		return
	if absf(player.get_center().x - position.x) <= ACTIVATION_DISTANCE:
		spawn_requested.emit(position)
		cooldown = COOLDOWN_TICKS
