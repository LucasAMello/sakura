# Second-stage parity record

The stage-two implementation is based on the canonical `old/2 Joguito` sources and authoritative `map20.map` through `map23.map` files. Existing player speed, animation holds, firing cadence, projectile speed, damage presentation, and other manually reviewed first-stage tuning remain unchanged.

| Area | Evidence checked | Port result |
|---|---|---|
| Map geometry and limits | `Main.cpp`, `maps.h`, map files, playtest review | Original 20-pixel maps, dimensions, starts, exits, camera limits, recycled stage-two parallax background on map20, no backdrop on maps 21–23, and stage transitions for maps 20–23 |
| Terrain set | `maps.h`, datafile object `TEXTURES02`, loose `textures03.bmp`, playtest review | Stage-two castle atlas mapping with decorative `6`, `m`, `n`, `x`, and `z` wall-type-1 cells kept non-solid. The `6` wall interiors use the alternating brick background graphics instead of the atlas's flat placeholder fill. |
| Spawn tables | `maps.h` | Original ghosts, mask emitters, paintings, armors, spikes, cards, doors, and boss coordinates |
| Ghosts | `sprite.h`, `scripts.h`, `colision.h` | Proximity activation, translucency, pursuit acceleration, animation, HP, damage, and collision gating, paced at half the original update rate |
| Flying masks | `sprite.h`, `scripts.h`, `colision.h` | Directional random-height emission, immediate gameplay activation, oscillation, speed, HP, damage, fade, and original two-roll drop logic, paced at half the original update rate |
| Paintings and armor | `draw.h`, `scripts.h`, `colision.h`, playtest review | One-shot painting reversion triggered by Sakura and animated at her movement speed, animated armor eyes, one-hit break sequence, recovery/card release, inert shell, and armor drawn behind active enemies |
| Cards | `sprite.h`, `scripts.h`, `colision.h` | Falling or hovering movement, animation, fade collection, and persistent card IDs |
| Map23 transition | `Main.cpp`, `draw.h`, `colision.h` | Left door, playable checkpoint room, right door, scripted walking, camera handoff, and boss-room respawn |
| Shadow boss | `sprite.h`, `scripts.h`, `colision.h` | Shadow cycle, twelve-frame transformation, 30-point meter and HP, substepped bounce, split clone, shared damage, death effect, card reward, and portal departure, with active logic paced at half the original update rate |

The half-rate World 2 pacing is confirmed tuning and takes precedence over the archive's raw tick speed. Canonical music, sound effects, menus, JSON and legacy saving, pause weapon selection, and control remapping are provided by the shared project systems. Boss victory uses the original portal-departure presentation and returns to stage select through the campaign flow.
