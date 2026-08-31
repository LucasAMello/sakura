# Sixth-stage parity record

World 6 covers maps 60–62 and is based on the canonical `old/2 Joguito` sources and authoritative map files. World-local gameplay runs once every two 60 Hz physics ticks to reproduce the original 30 Hz real-time movement, animation, state timing, and firing cadence.

| Area | Evidence checked | Port result |
|---|---|---|
| Maps and terrain | `maps.h`, `Main.cpp`, map files, `TEXTURES07` | Original dimensions, starts, exits, complete ice atlas mapping, decorative overlay cells, backgrounds, camera bounds, and map60→61→62 transitions |
| Spawn tables | `maps.h` | Original Ice Mets, icicle pairs, spike strips, reused pumpkins, loose cards, card/ice holders, boss-floor blocks, doors, and Icy coordinates |
| Ordinary gameplay | `sprite.h`, `scripts.h`, `colision.h`, `draw.h` | Ice Met patrol and seven-needle death burst, falling icicles, ice spikes, pumpkin stun behavior, persistent cards, and breakable holders |
| Map62 transition | `Main.cpp`, `set_dvalues` | Boss checkpoint, two doors, checkpoint respawn, scripted traversal, fixed boss camera, and boss-room floor caps |
| Icy boss | `sprite.h`, `scripts.h`, `colision.h`, `draw.h` | 30 HP, shadow entrance, vulnerable emergence forms, player-relative repositioning, health-tiered projectile patterns, five attack variants, reward, portal departure, and completion screen |

World 6 ends at its completion screen because World 7 is not implemented. Music, sound effects, menus, saving, and weapon selection remain project-wide omissions rather than missing World 6 gameplay entities.
