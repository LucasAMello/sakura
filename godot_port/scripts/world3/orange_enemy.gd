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
	set_update_interval(1)
	body_size = Vector2(40, 51)
	hit_points = 5
	contact_damage = 2
	drops_recovery = false
	timer = initial_timer * 4
	sprite.texture = FRAMES[3]


func _update_enemy() -> void:
	if position.x > player.position.x + 55.0:
		direction = 1
	elif position.x + 40.0 < player.position.x - 15.0:
		direction = 3
	else:
		direction = 2
	_update_bob()
	propeller.texture = PROPELLERS[int((propeller_tick + 1) / 4.0) % PROPELLERS.size()]
	propeller_tick += 1
	if timer % 4 == 3:
		_update_frame(int(timer / 4.0))
	if timer == 35:
		var shot_direction := World3Projectile.ShotDirection.DOWN_LEFT if direction == 1 else World3Projectile.ShotDirection.DOWN if direction == 2 else World3Projectile.ShotDirection.DOWN_RIGHT
		var offset := Vector2(-3, 46) if direction == 1 else Vector2(16, 50) if direction == 2 else Vector2(35, 46)
		_spawn_shot(position + offset, shot_direction)
	if timer >= 67:
		timer = 4
	else:
		timer += 1
	sprite.flip_h = timer >= 36


func _update_frame(source_tick: int) -> void:
	if source_tick % 2 != 0:
		return
	var sequence_index := mini(int(source_tick / 2.0), 8)
	var sequences := {
		1: [0, 1, 2, 1, 6, 7, 8, 7, 0],
		2: [3, 4, 5, 4, 3, 4, 5, 4, 3],
		3: [6, 7, 8, 7, 0, 1, 2, 1, 6],
	}
	sprite.texture = FRAMES[sequences[direction][sequence_index]]


func _update_bob() -> void:
	if bob_tick < 8:
		position.y -= 0.25
	elif bob_tick < 32:
		position.y -= 0.5
	elif bob_tick < 40:
		position.y -= 0.25
	elif bob_tick < 44:
		pass
	elif bob_tick < 52:
		position.y += 0.25
	elif bob_tick < 76:
		position.y += 0.5
	elif bob_tick < 84:
		position.y += 0.25
	bob_tick = (bob_tick + 1) % 88


func _spawn_shot(spawn_position: Vector2, shot_direction: int) -> void:
	var shot := World3Projectile.new()
	shot.position = spawn_position
	shot.z_index = 11
	get_parent().add_child(shot)
	shot.setup(World3Projectile.Kind.ORANGE_SHOT, terrain, player, shot_direction)


func _roll_drop() -> int:
	return DropType.SMALL if randi() % 3 == 0 else DropType.NONE


func _death_effect_position() -> Vector2:
	return position + Vector2(20, 25)
