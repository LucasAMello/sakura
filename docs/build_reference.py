"""Build the offline Sakura reference from curated notes and repository evidence."""
from pathlib import Path
import ast
import base64
import html
import json
import re

ROOT = Path(__file__).resolve().parents[1]
PORT = ROOT / 'godot_port'
OUT = ROOT / 'Sakura_Complete_Reference.html'
E = html.escape

def read(path):
    return (PORT / path).read_text(encoding='utf-8')

def literal(source, name):
    match = re.search(r'const ' + name + r'\s*:?=\s*([\[{])', source)
    if not match:
        return {}
    start = match.start(1)
    stack, quoted, escape = [], False, False
    for end in range(start, len(source)):
        ch = source[end]
        if quoted:
            if escape: escape = False
            elif ch == '\\': escape = True
            elif ch == '"': quoted = False
        elif ch == '"': quoted = True
        elif ch in '[{(': stack.append(ch)
        elif ch in ']})':
            stack.pop()
            if not stack: break
    text = source[start:end+1]
    text = re.sub(r'\b(?:Vector2i?|Rect2)\(([^()]*)\)', r'[\1]', text)
    text = re.sub(r'\btrue\b', 'True', text)
    text = re.sub(r'\bfalse\b', 'False', text)
    return ast.literal_eval(text)

def source(path, label='Read implementation'):
    text = read('scripts/' + path)
    return f'<details class="source"><summary>{E(label)} · {E(path)}</summary><pre><code>{E(text)}</code></pre></details>'

def image(path, alt='', cls='sprite'):
    p = PORT / 'assets' / path
    data = base64.b64encode(p.read_bytes()).decode()
    return f'<img class="{cls}" src="data:image/png;base64,{data}" alt="{E(alt)}" loading="lazy">'

def first_image(script):
    selected = {
        'world2/second_boss.gd': 'world2/boss_ball.png',
        'world6/icy_boss.gd': 'world6/boss_up_3.png',
        'world4/fish.gd': 'world4/fish_1_1.png',
    }
    if script in selected:
        return image(selected[script], script.split('/')[-1].replace('.gd', '').replace('_', ' '))
    matches = re.findall(r'res://assets/([^"\n]+\.png)', read('scripts/' + script))
    return image(matches[0], script.split('/')[-1].replace('.gd', '').replace('_', ' ')) if matches else ''

def table(head, rows):
    return '<div class="table-wrap"><table><thead><tr>' + ''.join('<th>'+x+'</th>' for x in head) + '</tr></thead><tbody>' + ''.join('<tr>'+''.join('<td>'+str(x)+'</td>' for x in row)+'</tr>' for row in rows) + '</tbody></table></div>'

def section(id, eyebrow, title, intro, content):
    return f'<section id="{id}"><div class="section-head"><p class="eyebrow">{eyebrow}</p><h2>{title}</h2><p class="lede">{intro}</p></div>{content}</section>'

BOSS_NAMES = {1: 'The Windy', 2: 'The Shadow', 3: 'The Thunder', 4: 'The Watery', 5: 'The Firey', 6: 'The Freeze', 7: 'Final Boss'}

SPAWN_LABELS = {
    'red_balls': ('Red Ball', ['Direction']), 'springs': ('Happy Spring', ['Initial timer']),
    'turrets': ('Green Turret', ['Direction']), 'birds': ('Pirikito', ['Initial timer']),
    'pumpkins': ('Pumpkin', ['Direction']), 'ghosts': ('Ghost', ['Variant']),
    'paintings': ('Haunted Painting', []), 'armors': ('Haunted Armor', ['Card ID / recovery']),
    'spikes': ('Spike strip', ['Width']), 'mask_spawners': ('Ghost Mask emitter', ['Direction', 'Height span', 'Destination X']),
    'wall_turrets': ('Wall Turret', ['Orientation', 'Initial timer']), 'machines': ('Machine', []),
    'oranges': ('Orange Flyer', ['Initial timer']), 'shockers': ('Shocker', ['Orientation', 'Initial timer']),
    'resettis': ('Resetti', []), 'seahorse_spawners': ('Seahorse emitter', []), 'fish': ('Fish', []),
    'oysters': ('Oyster', ['Direction']), 'sand_mounds': ('Sand mound', ['Card ID']),
    'horizontal_flamethrowers': ('Horizontal flamethrower', ['Direction', 'Initial timer']),
    'vertical_flamethrowers': ('Vertical flamethrower', ['Direction', 'Initial timer']),
    'flamemets': ('Flamemet', ['Direction', 'Ceiling']), 'lava': ('Lava strip', ['Width']),
    'squids': ('Squid', []), 'ice_mets': ('Ice Met', []), 'icicles': ('Icicle', ['Variant']),
    'holder': ('Card holder', ['Card ID']), 'card_holders': ('Card holder', ['Card ID']),
    'ice_holders': ('Ice holder', ['Card ID']), 'ice_blocks': ('One-way ice block', ['Variant']),
}
REUSED_NAMES = {10:'Red Ball',12:'Green Turret',14:'Pirikito',15:'Ghost',21:'Machine',23:'Orange Flyer',33:'Oyster',41:'Floor Flamemet',42:'Ceiling Flamemet',50:'Ice Met',55:'Pumpkin'}

def spawn_table(cfg):
    rows = []
    def add(name, position, parameters='—'):
        rows.append([E(name), position[0], position[1], E(parameters)])
    for key, items in cfg.items():
        if key == 'reused_enemy_spawns_type_x_y_variant':
            for kind,x,y,variant in items:
                add(REUSED_NAMES.get(kind, f'Type {kind}'), [x,y], f'Type: {kind}; configuration value: {variant}')
        elif key == 'ghost_mask_spawners':
            for item in items:
                add('Ghost Mask emitter', item['position'], f'Destination X: {item["destination"]}; height span: {item["span"]}')
        elif key == 'cards':
            for position,a,b in items:
                cid,falls = (b,a) if cfg['world'] <= 3 else (a,b)
                add('The ' + card_names[cid].title(), position, f'Card ID: {cid}; movement: {"falling" if falls else "hovering"}')
        elif key in SPAWN_LABELS:
            name, labels = SPAWN_LABELS[key]
            if key == 'holder' and items: items = [items]
            for item in items:
                if isinstance(item[0], (int,float)):
                    add(name, item)
                elif key == 'oysters':
                    add('Oyster · lower shell', item[0], f'Direction: {item[2]}')
                    add('Oyster · upper shell', item[1], f'Direction: {item[2]}')
                else:
                    values = item[1:]
                    parameters = '; '.join(f'{label}: {str(value).lower() if isinstance(value,bool) else value}' for label,value in zip(labels,values)) or '—'
                    add(name, item[0], parameters)
    return table(['Spawn / object','X','Y','Parameters'],rows) if rows else '<p>No regular enemies or collectibles configured.</p>'

def collision_profile(world):
    script = read(f'scripts/world{world}/stage{world}.gd')
    tokens = literal(script, 'NON_SOLID_TOKENS' if world == 7 else f'STAGE{world}_NON_SOLID')
    profile = {'nonSolid':tokens, 'alphaRects':{}, 'alphaAtlas':''}
    if world == 4:
        rects = literal(script, 'STAGE4_SOURCE_RECTS')
        alpha_tokens = ast.literal_eval(re.search(r'set_alpha_collision_tokens\(PackedStringArray\((\[.*?\])\)',script)[1])
        profile['alphaRects'] = {token:rects[token] for token in alpha_tokens}
        profile['alphaAtlas'] = 'data:image/png;base64,' + base64.b64encode((PORT/'assets/world4/terrain.png').read_bytes()).decode()
    return profile

def portal_schematic(cfg, portals, profile):
    tokens = (PORT/'maps/map73.map').read_text(encoding='latin-1').split()
    shapes = []
    for y in range(cfg['height']):
        x = 0
        while x < cfg['width']:
            if tokens[y*cfg['width']+x] in profile['nonSolid']:
                x += 1
                continue
            start = x
            while x < cfg['width'] and tokens[y*cfg['width']+x] not in profile['nonSolid']: x += 1
            shapes.append(f'<rect x="{start*20}" y="{y*20}" width="{(x-start)*20}" height="20"/>')
    svg = '<div class="portal-diagram"><svg viewBox="-40 -70 3080 1750" role="img" aria-labelledby="portal-title portal-desc" xmlns="http://www.w3.org/2000/svg"><title id="portal-title">Map 73 rematch portal positions</title><desc id="portal-desc">Spatial layout of the six portals: The Freeze, The Windy, The Shadow, The Thunder, The Watery and The Firey. Select a label to open its map entry.</desc><rect x="0" y="0" width="3000" height="1600" fill="#edf0e9"/><g fill="#385665" opacity=".4">'+''.join(shapes)+'</g>'
    svg += '<g font-family="Segoe UI,Arial,sans-serif"><text x="70" y="-18" font-size="42" fill="#233c48">MAP 73 · 3000 × 1600 px</text><circle cx="0" cy="240" r="16" fill="#466b60"/><text x="60" y="230" font-size="38" fill="#233c48">Entry (0, 240)</text>'
    for index,(pos,world,destination) in enumerate(portals):
        x,y = pos
        label_x = 20 + index * 504
        label_y = y-235
        name = BOSS_NAMES[world]
        svg += f'<a href="#map-{destination}" aria-label="{name}, map {destination}, position {x}, {y}"><path d="M{x} {y} L{label_x+215} {label_y+165}" stroke="#c85f7e" stroke-width="7"/><circle cx="{x}" cy="{y}" r="22" fill="#c85f7e" stroke="#fff" stroke-width="5"/><rect x="{label_x}" y="{label_y}" width="430" height="165" rx="14" fill="#fffefb" stroke="#c85f7e" stroke-width="3"/><text x="{label_x+22}" y="{label_y+52}" font-size="43" fill="#233c48">{name}</text><text x="{label_x+22}" y="{label_y+98}" font-size="36" fill="#466b60">Map {destination}</text><text x="{label_x+22}" y="{label_y+139}" font-size="31" fill="#65747b">({x}, {y})</text></a>'
    svg += '<circle cx="1500" cy="1260" r="18" fill="#d29e38" stroke="#fff" stroke-width="4"/><text x="1500" y="1030" text-anchor="middle" font-size="38" fill="#233c48">Medium recovery</text><text x="1500" y="1075" text-anchor="middle" font-size="31" fill="#65747b">(1500, 1260)</text><path d="M1500 1090 V1240" stroke="#d29e38" stroke-width="5"/></g></svg></div><p class="caption">Positions use map coordinates. Select a portal label to open the rematch map. Pink: portals · gold: recovery · green: entry.</p>'
    return svg

world_names = ['Wind', 'Shadow', 'Thunder', 'Water', 'Fire', 'Ice', 'Final stage']
world_notes = [
    ('Outdoor platforms and vertical rooms', 'Five rooms alternate long outdoor stretches with a descent and a climb. Red Balls establish ledge patrols; springs and birds add vertical threats. Pumpkins cannot be killed. The last room leads through two doors and a playable checkpoint before the falling-block bird entrance.', 'Long gaps require controlled jumps. Pumpkin stun duration is 120 ticks. Both vertical maps contain cards outside the direct exit route.'),
    ('The haunted castle', 'A short exterior leads into a dark castle. Ghosts wake when approached, masks arrive from emitters, and armor hides recoveries or cards. Map22 adds spike-lined vertical traversal; map23 combines a long spike bed with the The Shadow checkpoint and arena.', 'Wait for ghosts to activate before shooting. Strike armor while its eyes are visible; inspect both high and low routes for cards.'),
    ('Industrial platforms and electrical hazards', 'Wall turrets, missile machines, airborne Orange enemies and four-direction Shockers form overlapping firing lanes. Map31 is a tall interior route. Map32 ends in the The Thunder checkpoint and arena.', 'Water is effective against machines and Shockers. Watch missile paths and the charge before each electrical launch.'),
    ('Shoreline & submerged passages', 'Three broad rooms combine shore slopes, water surfaces, fish schools, emerging seahorses and pearl-firing oysters. Sand mounds conceal cards. Water changes Sakura’s jump/fall behavior; the final room ends at The Watery’s two-door checkpoint.', 'Thunder deals 4 damage to fish and seahorses. Explore behind the starting position in map40. Sand mounds can be broken with shots.'),
    ('The furnace', 'A vertical descent opens into a long lava corridor, a climb, and a deep final shaft. Horizontal and vertical flamethrowers, floor and ceiling Flamemets, and lava-dwelling squids demand timed movement. Map53 uses a checkpoint shaft.', 'Water deals 3 damage to Flamemets and squids. Leave room for rising squid attacks. Lava deals 4 damage. Foreground strips have collision disabled.'),
    ('Frozen halls', 'Ice Mets burst into seven needles on defeat. Ceiling icicles fall into the route, spike strips guard gaps, pumpkins reappear and ice holders conceal cards. Map62 descends toward the The Freeze checkpoint and a boss arena with raised floor caps.', 'Bring Fire to melt ice holders and exploit The Freeze’s weakness. Step away from dying Ice Mets. Ice spikes deal 20 damage, enough to kill at the maximum normal HP.'),
    ('Final-stage progression', 'Maps70–72 remix enemies from the elemental worlds. Map73 is a six-portal rematch hub. The original six bosses return without card rewards; the sixth victory routes directly to map80 and the final encounter.', 'The route combines multiple enemy families and projectile interception rules. Rematch completion lasts only for the current final-stage run. Map80 restores maximum HP and accepts only the basic weapon as boss damage.')
]

entities = [
 ('world1/red_ball.gd','Red Ball','Enemy','Patrols horizontally and turns at walls or missing ground. Current movement is 1.5 pixels per physics tick (90 px/s).','Small recovery: 1/3 chance.','Keep a level firing lane; it has 5 HP.'),
 ('world1/happy_spring.gd','Happy Spring','Enemy','A spring-bodied enemy alternates its compressed and extended forms and jumps through its timed movement cycle.','Small recovery when enabled by its inherited drop rule.','Its collision body changes height during the jump cycle.'),
 ('world1/green_turret.gd','Green Turret','Enemy','Stationary directional gun. Fires every 120 physics ticks; its projectile deals 4 damage and survives player fire.','25% medium recovery; 10% extra life; 65% none.','Contact deals 5 damage. Attack from range and jump the shot.'),
 ('world1/pirikito.gd','Pirikito','Enemy','Flying bird uses a repeating velocity state machine with ascent, turn and descent; spawn timers stagger groups.','See inherited drop flag in implementation.','Lead its flight path; only 3 HP.'),
 ('world1/pumpkin.gd','Pumpkin','Enemy','Patrols at 2.5 px/tick and chases at 5. Hits apply a 120-tick stun. HP remains unchanged.','No kill drop.','Each hit provides a two-second stun window.'),
 ('world2/ghost.gd','Ghost','Enemy','Dormant, nearly transparent ghosts have no hit rectangle. Within 300 horizontal pixels and its vertical detection band, the ghost wakes, accelerates toward Sakura and becomes hittable. It slows and fades back to rest when far away.','Small recovery: 1/3 chance.','Its active pursuit can follow both axes. Shooting the dormant silhouette does nothing.'),
 ('world2/ghost_mask.gd','Flying Ghost Mask','Enemy','Emitters launch directional masks at randomized heights. They oscillate while crossing their configured route, then fade out.','20% small recovery; 10% extra life in the current roll function.','Shoot through the narrow body and allow for vertical oscillation.'),
 ('world2/stage2_armor.gd','Haunted Armor','Container','Eyes animate when Sakura approaches. One accepted hit while the eyes are visible starts the break sequence; it releases a card or recovery and leaves an inert shell.','Configured card ID greater than 5, otherwise recovery.','No contact damage. Check each suit for a hidden card.'),
 ('world2/stage2_painting.gd','Haunted Painting','Scenery','Player proximity triggers a one-shot visual transformation/reversion. Its animation follows Sakura’s movement pace.','None.','Animated scenery with no enemy health or damage handler.'),
 ('world2/shadow_clone.gd','Shadow Clone','Boss component','Created during The Shadow’s split phase. It bounces independently but sends received damage to the original boss’s shared health pool.','None.','Wind deals 3 damage through the shared boss health handler.'),
 ('world3/wall_turret.gd','Wall Turret','Enemy','Mounted guns use orientation and initial timer values from each map. They fire paired directional projectiles.','See base drop settings.','Check floor, wall and ceiling positions; orientation changes the firing lane.'),
 ('world3/machine.gd','Machine','Enemy','Heavy 12-HP machine chooses attacks, including accelerating missiles, and uses a dedicated destruction effect. Water overrides direct-hit damage to 3.','Two sequential 25% medium-recovery rolls: 43.75% total.','Its missiles block ordinary shots and survive. Water shortens the fight.'),
 ('world3/orange_enemy.gd','Orange Flyer','Enemy','Flying body with a separate propeller, vertical bobbing and player-relative aiming states. Fires from direction-specific origins.','Small recovery: 1/3 chance.','Shot direction depends on the player-relative aiming state.'),
 ('world3/shocker.gd','Shocker','Enemy','Four mount orientations share charge, launch and retract phases. Its stationary charge blocks shots; the launched shock ball does not. Water deals 3.','See base drop settings.','Wait for the charge/retract rhythm or shoot from a safe side.'),
 ('world4/resetti.gd','Resetti','Enemy','Emerges from the ground when Sakura faces it at the configured short range, holds, then retracts. The exposed hitbox grows with the visible body.','None.','One hit defeats it, but it cannot be hit while fully hidden.'),
 ('world4/seahorse.gd','Seahorse','Enemy','Proximity spawner creates a rising ambush. It shows its head, faces Sakura, holds upright, spins, then dashes. Thunder deals 4.','See base drop settings.','Expect a dash after the emergence tell; one Thunder hit exceeds its 3 HP.'),
 ('world4/fish.gd','Fish','Enemy','Fish accelerate toward Sakura using asymmetric detection distances and braking when reversing. Thunder deals 4 damage per hit.','See base drop settings.','Avoid becoming surrounded by a school. Thunder defeats a 3-HP fish in one hit.'),
 ('world4/oyster.gd','Oyster · upper shell','Enemy','Opens and closes with direction-dependent rotation and offset. Fires pearls; the upper shell is a separate enemy from its lower base.','See base drop settings.','Aim at the upper shell. Pearls survive shots and can shield it.'),
 ('world4/oyster_lower.gd','Oyster · lower shell','Scenery','Separate lower shell with zero contact damage. Its projectile-hit handler ignores damage.','None.','Its nominal 1 HP is unused because the hit handler ignores damage.'),
 ('world5/flamemet.gd','Flamemet · floor / ceiling','Enemy','Both variants have 5 HP. Floor units patrol and turn at edges; ceiling variants also release falling fire. Main Water shots deal 3 to both. Water splash deals 3 to floor units but only 1 to ceiling units.','See base drop settings.','Watch the ceiling variant while crossing platforms; its falling fire cannot be shot.'),
 ('world5/squid.gd','Lava Squid','Enemy','Rises from lava with a staged velocity arc and surface clipping, then retreats. Water deals 3, matching its full HP.','See base drop settings.','Attack when exposed and leave space for the jump trajectory.'),
 ('world6/ice_met.gd','Ice Met','Enemy','Patrols frozen platforms. Defeat emits seven directional ice needles from its position.','Needle burst on death; recovery follows its configured drop rule.','Stay out of the death burst even after the body disappears.'),
 ('world6/ice_pumpkin.gd','Ice-stage Pumpkin','Enemy','Reused pumpkin behavior in Ice and the final stage. Hits apply a 120-tick stun. The enemy remains active after recovery.','No kill drop.','Use the stun window to move past it.'),
]

hazards = [
 ('world1/enemy_projectile.gd','Green-turret shot','4','Directional projectile with a three-frame impact explosion. Blocks shots and survives.'),
 ('world1/boss_feather.gd','Bird feather','3','Fast, collision-substepped feather. Blocks shots and survives.'),
 ('world1/boss_room_block.gd','Falling arena block','Scripted','Map14 introduction scenery; falling blocks construct the arena presentation before the bird fight.'),
 ('world2/shadow_spike.gd','Shadow spike strip','20','Continuous ground hazard; cannot be cleared with weapons.'),
 ('world3/world3_projectile.gd','Electrical-stage projectile family','0 / 2 / 3 / 4','Eight kinds: wall shot, machine shot, Orange shot, missile, Shocker charge, shock ball, boss lightning and boss beam. Ordinary gunfire deals 2; missiles 4; shock balls and boss beams 3. Charge and boss-lightning presentation initialize with zero damage and no body area; their projectile-blocking rules are separate. See configure() for each branch.'),
 ('world4/oyster_pearl.gd','Oyster pearl','2','Fired behind the shell; blocks player projectiles and survives.'),
 ('world4/water_shot.gd','The Watery water jet','3','Segmented expanding jet with a moving front and retracting tail. Blocks shots; cannot be destroyed.'),
 ('world5/flamethrower.gd','Flamethrower · horizontal / vertical','0 body','Indestructible emitter. Timing and direction are configured per spawn. Creates a separate damaging flame burst.'),
 ('world5/flame_burst.gd','Flame burst · horizontal / vertical','3','Timed 90×58 or 58×90 flame. Shots pass through; wait for the cycle to finish.'),
 ('world5/falling_fire.gd','Falling Flamemet fire','2','Falls from ceiling Mets, then changes to its ground-impact form. Player shots pass through.'),
 ('world5/lava_strip.gd','Lava','4','Damaging surface strip. Foreground-only strips have no damage collision.'),
 ('world5/boss_projectile.gd','The Firey attack family','2 / 7 / 3','Spray deals 2 and can be destroyed. Hadouken deals 7; straight and rising slashes deal 3. Hadouken and slashes block shots and survive. Impact animation no longer intercepts.'),
 ('world6/icicle.gd','Icicle · two sizes','3','Proximity-triggered falling hazards. They preserve source acceleration overshoot, terrain grace and landing linger. Indestructible shot blockers.'),
 ('world6/ice_spike.gd','Ice spike strip','20','Fixed strip, normally lethal even with all 52 cards. Ignores player projectiles.'),
 ('world6/ice_needle.gd','Ice Met needle · four sprites','1','Seven needles scatter on an Ice Met’s death, using four directional sprite shapes. Destructible.'),
 ('world6/icy_attack.gd','The Freeze attack · five variants','3','Direction-specific attack sprites and collision shapes. Blocks shots and ignores damage.'),
 ('world7/final_boss_projectile.gd','Final-boss attacks · types75–79','3','Target ball, vertical lightning, left/right fire and directional ice. Ball/lightning block Fire, Ice and Water splashes; other main shots pass through. Fire/ice attacks block shots and survive.'),
]

bosses = [
 ('world1/first_boss.gd','The Windy',1,'Ice',4,'Entry → hover → rise → delayed dash passes → platform landing → feathers. Becomes vulnerable after its opening hover. The two platforms alternate its attack direction.','Dodge horizontal dashes and fire while it is reachable. Ice deals eight times the ordinary per-hit boss damage.'),
 ('world2/second_boss.gd','The Shadow',2,'Wind',3,'Turning silhouette → transformation → meter fill → bouncing ball → split into two. Both bodies share health. Only ACTIVE and ACTIVE_SPLIT accept damage.','Track both bounce paths after the split. Wind pierces and applies the special 3-point damage to boss and clone.'),
 ('world3/third_boss.gd','The Thunder',3,'Shadow',4,'Flicker → crouch → dash → wait → takeoff. High-health attacks use shock balls; low-health attacks use randomized beams. Only visible The Thunder body frames accept damage.','Use the bouncing Shadow shot during visible body phases; avoid wasting it on beam or invisible states.'),
 ('world4/fourth_boss.gd','The Watery',4,'Thunder',2,'Alternates directional water jets and shell dashes; low health enables rapid shooting, rapid dashes and chained recovery. Waiting and intro states are invulnerable.','Jump its dash lane and avoid the growing jets. Thunder is the weakness but still requires 15 successful hits from full health.'),
 ('world5/fifth_boss.gd','The Firey',5,'Water',3,'Intro → idle → randomized spray, Hadouken or slash attacks. Vulnerable after the intro. Its attack family includes straight and rising slashes.','Prioritize dodging the 7-damage Hadouken. Water is effective; the impact splashes can also use the boss’s Water damage handler.'),
 ('world6/icy_boss.gd','The Freeze',6,'Fire',4,'Shadow and rising introduction → center attack → bottom dash → descent → high/mid/low side emergence. Attack patterns depend on health. Only the fight’s exposed damage forms accept damage.','Wait for a visible vulnerable emergence, then use Fire. Its attacks and body can emerge near the walls.'),
 ('world7/final_boss.gd','Final Boss',7,'Basic only',0.5,'Seven choices: target balls, left/right lightning, left/right fire and left/right ice. Fades between fixed attack positions and never chooses the exact same state consecutively.','Use weapon 1. Continue firing during vulnerable appearances: the current file comments out the assignment that would enforce one hit per appearance.'),
]

maps = {}
for w in range(1,8):
    file = f'world{w}/stage{w}.gd'
    for n, cfg in literal(read('scripts/' + file), 'MAP_CONFIGS').items():
        maps[n] = dict(cfg, world=w, source=file)
    if w == 7:
        for constant, label in [('SPAWNS', 'reused_enemy_spawns_type_x_y_variant'), ('SEAHORSE_SPAWNERS', 'seahorse_spawners'), ('GHOST_MASK_SPAWNERS', 'ghost_mask_spawners')]:
            for n, spawns in literal(read('scripts/' + file), constant).items():
                maps[n][label] = spawns
for w in range(1,7):
    file = f'world7/rematch_world{w}.gd'
    for n,cfg in literal(read('scripts/'+file), 'REMATCH_CONFIGS').items():
        maps[n] = dict(cfg, world=w, source=file, rematch=True)
for n,cfg in literal(read('scripts/world7/stage80.gd'), 'FINAL_CONFIGS').items():
    maps[n] = dict(cfg, world=7, source='world7/stage80.gd')

card_names = re.findall(r'card_([a-z]+)\.png', read('scripts/hud/hud.gd').split('const CARD_RANKS')[0])
locations = {i:[] for i in range(52)}
for i,n in enumerate([14,23,32,42,53,62]):
    locations[i].append((n,'Boss reward',None))
for n,cfg in maps.items():
    for item in cfg.get('cards',[]):
        cid, falls = (item[2],item[1]) if cfg['world'] <= 3 else (item[1],item[2])
        locations[cid].append((n,'Loose · '+('falling' if falls else 'hovering'),item[0]))
    for key,label in [('holder','Breakable holder'),('card_holders','Breakable holder'),('ice_holders','Ice holder · Fire required'),('sand_mounds','Sand mound'),('armors','Haunted armor')]:
        items=cfg.get(key,[])
        if key=='holder' and items: items=[items]
        for pos,cid in items:
            if cid > 5: locations[cid].append((n,label,pos))

parts=[]
parts.append(section('guide','01 / PLAYER MANUAL','Player manual','Controls, campaign progression, movement, combat and recovery.',
    '<div class="two-col"><article><h3>Campaign progression</h3><p>New Game opens with a dream and Sakura falling toward an island. Select any of six elemental worlds, defeat its boss, collect a boss card and gain a new weapon. Collect all six boss cards to uncover the final stage; survive its mixed enemies and six rematches, then defeat the final boss to reach the ending and credits.</p><p>This reference documents the canonical campaign and the current Godot port. Tactical guidance is derived from the implemented behavior.</p><h3>Initial state and respawn</h3><p>Start with 5 lives, 15 maximum HP, weapon 1 and no cards. Entering a world heals to maximum and selects weapon 1. HP carries between ordinary maps. Dying reloads the current map, using its boss checkpoint when active, and resets the selected weapon. Life exhaustion occurs when the counter falls below zero; game over returns to stage select and restores the five-life session.</p></article><article><h3>Movement & combat</h3><p>Sakura has a 40×80 collision body and a normal horizontal speed cap of 4 pixels per 60 Hz tick. Hold jump to extend ascent; releasing it cuts the jump. Water changes ascent and falling behavior. Weapons have unlimited ammunition. Cooldowns, projectile completion and active-shot accounting govern firing.</p><p>Damage normally subtracts HP and grants 80 physics ticks (about 1.33 seconds) of immunity. Small recovery restores 1 HP, medium recovery 3 HP; extra lives cap at 9. Lethal terrain and falling out of the map can kill directly.</p><p>Portals mark world entrance, exit and checkpoint revival. Ordinary room transitions use neither a portal nor READY. Boss doors lead through a playable checkpoint room in Worlds 1–4 and 6; Fire uses a shaft checkpoint.</p></article></div>'
    + table(['Default input','Action'],[['← / →','Move; arrows also navigate menus'],['F','Jump / confirm; intro skip after opening hold'],['D','Fire'],['A / S','Previous / next unlocked weapon'],['1–7','Select an unlocked weapon directly'],['Enter','Confirm / pause / resume'],['Escape','Back in menus; use pause Exit to leave a stage'],['F3 / R','Compatibility display / development map reload']])
    + '<p class="note">Controls are remappable in Options. Weapon selection is blocked while firing and cannot bypass an active firing cycle. Pause includes weapons, lives, the card book, audio, control rebinding and exit to stage select.</p>'
    + source('player/player.gd','Player movement, firing and damage')))

weapon_rows=[
 ('Basic','Always available',1,'9 px/tick · 540 px/s','Release ≥10 ticks; or ≥25 ticks with no counted shots','Straight small projectile; 480-pixel horizontal distance limit.'),
 ('Wind','The Windy / card 0',2,'6.25 px/tick · 375 px/s','Reset at 50 ticks','Pierces enemies once per target and passes through enemy attacks; stops on terrain.'),
 ('Shadow','The Shadow / card 1',3,'5 horizontal + 3 vertical px/tick','Locked until projectile finishes','Bounces independently on horizontal and vertical terrain collision; one continuing shot controls the lock.'),
 ('Thunder','The Thunder / card 2',2,'5 px/tick · 300 px/s','Release ≥35 ticks; or ≥50 with no counted shots','Straight animated shot; 4 damage against fish and seahorses.'),
 ('Water','The Watery / card 3',1,'5 horizontal; initially −1 vertical px/tick','Reset at 40 ticks','Arcing projectile; vertical displacement increases by 1 every 12 ticks. Impact releases two damaging splashes.'),
 ('Fire','The Firey / card 4',3,'8 px/tick · 480 px/s','Reset at 70 ticks','Straight flame with expanding impact frames. Melts Ice holders.'),
 ('Ice','The Freeze / card 5',2,'Accelerates to 10 px/tick · 600 px/s','Reset at 50 ticks','Accelerating ice projectile, symmetric left/right speed cap, decorative ice debris on impact.')]
weapon_html='<p>Numbers below are current port values. One physics tick is 1/60 second. The next shot starts on the input tick after the firing cycle resets. Only Basic and Thunder increment the shared four-shot counter. Water, Fire and Ice support multiple simultaneous projectiles.</p><div class="weapon-grid">'
for i,(name,unlock,dmg,speed,cycle,desc) in enumerate(weapon_rows,1):
    pic='player/player_fire_idle.png' if i==1 else f'player/weapon{i}_{name.lower()}/fire_idle.png'
    weapon_html+=f'<article class="weapon searchable" data-world="all"><div class="weapon-top">{image(pic,name)}<span class="number">0{i}</span></div><h3>{name}</h3><p class="tag">{unlock}</p><p>{desc}</p><dl><dt>Ordinary direct damage</dt><dd>{dmg}</dd><dt>Motion</dt><dd>{speed}</dd><dt>Firing cycle</dt><dd>{cycle}</dd></dl></article>'
weapon_html+='</div><h3>Elemental exceptions</h3>'+table(['Target','Effective weapon','Damage'],[['Machine / Shocker','Water','3'],['Floor / ceiling Flamemet','Water direct shot','3'],['Floor Flamemet / Machine / Shocker / Squid','Water splash','3'],['Ceiling Flamemet','Water splash','1'],['Squid','Water direct shot','3'],['Fish / Seahorse','Thunder','4']])
weapon_html+='<p>Water splashes otherwise deal 1 and disappear on their first hit; they do not consume additional shot slots. Wind hits each enemy at most once per projectile. Weapons 2–7 end beyond 640 horizontal pixels from Sakura or at 240 physics ticks, with additional map-bound checks. Shadow also has vertical cleanup bounds of −480/+560 pixels. Bosses use their own damage values.</p>'+source('player/weapon_projectile.gd')+source('player/weapon_impact_particle.gd','Water splash and Ice debris')
parts.append(section('weapons','02 / ARSENAL','Weapons','Unlimited ammunition, distinct trajectories and an elemental weakness cycle.',weapon_html))

boss_html='<div class="callout"><strong>Weakness route</strong><p>The Windy → The Shadow → The Thunder → The Watery → The Firey → The Freeze → The Windy.</p><p>Each arrow connects a boss to the target vulnerable to its weapon reward. All six worlds are selectable at the start, so the first fight uses Basic unless progress already unlocks another weapon.</p></div>'
boss_html+=table(['Boss · 30 HP each','Basic','Wind','Shadow','Thunder','Water','Fire','Ice'],[
 ['The Windy',0.5,0.5,0.5,0.5,0.5,0.5,4],['The Shadow',0.5,3,0.5,0.5,0.5,0.5,0.5],['The Thunder',0.5,0.5,4,0.5,0.5,0.5,0.5],['The Watery',0.5,0.5,0.5,2,0.5,0.5,0.5],['The Firey',0.5,0.5,0.5,0.5,3,0.5,0.5],['The Freeze',0.5,0.5,0.5,0.5,0.5,4,0.5],['Final Boss',0.5,'Immune','Immune','Immune','Immune','Immune','Immune']])
boss_html+='<p class="note">Damage per accepted direct hit in the current <code>take_weapon_hit</code> path, including Basic. Nominal weak-hit counts from 30 HP: The Windy 8, The Shadow 10, The Thunder 8, The Watery 15, The Firey 10, The Freeze 8; Basic requires 60. These exclude missed or invulnerable hits. Rematches reuse these handlers.</p><div class="boss-grid">'
for script,name,w,weak,dmg,behavior,tip in bosses:
    name = BOSS_NAMES[w]
    s=read('scripts/'+script); contact=re.search(r'contact_damage = (\d+)',s)[1]
    boss_html+=f'<article class="boss searchable" data-world="{w}"><div class="boss-art">{first_image(script)}</div><div><p class="eyebrow">WORLD {w} / BOSS</p><h3>{name}</h3><p class="tag">30 HP · contact {contact} · {weak}: {dmg} damage</p><p>{behavior}</p><p class="tip">{tip}</p></div>{source(script)}</article>'
boss_html+='</div><h3>Final-boss attack sequence</h3>'+table(['Attack state','Pattern'],[['Target','Spawns a ball at Sakura’s position every 15 boss updates (1 second at 15 Hz). Its short charge gives a repositioning cue.'],['Lightning left / right','Screen flash at updates 25–28; lightning every 10 updates thereafter in randomized lanes excluding the current boss lane.'],['Fire left / right','Six spawns at updates 25,29,33,39,45,51. The current boss waits for all six orbit-completion signals before fading out.'],['Ice left / right','Five-way opening at update 25, followed by 14 player-height-selected shots at updates 60,70,80,86,96,106,120,130,140,150,160,165,180,190.']])
boss_html+='<p>Final-boss decisions run every 4 physics ticks. Fade-out recovery uses 50 boss updates normally and 90 after Fire. Ball logic, fire motion, ice motion and lightning presentation use separate update paths.</p>'
parts.append(section('bosses','03 / BOSS REFERENCE','Bosses','Seven bosses, six rematches, damage tables and phase behavior.',boss_html))

enemy_html='<p>HP and contact values are read from initialization. Invulnerability and stun handlers override nominal HP values. Combat notes are derived from the implementation.</p><div class="catalog">'
for script,name,kind,behavior,drop,tip in entities:
    s=read('scripts/'+script); hp=re.search(r'hit_points = (\d+)',s); dmg=re.search(r'contact_damage = (\d+)',s)
    if 'See base drop settings.'==drop or 'See inherited drop flag' in drop or 'when enabled' in drop or 'recovery follows' in drop:
        drop=('Small recovery: 1/3 chance via the shared enemy rule.' if 'drops_recovery = true' in s else 'No recovery drop enabled by this script.') + (' Seven needles are emitted on defeat.' if 'ice_met' in script else '')
    enemy_html+=f'<article class="entity searchable" data-world="{script[5]}"><div class="entity-heading"><div class="specimen">{first_image(script)}</div><div><p class="eyebrow">WORLD {script[5]} / {kind}</p><h3>{name}</h3><p class="tag">'+(f'HP {hp[1]} · contact {dmg[1]}' if hp and dmg else 'Scripted object')+f'</p></div></div><p>{behavior}</p><p><strong>Drop:</strong> {drop}</p><p class="tip">{tip}</p>{source(script)}</article>'
enemy_html+='</div>'
parts.append(section('enemies','04 / ENEMY CATALOG','Enemies','Every regular enemy family, both Flamemet variants, the Shadow clone and interactive castle objects.',enemy_html))

hazard_html='<div class="catalog">'
for script,name,damage,desc in hazards:
    hazard_html+=f'<article class="entity searchable" data-world="{script[5]}"><div class="entity-heading"><div class="specimen">{first_image(script)}</div><div><p class="eyebrow">WORLD {script[5]} / HAZARD & ATTACK</p><h3>{name}</h3><p class="tag">Damage: {damage}</p></div></div><p>{desc}</p>{source(script)}</article>'
hazard_html+='</div><div class="callout"><strong>Projectile interception</strong><p>Interception consumes the player projectile. Damage and destruction depend on the target’s collision handler. Wind passes through enemy attacks and ends on terrain.</p></div>'
hazard_html+=table(['Interaction','Attacks'],[['Blocks shots; survives','Turret shot, feather, missile, Shocker charge, Thunder lightning/beam, pearl, The Watery jet, Hadouken, slashes, icicles, The Freeze attack, final fire/ice'],['Destructible','Spray and Ice Met needles'],['Player shots pass through','Wall / machine / Orange gunfire, shock ball, flamethrower flame, falling fire'],['Weapon-dependent','Final ball and lightning block Fire, Ice and Water splashes; other main shots pass through']])+source('shared/projectile_interception.gd')
parts.append(section('hazards','05 / PROJECTILES & HAZARDS','Projectiles','Hazards, enemy projectiles, boss attacks, contact damage and interception.',hazard_html))

map_hints={10:'Outdoor opening; holder above the route.',11:'Vertical descent with paired turrets.',12:'Long outdoor route introduces pumpkins.',13:'Vertical climb; two loose cards.',14:'Approach, checkpoint and falling-block boss introduction.',20:'Short castle exterior.',21:'Castle corridor with painting and armor.',22:'Tall spike-lined castle interior.',23:'Long spike crossing and The Shadow checkpoint.',30:'Long industrial opening.',31:'Vertical machine room with dense Shocker mounts.',32:'Turret corridor and The Thunder checkpoint.',40:'Shoreline; a card lies left of the start.',41:'Begins underwater and exits near the top.',42:'Water route, repeated card IDs and The Watery checkpoint.',50:'Vertical furnace descent.',51:'Long lava route with alternating flame emitters.',52:'Vertical climb toward a high card.',53:'Multi-level furnace and deep boss shaft.',60:'Ice approach; first Fire-only holder.',61:'Wide frozen route with multiple elevations.',62:'Descending route, ice holders and The Freeze checkpoint.',70:'Wind, Shadow and Thunder enemy mix.',71:'Thunder, Water, Fire and Ice enemy mix.',72:'Longest final-stage traversal; mixed ambushes.',73:'Six-portal hub and medium recovery at (1500,1260).',74:'The Freeze rematch.',75:'The Windy rematch.',76:'The Shadow rematch.',77:'The Thunder rematch.',78:'The Watery rematch.',79:'The Firey rematch.',80:'Final arena; full HP is restored on entry.'}
map_html='<p>Map dimensions are logical pixels (20 pixels per tile). Coordinates use the map’s top-left origin, with positive Y downward. Expand a map for spawn coordinates and its static tile collision schematic. Non-solid and decorative tiles are omitted using the owning world controller’s collision rules. Water-stage slopes use the atlas alpha mask. Scripted doors and moving objects are excluded from static tile geometry.</p>'
for w in range(1,8):
    a,b,c=world_notes[w-1]
    map_html+=f'<article class="world searchable" data-world="{w}" id="world-{w}"><div class="world-banner">{image(f"world{w}/background.png",world_names[w-1],"world-background")}<div><p class="eyebrow">WORLD 0{w}</p><h3>{world_names[w-1]}</h3><p>{a}</p></div></div><p>{b}</p><p class="tip">{c}</p>'
    for n,cfg in sorted(maps.items()):
        if (w==7 and n>=70) or (w<7 and cfg['world']==w and n<70):
            loc=[]
            for cid,ls in locations.items():
                for mn,kind,pos in ls:
                    if mn==n: loc.append(f'<a href="#card-{cid}">{cid:02} The {card_names[cid].title()}</a> · {kind}'+(f' at {tuple(pos)}' if pos else ''))
            nexttxt=str(cfg['next']) if cfg['next'] else ('Hub73 / final80 after last victory' if cfg.get('rematch') else ('Six rematches' if n==73 else ('Ending' if n==80 else 'Boss → stage select')))
            map_html+=f'<details class="map searchable" data-world="{w}" id="map-{n}"><summary><span class="map-id">{n}</span><strong>{map_hints[n]}</strong><span class="map-size">{cfg["width"]*20:,} × {cfg["height"]*20:,}</span></summary><div class="map-body"><p>Start: {tuple(cfg["start"])} · Exit rectangle: {cfg["exit"] or "Scripted"} · Next: {nexttxt}</p><p>'+('<br>'.join(loc) if loc else 'No new collectible card IDs in this map.')+f'</p><div class="map-controls"><button type="button" class="draw-map" data-map="{n}">Show tile schematic</button><label>Scale <select class="map-scale" data-map="{n}"><option value="0.1">10%</option><option value="0.25">25%</option><option value="0.5">50%</option><option value="1">100%</option></select></label></div><div class="canvas-scroll"><canvas id="canvas-{n}" hidden aria-label="Map {n} tile schematic"></canvas></div><p class="caption">Navy: solid tile geometry · green: start · gold: card and container positions. Pass-through tiles and non-solid lethal-floor markers are omitted.</p><details class="spawn-list"><summary>Spawn coordinates and parameters</summary>{spawn_table(cfg)}</details><details class="raw-config"><summary>Raw map configuration</summary><pre>{E(json.dumps(cfg,indent=None,ensure_ascii=False))}</pre></details></div></details>'
    map_html+='</article>'
map_html+='<h3>Rematch hub schematic</h3>'+portal_schematic(maps[73], literal(read('scripts/world7/stage7.gd'),'PORTALS'), collision_profile(7))
map_html+='<p>Rematches retain the owning boss controller’s tuning and carry HP back through the hub. Boss reward cards are suppressed. The sixth rematch victory automatically opens map80. Re-entering the final stage clears the rematch checklist. The hub spawns a medium recovery pickup on load.</p>'+source('world7/stage7.gd','Final-stage mixed spawn tables and portal logic')
parts.append(section('stages','06 / WORLD ATLAS','Stages and maps','33 campaign maps: 22 elemental rooms, three final corridors, a hub, six rematches and the final arena.',map_html))

card_html='<div class="callout"><strong>Card progression</strong><p>Only boss cards 0–5 unlock weapons. Other cards contribute to completion and maximum HP. Crossing an HP threshold raises the maximum without healing current HP.</p></div>'+table(['Collected','0–9','10–19','20–29','30–39','40–51','52'],[['Maximum HP',15,16,17,18,19,20]])
card_html+='<p>Card IDs below follow save-system ordering. Map 42 repeats The Mirror (30) and The Sand (36) IDs found in map 41; collecting either location suppresses its duplicate. Checkboxes store collection progress in browser-local storage.</p><p id="check-status" role="status">0 / 52 marked in this browser</p><button id="clear-checklist" type="button">Clear browser checklist</button><div class="card-grid">'
for cid,name in enumerate(card_names):
    ls=locations[cid]; w=maps[ls[0][0]]['world'] if ls else 0
    rows=''.join(f'<li><a href="#map-{n}">Map {n}</a> · {kind}'+(f'<br><span class="coords">({pos[0]}, {pos[1]})</span>' if pos else '')+'</li>' for n,kind,pos in ls)
    card_html+=f'<article class="collectible searchable" data-world="{w}" id="card-{cid}"><label><input type="checkbox" data-card="{cid}"><span class="eyebrow">CARD {cid:02}</span></label><h3>The {name.title()}</h3><ul>{rows or "<li>No location extracted; inspect the source.</li>"}</ul></article>'
card_html+='</div><h3>Containers and support objects</h3>'+table(['Object','Rule'],[['Card holder','Breakable container used in Wind, Thunder, Fire and Ice. Releases its configured card.'],['Ice holder','Only weapon 6 (Fire) begins breaking it; cards 51,44,46 require this interaction.'],['Sand mound','Breakable Water-stage container; exposes the configured card.'],['Haunted armor','Hit when eyes are visible. Card IDs above 5 release a card; other armor releases recovery.'],['Recovery','Small +1 HP; medium +3 HP; extra life +1 to a maximum 9.'],['Boss reward','Homes toward Sakura, spins and fades on collection; suppresses duplicate awards on completed stages.'],['Water layer / bubbles / splash','Environmental presentation and water-state feedback.'],['Doors / portals / floor caps','Control transitions, checkpoints and arena geometry.']])
card_html+=source('world6/ice_holder.gd','Fire-only container')+source('shared/stage_progress.gd','Card progression and persistence')
parts.append(section('cards','07 / CARD BOOK','Cards','All 52 names, exact map coordinates, container requirements and duplicate locations.',card_html))

system_html='<div class="two-col"><article><h3>Save & load</h3><p>The native single slot is <code>user://sakura_save.json</code>, version 1. It stores validated unique card IDs and the final-stage reveal flag. Boss completion, weapons and maximum HP derive from collected cards. Saving also writes <code>user://save.sav</code>, the original 18-character Allegro slot. If JSON is absent, Load Game accepts the legacy slot.</p><p>HP, lives, weapon selection, checkpoints, current map and rematches are transient. Audio and controls live separately in <code>user://sakura_settings.json</code>. On Windows, Godot user data is under <code>%APPDATA%/Godot/app_userdata/Sakura — Godot Port/</code>.</p><h3>Presentation contract</h3><p>640×480 logical viewport, integer scaling, nearest-neighbor textures and pixel-snapped rendering. Gameplay retains fractional positions. Original magenta transparency was converted without changing pixel-art dimensions; the later Ice needle resize is a documented exception.</p></article><article><h3>Secrets & development controls</h3><p>Type K E R O in title Options or paused Options outside key rebinding. Then G toggles cheat invincibility at normal movement speed; B opens the final boss; C grants all 52 cards and their unlocks; T disables cheats. Session cheats survive New Game and Load but are not saved; granted cards can be saved.</p><p>The 52-card ending can reveal the code after the final fade and Enter; a second Enter returns to title. The code can also be entered before finishing the game.</p><p>The damage handler contains a hard-mode branch that makes any positive damage fatal. The current scripts contain no assignment enabling <code>hard_mode</code>. Debug God Mode is distinct from cheat God Mode.</p></article></div><h3>Music and sound</h3>'
tracks=literal(read('scripts/shared/audio_manager.gd'),'TRACK_NAMES')
system_html+=table(['Role','Source track'],[[k,v] for k,v in tracks.items()])
system_html+='<p>Twelve MIDI-derived tracks are rendered to OGG. Ten looping roles use native offsets within the base recording; Intro and Ending do not loop. Forty extracted sound effects use per-effect gains targeting approximately −10 dBFS at full SFX volume, with quieter contextual variants. Options changes SFX in 20% steps. Timing is derived from the source MIDI tempo events.</p><h3>Design structure</h3>'+table(['System','Responsibility'],[['SakuraProgress','Cards, derived unlocks/HP, lives, checkpoints, rematches, save validation'],['GameFlow','Title, intro, world selection, stage routing, game over, rematches and ending'],['StageBase','Shared lifecycle, player/HUD, pause, camera, transitions, death and enemy registry'],['World controllers','Map configuration, terrain interpretation, authored spawns and boss events'],['SakuraPlayer','Movement, collision, damage immunity, animation, selection and firing cycles'],['SakuraEnemy','Shared health, damage/contact behavior, update intervals and drops'],['AudioManager / SakuraSettings','Track transitions, exact loop points, SFX and persistent preferences']])
system_html+='<h3>Progression structure</h3><p>The campaign combines free stage choice with a circular weapon advantage, then reuses mastered enemy patterns in a final endurance route. Card collection raises maximum HP at fixed thresholds. Boss checkpoints reduce repeated traversal while rematches ask the player to retain pattern knowledge. These relationships describe the current campaign structure.</p>'+source('shared/game_flow.gd')
parts.append(section('systems','08 / DESIGN & SYSTEMS','Game systems','Persistence, secrets, audiovisual presentation and implementation architecture.',system_html))

evidence='<p>This is a documentation snapshot generated from the current working tree, 21 September 2026. Current source excerpts are embedded so the reference remains readable offline. The historical baseline is <code>old/2 Joguito</code>; unfinished later Sakura 2.0 systems are outside the campaign scope.</p><h3>Important distinctions found during research</h3>'+table(['Topic','Current implementation / qualification'],[['Firing','The recent source firing-cycle state machine supersedes older fixed/doubled cooldown notes. Wind resets at 50 ticks.'],['Red Ball','Current speed constant is 1.5 px/tick; older notes mention 1 or 2.'],['Boss damage','All normal stage collisions call take_weapon_hit, including Basic. Older take_projectile_hit methods may show different damage. The table follows the live call path.'],['Final-boss hit limit','The assignment hit_this_appearance = true is commented out. The documented historical one-hit-per-appearance limit is currently not enforced.'],['Final-boss Fire','The boss waits for six orbit-completion signals; its post-Fire recovery target is 90 updates, compared with 50 after other attacks.'],['Hard mode','A lethal-damage branch exists, but no current enabling assignment was found. Older README wording should not be treated as a usable shortcut.'],['Timing','The canonical Main.cpp runs input at 60 Hz and run_scripts every fourth tick (15 Hz). Current entities have individual conversions and tuning; older global 30 Hz descriptions are not universally correct.'],['Map42 cards','IDs 30 and 36 each have duplicate locations in the current map configuration.'],['Historical parity','Source inspection does not establish exact behavior of the shipped executable. Draw-clock assumptions and outstanding playtest notes remain in the repository records.']])
evidence+='<h3>Canonical evidence excerpts</h3>'
for f,start,end,title in [('Main.cpp',2198,2286,'Input and firing rules'),('Main.cpp',2495,2505,'Separate input and script clocks'),('colision.h',580,590,'Basic direct damage'),('colision.h',668,678,'Wind direct damage'),('colision.h',760,770,'Shadow direct damage')]:
    lines=(ROOT/'old/2 Joguito'/f).read_text(encoding='latin-1').splitlines()
    excerpt='\n'.join(f'{i+1:4}  {lines[i]}' for i in range(start-1,min(end,len(lines))))
    evidence+=f'<details class="source"><summary>{title} · old/2 Joguito/{f}:{start}</summary><pre><code>{E(excerpt)}</code></pre></details>'
evidence+='<h3>Embedded source library</h3><p>Every active GDScript file is available here, including supporting effects, pickups, rewards, menu and ending logic. Select a file to read the exact snapshot. The viewer displays the source snapshot as plain text.</p><label for="source-select">Implementation file</label><select id="source-select"><option value="">Choose a source file…</option>'
scripts={str(p.relative_to(PORT/'scripts')).replace('\\','/'):p.read_text(encoding='utf-8') for p in sorted((PORT/'scripts').rglob('*.gd'))}
evidence+=''.join(f'<option value="{E(k)}">{E(k)}</option>' for k in scripts)+'</select><pre id="source-view" tabindex="0">Choose a file above.</pre><h3>Historical records and asset provenance</h3><p>These notes are preserved as written; dated later changes or the current implementation may supersede them. Current implementation notes identify known differences from these historical records.</p>'
for p in sorted(PORT.glob('*.md')):
    evidence+=f'<details class="source"><summary>{E(p.name)}</summary><pre>{E(p.read_text(encoding="utf-8"))}</pre></details>'
for p in sorted((PORT/'assets').rglob('*.md')):
    if 'licenses' not in p.parts:
        evidence+=f'<details class="source"><summary>{E(str(p.relative_to(PORT)))}</summary><pre>{E(p.read_text(encoding="utf-8"))}</pre></details>'
evidence+='<p class="note">Original graphics and audio retain their original ownership and redistribution terms. Gameplay code, assets, timing and balance were not modified. Repository instructions prohibit automated and manual tests; this artifact was assembled by source inspection without running gameplay or browser tests.</p>'
parts.append(section('sources','09 / SOURCE REFERENCE','Sources and implementation notes','Current code, canonical excerpts, provenance and the limits of the snapshot.',evidence))

collision_profiles = {world:collision_profile(world) for world in range(1,8)}
map_data={}
for n,cfg in maps.items():
    p=PORT/'maps'/f'map{n}.map'
    tokens=p.read_text(encoding='latin-1').split()
    marks=[pos for ls in locations.values() for mn,kind,pos in ls if mn==n and pos]
    map_data[n]={'width':cfg['width'],'height':cfg['height'],'tokens':tokens,'start':cfg['start'],'cards':marks,'world':cfg['world']}

css=(Path(__file__).parent/'reference.css').read_text(encoding='utf-8')
js=(Path(__file__).parent/'reference.js').read_text(encoding='utf-8')
nav=[('guide','Start here'),('weapons','Weapons'),('bosses','Bosses'),('enemies','Enemies'),('hazards','Projectiles'),('stages','World atlas'),('cards','Card book'),('systems','Design & systems'),('sources','Sources')]
hero=image('world1/background.png','Original Wind-stage background','hero-bg')+image('player/player_idle.png','Sakura','hero-player')
document='''<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1"><meta name="color-scheme" content="light"><title>Sakura · Technical Reference</title><style>'''+css+'''</style></head><body><a class="skip" href="#main">Skip to content</a><aside class="sidebar"><a class="brand" href="#top"><span class="brand-mark">✿</span><span>SAKURA<small>TECHNICAL REFERENCE</small></span></a><p class="edition">ARCHIVE EDITION / 2026</p><nav aria-label="Contents">'''+''.join(f'<a href="#{id}"><span>{i:02}</span>{name}</a>' for i,(id,name) in enumerate(nav,1))+'''</nav><div class="sidebar-bottom"><span class="status-dot"></span> Fully offline reference<p>Manual · Wiki · Design document</p><button type="button" id="print">Print / save PDF</button></div></aside><main id="main"><header id="top" class="hero">'''+hero+'''<div class="hero-copy"><p class="eyebrow">GAME DESIGN DOCUMENT / MANUAL / WIKI</p><h1>Sakura<br><em>Technical Reference</em></h1><p>Campaign maps, enemy behavior, boss states, weapon parameters, card locations and implementation details.</p><a class="primary" href="#guide">Player manual <span>↘</span></a></div><div class="hero-stats"><span><b>07</b> Worlds</span><span><b>33</b> Maps</span><span><b>07</b> Weapons</span><span><b>52</b> Cards</span></div></header><div class="toolbar"><label class="search-label" for="search">Find an entry<input id="search" type="search" placeholder="Enemy, card, map or weapon…" autocomplete="off"></label><label for="world-filter">World<select id="world-filter"><option value="all">All worlds</option>'''+''.join(f'<option value="{i}">{name}</option>' for i,name in enumerate(world_names,1))+'''</select></label><button type="button" id="reset-filter">Reset</button><span id="search-status" role="status" aria-live="polite">Browse the complete reference</span></div><p class="filter-note">Search and world filters narrow catalog entries. General rules and evidence remain visible. Clear filters to restore the full guide.</p><div id="no-results" hidden>No catalog entries match. Try a name such as “The Freeze”, “Mirror” or “map42”, or reset the filters.</div><noscript><p class="note">JavaScript is disabled. All written reference content remains available; filters, map schematics and the browser checklist require JavaScript.</p></noscript>'''+''.join(parts)+'''<footer><span>✿ SAKURA</span><p>Offline game documentation and embedded source snapshot.<br>Snapshot: 21 September 2026 · Spoilers throughout.</p><a href="#top">Back to top ↑</a></footer></main><script id="reference-data" type="application/json">'''+json.dumps({'maps':map_data,'scripts':scripts,'collisionProfiles':collision_profiles},ensure_ascii=False).replace('<','\\u003c')+'''</script><script>'''+js+'''</script></body></html>'''
OUT.write_text(document,encoding='utf-8')
print(f'Wrote {OUT.name}: {OUT.stat().st_size:,} bytes; {len(maps)} maps, {len(card_names)} cards, {len(entities)} bestiary entries, {len(hazards)} hazard families, {len(bosses)} bosses, {len(scripts)} source files.')
