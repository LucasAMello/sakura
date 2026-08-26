extends Node

var carried_hp := -1
var first_boss_reward := false
var second_boss_reward := false
var third_boss_reward := false
var boss_checkpoint := false
var second_boss_checkpoint := false
var third_boss_checkpoint := false
var lives := 5
var cards: Dictionary = {}


func store_hp(value: int) -> void:
	carried_hp = value


func take_hp(default_value: int) -> int:
	var value := default_value if carried_hp < 0 else carried_hp
	carried_hp = -1
	return value


func unlock_first_boss_reward() -> void:
	first_boss_reward = true


func set_boss_checkpoint(value: bool) -> void:
	boss_checkpoint = value


func unlock_second_boss_reward() -> void:
	second_boss_reward = true


func set_second_boss_checkpoint(value: bool) -> void:
	second_boss_checkpoint = value


func unlock_third_boss_reward() -> void:
	third_boss_reward = true


func set_third_boss_checkpoint(value: bool) -> void:
	third_boss_checkpoint = value


func has_card(card_id: int) -> bool:
	return cards.has(card_id)


func collect_card(card_id: int) -> bool:
	if cards.has(card_id):
		return false
	cards[card_id] = true
	return true


func add_life() -> int:
	lives = mini(9, lives + 1)
	return lives


func lose_life() -> int:
	lives -= 1
	if lives < 0:
		lives = 5
	return lives
