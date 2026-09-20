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

`Intro.mid` and `Ending.mid` remain non-looping. The intro is rendered in full and retains its existing playback cue.

## In-file music loops (2026-09-14)

The user confirmed that CSelect loops seamlessly when the unchanged initial recording seeks back into itself, and requested the same solution for every looping track. All ten looping tracks now use their existing base OGG with Godot's native `loop` and `loop_offset`; no stream swap or appended loop section is used. The twelve base OGGs are unchanged. Ten separate loop OGGs and two composite OGGs have been removed.

| Role | File | Loop start sample (44,100 Hz) | Loop start seconds |
|---|---|---:|---:|
| Title | `title.ogg` | 1,632,639 | 37.021293 |
| Stage select | `cselect.ogg` | 2,928,777 | 66.412177 |
| World 1 | `tek.ogg` | 157,970 | 3.582086 |
| World 2 | `wkn.ogg` | 157,970 | 3.582086 |
| World 3 | `emr.ogg` | 1,400,822 | 31.764671 |
| World 4 | `ask.ogg` | 3,608,178 | 81.818095 |
| World 5 | `ce.ogg` | 789,850 | 17.910431 |
| World 6 | `myk.ogg` | 473,910 | 10.746259 |
| World 7 | `rrk.ogg` | 2,073,357 | 47.014898 |
| Final boss | `omoide.ogg` | 565,908 | 12.832381 |

Offsets follow the approved CSelect method: use `tools/midi_timing.py` to subtract the existing render's initial seek time from its source loop-start time, then round to the nearest 44,100 Hz sample. The existing files end at their rendered loop-end markers, so Godot repeats from EOF to the listed offset. Each file's duration was checked against its MIDI tempo map; rounding differs by less than one sample. Explicit tick-zero tempos override the Standard MIDI default of 120 BPM.

This preserves sustained notes and reverb already present at the destination in the continuous recording. It supersedes the earlier requirement for fresh-state loop renders, which dropped note starts preceding their slice boundary. Exact Allegro beat-number conversion is a separate historical question; these offsets intentionally preserve the existing recordings and the user-approved CSelect approach rather than rerendering or shifting their initial cues.

CSelect's 125.038095-to-66.412177-second transition is user-validated. The other nine transitions use the same method and still need user listening confirmation. No gameplay tests were run.

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

Current playback uses one tuned gain per sound file. Former event multipliers are folded into `SFX_GAIN_DB`, choosing the quieter level for shared effects and identical WAV copies. This supersedes the archive relative mix and earlier contextual volume differences. See `SFX_LEVELS.md` for current gains and listening adjustments. Menu and pause navigation remain silent; `sands` is not a navigation sound.

The original `inpl()` gate is also preserved for turret shots and impacts, World 3 wall shots/missiles/shock balls, falling fire, flamethrowers, and Ice-shot impacts. These sounds play only while their source is strictly within `520` horizontal and `380` vertical pixels of the player; the cutoff is binary, with no attenuation or panning.

## Overlapping sound levels

As a playtest-driven mix adjustment, identical effects at the same pitch within one physics tick share one playback at the loudest requested gain. Effects triggered on later ticks still overlap, preserving the timing of boss explosions and health-meter filling. The SFX bus limits peaks to -6 dB, and the Master bus limits the combined music/effects output to -1 dB, both without added pre-gain. These are port mix settings rather than archive values; proximity gates and gameplay timing remain unchanged; individual gains now follow the -10 dBFS tuning recorded in `SFX_LEVELS.md`.

## Manual validation required

- Listen through every seam in the packaged build and verify menu/stage/final-boss/ending transitions and SFX event coverage.
- Check falling-block and boss-death bursts against ordinary effects and music; confirm the peak limits sound balanced and health-meter ticks remain distinct.
