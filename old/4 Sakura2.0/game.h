#ifndef GAME_H
#define GAME_H

#include <allegro.h>
#include <iostream>
#include <fstream.h>

#include "player.h"
#include "actor.h"
#include "wall.h"
#include "menu.h"
#include "map.h"

using namespace std;

class Game
{
public:
    Menu *menu;
    Player player;
    ActorList actors;
    WallList walls;
    Map *map;

    BITMAP* buffer;
    BITMAP* scenario;
    BITMAP* bakg;
    BITMAP* background;
    BITMAP* foreground;

    ofstream myfile;

    unsigned char jump_key_state;

    int recordinging;
    int fire_key;
    int number_of_walls;
    int dieanimation;
    int texture;
    int restart;
    int screenx, screeny;
    int number_of_actors;
    int actual_cycle;
    int myrandnumber;
    int bibinhalinda, bibinhafeia;
    int limpation;
    int input_locked, screen_locked;
    int bframe;
    int weaponlock;
    int looper;
    int doorrecord;
    int event_organizer;
    int call_event;
    int bosslife;
    int key_rest;
    int light_level;
    int aguaa;
    int pisca;
    int starting, starting2, finishing;
    int create_bubbles;
    int osutatakaefadeout;
    int something, something2;
    int doft[4];
    int desired_music;
    int desired_level;
    int hard_mode;
    int rollinglol;
    int bouldergo;
    int player_col;
    int lastagedoor;
    int lastageblack;
    int sparkmandril;
    int itsover;

    char bossfight;
    char current_level;
    char desired_weapon;
    char force_draw;        // Forces drawing of the player when he hits the ground
    char vglvfs;
    char stopall;
    char movingscreen;
    char flash_screen;
    char mainmenu;
    char key_enter_rest;
    char key_f_rest;
    char howtoend, stage_screen;
    char gamemenustat;
    char timetoquit;
    char menupos;
    char next_level;
    char gamestartmusic;
    char lastageportal[6];
    char lastageboss;
    char cheats, show_fps, fps_rest;
    char god_mode, gotolastage;
    char drawendchar;
    char txt[80];
    char txt2[80];
    char mensagem[40];
    char checker;

    float fademeout;
    float intring;
    float bigbig;
    float bolas[12][2];

    bool bFullScreen;
    bool time_to_quit;

    Game(BITMAP *b);
    ~Game();

    void die();
    void damage(int howmuch);
    void setup_game();
    void input();
    void logic();
    void draw();
    int check_colision(Actor, WallList::iterator, int);
    int check_colision(Actor, ActorList::iterator, int);
    void callevent(int event_number);
    void move_to_end();
    void set_controls();
    void run_scripts();

    void create_actor(ActorType type, int x_position, int y_position,  int direction, int time);
    void actor_colision(Actor *actor);
    void wall_colision(Actor *actor);
    void destroy_actors();
    void destroy_walls();

    int in_player_view(Actor*);
};

#endif
