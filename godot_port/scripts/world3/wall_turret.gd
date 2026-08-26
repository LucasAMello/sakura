class_name World3WallTurret
extends SakuraEnemy

const HORIZONTAL_TEXTURE := preload("res://assets/world3/wall_turret.png")
const VERTICAL_TEXTURE := preload("res://assets/world3/wall_turret_vertical.png")

var direction := 0
var timer := 0


func configure(turret_direction: int, initial_timer: int = 0) -> void:
	direction = turret_direction
	timer = initial_timer
	hit_points = 5
	contact_damage = 2
	drops_recovery = false
	if direction == 0:
		body_size = Vector2(40, 20)
		sprite.texture = HORIZONTAL_TEXTURE
	else:
		body_size = Vector2(20, 40)
		sprite.texture = VERTICAL_TEXTURE
		sprite.flip_h = direction == 2


func _update_enemy() -> void:
	if timer == 50:
		timer = 0
		if direction == 0:
			_spawn_shot(position + Vector2(-4, 16), 0)
			_spawn_shot(position + Vector2(36, 16), 3)
		elif direction == 1:
			_spawn_shot(position + Vector2(16, -4), 1)
			_spawn_shot(position + Vector2(16, 36), 4)
		else:
			_spawn_shot(position + Vector2(-4, -4), 2)
			_spawn_shot(position + Vector2(-4, 36), 5)
	timer += 1


func _spawn_shot(spawn_position: Vector2, shot_direction: int) -> void:
	var shot := World3Projectile.new()
	shot.position = spawn_position
	shot.z_index = 11
	get_parent().add_child(shot)
	shot.setup(World3Projectile.Kind.WALL_SHOT, terrain, player, shot_direction)


func _death_effect_position() -> Vector2:
	return position + body_size * 0.5
