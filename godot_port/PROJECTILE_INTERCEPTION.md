# Enemy projectile interception

Checked against `old/2 Joguito/sprite.h`, `scripts.h`, and `colision.h` (`sprite_colision`, starting at line 502). A successful collision animates the player's shot; only the subsequent damage whitelist damages the target. Being able to block a shot therefore does not mean an enemy attack is destructible.

| Attack | Player-shot behavior |
| --- | --- |
| Turret shot (13), boss feather (64), missile (22), shocker charge (25), Thunder lightning/beam (27/28), oyster pearl (35), turtle water jet (36), hadouken/slashes (47–49), icicles (51/52), icy boss attack (56) | Block shots and survive |
| Squid spray (45), ice needle (54) | Can be destroyed |
| Wall/machine/orange turret shots (20), shock balls (26), flamethrower flames (39/40), falling Met fire (43) | Shots pass through |
| Final boss ball/lightning (75/76) | Block fire (6), ice (7), and water splash particles; other main shots pass through |
| Final boss fire/ice attacks (77–79) | Block shots and survive |

The requested wind (2) override is preserved: it pierces enemies and enemy attacks and ends on terrain. Icicles remain indestructible. Projectile motion and firing/animation tuning are unchanged.

Standalone attacks now register for interception through StageBase, including segmented beams and jets. Default shots use sprite opacity; other weapons use attack rectangles. Shocker charging effects stop intercepting immediately when their source dies. Queued/deleted attacks and the fifth boss's impact animations no longer act as live targets.

The existing enemy damage path handles destructible spray and needles, and indestructible icicles. Water splash particles retain their separate source exception for the final boss's ball and lightning.

## Related corrections

Map70 uses the archived spawn (100,460). The earlier change to Y=440 worked around incorrectly solid trim at Y=520. Stage 7 terrain classification is now corrected: that trim is passable and the actual floor is Y=540, so the original spawn is restored.

The four world6 ice-needle PNGs are resized from the preserved originals with high-quality bilinear smoothing to 14x11, 17x17, 12x18 and 14x18 pixels (1.5x rounded to whole pixels). Comparison copies remain ice_needle_old_1.png through ice_needle_old_4.png at their original dimensions. No additional runtime scaling is applied. Collision sizes follow the PNG dimensions; spawn centers and velocities are preserved.

## Original player firing rules restored

Supersedes the preceding fixed-cooldown tuning. Main.cpp input() advances fire_key at60Hz, while enemy scripts use the separate four-tick cadence. The port now uses the original firing-cycle state machine rather than doubled intervals or an immediate-tap bypass.

| Weapon | Firing-cycle reset |
| --- | --- |
| 1 | After10 ticks with fire released, or after25 ticks with no counted shots remaining |
| 2 Wind | After50 ticks |
| 3 Shadow | When its projectile finishes |
| 4 Thunder | After35 ticks with fire released, or after50 ticks with no counted shots remaining |
| 5 Water | After40 ticks |
| 6 Fire | After70 ticks |
| 7 Ice | After50 ticks |

Only weapons1 and4 count toward the shared four-shot limit, matching player.shots in the original. Water/fire/ice no longer have an artificial one-active-projectile restriction. Completion signals identify their weapon, so unrelated impacts cannot decrement counted shots or reset Shadow's firing lock. Weapon selection cannot reset an active firing cycle. First shots remain immediate; the next shot begins on the input tick after the cycle resets.

Evidence: old/2 Joguito/Main.cpp input(), lines2198–2285 and the60Hz loop at2499–2503; scripts.h Shadow completion paths. Existing projectile movement, animation and collision tuning is unchanged.