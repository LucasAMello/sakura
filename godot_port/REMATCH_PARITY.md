# Rematch portals and cameras

Checked against old/2 Joguito/Main.cpp map73–79 setup, maps.h rematch rooms and hub portals, and draw.h portal passes.

Hub portals require both PORTAL1 (back) and PORTAL2 (front). The port previously drew only PORTAL2. Both are now drawn at the original positions with the original right-side flips: back Z18, player Z20, front Z22, labels Z23. Rematch arrival and hub-return entry now show the shared complete portal presentation.

| Boss | Map | Player spawn | Camera center | Hub return |
| --- | --- | --- | --- | --- |
| Icy | 74 | 3620,1020 | 3640,960 | 100,1160 |
| First | 75 | 3380,300 | Follows player, clamped X3060–3680 / Y240–320 | 580,1280 |
| Shadow | 76 | 5500,460 | 5640,360 | 1180,1480 |
| Thunder | 77 | 5400,400 | 5600,400 | 1800,1480 |
| Turtle | 78 | 9500,560 | 9640,500 | 2400,1280 |
| Fifth | 79 | 5400,2220 | 5600,2160 | 2880,1160 |

Camera centers come from the original map limits. Rematch-specific camera overrides run from camera creation through arrival, intro, fight and departure, preventing inherited regular-stage callbacks from changing the view. Map75 retains the original wider room's camera movement and current boss tuning.

The hub previously stored portal top-left plus (0,20), placing the left-side returns40px too far left and right-side returns33px too far left. Left return positions match Main.cpp. The right-side source positions (1828,1480), (2428,1280), (2908,1160) overlap their walls by28px with the port's40px-wide collision body. Those three returns now shift28px left onto clear floor. Incoming stored return coordinates are normalized to the nearest portal's safe return point, including rematches already in progress.

Rematches no longer retain inherited regular-stage doors. The icy door sprites are removed from terrain's solid-sprite registry as well. Icy rematch74 uses RGB(0,16,63) background; maps60/61 retain light blue and map62 retains dark blue. Boss platform coordinates, current attack tuning and rewards remain as configured.

Validation: source and asset inspection, followed by the permitted headless Godot editor compile. No gameplay tests run.


Hub portal entry now moves2px each physics tick (120px/second), rather than2px every other tick. It reuses the departure sprite clipping so Sakura disappears progressively at the portal center and the scene changes only when fully inside. The camera stays fixed during this walk. All six return rectangles were inspected against map73: left returns100/580/1180; right returns1800/2400/2880, with floors at1240/1360/1560 according to each portal's height.

Rematch input handoff: completing the arrival portal no longer enables gameplay when the destination state is BOSS_INTRO. Each rematch explicitly starts its boss intro, then its existing readiness/meter completion path enables player control at BOSS. The first rematch also requires a full meter before handoff and caps meter filling at the boss HP. This shared entry correction also covers the final arena's intro without stopping its explicit intro activation.

Right-side hub returns face left. Both portal halves, opening/closing effects, and Sakura's clipped arrival animation are mirrored around her body center; the actual player also retains left facing when control resumes. The three left-side returns retain their right-facing presentation. Safe return coordinates are unchanged.
