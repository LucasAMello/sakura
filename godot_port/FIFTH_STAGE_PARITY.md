# Fifth-stage parity record

World 5 covers maps 50–53 and is based on the canonical `old/2 Joguito` sources and authoritative map files. World-local gameplay runs once every two 60 Hz physics ticks to retain the original 30 Hz real-time pace without changing shared player movement or weapons.

| Area | Evidence checked | Port result |
|---|---|---|
| Maps and terrain | `maps.h`, `Main.cpp`, map files, `TEXTURES06` | Original dimensions, starts, exits, layered fire terrain, parallax backgrounds, camera bounds, and map50→51→52→53 transitions |
| Spawn tables | `maps.h` | Original horizontal/vertical flamethrowers, Flamemets, falling fire, lava strips, squids, cards, holder, boss triggers, and Scaled coordinates |
| Ordinary gameplay | `sprite.h`, `scripts.h`, `colision.h`, `draw.h` | Flamethrower timing, flame bursts, Flamemet states, falling-fire hazards, damaging lava, squid behavior, persistent cards, and breakable holder |
| Map53 transition | `Main.cpp`, `set_dvalues` | Checkpoint shaft, boss-death respawn, camera handoff, and boss-room activation |
| Scaled boss | `sprite.h`, `scripts.h`, `colision.h`, `draw.h` | 30 HP, randomized attack state machine, three projectile families, damage windows, reward, portal departure, and progression to map60 |

Music, sound effects, menus, saving, and weapon selection remain project-wide omissions rather than missing World 5 gameplay entities.
