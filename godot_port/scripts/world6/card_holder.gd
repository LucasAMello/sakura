class_name World6CardHolder
extends World1CardHolder

var update_phase := 0


func _physics_process(delta: float) -> void:
	update_phase = (update_phase + 1) % 2
	if update_phase == 0:
		super._physics_process(delta)

