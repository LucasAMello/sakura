# Player asset provenance

All PNGs preserve the original pixels and convert RGB `(255, 0, 255)` to alpha. Nearest-neighbor filtering must remain enabled.

Primary source: `old/5 jogos new sakura`.

| Port asset | Loose source | Release object |
|---|---|---|
| `player_idle.png` | `playermo01.bmp` | `PLAYER_MOVING01` |
| `player_walk2.png` | `playermo02.bmp` | `PLAYER_MOVING02` |
| `player_jump.png` | `playermo03.bmp` | `PLAYER_MOVING03` |
| `player_walk4.png` | `playermo04.bmp` | `PLAYER_MOVING04` |
| `player_walk5.png` | `playermo05.bmp` | `PLAYER_MOVING05` |
| `player_fire_idle.png` | `playermo12.bmp` | `PLAYER_MOVING12` |
| `player_fire_walk2.png` | folder-2 fallback `playermo2.bmp` | `PLAYER_MOVING22` |
| `player_fire_jump.png` | `playermo32.bmp` | `PLAYER_MOVING32` |
| `player_fire_walk4.png` | `playermo42.bmp` | `PLAYER_MOVING42` |
| `player_fire_walk5.png` | `playermo52.bmp` | `PLAYER_MOVING52` |
| `default_shot.png` | `tiro0.bmp` | `YELLOW_TOSKO_SHOT` |
| `shot_hit_1.png`–`shot_hit_3.png` | `tiro0ani1.bmp`–`tiro0ani3.bmp` | `SHOT_0_1`–`SHOT_0_3` |
| `recovery_small.png` | `recuperator2.bmp` | `RECOVERY_S` |
| `recovery_medium.png` | `recuperator.bmp` | `RECOVERY_M` |
| `extra_life.png` | `vida.bmp` | `VIDA` |
| `portal_1.png`–`portal_6.png` | `portal1.bmp`–`portal6.bmp` | `PORTAL1`–`PORTAL6` |
| `death_1.png`–`death_5.png` | `pdie1.bmp`–`pdie5.bmp` | `PDIE1`–`PDIE5` |
| `attack_overlay.png` | — | `AAA` in `old/4 Sakura2.0/Media/files.dat` |

## Weapon-specific Sakura sprites

The unsuffixed player frame is weapon 1; suffixes `A` through `F` are weapons 2 through 7 respectively. The port stores the weapon sets under `weapon2_wind/`, `weapon3_shadow/`, `weapon4_thunder/`, `weapon5_water/`, `weapon6_fire/`, and `weapon7_ice/`.

At the user's request, each directory's `idle.png`, `walk2.png`, `jump.png`, `walk4.png`, and `walk5.png` come from `old/5 jogos new sakura/playermo01[a-f].bmp` through `playermo05[a-f].bmp`, respectively. All 30 frames retain their original 54×80 dimensions, with RGB `(255, 0, 255)` converted to transparent pixels. Animation order, frame timing, and collision dimensions are unchanged.

The five `fire_*` equivalents still come from the corresponding `PLAYER_MOVING12*`–`PLAYER_MOVING52*` objects in `old/2 Joguito/files.dat`.

The later completed source draws `AAA` over every firing player frame. The port preserves its direction-dependent horizontal placement and its original two-pixel vertical adjustment for the jump and fifth walk frames.
