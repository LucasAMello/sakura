class_name ShadowClone
extends SakuraEnemy

const TEXTURE := preload("res://assets/world2/boss_ball.png")

var boss: SecondStageBoss
var x_velocity := 8.0
var y_velocity := 8.0
var timer := 0
var drift := 3.0
var active_motion := false


func _ready() -> void:
	super._ready()
	body_size = Vector2(50, 50)
	hit_points = 30
	contact_damage = 3
	drops_recovery = false
	sprite.texture = TEXTURE
	add_to_group("second_boss_clones")


func configure(owner_boss: SecondStageBoss) -> void:
	boss = owner_boss


func take_projectile_hit(damage: int) -> void:
	if is_instance_valid(boss):
		boss.receive_clone_hit(damage)
		hit_flash_ticks = 5


func take_weapon_hit(damage: int, weapon_id: int) -> void:
	if is_instance_valid(boss):
		boss.receive_clone_weapon_hit(damage, weapon_id)
		hit_flash_ticks = 5


func _update_enemy() -> void:
	if not is_instance_valid(boss):
		queue_free()
		return
	if not active_motion:
		if timer > 0 and timer < 25:
			position.x += drift
		elif timer == 30:
			active_motion = true
		timer += 1
		return
	_move_axis(Vector2(x_velocity, 0.0), true)
	_move_axis(Vector2(0.0, y_velocity), false)


func _move_axis(amount: Vector2, horizontal: bool) -> void:
	var distance := absf(amount.x if horizontal else amount.y)
	var direction := signf(amount.x if horizontal else amount.y)
	while distance > 0.0:
		var step := minf(1.0, distance) * direction
		var offset := Vector2(step, 0.0) if horizontal else Vector2(0.0, step)
		if horizontal and (position.x + step < 5340.0 or position.x + step > 5910.0):
			x_velocity *= -1.0
			return
		if terrain.rect_hits_solid(Rect2(position + offset, body_size)):
			if horizontal:
				x_velocity *= -1.0
			else:
				y_velocity *= -1.0
			return
		position += offset
		distance -= absf(step)
