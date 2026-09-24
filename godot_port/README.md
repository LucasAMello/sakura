# Sakura — Godot port

This is a preservation-minded Godot 4.7.2 port of Sakura, the 2008 C++/Allegro game. It restores the canonical campaign represented by `old/2 Joguito`: the original menu and stage-selection structure, six elemental worlds, seven weapons, 52 cards, the final-stage rematches, final boss, and ending. The original cheat-based hard mode is restored; the later Sakura 2.0 selectable difficulty system remains outside scope.

## Campaign

New Game resets progress, plays the original dream sequence and Sakura's fall toward the island, then opens stage select with five lives, 15 maximum HP, weapon 1, no cards, and all six elemental stages selectable. Enter or F skips the sequence after its opening hold. Defeating an elemental boss returns to stage select, records boss card 0–5, and unlocks the corresponding weapon 2–7. Completed stages remain replayable and cannot award a second boss card.

The final stage unlocks after all six boss cards are collected. Maps 70–72 lead to the six-portal hub on map73. The portals launch the original bosses in rematch mode; rewards are suppressed and each victory returns to the hub. Rematch state lasts only for the current final-stage run. Completing all six opens map80, the final boss, and the six-part ending and credits.

All 52 card IDs are represented. Maximum HP is derived from the card count and is not saved separately: 15 initially, 16 at 10 cards, 17 at 20, 18 at 30, 19 at 40, and 20 at all 52. Crossing a threshold increases the maximum without healing current HP.

## Controls

- Arrow keys: move and navigate
- F: jump or confirm
- D: fire
- A / S: previous or next unlocked weapon
- 1–7: direct weapon selection
- Enter: confirm, pause, or resume
- Escape: back in menus; leave a stage using the pause menu's exit option
- F3: compatibility/debug display
- R: reload the current map during development

Controls can be remapped from Options. Music and SFX levels apply immediately and are retained separately from campaign progress. SFX adjusts in 20% steps in title and pause Options. Individual SFX gains target approximately -10 dBFS at full SFX volume, with quieter contextual variants retained; see `SFX_LEVELS.md`. The pause menu provides the original weapon grid, lives display, collected-card book, audio and control options, resume, and return to stage select.

## Cheats

Type **K E R O** in title-menu Options or paused Options (outside control rebinding). The accept sound confirms activation. Then use these keys during active gameplay:

| Key | Effect |
| --- | --- |
| G | God Mode Toggle: invincibility, with normal movement speed |
| B | Battle the Last Boss |
| C | Collect all 52 cards and unlock their weapons/maximum HP |
| T | Turn cheats off |

Cheats last for the application session, across deaths, room changes, New Game and Load Game; they are not saved. Changes to collected cards can be saved normally. Completing the ending with all 52 cards displays the code and shortcuts after Enter, once the final fade has finished. A second Enter returns to the title. Knowing the code is sufficient to activate cheats before completing the game.

The 2008 release readmes document the original shortcuts. The later `old/4 Sakura2.0/menu.cpp` and `intro.cpp` preserve KERO and the 52-card ending condition absent from the canonical source snapshot. The hint is recreated as text rather than using the later CHEAT bitmap. Existing debug-only G behavior remains available when cheats are disabled.

Validation (2026-09-13): Godot 4.7.2 editor/parser compile check completed without script errors. No gameplay tests were run under repository instructions. User playtesting remains pending for both Options entry points, the cheat shortcuts, hard-mode damage, and the 51/52-card ending branches.

## Saves and settings

The final-stage boulder reveal waits for the stage-select screen to draw and any transition to finish, holds the boulder for half a second, then fades it over 60 ticks (one second), playing `lasts`, the final boss first-attack sound, as the fade begins. The fade runs on rendered frames instead of physics ticks so loading catch-up cannot consume the animation before presentation. The reveal is recorded once its fade finishes and preserved in saves. Older native saves without that flag replay the reveal once when all six bosses are complete. Saves that already mark it seen do not replay it. The initial hold is a presentation adjustment following the 2026-09-17 playtest report; the fade was subsequently extended to 60 ticks and the sound added at the user's request. Listening and visual playtest confirmation remain pending.

The single versioned campaign slot is `user://sakura_save.json`. On Windows that resolves beneath `%APPDATA%\Sakura\`. The v1 schema stores only validated collected-card IDs; boss completion, weapon unlocks, final-stage access, score, and maximum HP are derived when loading. A missing, corrupt, duplicate, out-of-range, or unsupported save is rejected before active progress is changed.

Saving also writes the original 18-character Allegro slot as `user://save.sav`. When the JSON slot is absent, Load Game accepts and validates that legacy format, so an original campaign save can be copied into the Godot user-data directory and migrated without losing collected cards. Controls and audio levels are stored in `user://sakura_settings.json`. HP, lives, selected weapon, checkpoints, active map, and final-stage rematch state are transient.

## Timing and presentation

The game renders into a fixed 640×480 viewport with integer scaling and 2D transform pixel snapping. Window sizes that do not fit an exact scale use borders. Gameplay positions retain their fractional precision; snapping affects rendering only.

The logical viewport is 640×480 with nearest-neighbor filtering. Godot physics remains at 60 Hz. The archived main loop has a 60 Hz timer but calls gameplay scripts every fourth tick, nominally 15 Hz. Earlier port work incorrectly assumed 30 Hz; many later-world controllers still use interval two and remain pending review. Stages 1–6 have received timing passes with updates every physics tick and source-paced movement, animation, attacks, projectiles, and objects. Draw-driven source visuals use documented presentation assumptions pending playtesting. Player control and the seven weapons retain their existing 60 Hz tuning. See [TIMING_ADJUSTMENTS.md](TIMING_ADJUSTMENTS.md) for source evidence, per-entity conversion details, exceptions, and pending user playtests; interval two alone does not establish source timing parity.

Existing manual tuning is deliberate, including 25-tick default autofire, 9-pixel default projectile movement, 80-tick player immunity, card animation speed, door timings, portal timing, recovery fall speed, and the map14 introduction.

World 4 shoreline slope tokens use source-image alpha for pixel-accurate collision instead of full 20×20 collision cells.

Boss doors in Worlds 1, 2, 3, 4, and 6 retract into the wall: the doorway's top edge stays fixed while the upper portion of the moving artwork is clipped. Fully open doors retain a 20-pixel visible strip, leaving 80 pixels of clearance for the 100-pixel doors and 120 pixels for the Ice doors. Collision bounds follow the visible portion. Existing opening/closing durations and scripted walking timings are preserved. This presentation change follows the user's request and awaits visual playtest confirmation.

## Assets and audio

Maps and behavior come from `old/2 Joguito`. Release menu, ending, credits, World 7 atlases, and final-boss graphics were extracted from its authoritative `files.dat`; loose assets were used only when verified or when the archive did not contain that group. Allegro magenta `(255, 0, 255)` was converted to transparency without resizing.

The 40 canonical sound effects were extracted from `files.dat`. `Title`, `Intro`, `CSelect`, `Tek`, `Wkn`, `Emr`, `Ask`, `Ce`, `Myk`, `Rrk`, `Omoide`, and `Ending` were rendered to OGG with FluidSynth 2.6.0 and MuseScore General. All ten looping tracks use their unchanged base OGG with native in-file loop offsets, following the user-confirmed seamless CSelect solution. Separate loop and composite OGGs have been removed. Intro and ending remain non-looping, and the intro retains its existing playback cue. See `AUDIO_PARITY.md` for sample offsets and listening-validation status. MuseScore General attribution and license are in `assets/audio/licenses/`; rendered OGG files do not bundle the soundfont.

Asset-group provenance is recorded in the parity documents and the READMEs beside converted asset groups. The original game assets remain subject to their original ownership; redistribution of a packaged build should be authorized by the rights holder.

## Architecture

`GameFlow.STAGE_STARTS` selects the scene launched by stage select. Each map scene explicitly sets its `map_number`, which selects the stage controller's map configuration. There is no script-level default-map fallback. `_first_map_number()` identifies the canonical entrance map for portal presentation; it does not control scene routing or debug start maps.

- `SakuraProgress`: validated save/load, cards, derived HP/unlocks, lives, checkpoints, and transient rematches
- `GameFlow`: title, stage select, stage launch, boss completion, game over, rematches, final stage, and ending routing
- `AudioManager`: Music/SFX buses, track roles, exact loop offsets, and one-shot effects
- `SakuraSettings`: immediate audio/control settings and persistence
- `StageBase`: shared stage lifecycle, player/HUD, pause, map transitions, deaths, projectiles, and enemy registry
- `scripts/world1/` through `scripts/world6/`: elemental stage and boss controllers
- `scripts/world7/stage7.gd`: maps 70–73 and the rematch hub
- `scripts/world7/stage80.gd`, `final_boss.gd`: final arena and boss
- `scripts/menu/intro.gd`: New Game dream and island-fall sequence
- `scripts/menu/ending.gd`: ending and credits sequence

## Build

Use Godot 4.7.2 and its matching standard export templates.

```powershell
& 'C:\Program Files\Godot\Godot_v4.7.2-stable_win64_console.exe' --headless --path godot_port --editor --quit
& 'C:\Program Files\Godot\Godot_v4.7.2-stable_win64_console.exe' --headless --path godot_port --export-release 'Windows Desktop' release\Sakura.exe
```

The first command is the only permitted automated validation and is strictly a parser/editor compile check. Do not add or run automated gameplay tests. Gameplay validation is manual.

The Windows preset produces `Sakura.exe` and `Sakura.pck`. The portable release ZIP also contains this README, controls, credits, license/attribution files, and the original icon.

## Manual release checklist

Playtest the packaged build on Windows across the complete New Game intro, all six elemental stages, all seven weapons, all 52 cards and HP thresholds, save/load and corrupt-save handling, stage selection, life exhaustion, pause/options/remapping, maps 70–80, every rematch, final boss, track loops, sound effects, and the complete ending. The parity records identify archive-confirmed behavior and remaining visual/gameplay approximations.

Boss damage is ignored once Sakura is dead, including lingering projectiles, water splashes, Shadow clone hits, and rematches. During the boss explosion sequence, airborne Sakura keeps her jumping pose; grounded Sakura uses idle. Existing scripted landing and departure behavior remains in place.
