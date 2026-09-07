class_name World4Resetti
extends SakuraEnemy

const TEXTURE := preload("res://assets/world4/resetti.png")
const FULL_HEIGHT := 34.0

var timer := 0
var base_y := 0.0
var emerged_height := 0.0
var configured := false


func configure() -> void:
	body_size = Vector2(37.0, 0.0)
	hit_points = 1
	contact_damage = 2
	drops_recovery = false
	sprite.texture = TEXTURE
	sprite.region_enabled = true
	sprite.region_rect = Rect2(0.0, 0.0, 37.0, 0.0)
	sprite.visible = false
	base_y = position.y
	configured = true


func _update_enemy() -> void:
	if not configured or not is_instance_valid(player):
		return
	if timer == 0:
		var player_ahead := player.facing > 0 and position.x - player.position.x - 40.0 > 24.0 and position.x - player.position.x - 40.0 < 56.0
		var player_behind := player.facing < 0 and player.position.x - position.x - 37.0 > 24.0 and player.position.x - position.x - 37.0 < 56.0
		if not player_ahead and not player_behind:
			return
		sprite.flip_h = player_behind
		timer = 1
	else:
		timer += 1
	if timer >= 1 and timer <= 10:
		_set_emerged_height(minf(FULL_HEIGHT, emerged_height + (6.0 if timer == 1 else 7.0)))
	elif timer >= 26 and timer <= 30:
		_set_emerged_height(maxf(0.0, emerged_height - (6.0 if timer == 26 else 7.0)))
	elif timer >= 34:
		var horizontal_distance := absf(player.position.x - position.x)
		if horizontal_distance > 110.0:
			timer = 0


func _set_emerged_height(value: float) -> void:
	emerged_height = clampf(value, 0.0, FULL_HEIGHT)
	position.y = base_y - emerged_height
	body_size.y = emerged_height
	sprite.visible = emerged_height > 0.0
	sprite.region_rect = Rect2(0.0, 0.0, 37.0, emerged_height)


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	if emerged_height <= 0.0:
		return false
	return super.projectile_mask_overlap(projectile_rect)
