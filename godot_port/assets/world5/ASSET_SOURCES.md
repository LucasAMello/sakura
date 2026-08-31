# World 5 asset provenance

All PNGs preserve their original dimensions and pixels. RGB `(255, 0, 255)` was converted to alpha, and the Godot scripts select nearest-neighbor filtering.

The primary loose sources are in `old/5 jogos new sakura`. The nine horizontal flame frames absent there use the canonical `old/2 Joguito` copies. Decoded pixels for every other listed BMP were compared across both folders and matched; the port was converted from the matching canonical copies in `old/2 Joguito`.

| Port assets | Original sources |
|---|---|
| `terrain.png` | `textures07.bmp` (`TEXTURES06` in the Allegro datafile) |
| `background.png` | `bg.bmp` |
| `flamethrower_horizontal.png`, `flamethrower_vertical.png` | `flamethrower.bmp`, `flamethrower2.bmp` |
| `flame_horizontal_1.png`–`flame_horizontal_9.png` | `flame01.bmp`–`flame09.bmp` |
| `flame_vertical_1.png`–`flame_vertical_9.png` | `flame11.bmp`–`flame19.bmp` |
| `flamemet_1.png`–`flamemet_4.png` | `flamemet1.bmp`–`flamemet4.bmp` |
| `falling_fire_1.png`–`falling_fire_7.png` | `fire1.bmp`–`fire7.bmp` |
| `squid_1.png`–`squid_6.png` | `ewul_squid1.bmp`–`ewul_squid6.bmp` |
| `lava_1.png`–`lava_3.png` | `lava1.bmp`–`lava3.bmp` |
| `card_holder.png`, `card_holder_broken.png` | `cardholder.bmp`, `cardholder2.bmp` |
| `boss_idle_1.png`–`boss_idle_4.png` | `scaled1.bmp`–`scaled4.bmp` |
| `boss_cut_1.png`, `boss_cut_2.png` | `scaledcut1.bmp`, `scaledcut2.bmp` |
| `boss_fire_1.png`–`boss_fire_3.png` | `scaledfire1.bmp`–`scaledfire3.bmp` |
| `boss_spray_1.png`–`boss_spray_7.png` | `sfire1.bmp`–`sfire7.bmp` |
| `boss_hadouken_1.png`–`boss_hadouken_7.png` | `hadouken.bmp`, `hadouken2.bmp`–`hadouken7.bmp` |
| `boss_slash_1.png`, `boss_slash_2.png` | `slash01.bmp`, `slash02.bmp` |
| `boss_reward_1.png`–`boss_reward_5.png` | `card01.bmp`–`card05.bmp` |
| `stage_icon.png`, `stage_icon_unlocked.png` | `stagefire.bmp`, `stagefire2.bmp` |
