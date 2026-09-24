# Sakura complete reference

Open `../Sakura_Complete_Reference.html` in a browser. The generated file is self-contained: artwork, reference text, source snapshots, map data, styling and interactions are embedded. No server, installation or network is required. The card checklist is browser-local and does not read or modify game saves.

The reference covers all 33 campaign maps, seven weapons, seven bosses, six rematches, all regular enemy families and variants, attack and hazard families, 52 cards, controls, persistence, audio, architecture and historical evidence. It identifies differences between current implementation and historical parity notes. Card and elemental boss names use the full card names, including “The”.

Map schematics use each world controller’s non-solid token exclusions. Water-stage slope shapes come from the collision atlas alpha mask. Static schematics omit pass-through tiles, non-solid lethal-floor markers, scripted doors and moving objects. Spawn tables list coordinates and configuration parameters in separate columns. A spatial SVG diagram shows the six rematch portals on map 73, with links to their destination maps.

To regenerate after documentation or game changes, run from the repository root:

```powershell
python docs/build_reference.py
```

`build_reference.py` combines curated descriptions with current source constants, map configurations, card names, coordinates and embedded GDScript. `reference.css` and `reference.js` own presentation and browser interactions. Curated behavior descriptions and boss damage tables need a source review when gameplay changes; regeneration alone does not audit their meaning.

Snapshot: 2026-09-21. No game code or assets were changed. No automated tests, manual tests, browser tests or gameplay sessions were run, in accordance with AGENTS.md.
