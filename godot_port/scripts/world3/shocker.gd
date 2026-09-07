class_name World3Shocker
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world3/shocker_1.png"),
	preload("res://assets/world3/shocker_2.png"),
	preload("res://assets/world3/shocker_3.png"),
	preload("res://assets/world3/shocker_4.png"),
	preload("res://assets/world3/shocker_5.png"),
]

var direction := 0
var timer := 0


func configure(shocker_direction: int, initial_timer: int = 0) -> void:
	direction = shocker_direction
	timer = initial_timer
	hit_points = 6
	contact_damage = 2
	drops_recovery = false
	body_size = Vector2(37, 47) if direction == 0 or direction == 2 else Vector2(47, 37)
	sprite.texture = FRAMES[0]
	_apply_direction_transform()


func take_weapon_hit(damage: int, weapon_id: int) -> void:
	take_projectile_hit(3 if weapon_id == 5 else damage)


func _update_enemy() -> void:
	timer += 1
	if timer > 9 and timer < 14:
		sprite.texture = FRAMES[timer - 9]
	if timer == 16:
		_spawn_charge()
	elif timer > 30 and timer < 35:
		sprite.texture = FRAMES[34 - timer]
	elif timer == 60:
		timer = 0


func _spawn_charge() -> void:
	var charge := World3Projectile.new()
	charge.position = position + [Vector2(7, 21), Vector2(9, 7), Vector2(7, 9), Vector2(21, 8)][direction]
	charge.z_index = 11
	get_parent().add_child(charge)
	charge.setup(World3Projectile.Kind.SHOCK_CHARGE, terrain, player, direction)


func _apply_direction_transform() -> void:
	if direction == 1:
		sprite.rotation = PI * 0.5
		sprite.position = Vector2(47, 0)
	elif direction == 2:
		sprite.flip_v = true
	elif direction == 3:
		sprite.rotation = -PI * 0.5
		sprite.position = Vector2(0, 37)


func _death_effect_position() -> Vector2:
	return position + body_size * 0.5
