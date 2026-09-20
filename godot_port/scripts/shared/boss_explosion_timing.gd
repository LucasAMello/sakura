extends RefCounted


static func due_count(stage: Node, ticks: int, channel: String = "boss", first_delay: int = 16) -> int:
	var count := 0
	for stream in range(3):
		if is_due(stage, ticks, channel + "_" + str(stream), first_delay + stream * 8):
			count += 1
	return count


static func is_due(stage: Node, ticks: int, channel: String = "boss", first_delay: int = 16) -> bool:
	var key := "boss_explosion_deadline_" + channel
	if ticks == 1 or not stage.has_meta(key):
		stage.set_meta(key, ticks + maxi(1, first_delay))
	if ticks < int(stage.get_meta(key)):
		return false
	stage.set_meta(key, ticks + randi_range(16, 40))
	return true
