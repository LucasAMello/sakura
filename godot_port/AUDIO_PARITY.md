# Audio parity

## Provenance

- Forty SFX WAV files were extracted from canonical `old/2 Joguito/files.dat`.
- Eleven campaign MIDI files came from `old/2 Joguito`; the New Game `Intro` MIDI and its embedded copy came from the Sakura 2.0 archive. All twelve tracks were rendered with FluidSynth 2.6.0 plus MuseScore General.
- MuseScore General licensing is retained in `assets/audio/licenses/`.

## Start and loop markers

| Role | MIDI | Initial seek | Loop range |
|---|---|---:|---:|
| New Game intro | Intro | starts at beat 4, non-looping | 3.0 s playback cue |
| Title | Title | beat 6 | 93–237 |
| Stage select | CSelect | beat 4 | 149–277 |
| World 1 | Tek | beat 5 | 13–165 |
| World 2 | Wkn | beat 5 | 13–177 |
| World 3 | Emr | beat 5 | 77–277 |
| World 4 | Ask | beat 5 | 185–357 |
| World 5 | Ce | beat 5 | 45–193 |
| World 6 | Myk | beat 5 | 29–157 |
| World 7 | Rrk | beat 5 | 110–278 |
| Final boss | Omoide | file start | 37–389 |

`Intro.mid` and `Ending.mid` are non-looping. The intro is rendered in full and playback begins at the source's beat-4 seek point. Every looping MIDI is sliced into an initial seek-to-end file and a loop-start-to-end file before synthesis, matching Allegro's all-notes-off seek behavior. `tools/midi_timing.py` converts beat positions using the MIDI tempo map; `tools/midi_slice.py` creates the state-restored MIDI sections.

Stage select packages those two independently synthesized sections into `cselect_composite.ogg` and loops at `125.038095` seconds, the exact end of its initial beat-4-to-277 section. This keeps the loop's fresh MIDI state while avoiding an audible process-frame gap from swapping streams after the initial section finishes.

World 4 similarly packages the existing `ask.ogg` and `ask_loop.ogg` sections into `ask_composite.ogg`. Its loop offset is exactly 7,055,993 samples at 44,100 Hz (159.999841 seconds), preserving the beat-5 initial seek and beat-185-to-357 repeat without switching streams. The composite is generated with FFmpeg's audio concat filter and Vorbis quality 6.

The MIDI files provide explicit tick-zero tempos; these override Standard MIDI's default 120 BPM. World 1's initial/loop renders are `71.641760`/`68.059672` seconds, and World 2's are `77.014892`/`73.432804` seconds. The previous 120 BPM assumption placed both loop ends several musical bars late.

## Canonical SFX event mapping

The event assignments below were checked against every `play_sample(...)` call in `old/2 Joguito`. Names refer directly to the forty WAV files extracted from `files.dat`.

| Event | Canonical sample |
|---|---|
| Menu/stage confirmation; locked final-stage denial | `accept`; `deny` |
| Ordinary enemy death; large turret/machine death; enemy-shot or boss destruction burst | `anim40`; `anim60`; `anim13` |
| Player death sequence | `die`, at death-timer values 0, 20, 40, 60, and 80 |
| Card collection; maximum-HP threshold | `cardget`; `sparkle` |
| Any small/medium/life recovery pickup; each boss-meter point | `recuperators`; `recuperator` |
| Generic card holder; sand card mound | `glass`; `sands` |
| Player weapons 1–7 | `tiro1` through `tiro7` |
| Wind/Shadow/Water/Fire/Ice special events | `windydash`; `quicar`; `splaash`; `haduex`; `iceanim` |
| Green turret shot and impact; first-boss feather | `turret`; `anim13`; `penasound` |
| World 2 boss split | `tiro3` |
| World 3 wall shot, missile, shock ball, lightning, beam, and boss dash | `wts`; `ewulmissile`; `tiro4`; `bigthunder`; `thundersound`; `roar2` |
| Water entry/exit, fourth-boss intro, jet, and dash | `splash`; `roar`; `turtlejato`; `turtledash` |
| Flamethrower, falling/sprayed fire, fire slash, and fifth-boss intro | `flamethrower`; `fireyflame`; `fireslash`; `roar` |
| Falling icicle and sixth-boss ice attack | `icefall`; `tiro7` |
| Final-boss small shot, thunder shot, and fire shot | `lasts`; `thundersound`; `fireyflame` |

Archive gain differences are preserved for `tiro1` (205/255), `turret`, `wts`, and `flamethrower` (100/255), `glass` and `sands` (125/255), falling `fireyflame` (128/255), `roar2` (155/255), and turret-shot `anim13` (150/255). All other listed events use full source gain. Menu and pause navigation are intentionally silent in the canonical source; `sands` is not a navigation sound.

The original `inpl()` gate is also preserved for turret shots and impacts, World 3 wall shots/missiles/shock balls, falling fire, flamethrowers, and Ice-shot impacts. These sounds play only while their source is strictly within `520` horizontal and `380` vertical pixels of the player; the cutoff is binary, with no attenuation or panning.

## Overlapping sound levels

As a playtest-driven mix adjustment, identical effects at the same pitch within one physics tick share one playback at the loudest requested gain. Effects triggered on later ticks still overlap, preserving the timing of boss explosions and health-meter filling. The SFX bus limits peaks to -6 dB, and the Master bus limits the combined music/effects output to -1 dB, both without added pre-gain. These are port mix settings rather than archive values; individual sound gains, proximity gates, and gameplay timing remain unchanged.

## Manual validation required

- Listen through every seam in the packaged build and verify menu/stage/final-boss/ending transitions and SFX event coverage.
- Check falling-block and boss-death bursts against ordinary effects and music; confirm the peak limits sound balanced and health-meter ticks remain distinct.
