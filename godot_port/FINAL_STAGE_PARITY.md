# Final stage parity

## Archive-confirmed

- Authoritative maps 70–80 and the canonical 200×200 `TEXTURES08`/`TEXTURES09` atlases are imported from `old/2 Joguito` and `files.dat`.
- Maps 70–72 use their original dimensions, starts, exits, mixed enemy families, source ghost-mask emitters, dual-atlas terrain switching, and Rrk music.
- Map73 uses six portals, source element labels, and the medium recovery in their original positions. The source order is Ice, Wind, Shadow, Thunder, Water, Fire, leading to maps 74–79.
- Rematches reuse the existing boss controllers, suppress reward cards, return to map73, and remain transient.
- Map80 uses the original start, arena, 30-HP boss, seven main attack states, source attack positions and firing schedules, teleport fades, source projectile art, Omoide music, death fade, and ending trigger.
- Ending panels, credits panels, Thanks, The End, player walk, scrolling presentation, and Ending music use canonical archive assets.

## 60/30 Hz conversion

- World 7 stage logic, reused enemies, new projectiles, final-boss state timers, animation, hazards, and attacks update at the 30 Hz-equivalent cadence while player control and rendering remain at 60 Hz.
- The invisible source type-71 proximity triggers on maps 71 and 72 reuse the ported type-72 seahorse controller, including their 90-source-tick cooldown.

## Manual verification focus

- Maps 74–79 are the six canonical boss arenas at their source dimensions and coordinates, with their existing boss controllers running in transient rematch mode.
- Final-boss projectile collision and presentation reproduce the source target-ball, lightning-column, orbiting-fire, and six-angle ice families; packaged playtesting should confirm safe gaps and visual layering at release resolution.
- Ending panel dwell, fades, one-second inter-panel holds, backgrounds, reflection panel, ground widths, credit alpha, and final Enter gate are reconstructed directly from `menu.h`; packaged playtesting should confirm uninterrupted audio/video timing.
