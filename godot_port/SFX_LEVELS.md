# SFX source levels and playback gains

Measured 2026-09-14 from all 40 source WAVs and current playback calls. No audio assets or playback settings changed.

Values are dBFS: 0 is digital full scale; more negative values are smaller amplitudes. RMS measures average signal level over the entire file, including fades/silence. It is not perceptual loudness. Predicted playback values apply only the event gain, before import compression, resampling, bus effects, overlapping sounds, and the user's volume settings. The import settings currently disable normalization for all effects.

The SFX bus has a -6 dB peak limiter and Master has a -1 dB peak limiter, with no configured added pre-gain. They constrain the combined signal rather than equalizing individual sounds. The table assumes 100% SFX volume. At 50% SFX volume, the bus gain contributes approximately -6 dB, though final output depends on limiter processing and other sounds.

`ewulmissile` has the lowest source peak and whole-file RMS of all 40 effects. Its playback multiplier is 1.0 in both the original source and the port; no automatic boost compensates for its low source amplitude. It plays only within the source proximity gate, with no gradual distance attenuation. Its loudest measured 50 ms block has RMS -20.35 dBFS, confirming that its low whole-file average is not solely due to silence at the end.

Two gain values indicate different events: `fireyflame` uses 128/255 for falling fire and full gain for other uses; `anim13` uses 150/255 for turret-shot impacts and full gain for other uses. Rows are sorted from lowest predicted whole-file RMS at the highest event gain.

| WAV | Source peak | Source RMS | Event gain | Peak after event gain | RMS after event gain |
|---|---:|---:|---:|---:|---:|
| `ewulmissile.wav` | -12.3 | -28.7 | 100.0% | -12.3 | -28.7 |
| `sands.wav` | -0.0 | -17.4 | 49.0% | -6.2 | -23.6 |
| `wts.wav` | -8.0 | -14.6 | 39.2% | -16.1 | -22.7 |
| `quicar.wav` | -0.3 | -21.2 | 100.0% | -0.3 | -21.2 |
| `flamethrower.wav` | 0.0 | -12.9 | 39.2% | -8.1 | -21.0 |
| `tiro5.wav` | -2.0 | -19.7 | 100.0% | -2.0 | -19.7 |
| `lasts.wav` | 0.0 | -19.4 | 100.0% | 0.0 | -19.4 |
| `turret.wav` | -1.4 | -11.1 | 39.2% | -9.5 | -19.3 |
| `anim40.wav` | -0.1 | -18.9 | 100.0% | -0.1 | -18.9 |
| `fireslash.wav` | -1.1 | -18.9 | 100.0% | -1.1 | -18.9 |
| `glass.wav` | 0.0 | -12.5 | 49.0% | -6.2 | -18.7 |
| `iceanim.wav` | -5.2 | -17.9 | 100.0% | -5.2 | -17.9 |
| `tiro7.wav` | -0.3 | -17.9 | 100.0% | -0.3 | -17.9 |
| `splaash.wav` | -4.0 | -17.9 | 100.0% | -4.0 | -17.9 |
| `turtlejato.wav` | -4.0 | -17.9 | 100.0% | -4.0 | -17.9 |
| `cardget.wav` | -0.1 | -17.5 | 100.0% | -0.1 | -17.5 |
| `sparkle.wav` | 0.0 | -16.9 | 100.0% | 0.0 | -16.9 |
| `splash.wav` | 0.0 | -16.8 | 100.0% | 0.0 | -16.8 |
| `anim13.wav` | -0.1 | -16.8 | 58.8% / 100.0% | -4.7 / -0.1 | -21.4 / -16.8 |
| `icefall.wav` | -0.1 | -16.5 | 100.0% | -0.1 | -16.5 |
| `tiro2.wav` | -4.4 | -16.5 | 100.0% | -4.4 | -16.5 |
| `turtledash.wav` | -4.4 | -16.5 | 100.0% | -4.4 | -16.5 |
| `windydash.wav` | -4.4 | -16.5 | 100.0% | -4.4 | -16.5 |
| `accept.wav` | -1.9 | -15.9 | 100.0% | -1.9 | -15.9 |
| `recuperators.wav` | -0.2 | -15.6 | 100.0% | -0.2 | -15.6 |
| `tiro1.wav` | -8.0 | -13.7 | 80.4% | -9.9 | -15.6 |
| `tiro6.wav` | -0.1 | -15.1 | 100.0% | -0.1 | -15.1 |
| `bigthunder.wav` | -1.3 | -15.0 | 100.0% | -1.3 | -15.0 |
| `thundersound.wav` | 0.0 | -14.9 | 100.0% | 0.0 | -14.9 |
| `tiro4.wav` | 0.0 | -14.9 | 100.0% | 0.0 | -14.9 |
| `tiro3.wav` | -0.0 | -14.6 | 100.0% | -0.0 | -14.6 |
| `roar2.wav` | 0.0 | -10.1 | 60.8% | -4.3 | -14.4 |
| `die.wav` | -10.1 | -14.1 | 100.0% | -10.1 | -14.1 |
| `roar.wav` | 0.0 | -13.9 | 100.0% | 0.0 | -13.9 |
| `penasound.wav` | -0.0 | -13.8 | 100.0% | -0.0 | -13.8 |
| `fireyflame.wav` | 0.0 | -12.8 | 50.2% / 100.0% | -6.0 / 0.0 | -18.8 / -12.8 |
| `haduex.wav` | 0.0 | -12.5 | 100.0% | 0.0 | -12.5 |
| `anim60.wav` | -0.1 | -11.5 | 100.0% | -0.1 | -11.5 |
| `deny.wav` | -3.1 | -10.2 | 100.0% | -3.1 | -10.2 |
| `recuperator.wav` | -0.1 | -9.3 | 100.0% | -0.1 | -9.3 |
