# Weapons parity

## Implemented

- Weapon 1 retains the established port tuning: 25-tick autofire, four active shots, 9-pixel substepped motion, and 480-pixel range.
- Weapons 2–7 implement their archived projectile art, active-shot limits, terrain impact, enemy damage, animation, and selection restrictions.
- Weapons have unlimited ammunition. The archived `player.shots` value is an active-projectile counter, not an ammo reserve; firing is constrained by active-shot limits and cooldowns.
- Wind (weapon 2) deals the archived 3 damage per hit to the second boss and its clone instead of its normal 2 damage.
- Wind firing is timer-based, matching `old/2 Joguito/Main.cpp` lines 2264–2266: it does not reserve an active-shot slot or wait for the previous shot to hit. The port retains its 100-physics-tick cooldown, including repeated button presses. Wind now also uses the existing 640-pixel distance and 240-tick lifetime cleanup, so missed shots cannot persist indefinitely.
- Original 30 Hz weapon timer values are doubled on the 60 Hz player path. Fast movement remains substepped to prevent tunneling.
- Boss cards 0–5 unlock weapons 2–7. A/S cycling and keys 1–7 reject locked weapons.
- Shot sounds `tiro1` through `tiro7` are routed to the SFX bus.
- Selecting a weapon swaps Sakura to that weapon's full archived normal/firing sprite set, including idle, walk, and jump frames (`PLAYER_MOVING*` base plus variants `A`–`F`).

## Direct-hit damage audit

`old/2 Joguito/colision.h` sets ordinary enemy damage to 1 for weapon 1 (line 588), 2 for Wind (675), 3 for Shadow (767), 2 for Thunder (856), 1 for Water (944), 3 for Fire (1110), and 2 for Ice (1187). Wind previously dealt 1 and Shadow 2 in the port; both now use those source values.

Thunder deals 4 to seahorses and fish (types 30 and 32, lines 853–856). Water deals 3 to machines, shockers, both Flamemet variants, and squids (types 21, 24, 41, 42, and 45, lines 941–944). Their enemy scripts now apply those exceptions, including when reused in World 7. Boss damage remains independently defined by each boss's weapon handler; stun-only and invulnerable enemy handling is unchanged.

Water splash particles (source types 57/58, `colision.h` lines 950–1028) now hit enemies through their 14×14 collision rectangles and disappear after the first hit. Each deals 1 damage, or 3 against machines, shockers, floor Flamemets, and squids. Ceiling Flamemets take 1 from splashes, unlike the main Water shot's 3. Bosses receive their existing Water weapon damage and retain their vulnerable-state checks. Splash movement checks collision in steps of at most 2 pixels. Existing splash velocities, acceleration, two-tick update cadence, firing limits, and Ice debris behavior are unchanged; splashes do not consume additional active-shot slots.

## Projectile movement audit

The archived build (`old/2 Joguito/Makefile.win` and `Joguito.dev`) compiles `Main.cpp`. That file installs a 60 Hz timer at line 2372, but calls `run_scripts()` only when `script_timer % 4 == 1` at line 2502. Projectile movement in `scripts.h` therefore runs at 15 Hz in this source snapshot, rather than the 30 Hz assumed by the earlier port conversion. This confirms the source cadence, not the timing of the shipped executable.

Weapons 2–7 now distribute each source update's full movement across four Godot physics ticks. The movement totals include every repeated collision step in the original; reading only `x_speed` understates their speed.

| Weapon | Original displacement per script update | Previous port pixels/second | Corrected port pixels/second |
|---|---|---|---|
| Wind | 5 × 5 = 25 horizontal | 750 | 375 |
| Shadow | 5 × 4 = 20 horizontal; 3 × 4 = 12 vertical | 600 horizontal; 360 vertical | 300 horizontal; 180 vertical |
| Thunder | 5 × 4 = 20 horizontal | 600 | 300 |
| Water | 5 × 4 = 20 horizontal; initially −1 × 4 = −4 vertical | 600 horizontal; −120 vertical | 300 horizontal; −60 vertical |
| Fire | 8 × 4 = 32 horizontal | 960 | 480 |
| Ice | Two moves using the accelerating source velocity; rightward maximum 20 × 2 = 40 | Maximum 1200 | Maximum 600 |

Water's source vertical speed increases by 1 every third source update (12 Godot ticks); its converted displacement increases by 1 pixel per Godot tick at that boundary. Ice adds 0.25 to its source speed each source update, doubles every third update, and moves twice; its converted velocity updates every four Godot ticks while movement and collision continue every tick. The port retains its symmetric Ice speed cap rather than copying the archive's missing leftward cap. Wind's impact drift is likewise converted from 10 pixels per source update to 2.5 per Godot tick; Shadow's drift remains one quarter of its flight velocity.

This correction is limited to projectile motion. Weapon 1's manual tuning, player movement, firing cooldowns, animation/impact durations, lifetimes, damage, ranges, and impact-particle timing retain their current values. Existing collision substeps are preserved. This is not a claim that all weapon behavior matches the source's 15 Hz timing; those remaining timings and the broader campaign's established 30 Hz tuning were not changed.

## Manual validation required

- Confirm every weapon against enemies, bosses, terrain edges, water, and active-shot expiry. Compare damage cadence and persistent Water-shot behavior to `scripts.h`, `sprite.h`, and `colision.h`.
