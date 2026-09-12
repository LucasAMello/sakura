class_name World6IcyAttack
extends SakuraEnemy

const FRAMES := [
	preload("res://assets/world6/boss_attack_1.png"),
	preload("res://assets/world6/boss_attack_2.png"),
	preload("res://assets/world6/boss_attack_3.png"),
	preload("res://assets/world6/boss_attack_4.png"),
	preload("res://assets/world6/boss_attack_5.png"),
]
const SIZES := [
	Vector2(19, 47), Vector2(25, 40), Vector2(40, 25),
	Vector2(47, 19), Vector2(40, 25),
]
const SPEEDS := [
	Vector2(0, 24), Vector2(8, 14), Vector2(16, 8),
	Vector2(24, 0), Vector2(16, -8),
]

var variant := 0
var direction := 0
var timer := 0
var velocity := Vector2.ZERO
var charging := true


func _ready() -> void:
	add_to_group("enemy_projectile_blockers")
	super._ready()
	hit_points = 1
	contact_damage = 3
	drops_recovery = false
	sprite.modulate.a = 0.0


func configure(attack_variant: int, attack_direction: int) -> void:
	set_update_interval(1)
	variant = clampi(attack_variant, 0, FRAMES.size() - 1)
	direction = 0 if attack_direction <= 0 else 1
	body_size = SIZES[variant]
	velocity = SPEEDS[variant] * 0.5
	if direction == 1:
		velocity.x *= -1.0
	sprite.texture = FRAMES[variant]
	sprite.flip_h = direction == 1


func projectile_mask_overlap(_projectile_rect: Rect2) -> bool:
	return false


func take_projectile_hit(_damage: int) -> void:
	pass


func _update_enemy() -> void:
	if charging:
		timer += 1
		sprite.modulate.a = minf(1.0, timer * 7.5 / 255.0)
		if timer >= 52:
			charging = false
			sprite.modulate.a = 1.0
		return
	if _move_and_hit(velocity):
		queue_free()
		return
	if position.x + body_size.x < 0.0 or position.x > terrain.world_size.x or position.y + body_size.y < 0.0 or position.y > terrain.world_size.y:
		queue_free()


func _move_and_hit(amount: Vector2) -> bool:
	var steps := maxi(1, ceili(maxf(absf(amount.x), absf(amount.y))))
	var step := amount / float(steps)
	for _index in range(steps):
		var candidate := Rect2(position + step, body_size)
		if terrain.rect_hits_solid(candidate):
			return true
		position += step
	return false


func blocks_player_projectile(rect: Rect2, weapon_id: int, _water_splash: bool = false) -> bool:
	return preload("res://scripts/shared/projectile_interception.gd").overlaps(self, rect, body_size, weapon_id)
