#ifndef PLAYER_H
#define PLAYER_H

#include <allegro.h>

#include "map.h"

class Game;

extern Game *game;

class Player
{
public:
    int imune;
    int width, height;
    int frame;
    int current_weapon;
    int score;
    int shine;
    int key_up, key_down, key_right, key_left, key_fire, key_jump, key_weapon1, key_weapon2, key_menu, key_quit;
    int vidas;
    int on_ground;

    float timer;
    float x_position, y_position;
    float x_speed, y_speed;

    char skin;
    char move;
    char shots;
    char shooting;
    char cards[52];
    char hpmax;
    char hp;
    char in_water;
    char letter_order;
    char animation_timer;
    char direction;
    char test_fall;         // Tests if there's ground under player

    bool dead;

    Player();

    void player_colision();
    void move_player(BITMAP *scenario, Map *map, bool x, bool y);
};

#endif
