# Sakura project instructions

## Scope

This repository contains the archived source and assets for Sakura plus a preservation-minded Godot 4 port. Active development is in `godot_port/`. The port covers the complete canonical campaign: title/menu and stage select, Worlds 1–6, maps 70–80, six final-stage rematches, the final boss, and ending/credits. Later unfinished Sakura 2.0 features are outside scope.

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
- `old/2 Joguito/map10.map` through `map14.map`, `map20.map` through `map23.map`, `map30.map` through `map32.map`, `map40.map` through `map42.map`, `map50.map` through `map53.map`, `map60.map` through `map62.map`, and `map70.map` through `map80.map`: authoritative campaign maps

Search the archive before guessing. Follow entity type numbers through initialization, update, collision, and draw code because behavior is often split across several files.

## Port architecture

- `godot_port/scripts/shared/stage_base.gd` owns behavior shared by every stage controller.
- `godot_port/scripts/world1/stage1.gd` is the controller for maps 10–14.
- `godot_port/scripts/world2/stage2.gd` is the shared controller for maps 20–23.
- `godot_port/scripts/world3/stage3.gd` is the shared controller for maps 30–32.
- `godot_port/scripts/world4/stage4.gd` is the shared controller for maps 40–42.
- `godot_port/scripts/world5/stage5.gd` is the shared controller for maps 50–53.
- `godot_port/scripts/world6/stage6.gd` is the shared controller for maps 60–62.
- `godot_port/scripts/world7/stage7.gd` controls maps 70–73 and the rematch hub; `stage80.gd` controls the final arena.
- `godot_port/scripts/shared/game_flow.gd` is the only campaign scene router. Stage controllers must not hard-code the next elemental world.
- `godot_port/scripts/shared/audio_manager.gd` owns track transitions, source loop offsets, and one-shot SFX playback.
- `godot_port/scripts/player/player.gd` owns movement, collision, damage, immunity, animation, firing, and scripted walking.
- `godot_port/scripts/shared/enemy_base.gd` owns shared enemy behavior.
- Individual enemy and boss scripts live in their owning `godot_port/scripts/world1/` through `world6/` folders; cross-world logic lives in `godot_port/scripts/shared/`.
- Small scene wrappers in `godot_port/scenes/` select each implemented map number.
- `SakuraProgress` is registered as an autoload in `godot_port/project.godot`. In scripts, resolve it with `get_node("/root/SakuraProgress")`; direct global identifier use has caused parser failures in this workspace.

The game uses a 640×480 logical viewport and 60 fixed physics ticks per second, while the original Allegro game updated gameplay at 30 Hz. Preserve the 60 Hz Godot physics rate, but convert original tick-based movement, collision, attacks, firing, and animation to the same real-time pace. World-local enemies and enemy projectiles can retain the archive's per-update values by running their gameplay update once every two physics ticks. Do not apply that world-local cadence to shared player movement or weapon tuning. Use `delta` only for new visual behavior that cannot affect gameplay parity.

The New Game dream/intro sequence is a presentation exception: the Sakura 2.0 source installs its `speed_counter` at 60 Hz, so its opening delay, text fades, falling animation, scene fades, and closing hold advance every Godot physics tick. Do not apply the two-tick world cadence to that cinematic.

World 7 has the same conversion requirement as Worlds 3–6. Every reused or new enemy, hazard, projectile, animation, state timer, attack chooser, portal trigger, and firing interval must advance on the 30 Hz-equivalent world tick. Setting enemy movement to half speed while leaving its animation or firing timer at 60 Hz is incorrect. Final-boss projectiles use an explicit two-physics-tick phase; final-boss behavior uses `SakuraEnemy.update_interval_ticks = 2` through the stage spawn path. The player remains a 60 Hz controller throughout World 7.

World 7 final-boss constants in `old/2 Joguito/scripts.h` are source-tick values and should be used directly on those two-tick update paths; do not double their timers or halve their per-update projectile motion a second time. Maps 71–73 change between `TEXTURES08` and `TEXTURES09` within each row, and map80 uses tokens `2` and `3` as non-solid atlas selectors rather than visible terrain. Preserve those selector rules when changing World 7 map rendering or collision.

Weapons 2–7 also remain on the player's 60 Hz path. Translate original 30 Hz weapon timers to the same real time by doubling tick durations, and translate motion without losing collision substeps. Never place player weapon selection or active-shot accounting on the World 7 cadence.

## Current tuning that must be preserved

Stage 6 update (2026-09-08): the user's continuation supersedes older Stage 6 interval-two and tuned timing guidance. Enemies, needles, the icy boss and attacks now update every physics tick with source-paced timers and movement; holders, rewards, recovery and death effects are converted too. Icicles retain source acceleration overshoot to 42, 20-tick terrain grace, and eight-tick landing linger. Keep the boss wall clipping and pose alignment. See the Stage 6 record in `godot_port/TIMING_ADJUSTMENTS.md`.

Stage 5 update (2026-09-08): the user's continuation supersedes older interval-two timing for Stage 5. Enemy and boss logic now runs every 60 Hz physics tick with fourfold source-script timers and quarter-step motion. The squid retains its source velocity milestones and surface clipping. See the latest Stage 5 work record in `godot_port/TIMING_ADJUSTMENTS.md`; do not restore the old fast flame cycle or projectile speeds.

Stage 4 update (2026-09-08): the user's continuation of the source-fidelity timing pass supersedes the older interval-two guidance for Stage 4. Enemies, the turtle, jets, and water effects now update every physics tick with converted source-script timing. The turtle's prior interval-four pace is preserved with smooth movement. Consult the latest Stage 4 record in `godot_port/TIMING_ADJUSTMENTS.md` for values, reuse, and draw-clock assumptions. Preserve the portal and foreground layering fixes.

Stages 2/3 update (2026-09-08): the user's source-fidelity request supersedes their older interval-two and tuned timing guidance below. Both stages and converted reusable enemies/projectiles update every 60 Hz physics tick with 15 Hz-source-equivalent durations and movement. Consult the latest Stages 2/3 work record in `godot_port/TIMING_ADJUSTMENTS.md`, including Thunder phase/frame corrections and declared draw-rate assumptions. Do not restore the older 30 Hz gates or tuned speeds from this historical list.

Stage 1 object timing update (2026-09-07): the user's object pass also supersedes the older card, recovery, block, reward, and boss-meter exceptions below. Stage 1 card/holder spin cycles are 160 ticks, holder breaking is 80 ticks, card/reward fades are 36 ticks, recovery falls at 3.75 px/tick, blocks fall at 3 px/tick, and the boss meter fills every four ticks. See the latest object record in `godot_port/TIMING_ADJUSTMENTS.md` for scope and original clock evidence.

Stage 1 timing update (2026-09-07): the user's latest instruction supersedes the older Stage 1 movement exceptions below. Red balls now move 1 px per 60 Hz tick; pumpkin patrol/chase are 2.5/5; Pirikito uses full source excursion with a fourfold clock; bird dash is 9.75 and feathers use two 5-pixel substeps. Source scripts run at 15 Hz, not the previously assumed 30 Hz. Consult `godot_port/TIMING_ADJUSTMENTS.md` for the current timing record; do not restore superseded values from this historical list.

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
- Maps 70–80 and all final-boss attacks follow that same two-physics-tick cadence. Rematches reuse the owning boss controller and therefore retain that controller's existing cadence and manual tuning.
- Original MIDI loop positions are beat markers, not percentages or sample offsets. Allegro loops by silencing active notes and seeking, so each looping track needs two renders: an initial section from its source `midi_seek` beat through the loop-end beat, and a fresh-state loop section from the loop-start beat through the loop-end beat. Do not point an OGG loop offset into a full render because it retains notes that began before the seek point. Use `godot_port/tools/midi_timing.py` and `midi_slice.py` when regenerating audio.
- Do not assume Sakura's MIDI files use 120 BPM. Their explicit tick-zero tempo events must override the Standard MIDI default tempo; preserve event order when calculating marker times. World 1's corrected initial and loop sections are `71.641760` and `68.059672` seconds, and World 2's are `77.014892` and `73.432804` seconds.
- World 1, World 2, and World 3 boss/checkpoint doors take 40 ticks to rise and 40 ticks to descend.
- The World 3 boss updates movement and screen-flash interpolation every physics tick while preserving its tuned sequence timing: four physics ticks per sequence step, or two for the shock-ball attack. Fractional movement is retained and rendering uses pixel snapping. Takeoff frame-alignment offsets apply with their sprite changes. Dashes use frames 5 then 4. Beam visuals last nine physics ticks, three per frame; strike timing and wave spacing are unchanged.
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
