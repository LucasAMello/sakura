class_name Stage2Armor
extends SakuraEnemy

signal opened(drop_position: Vector2, card_id: int)

const CLOSED_TEXTURE := preload("res://assets/world2/armor_1.png")
const OPEN_TEXTURE := preload("res://assets/world2/armor_2.png")
const EYE_TEXTURES := [
	preload("res://assets/world2/armor_eyes_1.png"),
	preload("res://assets/world2/armor_eyes_2.png"),
	preload("res://assets/world2/armor_eyes_3.png"),
	preload("res://assets/world2/armor_eyes_4.png"),
]

var card_id := 0
var action_state := 0
var timer := 0
var eye_ticks := 0
var eye_sprite: Sprite2D


func _ready() -> void:
	super._ready()
	body_size = Vector2(63, 70)
	hit_points = 1
	contact_damage = 0
	sprite.texture = CLOSED_TEXTURE
	eye_sprite = Sprite2D.new()
	eye_sprite.centered = false
	eye_sprite.position = Vector2(26, 17)
	eye_sprite.texture = EYE_TEXTURES[0]
	eye_sprite.texture_filter = CanvasItem.TEXTURE_FILTER_NEAREST
	eye_sprite.visible = false
	add_child(eye_sprite)


func configure(drop_card_id: int) -> void:
	card_id = drop_card_id


func projectile_mask_overlap(projectile_rect: Rect2) -> bool:
	return action_state < 3 and super.projectile_mask_overlap(projectile_rect)


func take_projectile_hit(_damage: int) -> void:
	if action_state == 3 or action_state == 4:
		return
	action_state = 3
	timer = 0
	eye_sprite.visible = false


func _update_enemy() -> void:
	if action_state == 3:
		timer += 1
		sprite.texture = OPEN_TEXTURE if timer % 8 <= 4 else CLOSED_TEXTURE
		sprite.position = Vector2(-7, 0) if sprite.texture == OPEN_TEXTURE else Vector2.ZERO
		if timer == 12:
			var drop_pos := Vector2(20, 20) if card_id > 5 else Vector2(28, 50)
			opened.emit(position + drop_pos, card_id)
		elif timer >= 18:
			action_state = 4
			sprite.texture = CLOSED_TEXTURE
			sprite.position = Vector2.ZERO
		return
	if action_state == 4:
		return
	if action_state == 0 and _player_is_near():
		action_state = 1
	elif action_state == 1 and _player_is_far():
		action_state = 2
	elif action_state == 2 and _player_is_near():
		action_state = 1
	if action_state == 1:
		eye_ticks = mini(24, eye_ticks + 1)
	elif action_state == 2:
		eye_ticks = maxi(0, eye_ticks - 1)
		if eye_ticks == 0:
			action_state = 0
	eye_sprite.visible = action_state == 1 or action_state == 2
	if eye_sprite.visible:
		eye_sprite.texture = EYE_TEXTURES[clampi(int((maxi(1, eye_ticks) - 1) / 6.0), 0, 3)]


func _player_is_near() -> bool:
	var armor_center := position.x + 31.0
	if player.position.x + 40.0 < armor_center:
		return armor_center - player.position.x + 40.0 <= 200.0
	if player.position.x > armor_center:
		return player.position.x - position.x + 31.0 <= 200.0
	return false


func _player_is_far() -> bool:
	var armor_center := position.x + 31.0
	if player.position.x + 40.0 < armor_center:
		return armor_center - player.position.x + 40.0 > 200.0
	if player.position.x > armor_center:
		return player.position.x - position.x + 31.0 > 200.0
	return false
