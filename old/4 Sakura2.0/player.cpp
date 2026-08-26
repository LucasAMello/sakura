#include "player.h"
#include "game.h"

Player::Player()
{
    key_up = KEY_UP;
    key_down = KEY_DOWN;
    key_right = KEY_RIGHT;
    key_left = KEY_LEFT;
    key_jump = KEY_F;
    key_fire = KEY_D;
    key_weapon1 = KEY_S;
    key_weapon2 = KEY_A;
    key_menu = KEY_ENTER;
    key_quit = KEY_ESC;
    current_weapon = 1;
    vidas = 5;
    score = 0;
    hpmax = 15;

    for (int i = 0; i < 52; i++)
        cards[i] = 1;
}

void Player::move_player(BITMAP *scenario, Map *map, bool x, bool y)
{

    ActorList::iterator it;

    if (x && x_speed > 0)
    {
        for (it = game->actors.begin(); it != game->actors.end(); it++)
        {
            if (it->type == 2000 || it->type == 2001 || it->type == 401)
            {
                char col = 'n';
                if (((int)it->y_position > (int)y_position)
                        && ((int)it->y_position - (int)y_position <= 80))
                {
                    if (x_position + 40 <= it->x_position && x_position + 40 + x_speed > it->x_position) col = 'p';
                }
                else if (((int)it->y_position <= (int)y_position)
                         && ((int)y_position - (int)it->y_position <= it->height))
                {
                    if (x_position + 40 <= it->x_position && x_position + 40 + x_speed > it->x_position) col = 'p';
                }
                if (col != 'n')
                {
                    x_position = it->x_position - 40;
                    x_speed = 0;
                    return;
                }
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39 +(x_speed)) / 20)] == '.' ||
            map->map[(int)((y_position + 79 - x_speed) / 20)][(int)((x_position + 39 +(x_speed)) / 20)] == '.' ||
            map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39 +(x_speed)) / 20)] == '}' ||
            map->map[(int)((y_position + 79 - x_speed) / 20)][(int)((x_position + 39 +(x_speed)) / 20)] == '}' ||
            map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39 +(x_speed)) / 20)] == '{' ||
            map->map[(int)((y_position + 79 - x_speed) / 20)][(int)((x_position + 39 +(x_speed)) / 20)] == '{')
        {
            x_position += x_speed;
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255)) y_position--;
            if (in_water == 1 && y_position + 29 < map->water_position && map->water_position != 0)
            {
                game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
                in_water = 0;
            }
        }
        else if ((map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ',') ||
                 (map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ',') ||
                 (map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ',') ||
                 (map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ','))
        {
            x_speed = 0;
            while ((int)x_position % 20 != 0) x_position++;
            if (y_speed == 0)
            {
                y_speed = 0.1;
                if (in_water == 0) timer = -21;
                else
                {
                    timer = -5;
                    y_speed = 0.40;
                }
                test_fall = 1;
                if (on_ground == false) test_fall = 0;
                on_ground = false;
                y = true;
            }
        }
        else if (map->map[(int)((y_position + 79 + x_speed) / 20)][(int)((x_position + 39 + (x_speed)) / 20)] == '1' && map->water_position != 0)
        {
            x_position += x_speed;
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255)) y_position--;
            if (y_speed == 0)
            {
                y_speed = 0.1;
                if (in_water == 0) timer = -21;
                else
                {
                    timer = -5;
                    y_speed = 0.40;
                }
                test_fall = 1;
                if (on_ground == false) test_fall = 0;
                on_ground = false;
                y = true;
            }
        }
        else if (map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 40 + (x_speed)) / 20)] != ',')
        {
            x_speed = 0;
            while ((int)x_position % 20 != 0) x_position++;
        }
        else
        {
            x_position += x_speed;
            if (y_speed == 0)
            {
                y_speed = 0.1;
                if (in_water == 0) timer = -21;
                else
                {
                    timer = -5;
                    y_speed = 0.40;
                }
                test_fall = 1;
                if (on_ground == false) test_fall = 0;
                on_ground = false;
                y = true;
            }
        }
    }

    else if (x && x_speed < 0)
    {
        for (it = game->actors.begin(); it != game->actors.end(); it++)
        {
            if (it->type == 2000 || it->type == 2001 || it->type == 401)
            {
                char col = 'p';
                x_position += x_speed;
                if (((int)it->x_position > (int)x_position) && ((int)it->x_position - (int)x_position >= 40)) col = 'n';
                else if (((int)it->x_position <= (int)x_position) && ((int)x_position - (int)it->x_position >= it->width)) col = 'n';
                if (((int)it->y_position > (int)y_position) && ((int)it->y_position - (int)y_position >= 80)) col = 'n';
                else if (((int)it->y_position <= (int)y_position) && ((int)y_position - (int)it->y_position >= it->height)) col = 'n';
                if (col != 'n')
                {
                    x_position = it->x_position + it->width;
                    x_speed = 0;
                    return;
                }
                x_position -= x_speed;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position + (x_speed)) / 20)] == ',' ||
            map->map[(int)((y_position + 79 + x_speed) / 20)][(int)((x_position + (x_speed)) / 20)] == ',' ||
            map->map[(int)((y_position + 79) / 20)][(int)((x_position + (x_speed)) / 20)] == '[' ||
            map->map[(int)((y_position + 79 + x_speed) / 20)][(int)((x_position + (x_speed)) / 20)] == '[' ||
            map->map[(int)((y_position + 79) / 20)][(int)((x_position + (x_speed)) / 20)] == ']' ||
            map->map[(int)((y_position + 79 + x_speed) / 20)][(int)((x_position + (x_speed)) / 20)] == ']')
        {
            x_position += x_speed;
            if (x_position < 0) x_position = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255)) y_position--;
            if (in_water == 1 && y_position + 29 < map->water_position && map->water_position != 0)
            {
                game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
                in_water = 0;
            }
        }
        else if ((map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ',') ||
                 (map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 20) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ',') ||
                 (map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 40) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ',') ||
                 (map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 60) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ','))
        {
            x_speed = 0;
            while ((int)x_position % 20 != 0) x_position--;
            if (x_position < 0) x_position = 0;
            if (y_speed == 0)
            {
                y_speed = 0.1;
                if (in_water == 0) timer = -21;
                else
                {
                    timer = -5;
                    y_speed = 0.40;
                }
                test_fall = 1;
                if (on_ground == false) test_fall = 0;
                on_ground = false;
                y = true;
            }
        }
        else if (map->map[(int)((y_position + 79 + x_speed) / 20)][(int)((x_position + (x_speed)) / 20)] == '1' && map->water_position != 0)
        {
            x_position += x_speed;
            if (x_position < 0) x_position = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255)) y_position--;
            if (in_water == 1 && y_position + 29 < map->water_position && map->water_position != 0)
            {
                game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
                in_water = 0;
            }
            if (y_speed == 0)
            {
                y_speed = 0.1;
                if (in_water == 0) timer = -21;
                else
                {
                    timer = -5;
                    y_speed = 0.40;
                }
                test_fall = 1;
                if (on_ground == false) test_fall = 0;
                on_ground = false;
                y = true;
            }
        }
        else if (map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '1' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '.' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '[' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ']' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '}' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != '{' &&
                 map->map[(int)((y_position + 79) / 20)][(int)((x_position + 0.1 + (x_speed)) / 20)] != ',')
        {
            x_speed = 0;
            while ((int)x_position % 20 != 0) x_position--;
            if (x_position < 0) x_position = 0;
        }
        else
        {
            x_position += x_speed;
            if (x_position < 0) x_position = 0;
            if (y_speed == 0)
            {
                y_speed = 0.1;
                if (in_water == 0) timer = -21;
                else
                {
                    timer = -5;
                    y_speed = 0.40;
                }
                test_fall = 1;
                if (on_ground == false) test_fall = 0;
                on_ground = false;
                y = true;
            }
        }
    }

    if (y && y_speed < 0)
    {
        for (it = game->actors.begin(); it != game->actors.end(); it++)
        {
            if (it->type == 2000 || it->type == 2001 || it->type == 401)
            {
                char col = 'n';
                if (((int)it->x_position > (int)x_position)
                        && ((int)it->x_position - (int)x_position <= 40))
                {
                    if ((int)y_position >= (it->y_position + it->height) && y_position + (y_speed * 5) < (it->y_position + it->height)) col = 'p';
                }
                else if (((int)it->x_position <= (int)x_position)
                         && ((int)x_position - (int)it->x_position <= it->width))
                {
                    if ((int)y_position >= (it->y_position + it->height) && y_position + (y_speed * 5) < (it->y_position + it->height)) col = 'p';
                }
                if (col != 'n')
                {
                    y_position = it->y_position + it->height;
                    if (y_position < 0) y_position = 0;
                    on_ground = false;
                    timer++;
                    return;
                }
            }
        }
        if (map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)(x_position / 20)] != '1' &&
                map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)(x_position / 20)] != '.' &&
                map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)(x_position / 20)] != ',')
        {
            while ((int)y_position % 20 != 0) y_position--;
            on_ground = false;
            timer++;
        }
        else if (map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)((x_position + 20) / 20)] != '1' &&
                 map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)((x_position + 20) / 20)] != '.' &&
                 map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)((x_position + 20) / 20)] != ',')
        {
            while ((int)y_position % 20 != 0) y_position--;
            on_ground = false;
            timer++;
        }
        else if (map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)((x_position + 39) / 20)] != '1' &&
                 map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)((x_position + 39) / 20)] != '.' &&
                 map->map[(int)((y_position + (y_speed * 5)) / 20)][(int)((x_position + 39) / 20)] != ',')
        {
            while ((int)y_position % 20 != 0) y_position--;
            on_ground = false;
            timer++;
        }
        else
        {
            y_position += (y_speed * 5);
            if (y_position < 0) y_position = 0;
            on_ground = false;
            timer++;
            if (in_water == 1 && y_position + 29 < map->water_position && map->water_position != 0)
            {
                game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
                in_water = 0;
            }
        }
    }

    if (y && y_speed > 0 && on_ground == false)
    {
        for (it = game->actors.begin(); it != game->actors.end(); it++)
        {
            if (it->type == 2000 || it->type == 2001 || it->type == 500 || it->type == 53)
            {
                char col = 'n';
                if (((int)it->x_position > (int)x_position)
                        && ((int)it->x_position - (int)x_position <= 40))
                {
                    if ((int)y_position + 80 <= (int)it->y_position && (int)y_position + 80 + (y_speed * 5) > (int)it->y_position) col = 'p';
                }
                else if (((int)it->x_position <= (int)x_position)
                         && ((int)x_position - (int)it->x_position <= it->width))
                {
                    if ((int)y_position + 80 <= (int)it->y_position && (int)y_position + 80 + (y_speed * 5) > (int)it->y_position) col = 'p';
                }
                //y_position += (y_speed * 5);
                //if (((int)it->x_position > (int)x_position) && ((int)it->x_position - (int)x_position >= 40)) col = 'n';
                //else if (((int)it->x_position <= (int)x_position) && ((int)x_position - (int)it->x_position >= it->width)) col = 'n';
                //if (((int)it->y_position > (int)y_position) && ((int)it->y_position - (int)y_position >= 80)) col = 'n';
                //else if (((int)it->y_position <= (int)y_position) && ((int)y_position - (int)it->y_position >= it->height)) col = 'n';
                if (col != 'n')
                {
                    y_position = it->y_position - 80;
                    y_speed = 0;
                    on_ground = true;
                    timer = 0;
                    if (test_fall == 1) test_fall = 0;
                    else game->force_draw = 1;
                    return;
                }
                //y_position -= (y_speed * 5);
            }
        }
        if (map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != '1' &&
                map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != '.' &&
                map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != '[' &&
                map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != ']' &&
                map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != '}' &&
                map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != '{' &&
                map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] != ',')
        {
            if (map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)(x_position / 20))] == '0')
            {
                dead = 1;
                return;
            }
            while ((int)y_position % 20 != 0) y_position++;
            y_speed = 0;
            on_ground = true;
            timer = 0;
            if (test_fall == 1) test_fall = 0;
            else game->force_draw = 1;
        }
        else if (map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != '1' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != '.' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != '[' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != ']' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != '}' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != '{' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] != ',')
        {
            if (map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 20) / 20))] == '0')
            {
                dead = 1;
                return;
            }
            while ((int)y_position % 20 != 0) y_position++;
            y_speed = 0;
            on_ground = true;
            timer = 0;
            if (test_fall == 1) test_fall = 0;
            else game->force_draw = 1;
        }
        else if (map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != '1' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != '.' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != '[' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != ']' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != '}' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != '{' &&
                 map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] != ',')
        {
            if (map->map[(int)((y_position + 79 + (y_speed * 5)) / 20)][((int)((x_position + 39) / 20))] == '0')
            {
                dead = 1;
                return;
            }
            while ((int)y_position % 20 != 0) y_position++;
            y_speed = 0;
            on_ground = true;
            timer = 0;
            if (test_fall == 1) test_fall = 0;
            else game->force_draw = 1;
        }
        else
        {
            y_position += (y_speed * 5);
            on_ground = false;
            timer--;
            test_fall = 0;
            if (in_water == 0 && y_position + 24 >= map->water_position && map->water_position != 0)
            {
                game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
                in_water = 1;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position) / 20)] == ',' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 20) / 20)] == ',' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39) / 20)] == ',')
        {
            int tcheck = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 20, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            if (tcheck > 0)
            {
                y_speed = 0;
                on_ground = true;
                timer = 0;
                if (test_fall == 1) test_fall = 0;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position) / 20)] == '.' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 20) / 20)] == '.' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39) / 20)] == '.')
        {
            int tcheck = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 20, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            if (tcheck > 0)
            {
                y_speed = 0;
                on_ground = true;
                timer = 0;
                if (test_fall == 1) test_fall = 0;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position) / 20)] == '[' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 20) / 20)] == '[' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39) / 20)] == '[')
        {
            int tcheck = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 20, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            if (tcheck > 0)
            {
                y_speed = 0;
                on_ground = true;
                timer = 0;
                if (test_fall == 1) test_fall = 0;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position) / 20)] == ']' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 20) / 20)] == ']' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39) / 20)] == ']')
        {
            int tcheck = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 20, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            if (tcheck > 0)
            {
                y_speed = 0;
                on_ground = true;
                timer = 0;
                if (test_fall == 1) test_fall = 0;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position) / 20)] == '}' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 20) / 20)] == '}' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39) / 20)] == '}')
        {
            int tcheck = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 20, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            if (tcheck > 0)
            {
                y_speed = 0;
                on_ground = true;
                timer = 0;
                if (test_fall == 1) test_fall = 0;
            }
        }
        if (map->map[(int)((y_position + 79) / 20)][(int)((x_position) / 20)] == '{' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 20) / 20)] == '{' ||
                map->map[(int)((y_position + 79) / 20)][(int)((x_position + 39) / 20)] == '{')
        {
            int tcheck = 0;
            while (getpixel(scenario, (int)x_position, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 20, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            while (getpixel(scenario, (int)x_position + 39, (int)y_position + 79) != makecol(255,0,255))
            {
                y_position--;
                tcheck++;
            }
            if (tcheck > 0)
            {
                y_speed = 0;
                on_ground = true;
                timer = 0;
                if (test_fall == 1) test_fall = 0;
            }
        }
    }

    if (in_water == 0 && y_position + 24 >= map->water_position && map->water_position != 0)
    {
        game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
        in_water = 1;
    }
    else if (in_water == 1 && y_position + 29 < map->water_position && map->water_position != 0)
    {
        game->create_actor(SPLASH_, (int)x_position - 4, map->water_position - 14, 0, 0);
        in_water = 0;
    }

    if (x_position < 0) x_position = 0;
}

void Player::player_colision()
{
    /*
    int it;
    for (it = 0; it < 100; it++)
    {
        if (it->active && (it->type == 10 || it->type == 11 || it->type == 12 || it->type == 13 || it->type == 14 || it->type == 15
                || it->type == 200 || it->type == 201 || it->type == 999 || it->type == 1000 || it->type == 1001 || it->type == 1002 || it->type == 1003 || it->type == 1010 || it->type == 1011
                || it->type == 17 || it->type == 18 || it->type == 19 || it->type == 20 || it->type == 21 || it->type == 22 || it->type == 23
                || it->type == 24 || it->type == 26 || it->type == 29 || it->type == 30 || it->type == 32 || it->type == 33 || it->type == 34
                || it->type == 35 || it->type == 1004 || it->type == 36 || it->type == 39 || it->type == 40 || it->type == 41 || it->type == 42
                || it->type == 43 || it->type == 44 || it->type == 45 || it->type == 46 || it->type == 47 || it->type == 48 || it->type == 49 || it->type == 74
                || it->type == 50 || it->type == 51 || it->type == 52 || it->type == 53 || it->type == 54 || it->type == 55 || it->type == 56 || it->type == 73
                || it->type == 62 || it->type == 1005 || it->type == 1006 || it->type == 1007 || it->type == 69 || it->type == 64 || it->type == 202
                || it->type == 72 || it->type == 75 || it->type == 77 || it->type == 78 || it->type == 79 || it->type == 80 || it->type == 1008))
        {
            char col = 'p';
            if (it->type == 53)
            {
                if (((int)it->x_position > (int)x_position) && ((int)it->x_position - (int)x_position >= 40)) col = 'n';
                else if (((int)it->x_position <= (int)x_position) && ((int)x_position - (int)it->x_position >= it->width)) col = 'n';
                if (((int)it->y_position > (int)y_position) && ((int)it->y_position - (int)y_position > 80)) col = 'n';
                else if (((int)it->y_position <= (int)y_position) && ((int)y_position - (int)it->y_position >= it->height)) col = 'n';
            }
            else
            {
                if (((int)it->x_position > (int)x_position) && ((int)it->x_position - (int)x_position >= 40)) col = 'n';
                else if (((int)it->x_position <= (int)x_position) && ((int)x_position - (int)it->x_position >= it->width)) col = 'n';
                if (((int)it->y_position > (int)y_position) && ((int)it->y_position - (int)y_position >= 80)) col = 'n';
                else if (((int)it->y_position <= (int)y_position) && ((int)y_position - (int)it->y_position >= it->height)) col = 'n';
            }
            if (col != 'n')
            {
                if (it->type == 1000)
                {
                    if (direction == 0)
                    {
                        if (it->direction == 0)
                            x_position = it->x_position - 40;
                        set_dvalues(it->timer);
                        stopall = 1;
                        it->height = 0;
                        input_locked = 1;
                        screen_locked = 1;
                        movingscreen = 1;
                        looper = 1;
                    }
                    else
                    {
                        x_speed = 0;
                        if (direction == 0) x_position = it->x_position - 40;
                        else x_position = it->x_position + 30;
                    }
                }
                else if (it->type == 999)
                {
                    if (direction == 0)
                    {
                        if (it->direction == 0)
                            x_position = it->x_position - 40;
                        set_dvalues(it->timer);
                        stopall = 1;
                        it->height = 0;
                        input_locked = 1;
                        screen_locked = 1;
                        movingscreen = 1;
                        looper = 1;
                    }
                    else
                    {
                        x_speed = 0;
                        if (direction == 0) x_position = it->x_position - 40;
                        else x_position = it->x_position + 30;
                    }
                }
                else if (it->type == 53)
                {
                    if (input_locked == 0)
                    {
                        damage(it->strength);
                    }
                }
                else if (it->type == 1010)
                {
                    stopall = 1;
                    input_locked = 1;
                    screen_locked = 1;
                    if (on_ground == false)
                    {
                        if (timer >= 0) timer = -1;
                        if (on_ground == false && timer < 0)
                        {
                            if (timer < 0 && timer > -11) y_speed+=0.04;
                            else if (timer < -10 && timer > -21) y_speed+=0.06;
                            else if (timer < -20 && timer > -31) y_speed+=0.1;
                            if (y_speed <= 0) timer = 0;
                            else move_player(0, 1);
                        }
                    }
                    else
                    {
                        stopall = 1;
                        input_locked = 1;
                        screen_locked = 1;
                        x_speed = 2;
                        x_position += 2;
                        next_level += 1;
                        if (next_level == 40)
                        {
                            current_level = it->timer;
                            stopall = 1;
                            input_locked = 1;
                            screen_locked = 1;
                            next_level = 0;
                            paulaumfromhell = 1;
                            setup_game();
                        }
                    }
                }
                else if (it->type == 73)
                {
                    stopall = 1;
                    input_locked = 1;
                    screen_locked = 1;
                    if (on_ground == false)
                    {
                        if (timer >= 0) timer = -1;
                        if (on_ground == false && timer < 0)
                        {
                            if (timer < 0 && timer > -11) y_speed+=0.04;
                            else if (timer < -10 && timer > -21) y_speed+=0.06;
                            else if (timer < -20 && timer > -31) y_speed+=0.1;
                            if (y_speed <= 0) timer = 0;
                            else move_player(0, 1);
                        }
                    }
                    else
                    {
                        if (x_position + 10 > it->x_position)
                        {
                            stopall = 1;
                            input_locked = 1;
                            screen_locked = 1;
                            direction = 1;
                            x_speed = -2;
                            x_position -= 2;
                        }
                        else
                        {
                            current_level = it->extra_int;
                            stopall = 1;
                            input_locked = 1;
                            screen_locked = 1;
                            paulaumfromhell = 1;
                            lastagedoor = it->extra_int - 73;
                            setup_game();
                            finishing = 0;
                        }
                    }
                }
                else if (it->type == 74)
                {
                    stopall = 1;
                    input_locked = 1;
                    screen_locked = 1;
                    if (on_ground == false)
                    {
                        if (timer >= 0) timer = -1;
                        if (on_ground == false && timer < 0)
                        {
                            if (timer < 0 && timer > -11) y_speed+=0.04;
                            else if (timer < -10 && timer > -21) y_speed+=0.06;
                            else if (timer < -20 && timer > -31) y_speed+=0.1;
                            if (y_speed <= 0) timer = 0;
                            else move_player(0, 1);
                        }
                    }
                    else
                    {
                        if (x_position + 30 < it->x_position + 65)
                        {
                            stopall = 1;
                            input_locked = 1;
                            screen_locked = 1;
                            direction = 0;
                            x_speed = 2;
                            x_position += 2;
                        }
                        else
                        {
                            current_level = it->extra_int;
                            stopall = 1;
                            input_locked = 1;
                            screen_locked = 1;
                            paulaumfromhell = 1;
                            lastagedoor = it->extra_int - 73;
                            setup_game();
                            finishing = 0;
                        }
                    }
                }
                else if (it->type == 1011)
                {
                    call_event = it->timer;
                    callevent(call_event);
                    it->active = 0;
                }
                else if (it->type == 1007 && it->frame == ICYUP03)
                {
                    if (it->direction == 0)
                    {
                        if (x_position > it->x_position + 58 && y_position > it->y_position + 57) continue;
                        else if (input_locked == 0)
                        {
                            damage(it->strength);
                        }
                    }
                    else if (it->direction == 1)
                    {
                        if (x_position + 40 < it->x_position + 61 && y_position > it->y_position + 57) continue;
                        else if (input_locked == 0)
                        {
                            damage(it->strength);
                        }
                    }
                }
                else if (it->type == 1008)
                {
                    if (it->extra_int >= 128)
                    {
                        damage(it->strength);
                    }
                }
                else if (it->type == 46 && it->action_state == 2)
                {
                    rest(1);
                }
                else if (it->type == 69)
                {
                    if (it->action_state != 3)
                    {
                        it->action_state = 3;
                        score++;
                        if (score == 10)
                        {
                            hpmax = 16;
                            sparkmandril = 1;
                            play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        }
                        else if (score == 20)
                        {
                            hpmax = 17;
                            sparkmandril = 1;
                            play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        }
                        else if (score == 30)
                        {
                            hpmax = 18;
                            sparkmandril = 1;
                            play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        }
                        else if (score == 40)
                        {
                            hpmax = 19;
                            sparkmandril = 1;
                            play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        }
                        else if (score == 52)
                        {
                            hpmax = 20;
                            sparkmandril = 1;
                            play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        }
                        play_sample((SAMPLE *)mydatafile[CARDGET].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                }
                else if (it->type == 202)
                {
                    it->active = 0;
                    if (vidas < 9) vidas++;
                    play_sample((SAMPLE *)mydatafile[RECUPERATORS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (it->type == 75)
                {
                    if (input_locked == 0 && it->extra_int == 255) damage(it->strength);
                }
                else if (it->type == 77)
                {
                    if (input_locked == 0 && it->extra_int == 255) damage(it->strength);
                }
                else if (it->type == 78)
                {
                    if (input_locked == 0 && it->extra_int == 255) damage(it->strength);
                }
                else if (input_locked == 0)
                {
                    damage(it->strength);
                    if (it->type == 13) animation(it);
                    else if (it->type == 20) animation(it);
                    else if (it->type == 22) it->active = 0;
                    else if (it->type == 200)
                    {
                        it->active = 0;
                        play_sample((SAMPLE *)mydatafile[RECUPERATORS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (it->type == 201)
                    {
                        it->active = 0;
                        play_sample((SAMPLE *)mydatafile[RECUPERATORS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (it->type == 46)
                    {
                        it->active = 0;
                    }
                    else if (it->type == 47 && it->action_state == 0)
                    {
                        it->action_state = 2;
                        it->timer = 0;
                        it->x_position = x_position + 40;
                    }
                }
            }
        }
    }
*/
}
