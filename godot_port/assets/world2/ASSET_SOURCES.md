# World 2 asset provenance

All PNGs preserve their original dimensions and pixels. RGB `(255, 0, 255)` was converted to alpha, and the Godot scripts select nearest-neighbor filtering.

The loose visual sources are in `old/5 jogos new sakura`. The three ghost-mask frames were absent there and were extracted from that folder's Allegro `grabber/files.dat` archive with its bundled `dat.exe` utility.

| Port asset | Original source |
|---|---|
| `terrain.png` | `textures03.bmp` (`TEXTURES02` in the Allegro datafile) |
| `background.png` | `bg3.bmp` |
| `ghost_1.png`–`ghost_4.png` | `ghost.bmp`, `ghost2.bmp`–`ghost4.bmp` |
| `ghost_mask_1.png`–`ghost_mask_3.png` | `GHOSTMASK01`–`GHOSTMASK03` from `grabber/files.dat` |
| `shadow_spike.png` | `shadowspike.bmp` |
| `painting_1.png`, `painting_2.png` | `painting.bmp`, `painting2.bmp` |
| `armor_1.png`, `armor_2.png` | `ewularmor1.bmp`, `ewularmor2.bmp` |
| `armor_eyes_1.png`–`armor_eyes_4.png` | `armoreyes1.bmp`–`armoreyes4.bmp` |
| `door.png` | `porta.bmp` |
| `boss_shadow_1.png`–`boss_shadow_3.png` | `Shadow01.bmp`–`Shadow03.bmp` |
| `boss_transform_1.png`–`boss_transform_12.png` | `Shadowchanging01.bmp`–`Shadowchanging12.bmp` |
| `boss_ball.png` | `ShadowBall.bmp` |
| `boss_reward_1.png`–`boss_reward_5.png` | `card01.bmp`–`card05.bmp` |

Decoded pixels for `textures03.bmp` and `bg3.bmp` were compared with the corresponding `old/2 Joguito` sources and matched. The extracted BMP intermediates are intentionally not retained in the port.
