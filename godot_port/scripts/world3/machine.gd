class_name World3Machine
extends SakuraEnemy

const TEXTURE := preload("res://assets/world3/machine.png")

var timer := 0
var direction := 0


func configure(machine_direction: int = 0) -> void:
	direction = machine_direction
	body_size = Vector2(64, 70)
	hit_points = 12
	contact_damage = 2
	drops_recovery = false
	sprite.texture = TEXTURE
	sprite.flip_h = direction != 0


func _update_enemy() -> void:
	if timer == 50:
		var attack := randi() % 3
		if attack == 0:
			_spawn_projectile(World3Projectile.Kind.MISSILE, position + Vector2(22, 27), 0)
		elif attack == 1:
			_spawn_projectile(World3Projectile.Kind.MISSILE, position + Vector2(-2, 26), 0)
		else:
			var shot_direction := 6 if direction == 0 else 7
			_spawn_projectile(World3Projectile.Kind.WALL_SHOT, position + Vector2(23, 17), shot_direction)
			_spawn_projectile(World3Projectile.Kind.WALL_SHOT, position + Vector2(0, 16), shot_direction)
		timer = 0
	timer += 1


func _spawn_projectile(projectile_kind: int, spawn_position: Vector2, projectile_direction: int) -> void:
	var projectile := World3Projectile.new()
	projectile.position = spawn_position
	projectile.z_index = 11
	get_parent().add_child(projectile)
	projectile.setup(projectile_kind, terrain, player, projectile_direction)


func _roll_drop() -> int:
	if randi() % 4 == 0:
		return DropType.MEDIUM
	if randi() % 4 == 0:
		return DropType.MEDIUM
	return DropType.NONE


func _death_effect_position() -> Vector2:
	return position + Vector2(32, 35)
