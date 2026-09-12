# Stage 6 background, pits, and platforms

Verified against `old/2 Joguito` on 2026-09-10. Current user tuning takes precedence over archived behavior.

## Background

`Main.cpp:1362–1400` builds map60 and map61 backgrounds with RGB (111, 200, 239), and map62 with RGB (0, 16, 63). Map60 places bg6 at X=0/640/1280/1920, Y=0. Map61 places it at X=640/1280/1920/2560, Y=-20. Map62 has no bg6 image. `draw.h:19–24` samples both background axes at one fifth of the camera offset. The port retains those image placements and parallax.

The latest user override uses light-blue background fill RGB (111, 200, 239) for maps60 and61. Map62 and the icy rematch74 use dark blue RGB (0, 16, 63).

## Bottomless pits

`player.h:401–438` treats map token `0` as lethal when Sakura's descending feet enter it, sampling the left, middle and right of her 40-pixel-wide body. A pit therefore need not reach the bottom of the map to kill Sakura.

Map60 leaves token `0` undrawn, exposing the background. `maps.h:2326`, `2478`, and `3332` explicitly draw token `0` in maps61, 62, and 74 using the atlas tile at (120, 40), RGB (0, 16, 63), while retaining its lethal token. Decorative dark tiles `l` and `L` are passable and nonlethal; they are not interchangeable with `0`.

The port previously omitted the `0` drawing rule and supplied no lethal tokens for Stage 6. Stage 6 now registers `0` as lethal and draws it with the archived dark tile in maps61, 62 and 74. Debug god mode still bypasses pit death.

## Boss platforms

`maps.h:2526–2531` and `3372–3377` place six static type-500 blocks. `sprite.h:1333–1342` gives each a 20×20 body. The left platform spans X=3440–3500 and the right spans X=3760–3820; both tops are Y=990, placing Sakura's top at Y=910 when standing on them. Their texture variants are 1/2/1 and 2/1/2 respectively.

`player.h:374–397` checks type 500 only during downward movement, landing when the feet cross its top from above. The upward collision list omits type 500. These are one-way platforms, not full solid blocks. The port's current one-way implementation, block sizes, texture pattern, and coordinates match that behavior, including the rematch.

Validation is limited to source/asset inspection and the permitted Godot editor compile check. No gameplay test was run.

## Platforms elsewhere in the stage

The regular ice ledges use top-row tokens `2/3/4` and lower rows `5/6/7` and `8/9/-`. `maps.h:2153–2161` (repeated for maps61/62/74) creates type-20 walls only for the top row; the lower rows are drawn with type 1. `sprite.h:1–40` confirms that type 1 only draws and creates no projectile-collision wall.

However, those lower-row tokens are never replaced with `1` in the map. Sakura's movement in `player.h` checks map tokens directly, with no exemption for `5/6/7/8/9/-`. Consequently the original lower ice tiles block Sakura from the sides, above and below even though projectiles pass through them. The regular ledges are static, do not collapse, and are not the type-500 one-way boss platforms.

The port currently makes `2/3/4` solid for both Sakura and projectiles, but lists `5/6/7/8/9/-` in `STAGE6_NON_SOLID`, making the lower ice tiles passable to both. That is a confirmed player-collision discrepancy. This audit leaves that behavior unchanged pending a decision about retaining the original lower-tile collision. Decorative `o` through `Z` tiles are separate: the source explicitly changes those tokens to `1`, so their passability is correct.
