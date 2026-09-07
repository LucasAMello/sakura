# Fourth-stage parity record

World 4 covers maps 40–42 and is based on the canonical `old/2 Joguito` sources and authoritative map files. Global player and weapon tuning remain at 60 Hz, while World 4 enemies, projectiles, hazards, boss logic, and source-timed water effects preserve the original 30 Hz real-time pace.

| Area | Evidence checked | Port result |
|---|---|---|
| Maps and terrain | `maps.h`, `Main.cpp`, map files, `TEXTURES05` | Original dimensions, starts, exits, layered scenario/foreground rendering, terrain tokens, water surfaces, camera limits, and map40→41→42 transitions |
| Water presentation | `Main.cpp`, `player.h`, `sprite.h`, `scripts.h`, `draw.h` | Animated water surface, underwater player gravity, surface-crossing splash, and a bubble every 160 original updates; effects use direct source artwork and 30 Hz-equivalent timing |
| Spawn tables | `maps.h` | Original Resettis, seahorse ambushes, randomized fish, oyster pairs, cards, sand mounds, doors, and Turtle coordinates |
| Ordinary objects | `sprite.h`, `scripts.h`, `colision.h`, `draw.h` | Resetti movement, seahorse emergence, fish pursuit, oyster pearls, persistent cards, and breakable card-bearing sand mounds |
| Map42 transition | `Main.cpp`, `set_dvalues`, door source | Two doors, playable checkpoint room, boss-death respawn, scripted walk, and fixed boss camera |
| Turtle boss | `sprite.h`, `scripts.h`, `colision.h`, `draw.h` | 30 HP, contact damage, intro, randomized water-shot/dash attacks, low-health rapid chains, segmented water jets, reward, portal departure, and progression to map50 |

The six shoreline slope tokens use the source-image alpha mask for pixel-accurate collision. Canonical music, sound effects, menus, JSON and legacy saving, pause weapon selection, and control remapping are provided by the shared project systems.

Background rows retain the original 400-pixel spacing and map40's -100-pixel offset on the upper row. Three copies per row cover the full viewport throughout scrolling. World 4 music uses a composite stream to avoid a gap at the initial-to-repeat boundary.

Seahorses reveal the head first and face Sakura during ascent and the upright hold. The original sequence holds the upright frame for six source updates, shows the intermediate frame for one update, then spins before dashing on attack update ten. Spin uses Allegro's 24/256-turn increment around the sprite center. Rise remains 17 pixels and dash 25 pixels per 30 Hz update (510 and 750 pixels/second), with the entire sequence advancing every two Godot physics ticks. Spawner activation uses the original player-edge distances.

Fish pursuit uses the original top-left coordinate comparisons, asymmetric detection distances, braking thresholds, and held swim frames. Acceleration remains 0.3 pixels per source update (0.4 when reversing horizontally), with a 5-pixel per-axis cap, applied once every two 60 Hz physics ticks. Detection displays the original HA sprite at its source offset for six source updates, including the timer-zero removal update. Gameplay validation remains dependent on user playtesting.

Oysters retain their map-defined facing direction, as in the archive. Opening and closing use the original position offsets, center pivot, Allegro angle conversion, and dedicated right-facing rotation texture. Firing and animation retain the two-physics-tick cadence; pearls draw behind the shell.

## Turtle audit

Rechecked canonical type 1005 in `scripts.h`, initialization in `sprite.h`, collision cases in `colision.h`, the type-36 jet drawing in `draw.h`, and the boss events and death flash. All boss and jet source updates run once per two 60 Hz physics ticks. Ordinary attack selection waits 30 source updates; normal shots fire on update 6 and finish on 27, while rapid shots finish on 15. Dashes begin moving on update 8 and play their sound on update 10.

The dash damages Sakura without ending on player contact. Recovery expands the shell collision width on the original direction-dependent frame. The rapid right-wall recovery proceeds directly to a left-facing shot; the opposite recovery selects its next attack. The low-health threshold uses fractional boss health.

Jets draw behind the boss, grow by two segments per source update, and include the original extra 16-pixel displacement when reaching full length. At walls, trailing jets finish expanding before retracting; right-facing jets keep their front anchored while shortening. The original two-frame front/tail and alternating middle animation remain in place. Collision remains substepped, with the arena door represented by its blocking edge.

Defeat uses a half-second full-white hold, source explosion offsets, and the boss's current collision dimensions for reward placement. Reward homing, spin, and collection fade use the world cadence, including the mirrored return half of the spin. Explosion artwork still uses the shared port effects; this audit does not establish exact visual parity for those effects. No gameplay tests were run; the Godot editor compile check passed, and gameplay/presentation require user playtesting.
