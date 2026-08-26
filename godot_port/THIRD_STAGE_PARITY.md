# Third-stage parity record

The third-stage implementation is based on the canonical `old/2 Joguito` sources and authoritative `map30.map` through `map32.map` files. Existing global player, weapon, damage, drop, door, and portal tuning remains unchanged. Unlike World 2, World 3 ordinary enemies, hazards, pickups, and boss logic run once per 60 Hz physics tick, matching the original update rate.

| Area | Evidence checked | Port result |
|---|---|---|
| Map geometry and limits | `Main.cpp`, `maps.h`, map files | Original 20-pixel maps, map30's 10,000×600 world, map31's 2,000×1,600 vertical world, map32's 6,000×640 world, starts, invisible exits, camera limits, and transitions |
| Terrain and background | `maps.h`, `TEXTURES04`, `textures05.bmp`, `bg4.bmp` | Complete thunder-stage atlas mapping, 608×480 repeating background, and the `+` token's original one-pixel-wide collision and rendering |
| Spawn tables | `maps.h` | Original wall turrets, machines, orange flyers, shockers, cards, card holder, doors, and boss coordinates and initial timers |
| Wall turrets and machines | `sprite.h`, `scripts.h`, `draw.h` | Original dimensions, HP, damage, paired directional fire, missile acceleration, random machine attacks, special machine destruction, and medium recovery rolls |
| Orange flyers | `sprite.h`, `scripts.h`, `draw.h` | Player-relative aim states, nine-frame body cycle, three-frame propeller, vertical bob, directional shot origins, HP, damage, and small recovery chance |
| Shockers | `sprite.h`, `scripts.h`, `draw.h` | Four orientations, original charge/retract timing, stationary charge animation, cardinal shock-ball launch, collision-substepped movement, HP, and damage |
| Cards | `maps.h`, `sprite.h`, `scripts.h` | Original loose card IDs, breakable holder card 38, falling/hovering movement, collection fade, and persistent inventory |
| Map32 transition | `Main.cpp`, `set_dvalues`, door source | Left door, playable checkpoint room, boss-death respawn, right door, scripted walk, fixed boss camera, and 20-tick door rise/descent tuning |
| Thunder boss | `sprite.h`, `scripts.h`, `Main.cpp` event 5 | Lightning appearance, 30-point meter and HP, flicker/crouch/dash/takeoff loop, high-health shock-ball attack, randomized low-health beam patterns, reappearance, damage gating, death sequence, card reward, and portal departure |

The release executable remains unavailable for direct visual comparison. Entry/reward portal presentation uses the already reviewed project-wide presentation, while map geometry, state order, timing, movement, damage, and spawn data follow the canonical source. Music, sound effects, menus, saving, weapon selection, and the stages after map32 remain project-wide omissions rather than missing World 3 gameplay entities.
