# World 3 asset provenance

These PNGs were converted from the release-era loose BMPs in `old/5 jogos new sakura`. Decoded pixels were checked against matching resources in the canonical `old/2 Joguito` archive before use.

The conversion preserves every source dimension and pixel, replacing only Allegro's RGB `(255, 0, 255)` mask color with alpha. Godot uses nearest-neighbor filtering for all of these resources.

- `background.png`: `bg4.bmp`
- `terrain.png`: `textures05.bmp`, corresponding to canonical `TEXTURES04`
- Wall turret, wall shot, machine, missile, orange flyer, propeller, shocker, charge, and shock-ball files: their matching loose enemy BMPs
- `door.png`, card-holder files, machine destruction frames, Thunder boss frames/projectiles, and boss reward frames: their matching loose object and boss BMPs
