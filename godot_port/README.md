# Sakura — Godot port hand-off

This is a preservation-minded Godot 4 port of Sakura, a C++/Allegro game originally released in 2008. The current playable milestone covers Worlds 1–6 continuously: maps 10–14, 20–23, 30–32, 40–42, 50–53, and 60–62.

The surviving Windows release crashes after its menu, so gameplay is being reconstructed from source code, maps, assets, and the creator's memory rather than compared against a working original executable.

## Current status

Running the main project starts map10 and progresses continuously through all implemented worlds. Each boss reward leads to the next world's first map through World 6; World 6 ends at its completion screen because World 7 is outside the implemented scope.

Implemented:

- Original terrain data for maps 10–14
- Horizontal maps 10, 12, and 14
- Vertical maps 11 and 13
- Normal player movement, variable jump, damage, immunity, animation, and default weapon
- Red balls, happy springs, green turrets, exploding turret projectiles, parakeets, and pumpkins
- Original ordinary-enemy positions, directions, and initial timers
- Entry sequence, original-style HUD, animated deaths, camera, restart, exits, and scene transitions
- HP preservation between maps through the `SakuraProgress` autoload
- Original small, medium, and extra-life drops with falling and terrain landing
- All eight original World 1 cards, including the two breakable card holders
- Persistent lives, including the original cap of nine
- Recycled 2×2 background grid that covers horizontal and vertical scrolling
- Enter-key pause overlay with resume, restart, and quit controls
- Map14 boss room, falling-block intro, giant parakeet boss, feather attacks, reward, portal departure, boss life meter, and stage completion
- Original terrain, starts, exits, camera limits, and spawn tables for maps 20–23
- Stage-two ghosts, directional ghost-mask streams, shadow spikes, reveal paintings, breakable armor, and persistent cards
- Map23 door sequence, playable checkpoint room, boss-death respawn, shadow-boss transformation, split clone, reward, and stage completion
- Original terrain, starts, exits, camera limits, background, and spawn tables for maps 30–32
- Stage-three wall turrets, accelerating missiles, machines, orange flyers, four-way shockers, shock charges and balls, breakable card holder, and persistent cards
- Map32 two-door checkpoint, boss-death respawn, Thunder boss intro, dash/takeoff cycle, high- and low-health attack patterns, reward, portal departure, and stage completion
- Authoritative maps 40–42, World 4 scenario/foreground terrain layers, parallax background, animated water, bubbles and splashes, underwater player gravity, Resetti and seahorse ambushes, four fish variants, oyster pairs/pearls, cards, map42 checkpoint, Turtle boss, segmented water attacks, reward, and departure
- Authoritative maps 50–53, layered fire terrain, original parallax backgrounds, ordinary enemies and hazards, seven persistent cards, map53 checkpoint, Scaled boss, reward, departure portal, and progression to World 6
- Authoritative maps 60–62, complete ice terrain and overlays, backgrounds, Ice Mets and death needles, icicles, spike strips, reused pumpkins, cards and holders, map62 checkpoint, Icy boss, five projectile patterns, reward, and departure

Map14 now uses two door transitions around a playable intermission room. Entering the left door establishes the original `(2300, 300)` boss checkpoint and returns control to the player; entering the right door starts the boss-room sequence. Death during the boss sequence respawns in the intermission room. The checkpoint camera is `(2440, 320)`, so both adjacent room transitions pan only horizontally. The falling-block order and reward behavior follow the source structure, while the door and portal presentation incorporates confirmed playtest tuning.

Both doors take 40 ticks to rise and 40 ticks to descend. During traversal the player advances at two pixels per tick using the normal `1, 2, 3, 2, 1, 4, 5, 4` walk cycle while the camera pans into the next room. The boss-room handoff ends at `(3120, 300)`, on the first solid floor tile, with the camera already at its normal playable position of `(3140, 320)`.

## Run and controls

Open `project.godot` in Godot 4.x and run the project. The project metadata currently targets Godot 4.7.

- Left/Right arrows: move
- F: jump; holding it produces the full jump
- D: fire; holding it repeatedly fires at the tuned 25-tick interval
- R: restart the current map
- F3: toggle debug information
- Enter: pause or resume
- Escape: quit

The logical viewport and window are both 640×480. Physics runs at 60 updates per second. Nearest-neighbor filtering is intentional and preserves the pixel art at native scale.

## Source folders

The numbered archive folders have different purposes:

| Folder | Meaning | Porting value |
|---|---|---|
| `old/1 Sakura (2008 release)` | Original distributable with `files.dat` | Release reference and final asset fallback |
| `old/2 Joguito` | Complete original C++/Allegro source | Canonical source for behavior, maps, spawns, and constants |
| `old/3 Joguito 2` | Partial C++ reorganization/rewrite | Useful for understanding intended refactors, not canonical behavior |
| `old/4 Sakura2.0` | Another incomplete and messier reorganization | Secondary research only |
| `old/5 jogos new sakura` | Incomplete GameMaker port with loose assets | Primary visual-asset source |

For maps and gameplay behavior, start with:

- `old/2 Joguito/maps.h`: terrain-token mapping and level spawn tables
- `old/2 Joguito/Main.cpp`: map dimensions, starting points, backgrounds, limits, and scripted events
- `old/2 Joguito/scripts.h`: per-tick enemy behavior and animation
- `old/2 Joguito/sprite.h`: entity initialization, dimensions, HP, damage, and speed
- `old/2 Joguito/colision.h`: original collision behavior
- `old/2 Joguito/map10.map` through `map14.map`, `map20.map` through `map23.map`, `map30.map` through `map32.map`, `map40.map` through `map42.map`, `map50.map` through `map53.map`, and `map60.map` through `map62.map`: authoritative map data used by this port

## Asset policy

Use assets in this order:

1. `old/5 jogos new sakura`
2. `old/2 Joguito` when folder 5 is missing the required file
3. Objects extracted from `old/1 Sakura (2008 release)/files.dat` for verification or final fallback

Folder 5 contains the correct release-era `playermo01.bmp`. The firing walk-frame fallback is `old/2 Joguito/playermo2.bmp`; do not replace it with folder 5's `playermo02.bmp`, which represents a different object/frame.

Many BMPs that appear to have different hashes differ only in header DPI metadata. Compare decoded pixels before treating them as different artwork. The red-ball, spring, bird, terrain, and default-shot graphics checked across the archives were pixel-identical.

Allegro transparency uses RGB `(255, 0, 255)`. Converted PNGs must replace that magenta with alpha without resizing or filtering the source pixels. Assets are grouped by ownership: `assets/player/`, `assets/menu/`, `assets/hud/`, and `assets/world1/` through `assets/world6/`. Provenance is recorded beside the relevant assets in each folder.

Godot `.import` files and the `.godot` import cache are generated metadata. Godot can regenerate them from the source PNGs. Do not treat them as original game assets.

## Project architecture

Scripts are grouped by ownership in `scripts/player/`, `scripts/menu/`, `scripts/hud/`, and `scripts/world1/` through `scripts/world6/`. Cross-world systems live in `scripts/shared/`. Each world uses one shared stage implementation instead of copied map scripts.

| File | Responsibility |
|---|---|
| `scripts/shared/stage_base.gd` | Shared stage lifecycle, player/HUD setup, entry presentation, projectiles, enemy registry, death flow, camera setup, and controls |
| `scripts/world1/stage1.gd` | Stage-one controller and `MAP_CONFIGS` for maps 10–14 |
| `scripts/shared/terrain.gd` | Dynamic map loader, tile rendering, solid checks, lethal cells, and world dimensions |
| `scripts/player/player.gd` | Player movement, jump, animation, firing, HP, damage, and exit walk |
| `scripts/shared/enemy_base.gd` | Shared enemy health, player contact, projectile mask checks, and drops |
| `scripts/world1/red_ball.gd` | Red-ball patrol and ledge detection |
| `scripts/world1/happy_spring.gd` | Spring timing and vertical movement |
| `scripts/world1/green_turret.gd` | Stationary turret and projectile spawning |
| `scripts/world1/enemy_projectile.gd` | Turret projectile movement and damage |
| `scripts/world1/turret_shot_explosion.gd` | Original three-frame turret projectile impact effect |
| `scripts/world1/card_pickup.gd`, `card_holder.gd` | Persistent World 1 cards and breakable holders |
| `scripts/world1/pirikito.gd` | Parakeet vertical cycle |
| `scripts/world1/pumpkin.gd` | Pumpkin patrol and proximity speed-up |
| `scripts/player/projectile.gd` | Player default shot |
| `scripts/shared/stage_progress.gd` | HP, lives, boss checkpoints, rewards, and card inventory carried between map scenes |
| `scripts/hud/hud.gd` | Original-style player and boss life meters, pause, messages, and debug display |
| `scripts/player/death_effect.gd` | Original twelve-fragment player death animation |
| `scripts/shared/enemy_death_effect.gd` | Shared ordinary-enemy destruction animation |
| `scripts/world1/first_boss.gd` | Map14 giant parakeet boss states and attacks |
| `scripts/world1/boss_feather.gd` | First-boss feather projectile |
| `scripts/world1/boss_room_block.gd` | Scripted falling blocks in the map14 boss intro |
| `scripts/world1/boss_reward.gd` | Animated first-boss reward and player homing sequence |
| `scenes/map10.tscn`–`map14.tscn` | Small scene wrappers that select `map_number` |
| `scripts/world2/stage2.gd` | Shared stage controller and spawn configuration for maps 20–23 |
| `scripts/world2/ghost.gd`, `scripts/world2/ghost_mask.gd` | Stage-two ghost families and directional mask attacks |
| `scripts/world2/stage2_armor.gd`, `scripts/world2/stage2_painting.gd` | Breakable armor and position-revealed painting |
| `scripts/world2/card_pickup.gd`, `scripts/world2/shadow_spike.gd` | Persistent cards and wide shadow-spike hazards |
| `scripts/world2/second_boss.gd`, `scripts/world2/shadow_clone.gd` | Map23 shadow boss and shared-health split clone |
| `scripts/world2/second_boss_reward.gd` | Animated second-boss reward and player homing sequence |
| `scenes/map20.tscn`–`map23.tscn` | Small scene wrappers that select the stage-two `map_number` |
| `scripts/world3/stage3.gd` | Shared controller, terrain mapping, spawn configuration, checkpoint, boss, and victory flow for maps 30–32 |
| `scripts/world3/wall_turret.gd`, `machine.gd`, `orange_enemy.gd`, `shocker.gd` | Stage-three ordinary enemy families |
| `scripts/world3/world3_projectile.gd` | Wall shots, missiles, shock charges/balls, boss lightning, and boss beams |
| `scripts/world3/card_holder.gd`, `card_pickup.gd` | Breakable card holder and persistent World 3 cards |
| `scripts/world3/third_boss.gd`, `third_boss_reward.gd` | Thunder's complete state machine and animated reward |
| `scenes/map30.tscn`–`map32.tscn` | Small scene wrappers that select the stage-three `map_number` |
| `scripts/world4/stage4.gd` | Shared controller for maps 40–42, layered terrain, water, checkpoint, boss, reward, and progression |
| `scripts/world4/water_layer.gd`, `water_bubble.gd`, `water_splash.gd`, `resetti.gd`, `seahorse.gd`, `fish.gd`, `oyster.gd` | Water presentation and World 4 ordinary enemy families |
| `scripts/world4/sand_mound.gd`, `card_pickup.gd` | Breakable sand-mound holders and persistent loose cards |
| `scripts/world4/fourth_boss.gd`, `water_shot.gd`, `fourth_boss_reward.gd` | Turtle boss, segmented water projectiles, and animated reward |
| `scenes/map40.tscn`–`map42.tscn` | Small scene wrappers that select the stage-four `map_number` |
| `scripts/world5/stage5.gd` | Shared controller, map configuration, layered terrain, backgrounds, checkpoint, boss, and victory flow for maps 50–53 |
| `scripts/world5/flamethrower.gd`, `flame_burst.gd`, `flamemet.gd`, `falling_fire.gd`, `lava_strip.gd`, `squid.gd` | World 5 ordinary enemies and hazards |
| `scripts/world5/card_holder.gd`, `card_pickup.gd` | Breakable card holder and persistent World 5 cards |
| `scripts/world5/fifth_boss.gd`, `boss_projectile.gd`, `fifth_boss_reward.gd` | Scaled's state machine, three projectile families, and animated reward |
| `scenes/map50.tscn`–`map53.tscn` | Small scene wrappers that select the stage-five `map_number` |
| `scripts/world6/stage6.gd` | Shared controller, map configuration, ice terrain/overlays, checkpoint, boss, and victory flow for maps 60–62 |
| `scripts/world6/ice_met.gd`, `ice_needle.gd`, `icicle.gd`, `ice_spike.gd`, `ice_pumpkin.gd` | World 6 ordinary enemies, projectiles, and hazards |
| `scripts/world6/card_holder.gd`, `ice_holder.gd`, `card_pickup.gd` | Breakable holders and persistent World 6 cards |
| `scripts/world6/icy_boss.gd`, `icy_attack.gd`, `sixth_boss_reward.gd` | Icy's complete state machine, five attack variants, and animated reward |
| `scenes/map60.tscn`–`map62.tscn` | Small scene wrappers that select the stage-six `map_number` |

The six world controllers extend `scripts/shared/stage_base.gd`. They retain their map data, world-specific objects and backgrounds, camera constraints, timing rules, and boss sequences while the common stage lifecycle stays in one place.

To add another similar map:

1. Copy the original `.map` file into `maps/`.
2. Add its dimensions, start, exit, next map, and spawn tables to `MAP_CONFIGS`.
3. Add a small `.tscn` wrapper with the correct `map_number`.
4. Add any new entity behavior as a reusable script rather than branching heavily inside the stage controller.
5. Use a Godot editor load only as a parser and resource compile check; gameplay validation is manual.

## Important current behavior decisions

These choices were made during hands-on review and should not be silently reverted to initial placeholder behavior:

- The player walk animation holds each frame for eight physics ticks.
- Jump and walk frame 3 share artwork. Landing resumes on texture index 2 for a smooth transition.
- Holding fire uses the firing variant of the current player frame.
- Holding D fires immediately and then every 25 physics ticks while fewer than four player shots are active.
- Player shots move 9 pixels per physics tick and play the original three-frame impact animation when they hit terrain or an enemy.
- Player shots explode once their horizontal distance from Sakura exceeds 480 pixels.
- Player damage grants 80 physics ticks of immunity and flashes the current sprite white through `shaders/white_flash.gdshader`; the separate damaged sprite was removed.
- Downward player collision snaps the body to the exact 20-pixel tile surface to prevent a subpixel gap beneath the sprite.
- Red-ball ground probes are 10 pixels deep. The previous 50-pixel probe incorrectly detected lower platforms and allowed enemies to walk in midair.
- Red balls move at 2 pixels per tick and hold each animation frame for eight ticks.
- The background uses four shared sprites in a 2×2 recycled grid.
- Recovery drops from defeated enemies are centered within the defeated enemy and fall at 7.5 pixels per tick.
- Portals appear only at the entrance to map10, map20, and map30, at boss-checkpoint revival entrances, and for the departure after the last map of a stage. Ordinary between-map exits use the original invisible exit regions without portal markers.
- Green turrets fire once every 120 ticks, half the previous firing rate.
- Green turrets retain their 25% medium-recovery chance and have an exact 10% extra-life chance.
- Turret projectiles play their original three-frame explosion when they hit terrain, hit the player, or exhaust their travel lifetime.
- Turret-projectile explosion frames are held twice as long as their previous timing.
- Pirikito preserves its original velocity cycle while applying a 75% movement scale.
- Pumpkin shots stun it without health loss or a red damage blink.
- The first boss uses one horizontal-flight sprite and dashes at 10 pixels per tick. Its feathers retain two collision substeps but move `20 / 3` pixels per substep, or `40 / 3` pixels per tick.
- The map14 falling-stage introduction uses the latest playtest timing: activation delays and explosion cadence are four times the archive timing, blocks fall at 3 pixels per tick, and the boss waits 120 ticks before entering. Falling blocks emit the same explosion used by turret projectiles.
- Card collectible spin frames are held twice as long in every world without changing their falling or collection-fade rates.
- The first-boss health meter fills one point every two physics ticks, and pausing suspends both the boss and active feathers.
- Player death fragments originate at the center of the 40×80 player body.
- Scripted walks at ordinary map exits use the normal walk animation.
- The first-boss life meter remains visible if the player dies during the fight. Victory portals appear 40 pixels ahead in the direction Sakura is facing; her sprite is progressively clipped at the portal plane until the complete 54-pixel-wide frame has passed through.
- World 2 enemies, hazards with active timing, pickups, rewards, and boss logic update once every two 60 Hz physics ticks. Shared player movement and weapon tuning remain global and are not halved.
- World 3 and later world-local enemies, enemy projectiles, active hazards, and boss logic update once every two 60 Hz physics ticks, matching the original Allegro game's 30 Hz real-time pace without lowering Godot's frame rate.
- World 3's `+` terrain token is a full-size, decorative 20×20 tile. The archive's `1` is its non-solid draw type, not a one-pixel width.
- Map21 has no stage backdrop; spawned ghost masks immediately join active gameplay, and armor draws behind other enemies.
- World 2 wall interiors use the alternating castle-brick background graphics while retaining the original non-solid decorative cells and solid border collision.
- World 2 ghost masks retain their 20% small-recovery chance and have an exact 10% extra-life chance.
- A stage-two painting begins reverting once Sakura's center reaches its left edge, reveals once at Sakura's four-pixel movement speed, and remains fully reverted afterward.
- The `READY` graphic appears only when entering the first map of a world or reviving at that world's boss checkpoint, never during ordinary between-map transitions.

The reviewed source-to-port behavior matrices are maintained in the world parity records, including `SECOND_STAGE_PARITY.md` through `SIXTH_STAGE_PARITY.md`. Update them whenever a source mismatch is confirmed or a deliberate playtest adjustment supersedes the archive.

Original movement and animation logic is tick-based because the Allegro game assumed a fixed update rate. Preserve ticks when matching original gameplay. Use `delta` for new purely visual effects unless their timing affects collision or attacks.

## Known omissions and risks

- Music, sound effects, menus, saving, and weapon changes are not implemented.
- Boss-room audio and the weapon unlocked by the first-boss reward still need restoration.
- Stage-two card inventory persists for the current run, but save-file persistence and card-driven maximum-HP progression are not yet connected to menus or a save system.
- Entry and exit presentation are functional approximations where the crashed release could not be observed.
- The original code sometimes contains contradictory or accidental values. Prefer source evidence plus in-game review over mechanically copying every bug.

## Validation

This project intentionally has no automated or smoke tests. Contributors should not create or run tests. A headless editor load may be used only as a GDScript and resource compile check:

```powershell
& $godot_executable --headless --path godot_port --editor --quit
```

Gameplay validation is based on user playtest feedback.

## Porting specifications

The original map10 investigation and first playable-slice specification remain in the repository root:

- `Sakura_Godot_Port_Spec_Map10.txt`: text-oriented implementation reference
- `Sakura_Godot_Port_Spec_Map10.html`: visual version with images and formatting

Those files contain the detailed initial evidence. This README records decisions made after implementation began and should be read alongside them.

## Collaboration preference

Keep changes small and testable, preserve user-adjusted values, and avoid adding explanatory comments directly to the code unless requested. Existing timing, animation holds, and movement speeds must be presumed intentional even when they differ from the old source. Use the archive to correct behavior structure, drops, coordinates, damage, and missing state transitions without reverting playtest tuning. Put hand-off rationale and research notes in this README or a dedicated document instead.
