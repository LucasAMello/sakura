# Timing adjustments: enemy audit and stage-by-stage work record

Audit date: 2026-09-07. Updated: 2026-09-08. Status: **Stages 1–6 timing passes cover enemies, attacks, and stage objects, including tuned entities; user playtest pending.** See the latest work records below. Audit tables describe the pre-adjustment snapshot.

This document records the timing audit requested after discovering that the archived main loop runs enemy scripts once every four 60 Hz timer ticks. It is the starting point for future stage-by-stage adjustments and user playtests, not an instruction to change every interval to four.

Snapshot: working tree based on commit `a279080d8280bd3880d37ed71590bd5771482a0f`, including uncommitted playtest changes. Values below describe that working tree, not just the commit. Re-read each implementation before changing it. Source line numbers are audit-time navigation hints and may move.

## How to use this record in future sessions

Read sections 1–3 before changing timing, then the selected stage's inventory and sections 14–15 for the adjustment and playtest record. Review every enemy and its projectiles, including entities labeled tuned: tuning in one dimension does not establish correctness in movement, animation, attack cadence, recovery, or effects. Preserve confirmed preferences while recording the remaining discrepancies individually. Earlier adjustment records describe the scope of those passes; they do not exempt an enemy from future review.

The key distinction from the discussion is that **60 Hz timer/input does not mean 60 Hz enemy scripts**. In the archived build, scripts are gated to 15 Hz. In Godot, interval two really does mean every other physics tick, or 30 updates/sec. Thus unchanged source counters advance twice as fast at interval two. Running at interval one is compatible with source pace only after converting the relevant quantities, including acceleration and animation—not just movement speed.

Related discussion to preserve alongside the timing work:

- Stage 4 foreground and portal layering are separate rendering fixes. `scripts/world4/stage4.gd` places terrain at z-index 24 and foreground terrain at 25, above the portal front at 22. The entry effect is behind Sakura at `player.z_index - 1`; preserve the corrected portal closing appearance when playtesting oyster motion.
- Pumpkin's nonlethal response is implemented by its overridden `take_projectile_hit()` in `scripts/world1/pumpkin.gd`: it starts a stun and selects a stun frame instead of applying the ordinary enemy damage/death path. Its stun duration is a timing question; changing the stun into damage or death is a separate behavior change.
- The recent oyster/pearl conversion made updates smoother at 60 Hz while preserving the previous 30 Hz pace. Section 7 records the remaining source-pace difference, rotation, launch timing, and trajectory concerns.
- Stage 5 flame burst is fast because source frame counters execute at 30 instead of 15 updates/sec, not because interval two is being ignored. See section 8 for burst duration and the separate flamethrower firing cycle.

This document is the detailed planning and evidence record. User playtesting and stage acceptance remain pending; creating or extending it does not certify gameplay or authorize a campaign-wide timing rewrite.

## 1. Corrected source baseline

The archived build selects `Main.cpp` (`old/2 Joguito/Makefile.win:29–30`; also `Joguito.dev:33`). In that file:

```cpp
// Main.cpp:2372
install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));

// Main.cpp:2499–2505, relevant structure
while (speed_counter > 0) {
    input();
    script_timer++;
    if (script_timer % 4 == 1) { run_scripts(); /* ... */ }
    speed_counter--;
    /* ... */
}
draw();
```

Thus the source schedules:

| Clock | Source behavior |
| --- | --- |
| Timer/input | 60 ticks per second |
| `run_scripts()` | Once every fourth timer tick: nominally **15 updates per second** |
| Rendering | Separate `draw()` call outside the timer catch-up loop; do not assume 15, 30, or 60 draws/sec |

`Main3.cpp` also contains the every-fourth-tick gate, but the build references `Main.cpp`. The local source is evidence of intended scheduling; it does not establish that every distributed executable was built from precisely this revision or maintained its nominal rate under load. The source's local `unsigned script_timer` also lacks an initializer; that is a separate source defect, not a reason to invent a different intended cadence.

### Conflict with existing documentation

At audit time, `AGENTS.md`, `README.md`, and earlier parity notes describe the original as 30 Hz and prescribe interval two for source values. **That historical explanation conflicts with the main loop above.** The existing interval-two implementation is real, but its claim of source-equivalent timing is not generally correct.

Those older documents were not rewritten during this audit. For future timing work, use the verified clock of the specific behavior, the current implementation, and the user's confirmed tuning. Do not silently restore a 30 Hz assumption from an older document. Also do not discard unrelated preservation rules or manual tuning because the cadence explanation was wrong.

### Draw-driven exceptions

Some original code mutates state during rendering:

| Behavior | Original location and clock |
| --- | --- |
| Seahorse rotation, including final-stage variant | `draw.h:356–393`: adds 24 rotation units per draw |
| Thunder boss beam, type 28 | `draw.h:311` onward: draw-count timer; frames/removal at 5/9/13 |
| Final-boss lightning, type 76 | `draw.h:327` onward: draw-count timer; frames/removal at 5/9/13 |
| Armor eyes/opening visual state | `draw.h:525` onward: changes `animation_state` per draw |
| Lava frames | `draw.h:439` onward: increments timer per draw; frame changes every 15 draws |
| Final target-ball texture animation | `draw.h:1116` onward: every six draws |
| Final left/right fire texture animation | `draw.h:1127–1143`: every eight/twelve draws |

A texture selected in `draw()` is not automatically draw-timed: inspect where its driving counter changes. For example, orange propellers use a script-incremented counter, and squid swimming frames use the script timer. Conversely, a draw-driven effect cannot be assigned a reliable speed ratio from `run_scripts()` alone.

## 2. How to interpret this audit

- **Faster 2×** means twice the real-time rate, or half the duration, compared with the nominal archived source schedule.
- **Matches / approximately matches** applies only to the listed dimensions. It does not certify collision, state ordering, coordinates, damage, or all animation details.
- **Mixed** means movement, animation, attack timing, or recovery have different ratios.
- **Uncertain** means a fixed ratio is not supported, commonly because the source uses draw counts.
- **Tuned** identifies existing adjustments that must not be overwritten automatically. A source difference is a suspect for discussion, not proof the preferred gameplay is wrong.
- Ratios are code-derived estimates. First-update phase, inclusive comparisons, immediate state transitions, collision, player position, and visibility can shift measured durations.

The inventory covers every active enemy controller, the seven bosses, reused instances, enemy projectile variants, spawners, and relevant hazards. Additional destructible objects and effects appear separately. Player weapons, pickups, portals, doors, HUD, menus, music, and cinematics are not comprehensively audited here.

All paths below are relative to `godot_port/` unless prefixed with `old/`; `old/` refers to the sibling archive directory in the repository.

## 3. Current scheduling and conversion rules

`scripts/shared/enemy_base.gd` increments `update_interval_counter` on active physics ticks and calls `_update_enemy()` at the configured interval. `scripts/shared/stage_base.gd::_spawn_enemy()` assigns the stage's interval after adding/configuring the shared setup. Individual controllers can override that assignment or change it later.

| Path | Audit-time cadence |
| --- | --- |
| Stage 1 / shared default | Interval 1: 60 enemy updates/sec |
| Stages 2–6 and Stage 7 | Interval 2: 30 enemy updates/sec by default |
| Third boss | Overrides to interval 1; generally fourfold durations and quarter-step dash motion |
| Fourth boss | Overrides to interval 4: 15 updates/sec |
| Oyster upper/lower | `configure()` calls `set_update_interval(1)` after stage spawning |
| Oyster pearl | Standalone physics processing at 60 Hz; does not inherit the stage interval |
| Orange attack/body animation | Extra gate inside `_update_enemy()`: 15 updates/sec under interval 2 |
| Orange bobbing/propeller | Outside its extra gate: 30 updates/sec |
| Turret bullets / bird feathers | Standalone 60 Hz processors, including when their owner is reused |
| Other standalone projectiles | Inspect their own phase counters; stage intervals do not propagate automatically |

Contact checks and hit-flash processing in the shared enemy base are outside the `_update_enemy()` interval gate. Changing an enemy interval does not automatically change damage-check frequency, shared player immunity, or hit-flash duration.

### Arithmetic for future adjustments

For a source displacement `D` per script update, source speed is `15 × D` pixels/sec. Include every source collision substep when calculating `D`.

For a source duration of `T` script updates, nominal duration is `T / 15` seconds. At 60 Hz with interval `I`, effective update rate is `60 / I`, before any additional internal gate.

Candidate representations of the same source-paced behavior:

| Representation | Duration count | Displacement/update | Acceleration/update² |
| --- | --- | --- | --- |
| Interval 4, retain source steps | `T` | `D` | source acceleration |
| Interval 2, smooth source pace | `2T` | `D/2` | source acceleration / 4 |
| Interval 1, smooth source pace | `4T` | `D/4` | source acceleration / 16 |

These formulas assume the same integration convention. They are not a mechanical patch recipe. Preserve event order, launch delay, one-time sprite-alignment offsets, thresholds, and collision substeps. Discrete ballistic trajectories can need an initial-velocity correction to agree at the old sample points. Do not divide a one-time coordinate offset as though it were a velocity. Do not multiply a duration that has already been converted.

Changing from an existing 30 Hz implementation to 60 Hz while doubling timers and halving movement preserves that existing pace; it does not by itself restore the archived 15 Hz pace. This is what happened with the recent oyster conversion.

## 4. Stage 1 — maps 10–14

Source anchors: `scripts.h:282` (red ball), `319` (spring), `364` (turret), `373` (turret bullet), `385` (Pirikito), `1308` (pumpkin/type 55), `1387` (feather), `2108` (bird boss/type 1001). Initial velocities: `sprite.h:138`, `178`, and the corresponding type blocks.

| Entity / implementation | Finding | Evidence and dimensions |
| --- | --- | --- |
| Red ball — `scripts/world1/red_ball.gd` | **Movement 2× faster; animation approximately matches. Tuned.** | Current `2 × 60 = 120 px/sec`; source `0.8 × 5 × 15 = 60`. Current frame hold `8/60` matches typical source hold `2/15`. Source resets at timer 14, producing a slightly different cycle boundary; current eight equally held entries give 64 physics ticks. |
| Happy spring — `happy_spring.gd` | **About 1.33× faster. Tuned.** | `TIMING_SCALE = 3` gives 20 source steps/sec rather than 15. Jump displacement is divided by three, with original acceleration progression distributed across those steps. Waits and jump timing share the mismatch. |
| Green turret — `green_turret.gd` | **Firing matches. Tuned.** | Current `120/60 = 2 sec`; source `30/15 = 2 sec`. Static body. Do not slow this firing interval merely because other enemies are fast. |
| Turret projectile — `enemy_projectile.gd` | **Travel 2× faster; lifetime halved.** | Current `10 × 60 = 600 px/sec`; source `4 × 5 × 15 = 300`. Current lifetime `40/60 ≈ 0.67 sec`; source `20/15 ≈ 1.33 sec`. Current collision substeps divide its displacement; they do not multiply its speed. |
| Pirikito — `pirikito.gd` | **Cycle/animation 4× faster; movement separately tuned.** | Source timers and acceleration sequence run every 60 Hz update. `MOVEMENT_SCALE = 0.75` reduces excursion; speed at corresponding sequence steps is about 3× source, while the cycle is four times faster. This is not an unchanged trajectory with one uniform time scale. |
| Pumpkin — `pumpkin.gd` | **Mixed. Tuned.** | Patrol `3 × 60 = 180` versus source `10 × 15 = 150 px/sec` (1.2×). Chase `10 × 60 = 600` versus `20 × 15 = 300` (2×). Two-update frame holds at 60 versus 15 Hz make animation 4× faster. Stun `180/60 = 3 sec` versus source `30/15 = 2 sec`: recovery is slower. Activation geometry also differs; do not attribute every chase difference to time. |
| Bird boss — `first_boss.gd` | **Mixed, mostly faster despite historical slowing. Tuned.** | Entry/rise/landing and wing holds generally use a threefold conversion, about 1.33× source pace. Dash `10 × 60 = 600` versus `39 × 15 = 585 px/sec` is nearly matched. Current volley separation `24/60 = 0.4 sec`; source `8/15 ≈ 0.53 sec`. Full attack duration and first-volley offsets are not a uniform exact multiple. |
| Bird feathers — `boss_feather.gd` | **About 1.33× faster. Tuned.** | Current two `20/3` substeps at 60 Hz yield `800 px/sec`. Source two `20` substeps at 15 Hz yield `600`. |

Future playtest focus: red-ball walking versus animation, spring apex and complete cycle, turret repeat versus bullet travel, Pirikito excursion and flap rhythm, pumpkin patrol/chase/stun separately, and every bird-boss phase. Preserve the preferred player pace as the comparison context.

## 5. Stage 2 — maps 20–23

Source anchors: `scripts.h:417` (ghost/type 15), `482/521` (mask spawners/types 16/61), `492/530` (masks/types 17/62), `1365` (armor/type 60), `2338/2439` (boss and clone/types 1002/1003). Boss initial axis velocities are ±15 in `sprite.h:1389–1419`.

| Entity / implementation | Finding | Evidence and dimensions |
| --- | --- | --- |
| Ghost — `scripts/world2/ghost.gd` | **Approximately 2× faster.** | Original acceleration, caps, frame timer, and alpha changes run at 30 rather than 15 updates/sec. Same-speed caps per update mean doubled real-time travel; acceleration unfolds over half the time. |
| Ghost masks, both directions — `ghost_mask.gd` | **Mixed, faster.** | Stage 2 uses horizontal speed 3: `90` versus original `5 × 15 = 75 px/sec` (1.2×). Animation and fade increments run about 2× faster. Oscillation also omits the source's endpoint hold, so bobbing is not an exact 2× replica. Fading movement uses 5 per update, independently of the normal 3. |
| Mask spawners — `stage2.gd::_update_mask_spawners()` | **Near source, somewhat faster; different startup.** | Current fixed repeat `80/30 = 2.67 sec`; source uses randomized 41–50 tick thresholds, nominal range `2.73–3.33 sec`. The threshold is sampled during updates, not simply chosen once as a uniform repeat delay. Current initial timer 40 also changes first-spawn latency. |
| Armor — `stage2_armor.gd` | **Opening/drop logic 2× faster; eyes uncertain.** | Source milestones 12 and 18 retained at 30 Hz. Original eye/opening visual state changes per draw; current visual progression is tied to enemy updates. |
| Shadow spikes — `shadow_spike.gd` | **No motion or animation speed suspect.** | Static hazard; contact timing depends on player immunity and checks outside this audit. |
| Shadow boss — `second_boss.gd` | **Movement nearly matches; transformation/split faster.** | Current axis velocity `8 × 30 = 240` versus source `15 × 15 = 225 px/sec` (about 1.07×). Transformation and split timer values run at 30 Hz, about 2× faster. Split activation geometry also differs, so time-to-split is not purely a clock comparison. |
| Shadow clone — `shadow_clone.gd` | **Movement nearly matches; emergence faster.** | Same 240 versus 225 axis speed once active. Initial drift retains 3 per update at 30 rather than 15 Hz; its 30-update activation delay is halved. |

Future playtest focus: ghost pursuit/settling, mask spawn frequency separately from horizontal speed and bobbing, armor eye/opening timing, boss transformation, bounce speed, split delay, and clone emergence.

## 6. Stage 3 — maps 30–32

Source anchors: `scripts.h:573` (wall turret/type 19), `591` (shot/type 20), `606/621` (machine/missile/types 21/22), `630` (orange/type 23), `697/709/724` (shocker/charge/ball/types 24–26), `739` (lightning/type 27), `2471` (boss/type 1004). Beam/type 28 uses `draw.h:311` onward.

| Entity / implementation | Finding | Evidence and dimensions |
| --- | --- | --- |
| Wall turret, all orientations — `scripts/world3/wall_turret.gd` | **Firing 2× faster.** | Source 50-tick firing cycle retained at 30 Hz. |
| Machine — `machine.gd` | **Attack cycle 2× faster.** | Same 50-tick selection/fire cycle at twice the cadence. |
| Orange — `orange_enemy.gd` | **Attacks/body animation match approximately; bobbing and propeller 2× faster.** | Extra `attack_update_phase` gate reduces attacks/body frames to 15 Hz. Bobbing and propeller run before the gate at 30 Hz. Source propeller counter is script-driven even though drawn separately. |
| Shocker, all orientations — `shocker.gd` | **Approximately 2× faster.** | Opening, tick-16 charge spawn, closing, and tick-60 reset retain source counts. |
| Wall/orange/machine shots — `world3_projectile.gd`, `WALL_SHOT` | **2× faster travel; lifetime halved.** | Source directional vectors and 30-tick lifetime retained under the projectile's own interval-two gate. |
| Machine missile — `MISSILE` | **Approximately 2× faster.** | Source −8 to −22 velocity change, acceleration milestone, and lifetime run at twice the cadence. Update-order differences around launch should be checked separately. |
| Shocker charge — `SHOCK_CHARGE` | **2× faster animation/charge.** | Same 16-update charge at 30 Hz. |
| Shock balls, including boss-spawned balls — `SHOCK_BALL` | **2× faster.** | Same 10-pixel displacement and 60-update lifetime at 30 Hz. |
| Thunder boss — `third_boss.gd` | **Core sequence approximately matches. Tuned.** | Forces interval one. Main durations are fourfold source counts and dash movement is divided by four. For example, source wait 40 becomes 160 physics ticks. Animation-frame choices and boundary ordering include existing tuning. |
| Boss lightning appearance — `BOSS_LIGHTNING` | **2× faster.** | Four-update source appearance now runs at 30 Hz. |
| Boss beam — `BOSS_BEAM` | **Uncertain. Tuned.** | Current nine physics ticks, three per texture. Source lifetime is 13 draw calls. Boss scheduling and beam visual lifetime are separate comparisons. |

Future playtest focus: orange bob/propeller without disturbing its already slower attack gate, turret/machine firing plus shots, shocker charge versus ball travel, boss dash/teleport schedule, lightning appearance, and beam visibility separately from damage timing.

## 7. Stage 4 — maps 40–42

Source anchors: `scripts.h:746` (Resetti/type 29), `774/784` (spawner/seahorse/types 31/30), `814` (fish/type 32), `917/967` (oyster/pearl/types 33/35), `995` (water jet/type 36), `2612` (turtle/type 1005). Lower oyster/type 34 is static. Seahorse rotation lives in `draw.h`.

| Entity / implementation | Finding | Evidence and dimensions |
| --- | --- | --- |
| Resetti — `scripts/world4/resetti.gd` | **Mixed, faster.** | Emergence displacement reaches full height in about half the source time. Current retraction begins at `26/30 ≈ 0.87 sec`, source `16/15 ≈ 1.07 sec`; extended current waits partly compensate. Current emergence range extends beyond the time needed to reach its height cap. |
| Seahorse spawner — `seahorse_spawner.gd` | **Approximately 2× faster.** | Same 90-update cooldown at 30 Hz: about 3 versus 6 sec. |
| Seahorse — `seahorse.gd` | **Movement/state sequence 2× faster; rotation uncertain.** | Source 17-pixel rise, six-update hold, dash delay, and 25-pixel dash retained at 30 Hz. Rotation adds source 24 units per current logic update, but the original added them per draw. |
| Fish, all four variants — `fish.gd` | **Approximately 2× faster.** | Original acceleration, speed caps, bobbing, and swimming timers run at 30 Hz. |
| Oyster upper, both directions — `oyster.gd` | **Approximately 2× faster. Recent 60 Hz conversion.** | Forces interval one; durations doubled and opening/closing movement/rotation split into half-steps. This preserves the previous 30 Hz-equivalent pace. Source opening completion 7/15 sec versus current 14/60 sec; cooldown 40/15 versus 80/60 sec. |
| Oyster lower — `oyster_lower.gd` | **No motion/animation suspect.** | Static component; configuration now sets interval one. |
| Pearl, every launch branch — `oyster_pearl.gd` | **Approximately 2× faster trajectory timing. Recent conversion.** | Current horizontal speeds 5/7.5/10 at 60 Hz give 300/450/600 px/sec; source 10/15/20 at 15 Hz gives 150/225/300. Source initial vertical speeds −14/−10/−6 and gravity +2 were converted for the previous 30 Hz pace. Current values are half-speed minus 0.25 initially, then gravity +0.5 per physics tick. Launch first moves at tick 11 after ten waiting ticks, versus source's sixth script update; phase is not an exact doubled sample boundary. |
| Turtle boss — `fourth_boss.gd` | **Core timing approximately matches.** | Overrides `set_update_interval()` to force four. Source state timers and 32-pixel dash displacement run at 15 Hz. |
| Turtle jet, normal and trailing — `water_shot.gd` | **Approximately 2× faster travel, expansion, and animation.** | Stage spawn gives jets interval two; they do not inherit the boss's interval four. Source 32-pixel travel and expansion steps run at 30 Hz. |

Future playtest focus: Resetti exposure duration, seahorse spawn/rise/dash/rotation separately, fish pursuit and idle movement, oyster opening versus pearl delay and arc at every distance/height branch, and turtle jets relative to the already 15 Hz boss. Preserve the portal/foreground fixes; they are unrelated to timing.

## 8. Stage 5 — maps 50–53

Source anchors: `scripts.h:1013/1021` (flamethrowers/types 37/38), `1029/1042` (bursts/types 39/40), `1055/1070` (Flamemets/types 41/42), `1086` (falling fire/type 43), `1103` (squid/type 45), `1179/1207/1234/1238` (boss projectiles/types 46–49), `2803` (boss/type 1006). Lava/type 44 uses `draw.h:439` onward.

| Entity / implementation | Finding | Evidence and dimensions |
| --- | --- | --- |
| Horizontal flamethrower — `scripts/world5/flamethrower.gd` | **2× faster cycle.** | Source fire/reset milestones 45/76 retained at 30 Hz. |
| Vertical flamethrower — same controller | **2× faster cycle.** | Same timing as horizontal variant; initial map offsets also use local update counts. |
| Horizontal burst — `flame_burst.gd` | **2× faster animation; half duration.** | Cycles frames 1–7 every update, closing frames at 27/28, expiry at 29. Current `29/30 ≈ 0.97 sec`; source `29/15 ≈ 1.93 sec`. Interval two is working; it is simply the wrong source-equivalence assumption. |
| Vertical burst — same controller | **2× faster animation; half duration.** | Same schedule as horizontal burst. |
| Ground Flamemet — `flamemet.gd` | **2× faster movement/animation.** | Current `2 × 30 = 60 px/sec`, source 30; two-update frame holds halve their real-time duration. |
| Ceiling Flamemet — same controller | **2× faster movement, animation, and fire drops.** | Also retains source 70-update drop cycle. |
| Falling fire — `falling_fire.gd` | **2× faster fall/animation.** | Current `8 × 30 = 240 px/sec`, source 120. Impact sequence also runs twice as fast. |
| Squid — `squid.gd` | **Approximately 2× faster.** | Source rise/fall acceleration, turnaround frame sequence, and recovery wait at 30 Hz. Preserve recent clipping and state-order corrections. |
| Scaled fire boss — `fifth_boss.gd` | **Approximately 2× faster.** | Idle animation, 50-update attack selection, spray every six updates, Hadouken windup, and slash sequence retain source counts. |
| Spray — `boss_projectile.gd`, `SPRAY` | **Approximately 2× faster.** | Source horizontal velocities, gravity increments, animation, and impact counts at 30 Hz. |
| Hadouken — `HADOUKEN` | **2× faster.** | Current `40 × 30 = 1200 px/sec`, source 600. Flight and impact frames also faster. |
| Straight slash — `SLASH_STRAIGHT` | **2× faster.** | Current `20 × 30 = 600 px/sec`, source 300. |
| Rising slash — `SLASH_RISING` | **2× faster.** | Source displacement (−17, −8) at twice the cadence. |
| Lava strips — `lava_strip.gd` | **Animation uncertain; static hazard.** | Current 15-physics-tick holds; source 15-draw holds. Do not label this 2× faster based on the stage interval: it has its own 60 Hz processor. |

Future playtest focus: flamethrower startup offsets, full repeat period, burst lifetime versus texture flicker, both orientations, ceiling drops, squid apex/turnaround, and each boss attack with its projectile. Slowing only the burst animation would not address the firing-cycle mismatch.

## 9. Stage 6 — maps 60–62

Source anchors: `scripts.h:1246` (Ice Met/type 50), `1261/1281` (icicles/types 51/52), `1301` (needles/type 54), `1308` (pumpkin/type 55), `1328` (icy attacks/type 56), `2884` (boss/type 1007). Static spikes/type 53 are initialized in `sprite.h`.

| Entity / implementation | Finding | Evidence and dimensions |
| --- | --- | --- |
| Ice Met — `scripts/world6/ice_met.gd` | **2× faster movement/animation.** | Same 2-pixel movement and two-update frame holds at 30 Hz. |
| Icicles, both sizes — `icicle.gd` | **Approximately 2× faster fall sequence.** | Initial speed 2 and acceleration +4 retained at twice the cadence. Current clamp at 39 differs slightly from source's `if speed < 39` increment, which can overshoot. Five-update collision delay also halves. |
| Needles, all four variants/both directions — `ice_needle.gd` | **2× faster.** | Original velocity vectors at 30 Hz. |
| Ice pumpkin — `ice_pumpkin.gd` | **Mixed, faster. Tuned movement.** | Uses Stage 1 patrol/chase constants multiplied by two: 6/20 per update. Patrol 180 versus source 150 px/sec (1.2×); chase 600 versus 300 (2×). Animation 2× faster. Stun `30/30 = 1 sec`, source `30/15 = 2 sec`. Shared constants make later Stage 1 edits affect this enemy. |
| Ice spikes — `ice_spike.gd` | **No motion/animation speed suspect.** | Static hazard. |
| Icy boss — `icy_boss.gd` | **Approximately 2× faster.** | Source state counts, 20-pixel intro movement, and 30-pixel dash/rise steps at 30 Hz. Preserve current wall clipping, pose offsets, and phase fixes. |
| Icy attack, five variants/both directions — `icy_attack.gd` | **2× faster charge/travel.** | Same 13-update charge, alpha increment, and source velocity vectors at 30 Hz. |

Future playtest focus: Ice Met movement and death needles, icicle acceleration/collision grace period, pumpkin chase/stun, every boss altitude/side phase, charge visibility, and projectile travel.

## 10. Stage 7 reuse — maps 70–73

Implementation: `scripts/world7/stage7.gd`, especially `_spawn_reused_enemy()`, `_update_ghost_mask_spawners()`, and `_on_seahorse_requested()`. Source variants/types remain identifiable through `maps.h`, `sprite.h`, and `scripts.h`.

| Reused entity | Stage 7 finding |
| --- | --- |
| Red ball/type 10 | **Movement matches:** 2 × 30 = 60 px/sec. **Animation roughly 2× slower:** eight-update holds now last 8/30 sec, rather than source's typical 2/15 sec. Source cycle reset differs slightly as described under Stage 1. |
| Green turret/type 12 | **Firing 2× slower:** 120/30 = 4 sec versus source 2 sec. Its separately processed bullet still travels **2× faster**. |
| Pirikito/type 14 | **Cycle/animation 2× faster**, corresponding movement about **1.5× faster** with the 0.75 displacement scale. |
| Ghost/type 15 | Same approximately 2× faster finding as Stage 2. |
| Ghost masks/types 17/62 family | Stage 7 supplies speed 5, not Stage 2's 3. Horizontal movement is **2× faster**; animation, bobbing, and fading remain faster. |
| Ghost-mask spawners | Retain source randomized 41–50 threshold at 30 Hz: **approximately 2× faster**, unlike Stage 2's fixed threshold 80. |
| Machine/type 21 | Same 2× faster attacks/projectiles as Stage 3. |
| Orange/type 23 | Same matching attack/body cadence and 2× faster bobbing/propeller as Stage 3. |
| Oyster/type 33, lower/type 34, pearl/type 35 | Same Stage 4 findings; configure overrides interval to one, pearl has its own processor. Lower shell static. |
| Ground/ceiling Flamemet/types 41/42 | Same 2× faster findings, including falling fire/type 43. |
| Ice Met/type 50 and needles/type 54 | Same 2× faster findings as Stage 6. |
| Ice pumpkin/type 55 | Same mixed findings as Stage 6. |
| Seahorse spawner/type 71 and seahorse/type 72 | Reuse World 4 implementations with a different water-surface limit. Source 90-update spawning, rise, holds, and dash imply approximately **2× faster** current behavior. Rotation uncertain because source is draw-driven. |

Do not treat an earlier-stage fix as complete until its Stage 7 instance has been reviewed. An explicit per-enemy interval or a change to shared constants can change these results.

## 11. Six boss rematches

The wrappers inherit their owning stage controller rather than the Stage 7 controller. At audit time they do not supply independent interval overrides.

| Map / wrapper | Boss finding carried into rematch |
| --- | --- |
| 74 — `scripts/world7/rematch_world6.gd` | Icy: approximately 2× faster; icy projectiles also faster |
| 75 — `rematch_world1.gd` | Bird: mixed/tuned; feathers about 1.33× faster |
| 76 — `rematch_world2.gd` | Shadow: near-matching movement, faster transformation/split; clone findings carry over |
| 77 — `rematch_world3.gd` | Thunder: core sequence approximately matched; projectile/effect exceptions carry over |
| 78 — `rematch_world4.gd` | Turtle: core interval-four timing approximately matched; jets still interval two/faster |
| 79 — `rematch_world5.gd` | Scaled fire boss and projectiles approximately 2× faster |

The wrappers' entry sequences, camera setup, and victory routing are not certified by these boss-controller comparisons. Validate the rematch context when its owning stage is adjusted and again during the final-stage pass.

## 12. Final boss — map 80

Implementation: `scripts/world7/final_boss.gd`, `final_boss_projectile.gd`, and spawning in `stage80.gd`. Source boss/type 1008 starts at `scripts.h:3359`; target/type 75 at `1502`, fire/types 77/78 at `1521/1673`, ice/type 79 at `1825`. Lightning/type 76 and several texture animations mutate in `draw.h`.

| Entity / attack | Finding | Evidence and dimensions |
| --- | --- | --- |
| Final boss, seven attack selections | **Approximately 2× faster.** | Source attack counts, spawn intervals, fades, and reappearance waits at 30 Hz. Includes target, left/right lightning, left/right fire, and left/right ice patterns. |
| Targeted ball/type 75 | **Appearance/lifetime/fades 2× faster; texture animation uncertain.** | Source six-update appearance and subsequent fade run at twice the cadence. Source texture frame counter advances every six draws; current every six projectile updates. |
| Lightning/type 76 | **Uncertain; potentially slower visual.** | Current lifetime 13/30 ≈ 0.43 sec. Original is 13 draw calls, not 13 script updates. At an assumed 60 draws/sec the current visual would last twice as long, but source draw rate has not been established. |
| Left-orbit fire/type 77 | **Motion/fades/settling approximately 2× faster; texture animation uncertain.** | Same script-timed orbital steps, including every-other-update motion, at 30 Hz. Texture loop originally advances every eight draws. |
| Right-orbit fire/type 78 | **Same motion suspicion; texture animation uncertain.** | Mirrored source path; original texture loop advances every twelve draws. |
| Ice/type 79, six variants/both directions | **2× faster charge/travel.** | Five-update charge and original velocity vectors at 30 Hz. |

Future playtest focus: appearance/vulnerability windows, intervals between targeted attacks, every lightning lane, fire orbit versus texture animation, settling lifetime, ice charge and all angles. Treat boss attack scheduling, individual effect lifetime, and damage timing as separate measurements.

## 13. Other destructible objects and effects

| Object / implementation | Finding and evidence |
| --- | --- |
| Card holders, Worlds 1/3/5 — respective `card_holder.gd` | **Destruction lifetime approximately 4× faster:** 20 physics ticks versus source type 65's 20 script updates (`scripts.h:1397`). Card display/spin behavior is separate and has existing tuning. |
| World 6 card holder — `scripts/world6/card_holder.gd` | **Destruction lifetime approximately 2× faster:** interval-two wrapper around World 1 implementation. |
| Sand mound — `scripts/world4/sand_mound.gd` | **Breaking animation 2× faster:** source type 66 milestones 3/6/9 (`scripts.h:1414`) retained at 30 Hz. |
| Ice card holder — `scripts/world6/ice_holder.gd` | **Melting approximately 2× faster:** type 67 alpha changes −18/+20 retained at 30 Hz (`scripts.h:1422`). |
| Ordinary enemy death — `scripts/shared/enemy_death_effect.gd` | **Faster, different frame holds:** current total 15/60 = 0.25 sec; source type 666 timer-5 removal is approximately 0.33–0.40 sec depending on initial/update counting. Not a uniform frame-by-frame ratio. |
| Turret death — `scripts/world1/turret_death_effect.gd` | Same duration suspicion as ordinary death; compare source type 667 (`scripts.h:1990`). |
| Turret-shot explosion — `scripts/world1/turret_shot_explosion.gd` | **Approximately 2× faster despite previous slowing.** Current changes at 2/6/10 physics ticks; source type 113 at 1/3/5 script counts (`scripts.h:1957`), with initial-count boundary differences. |
| Machine death — `scripts/world3/machine_death_effect.gd` | **Approximately 2× faster:** interval-two processor retains source type 112 sequence (`scripts.h:1968`). |
| Falling boss-room blocks — `scripts/world1/boss_room_block.gd` | **Fall about 1.33× faster, tuned:** current constant is 4 px/physics tick (240 px/sec); source types 2000/2001 use 12 px/script update (180 px/sec). Explosion spacing 16/60 equals source 4/15. Older notes say fall speed 3; current implementation says 4. Reverify before editing. |
| Guillotine/type 18 | **Inactive/missing comparison, not a speed verdict.** Behavior exists at `scripts.h:559`, but no corresponding active port controller or canonical spawn was found in the audited `Main.cpp`/`maps.h`. Do not add it merely to resolve timing. |
| Painting — `scripts/world2/stage2_painting.gd` | Not an enemy. Reveal currently follows player-speed-based physics updates. Not assigned a source speed verdict in this enemy audit; revisit only if the Stage 2 presentation pass needs it. |

Standalone death effects can ignore their owner's interval. Boss defeat sequences and shared hit flashes also need separate review if they become part of the stage adjustment request. Their full timing is not certified by the enemy tables.

## 14. Stage-by-stage workflow

No unchecked item below authorizes a bulk rewrite. Future work should follow the user's selected stage and playtest feedback.

1. Read this document, the current controller, its actual spawn path, and the original initialization/update/collision/draw blocks. Record any differences from this snapshot.
2. Identify the clock for every dimension: movement, acceleration, body frames, auxiliary rotation, firing, projectile delay/travel/lifetime, recovery, and effects. Check shared constants and nested update gates.
3. Decide the desired behavior for the selected enemy with the user's feedback: source pace, preserved tuning, or a specific adjustment. Record the choice and rationale; do not silently equate source parity with preferred gameplay.
4. Choose a cadence and convert only values that need conversion. Smooth 60 Hz movement is compatible with a 15 Hz-equivalent pace. Preserve collision substeps and one-time pose offsets.
5. Make focused changes for the selected scope. Keep unrelated player tuning, map coordinates, drops, damage, layer fixes, and assets stable unless requested.
6. Use the permitted Godot parser/editor load after GDScript changes as a compile check. Do not create or run automated gameplay tests or test scenes under the existing repository instructions. Gameplay acceptance comes from the user's playtest feedback; the checklist below is for that future work, not evidence it has happened.
7. Review the selected entity in relevant normal maps, boss phase(s), Stage 7 reuse, and rematch. Compare both direction variants and all projectile launch branches where present.
8. Update the work record with actual values, compile result, user feedback, and remaining uncertainty. Mark accepted only after the user has confirmed the gameplay result.

### Suggested observations to record during user playtesting

- Seconds per complete idle/attack/recovery cycle; seconds between shots and between spawns.
- Travel time over a known distance; patrol versus chase speed.
- Jump/arc apex, range, flight duration, launch delay, and collision grace period.
- Frame hold time and full animation cycle; auxiliary propeller/rotation separately.
- Stun duration, vulnerability windows, and whether player immunity masks timing differences.
- Behavior when paused, when entering/exiting an active area, and after checkpoint revival.
- Differences between owning stage, reused Stage 7 instances, and rematch.

For draw-driven source behavior, record the unresolved source draw rate and the chosen visual target. Do not present an assumed 60 FPS reference as an observed original measurement.

## 15. Progress tracker

All entries start as **audited suspects; adjustment and playtest pending**. A stage can intentionally retain a source difference after playtesting.

| Stage | Maps | Adjustment | User playtest | Reuse/rematch review | Accepted |
| --- | --- | --- | --- | --- | --- |
| 1 | 10–14 | All enemy/attack dimensions reviewed; timing corrections implemented | Pending | Shared Pirikito, bullets/effects and map75 boss updated; playtest pending | No |
| 2 | 20–23 | 60 Hz timing conversion implemented, including tuned entities | Pending | Reused classes and map76 inspected; playtest pending | No |
| 3 | 30–32 | 60 Hz timing conversion implemented, including tuned entities | Pending | Reused classes and map77 inspected; playtest pending | No |
| 4 | 40–42 | Converted; see latest work record | User playtest pending | Reused classes and map78 inherit conversion; playtest pending | No |
| 5 | 50–53 | Converted; see latest work record | User playtest pending | Reused classes and map79 inherit conversion; playtest pending | No |
| 6 | 60–62 | Converted; see latest work record | User playtest pending | Reused classes and map74 inherit conversion; playtest pending | No |
| 7 reuse/hub | 70–73 | Pending | Pending | Cross-stage cadence review pending | No |
| Final boss | 80 | Pending | Pending | All seven attack selections pending | No |

### Per-entity work record template

Copy this section for each future adjustment, retaining the original audit row as history.

```text
Date / stage / maps:
Enemy, variant, projectile, or effect:
Current revision and relevant working-tree changes:
Port file / function / actual update path:
Original type / initialization / scripts / draw / collision references:
Source clock and uncertainty:
Before: interval, internal gates, speed, acceleration, timers, frame holds:
Desired result and user direction:
After: interval, internal gates, speed, acceleration, timers, frame holds:
One-time offsets and collision substeps preserved:
Shared constants / Stage 7 / rematch affected:
Compile check result:
User playtest observations:
Accepted tuning or remaining issues:
Status: pending / changed-awaiting-playtest / revise / accepted:
```

### Audit and adjustment history

| Date | Work | Result |
| --- | --- | --- |
| 2026-09-07 | Read-only enemy timing audit following main-loop discovery | Source-clock mismatch and per-entity exceptions documented; no gameplay changes or tests |
| 2026-09-07 | Created this adjustment record at the user's request | Documentation only; all future adjustment/playtest items remain pending |
| 2026-09-07 | Stage 1: preserve documented tuned enemies; correct untuned turret bullet at 60 Hz | Speed 10 → 5 px/physics tick; lifetime 40 → 80 physics ticks; user playtest pending |

### Stage 1 adjustment record — 2026-09-07

- User direction: start with Stage 1; match source timing at 60 Hz, except enemies already tuned.
- Scope interpretation: preserve the entire behavior of entities marked tuned in the Stage 1 audit: red ball, happy spring, green turret firing, Pirikito, pumpkin, first boss, and boss feathers. Their listed source differences remain intentional exclusions in this pass, not silently accepted source parity.
- Stage 1 already uses interval one through the shared default; its active enemy logic runs on every physics tick. Its turret bullet and feathers also have standalone 60 Hz processors. No lower-frequency gate needed removal in this stage. The shared interval mechanism remains for later stages until their values are converted; removing it globally now would accelerate unconverted enemies outside the selected scope.
- Changed file: `scripts/world1/enemy_projectile.gd`.
- Source: type 13, `sprite.h:178` onward initializes speed 4 and lifetime 20; `scripts.h:373` onward applies `speed × 5` once per 15 Hz script update and decrements lifetime once per update.
- Before: 10 px/physics tick × 60 = 600 px/sec; lifetime 40/60 ≈ 0.67 sec.
- After: 5 px/physics tick × 60 = 300 px/sec; lifetime 80/60 ≈ 1.33 sec. This equals source 20 px/update × 15 = 300 px/sec and 20/15 ≈ 1.33 sec.
- Unobstructed travel distance remains 400 px. Four collision substeps remain; each is now 1.25 px instead of 2.5 px. The sprite has no flight animation to rescale.
- Preserved: damage, spawn offsets, directions, terrain/player collision checks, tuned turret firing interval, and tuned shot-explosion animation.
- Reuse: Stage 7 green turrets instantiate this same standalone projectile, so their bullets receive the correction automatically. Stage 7 turret firing remains outside this pass. Map75 bird boss and feathers are unchanged.
- Adjacent death effects, card holders, pickups, and falling blocks were not included in this enemy/attack pass; their separate audit rows remain pending.
- Compile check: Godot 4.7.2 headless editor load completed with exit code 0 and no script/parser errors. Sandbox errors concerned editor/user directories, certificate access, and saving editor settings. `git diff --check` reported no whitespace errors. No gameplay tests were run.
- User playtest: pending. Check both firing directions, perceived bullet travel, collision-triggered explosions, unchanged turret firing cadence, and Stage 7 reuse when available.
- Status: changed-awaiting-playtest; no stage acceptance claimed.

### Stage 1 comprehensive timing pass — 2026-09-07

This supersedes the earlier whole-entity exclusions. The user explicitly requested review of tuned enemies too. Existing preferred movement values were evaluated separately from animation, waits, recovery, and projectile clocks; they were not used to exempt an entire controller.

| Entity / dimension | Current result |
| --- | --- |
| Red ball | Still 2 px/physics tick as explicitly tuned. Frame holds remain eight ticks except the final frame, now four: the source resets its counter at 14 to −1, making a 15-source-tick / 60-physics-tick loop, rather than the previous 64-tick loop. |
| Happy spring | Scale 3 → 4. Each source displacement is split over four physics ticks; acceleration changes retain the original before/after-motion ordering. Source tick 40 starts after 39 complete source steps. The 59 → 79 counter jump now occurs after all four movement substeps. Full cycle is 316 physics ticks (79/15 sec), with source jump extent retained. Initial map phase offsets are scaled by four. |
| Green turret | Firing remains 120 physics ticks / 2 sec, already equal to 30 source updates. Static body has no animation or travel clock to convert. |
| Turret projectile | 5 px/physics tick, 80-tick lifetime, four collision substeps: 300 px/sec and 1⅓ sec, preserving 400 px maximum travel. |
| Pirikito | Cycle 76 → 304 physics ticks; all frame events and initial map offsets use the fourfold clock. Original velocity increments occur once per source step, with displacement divided across all four physics ticks. Deliberately tuned 75% excursion remains. Configuration forces interval one, including Stage 7 reuse, to avoid applying its world interval on top of this conversion. |
| Pumpkin | Frame holds 2 → 8 physics ticks. Stun 180 → 120 ticks / 2 sec. Stun-frame selection uses source-equivalent animation phase. Explicitly tuned patrol/chase speeds 3/10 px per physics tick remain; its nonlethal hit behavior and activation geometry remain. Ice pumpkin's shared speed constants consequently stay unchanged. |
| Bird boss | Entry 150 → 200 ticks, hover 120 → 160, rise and landing 75 → 100, dash delay 30 → 40. Vertical movement becomes 1.25/−3/2.5 px per physics tick, preserving phase travel distances and one-time alignment offsets. Wing and attack holds become eight ticks; air animation includes the original hover/rise/left-landing counter offsets. |
| Bird attack schedule | Standing windup remains 48 ticks. Volleys now occur at 80/112/144/176, and the attack phase ends at 200. Both sides retain their alternating single/double patterns and spawn offsets. |
| Bird dash and feathers | Evaluated separately: retain explicitly tuned 10 px/physics-tick dash with spatial turnaround bounds, single dash sprite, and two feather collision substeps of 20/3 px. Feathers have no animation, launch delay, acceleration, or fixed lifetime to convert. These movement preferences intentionally differ from source speed; the rest of the boss is no longer excluded because of them. |
| Turret-shot explosion | Frame transitions now at 8/16 ticks, removal at 24. Source counter starts at zero and is tested before increment, so thresholds 1/3/5 occur on updates 2/4/6. This corrects the previously overlooked initial-count boundary as well as the clock. |
| Enemy/turret death | Stage 1 uses eight-tick frame holds and 24-tick total duration for the same zero-initialized, test-before-increment source sequence. Ordinary shared death effects gain a configurable hold; other worlds retain their existing five-tick default. |

All Stage 1 enemies still execute `_update_enemy()` every active physics tick. Spring and Pirikito distribute movement over those ticks; source-step acceleration milestones do not gate their entire update. Contact checks, pause behavior, player timing, damage, drops, and terrain remain unchanged. Card holders and boss-room falling blocks are stage objects with separate audit rows, not enemy controllers changed by this pass.

Reuse implications: Stage 7 shares red-ball animation, Pirikito, turret projectiles and their explosions; its red-ball/turret owner interval remains part of the later Stage 7 pass. Map75 inherits the updated boss controller. Ordinary death-effect duration is selected by Stage 1, so unrelated worlds do not receive that change. These paths were inspected in code; no gameplay acceptance is claimed.

Validation: Godot 4.7.2 headless editor compile check completed after the final script changes with exit code 0 and no script/parser errors. The sandbox reported editor/user-directory, certificate-store, and editor-settings save errors. `git diff --check` passed. No gameplay tests were run. Implementation status: changed-awaiting-playtest.

Playtest all five regular enemy types in maps 10–14 and the bird boss on both sides. Pay special attention to the spring's return to its base, Pirikito's turnaround and reset, pumpkin stun recovery, red-ball final frame, projectile impacts, boss vulnerability onset, wing phase continuity, and volley spacing. Record any further desired movement changes explicitly rather than inferring acceptance from the retained values above.

### Stage 1 remaining movement differences — 2026-09-07

The user requested correcting the retained differences in the comparison table too. This supersedes the movement exceptions in the preceding records and older tuning guidance.

| Dimension | Before this follow-up | Current / original target |
| --- | --- | --- |
| Red-ball speed | 120 px/sec | 60 px/sec: 1 px per physics tick |
| Pumpkin patrol | 180 px/sec | 150 px/sec: 2.5 px per physics tick |
| Pumpkin chase | 600 px/sec | 300 px/sec: 5 px per physics tick |
| Pirikito excursion | 75% of source | 100%; movement scale 1.0, fourfold cycle duration retained |
| Bird dash speed | 600 px/sec | 585 px/sec: 9.75 px per physics tick |
| Bird feather speed | 800 px/sec | 600 px/sec: two 5-pixel collision substeps per physics tick |

Red-ball configuration now selects interval one, including Stage 7 reuse, so the converted movement is not halved again by that stage's interval. Map75 inherits the boss/feather correction. Ice pumpkin previously referenced Stage 1's speed constants; its existing 6/20 px per update are now local values, preserving that later-stage behavior for its own timing pass. Boss dash turnaround positions remain spatially controlled; matching speed does not certify the original full dash-state duration or geometry. Gameplay playtest remains pending.

### Stage 1 objects and effects — 2026-09-07

The user requested the remaining Stage 1 object timing corrections, superseding the earlier card, recovery, block, and meter tuning exceptions.

| Object / dimension | Before this pass | Current source-paced result |
| --- | --- | --- |
| Loose/holder-released card initial fall | 10 px/physics tick, 600 px/sec | 2.5 px/physics tick, 150 px/sec; source type 69 starts at 10 px/script update |
| Card bobbing and deceleration | Motion gate every four physics ticks; speed changes every eight | Source motion distributed over four physics substeps; low-speed movement occurs every fourth source step; speed changes every 16 physics ticks, after movement; reversal at +2/−2 source units |
| Card spin | 120-physics-tick loop | 160 ticks / 2.667 sec; source timer modulo 40 at 15 Hz |
| Holder card spin | 80-physics-tick loop | 160 ticks / 2.667 sec |
| Broken holder | 20 ticks, blink every tick | 80 ticks / 1.333 sec, blink every four ticks |
| Card collection fade | 13 ticks, alpha −20/tick | 36 ticks / 0.6 sec; smooth fade over nine source steps at −30 from 255. Ownership is still recorded immediately on contact to preserve the replay fix. |
| Small/medium recovery and extra life fall | 7.5 px/tick, 450 px/sec | 3.75 px/tick, 225 px/sec; source types 200–202 use 3×5 px/script step |
| Falling boss-room blocks | 4 px/tick, removal at y560 | 3 px/tick, 180 px/sec, removal at source y540 |
| Block explosions | First burst immediately on falling | First burst after one four-tick movement step, then every 16 ticks; source first falls at timer 11 and emits at timer 12. Existing stagger `(1 + 2×index)×4` and 120-tick boss wait already match source delays. |
| Ordinary enemy/turret death | Previously corrected | Retained eight ticks per frame, 24 total / 0.4 sec; confirmed zero-start, test-before-increment source counters 1/3/5. Direction fixes retained. |
| Boss-defeat explosions | Generic enemy-death visual, 15 ticks; repeated every seven ticks | Uses the source type-113 explosion, 24 ticks; repeated every 28 ticks with initial zero-counter phase accounted for |
| Boss reward homing/spin | 5 px/tick; two-tick frame holds; arrival check every 16 | 1.25 px/tick / 75 px/sec; eight-tick holds; arrival check every 64 ticks |
| Boss reward fade | Nine ticks | 36 ticks / 0.6 sec |
| Boss meter fill | One point every two ticks | One point every four ticks, matching one per source script step |

Evidence: `scripts.h` types 65, 69, 200–202, 113, 666/667, 2000/2001, 1666; initialization in `sprite.h`; map14 events 75–105 and 106–136 in `Main.cpp`. Card frame selection in `draw.h:157–201` uses script counters, so it is not independently draw-timed. Boss white-screen fades use `draw.h:1487` onward and retain their existing presentation clock; the explicit original 500 ms white hold remains 30 physics ticks. Door/portal presentation and player scripted walking are not mechanically rescaled by this object pass because their original draw/event clocks differ.

Other-stage isolation: recovery fall speed is selected through a stage hook, with the prior default retained outside Stage 1. World 6 inherits the holder class, so its existing animation/break scales are explicitly retained for its own pass. Boss rematch 75 inherits Stage 1 changes, while boss rewards remain suppressed there. Gameplay playtest is pending, particularly card floor contact/bobbing, block order and disappearance, pickups, and the complete boss reward/departure sequence.

Object-pass validation: Godot 4.7.2 editor/parser check completed with exit code 0 and no script errors; the known sandbox editor-directory/certificate/settings errors remain. Diff whitespace check passed. No gameplay tests were run. The final block removal threshold was checked directly against source y540.

### Card floor-arrival correction — 2026-09-07

User playtest found the first holder's card hovering before reaching the floor. Card collision only checks terrain, so the nearby spring cannot stop it. Applying the bobbing velocity cycle during initial descent reduced its speed to zero and then reversed it while airborne. Falling cards now retain their 2.5 px/physics-tick descent until terrain contact; only then does the bobbing velocity cycle start. Cards configured to hover immediately still do so. This intentionally supersedes the previous source-style deceleration during the initial fall in favor of the user's floor-arrival requirement. Immediate ownership recording, collected-card suppression, animation, fade, and collision substeps remain. Compile check completed with no script errors; gameplay confirmation pending.

### Shared boss explosion sprites — 2026-09-08

At the user's request, the shared boss-explosion helper now uses the type-113 turret-shot explosion frames instead of ordinary enemy-death frames. The Stage 1 duplicate helper was removed. This covers all elemental bosses, Shadow's clones, rematches, and the final boss through their existing helper calls. Each effect is centered on the supplied spawn point and uses the already-converted 8/16/24-tick frame transitions/lifetime. Sound and layering remain unchanged. Boss-specific burst schedules are unchanged and remain subject to their stage timing passes. Visual gameplay confirmation is pending.

### Stages 2 and 3 — 60 Hz conversion, 2026-09-08

User direction: adjust both stages, including tuned behavior, toward the archived original while updating every physics tick for smoothness. This supersedes the previous interval-two guidance and tuned exceptions for these stages. The inventory tables above remain the pre-conversion snapshot.

Both stage controllers now select enemy interval one. Converted reusable enemy classes also select or enforce interval one so Stage 7's default interval cannot slow them a second time. Projectile, reward, card, and effect processors no longer return early on alternate ticks. Movement is distributed across physics ticks; discrete frame/attack events retain source timing. Contact and collision substeps remain active at 60 Hz.

| Stage 2 entity | Current implementation and source evidence |
| --- | --- |
| Ghost | Source-unit velocity capped at ±5, applied at one quarter per physics tick: 75 px/sec per axis. Acceleration increments divided by four (0.075/0.1 in source-velocity units); actual displacement acceleration is divided by sixteen. Braking is 0.05 per tick, fade −2.5 alpha units/tick, animation changes every 20 physics ticks. Pursuit is evaluated each tick for smooth response. `scripts.h` type 15. |
| Ghost mask | Normal and fading horizontal travel 1.25 px/tick / 75 px/sec; source vertical steps divided over four ticks. Restored the source's extra endpoint step before reversing at ±2. Animation events at 4/16/28/40 ticks, reset to −8; fade 160 → 0 over 32 ticks. Types 17/62. |
| Mask spawners | Timer starts at zero. Every four eligible physics ticks, re-sample the original 41–50 source-step threshold. This restores the original per-update random comparison rather than choosing one fixed 80-update repeat. Types 16/61. |
| Armor | Drop at 48 ticks, opening logic finishes at 72. Eyes and opening flicker were originally draw-driven: retain original 6/12/18/24 eye-count progression and four-count opening holds on a chosen 60 Hz presentation clock. This is a declared draw-rate assumption, not a measured original duration. Type 60 and `draw.h:525` onward. |
| Static spikes / painting | Spikes have no motion or animation clock. Painting already updates reveal width each physics tick, linked to player pace; retained as a presentation behavior rather than assigning a false source-script ratio. |
| Shadow boss | Axis speed 8 per 30 Hz update → 3.75 per 60 Hz tick, matching original 15×15 = 225 px/sec. Shadow cycle, transformation events, split, and meter use fourfold timing with test-before-increment boundaries preserved. Transform rise distributed at 1.25 px/tick; pose offsets stay instantaneous. Split trigger restored to source y200–300; clone at split tick 28, resume at 148, resuming right/up as source. Type 1002. |
| Shadow clone | Axis speed 3.75 px/tick; emergence drift 0.75 for 96 ticks, four-tick initial pause, activation after 124 ticks. Source side-dependent drift/velocity sign restored at x5660 (map limit 5960 − 300). Type 1003. |

| Stage 3 entity | Current implementation and source evidence |
| --- | --- |
| Wall turret / machine | Test-before-increment source timer 50 first fires after 204 physics ticks from zero, then every 200 ticks. Map turret phase offsets multiply by four. Types 19/21. |
| Orange | Removed the nested attack gate; all update work runs every tick. Bob cycle 88 physics ticks, displacements ±0.25/0.5 per tick; source excursion and endpoint holds retained. Propeller uses four-tick holds. Body/shot cycle retains source timer-zero/reset behavior: initial shot at tick 36, repeats every 64. Type 23. |
| Shocker | Frame opening at source ticks 10–13, charge at 16, closing 31–34, reset 60: multiplied by four to 40–52, 64, 124–136, 240 physics ticks. Initial phase offsets scale too. Type 24. |
| Wall/orange/machine shots | Direction vectors divided by four; 120-tick lifetime. Wall-shot ending frames at 8 and 16 ticks. Collision substeps preserved. Types 20/120. |
| Missile | Four-tick initial motion delay; −2 px/tick initially, −5.5 starting tick 41; 120-tick total flight. Source checks acceleration before increment, after ten completed source steps. Collision/expiry now creates the original type-113 explosion rather than silently disappearing. Type 22. |
| Charge / shock balls | Charge frame cadence four ticks, emits at 64; corrected frame-index phase. Ball travels 2.5 px/tick / 150 px/sec, expires at 240 ticks. Ball texture cycling is draw-driven in `draw.h:304–309`, so uses one frame per chosen 60 Hz presentation tick; it is not script-paced. Types 25/26. |
| Lightning / beam | Lightning appearance offsets at 4/8/12, expires at 16; offsets remain one-time sprite alignment changes. Beam uses original draw-count milestones 5/9/13 on the chosen 60 Hz presentation clock, replacing the tuned 3/6/9. Instantaneous beam strike/collision behavior retained. Types 27/28. |
| Thunder boss | Existing source-paced attack events retained after source comparison. Corrected pre-increment state lengths: flicker 164, crouch 24, each dash including final hold 36, inter-dash wait 28 ticks. Restored dash frames 4 → 5 → 4 and source body widths 96/130/96. Corrected takeoff flicker phase; two 100-pixel ascent steps distributed as eight 25-pixel physics movements while keeping sprite pose offsets. High/low attack timers already used fourfold source counts. Type 1004. |
| Thunder intro / meter | Walking 1.25 px/tick over 160 ticks; lightning at 228, flash events 240/244/248/252, meter at 272–388 every four ticks, fight begins at 392. HUD uses the same clock. Map77's skipped walking offset changed 40 → 80 to retain its intended 100-pixel remaining walk. `Main.cpp` event 5 and rematch event. |

Shared object work in these two stages: cards use the corrected Stage 1 implementation with each world's existing textures (160-tick spin, 150 px/sec initial fall, terrain-arrival-before-bobbing correction, 36-tick pickup fade, immediate ownership recording). Stage 3 holder breaks over 80 ticks with four-tick blinking. Boss rewards home at 1.25 px/tick, hold frames eight ticks, check arrival at 64-tick cycle boundaries and fade over 36 ticks. Recovery/extra-life falls at 3.75 px/tick via stage overrides. Ordinary and machine death effects last 24 ticks with eight-tick holds. Boss-defeat repeated bursts use 28-tick periods with source initial-counter phase; shared type-113 explosion visuals remain.

Stage 2 victory now advances every tick, matching Stage 1/3's selected 60 Hz draw-derived white fade and explicit 500 ms white hold. Door/portal presentation and the painting retain their existing presentation behavior; the archive's draw-loop pacing is not proven, so the 15 Hz conversion is not mechanically applied to those visuals. Player control/weapon tuning remains outside this stage enemy/object pass.

Reuse inspected: Stage 7 Ghost, mask, machine, Orange and projectiles use converted classes; Stage 7 spawner scheduling itself remains for the Stage 7 pass. Rematches 76/77 inherit the owning stage behavior, and map77's intro offset was updated. Other worlds' recovery and ordinary death defaults remain unchanged.

User playtest pending: every map in both stages, both mask directions/endpoints, pursuit/braking, armor near/far/open/drop, Shadow transformation and split on either side, clone emergence, all turret orientations and machine attack choices, Orange shot direction/bobbing/propeller, every shocker orientation, charge/ball/beam impact and expiration, both Thunder attack patterns, card floor arrival, boss rewards, and rematches. Draw-paced effects need visual feedback. Code-derived timing is not a claim of runtime gameplay acceptance.

Stages 2/3 validation: Godot 4.7.2 headless editor/parser load completed after the final script changes with exit code 0 and no script/parser errors. Known sandbox messages concerned editor/user directories, certificate-store access, and editor-settings saving. `git diff --check` passed. A final processor audit confirmed interval one for both stages and converted reusable enemies, and no remaining alternate-tick processor gates in their projectile, reward, card, or effect paths. No gameplay tests were created or run, in accordance with repository instructions. Implementation is ready for user playtesting; visual acceptance remains pending.

### Stage 4 — 60 Hz conversion, 2026-09-08

User direction: continue the source-fidelity timing pass in Stage 4, including tuned values, with updates every physics tick. This supersedes its previous interval-two guidance. The original script clock is 15 Hz; the turtle already used that pace through interval four, while its independently spawned jets did not. All Stage 4 enemy classes now configure interval one; the turtle enforces it. Standalone spawner, sand, bubble, splash, card, reward, and victory paths no longer have alternate-tick processor gates.

| Entity / effect | Before this pass | Current source-paced implementation |
| --- | --- | --- |
| Resetti | 30 Hz emergence; tuned retreat at counter 26–30, reset from 34 | Rise over 20 physics ticks, 34 pixels total (6 then four 7-pixel source steps, distributed). Retreat over ticks 61–80 (source steps 16–20); reset eligible from 96. Restored source side-specific distance thresholds. |
| Seahorse spawner | 90 cooldown updates at 30 Hz, then a new activation update | 360 physics ticks for the 90-step cooldown, plus the following four-tick activation step: 364 ticks between eligible repeated spawns. Stored countdown is 363 because the next activation consumes the final tick. First activation remains responsive every tick. |
| Seahorse | 17 px/update rise and 25 px/update dash at 30 Hz | Rise 4.25 px/tick (255 px/sec), initial 51-pixel emergence over 12 ticks. Height checks finish on four-tick boundaries. Hold 24 ticks; dash pose at tick 4, movement begins at 37 and completes its first 25-pixel source step at 40. Dash speed 6.25 px/tick / 375 px/sec. |
| Seahorse rotation | 24 Allegro angle units per 30 Hz logic update | Source `draw.h:356–371` increments by 24 per draw. Uses 24 units per chosen 60 Hz presentation tick after the dash pose appears. Original draw rate is unknown; this is a presentation assumption requiring visual feedback, not verified wall-clock parity. |
| Fish, all four variants | Source velocities, acceleration, animation and bobbing at 30 Hz | Source-unit speed caps ±5, applied at one quarter: 75 px/sec per axis. Acceleration 0.075/0.1 per tick, braking 0.05; applied acceleration is source acceleration divided by sixteen. Swim frames hold eight ticks; idle bob cycle 80 ticks with source ±1/±2 displacement spread across four ticks. Alert lasts 24 ticks (type 501 starts at five and removes on its sixth update). |
| Oyster, both directions | Smooth 60 Hz motion preserving the old 30 Hz pace | Pearl emission at opening tick 4; shell rotation/motion distributed over ticks 13–24, open pose at 28. Open hold 40 ticks; closing motion at 5–16, cooldown begins at 20 and lasts 160. Rotational increments ±2.75 source angle units/tick; full 33-unit excursion retained. Texture-alignment offsets and rotation center remain unscaled. Lower shell remains static. |
| Pearl, all distance/height branches | 300/450/600 px/sec; gravity 0.5 px/tick² | Horizontal 150/225/300 px/sec (2.5/3.75/5 per tick). Wait 20 ticks; first motion at 21. Vertical launch is source −14/−10/−6 divided by four, minus 0.1875; gravity 0.125 per tick. The subtraction makes each four-tick sum equal the corresponding source displacement, including the first step. Example: first four vertical movements sum to −14, then the next four sum to −12. Retained unit collision substeps and both facing branches. Removed the port-only fixed lifetime; collision and world bounds end flight. |
| Turtle boss | Interval four, already source-paced but moving 32 pixels at a time | Interval one; all discrete source timers multiplied by four. Dash moves 8 px/tick / 480 px/sec starting at tick 29, completing its first source movement at 32. Idle 120 ticks; normal shot phase 108, rapid shot 60; emission at 24. Recovery 52/28 ticks; chained chooser consumes four ticks. Pose offsets remain instantaneous. Both directions and the original asymmetric rapid-recovery branch retained. |
| Turtle intro and meter | Meter at 24–82 every two ticks, overlapping the roar | Roar frames at 8/12/40/44; meter at 44–160 every four ticks, fight begins at 164. HUD uses the same schedule. Source boss type 1005 sets event 51 after its eleventh intro step; `Main.cpp` event 7 then fills 30 points and unlocks. Existing door traversal presentation remains. |
| Water jets, normal/trailing and both directions | 32-pixel movement/growth at 30 Hz | 8 px/tick movement/growth; final 16-pixel source extension distributed over ticks 17–20. Expansion completes at 20, with 11 middle segments. Fractional segment widths crop the last middle piece, keeping expansion smooth. Collision retreat distributes 32-pixel shrinkage as 8 per tick. Tip/end frames hold eight ticks, middle frames four. Unit terrain/player collision paths retained. |
| Bubbles | Emitted every 320 physics ticks; rise 6 pixels every other tick | Emitted every 160 input/physics ticks, as in `Main.cpp:2351`; rise 1.5 px/tick / 90 px/sec from type 70's −6 per script step. These are distinct source clocks. |
| Splash / sand mound | Frame changes at 3/5/7 and 3/6/9 alternate-tick updates | Splash frames at 12/20, removal at 28; sand frames at 12/24, removal at 36. Source types 404 and 66 increment before checking. |
| Cards / recovery / death | World-local card override retained older fast rates; recovery/death used shared defaults | Cards inherit the corrected Stage 1 160-tick spin, terrain-arrival fall, 36-tick fade and immediate ownership, retaining Stage 4's initial bob direction. Recovery falls at 3.75 px/tick; ordinary death holds eight ticks per frame, 24 total. Stage overrides keep other-world defaults unchanged. |
| Boss reward / victory | Homing 5 pixels every other tick; fast reward animation/fade; victory on alternate ticks | Reward 1.25 px/tick, eight-tick frames, arrival check every 64 ticks, 36-tick fade. Removed non-source reward mirroring. Initial triple burst at 24, repeated bursts every 28 at phase 16; shared type-113 explosion visuals retained. Victory fade now uses the same chosen 60 Hz presentation clock as Stages 1–3, with a 30-tick/500 ms white hold. |
| Water surface | Three frames with 20-tick holds at 60 Hz | Hold duration retained on the chosen draw-derived clock; restored source order 3 → 2 → 1. `draw.h` advances `aguaa` once per draw. Original draw rate remains unknown. |

Source comparison covered `scripts.h` types 29–36, 66, 69/70, 404, 501, 1005 and the shared reward/death paths; their initialization, collision, and draw branches were checked where clocks or movement depend on them. Continuous fish pursuit and fractional collision interception intentionally evaluate more often than the original 15 Hz sampling, so matching source rates does not imply identical discrete trajectories for a moving player. Water-jet collision timing can likewise land between original source steps after smoothing.

Reuse: Stage 7's seahorse spawners, seahorses, oysters and pearls use these converted implementations without an extra interval. Map78 inherits the converted turtle, meter, jets and victory path. Player/weapon tuning, doors, portals, terrain, and corrected Stage 4 foreground/portal z-order remain outside this timing change.

User playtest pending: maps 40–42, Resetti exposure/rearming, all fish variants, seahorse rise/hold/dash and perceived rotation, both oyster facings at all pearl range/height branches, normal and trailing jets against both arena walls, both turtle phases/directions, sand cards and replay suppression, underwater bubbles/splashes, meter/roar alignment, boss reward/departure, and Stage 7/map78 reuse. Draw-derived rotation, water animation, and white fades need visual feedback.

Stage 4 validation: final Godot 4.7.2 headless editor/parser load completed with exit code 0 and no script/parser errors. Sandbox messages were limited to editor/user-directory access, certificate-store access, and saving editor settings. Final `git diff --check` passed. The processor audit confirmed interval one for every Stage 4 enemy and no remaining alternate-tick gates in its standalone effects/spawner/reward paths. No gameplay tests were created or run; user playtest acceptance is pending.

### Stage 5 — 60 Hz conversion, 2026-09-08

User direction: continue the same source-fidelity timing pass in Stage 5. Stage controller now selects interval one, all regular enemy/projectile configurations select interval one, and the boss enforces interval one for rematch reuse. Physics still runs at 60 Hz. Source script durations multiply by four; displacement is distributed across each four-tick source step. Earlier Stage 5 inventory rows are the pre-conversion snapshot, not the current rates.

| Entity / dimension | Before this pass | Current implementation / source evidence |
| --- | --- | --- |
| Flamethrowers, horizontal/vertical | Source counters 45/76 at 30 Hz | First emission from zero after 184 physics ticks: source pre-increment timer 45 fires on update 46. Reset at 308, with repeat interval 304 / 5.067 sec. Initial map phase offsets multiply by four. The internal reset is 3 before the final increment to 4, preserving the source reset-to-zero-then-increment order. Types 37/38. |
| Flame bursts, all directions | 29 updates at 30 Hz, about 0.967 sec | 116 ticks / 1.933 sec. Seven-frame active cycle uses four-tick source holds; initial frame stays visible through the first source update. Closing frames at 108/112, removal at 116. Flame sound repeats at 4/32/60/88, matching source modulo-seven events. Types 39/40. |
| Ground/ceiling Flamemet | 2 px/update at 30 Hz; two-update frames | 0.5 px/tick / 30 px/sec, eight-tick frame holds. Ceiling drops every 280 ticks / 4.667 sec, including the original initial counter boundary. Fractional movement now uses a remainder loop, so 0.5-pixel steps are not truncated to zero. Source ledge-token checks, snaps, facing and ceiling alignment remain. Types 41/42. |
| Falling fire | 8 px/update at 30 Hz, one-update flight frames | 2 px/tick / 120 px/sec, four-tick flight frames. Floor-impact first frame remains immediate; following frames appear at 4/8, removal at 12 after impact. Source type 43 checks impact counters 0/1/2 before increment. |
| Squid rise | Source velocity recurrence applied at 30 Hz | Velocity retains source units, incremented at each four-tick step start; one quarter is applied on every physics tick. Rise reaches velocity −4 after 56 ticks and transitions only after completing that step. Source total rise is 217 px. Clipping is recalculated every tick. Type 45. |
| Squid turnaround/fall/reset | Turnaround 5 updates, recovery 10 at 30 Hz | Turnaround events at 4/8/12/16/20 with original one-time pose offsets and vertical flip. Source fall executes its first 1-pixel step in the same update as the fifth turnaround event; this is retained at tick 20, with timer set to 4 before later fall substeps. Subsequent fall motion is quartered, source +1/+2/+4 velocity milestones retained, home reset at velocity 44 after the full source step. Total source fall displacement is 352 px before the original home-position reset; recovery lasts 40 ticks. Swim frames follow the fourfold script counter even though selected in source draw code. |
| Fire boss idle/intro | Source timers at interval two | Interval one. Idle frames every 12 ticks; first attack selection at 200. Intro poses at 8/16/24/80/88/96, roar at 16. Source type 1006. |
| Boss spray phase | Nine shots every six 30 Hz updates; phase 61 updates | Nine shots at 24/48/72/96/120/144/168/192/216, ending at 244. Windup and closing frames multiply by four. Return-to-idle counter is 12 (source 3), so subsequent idle waits are 188 ticks, not 200. |
| Boss Hadouken/slash | Source durations at 30 Hz | Hadouken emission at 80, return at 120. Slash pose offset at 4, both slash projectiles at 32, return and pose restoration at 60. All one-time offsets remain unscaled. |
| Spray projectile | Source random speeds and alternating gravity at 30 Hz | Horizontal speed 4–6.75 px/tick / 240–405 px/sec. Initial random frame/timer phase scales by four. Source-unit vertical speed increments by one at the original odd source phases; displacement is divided by four every tick, preserving the four-tick trajectory samples. Flight frames hold four ticks. Impact frame events at 4/12/20, removal at 28 (source pre-increment checks 0/2/4/6). Type 46. |
| Hadouken projectile | 40 px/update at 30 Hz / 1200 px/sec | 10 px/tick / 600 px/sec using two 5-pixel sweeps, each retaining unit collision substeps. Flight frames hold eight ticks. Impact alignment and first frame at 4, following frames at 8/12/16/20, removal at 24, preserving source pre-increment checks 0–5. Type 47. |
| Straight/rising slashes | (−20, 0) / (−17, −8) per 30 Hz update | (−5, 0) / (−4.25, −2) per physics tick: 300 px/sec straight; rising components −255/−120 px/sec. Unit collision substeps remain. Types 48/49. |
| Boss entry/meter | Walk/hold/camera timing based on doubled source counts; meter every two ticks | Scripted horizontal alignment 1 px/tick over up to 128 ticks, hold through 132, camera pan through 212. Existing scripted fall acceleration and player controller remain unchanged as player tuning. After roar starts, meter fills at 96–212 every four ticks, fight at 216; HUD matches. Source event 9 receives event 61 from the boss's 24th intro update, fills 30 points, then unlocks. |
| Cards/holders | Loose cards already inherit the Stage 4 conversion; holders still fast | Retained inherited 160-tick spin, 150 px/sec terrain-arrival fall, immediate ownership, replay suppression and 36-tick fade. Holder spin now 160, break 80, blink every four ticks. Original direction and asset choices retained. |
| Recovery/death/reward | Recovery/death defaults; reward homing 5 px/tick and fast animation/fade | Stage-local recovery 3.75 px/tick, ordinary death frames held eight ticks / 24 total. Reward homing 1.25 px/tick, frames eight ticks, arrival check every 64, fade 36. Other-world defaults unchanged. |
| Victory/lava | Victory bursts every seven ticks; lava already independent of stage interval | Burst initial triple at 24, repeats every 28 at phase 16; shared type-113 effects retained. White fades and 30-tick white hold retain the chosen 60 Hz presentation clock. Lava remains 15-tick frame holds: original `draw.h:439` advances once per draw, so this remains a declared 60 Hz draw-rate assumption rather than verified source wall-clock parity. |

Evidence: canonical `scripts.h:1013–1243`, `2803–2899`; corresponding initialization and relevant collision/draw paths; `Main.cpp` event 9. Motion and collision now run every tick, while source acceleration changes and discrete animation events remain on their required milestones. Source trajectory samples for free movement are preserved; terrain/player collision can occur between original steps because collision is evaluated more often.

Reuse checked: Stage 7 ground/ceiling Flamemets and falling fire configure interval one after spawn; map79 inherits the boss, projectiles, intro/meter and victory changes. Existing projectile `Kind` argument typing, squid clipping/state order, player weapon tuning, damage, drops, terrain and scene routing remain intact.

User playtest pending: maps 50–53, flamethrower map offsets/repeat cycle in all orientations, burst closing frames, Flamemet ledges and ceiling drops, falling-fire impacts, squid apex/flip/surface clipping/home reset, all three boss attacks and projectile impacts, intro fall/camera/meter, card holders/replay, reward/departure, and Stage 7/map79 reuse. No stage acceptance is claimed by this source comparison.

Stage 5 validation: final Godot 4.7.2 headless editor/parser load completed with exit code 0 and no script/parser errors after the entry timing change. The known sandbox editor-directory, certificate-store and editor-settings messages remain. `git diff --check` passed. Final inspection confirmed interval one for every Stage 5 enemy/projectile path and the stage controller, plus inherited converted card processing. No gameplay tests were created or run; implementation is ready for the user's stage playtest.

### Stage 6 — 60 Hz conversion, 2026-09-08

User direction: continue the source-fidelity timing pass in Stage 6. Stage controller now selects interval one. Ice Met, icicle, needle, pumpkin and icy-attack configurations select interval one; the boss enforces it, including its rematch. Static spikes inherit the stage cadence and have no movement or animation to rescale. Card-holder and ice-holder processors no longer skip alternate physics ticks.

| Entity / dimension | Before this pass | Current source-paced result |
| --- | --- | --- |
| Ice Met | 2 px/update at 30 Hz, frames every two updates | 0.5 px/tick / 30 px/sec, eight-tick frame holds. Frame selection now uses the counter before increment as in source type 50. Terrain/ledge reversal and death needles remain. |
| Icicles, both sizes | +4 velocity at 30 Hz, clamped at 39; five-update grace; immediate removal on impact | Source-unit velocity starts at 2 and increases by 4 at each four-tick step start while below 39, reaching the original overshoot of 42. Apply one quarter per tick: first movement 1.5 px/tick, final 10.5 / 630 px/sec. Terrain collision begins after 20 physics ticks; unit collision substeps remain. On impact snap to the tile surface and linger eight ticks, restoring type 51/52's zero-start pre-increment removal at counter 1. |
| Ice needles, four variants/both directions | Source vectors at 30 Hz | Quarter vectors: (5, 0), (3.75, −2.5), (2.5, −3.75), (0, −5) px/tick, horizontal component mirrored by direction. Existing unit-sized collision subdivisions retained. Type 54. |
| Ice pumpkin | Patrol/chase 6/20 per 30 Hz update, one-second stun | Patrol 2.5 px/tick / 150 px/sec, chase 5 / 300 px/sec, stun 120 ticks / two seconds. Eight-tick animation holds, source-equivalent phase retained across stun. Restored source integer-height comparison and asymmetric chase gaps: subtract 24 on the right or 40 on the left, compare against 200. Nonlethal stun behavior remains. Type 55. |
| Icy attack, five variants/both directions | 13 updates of charge, alpha +30/update, source vectors at 30 Hz | Charge 52 ticks / 0.867 sec; alpha +7.5/255 per tick, then flight starts on tick 53. Quarter movement vectors: (0, 6), (2, 3.5), (4, 2), (6, 0), (4, −2); horizontal components reverse on the other side. Collision and bounds checks run every flight tick. Type 56. |
| Boss shadow intro | 45 updates at 30 Hz, 20 px/update | 180 ticks / three seconds, 5 px/tick, same 900-pixel travel. Source shadow frame sequence 1/2/3/2 uses fourfold timer phase. Type 1007. |
| Boss rise intro / emergence | Source times 6/18/20/22 or 30 at 30 Hz | Teleport/vertical-shadow pose at 24, rise 7.5 px/tick over ticks 25–68 (330 pixels), pose changes at 72/80, intro signal at 88. Later emergence uses the same rise and transitions into its attack at 120. One-time teleports and sprite-alignment offsets remain unscaled. |
| Center/high attacks, both sides | Shot events 20/35; retreat starts after 53 at 30 Hz | Shot events 80/140; pose changes 200/208; retreat begins at 213, 7.5 px/tick / 450 px/sec. Wall shadow threshold y820 and next-move selection below y580 retain their source geometry. |
| Mid attacks, both sides | Fan at 25; pose events 40/42; retreat after 43 | Fan at 100; poses 160/168; retreat from 173 at 7.5 px/tick. |
| Low attacks, both sides | Fan/cross 20/35; pose events 60/62; retreat after 63 | Fan/cross at 80/140; poses 240/248; retreat from 253. Five-variant fan and cross offsets unchanged. |
| Boss bottom dash | 30-pixel horizontal steps and brief −10 vertical steps at 30 Hz | Setup at 4; horizontal 7.5 px/tick during 41–156, with −2.5 vertical during 61–72. Source travel remains 870 px horizontally and −30 vertically. Chooses emergence at 160. |
| Boss side descents | Source movement and pose sequence at 30 Hz | Setup at 4; ±3 px/tick approach during 21–68. Pose changes retain exact offsets at 72/80/88/96. Movement-only steps between poses are distributed over 73–76, 81–84, 89–92, 97–100. Subsequent descent is 5 px/tick; source y1260 transition retained. Wall-clipping shaders and shadow alignment continue updating every tick. |
| Boss meter | Every two physics ticks after intro | First point/sound when intro finishes, then one every four ticks. HUD uses the same counter. After 30 points, one additional source step precedes control/fight handoff. Internal counter begins at 4, fills through 120, unlocks at 124. This models source event 51 filling immediately when set by the boss, then event 81 unlocking. |
| Normal card holder / loose cards | Holder override retained alternate-tick gate and older scales | Holder now inherits Stage 1's direct 60 Hz processor, 160-tick card spin, 80-tick breaking and four-tick blink. Loose cards already inherit the converted Stage 4 controller: 160-tick spin, terrain-arrival fall, 36-tick fade, immediate ownership/replay suppression. |
| Ice holder | Alpha −18/+20 every other tick | Alpha −4.5/+5 every tick; each source 11-update dissolve takes 44 ticks. Four transitions release the card at 176 ticks / 2.933 sec. Float alpha avoids truncating quarter increments. Source type 67's threshold/reset and existing assets retained. |
| Recovery/death/reward | Shared defaults and fast reward processing | Stage-local recovery 3.75 px/tick; ordinary death eight ticks/frame, 24 total. Reward 1.25 px/tick homing, eight-tick frame holds, arrival every 64, fade 36. Other-stage shared defaults remain unchanged. |
| Victory | Bursts every seven physics ticks | Initial triple burst at 24, repeats every 28 at phase 16. Shared type-113 explosion visuals, chosen draw-derived 60 Hz white fades and 30-tick white hold retained. |

Source evidence: canonical `scripts.h:1246–1345`, type 67 at 1422, and every type-1007 state from 2884 through 3355; matching `sprite.h` velocity initialization; icicle landing in `colision.h:1673/1686`; source boss-meter event order. The boss's left/right high, mid and low attack branches were compared separately. Some source pose offsets intentionally remain instantaneous because they align differently sized sprites. Continuous movement and collision/threshold checks can react between original 15 Hz samples; this is the intended consequence of updating every tick, not a claim of identical sampled gameplay against a moving player.

Reuse checked: Stage 7 Ice Met, ice pumpkin and death needles configure interval one after spawn; map74 inherits the icy boss, attacks, intro meter and victory path. Player/weapon tuning, doors, portals, terrain and collision shaders remain unchanged. Static ice spikes need no timing conversion.

Validation: Godot 4.7.2 headless editor/parser load completed after the final script edits with exit code 0 and no script/parser errors. Known sandbox messages concerned editor/user directories, certificate-store access and editor-settings saving. `git diff --check` passed; processor inspection found no remaining alternate-tick gates in Stage 6's converted paths. No gameplay tests were created or run, in accordance with repository instructions.

User playtest pending: maps 60–62, Ice Met ledges/death needles, both icicle sizes including grace period and landing linger, pumpkin patrol/chase/stun, normal and ice card holders, all five icy-attack variants, boss intro/meter, bottom dash, both side descents, all health-dependent attack phases and wall clipping, reward/departure, Stage 7 reuse and map74. Implementation completion does not claim stage acceptance.

## 16. Items deliberately not resolved by this document

- Whether the user's remembered/shipped executable exactly matches this archived build and its rendering rate.
- Which deliberate playtest changes should remain despite differing from source timing.
- Comprehensive player movement, weapon, immunity, pickup, portal, door, HUD, menu, and cinematic timing audits.
- Precise wall-clock ratios for source draw-driven visuals without an established draw rate.
- Automatic replacement of old 30 Hz documentation throughout the repository. Reconcile those statements when timing work is undertaken; preserve non-timing guidance.

The highest-confidence broad suspect is unchanged source script values running at interval two. The strongest counterexamples to a blanket change are Stage 1 turret firing, the thunder boss's fourfold conversion, the turtle boss's interval four, and orange's extra attack gate. Stage 7 red-ball animation and turret firing are already slower cases. Review the actual execution path before changing any of them.
