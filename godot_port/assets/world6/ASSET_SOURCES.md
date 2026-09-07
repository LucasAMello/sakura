# World 6 asset provenance

The World 6 terrain is a transparency-preserving export of the canonical `TEXTURES07` bitmap embedded in `old/2 Joguito/files.dat`. The loose `textures07.bmp` files are incomplete 240x100 working sheets; the runtime datafile contains the actual 180x140 ice atlas referenced by the map loader. `background.png` and the ice enemy, hazard, holder, projectile, and block frames are direct transparency-preserving conversions from their matching BMP files in `old/5 jogos new sakura`.

The shared pumpkin and card artwork remains referenced from the already converted World 1 assets because the canonical World 6 source reuses those same sprite families.

The Icy boss assets are direct conversions of `icyshadow01.bmp`–`icyshadow04.bmp`, `icyside01.bmp`–`icyside04.bmp`, `icyup01.bmp`–`icyup03.bmp`, and `iceattack1.bmp`–`iceattack5.bmp`. The boss-room door and floor caps come from `porta2.bmp`, `icetop.bmp`, and `icetop2.bmp`. The reward frames come from `card01.bmp`–`card05.bmp`.
