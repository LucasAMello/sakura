#include "map.h"
#include "game.h"

Map::Map(Player *p, WallList *w)
{
    player = p;
    walls = w;
}

Map::~Map()
{
    for (int i = 0; i < height; i++)
        delete [] map[i];
    delete [] map;
}

void Map::create_level(Game *game, int mapnumber, int restart)
{
    if (mapnumber == 10)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            game->screenx = 0;
            game->screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            load_map(10);
        }

        texture = TEXTURES01;
        for (int i = 0; i <= 27; i++)
        {
            for ( int t = 0; t <= 449; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(20 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(60 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(20 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(40 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(0 , 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(40 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(0 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;

        if (player->cards[32] == 0) game->create_actor(CARD, 4052, 260, 0, 32);
        if (player->cards[43] == 0) game->create_actor(CARD_HOLDER, 6470, 120, 0, 43);
        game->create_actor(RED_BALL, 800, 320, 0, 0);
        game->create_actor(RED_BALL, 1480, 320, 0, 0);
        game->create_actor(RED_BALL, 1780, 240, 1, 0);
        game->create_actor(RED_BALL, 2920, 120, 0, 0);
        game->create_actor(RED_BALL, 3220, 120, 0, 0);
        game->create_actor(RED_BALL, 3720, 280, 0, 0);
        game->create_actor(RED_BALL, 5140, 400, 0, 0);
        game->create_actor(RED_BALL, 5500, 340, 0, 0);
        game->create_actor(RED_BALL, 5800, 280, 0, 0);
        game->create_actor(RED_BALL, 7060, 420, 0, 0);
        game->create_actor(RED_BALL, 7480, 240, 0, 0);
        game->create_actor(RED_BALL, 7700, 160, 0, 0);
        game->create_actor(RED_BALL, 7900, 120, 0, 0);

        game->create_actor(SPRING, 2720, 220, 0, 0);
        game->create_actor(SPRING, 6480, 380, 0, 0);
        game->create_actor(SPRING, 7060, 400, 0, 0);

        game->create_actor(SMALL_BIRD, 4320, 120, 0, 0);
        game->create_actor(SMALL_BIRD, 6100, 160, 0, 0);
        game->create_actor(SMALL_BIRD, 6180, 160, 0, -10);

        game->create_actor(END_STAGE, 8960, 280, 100, 11);

        texture = -1;
    }
    /*
    else if (mapnumber == 11)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(11);
        }

        texture = TEXTURES01;
        for (int i = 0; i <= 99; i++)
        {
            for ( int t = 0; t <= 39; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(20 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(60 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(20 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(40 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(0 , 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(40 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(0 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[42] == 0) game->create_actor(69, 612, 740, 0, 42);
        game->create_actor(10, 300, 180, 0, 0);
        game->create_actor(10, 180, 560, 0, 0);
        game->create_actor(10, 180, 1200, 0, 0);
        game->create_actor(10, 420, 1440, 0, 0);
        game->create_actor(10, 480, 1720, 1, 0);
        game->create_actor(10, 380, 1720, 0, 0);

        game->create_actor(11, 480, 420, 0, 0);
        game->create_actor(11, 460, 1100, 0, 0);
        game->create_actor(11, 280, 1540, 0, 0);

        game->create_actor(12, 340, 880, 0, 0);
        game->create_actor(12, 400, 880, 1, 0);
        game->create_actor(12, 620, 1860, 0, 0);

        game->create_actor(1010, 760, 1820, 100, 12);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 12)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            //set_dvalues(//doorrecord - 1);
            load_map(12);
        }

        texture = TEXTURES01;
        for (int i = 0; i <= 29; i++)
        {
            for ( int t = 0; t <= 419; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(20 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(60 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(20 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(40 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(0 , 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(40 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(0 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[10] == 0) game->create_actor(69, 2552, 380, 0, 10);
        if (player->cards[37] == 0) game->create_actor(65, 7180, 80, 0, 37);
        game->create_actor(10, 680, 360, 0, 0);
        game->create_actor(10, 1860, 400, 0, 0);
        game->create_actor(10, 2440, 120, 0, 0);
        game->create_actor(10, 4720, 280, 0, 0);
        game->create_actor(10, 7240, 300, 0, 0);

        game->create_actor(11, 880, 340, 0, 0);
        game->create_actor(11, 4180, 380, 0, 0);
        game->create_actor(11, 4240, 380, 0, -20);
        game->create_actor(11, 6760, 360, 0, 0);
        game->create_actor(11, 6805, 360, 0, -5);
        game->create_actor(11, 6850, 360, 0, -10);

        game->create_actor(12, 980, 500, 0, 0);
        game->create_actor(12, 2420, 440, 0, 0);
        game->create_actor(12, 5710, 240, 0, 0);
        game->create_actor(12, 7480, 420, 1, 0);

        game->create_actor(14, 4030, 50, 0, 0);
        game->create_actor(14, 4880, 180, 0, 0);
        game->create_actor(14, 6080, 100, 0, 0);

        game->create_actor(55, 3440, 320, 0, 0);
        game->create_actor(55, 6240, 240, 0, 0);
        game->create_actor(55, 5080, 240, 0, 0);

        game->create_actor(1010, 8360, 420, 120, 13);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 13)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(13);
        }
        texture = TEXTURES01;
        for (int i = 0; i <= 89; i++)
        {
            for ( int t = 0; t <= 39; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(20 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(60 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(20 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(40 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(0 , 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(40 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(0 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }
        if (player->cards[38] == 0) game->create_actor(69, 562, 1720, 0, 28);
        if (player->cards[13] == 0) game->create_actor(69, 620, 240, 0, 13);
        game->create_actor(10, 500, 1200, 0, 0);
        game->create_actor(10, 380, 940, 0, 0);
        game->create_actor(10, 300, 120, 0, 0);
        game->create_actor(10, 480, 120, 1, 0);
        game->create_actor(11, 340, 1600, 0, 0);
        game->create_actor(11, 310, 360, 0, 0);
        game->create_actor(12, 470, 700, 0, 0);
        game->create_actor(55, 600, 1740, 0, 0);
        game->create_actor(55, 320, 1120, 0, 0);
        game->create_actor(55, 400, 580, 0, 0);
        game->create_actor(1010, 760, 40, 100, 14);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 14)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(14);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }
        texture = TEXTURES01;
        for (int i = 0; i <= 27; i++)
        {
            for ( int t = 0; t <= 199; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(20 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(60 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(20 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(40 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(0 , 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(40 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(0 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }
        if (player->cards[20] == 0) game->create_actor(69, 1720, 280, 0, 20);
        game->create_actor(10, 580, 380, 0, 0);
        game->create_actor(10, 1380, 360, 0, 0);
        game->create_actor(14, 1170, 160, 0, 0);
        game->create_actor(14, 1250, 180, 0, -10);
        game->create_actor(14, 1540, 260, 0, 0);
        game->create_actor(1000, 2120, 280, 0, 0);
        game->create_actor(1000, 2730, 280, 0, 1);
        game->create_actor(2001, 2760, 380, 0, 0);
        game->create_actor(2000, 2780, 380, 0, 0);
        game->create_actor(2000, 2860, 380, 0, 0);
        game->create_actor(2000, 2940, 380, 0, 0);
        game->create_actor(2000, 3020, 380, 0, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 20)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(20);
        }

        texture = TEXTURES02;
        for (int i = 0; i <= 23; i++)
        {
            for ( int t = 0; t <= 99; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(40 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(80 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm')
                {
                    walls->push_back(Wall(100, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(100, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(80, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
            }
        }

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        if (player->cards[12] == 0) game->create_actor(69, 1770, 280, 0, 12);
        game->create_actor(15, 1580, 200, 0, 0);

        game->create_actor(1010, 1960, 100, 240, 21);

        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 13, 177);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 21)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(21);
        }

        texture = TEXTURES02;
        for (int i = 0; i <= 27; i++)
        {
            for ( int t = 0; t <= 209; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(40 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(80 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm')
                {
                    walls->push_back(Wall(100, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(100, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(80, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
            }
        }

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        if (player->cards[16] == 0) game->create_actor(69, 2040, 300, 0, 16);
        game->create_actor(59, 2100, 180, 0, 0);
        game->create_actor(60, 1120, 370, 0, 0);
        game->create_actor(60, 3860, 390, 0, 22);

        game->create_actor(15, 510, 220, 0, 0);
        game->create_actor(15, 1300, 200, 0, 0);
        game->create_actor(15, 2670, 280, 0, 0);
        game->create_actor(15, 3630, 400, 0, 0);

        game->create_actor(16, 3120, 180, 1580, 140);

        game->create_actor(1010, 4160, 340, 120, 22);

        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 22)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(22);
        }

        texture = TEXTURES02;
        for (int i = 0; i <= 69; i++)
        {
            for ( int t = 0; t <= 119; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(40 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(80 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm')
                {
                    walls->push_back(Wall(100, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(100, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(80, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
            }
        }

        if (player->cards[47] == 0) game->create_actor(69, 1680, 200, 1, 47);
        if (player->cards[39] == 0) game->create_actor(69, 40, 1040, 1, 39);
        game->create_actor(60, 1180, 250, 0, 0);
        game->create_actor(60, 400, 1250, 0, 0);
        game->create_actor(60, 1770, 990, 0, 35);

        game->create_actor(53, 740, 352, 1, 120);
        game->create_actor(53, 1620, 352, 1, 160);
        game->create_actor(53, 2100, 772, 1, 100);
        game->create_actor(53, 1160, 772, 1, 220);
        game->create_actor(53, 620, 772, 1, 120);
        game->create_actor(53, 1160, 1172, 1, 120);

        game->create_actor(15, 600, 230, 0, 0);
        game->create_actor(15, 1800, 200, 0, 0);
        game->create_actor(15, 1860, 560, 1, 0);
        game->create_actor(15, 720, 1080, 0, 0);
        game->create_actor(15, 1610, 960, 0, 0);

        game->create_actor(61, 120, 560, 2400, 140);

        game->create_actor(1010, 2360, 940, 120, 23);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 23)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(23);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES02;
        for (int i = 0; i <= 35; i++)
        {
            for ( int t = 0; t <= 299; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(40 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(80 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm')
                {
                    walls->push_back(Wall(100, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(100, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'w') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'q') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(80, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
            }
        }

        if (player->cards[24] == 0) game->create_actor(69, 660, 60, 1, 24);
        game->create_actor(60, 3860, 530, 0, 27);
        game->create_actor(53, 340, 652, 1, 2500);

        game->create_actor(1000, 4700, 440, 0, 2);
        game->create_actor(1000, 5310, 440, 0, 3);

        game->create_actor(1002, 5700, 530, 0, 0);

        game->create_actor(15, 620, 340, 0, 0);
        game->create_actor(15, 860, 460, 0, 0);
        game->create_actor(15, 1230, 530, 0, 0);
        game->create_actor(15, 1400, 200, 0, 0);
        game->create_actor(15, 1760, 400, 0, 0);
        game->create_actor(15, 2160, 260, 0, 0);
        game->create_actor(15, 3300, 460, 0, 0);

        game->create_actor(16, 4560, 440, 3080, 140);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 30)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(30);
        }

        texture = TEXTURES04;
        for (int i = 0; i <= 29; i++)
        {
            for ( int t = 0; t <= 499; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(100, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(120, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(0, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '#') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '$') walls->push_back(Wall(40, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '%') walls->push_back(Wall(60, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(80, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '+') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '_') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[25] == 0) game->create_actor(69, 2230, 310, 1, 25);
        if (player->cards[21] == 0) game->create_actor(69, 6300, 260, 1, 21);
        if (player->cards[38] == 0) game->create_actor(65, 8540, 100, 0, 38);
        game->create_actor(19, 900, 260, 0, 5);
        game->create_actor(19, 1380, 100, 0, 10);
        game->create_actor(19, 1480, 340, 1, 0);
        game->create_actor(19, 4080, 300, 1, 0);
        game->create_actor(19, 4260, 300, 2, 0);
        game->create_actor(19, 6740, 340, 1, 0);
        game->create_actor(21, 4580, 450, 0, 0);
        game->create_actor(21, 5620, 310, 0, 0);
        game->create_actor(21, 8760, 370, 0, 0);
        game->create_actor(23, 2770, 260, 0, 0);
        game->create_actor(23, 6200, 140, 0, 0);
        game->create_actor(23, 7150, 280, 0, 0);
        game->create_actor(23, 7670, 240, 0, 0);
        game->create_actor(23, 5140, 210, 0, 0);
        game->create_actor(24, 3180, 116, 0, 0);
        game->create_actor(24, 3330, 356, 2, 0);
        game->create_actor(24, 4716, 260, 3, 0);
        game->create_actor(24, 5760, 56, 0, 0);
        game->create_actor(24, 9160, 196, 0, 0);
        game->create_actor(24, 9360, 336, 2, 0);
        game->create_actor(1010, 9960, 220, 140, 31);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 77, 277);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 31)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(31);
        }

        texture = TEXTURES04;
        for (int i = 0; i <= 79; i++)
        {
            for ( int t = 0; t <= 99; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(100, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(120, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(0, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '#') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '$') walls->push_back(Wall(40, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '%') walls->push_back(Wall(60, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(80, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '+') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '_') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[6] == 0) game->create_actor(69, 80, 1480, 1, 6);
        if (player->cards[17] == 0) game->create_actor(69, 1760, 400, 1, 17);
        game->create_actor(19, 820, 280, 2, 0);
        game->create_actor(19, 240, 380, 0, 0);
        game->create_actor(19, 430, 380, 0, 15);
        game->create_actor(19, 620, 380, 0, 0);
        game->create_actor(19, 720, 920, 1, 0);
        game->create_actor(19, 880, 1340, 0, 0);
        game->create_actor(21, 560, 150, 0, 0);
        game->create_actor(21, 930, 1470, 0, 0);
        game->create_actor(21, 1740, 490, 0, 0);
        game->create_actor(21, 1840, 230, 0, 0);
        game->create_actor(23, 1660, 1200, 0, 0);
        game->create_actor(23, 1240, 1000, 0, 0);
        game->create_actor(23, 1240, 220, 0, 0);
        game->create_actor(24, 110, 796, 2, 0);
        game->create_actor(24, 876, 680, 1, 0);
        game->create_actor(24, 876, 780, 1, -10);
        game->create_actor(24, 216, 1100, 3, 0);
        game->create_actor(24, 216, 1180, 3, -12);
        game->create_actor(24, 216, 1260, 3, -24);
        game->create_actor(24, 436, 1140, 1, -6);
        game->create_actor(24, 436, 1220, 1, -18);
        game->create_actor(24, 110, 1316, 0, -24);
        game->create_actor(24, 170, 1316, 0, -44);
        game->create_actor(24, 1276, 820, 3, 0);
        game->create_actor(24, 1696, 920, 3, 0);
        game->create_actor(1010, 1960, 140, 160, 32);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 32)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(32);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES04;
        for (int i = 0; i <= 31; i++)
        {
            for ( int t = 0; t <= 299; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(100, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(120, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(0, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '#') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '$') walls->push_back(Wall(40, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '%') walls->push_back(Wall(60, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(80, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '+') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '_') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[26] == 0) game->create_actor(69, 4020, 220, 1, 26);
        if (player->cards[48] == 0) game->create_actor(69, 1520, 360, 1, 48);
        game->create_actor(19, 1110, 240, 0, 0);
        game->create_actor(19, 1350, 240, 0, 0);
        game->create_actor(19, 1590, 240, 0, 15);
        game->create_actor(19, 3760, 300, 1, 0);
        game->create_actor(19, 3760, 380, 1, 20);
        game->create_actor(19, 3760, 460, 1, 10);
        game->create_actor(21, 1000, 450, 0, 0);
        game->create_actor(21, 3260, 290, 0, 0);
        game->create_actor(21, 4600, 410, 0, 0);
        game->create_actor(23, 2160, 140, 0, 0);
        game->create_actor(23, 3140, 100, 0, 0);
        game->create_actor(24, 1111, 556, 2, -10);
        game->create_actor(24, 1351, 556, 2, -50);
        game->create_actor(24, 1591, 556, 2, -20);
        game->create_actor(24, 1232, 156, 0, -40);
        game->create_actor(24, 1472, 156, 0, 0);
        game->create_actor(24, 1712, 156, 0, -30);
        game->create_actor(1000, 4720, 380, 0, 4);
        game->create_actor(1000, 5330, 380, 0, 5);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 40)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(40);
        }

        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++)
        {
            for ( int t = 0; t <= 449; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(40, 20, 10, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(40, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'a')
                {
                    walls->push_back(Wall(60, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'b')
                {
                    walls->push_back(Wall(60, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'c')
                {
                    walls->push_back(Wall(80, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'd')
                {
                    walls->push_back(Wall(80, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'e')
                {
                    walls->push_back(Wall(100, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'f')
                {
                    walls->push_back(Wall(100, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'g')
                {
                    walls->push_back(Wall(100, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'h') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i')
                {
                    walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'j')
                {
                    walls->push_back(Wall(40, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'k')
                {
                    walls->push_back(Wall(60, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(40, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(60, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(80, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(120, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(40, 40, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '}') walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '{') walls->push_back(Wall(40, 60, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));

            }
        }

        if (player->cards[50] == 0) game->create_actor(69, 20, 220, 1, 50);
        if (player->cards[8] == 0) game->create_actor(69, 3220, 470, 1, 8);
        game->create_actor(66, 7290, 344, 0, 34);
        game->create_actor(29, 700, 300, 0, 0);
        game->create_actor(29, 1440, 380, 0, 0);
        game->create_actor(29, 6270, 380, 0, 0);
        game->create_actor(31, 3860, 600, 0, 0);
        game->create_actor(31, 8540, 540, 0, 0);
        game->create_actor(32, 3170, 480, 0, 0);
        game->create_actor(32, 3220, 450, 0, 0);
        game->create_actor(32, 3190, 500, 0, 0);
        game->create_actor(32, 3230, 485, 0, 0);
        game->create_actor(32, 3185, 445, 0, 0);
        game->create_actor(32, 5280, 470, 0, 0);
        game->create_actor(32, 5300, 485, 0, 0);
        game->create_actor(32, 5270, 515, 0, 0);
        game->create_actor(32, 5285, 500, 0, 0);
        game->create_actor(32, 8200, 480, 0, 0);
        game->create_actor(34, 2040 + 6, 433 + 13, 0, 0);
        game->create_actor(33, 2040, 433, 0, 0);
        game->create_actor(34, 4690 + 6, 493 + 13, 0, 0);
        game->create_actor(33, 4690, 493, 0, 0);
        game->create_actor(34, 5920 + 6, 473 + 13, 0, 0);
        game->create_actor(33, 5920, 473, 0, 0);
        game->create_actor(34, 6990 + 6, 373 + 13, 0, 0);
        game->create_actor(33, 6990, 373, 0, 0);
        game->create_actor(34, 7560 + 1, 413 + 13, 1, 0);
        game->create_actor(33, 7560, 413, 1, 0);
        game->create_actor(1010, 8960, 360, 220, 41);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 185, 357);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 41)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 1;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            bossfight = 0;
            load_map(41);
        }

        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++)
        {
            for ( int t = 0; t <= 449; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(40, 20, 10, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(40, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'a')
                {
                    walls->push_back(Wall(60, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'b')
                {
                    walls->push_back(Wall(60, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'c')
                {
                    walls->push_back(Wall(80, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'd')
                {
                    walls->push_back(Wall(80, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'e')
                {
                    walls->push_back(Wall(100, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'f')
                {
                    walls->push_back(Wall(100, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'g')
                {
                    walls->push_back(Wall(100, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'h') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i')
                {
                    walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'j')
                {
                    walls->push_back(Wall(40, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'k')
                {
                    walls->push_back(Wall(60, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(40, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(60, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(80, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(120, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(40, 40, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '}') walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '{') walls->push_back(Wall(40, 60, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));

            }
        }

        if (player->cards[36] == 0) game->create_actor(69, 810, 310, 1, 36);
        if (player->cards[30] == 0) game->create_actor(69, 8660, 80, 1, 30);
        game->create_actor(66, 6980, 164, 0, 40);
        game->create_actor(29, 7120, 200, 0, 0);
        game->create_actor(32, 770, 280, 0, 0);
        game->create_actor(32, 870, 320, 0, 0);
        game->create_actor(32, 800, 320, 0, 0);
        game->create_actor(32, 830, 290, 0, 0);
        game->create_actor(32, 786, 300, 0, 0);
        game->create_actor(32, 1770, 480, 0, 0);
        game->create_actor(32, 1870, 460, 0, 0);
        game->create_actor(32, 1700, 490, 0, 0);
        game->create_actor(32, 1740, 500, 0, 0);
        game->create_actor(32, 3320, 420, 0, 0);
        game->create_actor(32, 3300, 440, 0, 0);
        game->create_actor(32, 3335, 405, 0, 0);
        game->create_actor(32, 3785, 385, 0, 0);
        game->create_actor(32, 3805, 355, 0, 0);
        game->create_actor(32, 4660, 285, 0, 0);
        game->create_actor(32, 4685, 275, 0, 0);
        game->create_actor(32, 4670, 305, 0, 0);
        game->create_actor(32, 7900, 220, 0, 0);
        game->create_actor(32, 7920, 225, 0, 0);
        game->create_actor(32, 7960, 235, 0, 0);
        game->create_actor(32, 7970, 255, 0, 0);
        game->create_actor(32, 8000, 220, 0, 0);
        game->create_actor(31, 2050, 620, 0, 0);
        game->create_actor(31, 2940, 560, 0, 0);
        game->create_actor(31, 3140, 560, 0, 0);
        game->create_actor(31, 5740, 320, 0, 0);
        game->create_actor(31, 8480, 380, 0, 0);
        game->create_actor(34, 2650 + 6, 533 + 13, 0, 0);
        game->create_actor(33, 2650, 533, 0, 0);
        game->create_actor(34, 4000 + 6, 453 + 13, 0, 0);
        game->create_actor(33, 4000, 453, 0, 0);
        game->create_actor(34, 4180 + 6, 393 + 13, 0, 0);
        game->create_actor(33, 4180, 393, 0, 0);
        game->create_actor(34, 6600 + 6, 233 + 13, 0, 0);
        game->create_actor(33, 6600, 233, 0, 0);
        game->create_actor(34, 1360 + 1, 593 + 13, 1, 0);
        game->create_actor(33, 1360, 593, 1, 0);
        game->create_actor(34, 7280 + 1, 233 + 13, 1, 0);
        game->create_actor(33, 7280, 233, 1, 0);
        game->create_actor(1010, 8960, 0, 240, 42);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 42)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(42);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++)
        {
            for ( int t = 0; t <= 499; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(40, 20, 10, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(40, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'a')
                {
                    walls->push_back(Wall(60, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'b')
                {
                    walls->push_back(Wall(60, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'c')
                {
                    walls->push_back(Wall(80, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'd')
                {
                    walls->push_back(Wall(80, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'e')
                {
                    walls->push_back(Wall(100, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'f')
                {
                    walls->push_back(Wall(100, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'g')
                {
                    walls->push_back(Wall(100, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'h') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i')
                {
                    walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'j')
                {
                    walls->push_back(Wall(40, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'k')
                {
                    walls->push_back(Wall(60, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(40, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(60, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(80, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(120, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(40, 40, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '}') walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '{') walls->push_back(Wall(40, 60, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));

            }
        }

        if (player->cards[30] == 0) game->create_actor(69, 5480, 480, 1, 30);
        if (player->cards[36] == 0) game->create_actor(69, 3550, 330, 0, 36);
        game->create_actor(66, 2510, 204, 0, 11);
        game->create_actor(29, 1790, 260, 0, 0);
        game->create_actor(29, 2170, 240, 0, 0);

        game->create_actor(31, 1160, 400, 0, 0);
        game->create_actor(31, 4210, 420, 0, 0);
        game->create_actor(31, 5720, 620, 0, 0);
        game->create_actor(31, 5755, 620, 0, 0);
        game->create_actor(31, 8180, 580, 0, 0);
        game->create_actor(31, 8220, 580, 0, 0);
        game->create_actor(31, 8260, 580, 0, 0);

        game->create_actor(32, 960, 275, 0, 0);
        game->create_actor(32, 930, 320, 0, 0);
        game->create_actor(32, 3560, 320, 0, 0);
        game->create_actor(32, 3550, 300, 0, 0);
        game->create_actor(32, 3580, 340, 0, 0);
        game->create_actor(32, 3560, 355, 0, 0);
        game->create_actor(32, 3980, 300, 0, 0);
        game->create_actor(32, 3900, 325, 0, 0);
        game->create_actor(32, 5270, 460, 0, 0);
        game->create_actor(32, 5200, 465, 0, 0);
        game->create_actor(32, 5370, 470, 0, 0);
        game->create_actor(32, 5250, 430, 0, 0);
        game->create_actor(32, 5320, 480, 0, 0);
        game->create_actor(32, 5235, 475, 0, 0);
        game->create_actor(32, 7450, 460, 0, 0);
        game->create_actor(32, 7400, 480, 0, 0);
        game->create_actor(32, 7510, 500, 0, 0);
        game->create_actor(32, 7465, 493, 0, 0);
        game->create_actor(32, 7710, 460, 0, 0);
        game->create_actor(32, 7765, 435, 0, 0);

        game->create_actor(34, 2680 + 6, 213 + 13, 0, 0);
        game->create_actor(33, 2680, 213, 0, 0);
        game->create_actor(34, 4700 + 6, 473 + 13, 0, 0);
        game->create_actor(33, 4700, 473, 0, 0);
        game->create_actor(34, 6440 + 6, 513 + 13, 0, 0);
        game->create_actor(33, 6440, 513, 0, 0);
        game->create_actor(34, 2300 + 1, 213 + 13, 1, 0);
        game->create_actor(33, 2300, 213, 1, 0);
        game->create_actor(34, 7040 + 1, 493 + 13, 1, 0);
        game->create_actor(33, 7040, 493, 1, 0);

        game->create_actor(1000, 8720, 540, 0, 6);
        game->create_actor(1000, 9330, 540, 0, 7);
        game->create_actor(1005, 9770, 570, 0, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 50)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(50);
        }

        texture = TEXTURES06;
        for (int i = 0; i <= 79; i++)
        {
            for ( int t = 0; t <= 39; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 20, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == '3') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == '4') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == '5') walls->push_back(Wall(40, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(140, 60, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == '7') walls->push_back(Wall(160, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == '8') walls->push_back(Wall(140, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == '9') walls->push_back(Wall(160, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(100, 0, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == 'b') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == 'c') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == 'd') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(100, 40, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == 'f') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == 'g') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                //else if( map[i][t] == 'h') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'p') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '>')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'u') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '<')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'v') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'B')
                {
                    walls->push_back(Wall(160, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'C')
                {
                    walls->push_back(Wall(180, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(200, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(220, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'F')
                {
                    walls->push_back(Wall(200, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(180, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(180, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(200, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(220, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(200, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'I')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'J')
                {
                    walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(220, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(200, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[29] == 0) game->create_actor(69, 535, 850, 1, 29);
        game->create_actor(37, 496, 200, 1, 0);
        game->create_actor(37, 184, 360, 0, -15);
        game->create_actor(38, 480, 940, 1, 0);
        game->create_actor(41, 320, 1147, 0, 0);
        game->create_actor(44, 220, 1540, 0, 140);
        game->create_actor(44, 440, 1540, 0, 220);
        game->create_actor(1010, 760, 1300, 200, 51);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 45, 193);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 51)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(51);
        }

        texture = TEXTURES06;
        for (int i = 0; i <= 35; i++)
        {
            for ( int t = 0; t <= 359; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 20, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(140, 60, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(100, 0, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(100, 40, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'p') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '>')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'u') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '<')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'v') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'B')
                {
                    walls->push_back(Wall(160, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'C')
                {
                    walls->push_back(Wall(180, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(200, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(220, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'F')
                {
                    walls->push_back(Wall(200, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(180, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(180, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(200, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(220, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(200, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'I')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'J')
                {
                    walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(220, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(200, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[33] == 0) game->create_actor(69, 3460, 320, 1, 33);
        if (player->cards[15] == 0) game->create_actor(69, 7060, 420, 1, 15);
        game->create_actor(37, 4900, 320, 0, 0);
        game->create_actor(37, 5180, 380, 1, -10);
        game->create_actor(37, 4900, 440, 0, -20);
        game->create_actor(38, 2340, 500, 1, 0);
        game->create_actor(38, 2400, 260, 0, -40);
        game->create_actor(38, 2460, 500, 1, 0);
        game->create_actor(38, 2520, 260, 0, -40);
        game->create_actor(38, 2580, 500, 1, 0);
        game->create_actor(38, 2640, 260, 0, -40);
        game->create_actor(38, 6040, 300, 0, 0);
        game->create_actor(38, 6040, 580, 1, 0);
        game->create_actor(38, 6400, 300, 0, -40);
        game->create_actor(38, 6400, 580, 1, -40);
        game->create_actor(38, 6840, 300, 0, 0);
        game->create_actor(38, 6840, 580, 1, 0);

        game->create_actor(41, 610, 467, 0, 0);
        game->create_actor(41, 1840, 587, 0, 0);
        game->create_actor(41, 2080, 547, 0, 0);
        game->create_actor(41, 4280, 227, 0, 0);
        game->create_actor(42, 5800, 340, 0, 0);
        game->create_actor(42, 6160, 340, 0, 0);
        game->create_actor(42, 6320, 340, 1, 0);
        game->create_actor(42, 6520, 340, 0, 0);
        game->create_actor(42, 6680, 340, 0, 0);

        game->create_actor(44, 860, 520, 0, 160);
        game->create_actor(44, 1140, 520, 0, 160);
        game->create_actor(44, 3060, 520, 0, 480);
        game->create_actor(44, 4060, 300, 0, 160);
        game->create_actor(44, 4380, 300, 0, 200);

        game->create_actor(45, 1200, 540, 0, 0);
        game->create_actor(45, 4120, 320, 0, 0);
        game->create_actor(45, 4440, 320, 0, 0);

        game->create_actor(1010, 7160, 340, 160, 52);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 52)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(52);
        }

        texture = TEXTURES06;
        for (int i = 0; i <= 79; i++)
        {
            for ( int t = 0; t <= 59; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 20, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(140, 60, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(100, 0, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(100, 40, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'p') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '>')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'u') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '<')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'v') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'B')
                {
                    walls->push_back(Wall(160, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'C')
                {
                    walls->push_back(Wall(180, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(200, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(220, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'F')
                {
                    walls->push_back(Wall(200, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(180, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(180, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(200, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(220, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(200, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'I')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'J')
                {
                    walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(220, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(200, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[7] == 0) game->create_actor(69, 880, 80, 1, 7);
        game->create_actor(37, 260, 1160, 0, 0);
        game->create_actor(37, 20, 360, 0, -30);
        game->create_actor(37, 140, 440, 0, 0);

        game->create_actor(41, 140, 1027, 0, 0);
        game->create_actor(41, 860, 1387, 0, 0);
        game->create_actor(41, 620, 867, 0, 0);
        game->create_actor(41, 560, 547, 0, 0);
        game->create_actor(42, 760, 460, 0, 0);

        game->create_actor(44, 700, 320, 0, 280);

        game->create_actor(45, 740, 340, 0, 0);
        game->create_actor(45, 800, 340, 0, 0);
        game->create_actor(45, 860, 340, 0, 0);

        game->create_actor(1010, 1160, 180, 120, 53);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 53)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(53);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES06;
        for (int i = 0; i <= 119; i++)
        {
            for ( int t = 0; t <= 299; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 20, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(140, 60, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(100, 0, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(100, 40, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'p') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '>')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'u') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '<')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'v') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'B')
                {
                    walls->push_back(Wall(160, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'C')
                {
                    walls->push_back(Wall(180, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(200, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(220, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'F')
                {
                    walls->push_back(Wall(200, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(180, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(180, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(200, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(220, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(200, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'I')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'J')
                {
                    walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(220, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(200, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[45] == 0) game->create_actor(69, 3110, 320, 0, 45);
        if (player->cards[19] == 0) game->create_actor(69, 5860, 680, 0, 19);
        if (player->cards[9] == 0) game->create_actor(65, 2820, 1200, 0, 9);
        game->create_actor(37, 2980, 320, 0, 0);
        game->create_actor(37, 3180, 320, 1, -40);
        game->create_actor(37, 540, 800, 0, 0);
        game->create_actor(37, 540, 840, 0, -10);
        game->create_actor(37, 540, 880, 0, -20);
        game->create_actor(37, 780, 800, 1, -30);
        game->create_actor(37, 780, 840, 1, -40);
        game->create_actor(37, 780, 880, 1, -50);
        game->create_actor(38, 4200, 300, 1, 0);
        game->create_actor(38, 3040, 740, 1, 0);
        game->create_actor(38, 3720, 740, 1, 0);
        game->create_actor(38, 2560, 1540, 1, 0);
        game->create_actor(38, 2620, 1540, 1, -40);
        game->create_actor(38, 2680, 1540, 1, 0);

        game->create_actor(41, 1220, 267, 0, 0);
        game->create_actor(41, 3660, 347, 0, 0);
        game->create_actor(41, 4060, 347, 0, 0);
        game->create_actor(41, 3860, 347, 1, 0);
        game->create_actor(41, 4440, 347, 0, 0);
        game->create_actor(41, 1400, 1347, 0, 0);
        game->create_actor(41, 1940, 1347, 0, 0);
        game->create_actor(41, 3640, 1427, 0, 0);
        game->create_actor(41, 4200, 1427, 0, 0);
        game->create_actor(42, 3760, 140, 0, 0);
        game->create_actor(42, 4040, 140, 1, 0);
        game->create_actor(42, 2900, 620, 0, 0);
        game->create_actor(42, 3260, 620, 1, 0);
        game->create_actor(42, 3660, 620, 0, 0);
        game->create_actor(42, 4000, 620, 1, 0);

        game->create_actor(44, 980, 320, 0, 120);
        game->create_actor(44, 1500, 320, 0, 160);
        game->create_actor(44, 1740, 320, 0, 200);
        game->create_actor(44, 2020, 320, 0, 400);
        game->create_actor(44, 4760, 760, 0, 1060);
        game->create_actor(44, 2140, 760, 0, 240);
        game->create_actor(44, 1700, 760, 0, 160);
        game->create_actor(44, 1260, 760, 0, 160);
        game->create_actor(44, 1060, 760, 0, 120);
        game->create_actor(44, 5300, 2320, 0, 80);
        game->create_actor(44, 5540, 2320, 0, 140);
        game->create_actor(44, 5840, 2320, 0, 60);

        game->create_actor(45, 1600, 340, 0, 0);
        game->create_actor(45, 2100, 340, 0, 0);
        game->create_actor(45, 2360, 340, 0, 0);
        game->create_actor(45, 1760, 780, 0, 0);
        game->create_actor(45, 1100, 780, 0, 0);

        game->create_actor(1011, 4980, 1300, 0, 8);
        game->create_actor(1011, 5420, 1460, 0, 9);
        game->create_actor(1006, 5700, 2205, 1, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 60)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(60);
        }

        texture = TEXTURES07;
        for (int i = 0; i <= 33; i++)
        {
            for ( int t = 0; t <= 399; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(60, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'b') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'e') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'f') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(140, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(160, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L')
                {
                    walls->push_back(Wall(160, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(160, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(160, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(20, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(20, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(0, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q')
                {
                    walls->push_back(Wall(0, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'r')
                {
                    walls->push_back(Wall(40, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'R')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 's')
                {
                    walls->push_back(Wall(40, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(60, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 't')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(60, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'u')
                {
                    walls->push_back(Wall(100, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(100, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'v')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(80, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'w')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(80, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(120, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(120, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y')
                {
                    walls->push_back(Wall(120, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(140, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(140, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(140, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '(') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(140, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(160, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[41] == 0) game->create_actor(65, 3380, 120, 0, 41);
        if (player->cards[14] == 0) game->create_actor(69, 6180, 460, 0, 14);
        game->create_actor(67, 1840, 390, 0, 51);
        game->create_actor(50, 1140, 277, 0, 0);
        game->create_actor(50, 2500, 357, 0, 0);
        game->create_actor(50, 3540, 477, 0, 0);
        game->create_actor(50, 4880, 517, 0, 0);
        game->create_actor(50, 7460, 397, 0, 0);

        game->create_actor(51, 4184, 281, 0, 0);
        game->create_actor(52, 4219, 282, 0, 0);
        game->create_actor(51, 5624, 361, 0, 0);
        game->create_actor(52, 5659, 362, 0, 0);
        game->create_actor(51, 6404, 281, 0, 0);
        game->create_actor(52, 6439, 282, 0, 0);

        game->create_actor(53, 7140, 492, 0, 140);

        game->create_actor(1010, 7960, 300, 260, 61);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 29, 157);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 61)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(61);
        }

        texture = TEXTURES07;
        for (int i = 0; i <= 49; i++)
        {
            for ( int t = 0; t <= 399; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(60, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'b') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'e') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'f') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(140, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(160, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '0';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L')
                {
                    walls->push_back(Wall(160, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(160, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(160, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(20, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(20, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(0, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q')
                {
                    walls->push_back(Wall(0, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'r')
                {
                    walls->push_back(Wall(40, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'R')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 's')
                {
                    walls->push_back(Wall(40, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(60, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 't')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(60, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'u')
                {
                    walls->push_back(Wall(100, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(100, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'v')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(80, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'w')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(80, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(120, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(120, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y')
                {
                    walls->push_back(Wall(120, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(140, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(140, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(140, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '(') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(140, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(160, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[49] == 0) game->create_actor(69, 6540, 280, 1, 49);
        if (player->cards[18] == 0) game->create_actor(69, 5780, 720, 0, 18);
        game->create_actor(67, 7460, 810, 0, 44);
        game->create_actor(50, 1320, 877, 0, 0);
        game->create_actor(50, 1760, 577, 0, 0);
        game->create_actor(50, 2760, 517, 0, 0);
        game->create_actor(50, 3630, 517, 0, 0);
        game->create_actor(50, 6120, 337, 0, 0);
        game->create_actor(50, 5320, 817, 0, 0);
        game->create_actor(50, 7740, 737, 0, 0);

        game->create_actor(51, 544, 541, 0, 0);
        game->create_actor(52, 579, 542, 0, 0);
        game->create_actor(51, 1804, 341, 0, 0);
        game->create_actor(52, 1839, 342, 0, 0);
        game->create_actor(51, 4384, 141, 0, 0);
        game->create_actor(52, 4419, 142, 0, 0);
        game->create_actor(51, 6024, 721, 0, 0);
        game->create_actor(52, 6059, 722, 0, 0);
        game->create_actor(51, 7464, 561, 0, 0);
        game->create_actor(52, 7499, 562, 0, 0);

        game->create_actor(53, 3000, 652, 0, 200);
        game->create_actor(53, 5320, 352, 0, 140);
        game->create_actor(53, 6280, 472, 0, 240);

        game->create_actor(55, 1500, 680, 0, 0);
        game->create_actor(55, 4520, 400, 0, 0);

        game->create_actor(1010, 7960, 580, 120, 62);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 62)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(62);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else if (//doorrecord != 12) set_dvalues(//doorrecord);
        }

        texture = TEXTURES07;
        for (int i = 0; i <= 59; i++)
        {
            for ( int t = 0; t <= 199; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(60, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'b') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'e') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'f') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(140, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(160, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '0';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L')
                {
                    walls->push_back(Wall(160, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(160, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(160, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(20, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(20, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(0, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q')
                {
                    walls->push_back(Wall(0, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'r')
                {
                    walls->push_back(Wall(40, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'R')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 's')
                {
                    walls->push_back(Wall(40, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(60, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 't')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(60, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'u')
                {
                    walls->push_back(Wall(100, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(100, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'v')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(80, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'w')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(80, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(120, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(120, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y')
                {
                    walls->push_back(Wall(120, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(140, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(140, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(140, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '(') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(140, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(160, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        if (player->cards[23] == 0) game->create_actor(69, 840, 880, 1, 23);
        if (player->cards[31] == 0) game->create_actor(69, 2140, 260, 1, 31);
        game->create_actor(67, 1980, 1010, 0, 46);
        game->create_actor(1011, 620, 660, 0, 12);
        game->create_actor(999, 2740, 960, 0, 10);
        game->create_actor(999, 3350, 960, 0, 11);
        game->create_actor(2003, 2740, 960, 0, 0);
        game->create_actor(2002, 3320, 960, 0, 0);
        game->create_actor(500, 3440, 990, 0, 1);
        game->create_actor(500, 3460, 990, 0, 2);
        game->create_actor(500, 3480, 990, 0, 1);
        game->create_actor(500, 3760, 990, 0, 2);
        game->create_actor(500, 3780, 990, 0, 1);
        game->create_actor(500, 3800, 990, 0, 2);

        game->create_actor(50, 660, 257, 0, 0);
        game->create_actor(50, 1580, 337, 0, 0);
        game->create_actor(50, 3440, 377, 0, 0);
        game->create_actor(50, 1660, 617, 0, 0);
        game->create_actor(50, 2340, 617, 0, 0);
        game->create_actor(50, 3020, 617, 0, 0);
        game->create_actor(50, 880, 1097, 0, 0);
        game->create_actor(50, 1620, 1017, 0, 0);

        game->create_actor(51, 1384, 81, 0, 0);
        game->create_actor(52, 1419, 82, 0, 0);
        game->create_actor(51, 2104, 161, 0, 0);
        game->create_actor(52, 2139, 162, 0, 0);
        game->create_actor(51, 784, 521, 0, 0);
        game->create_actor(52, 819, 522, 0, 0);

        game->create_actor(53, 1220, 392, 0, 260);
        game->create_actor(53, 1940, 432, 0, 500);
        game->create_actor(53, 2600, 432, 0, 200);
        game->create_actor(53, 1400, 712, 0, 140);

        game->create_actor(55, 2140, 300, 0, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 70)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(70);
        }

        texture = TEXTURES08;
        for (int i = 0; i <= 35; i++)
        {
            for (int t = 0; t <= 499; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5')
                {
                    walls->push_back(Wall(60, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '6')
                {
                    walls->push_back(Wall(80, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(60, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',')
                {
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '<') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.')
                {
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '#')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '$')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '%')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'W') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'R') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(60, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(80, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Z') walls->push_back(Wall(0, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'X') walls->push_back(Wall(20, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(40, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'V') walls->push_back(Wall(60, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(80, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[')
                {
                    walls->push_back(Wall(0, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '^') walls->push_back(Wall(20, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '?') walls->push_back(Wall(40, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(60, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']')
                {
                    walls->push_back(Wall(80, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '7')
                {
                    walls->push_back(Wall(100, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(120, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(140, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '"')
                {
                    walls->push_back(Wall(160, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '-')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(180, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(140, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(180, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(140, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'L') walls->push_back(Wall(160, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Y') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'U') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(140, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O') walls->push_back(Wall(160, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(')
                {
                    walls->push_back(Wall(100, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == ')')
                {
                    walls->push_back(Wall(120, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '_')
                {
                    walls->push_back(Wall(140, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                    break;
                }
                else if ( map[i][t] == '{')
                {
                    walls->push_back(Wall(100, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '}')
                {
                    walls->push_back(Wall(120, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '+')
                {
                    walls->push_back(Wall(140, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
                else if ( map[i][t] == ';') walls->push_back(Wall(100, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(120, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '=')
                {
                    walls->push_back(Wall(140, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
                else if ( map[i][t] == '&') walls->push_back(Wall(100, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '|') walls->push_back(Wall(120, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '`')
                {
                    walls->push_back(Wall(140, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
                else if ( map[i][t] == '~') walls->push_back(Wall(100, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M')
                {
                    walls->push_back(Wall(140, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
            }
        }

        game->create_actor(14, 1380, 340, 0, 0);
        game->create_actor(14, 1460, 300, 0, -15);
        game->create_actor(14, 2700, 240, 0, 0);

        game->create_actor(10, 1660, 460, 0, 0);
        game->create_actor(10, 1920, 460, 1, 0);

        game->create_actor(12, 2100, 320, 0, 0);

        game->create_actor(16, 5280, 380, 2600, 170);

        game->create_actor(15, 5200, 300, 0, 0);
        game->create_actor(15, 5820, 200, 0, 0);
        game->create_actor(15, 6280, 620, 0, 0);

        game->create_actor(21, 7520, 510, 0, 0);
        game->create_actor(21, 8420, 390, 0, 0);
        game->create_actor(21, 9820, 310, 0, 0);

        game->create_actor(23, 7600, 300, 0, 0);
        game->create_actor(23, 7820, 300, 0, 0);
        game->create_actor(23, 9060, 180, 0, 0);
        game->create_actor(23, 9420, 100, 0, 0);

        game->create_actor(1010, 9960, 160, 360, 71);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 110, 278);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 71)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(71);
        }

        texture = TEXTURES08;
        for (int i = 0; i <= 39; i += 1, texture = TEXTURES08)
        {
            for (int t = 0; t <= 499; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5')
                {
                    walls->push_back(Wall(60, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '6')
                {
                    walls->push_back(Wall(80, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(60, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',')
                {
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '<') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.')
                {
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '#')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '$')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '%')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'W') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'R') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(60, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(80, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Z') walls->push_back(Wall(0, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'X') walls->push_back(Wall(20, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(40, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'V') walls->push_back(Wall(60, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(80, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[')
                {
                    walls->push_back(Wall(0, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '^') walls->push_back(Wall(20, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '?') walls->push_back(Wall(40, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(60, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']')
                {
                    walls->push_back(Wall(80, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '7')
                {
                    walls->push_back(Wall(100, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(120, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(140, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '"')
                {
                    walls->push_back(Wall(160, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '-')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(180, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(140, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(180, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(140, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'L') walls->push_back(Wall(160, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Y') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'U') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(140, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O') walls->push_back(Wall(160, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(')
                {
                    walls->push_back(Wall(100, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == ')')
                {
                    walls->push_back(Wall(120, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '_')
                {
                    walls->push_back(Wall(140, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '{')
                {
                    walls->push_back(Wall(100, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '}')
                {
                    walls->push_back(Wall(120, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '+')
                {
                    walls->push_back(Wall(140, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == ';') walls->push_back(Wall(100, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(120, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '=')
                {
                    walls->push_back(Wall(140, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '&') walls->push_back(Wall(100, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '|') walls->push_back(Wall(120, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '`')
                {
                    walls->push_back(Wall(140, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '~') walls->push_back(Wall(100, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M')
                {
                    walls->push_back(Wall(140, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                if (t == 97) texture = TEXTURES09;
            }
        }

        game->create_actor(23, 820, 140, 0, 0);
        game->create_actor(23, 1160, 140, 0, 0);

        game->create_actor(21, 1460, 450, 0, 0);

        game->create_actor(34, 2200 + 6, 573 + 13, 0, 0);
        game->create_actor(33, 2200, 573, 0, 0);
        game->create_actor(34, 3100 + 6, 653 + 13, 0, 0);
        game->create_actor(33, 3100, 653, 0, 0);
        game->create_actor(34, 4570 + 6, 573 + 13, 0, 0);
        game->create_actor(33, 4570, 573, 0, 0);
        game->create_actor(34, 4630 + 6, 533 + 13, 0, 0);
        game->create_actor(33, 4630, 533, 0, 0);
        game->create_actor(34, 3960 + 1, 613 + 13, 1, 0);
        game->create_actor(33, 3960, 613, 1, 0);

        game->create_actor(71, 2660, 800, 0, 0);
        game->create_actor(71, 3320, 800, 0, 0);
        game->create_actor(71, 4400, 800, 0, 0);

        game->create_actor(41, 5700, 407, 0, 0);
        game->create_actor(41, 6020, 487, 0, 0);
        game->create_actor(41, 6800, 567, 0, 0);

        game->create_actor(42, 6900, 320, 0, 0);
        game->create_actor(42, 7150, 320, 1, 0);
        game->create_actor(42, 7500, 320, 0, 0);
        game->create_actor(42, 7740, 320, 1, 0);

        game->create_actor(50, 8440, 557, 0, 0);
        game->create_actor(55, 8840, 540, 0, 0);
        game->create_actor(50, 9200, 557, 0, 0);

        game->create_actor(1010, 9960, 240, 240, 72);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 72)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(72);
        }

        texture = TEXTURES09;
        for (int i = 0; i <= 39; i += 1, texture = TEXTURES09)
        {
            for (int t = 0; t <= 749; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5')
                {
                    walls->push_back(Wall(60, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '6')
                {
                    walls->push_back(Wall(80, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(60, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',')
                {
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '<') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.')
                {
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '#')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '$')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '%')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'W') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'R') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(60, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(80, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Z') walls->push_back(Wall(0, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'X') walls->push_back(Wall(20, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(40, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'V') walls->push_back(Wall(60, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(80, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[')
                {
                    walls->push_back(Wall(0, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '^') walls->push_back(Wall(20, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '?') walls->push_back(Wall(40, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(60, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']')
                {
                    walls->push_back(Wall(80, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '7')
                {
                    walls->push_back(Wall(100, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(120, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(140, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '"')
                {
                    walls->push_back(Wall(160, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '-')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(180, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(140, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(180, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(140, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'L') walls->push_back(Wall(160, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Y') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'U') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(140, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O') walls->push_back(Wall(160, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(')
                {
                    walls->push_back(Wall(100, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == ')')
                {
                    walls->push_back(Wall(120, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '_')
                {
                    walls->push_back(Wall(140, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '{')
                {
                    walls->push_back(Wall(100, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '}')
                {
                    walls->push_back(Wall(120, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '+')
                {
                    walls->push_back(Wall(140, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == ';') walls->push_back(Wall(100, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(120, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '=')
                {
                    walls->push_back(Wall(140, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '&') walls->push_back(Wall(100, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '|') walls->push_back(Wall(120, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '`')
                {
                    walls->push_back(Wall(140, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '~') walls->push_back(Wall(100, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M')
                {
                    walls->push_back(Wall(140, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                if (t == 97) texture = TEXTURES08;
                if (t == 445) texture = TEXTURES09;
            }
        }

        game->create_actor(55, 780, 580, 0, 0);
        game->create_actor(50, 1080, 477, 0, 0);
        game->create_actor(55, 1400, 540, 0, 0);

        game->create_actor(14, 2240, 420, 0, 0);
        game->create_actor(14, 2880, 290, 0, 0);
        game->create_actor(14, 2960, 290, 0, -10);
        game->create_actor(10, 2660, 480, 0, 0);
        game->create_actor(10, 3100, 480, 0, 0);
        game->create_actor(12, 3500, 340, 0, 0);

        game->create_actor(16, 6340, 400, 4020, 200);
        game->create_actor(15, 4640, 620, 0, 0);
        game->create_actor(15, 5590, 480, 0, 0);
        game->create_actor(15, 6300, 340, 0, 0);

        game->create_actor(23, 7000, 260, 0, 0);
        game->create_actor(23, 7560, 160, 0, 0);
        game->create_actor(23, 8660, 300, 0, 0);
        game->create_actor(21, 7340, 450, 0, 0);
        game->create_actor(21, 8540, 530, 0, 0);

        game->create_actor(34, 10010 + 6, 693 + 13, 0, 0);
        game->create_actor(33, 10010, 693, 0, 0);
        game->create_actor(34, 10190 + 6, 653 + 13, 0, 0);
        game->create_actor(33, 10190, 653, 0, 0);
        game->create_actor(34, 9330 + 1, 693 + 13, 1, 0);
        game->create_actor(33, 9330, 693, 1, 0);
        game->create_actor(71, 9730, 800, 0, 0);
        game->create_actor(71, 10600, 800, 0, 0);
        game->create_actor(71, 10680, 800, 0, 0);

        game->create_actor(41, 11760, 527, 0, 0);
        game->create_actor(41, 12900, 527, 1, 0);
        game->create_actor(41, 13200, 567, 0, 0);
        game->create_actor(42, 11950, 440, 0, 0);
        game->create_actor(42, 12300, 440, 1, 0);
        game->create_actor(42, 12660, 440, 0, 0);
        game->create_actor(42, 12940, 440, 1, 0);

        game->create_actor(50, 13600, 517, 0, 0);
        game->create_actor(50, 14000, 437, 1, 0);
        game->create_actor(55, 14360, 360, 0, 0);

        game->create_actor(1010, 14960, 120, 200, 73);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 73)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(73);
        }

        texture = TEXTURES09;
        for (int i = 0; i <= 79; i += 1, texture = TEXTURES09)
        {
            for (int t = 0; t <= 149; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5')
                {
                    walls->push_back(Wall(60, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '6')
                {
                    walls->push_back(Wall(80, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(60, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',')
                {
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '<') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.')
                {
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '#')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '$')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '%')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'W') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'R') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(60, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(80, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Z') walls->push_back(Wall(0, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'X') walls->push_back(Wall(20, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(40, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'V') walls->push_back(Wall(60, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(80, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[')
                {
                    walls->push_back(Wall(0, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '^') walls->push_back(Wall(20, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '?') walls->push_back(Wall(40, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(60, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']')
                {
                    walls->push_back(Wall(80, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '7')
                {
                    walls->push_back(Wall(100, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(120, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(140, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '"')
                {
                    walls->push_back(Wall(160, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '-')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(180, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(140, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(180, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(140, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'L') walls->push_back(Wall(160, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Y') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'U') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(140, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O') walls->push_back(Wall(160, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(')
                {
                    walls->push_back(Wall(100, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == ')')
                {
                    walls->push_back(Wall(120, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '_')
                {
                    walls->push_back(Wall(140, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '{')
                {
                    walls->push_back(Wall(100, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '}')
                {
                    walls->push_back(Wall(120, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '+')
                {
                    walls->push_back(Wall(140, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == ';') walls->push_back(Wall(100, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(120, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '=')
                {
                    walls->push_back(Wall(140, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '&') walls->push_back(Wall(100, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '|') walls->push_back(Wall(120, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '`')
                {
                    walls->push_back(Wall(140, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                else if ( map[i][t] == '~') walls->push_back(Wall(100, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M')
                {
                    walls->push_back(Wall(140, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    if (texture == TEXTURES09) texture = TEXTURES08;
                    else texture = TEXTURES09;
                }
                if (t == 25) texture = TEXTURES08;
                if (t == 100) texture = TEXTURES09;
            }
        }

        if (lastageportal[0] == 0)
        {
            game->create_actor(73, 60, 1140, 0, 74);
            game->create_actor(2004, 31, 1140, 0, 0);
        }
        if (lastageportal[1] == 0)
        {
            game->create_actor(73, 540, 1260, 0, 75);
            game->create_actor(2004, 511, 1260, 0, 1);
        }
        if (lastageportal[2] == 0)
        {
            game->create_actor(73, 1140, 1460, 0, 76);
            game->create_actor(2004, 1111, 1460, 0, 2);
        }
        if (lastageportal[3] == 0)
        {
            game->create_actor(74, 1795, 1460, 0, 77);
            game->create_actor(2004, 1827, 1460, 0, 3);
        }
        if (lastageportal[4] == 0)
        {
            game->create_actor(74, 2395, 1260, 0, 78);
            game->create_actor(2004, 2427, 1260, 0, 4);
        }
        if (lastageportal[5] == 0)
        {
            game->create_actor(74, 2875, 1140, 0, 79);
            game->create_actor(2004, 2907, 1140, 0, 5);
        }
        game->create_actor(201, 1500, 1260, 0, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        if (lastagedoor < 4) starting = 47;
        else
        {
            starting2 = 47;
            player->direction = 1;
        }
        lastagedoor = 0;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 74)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(74);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else if (//doorrecord != 12) set_dvalues(//doorrecord);
        }

        texture = TEXTURES07;
        for (int i = 0; i <= 59; i++)
        {
            for ( int t = 0; t <= 199; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(60, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'b') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'e') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'f') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(140, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(160, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '0';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L')
                {
                    walls->push_back(Wall(160, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(160, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(160, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(20, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(20, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(0, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q')
                {
                    walls->push_back(Wall(0, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'r')
                {
                    walls->push_back(Wall(40, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'R')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 's')
                {
                    walls->push_back(Wall(40, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(60, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 't')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(60, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'u')
                {
                    walls->push_back(Wall(100, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(100, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'v')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(80, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'w')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(80, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(120, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(120, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y')
                {
                    walls->push_back(Wall(120, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(140, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(140, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(140, 120, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '(') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(140, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(160, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        game->create_actor(500, 3440, 990, 0, 1);
        game->create_actor(500, 3460, 990, 0, 2);
        game->create_actor(500, 3480, 990, 0, 1);
        game->create_actor(500, 3760, 990, 0, 2);
        game->create_actor(500, 3780, 990, 0, 1);
        game->create_actor(500, 3800, 990, 0, 2);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 75)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(75);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }
        texture = TEXTURES01;
        for (int i = 0; i <= 27; i++)
        {
            for ( int t = 0; t <= 199; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(20 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(60 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(20 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(40 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(0 , 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(40 , 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(0 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }
        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;

        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 76)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(76);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES02;
        for (int i = 0; i <= 35; i++)
        {
            for ( int t = 0; t <= 299; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(40 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40 , 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(60 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(80 , 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(60 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(80 , 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm')
                {
                    walls->push_back(Wall(100, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(100, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'w') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'q') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x')
                {
                    walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'z')
                {
                    walls->push_back(Wall(80, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
            }
        }
        game->create_actor(1002, 5700, 530, 0, 0);
        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 77)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(77);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES04;
        for (int i = 0; i <= 31; i++)
        {
            for ( int t = 0; t <= 299; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '3') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '4') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '5') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '9') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(20, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(40, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(100, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(120, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(100, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(0, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '#') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '$') walls->push_back(Wall(40, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '%') walls->push_back(Wall(60, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(80, 100, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '+') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '<') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '-') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '_') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }
        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 78)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 1;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(78);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++)
        {
            for ( int t = 0; t <= 499; t++)
            {
                if ( map[i][t] == '2')
                {
                    walls->push_back(Wall(0, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    walls->push_back(Wall(20, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '7') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(40, 20, 10, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(40, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'a')
                {
                    walls->push_back(Wall(60, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'b')
                {
                    walls->push_back(Wall(60, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'c')
                {
                    walls->push_back(Wall(80, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'd')
                {
                    walls->push_back(Wall(80, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'e')
                {
                    walls->push_back(Wall(100, 20, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'f')
                {
                    walls->push_back(Wall(100, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'g')
                {
                    walls->push_back(Wall(100, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'h') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i')
                {
                    walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'j')
                {
                    walls->push_back(Wall(40, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'k')
                {
                    walls->push_back(Wall(60, 40, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'l')
                {
                    walls->push_back(Wall(120, 0, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'm') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n')
                {
                    walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'o')
                {
                    walls->push_back(Wall(40, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'p')
                {
                    walls->push_back(Wall(60, 60, 2, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(120, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(120, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',') walls->push_back(Wall(80, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(120, 20, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(20, 40, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(40, 40, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '}') walls->push_back(Wall(20, 60, 11, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '{') walls->push_back(Wall(40, 60, 12, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));

            }
        }
        game->create_actor(1005, 9770, 570, 0, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 79)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            load_map(79);
            if (bossfight == 1)
            {
                bossfight = 0;
                set_dvalues(//doorrecord - 1);
            }
            else set_dvalues(//doorrecord);
        }

        texture = TEXTURES06;
        for (int i = 0; i <= 119; i++)
        {
            for ( int t = 0; t <= 299; t++)
            {
                if ( map[i][t] == '2') walls->push_back(Wall(20, 20, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '6') walls->push_back(Wall(140, 60, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '0') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(100, 0, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(100, 40, 1, 40, 40, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(20, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(40, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(60, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'p') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '>')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'u') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == '<')
                {
                    walls->push_back(Wall(100, 80, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    number_of_walls--;
                }
                else if ( map[i][t] == 'v') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(20, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(140, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(') walls->push_back(Wall(60, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ')') walls->push_back(Wall(60, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'B')
                {
                    walls->push_back(Wall(160, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'C')
                {
                    walls->push_back(Wall(180, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'D')
                {
                    walls->push_back(Wall(200, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'E')
                {
                    walls->push_back(Wall(220, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'F')
                {
                    walls->push_back(Wall(200, 20, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'U')
                {
                    walls->push_back(Wall(180, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'V')
                {
                    walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'W')
                {
                    walls->push_back(Wall(180, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'X')
                {
                    walls->push_back(Wall(200, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Y')
                {
                    walls->push_back(Wall(220, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Z')
                {
                    walls->push_back(Wall(200, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'I')
                {
                    walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'J')
                {
                    walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'L') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']') walls->push_back(Wall(220, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[') walls->push_back(Wall(200, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.') walls->push_back(Wall(160, 0, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
            }
        }

        game->create_actor(44, 5300, 2320, 0, 80);
        game->create_actor(44, 5540, 2320, 0, 140);
        game->create_actor(44, 5840, 2320, 0, 60);
        game->create_actor(1006, 5700, 2205, 1, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 80)
    {
        if (restart == 1)
        {
            player->imune = 0;
            game->actors.clear();
            game->walls.clear();
            howtoend = 0;
            screenx = 0;
            screeny = 0;
            restart = 0;
            player->direction = 0;
            player->timer = 0;
            player->shots = 0;
            player->x_speed = 0;
            player->y_speed = 0;
            if (player->dead == 1)
            {
                player->current_weapon = 1;
                player->hp = player->hpmax;
            }
            player->dead = 0;
            player->in_water = 0;
            limpation = 0;
            dieanimation = 0;
            input_locked = 0;
            screen_locked = 0;
            bosslife = -1;
            if (bossfight == 1) bossfight = 0;
            load_map(80);
        }

        texture = TEXTURES08;
        for (int i = 0; i <= 29; i++, texture = TEXTURES08)
        {
            for (int t = 0; t <= 124; t++)
            {
                if ( map[i][t] == '2')
                {
                    texture = TEXTURES08;
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '3')
                {
                    texture = TEXTURES09;
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '4')
                {
                    walls->push_back(Wall(40, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '5')
                {
                    walls->push_back(Wall(60, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '6')
                {
                    walls->push_back(Wall(80, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'q') walls->push_back(Wall(0, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'w') walls->push_back(Wall(20, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'e') walls->push_back(Wall(40, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'r') walls->push_back(Wall(60, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 't') walls->push_back(Wall(80, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'a') walls->push_back(Wall(0, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 's') walls->push_back(Wall(20, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'd') walls->push_back(Wall(40, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'f') walls->push_back(Wall(60, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'g') walls->push_back(Wall(80, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'z') walls->push_back(Wall(0, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'x') walls->push_back(Wall(20, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'c') walls->push_back(Wall(40, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'v') walls->push_back(Wall(60, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'b') walls->push_back(Wall(80, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ',')
                {
                    walls->push_back(Wall(0, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '<') walls->push_back(Wall(20, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '>') walls->push_back(Wall(40, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ':') walls->push_back(Wall(60, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '.')
                {
                    walls->push_back(Wall(80, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '!')
                {
                    walls->push_back(Wall(0, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '@')
                {
                    walls->push_back(Wall(20, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '#')
                {
                    walls->push_back(Wall(40, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '$')
                {
                    walls->push_back(Wall(60, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '%')
                {
                    walls->push_back(Wall(80, 100, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'Q') walls->push_back(Wall(0, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'W') walls->push_back(Wall(20, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'E') walls->push_back(Wall(40, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'R') walls->push_back(Wall(60, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'T') walls->push_back(Wall(80, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'A') walls->push_back(Wall(0, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'S') walls->push_back(Wall(20, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'D') walls->push_back(Wall(40, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'F') walls->push_back(Wall(60, 140, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'G') walls->push_back(Wall(80, 140, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Z') walls->push_back(Wall(0, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'X') walls->push_back(Wall(20, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'C') walls->push_back(Wall(40, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'V') walls->push_back(Wall(60, 160, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'B') walls->push_back(Wall(80, 160, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '[')
                {
                    walls->push_back(Wall(0, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '^') walls->push_back(Wall(20, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '?') walls->push_back(Wall(40, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '/') walls->push_back(Wall(60, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == ']')
                {
                    walls->push_back(Wall(80, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '7')
                {
                    walls->push_back(Wall(100, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '8')
                {
                    walls->push_back(Wall(120, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '9')
                {
                    walls->push_back(Wall(140, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '"')
                {
                    walls->push_back(Wall(160, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '-')
                {
                    walls->push_back(Wall(180, 0, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == 'y') walls->push_back(Wall(100, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'u') walls->push_back(Wall(120, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'i') walls->push_back(Wall(140, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'o') walls->push_back(Wall(160, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'p') walls->push_back(Wall(180, 20, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'h') walls->push_back(Wall(100, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'j') walls->push_back(Wall(120, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'k') walls->push_back(Wall(140, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'l') walls->push_back(Wall(160, 40, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'n') walls->push_back(Wall(180, 40, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'H') walls->push_back(Wall(100, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'J') walls->push_back(Wall(120, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'K') walls->push_back(Wall(140, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'L') walls->push_back(Wall(160, 60, 1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'N') walls->push_back(Wall(180, 60, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'Y') walls->push_back(Wall(100, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'U') walls->push_back(Wall(120, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'I') walls->push_back(Wall(140, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'O') walls->push_back(Wall(160, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'P') walls->push_back(Wall(180, 80, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '(')
                {
                    walls->push_back(Wall(100, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == ')')
                {
                    walls->push_back(Wall(120, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                }
                else if ( map[i][t] == '_')
                {
                    walls->push_back(Wall(140, 100,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = '1';
                    break;
                }
                else if ( map[i][t] == '{')
                {
                    walls->push_back(Wall(100, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '}')
                {
                    walls->push_back(Wall(120, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    map[i][t] = 'q';
                }
                else if ( map[i][t] == '+')
                {
                    walls->push_back(Wall(140, 120, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
                else if ( map[i][t] == ';') walls->push_back(Wall(100, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '*') walls->push_back(Wall(120, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '=')
                {
                    walls->push_back(Wall(140, 140,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
                else if ( map[i][t] == '&') walls->push_back(Wall(100, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '|') walls->push_back(Wall(120, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == '`')
                {
                    walls->push_back(Wall(140, 160,  1, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
                else if ( map[i][t] == '~') walls->push_back(Wall(100, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'm') walls->push_back(Wall(120, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                else if ( map[i][t] == 'M')
                {
                    walls->push_back(Wall(140, 180, 20, 20, 20, t * 20, i * 20, texture, game->scenario, game->foreground));
                    break;
                }
            }
        }

        game->create_actor(1008, 1215, 276, 1, 0);

        player->on_ground = true;
        player->x_position = startingpointx;
        player->y_position = startingpointy;
        player->frame = PLAYER_MOVING01;


        for (int i = 0; i < number_of_sprites; i++)
        {
            if (actors[i].type == 1000 && actors[i].timer == //doorrecord) actors[i].timer = -1;
            else if (actors[i].type == 999 && actors[i].timer == //doorrecord) actors[i].timer = -1;
        }

        starting = 1;
        input_locked = 1;
        stopall = 1;
        lastageblack = 255;
        draw();

        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 37, 389);
        if (music_volume_set == 0) midi_pause();

    }
    */
}

void Map::load_map(char mapnumber)
{
    if (mapnumber == 10)
    {
        width = 450;
        height = 28;
        limitleft = 0;
        limitright = 9000;
        limitup = 0;
        limitdown = 560;
        number = 1;
        startingpointx = 60;
        startingpointy = 200;
        water_position = 0;
        type = 1;
        map = new char* [28];

        for (int i = 0; i < 28; i++)
            map[i] = new char[450];

        fmap = fopen("Bin\\Data\\map10.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 11)
    {
        width = 40;
        height = 100;
        limitleft = 0;
        limitright = 800;
        limitup = 0;
        limitdown = 2000;
        number = 0;
        startingpointx = 0;
        startingpointy = 60;
        water_position = 0;
        type = 1;
        map = new char* [100];

        for (int i = 0; i < 100; i++)
            map[i] = new char[40];

        fmap = fopen("map11.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n'
                        //mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'
                      );
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n'
                            //mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'
                          );
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 12)
    {
        width = 420;
        height = 30;
        limitleft = 0;
        limitright = 8400;
        limitup = 0;
        limitdown = 600;
        number = 0;
        startingpointx = 0;
        startingpointy = 400;
        water_position = 0;
        type = 1;
        map = new char* [30];

        for (int i = 0; i < 30; i++)
            map[i] = new char[420];

        fmap = fopen("map12.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n'
                        //mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'
                      );
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n'
                            //mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'
                          );
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 13)
    {
        width = 40;
        height = 90;
        limitleft = 0;
        limitright = 800;
        limitup = 0;
        limitdown = 1800;
        number = 0;
        startingpointx = 0;
        startingpointy = 1680;
        water_position = 0;
        type = 1;
        map = new char* [90];

        for (int i = 0; i < 90; i++)
            map[i] = new char[40];

        fmap = fopen("map13.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 14)
    {
        width = 200;
        height = 28;
        limitleft = 0;
        limitright = 2150;
        limitup = 0;
        limitdown = 560;
        number = 0;
        startingpointx = 0;
        startingpointy = 380;
        water_position = 0;
        type = 1;
        map = new char* [28];

        for (int i = 0; i < 28; i++)
            map[i] = new char[200];

        fmap = fopen("map14.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 20)
    {
        width = 100;
        height = 24;
        limitleft = 0;
        limitright = 2000;
        limitup = 0;
        limitdown = 480;
        number = 0;
        startingpointx = 40;
        startingpointy = 260;
        water_position = 0;
        type = 1;
        number = 1;
        map = new char* [24];

        for (int i = 0; i < 24; i++)
            map[i] = new char[100];

        fmap = fopen("map20.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 21)
    {
        width = 210;
        height = 28;
        limitleft = 0;
        limitright = 4200;
        limitup = 0;
        limitdown = 560;
        number = 0;
        startingpointx = 0;
        startingpointy = 300;
        water_position = 0;
        type = 0;
        map = new char* [28];

        for (int i = 0; i < 28; i++)
            map[i] = new char[210];

        fmap = fopen("map21.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 22)
    {
        width = 120;
        height = 70;
        limitleft = 0;
        limitright = 2400;
        limitup = 0;
        limitdown = 1400;
        number = 0;
        startingpointx = 0;
        startingpointy = 120;
        water_position = 0;
        type = 0;
        map = new char* [70];

        for (int i = 0; i < 70; i++)
            map[i] = new char[120];

        fmap = fopen("map22.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 23)
    {
        width = 300;
        height = 36;
        limitleft = 0;
        limitright = 4730;
        limitup = 0;
        limitdown = 720;
        number = 0;
        startingpointx = 0;
        startingpointy = 440;
        water_position = 0;
        type = 0;
        map = new char* [36];

        for (int i = 0; i < 36; i++)
            map[i] = new char[300];

        fmap = fopen("map23.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 30)
    {
        width = 500;
        height = 30;
        limitleft = 0;
        limitright = 10000;
        limitup = 0;
        limitdown = 600;
        number = 1;
        startingpointx = 60;
        startingpointy = 400;
        water_position = 0;
        type = 1;
        map = new char* [30];

        for (int i = 0; i < 30; i++)
            map[i] = new char[500];

        fmap = fopen("map30.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 31)
    {
        width = 100;
        height = 80;
        limitleft = 0;
        limitright = 2000;
        limitup = 0;
        limitdown = 1600;
        number = 0;
        startingpointx = 0;
        startingpointy = 140;
        water_position = 0;
        type = 1;
        map = new char* [80];

        for (int i = 0; i < 80; i++)
            map[i] = new char[100];

        fmap = fopen("map31.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 32)
    {
        width = 300;
        height = 32;
        limitleft = 0;
        limitright = 4750;
        limitup = 0;
        limitdown = 640;
        number = 0;
        startingpointx = 0;
        startingpointy = 320;
        water_position = 0;
        type = 1;
        map = new char* [32];

        for (int i = 0; i < 32; i++)
            map[i] = new char[300];

        fmap = fopen("map32.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 40)
    {
        width = 450;
        height = 40;
        limitleft = 0;
        limitright = 9000;
        limitup = 0;
        limitdown = 800;
        number = 1;
        water_position = 420;
        startingpointx = 380;
        startingpointy = 220;
        type = 3;
        map = new char* [40];

        for (int i = 0; i < 40; i++)
            map[i] = new char[450];

        fmap = fopen("map40.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 41)
    {
        width = 450;
        height = 40;
        limitleft = 0;
        limitright = 9000;
        limitup = 0;
        limitdown = 800;
        number = 0;
        water_position = 200;
        startingpointx = 0;
        startingpointy = 320;
        type = 3;
        map = new char* [40];

        for (int i = 0; i < 40; i++)
            map[i] = new char[450];

        fmap = fopen("map41.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 42)
    {
        width = 500;
        height = 40;
        limitleft = 0;
        limitright = 8750;
        limitup = 0;
        limitdown = 800;
        number = 0;
        water_position = 300;
        startingpointx = 0;
        startingpointy = 260;
        type = 3;
        map = new char* [40];

        for (int i = 0; i < 40; i++)
            map[i] = new char[500];

        fmap = fopen("map42.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 50)
    {
        width = 40;
        height = 80;
        limitleft = 0;
        limitright = 800;
        limitup = 0;
        limitdown = 1600;
        number = 1;
        water_position = 0;
        startingpointx = 40;
        startingpointy = 100;
        type = 1;
        map = new char* [80];

        for (int i = 0; i < 80; i++)
            map[i] = new char[40];

        fmap = fopen("map50.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 51)
    {
        width = 360;
        height = 36;
        limitleft = 0;
        limitright = 7200;
        limitup = 0;
        limitdown = 720;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 340;
        type = 1;
        map = new char* [36];

        for (int i = 0; i < 36; i++)
            map[i] = new char[360];

        fmap = fopen("map51.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 52)
    {
        width = 60;
        height = 80;
        limitleft = 0;
        limitright = 1200;
        limitup = 0;
        limitdown = 1600;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 1420;
        type = 1;
        map = new char* [80];

        for (int i = 0; i < 80; i++)
            map[i] = new char[60];

        fmap = fopen("map52.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 53)
    {
        width = 300;
        height = 120;
        limitleft = 0;
        limitright = 6000;
        limitup = 0;
        limitdown = 2400;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 140;
        type = 1;
        map = new char* [120];

        for (int i = 0; i < 120; i++)
            map[i] = new char[300];

        fmap = fopen("map53.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 60)
    {
        width = 400;
        height = 34;
        limitleft = 0;
        limitright = 8000;
        limitup = 0;
        limitdown = 680;
        number = 1;
        water_position = 0;
        startingpointx = 60;
        startingpointy = 160;
        type = 1;
        map = new char* [34];

        for (int i = 0; i < 34; i++)
            map[i] = new char[400];

        fmap = fopen("map60.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 61)
    {
        width = 400;
        height = 50;
        limitleft = 0;
        limitright = 8000;
        limitup = 0;
        limitdown = 1000;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 740;
        type = 1;
        map = new char* [50];

        for (int i = 0; i < 50; i++)
            map[i] = new char[400];

        fmap = fopen("map61.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 62)
    {
        width = 200;
        height = 60;
        limitleft = 0;
        limitright = 4000;
        limitup = 0;
        limitdown = 1200;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 140;
        type = 1;
        map = new char* [60];

        for (int i = 0; i < 60; i++)
            map[i] = new char[200];

        fmap = fopen("map62.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 70)
    {
        width = 500;
        height = 36;
        limitleft = 0;
        limitright = 10000;
        limitup = 0;
        limitdown = 720;
        number = 1;
        water_position = 0;
        startingpointx = 100;
        startingpointy = 460;
        type = 1;
        map = new char* [36];

        for (int i = 0; i < 36; i++)
            map[i] = new char[500];

        fmap = fopen("map70.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 71)
    {
        width = 500;
        height = 40;
        limitleft = 0;
        limitright = 10000;
        limitup = 0;
        limitdown = 800;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 280;
        type = 1;
        map = new char* [40];

        for (int i = 0; i < 40; i++)
            map[i] = new char[500];

        fmap = fopen("map71.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 72)
    {
        width = 750;
        height = 40;
        limitleft = 0;
        limitright = 15000;
        limitup = 0;
        limitdown = 800;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 480;
        type = 1;
        map = new char* [40];

        for (int i = 0; i < 40; i++)
            map[i] = new char[750];

        fmap = fopen("map72.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 73)
    {
        width = 150;
        height = 80;
        limitleft = 0;
        limitright = 3000;
        limitup = 0;
        limitdown = 1600;
        number = 0;
        water_position = 0;
        startingpointx = 0;
        startingpointy = 240;
/*        if (lastagedoor == 1)
        {
            number = 1;
            startingpointx = 100;
            startingpointy = 1160;
        }
        else if (lastagedoor == 2)
        {
            number = 1;
            startingpointx = 580;
            startingpointy = 1280;
        }
        else if (lastagedoor == 3)
        {
            number = 1;
            startingpointx = 1180;
            startingpointy = 1480;
        }
        else if (lastagedoor == 4)
        {
            number = 1;
            startingpointx = 1828;
            startingpointy = 1480;
        }
        else if (lastagedoor == 5)
        {
            number = 1;
            startingpointx = 2428;
            startingpointy = 1280;
        }
        else if (lastagedoor == 6)
        {
            number = 1;
            startingpointx = 2908;
            startingpointy = 1160;
        }
        */
        type = 1;
        map = new char* [80];

        for (int i = 0; i < 80; i++)
            map[i] = new char[150];

        fmap = fopen("map73.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 74)
    {
        width = 200;
        height = 60;
        limitleft = 3320;
        limitright = 3960;
        limitup = 720;
        limitdown = 1200;
        number = 1;
        water_position = 0;
        startingpointx = 3620;
        startingpointy = 1020;
        type = 1;
        map = new char* [60];

        for (int i = 0; i < 60; i++)
            map[i] = new char[200];

        fmap = fopen("map74.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 75)
    {
        width = 200;
        height = 28;
        limitleft = 2740;
        limitright = 4000;
        limitup = 0;
        limitdown = 560;
        number = 1;
        startingpointx = 3380;
        startingpointy = 300;
        water_position = 0;
        type = 1;
        map = new char* [28];

        for (int i = 0; i < 28; i++)
            map[i] = new char[200];

        fmap = fopen("map75.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 76)
    {
        width = 300;
        height = 36;
        limitleft = 5320;
        limitright = 5960;
        limitup = 120;
        limitdown = 600;
        number = 1;
        startingpointx = 5500;
        startingpointy = 460;
        water_position = 0;
        type = 0;
        map = new char* [36];

        for (int i = 0; i < 36; i++)
            map[i] = new char[300];

        fmap = fopen("map76.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 77)
    {
        width = 300;
        height = 32;
        limitleft = 5280;
        limitright = 5920;
        limitup = 160;
        limitdown = 640;
        number = 1;
        startingpointx = 5400;
        startingpointy = 400;
        water_position = 0;
        type = 1;
        map = new char* [32];

        for (int i = 0; i < 32; i++)
            map[i] = new char[300];

        fmap = fopen("map77.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 78)
    {
        width = 500;
        height = 40;
        limitleft = 9320;
        limitright = 9960;
        limitup = 260;
        limitdown = 740;
        number = 1;
        water_position = 300;
        startingpointx = 9500;
        startingpointy = 560;
        type = 3;
        map = new char* [40];

        for (int i = 0; i < 40; i++)
            map[i] = new char[500];

        fmap = fopen("map78.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 79)
    {
        width = 300;
        height = 120;
        limitleft = 5280;
        limitright = 5920;
        limitup = 1920;
        limitdown = 2400;
        number = 1;
        water_position = 0;
        startingpointx = 5400;
        startingpointy = 2220;
        type = 1;
        map = new char* [120];

        for (int i = 0; i < 120; i++)
            map[i] = new char[300];

        fmap = fopen("map79.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }
    else if (mapnumber == 80)
    {
        width = 125;
        height = 30;
        limitleft = 840;
        limitright = 1660;
        limitup = 0;
        limitdown = 600;
        number = 1;
        water_position = 0;
        startingpointx = 930;
        startingpointy = 260;
        type = 1;
        map = new char* [30];

        for (int i = 0; i < 30; i++)
            map[i] = new char[125];

        fmap = fopen("map80.map", "rb");
        char mychar = ' ';

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                do
                {
                    mychar = getc(fmap);
                }
                while (mychar == ' ' || mychar == '\n');
                if (j == 0 && i != 0) do
                    {
                        mychar = getc(fmap);
                    }
                    while (mychar == ' ' || mychar == '\n');
                if (mychar != EOF) map[i][j] = mychar;
            }
        }

        fclose(fmap);

    }

}

void Map::set_dvalues(int number)
{
    if (number == 0)
    {
        limitleft = 2120;
        limitright = 2760;
        limitup = 0;
        limitdown = 560;
        startingpointx = 2300;
        startingpointy = 300;
        number = 1;
        //doorrecord = 0;
    }
    else if (number == 1)
    {
        limitleft = 2740;
        limitright = 4000;
        limitup = 0;
        limitdown = 560;
        //doorrecord = 1;
    }
    else if (number == 2)
    {
        limitleft = 4700;
        limitright = 5340;
        limitup = 140;
        limitdown = 620;
        startingpointx = 4840;
        startingpointy = 460;
        number = 1;
        //doorrecord = 2;
    }
    else if (number == 3)
    {
        limitleft = 5320;
        limitright = 5960;
        limitup = 140;
        limitdown = 620;
        //doorrecord = 3;
    }
    else if (number == 4)
    {
        limitleft = 4720;
        limitright = 5360;
        limitup = 160;
        limitdown = 640;
        startingpointx = 4840;
        startingpointy = 400;
        number = 1;
        //doorrecord = number;
    }
    else if (number == 5)
    {
        limitleft = 5280;
        limitright = 5920;
        limitup = 160;
        limitdown = 640;
        //doorrecord = number;
    }
    else if (number == 6)
    {
        limitleft = 8720;
        limitright = 9360;
        limitup = 280;
        limitdown = 760;
        startingpointx = 8800;
        startingpointy = 560;
        number = 1;
        //doorrecord = number;
    }
    else if (number == 7)
    {
        limitleft = 9330;
        limitright = 9970;
        limitup = 280;
        limitdown = 760;
        //doorrecord = number;
    }
    else if (number == 8)
    {
        startingpointx = 5160;
        startingpointy = 1340;
        number = 1;
        //doorrecord = number;
    }
    else if (number == 9)
    {
        limitleft = 5280;
        limitright = 5920;
        limitup = 1920;
        limitdown = 2400;
        //doorrecord = number;
    }
    else if (number == 10)
    {
        limitleft = 2740;
        limitright = 3380;
        limitup = 720;
        limitdown = 1200;
        startingpointx = 2940;
        startingpointy = 1020;
        number = 1;
        //doorrecord = number;
    }
    else if (number == 11)
    {
        limitleft = 3310;
        limitright = 3950;
        limitup = 720;
        limitdown = 1200;
        //doorrecord = number;
    }
    else if (number == 12)
    {
        limitright = 2770;
        //doorrecord = number;
    }
}
