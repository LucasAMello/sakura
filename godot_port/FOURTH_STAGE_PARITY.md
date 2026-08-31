# Fourth-stage port record

World 4 covers maps 40–42. The current slice establishes all three authoritative map files and dimensions, the `TEXTURES05` terrain mapping, scenario/foreground separation, the repeating `bg5.bmp` background, water surfaces, underwater player gravity, ordinary transitions from map40 to map41 and map41 to map42, and the canonical ordinary object layouts.

Implemented ordinary objects now include Resetti enemies, hidden seahorse ambush spawners, the four randomized fish variants and pursuit behavior, upper/lower oyster pairs with ballistic black pearls, loose persistent cards, and breakable sand mounds containing cards. Their positions, facing values, and card IDs follow `maps.h`.

The terrain setup follows the `initialize_wall` argument meanings in the canonical source. Types `1` and `2` are decorative layers rather than one- or two-pixel collision widths. Types `10`, `11`, `12`, and `20` remain solid. The six sloped shoreline tokens currently use full-cell collision pending a pixel-mask or slope representation.

Still to port:

- Water bubbles and splash effects
- Map42 checkpoint doors, Icy boss, reward, and stage completion

This file records an intentionally incomplete milestone; it must not be presented as full World 4 parity.
