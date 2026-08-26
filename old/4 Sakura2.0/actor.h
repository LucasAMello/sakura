#ifndef ACTOR_H
#define ACTOR_H

#include <allegro.h>
#include <list>

#include "timing.h"

enum ActorType
{
    YELLOW_SHOT = 1,
    WIND_SHOT,
    SHADOW_SHOT,
    THUNDER_SHOT,
    WATER_SHOT,
    FIRE_SHOT,
    ICE_SHOT,
    UNUSED01,
    UNUSED02,
    RED_BALL,
    SPRING,
    TURRET_ENEMY,
    TURRET_ENEMY_SHOT,
    SMALL_BIRD,
    GHOST,
    PHANTOM_SPAWNER,
    PHANTOM,
    PHANTOM_SPAWNER2,
    PHANTOM2,
    MAGIC_WALL,
    WALL_TURRET,
    WALL_TURRET_SHOT,
    BATTLE_MACHINE,
    MISSILE,
    FLOATING_ORANGE,
    SHOCKER_MACHINE,
    SHOCKING,
    SHOCKER_SHOT,
    BIG_THUNDER,
    SMALL_THUNDER,
    MR_RESET,
    SEA_HORSE,
    SEA_HORSE_SPAWNER,
    FISH,
    OYSTER_TOP,
    OYSTER_BOTTOM,
    OYSTER_BALL,
    WATER_JET,
    FLAME_THROWER,
    FLAME_THROWER2,
    FLAMES,
    FLAMES2,
    FLAME_METROID,
    FLAME_METROID_WALL,
    FIRE,
    SQUID,
    SQUID2,
    FIRES,
    FIRE_BALL,
    SLASH1,
    SLASH2,
    ICE_METROID,
    ICE1,
    ICE2,
    SPIKE,
    ICE_NEEDLE,
    PUMPKIN,
    ICY_ATTACK,
    WATER_SHOT_SMALL1,
    WATER_SHOT_SMALL2,
    PAINTING,
    ARMOR,
    FEATHER,
    CARD_HOLDER,
    SAND_PILE,
    ICE_HOLDER,
    CARD,
    AIR_BUBBLE,
    SEA_HORSE_SPAWNER2,
    SEA_HORSE2,
    PORTAL_1,
    PORTAL_2,
    LAST_SHOT,
    LAST_THUNDER,
    LAST_FIRE1,
    LAST_FIRE2,
    LAST_ICE,
    TURRET_SHOT_DSTR,
    RECOVERY_SMALL,
    RECOVERY_MEDIUM,
    LIFE,
    PARTICLES1,
    PARTICLES2,
    PARTICLES3,
    PARTICLES4,
    ICE_DSTR,
    SPLASH_,
    ICE_BLOCK,
    HA_,
    PORTA_1,
    PORTA_2,
    BOSS_WIND,
    BOSS_SHADOW,
    BOSS_SHADOW2,
    BOSS_THUNDER,
    BOSS_WATER,
    BOSS_FIRE,
    BOSS_ICE,
    SHADOW_BALL,
    LAST_BOSS,
    END_STAGE,
    DELIMITER,
    TRANGLE_FLASH,
    MOVING_CARD,
    FALLING_FLOOR1,
    FALLING_FLOOR2,
    ICE_TOP1,
    ICE_TOP2,
    PORTAL_SIDE,
    YELLOW_SHOT_DSTR,
    WIND_SHOT_DSTR,
    SHADOW_SHOT_DSTR,
    THUNDER_SHOT_DSTR,
    WATER_SHOT_DSTR,
    FIRE_SHOT_DSTR,
    ICE_SHOT_DSTR,
    EXPLOSION,
    TURRET_ENEMY_DSTR,
    DSTR_40,
};

class Game;
class Player;

class Actor
{
public:
    bool active;
    ActorType type;
    int timer;
    int animation_state;
    int width, height;
    int action_state;
    int frame;
    float hit_points_left;
    float x_position, y_position;
    float x_speed, y_speed;
    int direction;
    unsigned char rotate_factor;
    int extra_int;
    int strength;

    bool hittable[7];

    Actor(ActorType, int, int, int, int);

    void actor_check();
    void enemy_ai(int type, int actor_number);
    void animation();
    void actor_update(Player *player);
    void destroyactor();
    void damage(Actor *a);
};

typedef std::list<Actor> ActorList;

#endif
