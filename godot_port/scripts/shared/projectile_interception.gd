extends RefCounted


static func overlaps(target: Node2D, rect: Rect2, size: Vector2, weapon_id: int) -> bool:
	if target.is_queued_for_deletion() or not target.visible:
		return false
	var overlap := Rect2(target.position, size).intersection(rect)
	if not overlap.has_area():
		return false
	if weapon_id != 1:
		return true
	for child in target.get_children():
		var piece := child as Sprite2D
		if piece == null or not piece.visible or piece.texture == null:
			continue
		for y in range(floori(overlap.position.y), ceili(overlap.end.y)):
			for x in range(floori(overlap.position.x), ceili(overlap.end.x)):
				var point := piece.to_local(target.to_global(Vector2(x + 0.5, y + 0.5) - target.position))
				if piece.get_rect().has_point(point) and piece.is_pixel_opaque(point):
					return true
	return false
