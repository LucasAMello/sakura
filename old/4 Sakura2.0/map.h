#ifndef MAP_H
#define MAP_H

#include <allegro.h>

#include "actor.h"
#include "wall.h"

class Game;
class Player;

class Map
{
public:
    WallList *walls;
    Player *player;

    FILE* fmap;

    short int width;
    short int height;
    short int limitleft;
    short int limitright;
    short int limitup;
    short int limitdown;

    char type;
    char number;
    char **map;

    int startingpointx, startingpointy;
    int water_position;

    int texture;

    Map(Player *, WallList *);
    ~Map();

    void load_map(char mapnumber);
    void create_level(Game *game, int mapnumber, int restart);
    void set_dvalues(int number);
};

#endif
