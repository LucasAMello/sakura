# Stage 7 terrain collision correction

The old port SOLID_TOKENS list made the decorative upper trim solid and omitted actual floor and wall borders. Replaced it with the explicit passable tokens from the original maps.h setup for maps70–73 and map80.

Tokens 2–9, double quote, hyphen, !/@/#/$/%, and (/) / underscore are drawn but explicitly rewritten to empty token 1 in the original. They are now passable. Tokens 0 and 1 remain passable, with 0 lethal.

Actual terrain borders (including q/w/e/r/t, a/g/z/b, their uppercase equivalents, y/u/i/o/p, h/n/H/N, Y/U/I/O/P and bottom-border punctuation) now block movement. Comma, period, brackets and braces are full solid tiles in this world: the source rewrites them to q, so they must not inherit earlier worlds' slope behavior. Interior tokens that are not rewritten to 1 remain solid to Sakura, as in the original player.h map collision.

Evidence: old/2 Joguito/maps.h map70 block at 2601–2694, corresponding blocks for maps71–73, and map80 at 3860–3958. Map71–73 atlas switching and map80's hidden 2/3 atlas selectors are preserved.

Map70's spawn is restored to (100,460). The trim at Y=520 is passable; the floor starts at Y=540. The previous Y=440 workaround was based on the incorrect trim collision.

The original has separate wall rectangles for projectile collision; some interior tiles block Sakura but not original shots. The shared port terrain still treats those interior tiles as solid to both. This correction addresses the wrong terrain classifications without changing that separate interior-wall distinction.

Validation: source and map inspection plus Godot headless editor compile only; no gameplay tests.

## Reused enemies, exits, and mask spawners

Flame Mets previously retained stage5's SOURCE_EMPTY_TOKENS when reused in stage7. That list considers W/E/R and several other stage7 floor tiles empty, causing repeated ledge turns at the original, correctly floor-aligned spawn positions (for example map71's Y=407 plus height33 meets the floor at440). Stage7 now supplies its own passable tokens to both floor and ceiling Mets. Placement, sprite alignment, animation holds and movement remain unchanged.

Exit triggers now match the original type1010 initialization: map70 (9960,160), map71 (9960,240), map72 (14960,120), all size80x200. maps.h provides the positions, while sprite.h:1480 fixes width80 and height200; the direction argument is not used as trigger height. Previous port trigger X values were 40 pixels too far left and their vertical spans were oversized.

Mask spawners previously advanced the 41–50 source-tick cooldown every two physics ticks: 82–100 ticks, about1.37–1.67 seconds. They now match stage2's four-physics-tick conversion:164–200 ticks, about2.73–3.33 seconds. Random threshold sampling remains once per source tick. The original initial timer40 is retained as160 physics ticks, so the first spawn can still occur soon after activation. Position, vertical spread, destination, and left-side350px activation condition remain source-defined.

Stage7 uses the earlier worlds' enemy scripts rather than stronger enemy variants. HP, damage, attacks and drops are shared, while placement, facing and spawn parameters vary. Reused enemies now use the same one-physics-tick update cadence as their owning stages. Removed stage7's blanket two-tick enemy override, restoring green turrets to their shared120-tick (2-second) firing cooldown. All other reused enemy configure methods already selected this cadence. Stage80 explicitly retains the final boss's two-tick interval; rematch timing is unchanged.
