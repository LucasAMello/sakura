#ifndef MENU_H
#define MENU_H

#include <allegro.h>
#include <iostream>
#include <fstream.h>

#include "player.h"
#include "timing.h"
#include "data.h"
#include "intro.h"

class Menu
{
public:
    int position;
    int position2;
    int choice;
    int key_enter_rest;
    int key_f_rest;
    int key_rest;
    int timer;
    int stage_select_boulder;
    int *hard_mode;

    int doft[4];

    bool fadein;
    bool fadeout;

    Player *player;

    BITMAP *buffer;

    Menu(int *, Player*);
    ~Menu();
    int main_menu();
    void draw_main_menu();
    void options();
    void draw_options();
    void set_controls();
    void intro_menu();
    void draw_intro_menu();
    int stage_select_menu();
    void draw_stage_select_menu();
    int game_menu();
    void draw_game_menu(int menuposx);

    void savegame();
    int loadgame();
};

#endif
