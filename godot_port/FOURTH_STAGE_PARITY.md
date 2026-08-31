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

The six shoreline slope tokens still use full-cell collision because the current terrain system has no pixel-mask or slope representation. This is a documented collision approximation, not a missing gameplay entity. Music, sound effects, menus, saving, and weapon selection remain project-wide omissions.
