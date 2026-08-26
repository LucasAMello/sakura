class_name GreenTurretEnemy
extends SakuraEnemy

const TEXTURE := preload("res://assets/world1/green_turret.png")
const EnemyProjectileScript = preload("res://scripts/world1/enemy_projectile.gd")
const FIRE_INTERVAL_TICKS := 120
const MEDIUM_DROP_PERCENT := 25
const EXTRA_LIFE_DROP_PERCENT := 10

var direction := 0
var timer := 0


func configure(initial_direction: int) -> void:
	body_size = Vector2(60, 60)
	hit_points = 10
	contact_damage = 5
	drops_recovery = true
	direction = 1 if initial_direction == 1 else 0
	sprite.texture = TEXTURE
	sprite.flip_h = direction == 1


func _update_enemy() -> void:
	timer += 1
	if timer < FIRE_INTERVAL_TICKS:
		return
	timer = 0
	var projectile: EnemyProjectile = EnemyProjectileScript.new()
	projectile.position = position + Vector2(59 if direction == 1 else 0, 16)
	projectile.z_index = 11
	projectile.setup(terrain, player, direction)
	get_parent().add_child(projectile)


func _roll_drop() -> int:
	return _drop_for_roll(randi_range(0, 99))


func _drop_for_roll(roll: int) -> int:
	if roll < MEDIUM_DROP_PERCENT:
		return DropType.MEDIUM
	if roll < MEDIUM_DROP_PERCENT + EXTRA_LIFE_DROP_PERCENT:
		return DropType.EXTRA_LIFE
	return DropType.NONE


func _drop_position(drop_type: int) -> Vector2:
	if drop_type == DropType.MEDIUM:
		return position + Vector2(20, 20)
	if drop_type == DropType.EXTRA_LIFE:
		return position + Vector2(20, 10)
	return position


func _death_effect_position() -> Vector2:
	return position + Vector2(30, 30)
