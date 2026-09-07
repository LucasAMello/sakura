# Menu assets

The title, stage-select, options, pause, and campaign-menu artwork in this directory is extracted from the canonical Allegro archive at `old/2 Joguito/files.dat`.

The six `stage_*_complete.png` images are the original `STAGEWIND2`, `STAGEWATER2`, `STAGEFIRE2`, `STAGETHUNDER2`, `STAGEICE2`, and `STAGESHADOW2` stage-select variants. They are displayed after the corresponding boss reward card has been collected. Source magenta `(255, 0, 255)` was converted to transparency; dimensions and nearest-neighbor presentation are preserved.

`quit_game.png` is a direct conversion of the original `QuitGame.bmp` stage-select sprite. It retains the source position at `(439, 88)` and returns the player to the title menu, matching the original `mainmenu = 1` action.

`final_stage_boulder.png` is the `BOULDERLOL` object from `old/4 Sakura2.0/Media/files.dat`. The completed source draws it at `(244, 211)` over the final-stage entrance while it is locked, then fades it out across 20 ticks when all six boss rewards have been collected.

The `card_the.png` and `card_*.png` word sprites are direct conversions of the original loose card-book BMPs. Their source positions and one-pixel word offsets are retained by the pause HUD.
