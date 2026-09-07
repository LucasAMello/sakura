# Stages 5?7 playtest corrections

Stage 5 flames (original types 39/40), falling fire, and boss spray/hadouken/slashes all pass through StageBase._spawn_enemy and receive interval 2. Their movement and animation run at 30 Hz; the archive hadouken speed is 40 pixels per source tick and slash speeds are 20 horizontally or 17 horizontally plus 8 vertically. These values were retained, not halved again. Contact checks remain on the shared 60 Hz path.

Stage 5 entry movement/camera durations and intro health fill now use converted 60 Hz durations. The boss retains its interval-2 animation. Squid activation and the turn-to-fall handoff now perform the same-tick movement in scripts.h type 45, and choose the swim frame after updating the timer as draw.h does. Weapon 6 restores the original impact offset (-18, -17).

Stage 6 token 0 is no longer rendered. The A/D/E/H fill is behind the terrain edge, matching the order of initialize_wall calls in maps.h. Ice pumpkin patrol now matches World 1 in real time (6 pixels at 30 Hz versus 3 at 60 Hz); chase remains 20 at 30 Hz. Door rise/close take 40 physics ticks; scripted walks retain their distances with doubled durations. Ice-holder alpha resets immediately at frame changes, avoiding a blank frame. Released cards already inherit World 4's falling pickup behavior, with duplicate-card checks.

The ice boss draws normal artwork within the source room bounds x=3380..3880, y=820..1100 and translucent shadow outside. Vertical descent flips both the normal and shadow forms as in draw.h type 1007. The shader uses these rectangular boundaries rather than arbitrary terrain collision, preserving the arena-specific presentation. Gameplay visual validation remains outstanding, including the precise silhouette at intermediate bent poses.

Stage 7 atlas toggles use a constant Array converted to PackedStringArray at configuration. The reused oyster callback now forwards its firing direction. The boulder fade retains the Sakura 2.0 menu's 20-tick timing; its seen flag is saved after the fade completes, including the legacy save bit. Older native saves replay an unrecorded reveal once.

Validation: Godot headless editor/parser loads only. No gameplay or automated tests were run, per AGENTS.md.
