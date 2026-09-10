class_name World4CardPickup
extends "res://scripts/world1/card_pickup.gd"


func setup(map_terrain: SakuraTerrain, target_player: SakuraPlayer, pickup_card_id: int, falls: bool) -> void:
	super.setup(map_terrain, target_player, pickup_card_id, falls)
	oscillation_direction = 0
