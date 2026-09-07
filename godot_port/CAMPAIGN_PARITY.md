# Campaign and menu parity

## Archive-confirmed

- Title, menu, stage-select, six initially selectable elemental stages, final-stage lock, five starting lives, and original default controls follow `menu.h` and `Main.cpp`.
- The selected main-menu card uses the original four face frames, three card-back frames, reverse turn, staff cursors, and 30 Hz source cadence from `draw_menu()`.
- Moving between main-menu cards is silent, matching `main_menu()`; `ACCEPT` is reserved for confirmation.
- New Game plays the archived dream text and island-fall sequence before stage select. Its `Intro` music starts at the source beat-4 seek point; Enter or F skips after the opening input-release hold.
- Boss cards 0–5 unlock weapons 2–7 and the final-stage choice.
- Ordinary stage entry restores maximum HP, selects weapon 1, and clears that stage's transient checkpoint.
- Life exhaustion returns to stage select and resets the session to five lives.
- Completed elemental stages use the archive's gray `STAGE*2` stage-select artwork, keyed to boss reward cards 0-5; replay remains available.
- One-slot persistence stores cards; HP, lives, weapon, checkpoints, active map, and final-stage rematches are transient.

## Port decisions

- The save is a validated JSON v1 schema rather than the unsafe 18-character Allegro format.
- Settings use a separate JSON file and apply immediately.
- Completed stages suppress duplicate boss rewards but remain replayable.

## Manual validation required

- Menu layout positions, intro timing and falling-pivot presentation, fade lengths, remapped-key conflict handling, and every game-over return path need packaged-build playtesting.
