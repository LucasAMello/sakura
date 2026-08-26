class_name World3Orange
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world3/orange_1.png"), preload("res://assets/world3/orange_2.png"),
	preload("res://assets/world3/orange_3.png"), preload("res://assets/world3/orange_4.png"),
	preload("res://assets/world3/orange_5.png"), preload("res://assets/world3/orange_6.png"),
	preload("res://assets/world3/orange_7.png"), preload("res://assets/world3/orange_8.png"),
	preload("res://assets/world3/orange_9.png"),
]
const PROPELLERS := [
	preload("res://assets/world3/orange_propeller_1.png"),
	preload("res://assets/world3/orange_propeller_2.png"),
	preload("res://assets/world3/orange_propeller_3.png"),
]

var timer := 0
var bob_tick := 0
var propeller_tick := 0
var direction := 2
var propeller: Sprite2D


func _ready() -> void:
	super._ready()
	propeller = Sprite2D.new()
	propeller.centered = false
	propeller.position = Vector2(4, 0)
	propeller.texture = PROPELLERS[0]
	propeller.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(propeller)
	sprite.position = Vector2(0, 10)


func configure(initial_timer: int = 0) -> void:
	body_size = Vector2(40, 51)
	hit_points = 5
	contact_damage = 2
	drops_recovery = false
	timer = initial_timer
	sprite.texture = FRAMES[3]


func _update_enemy() -> void:
	if position.x > player.position.x + 55.0:
		direction = 1
	elif position.x + 40.0 < player.position.x - 15.0:
		direction = 3
	else:
		direction = 2
	_update_frame()
	_update_bob()
	propeller.texture = PROPELLERS[propeller_tick % PROPELLERS.size()]
	propeller_tick += 1
	if timer == 8:
		var shot_direction := 5 if direction == 1 else 8 if direction == 2 else 3
		var offset := Vector2(-3, 46) if direction == 1 else Vector2(16, 50) if direction == 2 else Vector2(35, 46)
		_spawn_shot(position + offset, shot_direction)
	if timer >= 16:
		timer = 1
	else:
		timer += 1


func _update_frame() -> void:
	var sequence_index := mini(int(timer / 2.0), 8)
	var sequences := {
		1: [0, 1, 2, 1, 6, 7, 8, 7, 0],
		2: [3, 4, 5, 4, 3, 4, 5, 4, 3],
		3: [6, 7, 8, 7, 0, 1, 2, 1, 6],
	}
	sprite.texture = FRAMES[sequences[direction][sequence_index]]
	sprite.flip_h = timer >= 9


func _update_bob() -> void:
	if bob_tick < 2:
		position.y -= 1.0
	elif bob_tick < 8:
		position.y -= 2.0
	elif bob_tick < 10:
		position.y -= 1.0
	elif bob_tick < 11:
		pass
	elif bob_tick < 13:
		position.y += 1.0
	elif bob_tick < 19:
		position.y += 2.0
	elif bob_tick < 21:
		position.y += 1.0
	else:
		bob_tick = -1
	bob_tick += 1


func _spawn_shot(spawn_position: Vector2, shot_direction: int) -> void:
	var shot := World3Projectile.new()
	shot.position = spawn_position
	shot.z_index = 11
	get_parent().add_child(shot)
	shot.setup(World3Projectile.Kind.WALL_SHOT, terrain, player, shot_direction)


func _roll_drop() -> int:
	return DropType.SMALL if randi() % 3 == 0 else DropType.NONE


func _death_effect_position() -> Vector2:
	return position + Vector2(20, 25)
