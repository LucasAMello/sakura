extends RefCounted


static func is_due(stage: Node, ticks: int, channel: String = "boss", first_delay: int = 16) -> bool:
	var key := "boss_explosion_deadline_" + channel
	if ticks == 1 or not stage.has_meta(key):
		stage.set_meta(key, ticks + randi_range(maxi(1, first_delay - 8), first_delay + 8))
	if ticks < int(stage.get_meta(key)):
		return false
	stage.set_meta(key, ticks + randi_range(16, 40))
	return true
