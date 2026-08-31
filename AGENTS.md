# Sakura project instructions

## Scope

This repository contains the archived source and assets for Sakura plus a preservation-minded Godot 4 port. Active development is in `godot_port/`. The current playable scope covers Worlds 1–6 continuously: maps 10–14, 20–23, 30–32, 40–42, 50–53, and 60–62, including each world's checkpoint, boss, reward, and departure sequence. World 6 currently ends at its completion screen because World 7 is outside the implemented scope.

Read `godot_port/README.md` before making changes, but verify every referenced file and stated value against the current tree. The README can lag behind recent playtest changes.

## Working principles

- Preserve the original game's behavior, coordinates, state order, drops, damage, and presentation details wherever evidence exists.
- Preserve manual playtest tuning in the Godot port. Existing movement speeds, animation holds, firing intervals, and timing scales are intentional unless the user explicitly asks to change them.
- Do not replace current tuned values with archive values merely because they differ.
- Treat the user's first-hand memory and playtest feedback as important evidence, especially where the old executable cannot run.
- Make focused changes. Avoid broad refactors while correcting a parity detail.
- Do not add explanatory comments to source code unless the user explicitly requests comments. Put rationale in documentation or the handoff response.
- Do not modify generated `.godot/` cache data or `.import` files as part of normal code changes.
- Do not create or run tests, smoke tests, test scripts, or test scenes. A Godot parser/editor load may be used only as a compile check; it is not authorization to run gameplay tests.
- Preserve pixel-art dimensions, nearest-neighbor filtering, and RGB `(255, 0, 255)` transparency conversion.

## Evidence order

For gameplay research, use these sources in this order:

1. Current user instructions and confirmed manual tuning
2. `old/2 Joguito`, the canonical original C++/Allegro gameplay source
3. Original maps and release assets
4. `old/4 Sakura2.0` and `old/3 Joguito 2` as secondary corroboration
5. Existing port behavior when no stronger evidence is available

Useful original files include:

- `old/2 Joguito/Main.cpp`: map setup and scripted events
- `old/2 Joguito/scripts.h`: per-tick behavior and animation
- `old/2 Joguito/sprite.h`: entity initialization and constants
- `old/2 Joguito/colision.h`: collision behavior
- `old/2 Joguito/maps.h`: terrain and spawn data
- `old/2 Joguito/map10.map` through `map14.map`, `map20.map` through `map23.map`, `map30.map` through `map32.map`, `map40.map` through `map42.map`, `map50.map` through `map53.map`, and `map60.map` through `map62.map`: authoritative maps for the currently ported scope

Search the archive before guessing. Follow entity type numbers through initialization, update, collision, and draw code because behavior is often split across several files.

## Port architecture

- `godot_port/scripts/shared/stage_base.gd` owns behavior shared by every stage controller.
- `godot_port/scripts/world1/stage1.gd` is the controller for maps 10–14.
- `godot_port/scripts/world2/stage2.gd` is the shared controller for maps 20–23.
- `godot_port/scripts/world3/stage3.gd` is the shared controller for maps 30–32.
- `godot_port/scripts/world4/stage4.gd` is the shared controller for maps 40–42.
- `godot_port/scripts/world5/stage5.gd` is the shared controller for maps 50–53.
- `godot_port/scripts/world6/stage6.gd` is the shared controller for maps 60–62.
- `godot_port/scripts/player/player.gd` owns movement, collision, damage, immunity, animation, firing, and scripted walking.
- `godot_port/scripts/shared/enemy_base.gd` owns shared enemy behavior.
- Individual enemy and boss scripts live in their owning `godot_port/scripts/world1/` through `world6/` folders; cross-world logic lives in `godot_port/scripts/shared/`.
- Small scene wrappers in `godot_port/scenes/` select each implemented map number.
- `SakuraProgress` is registered as an autoload in `godot_port/project.godot`. In scripts, resolve it with `get_node("/root/SakuraProgress")`; direct global identifier use has caused parser failures in this workspace.

The game uses a 640×480 logical viewport and 60 fixed physics ticks per second, while the original Allegro game updated gameplay at 30 Hz. Preserve the 60 Hz Godot physics rate, but convert original tick-based movement, collision, attacks, firing, and animation to the same real-time pace. World-local enemies and enemy projectiles can retain the archive's per-update values by running their gameplay update once every two physics ticks. Do not apply that world-local cadence to shared player movement or weapon tuning. Use `delta` only for new visual behavior that cannot affect gameplay parity.

## Current tuning that must be preserved

Unless the user requests otherwise:

- Player and red-ball walk frames are held for eight physics ticks.
- The player walk sequence is `1, 2, 3, 2, 1, 4, 5, 4`, represented internally by zero-based texture indices.
- Player autofire interval is 25 ticks with at most four active shots.
- Player shots travel 9 pixels per tick through substeps.
- Player shots explode when their horizontal distance from Sakura exceeds 480 pixels.
- Red balls move 2 pixels per tick.
- Green turrets fire every 120 ticks.
- Green turrets drop medium recovery 25% of the time and an extra life 10% of the time.
- Green-turret shots use their original three-frame explosion when they hit terrain or the player, or reach their lifetime limit.
- Green-turret explosion frames use twice the previous hold duration.
- Pumpkin hits stun rather than kill it.
- Player damage immunity lasts 80 physics ticks.
- Pirikito preserves the original velocity state machine and scales only its applied movement to 75%.
- The first boss's overall movement and state sequence are deliberately slower than the original.
- The first boss's horizontal dash is 10 pixels per tick and uses one flight sprite.
- Boss feathers move in two collision substeps of `20 / 3` pixels each.
- World 2 enemies, active hazards, pickups, rewards, and boss logic update once every two 60 Hz physics ticks to match the original 30 Hz real-time pace. Do not halve shared player movement or weapon tuning.
- World 2 ghost masks drop small recovery 20% of the time and an extra life 10% of the time.
- World 2 wall interiors use the alternating castle-brick background tiles; their decorative fill remains non-solid while the surrounding border tiles own collision.
- World 2 uses the stage backdrop only on map20; maps 21–23 use a black background.
- World 3 and later world-local enemies, enemy projectiles, active hazards, and boss logic update once every two 60 Hz physics ticks to match the original 30 Hz real-time pace. This cadence must cover movement, acceleration, animation, state timers, and firing intervals together; avoid correcting only one of those dimensions.
- World 1 and World 2 boss/checkpoint doors take 40 ticks to rise and 40 ticks to descend. World 3 doors retain their existing 20-tick motion.
- Map14's falling-stage introduction uses the latest playtest timing: blocks fall 3 pixels per tick, activation and explosion intervals are four times the archive timing, and the boss entry wait is 120 ticks.
- Card collectible spin animation runs at half its previous rate in every world; falling and collection fading retain their existing rates.
- The first-boss health meter fills one point every two physics ticks. The first boss and its active feathers must use pausable process mode even though the stage controller processes while paused.
- Ordinary map transitions do not show portals. Portals are reserved for entering the first map of a stage, exiting its last map, and checkpoint revival after death.
- Ordinary map transitions do not show the `READY` graphic. It appears only on the first map of a world and after checkpoint revival.
- Recovery drops fall at 7.5 pixels per tick.

Inspect the current constants before editing nearby code. Do not assume this list is more current than the implementation.

## Map14 boss sequence

The required room order is:

`stage -> left door -> playable intermission/checkpoint room -> right door -> boss room`

Important behavior:

- The intermission room is the boss-death respawn point.
- Its camera rests at `(2440, 320)`, matching the adjacent rooms vertically so door transitions pan only on the x-axis.
- Each door rises, the player walks through using the normal walk animation, and the door descends.
- Player control returns inside the intermission room.
- After the second door, the camera pans according to the player's complete scripted walk into the boss room and ends at `(3140, 320)`, matching the unlocked gameplay camera.
- The boss-room handoff places the player at `(3120, 300)` on solid ground.
- The boss faces inward when landing on either attack platform.
- Boss defeat disables gameplay without giving the player damage-blink immunity; the player must remain visually steady during the explosion sequence.
- After the first boss reward is collected, the player walks into the stage-exit portal before the scene changes.

## Collision and presentation traps

- Collision movement is substepped to avoid tunneling. Preserve substeps when increasing projectile speed.
- Downward collision snaps to the exact 20-pixel tile surface.
- Ceiling collision must stop upward movement without simulating a bounce or forcing an immediate downward step.
- Lethal-floor death must keep the player sprite hidden for the entire death effect. Remember that the same physics tick may continue into animation code after death.
- Player immunity controls both blinking and white flashing. Do not use a large immunity value merely to disable damage during cutscenes; disable gameplay or damage sources instead.
- Sprite artwork may have an intrinsic facing direction. Inspect the actual PNG before deciding `flip_h` semantics, and keep projectile direction consistent with the visible facing.

## Validation

Do not create or run automated or manual tests. After GDScript changes, a Godot headless parser/editor load is allowed strictly as a compile check. Gameplay validation comes from the user's playtest feedback.

Godot may not be on `PATH`. On Windows, inspect the running Godot process for its executable path when available. Typical commands are:

```powershell
& $godot_executable --headless --path godot_port --editor --quit
```

Errors about writing `user://`, editor settings, logs, or reading the Windows root certificate store can be sandbox-environment noise. Parser, resource-loading, scene, and runtime script errors are not.

Do not add test coverage for gameplay changes. Record any behavior that still needs user playtesting in the handoff instead.

## Handoff expectations

State what changed, what original evidence was checked, which manual tuning was preserved, and how the result was validated. If a detail remains an approximation, say so explicitly rather than presenting it as confirmed parity.
