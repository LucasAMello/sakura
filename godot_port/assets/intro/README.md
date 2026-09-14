# Intro assets

`intro1.png` through `intro5.png` and `intro.mid` were extracted from `old/4 Sakura2.0/Media/files.dat`, where they are stored as `INTRO1` through `INTRO5` and `INTRO`. The loose `old/5 jogos new sakura/Intro.mid` was verified byte-for-byte against the embedded MIDI.

The bitmap dimensions are preserved and palette magenta `(255, 0, 255)` was converted to alpha. `intro.ogg` in `assets/audio/music/` was rendered from the MIDI with FluidSynth 2.6.0 and MuseScore General, matching the rest of the port soundtrack.

The falling sequence also overlays `assets/menu/final_stage_boulder.png`, at the user's request. Its island-local position is (124, 31), corresponding to stage select's (244, 211) with the island origin at (120, 180). It inherits the intro island's 1.5x scale and visibility and draws behind falling Sakura. This adds the stage-select boulder to the archived intro's bare island without changing cinematic timing.
