class_name SakuraEnemy
extends Node2D

signal defeated(enemy: SakuraEnemy, effect_position: Vector2, drop_position: Vector2, drop_type: int)

enum DropType { NONE, SMALL, MEDIUM, EXTRA_LIFE }

var terrain: SakuraTerrain
var player: SakuraPlayer
var sprite: Sprite2D
var body_size := Vector2(40, 40)
var hit_points := 1
var contact_damage := 1
var drops_recovery := false
var gameplay_active := false
var defeated_state := false
var hit_flash_ticks := 0
var update_interval_ticks := 1
var update_interval_counter := 0


func _ready() -> void:
	process_mode = Node.PROCESS_MODE_PAUSABLE
	texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	sprite = Sprite2D.new()
	sprite.centered = false
	sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	add_child(sprite)


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer) -> void:
	terrain = map_terrain
	player = target_player


func set_gameplay_active(value: bool) -> void:
	gameplay_active = value


func set_update_interval(ticks: int) -> void:
	update_interval_ticks = maxi(1, ticks)
	update_interval_counter = 0


func get_hit_rect() -> Rect2:
	return Rect2(position, body_size)


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	var overlap := get_hit_rect().intersection(projectile_rect)
	if overlap.size.x <= 0.0 or overlap.size.y <= 0.0 or sprite.texture == null:
		return false
	var image := sprite.texture.get_image()
	if image == null:
		return true
	var start_x := floori(overlap.position.x)
	var end_x := ceili(overlap.end.x)
	var start_y := floori(overlap.position.y)
	var end_y := ceili(overlap.end.y)
	for world_y in range(start_y, end_y):
		for world_x in range(start_x, end_x):
			var local_x := world_x - floori(position.x)
			var local_y := world_y - floori(position.y)
			if sprite.flip_h:
				local_x = image.get_width() - 1 - local_x
			if sprite.flip_v:
				local_y = image.get_height() - 1 - local_y
			if local_x >= 0 and local_x < image.get_width() and local_y >= 0 and local_y < image.get_height():
				if image.get_pixel(local_x, local_y).a > 0.01:
					return true
	return false


func _physics_process(_delta: float) -> void:
	if defeated_state:
		return
	var current_alpha := sprite.modulate.a
	if hit_flash_ticks > 0:
		sprite.modulate = Color(1.0, 0.45, 0.45, current_alpha) if hit_flash_ticks % 4 < 2 else Color(1.0, 1.0, 1.0, current_alpha)
		hit_flash_ticks -= 1
	else:
		sprite.modulate = Color(1.0, 1.0, 1.0, current_alpha)
	if gameplay_active:
		update_interval_counter += 1
		if update_interval_counter >= update_interval_ticks:
			update_interval_counter = 0
			_update_enemy()
		if is_instance_valid(player) and get_hit_rect().intersects(player.get_hit_rect()):
			player.take_damage(contact_damage)


func _update_enemy() -> void:
	pass


func take_projectile_hit(damage: int) -> void:
	if defeated_state:
		return
	hit_points -= damage
	hit_flash_ticks = 8
	if hit_points <= 0:
		defeated_state = true
		var drop_type := _roll_drop()
		defeated.emit(self, _death_effect_position(), _drop_position(drop_type), drop_type)
		queue_free()


func take_weapon_hit(damage: int, _weapon_id: int) -> void:
	take_projectile_hit(damage)


func take_water_splash_hit() -> void:
	take_weapon_hit(1, 5)


func accepts_weapon_hit(_weapon_id: int) -> bool:
	return true


func _roll_drop() -> int:
	if drops_recovery and randi() % 3 == 0:
		return DropType.SMALL
	return DropType.NONE


func _drop_position(_drop_type: int) -> Vector2:
	return position + Vector2(10, (body_size.y - 10.0) * 0.5)


func _death_effect_position() -> Vector2:
	return position + Vector2(20, 20)
