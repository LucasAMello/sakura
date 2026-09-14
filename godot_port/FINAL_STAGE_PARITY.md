# Final stage parity

## Archive-confirmed

- Authoritative maps 70–80 and the canonical 200×200 `TEXTURES08`/`TEXTURES09` atlases are imported from `old/2 Joguito` and `files.dat`.
- Maps 70–72 use their original dimensions, starts, exits, mixed enemy families, source ghost-mask emitters, dual-atlas terrain switching, and Rrk music.
- Map73 uses six portals, source element labels, and the medium recovery in their original positions. The source order is Ice, Wind, Shadow, Thunder, Water, Fire, leading to maps 74–79.
- Rematches reuse the existing boss controllers, suppress reward cards, return to map73, and remain transient.
- Map80 uses the original start, arena, 30-HP boss, seven main attack states, source attack positions and firing schedules, teleport fades, source projectile art, Omoide music, death fade, and ending trigger.
- Ending panels, credits panels, Thanks, The End, player walk, scrolling presentation, and Ending music use canonical archive assets.

## Final boss timing correction (2026-09-11)

Subsequent playtest correction: fire projectiles (types77/78) now update every 60 Hz physics tick. Their charge lasts32 ticks, settling movement uses one quarter of each source velocity, and each orbit displacement is spread over eight ticks (four for the initial segment), preserving the existing path endpoints and departure times. The340-tick settling hold and28-tick fade retain the prior total lifetime. Damage checks and fade interpolation also run every physics tick. This supersedes the fire projectile cadence statement below; the boss chooser and other script-driven projectile families retain their current cadence.

The user's request to match original timing supersedes the preserved 30 Hz tuning below and the historical World 7 cadence guidance in AGENTS.md.

- Boss logic and target/fire/ice projectile logic now advance every four physics ticks (15 Hz). Source timer constants and movement vectors remain intact, including both ice collision substeps. Target spacing is 1s, lightning spacing 2/3s, horizontal ice speed 360px/s, and teleport recovery 50/15s. Charges take 0.4s for target balls, 8/15s for fire, and 1/3s for ice.
- Fade-in step1 now remains transparent, matching the source placement step; alpha starts rising at step2.
- Type76 lightning runs on a separate fixed 60 Hz presentation clock: frames change at ticks5/9, removal at13. Target-ball and fire artwork also use separate 60 Hz frame counters with source holds of 6, 8, and 12 ticks. Their charge, lifetime, and movement continue at 15 Hz. The archive's draw loop is uncapped, so 60 Hz is an explicit presentation assumption, not an exact historical frame-rate claim.
- Intro black fade and boss fade each last 64 source steps (256 physics ticks); the explicit 50ms source pause is represented by three physics ticks. Health fills one point every four ticks, followed by one source step before control returns. Fade alpha is interpolated each physics tick. Exact legacy phase alignment and repeated blocking `rest()` calls are not reproduced.
- Death explosions use source script spacing (first special burst at20 physics ticks, repeated bursts every28). The draw-driven white fade stays on the 60 Hz presentation clock, with the archive's explicit 500ms final hold restored.
- Camera, terrain-clipped lightning, player movement, weapon timing, and rematch health carryover remain intact. Validation: Godot parser/editor load only; no gameplay tests.

## Earlier final boss audit (2026-09-11)

- `Main.cpp` map80 specifies a 2500x600 map, arena limits x=840..1660 and y=0..600 (820x600), and Sakura's start (930,260). The map and spawn match. The fixed port camera was incorrect: restored `draw.h` tracking with center x=clamp(player.x+20,1160,1340), y=clamp(player.y,240,360). Restored background vertical scrolling at one fifth of the terrain rate; background origin (865,0) and fill RGB (20,15,60) already match.
- `scripts.h` type1008 and `sprite.h` confirm 30 HP, seven attack positions, no consecutive repeated attack, basic-weapon-only damage and one hit per appearance. Target balls spawn every 15 script steps; lightning every 10 after step25; six fire shots at 25/29/33/39/45/51; ice starts with five shots then fourteen aimed shots. Those schedules and projectile movement vectors match the port's source-step constants.
- Timing is not real-time parity: original `Main.cpp` installs a 60 Hz timer and calls `run_scripts()` every fourth tick (15 Hz); final boss and projectiles currently advance at 30 Hz. Existing tuning is preserved under AGENTS.md. Target spacing is 0.5s versus original 1s; lightning spacing 0.333s versus 0.667s; target/lightning/fire-or-ice appearances including fade-in are 5.333/4.267/6.667s versus 10.667/8.533/13.333s. Teleport interval is 1.667s versus 3.333s. First target appearance skips its 20-step fade-in.
- Ice velocity components are (0,24), (10,12), (17,7), (24,0), (17,-7), (10,-12) pixels per script step, mirrored horizontally. Horizontal ice travels 720px/s in the port versus 360px/s in the archive. Fire orbit advances its 16 displacement vectors every other script step; settling uses axis speeds 2..10 px/step (60..300px/s port versus 30..150px/s archive). Target-ball charge is 0.2s versus 0.4s; fire charge 0.267s versus 0.533s; ice charge 0.167s versus 0.333s.
- Lightning type76 is draw-clock-driven in `draw.h`, not script-driven, so its original wall-clock animation duration depends on rendering. The port retains frame changes at steps5/9 and removal at13 on its existing 30 Hz clock. `colision.h` records the first terrain wall and `draw.h` truncates the bolt there. Restored terrain clipping across the 34px bolt width, including a cropped final 128px texture segment. Damage and weapon interception use the same shortened rectangle. Original player-impact shortening is not reproduced; this correction concerns terrain.
- Intro fades/health filling and death presentation remain the current port approximation, not confirmed real-time parity. No gameplay tests were run; parser/editor load is the permitted validation.

## Historical 60/30 Hz conversion

- World 7 stage logic, reused enemies, new projectiles, final-boss state timers, animation, hazards, and attacks update at the 30 Hz-equivalent cadence while player control and rendering remain at 60 Hz.
- The invisible source type-71 proximity triggers on maps 71 and 72 reuse the ported type-72 seahorse controller, including their 90-source-tick cooldown.

## Manual verification focus

- Maps 74–79 are the six canonical boss arenas at their source dimensions and coordinates, with their existing boss controllers running in transient rematch mode.
- Final-boss projectile collision and presentation reproduce the source target-ball, lightning-column, orbiting-fire, and six-angle ice families; packaged playtesting should confirm safe gaps and visual layering at release resolution.
- Ending panel dwell, fades, one-second inter-panel holds, backgrounds, reflection panel, ground widths, credit alpha, and final Enter gate are reconstructed directly from `menu.h`; packaged playtesting should confirm uninterrupted audio/video timing.

## Ending sequence audit (2026-09-13)

Compared `scripts/menu/ending.gd` with canonical `old/2 Joguito/menu.h` (`myend` and `drawend`) and the boss-to-ending white hold in `draw.h`.

- Moved the opaque backdrop behind the scenery; it previously covered both background layers.
- Rebuilt each background as the original 800x480 composite, including the 608/400/640-pixel repeats, blue water fill, and horizontal reflection of the complete water composite. Panel five uses the first world's background, as the source reloads `bg.bmp`.
- Kept Sakura's horizontal position and eight-tick walk phase continuous across panels; initialized the first walk texture immediately. The water foreground now draws over her lower body, matching source draw order. Credit centering and background scrolling use source integer coordinates.
- Preserved the white screen through both five-second prelude holds and restored the first panel's white reveal. Its source fade decreases every third draw; 765 physics ticks uses the existing 60 Hz presentation assumption. Later black fades, panel durations, one-second holds, non-looping ending music, final fade, and final Enter gate retain their current timing/behavior.
- Preserved pre-existing edits to the ending's final fade, campaign routing, and final boss. No player or combat tuning changed.

Validation: Godot 4.7.2 headless editor/parser load exited 0 with no script/parser errors; sandbox editor-directory, certificate-store, and settings-save errors remained. `git diff --check` passed. No gameplay tests were created or run. Draw-driven fade timing remains a 60 Hz approximation; the original uncapped draw loop and accumulated timer ticks during blocking rests are not reproduced. Full audiovisual playtest acceptance remains pending.
