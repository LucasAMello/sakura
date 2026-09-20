# SFX gain tuning — 2026-09-14

The original mix targeted individual sound peaks around -10 dBFS. Later listening adjustments below supersede that target. All current event calls use the gain in `SFX_GAIN_DB` directly; former event multipliers are folded into these gains, so one sound file has the same playback amplitude wherever used.

Shared effects use their quietest tuned playback level. Identical WAV copies also share that level: `splaash/turtlejato` and `tiro2/turtledash/windydash`. Proximity gates still control whether a sound plays, without changing its amplitude. The historical adjustment notes below describe earlier mixes; this rule and the table describe the current mix.

Values below are predicted source-sample peaks at 100% SFX volume, before import compression, resampling, overlapping playback, and bus limiters. This is peak matching, not perceptual loudness matching. Compression and resampling can change peaks slightly. Combined effects can exceed -10 dBFS; the existing SFX -6 dB and Master -1 dB peak limiters remain enabled.

The SFX Options control uses 0%, 20%, 40%, 60%, 80%, and 100% in both title and pause menus. Old saved SFX values snap to the nearest step on load. A setting of 0% mutes SFX; other values multiply the tuned output amplitude. Music settings are unchanged.

| WAV | Source peak dBFS | Original event peak dBFS | Playback gain dB | Tuned event peak dBFS |
|---|---:|---:|---:|---:|
| `accept.wav` | -1.9 | -1.9 | -14.14 | -16.0 |
| `anim13.wav` | -0.1 | -4.7 / -0.1 | -14.54 | -14.6 |
| `anim40.wav` | -0.1 | -0.1 | -15.95 | -16.0 |
| `anim60.wav` | -0.1 | -0.1 | -9.93 | -10.0 |
| `bigthunder.wav` | -1.3 | -1.3 | -8.67 | -10.0 |
| `cardget.wav` | -0.1 | -0.1 | -9.93 | -10.0 |
| `deny.wav` | -3.1 | -3.1 | -18.92 | -22.0 |
| `die.wav` | -10.1 | -10.1 | -11.94 | -22.0 |
| `ewulmissile.wav` | -12.3 | -12.3 | -3.70 | -16.0 |
| `fireslash.wav` | -1.1 | -1.1 | -14.94 | -16.0 |
| `fireyflame.wav` | 0.0 | -6.0 / 0.0 | -16.02 | -16.0 |
| `flamethrower.wav` | 0.0 | -8.1 | -22.04 | -22.0 |
| `glass.wav` | 0.0 | -6.2 | -22.04 | -22.0 |
| `haduex.wav` | 0.0 | 0.0 | -16.02 | -16.0 |
| `iceanim.wav` | -5.2 | -5.2 | -10.82 | -16.0 |
| `icefall.wav` | -0.1 | -0.1 | -15.95 | -16.0 |
| `lasts.wav` | 0.0 | 0.0 | -16.02 | -16.0 |
| `penasound.wav` | -0.0 | -0.0 | -10.00 | -10.0 |
| `quicar.wav` | -0.3 | -0.3 | -9.74 | -10.0 |
| `recuperator.wav` | -0.1 | -0.1 | -9.93 | -10.0 |
| `recuperators.wav` | -0.2 | -0.2 | -9.82 | -10.0 |
| `roar.wav` | 0.0 | 0.0 | -10.00 | -10.0 |
| `roar2.wav` | 0.0 | -4.3 | -22.04 | -22.0 |
| `sands.wav` | -0.0 | -6.2 | -10.00 | -10.0 |
| `sparkle.wav` | 0.0 | 0.0 | -10.00 | -10.0 |
| `splaash.wav` | -4.0 | -4.0 | -18.07 | -22.0 |
| `splash.wav` | 0.0 | 0.0 | -16.02 | -16.0 |
| `thundersound.wav` | 0.0 | 0.0 | -22.04 | -22.0 |
| `tiro1.wav` | -8.0 | -9.9 | -15.99 | -24.0 |
| `tiro2.wav` | -4.4 | -4.4 | -11.61 | -16.0 |
| `tiro3.wav` | -0.0 | -0.0 | -10.00 | -10.0 |
| `tiro4.wav` | 0.0 | 0.0 | -16.02 | -16.0 |
| `tiro5.wav` | -2.0 | -2.0 | -14.05 | -16.0 |
| `tiro6.wav` | -0.1 | -0.1 | -9.93 | -10.0 |
| `tiro7.wav` | -0.3 | -0.3 | -15.77 | -16.0 |
| `turret.wav` | -1.4 | -9.5 | -14.62 | -16.0 |
| `turtledash.wav` | -4.4 | -4.4 | -11.61 | -16.0 |
| `turtlejato.wav` | -4.0 | -4.0 | -18.07 | -22.0 |
| `windydash.wav` | -4.4 | -4.4 | -11.61 | -16.0 |
| `wts.wav` | -8.0 | -16.1 | -14.05 | -22.0 |

Validation: source amplitudes and call-site multipliers were inspected; user listening validation remains pending. No gameplay tests were run.

Playtest adjustment (2026-09-15): weapon 1 shot amplitude was reduced by 20% from the previous mix (an additional -1.9382 dB). Other sound gains and the source WAV remain unchanged.

Playtest adjustment (2026-09-17): accept, tiro1, and splash playback amplitudes were halved from their current mix (an additional -6.0206 dB each), retaining the prior tiro1 reduction.

Further playtest adjustment (2026-09-17): orange and machine shots use half their previous `wts` event multiplier (50/255); wall shots retain 100/255. Machine missile launch (`ewulmissile`) and water-shot impact (`splaash`) gains were reduced by 6.0206 dB to halve their amplitudes. Missile explosion gains are unchanged.

Playtest adjustment (2026-09-19): tiro1 was halved again, and the default enemy death sound (`anim40`) was halved from its current mix, each by an additional -6.0206 dB.

Further playtest adjustment (2026-09-19): wall-shot amplitude was reduced to one quarter of its current volume by changing its `wts` event multiplier from 100/255 to 25/255 (-12.0412 dB). Machine and orange shot multipliers remain 50/255.

Further playtest adjustment (2026-09-19): machine and orange shots now also use 25/255, matching wall shots. Player death (`die`) amplitude was reduced to one quarter of its current volume by subtracting 12.0412 dB from its gain.

Further playtest adjustment (2026-09-19): enemy shock-ball shots use a 0.25 event multiplier for `tiro4`, preserving the player weapon's volume. The third boss roar (`roar2`) gain was reduced by 12.0412 dB. Both requested sounds play at one quarter of their previous amplitude.

Subsequent adjustment: player weapon 4 now also uses the 0.25 event multiplier for `tiro4`, matching the enemy shock shot's volume.

Subsequent adjustment: glass-breaking sound amplitude was reduced to one quarter of its previous volume by subtracting 12.0412 dB from the `glass` gain.

Subsequent adjustment: player and enemy shock shots now use a 0.5 event multiplier instead of 0.25, restoring half of their original volume. Turret shooting amplitude was halved by subtracting 6.0206 dB from the `turret` gain.

Latest adjustment: halved fifth-boss spray, slash, and fire impact sounds; icicle sound; weapon 6 impact; and shared sixth-boss/weapon 7 shot plus weapon 7 impact. Shared requests affecting the same sound were applied once. All event multipliers were folded into per-file gains, taking the quieter level where uses differed. Boss explosion anim13 now matches the quieter turret/missile impact. Identical WAV copies were matched to their quieter gain.
