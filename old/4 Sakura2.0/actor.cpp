#include "actor.h"
#include "game.h"

Actor::Actor(ActorType t, int x, int y, int d, int time)
{
    rotate_factor = timer = 0;

    for (int i = 0; i < 7; i++)
        hittable[i] = false;

    if (t == YELLOW_SHOT)
    {
        active = 1;
        type = t;
        width = 10;
        height = 10;
        frame = YELLOW_TOSKO_SHOT;
        direction = d;
        x_position = x;
        y_position = y;
        if (direction == 0) x_speed = 1.25;
        else x_speed = -1.25;
        play_sample((SAMPLE *)mydatafile[TIRO1].dat, (int)(205 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == WIND_SHOT)
    {
        active = 1;
        type = t;
        width = 65;
        height = 32;
        frame = WIND_SHOT01;
        direction = d;
        x_position = x;
        y_position = y;
        if (direction == 0) x_speed = 0.75;
        else x_speed = -0.75;
        timer = 1;
        play_sample((SAMPLE *)mydatafile[TIRO2].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == SHADOW_SHOT)
    {
        active = 1;
        type = t;
        width = 30;
        height = 30;
        frame = SHADOWSHOT;
        direction = d;
        x_position = x;
        y_position = y;
        if (direction == 0) x_speed = 5;
        else x_speed = -5;
        y_speed = 3;
        play_sample((SAMPLE *)mydatafile[TIRO3].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == THUNDER_SHOT)
    {
        active = 1;
        type = t;
        width = 16;
        height = 16;
        frame = ZOCK01;
        direction = d;
        x_position = x;
        y_position = y;
        if (direction == 0) x_speed = 1.25;
        else x_speed = -1.25;
        play_sample((SAMPLE *)mydatafile[TIRO4].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == WATER_SHOT)
    {
        active = 1;
        type = t;
        width = 29;
        height = 29;
        frame = WATERSHOT;
        direction = d;
        x_position = x;
        y_position = y;
        if (direction == 0) x_speed = 1.25;
        else x_speed = -1.25;
        y_speed = -0.25;
        play_sample((SAMPLE *)mydatafile[TIRO5].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == FIRE_SHOT)
    {
        active = 1;
        type = t;
        width = 34;
        height = 24;
        frame = HADOUKEN01;
        direction = d;
        x_position = x;
        y_position = y;
        if (direction == 0) x_speed = -2;
        else x_speed = +2;
        play_sample((SAMPLE *)mydatafile[TIRO6].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == ICE_SHOT)
    {
        active = 1;
        type = t;
        width = 47;
        height = 19;
        frame = ICYATTACK04;
        direction = d;
        x_position = x;
        y_position = y;
        play_sample((SAMPLE *)mydatafile[TIRO7].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == RED_BALL)
    {
        active = 1;
        type = t;
        width = 40;
        height = 40;
        frame = REDBALL01;
        x_position = x;
        y_position = y;
        x_speed = 0.8;
        hit_points_left = 5;
        direction = d;
        strength = 1;
        for (int i = 0; i < 7; i++)
            hittable[i] = true;
    }
    else if (t == SPRING)
    {
        active = 1;
        type = t;
        width = 40;
        height = 60;
        frame = MOLA_FELIZ;
        x_position = x;
        y_position = y;
        y_speed = 3;
        hit_points_left = 6;
        direction = d;
        extra_int = y;
        strength = 3;
        timer = time;
        for (int i = 0; i < 7; i++)
            hittable[i] = true;
    }
    else if (t == TURRET_ENEMY)
    {
        active = 1;
        type = t;
        width = 60;
        height = 60;
        frame = GREEN_TURRET;
        x_position = x;
        y_position = y;
        hit_points_left = 10;
        strength = 5;
        direction = d;
        for (int i = 0; i < 7; i++)
            hittable[i] = true;
    }
    else if (t == TURRET_ENEMY_SHOT)
    {
        active = 1;
        type = t;
        timer = 20;
        width = 20;
        height = 10;
        frame = TURRET_SHOT;
        x_position = x;
        y_position = y;
        x_speed = 4;
        hit_points_left = 1;
        strength = 4;
        direction = d;
        for (int i = 0; i < 7; i++)
            hittable[i] = true;
        if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[TURRET].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (t == SMALL_BIRD)
    {
        active = 1;
        type = t;
        width = 37;
        height = 33;
        frame = PIRIKITO;
        x_position = x;
        y_position = y;
        y_speed = 0;
        hit_points_left = 3;
        strength = 2;
        extra_int = y;
        direction = d;
        timer = time;
        for (int i = 0; i < 7; i++)
            hittable[i] = true;
    }
    /*    else if (t == GHOST)
        {
            active = 1;
            type = 15;
            width = 40;
            height = 51;
            frame = GHOST01;
            x_position = x;
            y_position = y;
            hit_points_left = 5;
            direction = d;
            strength = 2;
        }
        else if (t == PHANTOM_SPAWNER)
        {
            active = 1;
            type = 16;
            width = 1;
            height = 1;
            frame = NULO;
            x_position = x;
            y_position = y;
            y_speed = time;
            x_speed = direction;
            hit_points_left = 1;
            direction = 0;
            timer = 40;
        }
        else if (t == PHANTOM)
        {
            active = 1;
            type = 17;
            width = 70;
            height = 30;
            frame = GHOSTMASK01;
            x_position = x;
            y_position = y;
            x_speed = 5;
            extra_int = time;
            hit_points_left = 2;
            direction = d;
            strength = 2;
            action_state = 160;
        }
        else if (t == PHANTOM_SPAWNER2)
        {
            active = 1;
            type = 61;
            width = 1;
            height = 1;
            frame = NULO;
            x_position = x;
            y_position = y;
            y_speed = time;
            x_speed = direction;
            hit_points_left = 1;
            direction = 1;
            timer = 40;
        }
        else if (t == PHANTOM2)
        {
            active = 1;
            type = 62;
            width = 70;
            height = 30;
            frame = GHOSTMASK01;
            x_position = x;
            y_position = y;
            x_speed = 5;
            extra_int = time;
            hit_points_left = 2;
            direction = d;
            strength = 2;
            action_state = 160;
        }
        else if (t == 63)
        {
            active = 1;
            type = t;
            width = 40;
            height = 40;
            frame = WALLMAGIC;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
        }
        else if (t == WALL_TURRET)
        {
            if (direction == 0)
            {
                active = 1;
                type = 19;
                width = 40;
                height = 20;
                frame = WALLTURRET;
                x_position = x;
                y_position = y;
                direction = d;
                hit_points_left = 5;
                strength = 2;
                timer = time;
            }
            else if (direction == 1)
            {
                active = 1;
                type = 19;
                width = 20;
                height = 40;
                frame = WALLTURRET;
                x_position = x;
                y_position = y;
                direction = d;
                hit_points_left = 5;
                strength = 2;
                rotate_factor = 192;
                timer = time;
            }
            else if (direction == 2)
            {
                active = 1;
                type = 19;
                width = 20;
                height = 40;
                frame = WALLTURRET;
                x_position = x;
                y_position = y;
                direction = d;
                hit_points_left = 5;
                strength = 2;
                rotate_factor = 64;
                timer = time;
            }
        }
        else if (t == WALL_TURRET_SHOT)
        {
            active = 1;
            type = 20;
            width = 8;
            height = 8;
            frame = WTSHOT01;
            x_position = x;
            y_position = y;
            direction = d;
            hit_points_left = 1;
            strength = 2;
            if (direction == 0)
            {
                x_speed = -10;
                y_speed = 10;
            }
            else if (direction == 3)
            {
                x_speed = 10;
                y_speed = 10;
            }
            else if (direction == 1)
            {
                x_speed = 10;
                y_speed = -10;
            }
            else if (direction == 4)
            {
                x_speed = 10;
                y_speed = 10;
            }
            else if (direction == 2)
            {
                x_speed = -10;
                y_speed = -10;
            }
            else if (direction == 5)
            {
                x_speed = -10;
                y_speed = 10;
            }
            else if (direction == 6) x_speed = -16;
            else if (direction == 7) x_speed = 16;
            else if (direction == 8) y_speed = 12;
            if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[WTS].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == BATTLE_MACHINE)
        {
            active = 1;
            type = 21;
            width = 64;
            height = 70;
            frame = EWULMACHINE01;
            x_position = x;
            y_position = y;
            direction = d;
            hit_points_left = 12;
            strength = 2;
        }
        else if (t == MISSILE)
        {
            active = 1;
            type = 22;
            width = 25;
            height = 13;
            frame = EWULMISSILE01;
            x_position = x;
            x_speed = -8;
            y_position = y;
            direction = d;
            hit_points_left = 1;
            strength = 4;
            if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[EWULMISSILE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == FLOATING_ORANGE)
        {
            active = 1;
            type = 23;
            width = 40;
            height = 51;
            frame = ORANGE01;
            x_position = x;
            y_position = y;
            hit_points_left = 5;
            strength = 2;
            direction = d;
            timer = time;
        }
        else if (t == SHOCKER_MACHINE)
        {
            active = 1;
            type = 24;
            frame = SHOCKER01;
            width = 37;
            height = 47;
            x_position = x;
            y_position = y;
            hit_points_left = 6;
            strength = 2;
            direction = d;
            if (direction == 1 || direction == 3)
            {
                width = 47;
                height = 37;
            }
            timer = time;
        }
        else if (t == SHOCKING)
        {
            active = 1;
            type = 25;
            frame = SHOCKING01;
            width = 22;
            height = 17;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 0;
            direction = d;
            if (direction == 1 || direction == 3)
            {
                width = 17;
                height = 22;
            }
            timer = time;
        }
        else if (t == SHOCKER_SHOT)
        {
            active = 1;
            type = 26;
            frame = ZOCK01;
            width = 16;
            height = 16;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 3;
            direction = d;
            if (direction == 0) y_speed = 10;
            else if (direction == 1) x_speed = -10;
            else if (direction == 2) y_speed = -10;
            else if (direction == 3) x_speed = 10;
            timer = time;
            if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[TIRO4].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == BIG_THUNDER)
        {
            active = 1;
            type = 27;
            frame = THUNDERRAIO01;
            width = 64;
            height = 320;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            play_sample((SAMPLE *)mydatafile[BIGTHUNDER].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == SMALL_THUNDER)
        {
            active = 1;
            type = t;
            frame = THUNDER_SHOT01;
            width = 34;
            height = 512;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 3;
            play_sample((SAMPLE *)mydatafile[THUNDERSOUND].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == MR_RESET)
        {
            active = 1;
            type = 29;
            width = 37;
            height = 0;
            frame = RESETTI;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 2;
            direction = d;
            timer = time;
        }
        else if (t == SEA_HORSE)
        {
            active = 1;
            type = 30;
            width = 36;
            height = 0;
            frame = SEAHORSE1;
            x_position = x;
            extra_int = x;
            y_position = y;
            hit_points_left = 3;
            strength = 2;
        }
        else if (t == SEA_HORSE_SPAWNER)
        {
            active = 1;
            type = 31;
            width = 1;
            height = 1;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            timer = 0;
            frame = NULO;
        }
        else if (t == FISH)
        {
            active = 1;
            type = 32;
            width = 40;
            height = 20;
            x_position = x;
            y_position = y;
            hit_points_left = 3;
            direction = d;
            timer = time;
            strength = 2;
            int r = rand() % 4;
            if (r == 0)
            {
                frame = EWULFISH_11;
                extra_int = 1;
            }
            else if (r == 1)
            {
                frame = EWULFISH_21;
                extra_int = 2;
            }
            else if (r == 2)
            {
                frame = EWULFISH_31;
                extra_int = 3;
            }
            else if (r == 3)
            {
                frame = EWULFISH_41;
                extra_int = 4;
            }
        }
        else if (t == OYSTER_TOP)
        {
            active = 1;
            type = 33;
            frame = EWULOSTRAPT2;
            width = 43;
            height = 27;
            x_position = x;
            y_position = y;
            hit_points_left = 2;
            direction = d;
            strength = 3;
        }
        else if (t == OYSTER_BOTTOM)
        {
            active = 1;
            type = 34;
            frame = EWULOSTRAPT1;
            width = 36;
            height = 14;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 3;
        }
        else if (t == OYSTER_BALL)
        {
            active = 1;
            type = 35;
            frame = EWULOSTRABALLB;
            width = 12;
            height = 12;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 2;
        }
        else if (t == WATER_JET)
        {
            if (direction == 10) direction = 1;
            else if (direction == 11) direction = 0;
            active = 1;
            type = t;
            frame = WATER_PONTA1;
            if (direction == 0) width = 33;
            else width = 33;
            height = 30;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            if (direction == 0) x_speed = -32;
            else x_speed = 32;
            strength = 3;
            animation_state = time;
            play_sample((SAMPLE *)mydatafile[TURTLEJATO].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == FLAME_THROWER)
        {
            active = 1;
            type = t;
            frame = FLAMETHROWER1;
            width = 80;
            height = 40;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 0;
            timer = time;
        }
        else if (t == FLAME_THROWER2)
        {
            active = 1;
            type = t;
            frame = FLAMETHROWER2;
            width = 40;
            height = 80;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 0;
            timer = time;
        }
        else if (t == FLAMES)
        {
            active = 1;
            type = t;
            frame = FLAMES01;
            width = 90;
            height = 58;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 3;
        }
        else if (t == FLAMES2)
        {
            active = 1;
            type = t;
            frame = FLAMES11;
            width = 58;
            height = 90;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 3;
        }
        else if (t == FLAME_METROID)
        {
            active = 1;
            type = t;
            frame = FLAMEMET1;
            width = 42;
            height = 33;
            x_position = x;
            y_position = y;
            x_speed = 2;
            y_speed = 1;
            hit_points_left = 5;
            direction = d;
            strength = 2;
        }
        else if (t == FLAME_METROID_WALL)
        {
            active = 1;
            type = t;
            frame = FLAMEMET1;
            width = 42;
            height = 33;
            x_position = x;
            y_position = y;
            x_speed = 2;
            hit_points_left = 5;
            direction = d;
            strength = 2;
        }
        else if (t == FIRE)
        {
            active = 1;
            type = t;
            frame = FIRE1;
            width = 20;
            height = 39;
            x_position = x;
            y_position = y;
            y_speed = 8;
            hit_points_left = 1;
            direction = d;
            strength = 2;
            if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(128 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == SQUID)
        {
            active = 1;
            type = t;
            width = time;
            height = 20;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 4;
        }
        else if (t == SQUID2)
        {
            active = 1;
            type = t;
            width = 25;
            frame = EWUL_SQUID01;
            height = 59;
            x_position = x;
            y_position = y;
            hit_points_left = 3;
            strength = 2;
            extra_int = y;
            action_state = 0;
        }
        else if (t == FIRES)
        {
            active = 1;
            type = t;
            timer = rand() % 4;
            if (timer == 0) frame = SFIRE1;
            else if (timer == 1) frame = SFIRE2;
            else if (timer == 2) frame = SFIRE3;
            else if (timer == 3) frame = SFIRE4;
            width = 25;
            height = 20;
            x_position = x;
            y_position = y;
            x_speed = 16 + (rand() % 12);
            y_speed = -3 + (rand() % 4);
            hit_points_left = 1;
            direction = d;
            strength = 2;
            play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == FIRE_BALL)
        {
            active = 1;
            type = t;
            frame = HADOUKEN01;
            width = 31;
            height = 24;
            x_position = x;
            y_position = y;
            x_speed = 40;
            hit_points_left = 1;
            direction = d;
            strength = 7;
        }
        else if (t == SLASH1)
        {
            active = 1;
            type = t;
            frame = SLASH01;
            width = 20;
            height = 40;
            x_position = x;
            y_position = y;
            x_speed = 20;
            hit_points_left = 1;
            direction = d;
            strength = 3;
            play_sample((SAMPLE *)mydatafile[FIRESLASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == SLASH2)
        {
            active = 1;
            type = t;
            frame = SLASH02;
            width = 27;
            height = 37;
            x_position = x;
            y_position = y;
            x_speed = 17;
            y_speed = 8;
            hit_points_left = 1;
            direction = d;
            strength = 3;
            play_sample((SAMPLE *)mydatafile[FIRESLASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == ICE_METROID)
        {
            active = 1;
            type = t;
            frame = ICEMET01;
            width = 55;
            height = 43;
            x_position = x;
            y_position = y;
            x_speed = 2;
            hit_points_left = 4;
            direction = d;
            strength = 2;
        }
        else if (t == ICE1)
        {
            active = 1;
            type = t;
            frame = ICE01;
            width = 12;
            height = 30;
            x_position = x;
            y_position = y;
            y_speed = 2;
            hit_points_left = 1;
            direction = d;
            strength = 3;
        }
        else if (t == ICE2)
        {
            active = 1;
            type = t;
            frame = ICE02;
            width = 16;
            height = 32;
            x_position = x;
            y_position = y;
            y_speed = 2;
            hit_points_left = 1;
            direction = d;
            strength = 3;
        }
        else if (t == SPIKE)
        {
            active = 1;
            type = t;
            if (direction == 0) frame = ICESPIKE;
            else frame = SHADOWSPIKE;
            width = time;
            height = 29;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 20;
        }
        else if (t == ICE_NEEDLE)
        {
            active = 1;
            type = t;
            if (time == 0)
            {
                frame = ICENEEDLE01;
                width = 9;
                height = 7;
                x_speed = 20;
                y_speed = 0;
            }
            else if (time == 1)
            {
                frame = ICENEEDLE02;
                width = 11;
                height = 11;
                x_speed = 15;
                y_speed = 10;
            }
            else if (time == 2)
            {
                frame = ICENEEDLE03;
                width = 8;
                height = 12;
                x_speed = 10;
                y_speed = 15;
            }
            else if (time == 3)
            {
                frame = ICENEEDLE04;
                width = 9;
                height = 12;
                x_speed = 0;
                y_speed = 20;
            }
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 1;
        }
        else if (t == PUMPKIN)
        {
            active = 1;
            type = t;
            frame = PUMPKIN01;
            width = 24;
            height = 20;
            x_position = x;
            y_position = y;
            x_speed = 4;
            hit_points_left = 1;
            direction = d;
            strength = 2;
        }
        else if (t == ICY_ATTACK)
        {
            active = 1;
            type = t;
            if (time == 0)
            {
                frame = ICYATTACK01;
                width = 19;
                height = 47;
                x_speed = 0;
                y_speed = 24;
            }
            else if (time == 1)
            {
                frame = ICYATTACK02;
                width = 25;
                height = 40;
                x_speed = 8;
                y_speed = 14;
            }
            else if (time == 2)
            {
                frame = ICYATTACK03;
                width = 40;
                height = 25;
                x_speed = 16;
                y_speed = 8;
            }
            else if (time == 3)
            {
                frame = ICYATTACK04;
                width = 47;
                height = 19;
                x_speed = 24;
                y_speed = 0;
            }
            else if (time == 4)
            {
                frame = ICYATTACK05;
                width = 40;
                height = 25;
                x_speed = 16;
                y_speed = -8;
            }
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 3;
        }
        else if (t == WATER_SHOT_SMALL1)
        {
            active = 1;
            type = t;
            frame = WATERSHOTSMALL;
            width = 14;
            height = 14;
            x_position = x;
            y_position = y;
            if (direction == 0) x_speed = 8;
            else x_speed = -8;
            y_speed = -4;
            hit_points_left = 1;
            direction = d;
        }
        else if (t == WATER_SHOT_SMALL2)
        {
            active = 1;
            type = t;
            frame = WATERSHOTSMALL;
            width = 14;
            height = 14;
            x_position = x;
            y_position = y;
            if (direction == 0) x_speed = 8;
            else x_speed = -8;
            if (time == 0) y_speed = -4;
            else y_speed = 1;
            hit_points_left = 1;
            direction = d;
        }
        else if (t == WATER_SHOT_SMALL3)
        {
            active = 1;
            type = t;
            frame = WATERSHOTSMALL;
            width = 14;
            height = 14;
            x_position = x;
            y_position = y;
            if (direction == 0) x_speed = time * -1;
            else x_speed = time;
            y_speed = 10;
            hit_points_left = 1;
            direction = d;
        }
        else if (t == PAINTING)
        {
            active = 1;
            type = t;
            frame = PAINTING1;
            width = 100;
            height = 100;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
        }
        else if (t == ARMOR)
        {
            active = 1;
            type = t;
            frame = EWULARMOR1;
            width = 63;
            height = 70;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            extra_int = time;
        }
        else if (t == FEATHER)
        {
            active = 1;
            type = t;
            frame = PENA;
            width = 20;
            height = 9;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 3;
            play_sample((SAMPLE *)mydatafile[PENASOUND].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == CARD_HOLDER)
        {
            active = 1;
            type = t;
            frame = CARDHOLDER;
            width = 40;
            height = 60;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            x_speed = 9;
            extra_int = time;
        }
        else if (t == SAND_PILE)
        {
            active = 1;
            type = t;
            frame = SANDMORRO1;
            width = 46;
            height = 36;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            extra_int = time;
        }
        else if (t == ICE_HOLDER)
        {
            active = 1;
            type = t;
            frame = ICEHOLDER1;
            width = 40;
            height = 50;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = ICEHOLDER2;
            extra_int = time;
            x_speed = 200;
        }
        else if (t == CARD)
        {
            active = 1;
            type = t;
            frame = CARD01;
            width = 22;
            height = 36;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            extra_int = time;
            strength = 255;
            if (direction == 0) y_speed = 10;
            else y_speed = 0;
        }
        else if (t == AIR_BUBBLE)
        {
            active = 1;
            type = 70;
            width = 10;
            height = 12;
            frame = BOLHAS;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            y_speed = -6;
        }
        else if (t == SEA_HORSE_SPAWNER2)
        {
            active = 1;
            type = 71;
            width = 1;
            height = 1;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            timer = 0;
            frame = NULO;
        }
        else if (t == SEA_HORSE2)
        {
            active = 1;
            type = 72;
            width = 36;
            height = 0;
            frame = SEAHORSE1;
            x_position = x;
            extra_int = x;
            y_position = y;
            hit_points_left = 3;
            strength = 2;
        }
        else if (t == PORTAL1)
        {
            active = 1;
            type = t;
            width = 65;
            height = 120;
            frame = PORTAL1;
            x_position = x;
            extra_int = time;
            y_position = y;
            hit_points_left = 1;
        }
        else if (t == PORTAL2)
        {
            active = 1;
            type = t;
            width = 65;
            height = 120;
            frame = PORTAL1;
            x_position = x;
            extra_int = time;
            y_position = y;
            hit_points_left = 1;
        }
        else if (t == LAST_SMALL)
        {
            active = 1;
            type = t;
            width = 48;
            height = 46;
            frame = LASTSMALL1;
            x_position = x;
            strength = 3;
            y_position = y;
            hit_points_left = 1;
            extra_int = 0;
            play_sample((SAMPLE *)mydatafile[LASTS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == LAST_THUNDER)
        {
            active = 1;
            type = t;
            frame = THUNDER_SHOT01;
            width = 34;
            height = 512;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 3;
            play_sample((SAMPLE *)mydatafile[THUNDERSOUND].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == LAST_FIRE1)
        {
            active = 1;
            type = t;
            frame = FIRE1;
            width = 20;
            height = 39;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 3;
            direction = time;
            play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == LAST_FIRE1)
        {
            active = 1;
            type = t;
            frame = FIRE1;
            width = 20;
            height = 39;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = 3;
            direction = time;
            play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == LAST_ICE)
        {
            active = 1;
            type = t;
            if (time == 0)
            {
                frame = ICYATTACK01;
                width = 19;
                height = 47;
                x_speed = 0;
                y_speed = 24;
            }
            else if (time == 1)
            {
                frame = ICYATTACK02;
                width = 25;
                height = 40;
                x_speed = 10;
                y_speed = 12;
            }
            else if (time == 2)
            {
                frame = ICYATTACK03;
                width = 40;
                height = 25;
                x_speed = 17;
                y_speed = 7;
            }
            else if (time == 3)
            {
                frame = ICYATTACK04;
                width = 47;
                height = 19;
                x_speed = 24;
                y_speed = 0;
            }
            else if (time == 4)
            {
                frame = ICYATTACK05;
                width = 40;
                height = 25;
                x_speed = 17;
                y_speed = -7;
            }
            else if (time == 5)
            {
                frame = ICYATTACK06;
                width = 25;
                height = 40;
                x_speed = 10;
                y_speed = -12;
            }
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            direction = d;
            strength = 3;
            play_sample((SAMPLE *)mydatafile[TIRO7].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == TURRET_SHOT_DSTR)
        {
            active = 1;
            type = 113;
            x_position = x;
            y_position = y;
            width = 25;
            height = 25;
            timer = 0;
            frame = SHOT_13_1;
            hit_points_left = 1;
            play_sample((SAMPLE *)mydatafile[ANIM13].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == RECOVERY_SMALL && game->hard_mode == 0)
        {
            active = 1;
            type = 200;
            width = 10;
            height = 10;
            frame = RECOVERY_S;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = -1;
            y_speed = 3;
        }
        else if (t == RECOVERY_MEDIUM)
        {
            active = 1;
            type = 201;
            width = 20;
            height = 20;
            frame = RECOVERY_M;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
            strength = -3;
            y_speed = 3;
        }
        else if (t == LIFE)
        {
            active = 1;
            type = 202;
            width = 37;
            height = 31;
            frame = VIDA;
            x_position = x;
            y_position = y;
            direction = d;
            hit_points_left = 1;
            y_speed = 3;
        }
        else if (t == PARTICLES1)
        {
            active = 1;
            type = 301;
            width = 10;
            height = 10;
            frame = PARTICLES01;
            x_position = x;
            y_position = y;
            x_speed = -6;
            y_speed = 0;
            hit_points_left = 1;
        }
        else if (t == PARTICLES2)
        {
            active = 1;
            type = 302;
            width = 9;
            height = 9;
            frame = PARTICLES02;
            x_position = x;
            y_position = y;
            x_speed = 1;
            y_speed = -3;
            hit_points_left = 1;
        }
        else if (t == PARTICLES3)
        {
            active = 1;
            type = 303;
            width = 13;
            height = 11;
            frame = PARTICLES03;
            x_position = x;
            y_position = y;
            x_speed = -4;
            y_speed = 1;
            hit_points_left = 1;
        }
        else if (t == PARTICLES4)
        {
            active = 1;
            type = 304;
            width = 13;
            height = 12;
            frame = PARTICLES04;
            x_position = x;
            y_position = y;
            x_speed = 7;
            y_speed = -1;
            hit_points_left = 1;
        }
        else if (t == ICE_DSTR)
        {
            active = 1;
            type = 305;
            width = 15;
            height = 15;
            frame = ICEDESTROY;
            x_position = x;
            y_position = y;
            direction = d;
            if (direction == 0) x_speed = rand() % 2 + 1;
            else x_speed = (rand() % 2 + 1) * -1;
            y_speed = ((rand() % 7) + 4) * -1;
            hit_points_left = 1;
        }
        else if (t == SPLASH_)
        {
            active = 1;
            type = 404;
            width = 42;
            height = 44;
            frame = SPLASH1;
            x_position = x;
            y_position = y;
            play_sample((SAMPLE *)mydatafile[SPLASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (t == ICE_BLOCK)
        {
            active = 1;
            type = 500;
            width = 20;
            height = 20;
            if (time == 0) frame = BLOCK;
            else if (time == 1) frame = ICEBLOCK1;
            else if (time == 2) frame = ICEBLOCK2;
            x_position = x;
            y_position = y;
        }
        else if (t == HA_)
        {
            active = 1;
            type = 501;
            width = 8;
            height = 21;
            frame = HA;
            x_position = x;
            y_position = y;
            timer = time;
        }
        else if (t == PORTA_1)
        {
            active = 1;
            type = 1000;
            width = 30;
            height = 100;
            timer = time;
            frame = PORTA1;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
        }
        else if (t == PORTA_2)
        {
            active = 1;
            type = 999;
            width = 30;
            height = 140;
            timer = time;
            frame = PORTA2;
            x_position = x;
            y_position = y;
            hit_points_left = 1;
        }
        else if (t == BOSS_BIRD)
        {
            active = 1;
            type = 1001;
            width = 83;
            height = 117;
            frame = BIRD1;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            strength = 3;
            direction = d;
            action_state = 0;
            timer = 0;
            extra_int = time;
        }
        else if (t == BOSS_SHADOW)
        {
            active = 1;
            type = 1002;
            width = 50;
            height = 50;
            frame = SHADOW01;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            strength = 3;
            x_speed = -15;
            y_speed = -15;
            direction = d;
            action_state = 0;
            timer = 0;
        }
        else if (t == SHADOW_BALL)
        {
            active = 1;
            type = 1003;
            width = 50;
            height = 50;
            frame = SHADOWBALL;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            strength = 3;
            x_speed = 15;
            y_speed = 15;
            direction = d;
            action_state = 0;
            timer = 0;
        }
        else if (t == BOSS_THUNDER)
        {
            active = 1;
            type = 1004;
            width = 98;
            height = 69;
            frame = THUNDER01;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            strength = 3;
        }
        else if (t == BOSS_WATER)
        {
            active = 1;
            type = t;
            width = 128;
            height = 60;
            frame = TURTLE;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            strength = 4;
        }
        else if (t == BOSS_FIRE)
        {
            active = 1;
            type = t;
            width = 129;
            height = 106;
            frame = SCALED01;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            direction = d;
            strength = 4;
        }
        else if (t == BOSS_ICE)
        {
            active = 1;
            type = t;
            width = 154;
            height = 65;
            frame = ICYSHADOW02;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            direction = d;
            strength = 4;
        }
        else if (t == LAST_BOSS)
        {
            active = 1;
            type = t;
            width = 80;
            height = 109;
            frame = LASTBOSS;
            x_position = x;
            y_position = y;
            hit_points_left = 30;
            direction = d;
            strength = 3;
            extra_int = 255;
        }
        */
    else if (t == END_STAGE)
    {
        active = 1;
        type = END_STAGE;
        width = 80;
        height = 200;
        frame = NULO;
        timer = time;
        x_position = x;
        y_position = y;
    }
    /*
    else if (t == DELIMITER)
    {
        active = 1;
        type = t;
        width = 360;
        height = 40;
        timer = time;
        frame = NULO;
        x_position = x;
        y_position = y;
    }
    else if (t == TRIANGLE_FLASH)
    {
        active = 1;
        type = 1111;
        frame = NULO;
        x_position = x;
        y_position = y;
    }
    else if (t == MOVING_CARD)
    {
        active = 1;
        type = 1666;
        frame = CARD01;
        x_position = x;
        y_position = y;
        extra_int = time;
        strength = 255;
    }
    else if (t == FALLING_FLOOR1)
    {
        active = 1;
        type = 2000;
        width = 80;
        height = 20;
        frame = DESTROYABLEPAREDE;
        x_position = x;
        y_position = y;
        hit_points_left = 1;
    }
    else if (t == FALLING_FLOOR2)
    {
        active = 1;
        type = 2001;
        width = 20;
        height = 20;
        frame = DESTROYABLEPAREDE2;
        x_position = x;
        y_position = y;
        hit_points_left = 1;
    }
    else if (t == ICE_TOP1)
    {
        active = 1;
        type = 2002;
        width = 60;
        height = 20;
        frame = ICETOP;
        x_position = x;
        y_position = y;
        hit_points_left = 1;
    }
    else if (t == ICE_TOP2)
    {
        active = 1;
        type = 2003;
        width = 60;
        height = 20;
        frame = ICETOP2;
        x_position = x;
        y_position = y;
        hit_points_left = 1;
    }
    else if (t == PORTAL_SIDE)
    {
        active = 1;
        type = 2004;
        width = 62;
        height = 120;
        if (time == 0) frame = PPP1;
        else if (time == 1) frame = PPP2;
        else if (time == 2) frame = PPP3;
        else if (time == 3) frame = PPP4;
        else if (time == 4) frame = PPP5;
        else if (time == 5) frame = PPP6;
        x_position = x;
        y_position = y;
        hit_points_left = 1;
    }
    */
}

void Actor::animation()
{
    if (type == YELLOW_SHOT)
    {
        type = YELLOW_SHOT_DSTR;
        y_position -= 5;
        x_position -= 5;
        width = 20;
        height = 20;
        timer = 0;
        frame = SHOT_0_1;
        x_speed = 0;
        y_speed = 0;
        game->player.shots--;
    }
    else if (type == WIND_SHOT)
    {
        type = WIND_SHOT_DSTR;
        width = 65;
        height = 36;
        timer = 0;
        strength = 255;
    }
    else if (type == SHADOW_SHOT)
    {
        type = SHADOW_SHOT_DSTR;
        width = 30;
        height = 30;
        timer = 0;
        strength = 255;
        frame = SHADOWSHOT;
    }
    else if (type == THUNDER_SHOT)
    {
        active = 0;
        game->player.shots--;
    }
    else if (type == WATER_SHOT)
    {
        type = WATER_SHOT_DSTR;
        timer = 0;
        if (extra_int == 1)
        {
            if (strength == 0)
            {
                frame = WATERSHOTHIT1;
                action_state = 1;
                if (direction == 0) x_position += 7;
                width = 22;
                height = 29;
            }
            else
            {
                game->create_actor(WATER_SHOT_SMALL1, (int)x_position, (int)y_position, direction, 13);
                game->create_actor(WATER_SHOT_SMALL1, (int)x_position, (int)y_position + 15, direction, 8);
            }
        }
        else if (extra_int == 2)
        {
            if (strength == 0)
            {
                frame = WATERSHOTHIT4;
                action_state = 2;
                y_position += 7;
                width = 29;
                height = 22;
            }
            else
            {
                game->create_actor(WATER_SHOT_SMALL2, (int)x_position, (int)y_position, 0, 0);
                game->create_actor(WATER_SHOT_SMALL2, (int)x_position + 15, (int)y_position, 1, 0);
            }
        }
        else if (extra_int == 3)
        {
            if (strength == 0)
            {
                frame = WATERSHOTHIT7;
                action_state = 3;
                //y_position += 7;
                width = 29;
                height = 22;
            }
            else
            {
                game->create_actor(WATER_SHOT_SMALL2, (int)x_position, (int)y_position + 16, 0, 666);
                game->create_actor(WATER_SHOT_SMALL2, (int)x_position + 15, (int)y_position + 16, 1, 666);
            }
        }
        x_speed = 0;
        y_speed = 0;
        play_sample((SAMPLE *)mydatafile[SPLAASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == FIRE_SHOT)
    {
        action_state = 2;
        timer = 0;
        if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[HADUEX].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == ICE_SHOT)
    {
        active = 0;
        type = ICE_SHOT_DSTR;
        game->create_actor(ICE_SHOT_DSTR, (int)x_position + (rand() % 15), (int)y_position + (rand() % 5), 1, 0);
        game->create_actor(ICE_SHOT_DSTR, (int)x_position + (rand() % 15), (int)y_position + (rand() % 5), 0, 0);
        game->create_actor(ICE_SHOT_DSTR, (int)x_position + (rand() % 15), (int)y_position + (rand() % 5), 1, 0);
        game->create_actor(ICE_SHOT_DSTR, (int)x_position + (rand() % 15), (int)y_position + (rand() % 5), 0, 0);
        if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[ICEANIM].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == TURRET_ENEMY_SHOT || type == MISSILE)
    {
        type = EXPLOSION;
        x_position += 10;
        y_position -= 7;
        width = 25;
        height = 25;
        timer = 0;
        frame = SHOT_13_1;
        x_speed = 0;
        y_speed = 0;
        if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[ANIM13].dat, (int)(150 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == TURRET_ENEMY)
    {
        if (rand() % 4 == 0) game->create_actor(RECOVERY_SMALL, (int)x_position + 20, (int)y_position + 20, 0, 0);
        else if (rand() % 4 == 0) game->create_actor(RECOVERY_MEDIUM, (int)x_position + 20, (int)y_position + 10, 0, 0);
        type = TURRET_ENEMY_DSTR;
        timer = 0;
        frame = TOLETED_1;
        game->create_actor(PARTICLES1, (int)x_position, (int)y_position, 1, 0);
        game->create_actor(PARTICLES2, (int)x_position + 60, (int)y_position, 0, 0);
        game->create_actor(PARTICLES3, (int)x_position, (int)y_position + 20, 1, 0);
        game->create_actor(PARTICLES4, (int)x_position + 60, (int)y_position + 20, 0, 0);
        x_speed = 0;
        y_speed = 0;
        play_sample((SAMPLE *)mydatafile[ANIM60].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == RED_BALL || type == FLAME_METROID || type == FLAME_METROID_WALL)
    {
        if (rand() % 3 == 0) game->create_actor(RECOVERY_SMALL, (int)x_position + 10, (int)y_position + 15, 0, 0);
        type = DSTR_40;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == SQUID)
    {
        type = DSTR_40;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_position -= 8;
        y_position += 2;
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == SPRING)
    {
        if (rand() % 3 == 0) game->create_actor(RECOVERY_SMALL, (int)x_position + 10, (int)y_position + 25, 0, 0);
        type = DSTR_40;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == SEA_HORSE)
    {
        if (rand() % 3 == 0) game->create_actor(RECOVERY_SMALL, (int)x_position + 10, (int)y_position + 15, 0, 0);
        type = DSTR_40;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
        y_position -= 8;
    }
    else if (type == SMALL_BIRD)
    {
        type = DSTR_40;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    /*
    else if (type == 15)
    {
        if (rand() % 3 == 0) game->create_actor(RECOVERY_SMALL, (int)x_position + 20, (int)y_position + 15, 0, 0);
        type = 666;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 17)
    {
        if (rand() % 5 == 0) game->create_actor(200, (int)x_position + 5, (int)y_position + 5, 0, 0);
        else if (rand() % 5 == 0) game->create_actor(202, (int)x_position + 5, (int)y_position + 5, 0, 0);
        type = 666;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 72)
    {
        if (rand() % 3 == 0) game->create_actor(200, (int)x_position + 10, (int)y_position + 15, 0, 0);
        type = 666;
        x_position -= 5;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 62)
    {
        if (rand() % 5 == 0) game->create_actor(200, (int)x_position + 35, (int)y_position + 5, 0, 0);
        else if (rand() % 5 == 0) game->create_actor(202, (int)x_position + 5, (int)y_position + 5, 0, 0);
        type = 666;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_position += 30;
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 19)
    {
        //if (rand() % 5 == 0) create_actor(200, (int)x_position + 5, (int)y_position + 5, 0, 0);
        type = 666;
        y_position -= 10;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 21)
    {
        if (rand() % 4 == 0) game->create_actor(201, (int)x_position + 10, (int)y_position + 15, 0, 0);
        else if (rand() % 4 == 0) game->create_actor(201, (int)x_position + 10, (int)y_position + 15, 0, 0);
        type = 667;
        timer = 0;
        frame = DA600;
        x_speed = 0;
        y_speed = 0;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 23)
    {
        if (rand() % 3 == 0) game->create_actor(200, (int)x_position + 10, (int)y_position + 15, 0, 0);
        type = 666;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 24)
    {
        type = 666;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 30)
    {
        if (rand() % 3 == 0) game->create_actor(200, (int)x_position + 10, (int)y_position + 15, 0, 0);
        type = 666;
        x_position -= 5;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 20)
    {
        type = 120;
        timer = 0;
        frame = WTSHOT02;
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 50)
    {
        x_position += 7;
        if (rand() % 3 == 0) game->create_actor(200, (int)x_position + 10, (int)y_position + 15, 0, 0);
        game->create_actor(54, (int)x_position - 7, (int)y_position + 22, 0, 0);
        game->create_actor(54, (int)x_position - 4, (int)y_position + 9, 0, 1);
        game->create_actor(54, (int)x_position + 5, (int)y_position + 1, 0, 2);
        game->create_actor(54, (int)x_position + 15, (int)y_position - 1, 0, 3);
        game->create_actor(54, (int)x_position + 27, (int)y_position + 1, 1, 2);
        game->create_actor(54, (int)x_position + 34, (int)y_position + 9, 1, 1);
        game->create_actor(54, (int)x_position + 39, (int)y_position + 22, 1, 0);
        type = 666;
        timer = 0;
        frame = DA400;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        x_speed = 0;
        y_speed = 0;
    }
    else if (type == 301 || type == 302 || type == 303 || type == 304)
    {
        type = 310;
        timer = 0;
        frame = PARTICLEDESTROY1;
        x_speed = 0;
        y_speed = 0;
    }
    */
}

void Actor::actor_check()
{
    if (hit_points_left <= 0)
    {
        if (type != 1001 && type != 1002 && type != 1003 && type != 1004 && type != 1005 && type != 1006 && type != 1007 && type != 1008)
        {
            if (type == 10 || type == 11 || type == 12 || type == 14 || type == 15 || type == 17 ||
                    type == 19 || type == 21 || type == 23 || type == 24 || type == 30 || type == 32 ||
                    type == 41 || type == 42 || type == 45 || type == 50 || type == 62 || type == 72) animation();
            else destroyactor();
        }
    }
}

void Actor::actor_update(Player *player)
{
    if (type == YELLOW_SHOT)
    {
        x_position += x_speed*4;
        game->actor_colision(this);
        if (!active) return;
        x_position += x_speed*2;
        game->actor_colision(this);
        if (!active) return;
        if (active)
        {
            if (x_position > player->x_position && x_position - player->x_position > 640) this->animation();
            else if (x_position < player->x_position && player->x_position - x_position > 640) this->animation();
        }
    }
    else if (type == WIND_SHOT)
    {
        timer++;
        if (timer == 0)
            frame = WIND_SHOT01;
        else if (timer == 12)
            frame = WIND_SHOT02;
        else if (timer == 24)
            frame = WIND_SHOT03;
        else if (timer == 35)
            timer = -1;
        x_position += x_speed * 5;
        game->actor_colision(this);
    }
    else if (type == SHADOW_SHOT)
    {
        extra_int = 1;
        x_position += x_speed;
        game->actor_colision(this);
        if (active)
        {
            extra_int = 2;
            y_position += y_speed;
            game->actor_colision(this);
        }
        if (active)
        {
            if (x_position > player->x_position && x_position - player->x_position > 640)
            {
                active = 0;
                game->fire_key = 0;
            }
            else if (x_position < player->x_position && player->x_position - x_position > 640)
            {
                active = 0;
                game->fire_key = 0;
            }
            else if (x_position < 0) this->animation();
        }
        if (active)
        {
            if (y_position > player->y_position && y_position - player->y_position > 560)
            {
                active = 0;
                game->fire_key = 0;
            }
            else if (y_position < player->y_position && player->y_position - y_position > 480)
            {
                active = 0;
                game->fire_key = 0;
            }
            else if (y_position < 0) this->animation();
        }
        timer++;
        if (timer >= 260) this->animation();
    }
    else if (type == THUNDER_SHOT)
    {
        x_position += x_speed;
        game->actor_colision(this);
        if (active)
        {
            if (x_position > player->x_position && x_position - player->x_position > 640) this->animation();
            else if (x_position < player->x_position && player->x_position - x_position > 640) this->animation();
            else if (x_position < 0) this->animation();
        }
    }
    else if (type == WATER_SHOT)
    {
        timer++;
        if (timer % 12 == 0) y_speed+=0.25;
        extra_int = 1;
        x_position += x_speed;
        game->actor_colision(this);
        if (active)
        {
            extra_int = 2;
            y_position += y_speed;
            game->actor_colision(this);
        }
        if (active)
        {
            if (x_position > player->x_position && x_position - player->x_position > 640) this->animation();
            else if (x_position < player->x_position && player->x_position - x_position > 640) this->animation();
            else if (x_position < 0) this->animation();
        }
        if (active)
        {
            if (y_position > player->y_position && y_position - player->y_position > 560) this->animation();
            else if (y_position < player->y_position && player->y_position - y_position > 480) this->animation();
            else if (y_position < 0) this->animation();
        }
    }
    else if (type == FIRE_SHOT)
    {
        if (action_state == 2)
        {
            if (timer == 0)
            {
                x_position -= 18;
                y_position -= 17;
                frame = HADOUKEN03;
            }
            else if (timer == 4) frame = HADOUKEN04;
            else if (timer == 8) frame = HADOUKEN05;
            else if (timer == 12) frame = HADOUKEN06;
            else if (timer == 16) frame = HADOUKEN07;
            if (timer == 20) active = 0;
            else if (active) timer++;
        }
        else
        {
            if (timer % 16 == 0) frame = HADOUKEN01;
            else if (timer % 16 == 8) frame = HADOUKEN02;
            timer++;
            extra_int = 2;
            x_position -= x_speed;
            game->actor_colision(this);
            if (active)
            {
                if (x_position > player->x_position && x_position - player->x_position > 640) this->animation();
                else if (x_position < player->x_position && player->x_position - x_position > 640) this->animation();
                else if (x_position < 0) this->animation();
            }
        }
    }
    else if (type == ICE_SHOT)
    {
        if (timer % 4 == 0)
        {
            if (direction == 0) x_speed += 0.25;
            else x_speed -= 0.25;
        }
        timer++;
        if (timer % 12 == 0) x_speed *= 2;
        if (x_speed > 20) x_speed = 20;
        x_position += x_speed/4;
        game->actor_colision(this);
        if (active)
        {
            x_position += x_speed/4;
            game->actor_colision(this);
        }
        if (active)
        {
            if (x_position > player->x_position && x_position - player->x_position > 640) this->animation();
            else if (x_position < player->x_position && player->x_position - x_position > 640) this->animation();
            else if (x_position < 0) this->animation();
        }
    }
    else if (type == RED_BALL)
    {
        timer++;
        if (timer == 0)
        {
            frame = REDBALL01;
        }
        else if (timer == 8)
        {
            frame = REDBALL02;
        }
        else if (timer == 16)
        {
            frame = REDBALL03;
        }
        else if (timer == 24)
        {
            frame = REDBALL02;
        }
        else if (timer == 32)
        {
            frame = REDBALL01;
        }
        else if (timer == 40)
        {
            frame = REDBALL04;
        }
        else if (timer == 48)
        {
            frame = REDBALL05;
        }
        else if (timer == 56)
        {
            frame = REDBALL04;
            timer = -7;
        }
        if (direction == 1)
        {
            x_position += x_speed * 5/4;
            game->wall_colision(this);
            if (game->map->map[(int)((y_position + 50) / 20)][(int)(x_position / 20)] == '1')
            {
                if (direction == 1) direction = 0;
                else direction = 1;
                x_position = 20 * ((int)((x_position + 20) / 20));
            }
            if (game->map->map[(int)((y_position + 50) / 20)][(int)((x_position + 40) / 20)] == '1')
            {
                if (direction == 1) direction = 0;
                else direction = 1;
                x_position = 20 * ((int)(x_position / 20));
            }
        }
        else
        {
            x_position -= x_speed * 5/4;
            game->wall_colision(this);
            if (game->map->map[(int)((y_position + 50) / 20)][(int)(x_position / 20)] == '1')
            {
                if (direction == 1) direction = 0;
                else direction = 1;
                x_position = 20 * ((int)((x_position + 20) / 20));
            }
            if (game->map->map[(int)((y_position + 50) / 20)][(int)((x_position + 40) / 20)] == '1')
            {
                if (direction == 1) direction = 0;
                else direction = 1;
                x_position = 20 * ((int)(x_position / 20));
            }
        }
    }
    else if (type == SPRING)
    {
        timer++;
        if (timer == 160)
        {
            frame = MOLA_FELIZ2;
            height = 73;
            y_position -= 13;
        }
        if (timer > 160 && timer < 192)
        {
            y_position -= y_speed * 5/4;
            if (timer % 4 == 0) y_speed -= 0.16;
        }
        else if (timer >= 192 && timer < 224)
        {
            if (timer % 4 == 0) y_speed -= 0.16;
            y_position -= y_speed * 5/4;
        }
        else if (timer >= 224 && timer < 240)
        {
            if (timer % 4 == 0) y_speed -= 0.16;
            y_position -= y_speed * 5/4;
        }
        else if (timer >= 320 && timer < 352)
        {
            y_position -= y_speed * 5/4;
            if (timer % 4 == 0) y_speed -= 0.14;
        }
        else if (timer >= 352 && timer < 384)
        {
            if (timer % 4 == 0) y_speed -= 0.13;
            y_position -= y_speed * 5/4;
        }
        else if (timer >= 384 && timer < 400)
        {
            if (timer % 4 == 0) y_speed -= 0.12;
            y_position -= y_speed * 5/4;
        }
        if (timer == 236)
        {
            timer = 319;
            y_speed = 0;
        }
        if (timer == 400)
        {
            y_speed = 3;
            y_position = extra_int;
            timer = 0;
            frame = MOLA_FELIZ;
            height = 60;
        }
        if (player->x_position >= x_position + 20) direction = 1;
        else direction = 0;
    }
    else if (type == TURRET_ENEMY)
    {
        timer++;
        if (timer == 30)
        {
            if (direction == 0) game->create_actor(TURRET_ENEMY_SHOT, (int)(x_position), (int)(y_position + 16), direction, 0);
            else game->create_actor(TURRET_ENEMY_SHOT, (int)(x_position + 59), (int)(y_position + 16), direction, 0);
            timer = 0;
        }
    }
    else if (type == TURRET_ENEMY_SHOT)
    {
        timer--;
        if (direction == 1)
        {
            x_position += x_speed * 5;
            game->actor_colision(this);
        }
        else
        {
            x_position -= x_speed * 5;
            game->actor_colision(this);
        }
        if (active && timer <= 0) this->animation();
    }
    else if (type == SMALL_BIRD)
    {
        timer++;
        if (timer >= 1 && timer < 180)
        {
            if (timer % 4 == 1 && y_speed != 2.5) y_speed += 0.25;
            y_position += y_speed/4;
        }
        if (timer >= 180 && timer < 300)
        {
            if (y_speed == 2.5) y_speed = -6;
            if (timer % 4 == 0) y_speed += 0.176;
            y_position += y_speed/4;
        }
        if (timer == 180)
        {
            frame = PIRIKITO2;
        }
        if (timer == 184)
        {
            frame = PIRIKITO3;
        }
        if (timer == 192)
        {
            frame = PIRIKITO2;
        }
        if (timer == 196)
        {
            frame = PIRIKITO;
        }
        else if (timer == 300)
        {
            timer = 0;
            y_speed = 0;
            y_position = extra_int;
        }
    }
    /*
    else if (type == 15)
    {
        if (action_state == 0)
        {
            extra_int = 20;
            frame = GHOST04;
            if (player->y_position < y_position + 290 && player->y_position > y_position - 250)
            {
                if (player->x_position < x_position && x_position - player->x_position < 300)
                {
                    action_state = 1;
                    frame = GHOST03;
                }
                else if (player->x_position > x_position && player->x_position - x_position < 300)
                {
                    action_state = 1;
                    frame = GHOST03;
                }
            }
        }
        else if (action_state == 1)
        {
            if (player->x_position < x_position && x_position - player->x_position > 300 && (player->y_position < y_position + 290 && player->y_position > y_position - 250))
            {
                if (x_speed > 1 || x_speed < -1) frame = GHOST03;
                else frame = GHOST04;
                if (extra_int > 10) extra_int -= 10;
                if (y_speed > 0.4) y_speed -= 0.2;
                else if (y_speed < -0.4) y_speed += 0.2;
                if (x_speed > 0.4) x_speed -= 0.2;
                else if (x_speed < -0.4) x_speed += 0.2;
                else
                {
                    action_state = 0;
                    x_speed = 0;
                    y_speed = 0;
                }
            }
            else if (player->x_position > x_position && player->x_position - x_position > 300 && (player->y_position < y_position + 290 && player->y_position > y_position - 250))
            {
                if (x_speed > 1 || x_speed < -1) frame = GHOST03;
                else frame = GHOST04;
                if (extra_int > 10) extra_int -= 10;
                if (y_speed > 0.4) y_speed -= 0.2;
                else if (y_speed < -0.4) y_speed += 0.2;
                if (x_speed > 0.4) x_speed -= 0.2;
                else if (x_speed < -0.4) x_speed += 0.2;
                else
                {
                    action_state = 0;
                    x_speed = 0;
                    y_speed = 0;
                }
            }
            else if (player->y_position >= y_position + 290 || player->y_position <= y_position - 250)
            {
                if (x_speed > 1 || x_speed < -1) frame = GHOST03;
                else frame = GHOST04;
                if (extra_int > 10) extra_int -= 10;
                if (y_speed > 0.4) y_speed -= 0.2;
                else if (y_speed < -0.4) y_speed += 0.2;
                if (x_speed > 0.4) x_speed -= 0.2;
                else if (x_speed < -0.4) x_speed += 0.2;
                else
                {
                    action_state = 0;
                    x_speed = 0;
                    y_speed = 0;
                }
            }
            else
            {
                timer++;
                if (timer % 5 == 0)
                {
                    if (frame == GHOST03) frame = GHOST02;
                    else if (frame == GHOST01) frame = GHOST02;
                    else frame = GHOST01;
                }
                if (player->x_position < x_position && x_speed > 0)
                {
                    x_speed -= 0.4;
                    direction = 0;
                    extra_int = (int)(((x_position - player->x_position + 20) / 2) * -1) + 150;
                }
                else if (player->x_position > x_position && x_speed < 0)
                {
                    x_speed += 0.4;
                    direction = 1;
                    extra_int = (int)(((player->x_position - x_position + 20) / 2) * -1) + 150;
                }
                else if (player->x_position < x_position)
                {
                    x_speed -= 0.3;
                    direction = 0;
                    extra_int = (int)(((x_position - player->x_position + 20) / 2) * -1) + 170;
                }
                else if (player->x_position > x_position)
                {
                    x_speed += 0.3;
                    direction = 1;
                    extra_int = (int)(((player->x_position - x_position + 20) / 2) * -1) + 170;
                }
                if (player->y_position < y_position) y_speed -= 0.3;
                else if (player->y_position > y_position) y_speed += 0.3;
                if (x_speed > 5) x_speed = 5;
                else if (x_speed < -5) x_speed = -5;
                if (y_speed > 5) y_speed = 5;
                else if (y_speed < -5) y_speed = -5;
            }
            if (extra_int > 128) extra_int = 128;
            else if (extra_int < 20) extra_int = 20;
            x_position += x_speed;
            y_position += y_speed;
        }
    }
    else if (type == 16)
    {
        if (player->x_position < x_position - 350)
        {
            timer++;
            if (timer >= (rand() % 10) + 41)
            {
                game->create_actor(17, (int)x_position, (rand() % (int)y_speed) + (int)y_position, direction, (int)x_speed);
                timer = 0;
            }
        }
    }
    else if (type == 17)
    {
        if (animation_state == 0)
        {
            timer++;
            if (timer == 1) frame = GHOSTMASK01;
            else if (timer == 4) frame = GHOSTMASK02;
            else if (timer == 7) frame = GHOSTMASK03;
            else if (timer >= 10)
            {
                frame = GHOSTMASK02;
                timer = -2;
            }
            if (rotate_factor == 0)
            {
                if (y_speed == 2) rotate_factor = 1;
                else y_speed += 0.5;
            }
            else if (rotate_factor == 1)
            {
                if (y_speed == -2) rotate_factor = 0;
                else y_speed -= 0.5;
            }
            if (direction == 1) x_position += x_speed;
            else x_position -= x_speed;
            y_position += y_speed;
            if (x_position + width < game->map->limitleft) active = 0;
            else if (x_position < extra_int) animation_state = 1;
            else game->actor_colision(this);
        }
        else if (animation_state == 1)
        {
            action_state -= 20;
            if (direction == 1) x_position += x_speed;
            else x_position -= x_speed;
            if (action_state <= 0) active = 0;
        }
    }
    else if (type == 61)
    {
        if (player->x_position > x_position + 420)
        {
            timer++;
            if (timer >= (rand() % 10) + 41)
            {
                game->create_actor(62, (int)x_position, (rand() % (int)y_speed) + (int)y_position, direction, (int)x_speed);
                timer = 0;
            }
        }
    }
    else if (type == 62)
    {
        if (animation_state == 0)
        {
            timer++;
            if (timer == 1) frame = GHOSTMASK01;
            else if (timer == 4) frame = GHOSTMASK02;
            else if (timer == 7) frame = GHOSTMASK03;
            else if (timer >= 10)
            {
                frame = GHOSTMASK02;
                timer = -2;
            }
            if (rotate_factor == 0)
            {
                if (y_speed == 2) rotate_factor = 1;
                else y_speed += 0.5;
            }
            else if (rotate_factor == 1)
            {
                if (y_speed == -2) rotate_factor = 0;
                else y_speed -= 0.5;
            }
            if (direction == 1) x_position += x_speed;
            else x_position -= x_speed;
            y_position += y_speed;
            if (x_position + width < game->map->limitleft) active = 0;
            else if (x_position > extra_int) animation_state = 1;
            else game->actor_colision(this);
        }
        else if (animation_state == 1)
        {
            action_state -= 20;
            if (direction == 1) x_position += x_speed;
            else x_position -= x_speed;
            if (action_state <= 0) active = 0;
        }
    }
    else if (type == 18)
    {
        timer++;
        if (timer >= 20)
        {
            x_speed += 8.55;
            y_position += x_speed;
            if (y_position - extra_int > 150)
            {
                action_state = 1;
                timer = -30;
                x_speed = 0;
                y_position = extra_int + 129;
            }
        }
        else if (action_state == 1)
        {
            if (timer >= -20)
            {
                y_position -= 6;
                if (timer == 0) action_state = 0;
            }
        }
    }
    else if (type == 19)
    {
        if (timer == 50)
        {
            timer = 0;
            if (direction == 0)
            {
                game->create_actor(20, (int)x_position - 4, (int)y_position + 16, direction, 0);
                game->create_actor(20, (int)x_position + 36, (int)y_position + 16, direction + 3, 0);
            }
            else if (direction == 1)
            {
                game->create_actor(20, (int)x_position + 16, (int)y_position - 4, direction, 0);
                game->create_actor(20, (int)x_position + 16, (int)y_position + 36, direction + 3, 0);
            }
            else
            {
                game->create_actor(20, (int)x_position - 4, (int)y_position - 4, direction, 0);
                game->create_actor(20, (int)x_position - 4, (int)y_position + 36, direction + 3, 0);
            }
        }
        timer++;
    }
    else if (type == 20)
    {
        x_position += x_speed;
        extra_int = 1;
        game->actor_colision(this);
        if (active)
        {
            y_position += y_speed;
            extra_int = 2;
            game->actor_colision(this);
            if (active)
            {
                if (x_position < 0) active = 0;
            }
        }
        if (active)
        {
            timer++;
            if (timer == 30) this->animation();
        }
    }
    else if (type == 21)
    {
        if (timer == 50)
        {
            timer = rand() % 3;
            if (timer == 0) game->create_actor(22, (int)x_position + 22, (int)y_position + 27, direction, 0);
            else if (timer == 1) game->create_actor(22, (int)x_position - 2, (int)y_position + 26, direction, 0);
            else if (timer == 2)
            {
                if (direction == 0) extra_int = 6;
                else extra_int = 7;
                game->create_actor(20, (int)x_position + 23, (int)y_position + 17, extra_int, 0);
                game->create_actor(20, (int)x_position, (int)y_position + 16, extra_int, 0);
            }
            timer = 0;
        }
        timer++;
    }
    else if (type == 22)
    {
        if (timer == 10) x_speed = -22;
        if (timer != 0) x_position += x_speed;
        timer++;
        game->actor_colision(this);
        if (active)
        {
            if (timer == 30) this->animation();
        }
    }
    else if (type == 23)
    {
        if (x_position > player->x_position + 55) direction = 1;
        else if (x_position + 40 < player->x_position - 15) direction = 3;
        else direction = 2;
        if (timer == 0)
        {
            if (direction == 1) frame = ORANGE01;
            else if (direction == 2) frame = ORANGE04;
            else if (direction == 3) frame = ORANGE07;
        }
        else if (timer == 2)
        {
            if (direction == 1) frame = ORANGE02;
            else if (direction == 2) frame = ORANGE05;
            else if (direction == 3) frame = ORANGE08;
        }
        else if (timer == 4)
        {
            if (direction == 1) frame = ORANGE03;
            else if (direction == 2) frame = ORANGE06;
            else if (direction == 3) frame = ORANGE09;
        }
        else if (timer == 6)
        {
            if (direction == 1) frame = ORANGE02;
            else if (direction == 2) frame = ORANGE05;
            else if (direction == 3) frame = ORANGE08;
        }
        else if (timer == 8)
        {
            if (direction == 1) frame = ORANGE07;
            else if (direction == 2) frame = ORANGE04;
            else if (direction == 3) frame = ORANGE01;
        }
        else if (timer == 10)
        {
            if (direction == 1) frame = ORANGE08;
            else if (direction == 2) frame = ORANGE05;
            else if (direction == 3) frame = ORANGE02;
        }
        else if (timer == 12)
        {
            if (direction == 1) frame = ORANGE09;
            else if (direction == 2) frame = ORANGE06;
            else if (direction == 3) frame = ORANGE03;
        }
        else if (timer == 14)
        {
            if (direction == 1) frame = ORANGE08;
            else if (direction == 2) frame = ORANGE05;
            else if (direction == 3) frame = ORANGE02;
        }
        else if (timer == 16)
        {
            if (direction == 1) frame = ORANGE01;
            else if (direction == 2) frame = ORANGE04;
            else if (direction == 3) frame = ORANGE07;
            timer = 0;
        }
        if (extra_int < 2) y_position -= 1;
        else if (extra_int < 8) y_position -= 2;
        else if (extra_int < 10) y_position -= 1;
        else if (extra_int < 11) y_position = y;
        else if (extra_int < 13) y_position += 1;
        else if (extra_int < 19) y_position += 2;
        else if (extra_int < 21) y_position += 1;
        else extra_int = -1;
        if (timer == 8)
        {
            if (direction == 1) game->create_actor(20, (int)x_position - 3, (int)y_position + 46, 5, 0);
            else if (direction == 2) game->create_actor(20, (int)x_position + 16, (int)y_position + 50, 8, 0);
            else game->create_actor(20, (int)x_position + 35, (int)y_position + 46, 3, 0);
        }
        extra_int++;
        timer++;
        action_state++;
    }
    else if (type == 24)
    {
        timer++;
        if (timer > 9 && timer < 14) frame++;
        else if (timer == 16)
        {
            if (direction == 0) game->create_actor(25, (int)x_position + 7, (int)y_position + 21, 0, 0);
            else if (direction == 1) game->create_actor(25, (int)x_position + 9, (int)y_position + 7, 1, 0);
            else if (direction == 2) game->create_actor(25, (int)x_position + 7, (int)y_position + 9, 2, 0);
            else if (direction == 3) game->create_actor(25, (int)x_position + 21, (int)y_position + 8, 3, 0);
        }
        else if (timer > 30 && timer < 35) frame--;
        else if (timer == 60) timer = 0;
    }
    else if (type == 25)
    {
        timer++;
        if (timer % 5 == 1) frame = SHOCKING02;
        else if (timer % 5 == 2) frame = SHOCKING03;
        else if (timer % 5 == 3) frame = SHOCKING04;
        else if (timer % 5 == 4) frame = SHOCKING05;
        else if (timer % 5 == 0) frame = SHOCKING01;
        if (timer == 16)
        {
            if (direction == 0) game->create_actor(26, (int)x_position + 4, (int)y_position + 3, direction, 0);
            else if (direction == 1) game->create_actor(26, (int)x_position - 2, (int)y_position + 4, direction, 0);
            else if (direction == 2) game->create_actor(26, (int)x_position + 4, (int)y_position - 2, direction, 0);
            else if (direction == 3) game->create_actor(26, (int)x_position + 3, (int)y_position + 2, direction, 0);
            active = 0;
        }
    }
    else if (type == 26)
    {
        x_position += x_speed;
        extra_int = 1;
        game->actor_colision(this);
        if (active)
        {
            y_position += y_speed;
            extra_int = 2;
            game->actor_colision(this);
            if (active)
            {
                if (x_position < 0) active = 0;
            }
        }
        if (active)
        {
            timer++;
            if (timer == 60) active = 0;
        }
    }
    else if (type == 27)
    {
        timer++;
        if (timer == 1)
        {
            x_position -= 4;
            frame++;
        }
        else if (timer == 2)
        {
            x_position -= 14;
            frame++;
        }
        else if (timer == 3)
        {
            x_position -= 2;
            frame++;
        }
        else if (timer == 4) active = 0;
    }
    else if (type == 29)
    {
        if (action_state == 0)
        {
            if (player->direction == 0 && x_position - player->x_position-40 > 24 && x_position - player->x_position-40 < 56)
            {
                action_state = 1;
                direction = 1;
            }
            else if (player->direction == 1 && player->x_position - x_position-37 > 24 && player->x_position - x_position-37  < 56)
            {
                action_state = 1;
                direction = 0;
            }
        }
        if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                y_position -= 6;
                height += 6;
            }
            else if (timer == 2)
            {
                y_position -= 7;
                height += 7;
            }
            else if (timer == 3)
            {
                y_position -= 7;
                height += 7;
            }
            else if (timer == 4)
            {
                y_position -= 7;
                height += 7;
            }
            else if (timer == 5)
            {
                y_position -= 7;
                height += 7;
            }
            else if (timer == 16)
            {
                y_position += 7;
                height -= 7;
            }
            else if (timer == 17)
            {
                y_position += 7;
                height -= 7;
            }
            else if (timer == 18)
            {
                y_position += 7;
                height -= 7;
            }
            else if (timer == 19)
            {
                y_position += 7;
                height -= 7;
            }
            else if (timer == 20)
            {
                y_position += 6;
                height -= 6;
            }
            else if (timer >= 24)
            {
                if (player->x_position - x_position - 37 > 70 || x_position - player->x_position - 40  > 70)
                {
                    timer = 0;
                    action_state = 0;
                }
            }
        }
    }
    else if (type == 31)
    {
        if (action_state == 0)
        {
            if (player->x_position - x_position - 36 > 0 && player->x_position - x_position - 36 < 140)
            {
                game->create_actor(30, (int)x_position, (int)y_position, 0, 0);
                action_state = 1;
            }
            else if (x_position - player->x_position - 40 > 0 && x_position - player->x_position - 40 < 140)
            {
                game->create_actor(30, (int)x_position, (int)y_position, 0, 0);
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 90)
            {
                action_state = 0;
                timer = 0;
            }
        }
    }
    else if (type == 30)
    {
        if (action_state == 0) action_state = 1;
        if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                height+=17;
                y_position-=17;
            }
            else if (timer == 2)
            {
                height+=17;
                y_position-=17;
            }
            else if (timer == 3)
            {
                height+=17;
                y_position-=17;
            }
            else if (timer >= 4)
            {
                if (y_position <= player->y_position)
                {
                    action_state = 2;
                    timer = 0;
                }
                else if (y_position <= game->map->water_position + 20)
                {
                    y_position = game->map->water_position + 20;
                    action_state = 2;
                    timer = 0;
                }
                else
                {
                    y_position-=17;
                    y_speed+=17;
                }
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 6)
            {
                action_state = 3;
                frame = SEAHORSE2;
                width = 40;
                height = 41;
                timer = 0;
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 1)
            {
                width = 30;
                height = 30;
                frame = SEAHORSE3;
                if (player->x_position > x_position) x_speed = 25;
                else x_speed = -25;
            }
            else if (timer >= 10) x_position += x_speed;
            if (x_position - player->x_position - 40 > 640) active = 0;
            else if (player->x_position - x_position - 30 > 640) active = 0;
        }
        game->actor_colision(this);
    }
    else if (type == 32)
    {
        if (action_state == 0)
        {
            if (player->x_position < x_position && x_position - player->x_position - 40 < 260)
            {
                action_state = 1;
                frame++;
                if (direction == 1) game->create_actor(501, (int)x_position + 50, (int)y_position - 23, 0, 5);
                else game->create_actor(501, (int)x_position - 10, (int)y_position - 23, 0, 5);
                timer = 0;
            }
            else if (player->x_position > x_position && player->x_position - x_position - 20 < 260)
            {
                action_state = 1;
                frame++;
                if (direction == 1) game->create_actor(501, (int)x_position + 50, (int)y_position - 23, 0, 5);
                else game->create_actor(501, (int)x_position - 10, (int)y_position - 23, 0, 5);
                timer = 0;
            }
            else
            {
                timer++;
                if (timer % 20 == 0) y_position += 0;
                else if (timer % 20 == 2) y_position += 1;
                else if (timer % 20 == 4) y_position += 1;
                else if (timer % 20 == 6) y_position += 2;
                else if (timer % 20 == 8) y_position += 1;
                else if (timer % 20 == 10) y_position -= 0;
                else if (timer % 20 == 12) y_position -= 1;
                else if (timer % 20 == 14) y_position -= 1;
                else if (timer % 20 == 16) y_position -= 2;
                else if (timer % 20 == 18) y_position -= 1;
            }
        }
        else if (action_state == 1)
        {
            if (player->x_position < x_position && x_position - player->x_position - 40 > 300)
            {
                if (x_speed > 1 || x_speed < -1)
                {
                    if (extra_int == 1) frame = EWULFISH_12;
                    else if (extra_int == 2) frame = EWULFISH_22;
                    else if (extra_int == 3) frame = EWULFISH_32;
                    else if (extra_int == 4) frame = EWULFISH_42;
                }
                else
                {
                    if (extra_int == 1) frame = EWULFISH_11;
                    else if (extra_int == 2) frame = EWULFISH_21;
                    else if (extra_int == 3) frame = EWULFISH_31;
                    else if (extra_int == 4) frame = EWULFISH_41;
                }
                if (y_speed > 0.4) y_speed -= 0.2;
                else if (y_speed < -0.4) y_speed += 0.2;
                if (x_speed > 0.4) x_speed -= 0.2;
                else if (x_speed < -0.4) x_speed += 0.2;
                else
                {
                    action_state = 0;
                    x_speed = 0;
                    y_speed = 0;
                    timer = 0;
                }
            }
            else if (player->x_position > x_position && player->x_position - x_position - 20 > 300)
            {
                if (x_speed > 1 || x_speed < -1)
                {
                    if (extra_int == 1) frame = EWULFISH_12;
                    else if (extra_int == 2) frame = EWULFISH_22;
                    else if (extra_int == 3) frame = EWULFISH_32;
                    else if (extra_int == 4) frame = EWULFISH_42;
                }
                else
                {
                    if (extra_int == 1) frame = EWULFISH_11;
                    else if (extra_int == 2) frame = EWULFISH_21;
                    else if (extra_int == 3) frame = EWULFISH_31;
                    else if (extra_int == 4) frame = EWULFISH_41;
                }
                if (y_speed > 0.4) y_speed -= 0.2;
                else if (y_speed < -0.4) y_speed += 0.2;
                if (x_speed > 0.4) x_speed -= 0.2;
                else if (x_speed < -0.4) x_speed += 0.2;
                else
                {
                    action_state = 0;
                    x_speed = 0;
                    y_speed = 0;
                    timer = 0;
                }
            }
            else
            {
                timer++;
                if (timer % 4 == 0)
                {
                    if (extra_int == 1) frame = EWULFISH_12;
                    else if (extra_int == 2) frame = EWULFISH_22;
                    else if (extra_int == 3) frame = EWULFISH_32;
                    else if (extra_int == 4) frame = EWULFISH_42;
                }
                else if (timer % 2 == 0)
                {
                    if (extra_int == 1) frame = EWULFISH_13;
                    else if (extra_int == 2) frame = EWULFISH_23;
                    else if (extra_int == 3) frame = EWULFISH_33;
                    else if (extra_int == 4) frame = EWULFISH_43;
                }
                if (player->x_position < x_position && x_speed > 0)
                {
                    x_speed -= 0.4;
                    direction = 0;
                }
                else if (player->x_position > x_position && x_speed < 0)
                {
                    x_speed += 0.4;
                    direction = 1;
                }
                else if (player->x_position < x_position)
                {
                    x_speed -= 0.3;
                    direction = 0;
                }
                else if (player->x_position > x_position)
                {
                    x_speed += 0.3;
                    direction = 1;
                }
                if (player->y_position < y_position) y_speed -= 0.3;
                else if (player->y_position > y_position) y_speed += 0.3;
                if (x_speed > 5) x_speed = 5;
                else if (x_speed < -5) x_speed = -5;
                if (y_speed > 5) y_speed = 5;
                else if (y_speed < -5) y_speed = -5;
            }
            x_position += x_speed;
            game->actor_colision(this);
            if (active)
            {
                y_position += y_speed;
                game->actor_colision(this);
            }
        }
        if (y_position <  game->map->water_position) y_position = game->map->water_position;
    }
    else if (type == 33)
    {
        if (action_state == 0)
        {
            if (direction == 0 && x_position - player->x_position > 0 && x_position - player->x_position - 40 < 360) action_state = 1;
            else if (direction == 1 && player->x_position - x_position > 0 && player->x_position - x_position - 36 < 360) action_state = 1;
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                game->create_actor(35, (int)x_position + 17, (int)y_position + 4, direction, 0);
            }
            if (direction == 0)
            {
                if (timer == 4)
                {
                    rotate_factor += 11;
                    x_position += 2;
                    y_position += -5;
                    width = 46;
                    height = 38;
                }
                else if (timer == 5)
                {
                    rotate_factor += 11;
                    x_position += 3;
                    y_position += -4;
                }
                else if (timer == 6)
                {
                    rotate_factor += 11;
                    x_position += 4;
                    y_position += -3;
                }
                else if (timer == 7)
                {
                    action_state = 2;
                    x_position += 6;
                    y_position += -6;
                    timer = 0;
                    width = 31;
                    height = 37;
                    frame = EWULOSTRAPT3;
                }
            }
            else if (direction == 1)
            {
                if (timer == 4)
                {
                    rotate_factor -= 11;
                    x_position += -2;
                    y_position += -5;
                    width = 46;
                    height = 38;
                }
                else if (timer == 5)
                {
                    rotate_factor -= 11;
                    x_position += -3;
                    y_position += -4;
                }
                else if (timer == 6)
                {
                    rotate_factor -= 11;
                    x_position += -4;
                    y_position += -3;
                }
                else if (timer == 7)
                {
                    action_state = 2;
                    x_position += 6;
                    y_position += -6;
                    timer = 0;
                    width = 31;
                    height = 37;
                    frame = EWULOSTRAPT3;
                }
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 10)
            {
                if (direction == 0)
                {
                    timer = 0;
                    action_state = 3;
                    x_position += -6;
                    y_position += 6;
                    width = 46;
                    height = 38;
                }
                else
                {
                    timer = 0;
                    action_state = 3;
                    x_position += -6;
                    y_position += 6;
                    width = 46;
                    height = 38;
                }
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (direction == 0)
            {
                if (timer == 2)
                {
                    rotate_factor -= 11;
                    x_position += -4;
                    y_position += 3;
                }
                else if (timer == 3)
                {
                    rotate_factor -= 11;
                    x_position += -3;
                    y_position += 4;
                }
                else if (timer == 4)
                {
                    rotate_factor -= 11;
                    x_position += -2;
                    y_position += 5;
                    width = 43;
                    height = 21;
                }
                else if (timer == 5)
                {
                    action_state = 4;
                    timer = 0;
                }
            }
            if (direction == 1)
            {
                if (timer == 2)
                {
                    rotate_factor += 11;
                    x_position += 4;
                    y_position += 3;
                }
                else if (timer == 3)
                {
                    rotate_factor += 11;
                    x_position += 3;
                    y_position += 4;
                }
                else if (timer == 4)
                {
                    rotate_factor += 11;
                    x_position += 2;
                    y_position += 5;
                    width = 43;
                    height = 21;
                }
                else if (timer == 5)
                {
                    action_state = 4;
                    timer = 0;
                }
            }
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 40)
            {
                timer = 0;
                action_state = 0;
            }
        }
    }
    else if (type == 35)
    {
        if (action_state == 0)
        {
            timer++;
            if (timer == 5)
            {
                action_state = 1;
                timer = 0;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                if (direction == 0)
                {
                    if (x_position - player->x_position - 40 >= 180) x_speed = -20;
                    else if (x_position - player->x_position - 40 >= 125) x_speed = -15;
                    else x_speed = -10;
                }
                else
                {
                    if (player->x_position - x_position - 20 >= 180) x_speed = 20;
                    else if (player->x_position - x_position - 20 >= 125) x_speed = 15;
                    else x_speed = 10;
                }
                if (player->y_position < y_position - 20) y_speed = -14;
                else if (player->y_position < y_position) y_speed = -10;
                else y_speed = -6;
            }
            else y_speed += 2;
            x_position += x_speed;
            y_position += y_speed;
            game->actor_colision(this);
        }
    }
    else if (type == 36)
    {
        if (action_state == 0)
        {
            timer++;
            if (direction != 1 || animation_state != 0) x_position += x_speed;
            extra_int += 2;
            width += 32;
            if (extra_int >= 10)
            {
                if (direction == 0)
                {
                    x_position += -16;
                    extra_int++;
                    width += 16;
                    action_state = 1;
                }
                else
                {
                    x_position += 16;
                    extra_int++;
                    width += 16;
                    action_state = 1;
                }
            }
            game->actor_colision(this);
        }
        else if (action_state == 1)
        {
            timer++;
            x_position += x_speed;
            game->actor_colision(this);
        }
    }
    else if (type == 37)
    {
        if (timer == 45)
        {
            if (direction == 0) game->create_actor(39, (int)x_position + 80, (int)y_position - 9, 1, 0);
            else game->create_actor(39, (int)x_position - 90, (int)y_position - 9, 0, 0);
        }
        if (timer == 76) timer = 0;
        timer++;
    }
    else if (type == 38)
    {
        if (timer == 45)
        {
            if (direction == 0) game->create_actor(40, (int)x_position - 9, (int)y_position + 80, 0, 0);
            else game->create_actor(40, (int)x_position - 9, (int)y_position - 90, 1, 0);
        }
        if (timer == 76) timer = 0;
        timer++;
    }
    else if (type == 39)
    {
        timer++;
        if (timer == 27) frame = FLAMES08;
        else if (timer == 28) frame = FLAMES09;
        else if (timer == 29) active = 0;
        else if (timer % 7 == 1)
        {
            frame = FLAMES01;
            if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[FLAMETHROWER].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (timer % 7 == 2) frame = FLAMES02;
        else if (timer % 7 == 3) frame = FLAMES03;
        else if (timer % 7 == 4) frame = FLAMES04;
        else if (timer % 7 == 5) frame = FLAMES05;
        else if (timer % 7 == 6) frame = FLAMES06;
        else if (timer % 7 == 0) frame = FLAMES07;
    }
    else if (type == 40)
    {
        timer++;
        if (timer == 27) frame = FLAMES18;
        else if (timer == 28) frame = FLAMES19;
        else if (timer == 29) active = 0;
        else if (timer % 7 == 1)
        {
            frame = FLAMES11;
            if (game->in_player_view(this)) play_sample((SAMPLE *)mydatafile[FLAMETHROWER].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (timer % 7 == 2) frame = FLAMES12;
        else if (timer % 7 == 3) frame = FLAMES13;
        else if (timer % 7 == 4) frame = FLAMES14;
        else if (timer % 7 == 5) frame = FLAMES15;
        else if (timer % 7 == 6) frame = FLAMES16;
        else if (timer % 7 == 0) frame = FLAMES17;
    }
    else if (type == 41)
    {
        if (timer % 8 == 0) frame = FLAMEMET1;
        else if (timer % 8 == 2) frame = FLAMEMET2;
        else if (timer % 8 == 4) frame = FLAMEMET3;
        else if (timer % 8 == 6) frame = FLAMEMET4;
        timer++;
        if (direction == 1)
        {
            x_position += x_speed;
            game->wall_colision(this);
                if (map->map[(int)((y_position + 50) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position + 50) / 20)][(int)((x_position + 40) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20));
                    noisiloc = 1;
                }
        }
        else
        {
            x_position -= x_speed;
            game->wall_colision(this);
                if (map->map[(int)((y_position + 50) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position + 50) / 20)][(int)((x_position + 40) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20));
                    noisiloc = 1;
                }
        }
    }
    else if (type == 42)
    {
        if (timer % 8 == 0) frame = FLAMEMET1;
        else if (timer % 8 == 2) frame = FLAMEMET2;
        else if (timer % 8 == 4) frame = FLAMEMET3;
        else if (timer % 8 == 6) frame = FLAMEMET4;
        if (timer % 70 == 69) game->create_actor(43, (int)x_position + 9, (int)y_position - 2, 0, 0);
        timer++;
        if (direction == 1)
        {
            x_position += x_speed;
            game->wall_colision(this);
                if (map->map[(int)((y_position - 10) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position - 10) / 20)][(int)((x_position + 40) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20));
                    noisiloc = 1;
                }
        }
        else
        {
            x_position -= x_speed;
            game->wall_colision(this);
                if (map->map[(int)((y_position - 10) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position - 10) / 20)][(int)((x_position + 40) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20));
                    noisiloc = 1;
                }
        }
    }
    else if (type == 43)
    {
        if (action_state == 2)
        {
            if (timer == 0) frame = FIRE6;
            else if (timer == 1) frame = FIRE7;
            else if (timer == 2) active = 0;
            timer++;
        }
        else
        {
            if (timer % 4 == 0) frame = FIRE1;
            else if (timer % 4 == 1) frame = FIRE2;
            else if (timer % 4 == 2) frame = FIRE3;
            else if (timer % 4 == 3) frame = FIRE4;
            timer++;
            y_position += y_speed;
            game->actor_colision(this);
        }
    }
    else if (type == 45)
    {
        if (action_state == 0)
        {
            if (player->direction == 0 && x_position - player->x_position-40 > 15 && x_position - player->x_position-40 < 80)
            {
                if (player->y_position + 400 > y_position &&
                        player->y_position - 80 <= y_position)
                {
                    action_state = 1;
                    y_speed = -25;
                }
            }
            else if (player->direction == 1 && player->x_position - x_position-37 > 15 && player->x_position - x_position-37 < 80)
            {
                if (player->y_position + 400 > y_position &&
                        player->y_position - 80 <= y_position)
                {
                    action_state = 1;
                    y_speed = -25;
                }
            }
        }
        if (action_state == 1)
        {
            if (timer < 7) y_speed +=1;
            else if (timer < 16) y_speed +=2;
            else y_speed +=4;
            y_position += y_speed;
            timer++;
            if (y_speed == -4)
            {
                timer = 0;
                action_state = 2;
                y_speed = 0;
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 1)
            {
                frame = EWUL_SQUID05;
                width = 27;
                height = 33;
                y_position += 6;
                x_position -= 2;
            }
            else if (timer == 2) frame = EWUL_SQUID06;
            else if (timer == 3)
            {
                frame = EWUL_SQUID06;
                y_position += 4;
            }
            else if (timer == 4)
            {
                y_position += 6;
                frame = EWUL_SQUID05;
            }
            else if (timer == 5)
            {
                timer = 0;
                width = 25;
                height = 59;
                y_position -=20;
                x_position += 2;
                action_state = 3;
            }
        }
        if (action_state == 3)
        {
            if (timer < 8) y_speed +=1;
            else if (timer < 16) y_speed +=2;
            else y_speed +=4;
            y_position += y_speed;
            timer++;
            if (y_speed == 44)
            {
                timer = 0;
                action_state = 4;
                y_position = extra_int;
            }
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 10)
            {
                timer = 0;
                action_state = 0;
            }
        }
    }
    else if (type == 46)
    {
        if (action_state == 2)
        {
            if (timer == 0 && extra_int == 1) frame = FIRE5;
            else if (timer == 2 && extra_int == 1) frame = FIRE6;
            else if (timer == 4 && extra_int == 1) frame = FIRE7;
            else if (timer >= 6 && extra_int == 1)
            {
                active = 0;
            }
            if (timer == 0 && extra_int == 2) frame = SFIRE5;
            else if (timer == 2 && extra_int == 2) frame = SFIRE6;
            else if (timer == 4 && extra_int == 2) frame = SFIRE7;
            else if (timer >= 6 && extra_int == 2)
            {
                active = 0;
            }
            if (active) timer++;
        }
        else if (action_state == 0)
        {
            if (timer % 4 == 0) frame = SFIRE1;
            else if (timer % 4 == 1)
            {
                frame = SFIRE2;
                y_speed++;
            }
            else if (timer % 4 == 2) frame = SFIRE3;
            else if (timer % 4 == 3)
            {
                frame = SFIRE4;
                y_speed++;
            }
            timer++;
            extra_int = 1;
            y_position += y_speed;
            game->actor_colision(this);
            if (active)
            {
                extra_int = 2;
                x_position -= x_speed;
                game->actor_colision(this);
            }
        }
    }
    else if (type == 47)
    {
        if (action_state == 2)
        {
            if (timer == 0)
            {
                x_position -= 18;
                y_position -= 17;
                frame = HADOUKEN03;
            }
            else if (timer == 1) frame = HADOUKEN04;
            else if (timer == 2) frame = HADOUKEN05;
            else if (timer == 3) frame = HADOUKEN06;
            else if (timer == 4) frame = HADOUKEN07;
            else if (timer == 5) active = 0;
            if (active) timer++;
        }
        else
        {
            if (timer % 4 == 0) frame = HADOUKEN01;
            else if (timer % 4 == 2) frame = HADOUKEN02;
            timer++;
            extra_int = 2;
            x_position -= x_speed / 2;
            game->actor_colision(this);
            if (active)
            {
                x_position -= x_speed / 2;
                game->actor_colision(this);
            }
        }
    }
    else if (type == 48)
    {
        x_position -= x_speed;
        game->actor_colision(this);
    }
    else if (type == 49)
    {
        x_position -= x_speed;
        game->actor_colision(this);
        if (active)
        {
            y_position -= y_speed;
            game->actor_colision(this);
        }
    }
    else if (type == 50)
    {
        if (timer % 8 == 0) frame = ICEMET01;
        else if (timer % 8 == 2) frame = ICEMET02;
        else if (timer % 8 == 4) frame = ICEMET03;
        else if (timer % 8 == 6) frame = ICEMET04;
        timer++;
        if (direction == 1)
        {
            x_position += x_speed;
            game->actor_colision(this);
                if (map->map[(int)((y_position + 50) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position + 50) / 20)][(int)((x_position + 40) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20));
                    noisiloc = 1;
                }
        }
        else
        {
            x_position -= x_speed;
            game->actor_colision(this);
                if (map->map[(int)((y_position + 50) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position + 50) / 20)][(int)((x_position + 40) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20));
                    noisiloc = 1;
                }
        }
    }
    else if (type == 51)
    {
        if (action_state == 0)
        {
            if (player->x_position < x_position && x_position - player->x_position < 140 && player->y_position > y_position && player->y_position - y_position < 300)
            {
                action_state = 1;
                play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (player->x_position > x_position && player->x_position - x_position < 100 && player->y_position > y_position && player->y_position - y_position < 300)
            {
                action_state = 1;
                play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (y_speed < 39) y_speed += 4;
            y_position += y_speed / 2;
            if (timer > 5) game->actor_colision(this);
            if (active)
            {
                y_position += y_speed / 2;
                if (timer > 5) game->actor_colision(this);
            }
        }
        else if (action_state == 2)
        {
            if (timer == 1) active = 0;
            else timer++;
        }
    }
    else if (type == 52)
    {
        if (action_state == 0)
        {
            if (player->x_position < x_position && x_position - player->x_position < 140 && player->y_position > y_position && player->y_position - y_position < 300)
            {
                action_state = 1;
                play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (player->x_position > x_position && player->x_position - x_position < 100 && player->y_position > y_position && player->y_position - y_position < 300)
            {
                action_state = 1;
                play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (y_speed < 39) y_speed += 4;
            y_position += y_speed / 2;
            if (timer > 5) game->actor_colision(this);;
            if (active)
            {
                y_position += y_speed / 2;
                if (timer > 5) game->actor_colision(this);
            }
        }
        else if (action_state == 2)
        {
            if (timer == 1) active = 0;
            else timer++;
        }
    }
    else if (type == 54)
    {
        if (direction == 0) x_position -= x_speed;
        else x_position += x_speed;
        y_position -= y_speed;
        if (x_position < 0 || y_position < 0 || x_position - player->x_position > 640) active = 0;
        else game->actor_colision(this);
    }
    else if (type == 55)
    {
        if (action_state == 0)
        {
            timer++;
            if (timer % 6 == 1) frame = PUMPKIN01;
            else if (timer % 6 == 3) frame = PUMPKIN02;
            else if (timer % 6 == 5) frame = PUMPKIN03;
            x_speed = 10;
            if (player->on_ground == true && (int)player->y_position + 60 == (int)y_position)
            {
                if (player->x_position > x_position && player->x_position - x_position - 24 < 200) x_speed = 20;
                else if (player->x_position < x_position && x_position - player->x_position - 40 < 200) x_speed = 20;
            }
            if (direction == 0) x_position -= x_speed;
            else x_position += x_speed;
            game->actor_colision(this);
                if (map->map[(int)((y_position + 20) / 20)][(int)(x_position / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)((x_position + 20) / 20));
                    noisiloc = 1;
                }
                if (map->map[(int)((y_position + 20) / 20)][(int)((x_position + 20) / 20)] == '1')
                {
                    if (direction == 1) direction = 0;
                    else direction = 1;
                    x_position = 20 * ((int)(x_position / 20)) - 4;
                    noisiloc = 1;
                }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 30)
            {
                action_state = 0;
                timer = extra_int;
            }
        }
    }
    else if (type == 56)
    {
        if (action_state == 0)
        {
            timer++;
            extra_int += 30;
            if (extra_int > 256) extra_int = 256;
            if (timer == 13)
            {
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            if (direction == 0) x_position += x_speed / 2;
            else x_position -= x_speed / 2;
            y_position += y_speed / 2;
            game->actor_colision(this);
            if (active)
            {
                if (direction == 0) x_position += x_speed / 2;
                else x_position -= x_speed / 2;
                y_position += y_speed / 2;
                game->actor_colision(this);
            }
        }
    }
    else if (type == 57)
    {
        x_position += x_speed;
        y_position += y_speed;
        y_speed++;
        game->actor_colision(this);
    }
    else if (type == 58)
    {
        timer++;
        if (timer % 2 == 0 && x_speed != 0)
        {
            if (x_speed > 0) x_speed--;
            else x_speed++;
        }
        x_position += x_speed;
        y_position += y_speed;
        y_speed += 0.5;
        game->actor_colision(this);
    }
    else if (type == 60)
    {
        if (action_state == 0)
        {
            if (player->x_position + 40 < x_position + 31 && x_position + 31 - player->x_position + 40 <= 200) action_state = 1;
            else if (player->x_position > x_position + 31 && player->x_position - x_position + 31 <= 200) action_state = 1;
        }
        else if (action_state == 1)
        {
            if (player->x_position + 40 < x_position + 31 && x_position + 31 - player->x_position + 40 > 200) action_state = 2;
            else if (player->x_position > x_position + 31 && player->x_position - x_position + 31 > 200) action_state = 2;
        }
        else if (action_state == 2)
        {
            if (player->x_position + 40 < x_position + 31 && x_position + 31 - player->x_position + 40 <= 200) action_state = 1;
            else if (player->x_position > x_position + 31 && player->x_position - x_position + 31 <= 200) action_state = 1;
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 12)
            {
                if (extra_int == 0) game->create_actor(200, (int)x_position + 28, (int)y_position + 50, 0, 0);
                else if (extra_int > 5) if (player->cards[extra_int] == 0) game->create_actor(69, (int)x_position + 28, (int)y_position + 20, 0, extra_int);
            }
            else if (timer == 18) action_state = 4;
        }
    }
    else if (type == PENA)
    {
        if (direction == 0) x_position -= 20;
        else x_position += 20;
        game->actor_colision(this);
        if (active)
        {
            if (direction == 0) x_position -= 20;
            else x_position += 20;
            game->wall_colision(this);
            if (x_position > map->limitright) active = 0;
        }
    }
    else if (type == 65)
    {
        if (action_state == 0)
        {
            timer++;
            if (direction == 0)
            {
                y_speed++;
                if (y_speed == 2) direction = 1;
            }
            else
            {
                y_speed--;
                if (y_speed == -2) direction = 0;
            }
        }
        else
        {
            timer++;
            if (timer == 20) active = 0;
        }
    }
    else if (type == 66)
    {
        if (action_state == 1)
        {
            timer++;
            if (timer == 3) frame = SANDMORRO3;
            else if (timer == 6) frame = SANDMORRO4;
            else if (timer == 9) active = 0;
        }
    }
    else if (type == 67)
    {
        if (action_state == 1)
        {
            timer++;
            x_speed-=18;
            y_speed+=20;
            if (x_speed == 2)
            {
                x_speed = 200;
                y_speed = 0;
                frame++;
                direction++;
                if (direction > ICEHOLDER4) direction = NULO;
                if (frame > ICEHOLDER4)
                {
                    active = 0;
                    if (player->cards[extra_int] == 0) game->create_actor(69, (int)x_position + 9, (int)y_position + 6, 0, extra_int);
                }
            }
        }
    }
    else if (type == 69)
    {
        if (action_state == 0)
        {
            timer++;
            if (y_speed > 4) y_position = (int)y_position + (y_speed);
            else if (timer % 4 == 0) y_position = (int)y_position + (y_speed);
            if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
            game->actor_colision(this);
            if (timer % 4 == 0)
            {
                if (direction == 0)
                {
                    y_speed++;
                    if (y_speed == 2) direction = 1;
                }
                else
                {
                    y_speed--;
                    if (y_speed == -2) direction = 0;
                }
            }
        }
        else if (action_state == 3)
        {
            strength -= 30;
            if (strength < 0)
            {
                player->cards[extra_int] = 1;
                active = 0;
            }
        }
    }
    else if (type == 70)
    {
        y_position += y_speed;
        if (y_position < game->map->water_position) active = 0;
    }
    else if (type == 71)
    {
        if (action_state == 0)
        {
            if (player->x_position - x_position - 36 > 0 && player->x_position - x_position - 36 < 140)
            {
                game->create_actor(72, (int)x_position, (int)y_position, 0, 0);
                action_state = 1;
            }
            else if (x_position - player->x_position - 40 > 0 && x_position - player->x_position - 40 < 140)
            {
                game->create_actor(72, (int)x_position, (int)y_position, 0, 0);
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 90)
            {
                action_state = 0;
                timer = 0;
            }
        }
    }
    else if (type == 72)
    {
        if (action_state == 0) action_state = 1;
        if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                height+=17;
                y_position-=17;
            }
            else if (timer == 2)
            {
                height+=17;
                y_position-=17;
            }
            else if (timer == 3)
            {
                height+=17;
                y_position-=17;
            }
            else if (timer >= 4)
            {
                if (y_position <= player->y_position)
                {
                    action_state = 2;
                    timer = 0;
                }
                else
                {
                    y_position-=17;
                    y_speed+=17;
                }
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 6)
            {
                action_state = 3;
                frame = SEAHORSE2;
                width = 40;
                height = 41;
                timer = 0;
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 1)
            {
                width = 30;
                height = 30;
                frame = SEAHORSE3;
                if (player->x_position > x_position) x_speed = 25;
                else x_speed = -25;
            }
            else if (timer >= 10) x_position += x_speed;
            if (x_position - player->x_position - 40 > 640) active = 0;
            else if (player->x_position - x_position - 30 > 640) active = 0;
        }
    }
    else if (type == 75)
    {
        if (action_state == 0)
        {
            timer++;
            extra_int += 42;
            if (timer == 6)
            {
                extra_int = 255;
                timer = 0;
                action_state = 1;
                frame = LASTBALL1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer >= 8)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
    }
    else if (type == 77)
    {
        if (timer % 4 == 0) frame = FIRE1;
        else if (timer % 4 == 1) frame = FIRE2;
        else if (timer % 4 == 2) frame = FIRE3;
        else if (timer % 4 == 3) frame = FIRE4;
        if (action_state == 0)
        {
            timer++;
            extra_int += 32;
            if (timer == 8)
            {
                extra_int = 255;
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                x_position += -15;
                y_position += -3;
            }
            else if (timer == 3)
            {
                x_position += -13;
                y_position += -9;
            }
            else if (timer == 5)
            {
                x_position += -8;
                y_position += -12;
                if (rotate_factor == 2 && direction == 6)
                {
                    timer = 0;
                    action_state = 16;
                }
            }
            else if (timer == 7)
            {
                x_position += -3;
                y_position += -15;
            }
            else if (timer == 9)
            {
                x_position += 3;
                y_position += -15;
            }
            else if (timer == 11)
            {
                x_position += 9;
                y_position += -13;
                if (rotate_factor == 2 && direction == 5)
                {
                    timer = 0;
                    action_state = 15;
                }
            }
            else if (timer == 13)
            {
                x_position += 12;
                y_position += -8;
            }
            else if (timer == 15)
            {
                x_position += 15;
                y_position += -3;
            }
            else if (timer == 17)
            {
                x_position += 15;
                y_position += 3;
                if (rotate_factor == 2 && direction == 4)
                {
                    timer = 0;
                    action_state = 14;
                }
            }
            else if (timer == 19)
            {
                x_position += 13;
                y_position += 9;
            }
            else if (timer == 21)
            {
                x_position += 8;
                y_position += 12;
            }
            else if (timer == 23)
            {
                x_position += 3;
                y_position += 15;
                if (rotate_factor == 2 && direction == 3)
                {
                    timer = 0;
                    action_state = 13;
                }
            }
            else if (timer == 25)
            {
                x_position += -3;
                y_position += 15;
            }
            else if (timer == 27)
            {
                x_position += -9;
                y_position += 13;
                if (rotate_factor == 2 && direction == 2)
                {
                    timer = 0;
                    action_state = 12;
                }
            }
            else if (timer == 29)
            {
                x_position += -12;
                y_position += 8;
            }
            else if (timer == 31)
            {
                x_position += -15;
                y_position += 3;
                timer = -1;
                if (rotate_factor == 2 && direction == 1)
                {
                    timer = 0;
                    action_state = 11;
                }
                rotate_factor++;
            }
        }
        else if (action_state == 11)
        {
            if (x_position > 1080) x_position -= 2;
            if (x_position < 1080) x_position = 1080;
            if (y_position < 410) y_position += 6;
            if (y_position > 410) y_position = 410;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 12)
        {
            if (x_position < 1240) x_position += 2;
            if (x_position > 1240) x_position = 1240;
            if (y_position < 330) y_position += 4;
            if (y_position > 330) y_position = 330;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 13)
        {
            if (x_position < 1400) x_position += 6;
            if (x_position > 1400) x_position = 1400;
            if (y_position < 410) y_position += 6;
            if (y_position > 410) y_position = 410;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 14)
        {
            if (x_position < 1560) x_position += 10;
            if (x_position > 1560) x_position = 1560;
            if (y_position < 290) y_position += 4;
            if (y_position > 290) y_position = 290;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 15)
        {
            if (x_position < 1360) x_position += 6;
            if (x_position > 1360) x_position = 1360;
            if (y_position < 170) y_position += 2;
            if (y_position > 170) y_position = 170;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 16)
        {
            if (x_position > 920) x_position -= 6;
            if (x_position < 920) x_position = 920;
            if (y_position < 290) y_position += 4;
            if (y_position > 290) y_position = 290;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
    }
    else if (type == 78)
    {
        if (timer % 4 == 0) frame = FIRE1;
        else if (timer % 4 == 1) frame = FIRE2;
        else if (timer % 4 == 2) frame = FIRE3;
        else if (timer % 4 == 3) frame = FIRE4;
        if (action_state == 0)
        {
            timer++;
            extra_int += 32;
            if (timer == 8)
            {
                extra_int = 255;
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 1)
            {
                x_position -= -15;
                y_position += -3;
            }
            else if (timer == 3)
            {
                x_position -= -13;
                y_position += -9;
            }
            else if (timer == 5)
            {
                x_position -= -8;
                y_position += -12;
                if (rotate_factor == 2 && direction == 6)
                {
                    timer = 0;
                    action_state = 16;
                }
            }
            else if (timer == 7)
            {
                x_position -= -3;
                y_position += -15;
            }
            else if (timer == 9)
            {
                x_position -= 3;
                y_position += -15;
            }
            else if (timer == 11)
            {
                x_position -= 9;
                y_position += -13;
                if (rotate_factor == 2 && direction == 5)
                {
                    timer = 0;
                    action_state = 15;
                }
            }
            else if (timer == 13)
            {
                x_position -= 12;
                y_position += -8;
            }
            else if (timer == 15)
            {
                x_position -= 15;
                y_position += -3;
            }
            else if (timer == 17)
            {
                x_position -= 15;
                y_position += 3;
                if (rotate_factor == 2 && direction == 4)
                {
                    timer = 0;
                    action_state = 14;
                }
            }
            else if (timer == 19)
            {
                x_position -= 13;
                y_position += 9;
            }
            else if (timer == 21)
            {
                x_position -= 8;
                y_position += 12;
            }
            else if (timer == 23)
            {
                x_position -= 3;
                y_position += 15;
                if (rotate_factor == 2 && direction == 3)
                {
                    timer = 0;
                    action_state = 13;
                }
            }
            else if (timer == 25)
            {
                x_position -= -3;
                y_position += 15;
            }
            else if (timer == 27)
            {
                x_position -= -9;
                y_position += 13;
                if (rotate_factor == 2 && direction == 2)
                {
                    timer = 0;
                    action_state = 12;
                }
            }
            else if (timer == 29)
            {
                x_position -= -12;
                y_position += 8;
            }
            else if (timer == 31)
            {
                x_position -= -15;
                y_position += 3;
                timer = -1;
                if (rotate_factor == 2 && direction == 1)
                {
                    timer = 0;
                    action_state = 11;
                }
                rotate_factor++;
            }
        }
        else if (action_state == 13)
        {
            if (x_position > 1080) x_position -= 6;
            if (x_position < 1080) x_position = 1080;
            if (y_position < 410) y_position += 6;
            if (y_position > 410) y_position = 410;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 12)
        {
            if (x_position > 1240) x_position -= 2;
            if (x_position < 1240) x_position = 1240;
            if (y_position < 330) y_position += 4;
            if (y_position > 330) y_position = 330;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 11)
        {
            if (x_position < 1400) x_position += 2;
            if (x_position > 1400) x_position = 1400;
            if (y_position < 410) y_position += 6;
            if (y_position > 410) y_position = 410;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 16)
        {
            if (x_position < 1560) x_position += 6;
            if (x_position > 1560) x_position = 1560;
            if (y_position < 290) y_position += 4;
            if (y_position > 290) y_position = 290;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 15)
        {
            if (x_position > 1120) x_position -= 6;
            if (x_position < 1120) x_position = 1120;
            if (y_position < 170) y_position += 2;
            if (y_position > 170) y_position = 170;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
        else if (action_state == 14)
        {
            if (x_position > 920) x_position -= 10;
            if (x_position < 920) x_position = 920;
            if (y_position < 290) y_position += 4;
            if (y_position > 290) y_position = 290;
            timer++;
            if (timer > 85)
            {
                extra_int -= 42;
                if (extra_int <= 0) active = 0;
            }
        }
    }
    else if (type == 79)
    {
        if (action_state == 0)
        {
            timer++;
            extra_int += 60;
            if (extra_int > 255) extra_int = 255;
            if (timer == 5)
            {
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            if (direction == 0) x_position += x_speed / 2;
            else x_position -= x_speed / 2;
            y_position += y_speed / 2;
            game->actor_colision(this);
            if (active)
            {
                if (direction == 0) x_position += x_speed / 2;
                else x_position -= x_speed / 2;
                y_position += y_speed / 2;
                game->actor_colision(this);
            }
        }
        if (x_position < 840 || y_position < -80 || y_position > 680) active = 0;
    }
    */
    else if (type == YELLOW_SHOT_DSTR)
    {
        if (timer == 3) frame = SHOT_0_2;
        else if (timer == 7) frame = SHOT_0_3;
        else if (timer == 11)
        {
            active = 0;
        }
        if (active) timer++;
    }
    /*
    else if (type == WIND_SHOT_DSTR)
    {
        strength -= 16;
        x_position += x_speed * 2;
        if (timer == 2)
        {
            if (frame == WIND_SHOT01) frame = WIND_SHOT03;
            else if (frame == WIND_SHOT02) frame = WIND_SHOT03;
            else frame = WIND_SHOT01;
        }
        else if (timer == 5)
        {
            if (frame == WIND_SHOT01) frame = WIND_SHOT03;
            else if (frame == WIND_SHOT02) frame = WIND_SHOT03;
            else frame = WIND_SHOT02;
        }
        else if (timer == 10)
        {
            if (frame == WIND_SHOT01) frame = WIND_SHOT03;
            else if (frame == WIND_SHOT02) frame = WIND_SHOT03;
            else frame = WIND_SHOT01;
        }
        if (timer == 16) active = 0;
        else timer++;
    }
    else if (type == 102)
    {
        strength -= 16;
        if (timer < 16)
        {
            x_position += x_speed;
            y_position += y_speed;
        }
        else if (timer < 9)
        {
            x_position += x_speed * 2;
            y_position += y_speed * 2;
        }
        else if (timer < 4)
        {
            x_position += x_speed * 3;
            y_position += y_speed * 3;
        }
        if (timer == 16)
        {
            active = 0;
            game->fire_key = 0;
        }
        else timer++;
    }
    else if (type == 104)
    {
        if (strength == 1) active = 0;
        else if (action_state == 1)
        {
            if (timer == 2)
            {
                frame = WATERSHOTHIT2;
                width = 16;
                height = 32;
                if (direction == 0) x_position += 6;
                y_position -= 2;
            }
            else if (timer == 4)
            {
                frame = WATERSHOTHIT3;
                game->create_actor(58, (int)x_position, (int)y_position, direction, 13);
                game->create_actor(58, (int)x_position, (int)y_position + 15, direction, 8);
            }
            if (timer == 6) active = 0;
            else timer++;
        }
        else if (action_state == 2)
        {
            if (timer == 2)
            {
                frame = WATERSHOTHIT5;
                width = 32;
                height = 16;
                y_position += 6;
                x_position -= 2;
            }
            else if (timer == 4)
            {
                frame = WATERSHOTHIT6;
                game->create_actor(57, (int)x_position, (int)y_position, 0, 0);
                game->create_actor(57, (int)x_position + 15, (int)y_position, 1, 0);
            }
            if (timer == 6) active = 0;
            else timer++;
        }
        else if (action_state == 3)
        {
            if (timer == 2)
            {
                frame = WATERSHOTHIT8;
                width = 32;
                height = 16;
                //y_position += 6;
                x_position -= 2;
            }
            else if (timer == 4)
            {
                frame = WATERSHOTHIT9;
                game->create_actor(57, (int)x_position, (int)y_position + 16, 0, 666);
                game->create_actor(57, (int)x_position + 15, (int)y_position + 16, 1, 666);
            }
            if (timer == 6) active = 0;
            else timer++;
        }
    }
    else if (type == 200)
    {
        y_position = (int)y_position + (y_speed * 5);
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        game->actor_colision(this);
    }
    else if (type == 201)
    {
        y_position = (int)y_position + (y_speed * 5);
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        game->actor_colision(this);
    }
    else if (type == 202)
    {
        timer++;
        y_position = (int)y_position + (y_speed * 5);
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        game->actor_colision(this);
    }
    else if (type == 113)
    {
        if (timer == 1) frame = SHOT_13_2;
        else if (timer == 3) frame = SHOT_13_3;
        else if (timer >= 5)
        {
            active = 0;
        }
        if (active) timer++;
    }
    else if (type == 120)
    {
        if (timer == 1) frame = WTSHOT03;
        else if (timer == 3)
        {
            active = 0;
        }
        if (active) timer++;
    }
    else if (type == 112)
    {
        if (timer == 1) frame = TOLETED_2;
        else if (timer == 3) frame = TOLETED_3;
        else if (timer == 5)
        {
            active = 0;
        }
        if (active) timer++;
    }
    else if (type == 404)
    {
        timer++;
        if (timer == 3) frame = SPLASH2;
        else if (timer == 5) frame = SPLASH3;
        else if (timer == 7) active = 0;
    }
    else if (type == 501)
    {
        if (timer <= 0) active = 0;
        else timer--;
    }
    */
    else if (type == DSTR_40)
    {
        if (timer == 3) frame = DA401;
        else if (timer == 7) frame = DA402;
        else if (timer == 11)
        {
            active = 0;
        }
        if (active) timer++;
    }
    /*
    else if (type == 667)
    {
        if (timer == 1) frame = DA601;
        else if (timer == 3) frame = DA602;
        else if (timer == 5)
        {
            active = 0;
        }
        if (active) timer++;
    }
    else if (type == 301)
    {
        rotate_factor += 16;
        x_position += x_speed * 3;
        y_position += y_speed * 3;
        y_speed++;
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        if (active) game->actor_colision(this);
    }
    else if (type == 302)
    {
        rotate_factor += 4;
        x_position += x_speed * 3;
        y_position += y_speed * 3;
        y_speed++;
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        if (active) game->actor_colision(this);
    }
    else if (type == 303)
    {
        rotate_factor += 8;
        x_position += x_speed * 3;
        y_position += y_speed * 3;
        y_speed++;
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        game->actor_colision(this);
    }
    else if (type == 304)
    {
        rotate_factor += 32;
        x_position += x_speed * 3;
        y_position += y_speed * 3;
        y_speed++;
        if (y_position > (game->map->height * 20) || y_position < 0) active = 0;
        if (active) game->actor_colision(this); //301
    }
    else if (type == 305)
    {
        timer++;
        x_position += x_speed * 2;
        y_position += y_speed * 2;
        y_speed++;
        if (y_position > game->map->limitdown || y_position < 0) active = 0;
    }
    else if (type == 310)
    {
        if (timer == 1) frame = PARTICLEDESTROY2;
        else if (timer == 2)
        {
            active = 0;
        }
        if (active) timer++;
    }
    else if (type == 999)
    {
        if (timer == game->doorrecord)
        {
            //if (game->stopall == 1 && game->looper > 0 && game->looper < 9) rest(1);
            //else if (game->stopall == 1 && game->looper > 47 && game->looper < 56) rest(1);
            //else if (game->stopall == 1 && game->looper == 56)
            //{
            //    call_event = timer;
            //    timer = -1;
            //}
            //else if (stopall == 1) rest(1);
            if (game->stopall == 1 && game->looper == 56)
            {
                game->call_event = timer;
                timer = -1;
            }
        }
    }
    else if (type == 1000 && x_position < 2500)
    {
        if (timer == game->doorrecord)
        {
            if (game->stopall == 1 && game->looper == 56)
            {
                game->call_event = timer;
                timer = -1;
            }
        }
    }
    else if (type == 2000)
    {
        if (timer > 0 && timer <= 10)
        {
            timer++;
        }
        else if (timer > 10)
        {
            if ((timer % 4) == 0)
            {
                game->create_actor(113, ((int)x_position - 5), ((int)y_position - 7), 0, 0);
                game->create_actor(113, ((int)x_position + 63), ((int)y_position), 0, 0);
            }
            y_position += 12;
            if (y_position >= 540) active = 0;
            else timer++;
        }
    }
    else if (type == 2001)
    {
        if (timer > 0 && timer <= 10)
        {
            timer++;
        }
        else if (timer > 10)
        {
            if ((timer % 4) == 0)
            {
                game->create_actor(113, ((int)x_position - 5), ((int)y_position - 7), 0, 0);
                game->create_actor(113, ((int)x_position + 13), ((int)y_position), 0, 0);
            }
            y_position += 12;
            if (y_position >= 540) active = 0;
            else timer++;
        }
    }
    else if (type == 1001)
    {
        if (action_state == 0)
        {
            if (timer == 0) x_position += 180;
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            y_position += 5;
            if (timer == 50)
            {
                action_state = 1;
                game->event_organizer = extra_int + 1;
                timer = 2;
                y_position+=7;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            if (timer == 42)
            {
                action_state = 2;
                timer = 3;
                if (game->input_locked == 1) game->input_locked = 0;
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            y_position -= 12;
            if (timer == 28)
            {
                action_state = 3;
                timer = 0;
                y_position-=7;
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 10)
            {
                if (extra_int != 0)
                {
                    x_position -= 180;
                    extra_int = 0;
                }
                if (rand() % 2 == 0) y_position = 305;
                else y_position = 195;
                x_position += 840;
                width = 113;
                height = 43;
                frame = BIRDFLY1;
                direction = 0;
            }
            else if (timer == 46)
            {
                if (rand() % 2 == 0) y_position = 305;
                else y_position = 195;
                direction = 1;
                timer = 0;
                action_state = 4;
            }
            else if (timer > 10)
            {
                x_position -= 39;
            }
            else if (timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 46)
            {
                if (rand() % 2 == 0) y_position = 305;
                else y_position = 195;
                direction = 0;
                timer = 0;
                action_state = 5;
            }
            else if (timer > 10)
            {
                x_position += 39;
            }
            else if (timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (action_state == 5)
        {
            timer++;
            if (timer == 46)
            {
                y_position = -100;
                x_position += 865;
                direction = 0;
                width = 83;
                height = 110;
                frame = BIRD1;
                timer = 0;
                action_state = 6;
            }
            else if (timer > 10)
            {
                x_position -= 39;
            }
            else if (timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (action_state == 6)
        {
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            y_position += 10;
            if (timer == 25)
            {
                action_state = 7;
                timer = 0;
                frame = BIRDSTAND;
                y_position += 7;
            }
        }
        else if (action_state == 7)
        {
            timer++;
            if (timer == 50)
            {
                action_state = 8;
                timer = 3;
            }
            else if (timer >= 12)
            {
                if (timer % 8 == 0) frame = BIRDSTAND1;
                else if (timer % 8 == 2) frame = BIRDSTAND2;
                else if (timer % 8 == 4) frame = BIRDSTAND3;
                else if (timer % 8 == 6) frame = BIRDSTAND2;
                if (timer == 20)
                {
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 80, direction, 0);
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 40, direction, 0);
                }
                else if (timer == 28) game->create_actor(64, (int)x_position + 35, (int)y_position + 60, direction, 0);
                else if (timer == 36)
                {
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 80, direction, 0);
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 40, direction, 0);
                }
                else if (timer == 44) game->create_actor(64, (int)x_position + 35, (int)y_position + 60, direction, 0);
            }
        }
        else if (action_state == 8)
        {
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            y_position -= 12;
            if (timer == 28)
            {
                action_state = 9;
                timer = 0;
                y_position -= 7;
            }
        }
        else if (action_state == 9)
        {
            timer++;
            if (timer == 10)
            {
                if (rand() % 2 == 0) y_position = 305;
                else y_position = 195;
                x_position -= 905;
                width = 113;
                height = 43;
                frame = BIRDFLY1;
                direction = 1;
            }
            else if (timer == 46)
            {
                if (rand() % 2 == 0) y_position = 305;
                else y_position = 195;
                direction = 0;
                timer = 0;
                action_state = 10;
            }
            else if (timer > 10)
            {
                x_position += 39;
            }
            else if (timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (action_state == 10)
        {
            timer++;
            if (timer == 46)
            {
                if (rand() % 2 == 0) y_position = 305;
                else y_position = 195;
                direction = 1;
                timer = 0;
                action_state = 11;
            }
            else if (timer > 10)
            {
                x_position -= 39;
            }
            else if (timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (action_state == 11)
        {
            timer++;
            if (timer == 46)
            {
                x_position -= 820;
                y_position = -100;
                direction = 1;
                timer = 3;
                height = 117;
                width = 83;
                frame = BIRD1;
                action_state = 12;
            }
            else if (timer > 10)
            {
                x_position += 39;
            }
            else if (timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        }
        else if (action_state == 12)
        {
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            y_position += 10;
            if (timer == 28)
            {
                action_state = 15;
                timer = 0;
                y_position+=7;
                frame = BIRDSTAND;
            }
        }
        else if (action_state == 15)
        {
            timer++;
            if (timer == 50)
            {
                action_state = 16;
                timer = 3;
            }
            else if (timer >= 12)
            {
                if (timer % 8 == 0) frame = BIRDSTAND1;
                else if (timer % 8 == 2) frame = BIRDSTAND2;
                else if (timer % 8 == 4) frame = BIRDSTAND3;
                else if (timer % 8 == 6) frame = BIRDSTAND2;
                if (timer == 20) game->create_actor(64, (int)x_position + 35, (int)y_position + 60, direction, 0);
                else if (timer == 28)
                {
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 80, direction, 0);
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 40, direction, 0);
                }
                else if (timer == 36) game->create_actor(64, (int)x_position + 35, (int)y_position + 60, direction, 0);
                else if (timer == 44)
                {
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 80, direction, 0);
                    game->create_actor(64, (int)x_position + 35, (int)y_position + 40, direction, 0);
                }
            }
        }
        else if (action_state == 16)
        {
            timer++;
            if (timer % 8 == 0) frame = BIRD1;
            else if (timer % 8 == 2) frame = BIRD2;
            else if (timer % 8 == 4) frame = BIRD3;
            else if (timer % 8 == 6) frame = BIRD2;
            y_position -= 12;
            if (timer == 28)
            {
                action_state = 3;
                timer = 0;
                y_position-=7;
                x_position += 20;
            }
        }
        else if (action_state == 13)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + (width / 2), (int)y_position + (height / 2), 0, 0);
                game->create_actor(1111, (int)x_position + (width / 2), (int)y_position + (height / 2), 0, 0);
                game->create_actor(1111, (int)x_position + (width / 2), (int)y_position + (height / 2), 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 128) - 6, (int)y_position + (rand() % 60) - 6, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 0);
                else game->lastageportal[1] = 1;
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->input_locked == 0) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1002)
    {
        if (action_state == 0)
        {
            if (timer % 8 == 0) frame = SHADOW01;
            else if (timer % 8 == 2) frame = SHADOW02;
            else if (timer % 8 == 4) frame = SHADOW03;
            else if (timer % 8 == 6)
            {
                if (direction == 0) direction = 1;
                else direction = 0;
                frame = SHADOW02;
            }
            timer++;
            if (game->event_organizer == 45)
            {
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer % 8 == 0) frame = SHADOW01;
            else if (timer % 8 == 2) frame = SHADOW02;
            else if (timer % 8 == 4) frame = SHADOW03;
            else if (timer % 8 == 6)
            {
                if (direction == 0) direction = 1;
                else direction = 0;
                frame = SHADOW02;
            }
            if (frame == SHADOW01 && direction == 0)
            {
                timer = 0;
                action_state = 2;
            }
        }
        else if (action_state == 2)
        {
            if (animation_state == 4)
            {
                y_position -= 50;
                frame = SC01;
                play_sample((SAMPLE *)mydatafile[TIRO3].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (animation_state == 6) frame = SC02;
            else if (animation_state == 8) frame = SC03;
            else if (animation_state == 10) frame = SC04;
            else if (animation_state == 12) frame = SC05;
            else if (animation_state == 14) frame = SC06;
            else if (animation_state == 16) frame = SC07;
            else if (animation_state == 18) frame = SC08;
            else if (animation_state == 20) frame = SC09;
            else if (animation_state == 22) frame = SC10;
            else if (animation_state == 24) frame = SC11;
            else if (animation_state == 26) frame = SC12;
            else if (animation_state == 28)
            {
                x_position += 25;
                frame = SHADOWBALL;
            }
            else if (animation_state > 29 && animation_state < 39) y_position -= 5;
            else if (animation_state == 40)
            {
                y_position -= 3;
                game->event_organizer = 106;
            }
            else if (game->event_organizer == 0)
            {
                animation_state = 0;
                action_state = 3;
            }
            animation_state++;
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 1)
            {
                game->input_locked = 0;
                timer = 0;
                action_state = 4;
            }
        }
        else if (action_state == 4)
        {
            x_position += x_speed;
            extra_int = 1;
            game->actor_colision(this);
            y_position += y_speed;
            extra_int = 2;
            game->actor_colision(this);
            if (hit_points_left <= 15)
            {
                if (y_position > 200 && y_position < 300)
                {
                    action_state = 5;
                    game->input_locked = 1;
                }
            }
        }
        else if (action_state == 5)
        {
            if (timer == 6) game->create_actor(1003, (int)x_position, (int)y_position, 0, 0);
            else if (timer == 36)
            {
                if (x_speed < 0) x_speed = 15;
                if (y_speed > 0) y_speed = -15;
                game->input_locked = 0;
                action_state = 6;
            }
            timer++;
        }
        else if (action_state == 6)
        {
            x_position += x_speed;
            extra_int = 1;
            game->actor_colision(this);
            y_position += y_speed;
            extra_int = 2;
            game->actor_colision(this);
        }
        else if (action_state == 7)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 25, (int)y_position + 25, 0, 0);
                game->create_actor(1111, (int)x_position + 25, (int)y_position + 25, 0, 0);
                game->create_actor(1111, (int)x_position + 25, (int)y_position + 25, 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 50) - 6, (int)y_position + (rand() % 50) - 6, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 1);
                else game->lastageportal[2] = 1;
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->bossfight == 1) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1003)
    {
        if (action_state == 0)
        {
            if (timer == 0)
            {
                if (x_position < game->map->limitright - 300) extra_int = 3;
                else
                {
                    extra_int = -3;
                    x_speed *= -1;
                    y_speed *= -1;
                }
            }
            if (timer > 0 && timer < 25) x_position += extra_int;
            else if (timer == 30) action_state = 1;
            timer++;
        }
        else if (action_state == 1)
        {
            x_position += x_speed;
            extra_int = 1;
            game->actor_colision(this);
            y_position += y_speed;
            extra_int = 2;
            game->actor_colision(this);
        }
        else if (action_state == 2)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 25, (int)y_position + 25, 0, 0);
                game->create_actor(1111, (int)x_position + 25, (int)y_position + 25, 0, 0);
                game->create_actor(1111, (int)x_position + 25, (int)y_position + 25, 0, 0);
            }
            else if (timer % 7 == 6)
            {
                game->create_actor(113, (int)x_position + (rand() % 47), (int)y_position + (rand() % 47), 0, 0);
            }
            if (game->bosslife == -1) active = 0;
            else game->lastageportal[2] = 1;
            timer++;
        }
    }
    else if (type == 1004)
    {
        if (action_state == 0)
        {
            if (game->event_organizer == 0)
            {
                timer = 0;
                action_state = 1;
                game->input_locked = 0;
            }
        }
        else if (action_state == 1)
        {
            if (timer % 4 < 2) frame = THUNDER02;
            else frame = THUNDER01;
            if (timer == 40)
            {
                timer = 0;
                action_state = 2;
            }
            else timer++;
        }
        else if (action_state == 2)
        {
            if (timer == 0)
            {
                frame = THUNDER03;
                width = 100;
                height = 63;
                y_position +=6;
            }
            if (timer == 5)
            {
                timer = 0;
                action_state = 3;
            }
            else timer++;
        }
        else if (action_state == 3)
        {
            if (timer == 0)
            {
                frame = THUNDER04;
                width = 96;
                height = 64;
                x_speed = -35;
                y_speed = -2;
                play_sample((SAMPLE *)mydatafile[ROAR2].dat, (int)(155 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (timer == 1)
            {
                x_speed = -55;
                y_speed = -2;
            }
            else if (timer == 2)
            {
                frame = THUNDER05;
                width = 130;
                x_speed = -55;
                y_speed = -1;
            }
            else if (timer == 3)
            {
                x_speed = -55;
                y_speed = -1;
            }
            else if (timer == 4)
            {
                x_speed = -55;
                y_speed = 1;
            }
            else if (timer == 5)
            {
                x_speed = -42;
                y_speed = 1;
            }
            else if (timer == 6)
            {
                frame = THUNDER04;
                width = 96;
                x_speed = -26;
                y_speed = 2;
            }
            else if (timer == 7)
            {
                x_speed = -15;
                y_speed = 2;
            }
            if (timer == 8)
            {
                timer = 0;
                action_state = 4;
                direction = 1;
                frame = THUNDER03;
                width = 100;
                height = 63;
                x_speed = 0;
                y_speed = 0;
            }
            else
            {
                x_position += x_speed;
                y_position += y_speed;
                timer++;
            }
        }
        else if (action_state == 4)
        {
            if (timer == 7)
            {
                frame = THUNDER04;
                width = 96;
                height = 64;
                x_speed = 35;
                y_speed = -2;
            }
            else if (timer == 8)
            {
                x_speed = 55;
                y_speed = -2;
            }
            else if (timer == 9)
            {
                frame = THUNDER05;
                width = 130;
                x_speed = 55;
                y_speed = -1;
            }
            else if (timer == 10)
            {
                x_speed = 55;
                y_speed = -1;
            }
            else if (timer == 11)
            {
                x_speed = 55;
                y_speed = 1;
            }
            else if (timer == 12)
            {
                x_speed = 42;
                y_speed = 1;
            }
            else if (timer == 13)
            {
                frame = THUNDER04;
                width = 96;
                x_speed = 26;
                y_speed = 2;
            }
            else if (timer == 14)
            {
                x_speed = 15;
                y_speed = 2;
            }
            if (timer == 15)
            {
                timer = 0;
                action_state = 5;
                direction = 0;
                frame = THUNDER03;
                width = 100;
                height = 63;
            }
            else
            {
                x_position += x_speed;
                y_position += y_speed;
                timer++;
            }
        }
        else if (action_state == 5)
        {
            timer++;
            if (timer == 2)
            {
                frame = THUNDER02;
                width = 98;
                height = 69;
                y_position -= 6;
            }
            else if (timer == 4) frame = THUNDER01;
            else if (timer == 6) frame = THUNDER02;
            else if (timer == 8) frame = THUNDER01;
            else if (timer == 10) frame = THUNDER02;
            else if (timer == 12) frame = THUNDER01;
            else if (timer == 14) frame = THUNDER02;
            else if (timer == 16) frame = THUNDER01;
            else if (timer == 18) frame = THUNDER02;
            else if (timer == 20) frame = THUNDER01;
            else if (timer == 22) frame = THUNDER02;
            else if (timer == 24)
            {
                frame = THUNDER03;
                y_position += 6;
            }
            else if (timer == 28)
            {
                frame = THUNDERUP01;
                y_position += 13;
                x_position += 15;
            }
            else if (timer == 29)
            {
                frame = THUNDERUP02;
                y_position += 11;
                x_position -= 4;
            }
            else if (timer == 30)
            {
                frame = THUNDERUP03;
                y_position -= 46;
                x_position += 16;
            }
            else if (timer == 31)
            {
                frame = THUNDERUP04;
                y_position -= 44;
                x_position += 17;
            }
            else if (timer == 32) y_position -= 100;
            else if (timer == 33) y_position -= 100;
            else if (timer == 34)
            {
                timer = 0;
                if (game->bosslife > 15) action_state = 6;
                else
                {
                    action_state = 7;
                    animation_state = rand() % 2;
                }
                frame = NULO;
                x_position += 200;
            }
        }
        else if (action_state == 6)
        {
            timer++;
            if (timer == 20) game->create_actor(27, 5570, 160, 0, 0);
            else if (timer == 24) game->flash_screen = 1;
            else if (timer == 25)
            {
                game->flash_screen = 2;
                game->create_actor(26, 5580, 460, 1, 0);
                game->create_actor(26, 5590, 460, 3, 0);
                game->create_actor(26, 5585, 440, 1, 0);
                game->create_actor(26, 5585, 440, 3, 0);
            }
            else if (timer == 26) game->flash_screen = 1;
            else if (timer == 27) game->flash_screen = 0;
            else if (timer == 57) game->create_actor(27, 5740, 160, 0, 0);
            else if (timer == 58) game->flash_screen = 1;
            else if (timer == 59)
            {
                game->flash_screen = 2;
                x_position = 5720;
                y_position = 411;
                frame = THUNDER01;
            }
            else if (timer == 60) game->flash_screen = 1;
            else if (timer == 61)
            {
                game->flash_screen = 0;
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 7)
        {
            if (animation_state == 0)
            {
                timer++;
                if (timer == 20) game->flash_screen = 1;
                else if (timer == 21) game->flash_screen = 2;
                else if (timer == 22) game->flash_screen = 1;
                else if (timer == 23) game->flash_screen = 0;
                else if (timer == 26)
                {
                    game->create_actor(28, 5377, 160, 0, 0);
                    game->create_actor(28, 5790, 160, 0, 0);
                }
                else if (timer == 34)
                {
                    game->create_actor(28, 5445, 160, 0, 0);
                    game->create_actor(28, 5722, 160, 0, 0);
                }
                else if (timer == 42)
                {
                    game->create_actor(28, 5513, 160, 0, 0);
                    game->create_actor(28, 5654, 160, 0, 0);
                }
                else if (timer == 50) game->create_actor(28, 5583, 160, 0, 0);
                else if (timer == 67) game->create_actor(27, 5740, 160, 0, 0);
                else if (timer == 71) game->flash_screen = 1;
                else if (timer == 72)
                {
                    game->flash_screen = 2;
                    x_position = 5720;
                    y_position = 411;
                    frame = THUNDER01;
                }
                else if (timer == 73) game->flash_screen = 1;
                else if (timer == 74)
                {
                    game->flash_screen = 0;
                    timer = 0;
                    action_state = 1;
                }
            }
            else
            {
                timer++;
                if (timer == 20) game->flash_screen = 1;
                else if (timer == 21) game->flash_screen = 2;
                else if (timer == 22) game->flash_screen = 1;
                else if (timer == 23) game->flash_screen = 0;
                else if (timer == 26)
                {
                    game->create_actor(28, 5377, 160, 0, 0);
                    game->create_actor(28, 5654, 160, 0, 0);
                }
                else if (timer == 34)
                {
                    game->create_actor(28, 5445, 160, 0, 0);
                    game->create_actor(28, 5722, 160, 0, 0);
                }
                else if (timer == 42)
                {
                    game->create_actor(28, 5513, 160, 0, 0);
                    game->create_actor(28, 5790, 160, 0, 0);
                }
                else if (timer == 50) game->create_actor(28, 5583, 160, 0, 0);
                else if (timer == 67) game->create_actor(27, 5740, 160, 0, 0);
                else if (timer == 71) game->flash_screen = 1;
                else if (timer == 72)
                {
                    game->flash_screen = 2;
                    x_position = 5720;
                    y_position = 411;
                    frame = THUNDER01;
                }
                else if (timer == 73) game->flash_screen = 1;
                else if (timer == 74)
                {
                    game->flash_screen = 0;
                    timer = 0;
                    action_state = 1;
                }
            }
        }
        else if (action_state == 8)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 48, (int)y_position + 30, 0, 0);
                game->create_actor(1111, (int)x_position + 48, (int)y_position + 30, 0, 0);
                game->create_actor(1111, (int)x_position + 48, (int)y_position + 30, 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 98) - 6, (int)y_position + (rand() % 69) - 6, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 2);
                else game->lastageportal[3] = 1;
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->bossfight == 1) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1005)
    {
        if (action_state == 0)
        {
            if (game->event_organizer == 44) action_state = 1;
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 2)
            {
                frame = TURTLE_OPEN1;
                play_sample((SAMPLE *)mydatafile[ROAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (timer == 3) frame = TURTLE_OPEN2;
            else if (timer == 10) frame = TURTLE_OPEN1;
            else if (timer == 11)
            {
                game->event_organizer = 51;
                frame = TURTLE;
            }
            else if (game->event_organizer == 0)
            {
                timer = 0;
                action_state = 2;
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 30)
            {
                extra_int = rand() % 2;
                if (hit_points_left > 20)
                {
                    if (extra_int == 0)
                    {
                        timer = 0;
                        action_state = 3;
                    }
                    else
                    {
                        timer = 0;
                        action_state = 4;
                    }
                }
                else
                {
                    if (extra_int == 0)
                    {
                        timer = 0;
                        action_state = 11;
                    }
                    else
                    {
                        timer = 0;
                        action_state = 12;
                    }
                }
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 1) frame = TURTLE_OPEN1;
            else if (timer == 2) frame = TURTLE_OPEN2;
            else if (timer == 6) game->create_actor(36, (int)x_position + 31, (int)y_position + 31, direction, 0);
            else if (timer == 16) frame = TURTLE_OPEN1;
            else if (timer == 17) frame = TURTLE;
            else if (timer == 27)
            {
                timer = 0;
                action_state = 2;
            }
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 2)
            {
                frame = TURTLE_ENTER1;
                y_position++;
            }
            else if (timer == 3)
            {
                frame = TURTLE_ENTER2;
                y_position += 2;
            }
            else if (timer == 4)
            {
                frame = TURTLE_ENTER3;
                y_position += 3;
                x_position += 32;
                width -= 32;
            }
            else if (timer == 7) game->create_actor(36, (int)x_position + 40, (int)y_position + 25, direction + 10, 1);
            else if (timer >= 8)
            {
                x_position -= 32;
                if (timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                game->actor_colision(this);
            }
        }
        else if (action_state == 5)
        {
            timer++;
            if (timer == 6) direction = 1;
            else if (timer == 10)
            {
                frame = TURTLE_ENTER2;
                y_position -= 3;
            }
            else if (timer == 11)
            {
                frame = TURTLE_ENTER1;
                y_position -= 2;
            }
            else if (timer == 12)
            {
                frame = TURTLE;
                width += 32;
                y_position--;
            }
            else if (timer == 13)
            {
                action_state = 6;
                timer = 0;
            }
        }
        else if (action_state == 6)
        {
            timer++;
            if (timer == 30)
            {
                extra_int = rand() % 2;
                if (hit_points_left > 20)
                {
                    if (extra_int == 0)
                    {
                        timer = 0;
                        action_state = 7;
                    }
                    else
                    {
                        timer = 0;
                        action_state = 8;
                    }
                }
                else
                {
                    if (extra_int == 0)
                    {
                        timer = 0;
                        action_state = 15;
                    }
                    else
                    {
                        timer = 0;
                        action_state = 16;
                    }
                }
            }
        }
        else if (action_state == 7)
        {
            timer++;
            if (timer == 1) frame = TURTLE_OPEN1;
            else if (timer == 2) frame = TURTLE_OPEN2;
            else if (timer == 6) game->create_actor(36, (int)x_position + 77, (int)y_position + 31, direction, 0);
            else if (timer == 16) frame = TURTLE_OPEN1;
            else if (timer == 17) frame = TURTLE;
            else if (timer == 27)
            {
                timer = 0;
                action_state = 6;
            }
        }
        else if (action_state == 8)
        {
            timer++;
            if (timer == 2)
            {
                frame = TURTLE_ENTER1;
                y_position++;
            }
            else if (timer == 3)
            {
                frame = TURTLE_ENTER2;
                y_position += 2;
            }
            else if (timer == 4)
            {
                frame = TURTLE_ENTER3;
                y_position += 3;
                width -= 32;
            }
            else if (timer == 7) game->create_actor(36, (int)x_position + 58, (int)y_position + 25, direction + 10, 1);
            else if (timer >= 8)
            {
                x_position += 32;
                if (timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                game->actor_colision(this);
            }
        }
        else if (action_state == 9)
        {
            timer++;
            if (timer == 6) direction = 0;
            else if (timer == 10)
            {
                frame = TURTLE_ENTER2;
                y_position -= 3;
                x_position -= 32;
                width += 32;
            }
            else if (timer == 11)
            {
                frame = TURTLE_ENTER1;
                y_position -= 2;
            }
            else if (timer == 12)
            {
                frame = TURTLE;
                y_position--;
            }
            else if (timer == 13)
            {
                action_state = 2;
                timer = 0;
            }
        }
        else if (action_state == 10)
        {
            timer++;
            if (timer == 1)
            {
                extra_int = rand() % 2;
                if (extra_int == 0)
                {
                    timer = 0;
                    action_state = 11;
                }
                else
                {
                    timer = 0;
                    action_state = 12;
                }
            }
        }
        else if (action_state == 11)
        {
            timer++;
            if (timer == 1) frame = TURTLE_OPEN1;
            else if (timer == 2) frame = TURTLE_OPEN2;
            else if (timer == 6) game->create_actor(36, (int)x_position + 31, (int)y_position + 31, direction, 0);
            else if (timer == 13) frame = TURTLE_OPEN1;
            else if (timer == 14) frame = TURTLE;
            else if (timer == 15)
            {
                timer = 0;
                action_state = 10;
            }
        }
        else if (action_state == 12)
        {
            timer++;
            if (timer == 2)
            {
                frame = TURTLE_ENTER1;
                y_position++;
            }
            else if (timer == 3)
            {
                frame = TURTLE_ENTER2;
                y_position += 2;
            }
            else if (timer == 4)
            {
                frame = TURTLE_ENTER3;
                y_position += 3;
                x_position += 32;
                width -= 32;
            }
            else if (timer == 7) game->create_actor(36, (int)x_position + 40, (int)y_position + 25, direction + 10, 1);
            else if (timer >= 8)
            {
                x_position -= 32;
                if (timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                game->actor_colision(this);
            }
        }
        else if (action_state == 13)
        {
            timer++;
            if (timer == 2) direction = 1;
            else if (timer == 4)
            {
                frame = TURTLE_ENTER2;
                y_position -= 3;
            }
            else if (timer == 5)
            {
                frame = TURTLE_ENTER1;
                y_position -= 2;
            }
            else if (timer == 6)
            {
                frame = TURTLE;
                width += 32;
                y_position--;
            }
            else if (timer == 7)
            {
                action_state = 14;
                timer = 0;
            }
        }
        else if (action_state == 14)
        {
            timer++;
            if (timer == 1)
            {
                extra_int = rand() % 2;
                if (extra_int == 0)
                {
                    timer = 0;
                    action_state = 15;
                }
                else
                {
                    timer = 0;
                    action_state = 16;
                }
            }
        }
        else if (action_state == 15)
        {
            timer++;
            if (timer == 1) frame = TURTLE_OPEN1;
            else if (timer == 2) frame = TURTLE_OPEN2;
            else if (timer == 6) game->create_actor(36, (int)x_position + 77, (int)y_position + 31, direction, 0);
            else if (timer == 13) frame = TURTLE_OPEN1;
            else if (timer == 14) frame = TURTLE;
            else if (timer == 15)
            {
                timer = 0;
                action_state = 14;
            }
        }
        else if (action_state == 16)
        {
            timer++;
            if (timer == 2)
            {
                frame = TURTLE_ENTER1;
                y_position++;
            }
            else if (timer == 3)
            {
                frame = TURTLE_ENTER2;
                y_position += 2;
            }
            else if (timer == 4)
            {
                frame = TURTLE_ENTER3;
                y_position += 3;
                width -= 32;
            }
            else if (timer == 7) game->create_actor(36, (int)x_position + 58, (int)y_position + 25, direction + 10, 1);
            else if (timer >= 8)
            {
                x_position += 32;
                if (timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                game->actor_colision(this);
            }
        }
        else if (action_state == 17)
        {
            timer++;
            if (timer == 2) direction = 0;
            else if (timer == 4)
            {
                frame = TURTLE_ENTER2;
                y_position -= 3;
                x_position -= 32;
                width += 32;
            }
            else if (timer == 5)
            {
                frame = TURTLE_ENTER1;
                y_position -= 2;
            }
            else if (timer == 6)
            {
                frame = TURTLE;
                y_position--;
            }
            else if (timer == 7)
            {
                action_state = 11;
                timer = 0;
            }
        }
        else if (action_state == 18)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 55, (int)y_position + 30, 0, 0);
                game->create_actor(1111, (int)x_position + 55, (int)y_position + 30, 0, 0);
                game->create_actor(1111, (int)x_position + 55, (int)y_position + 30, 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 128) - 6, (int)y_position + (rand() % 60) - 6, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 3);
                else game->lastageportal[4] = 1;
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->bossfight == 1) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1006)
    {
        if (action_state == 0)
        {
            timer++;
            if (timer % 12 == 3) frame = SCALED01;
            else if (timer % 12 == 6) frame = SCALED02;
            else if (timer % 12 == 9) frame = SCALED03;
            else if (timer % 12 == 0) frame = SCALED04;
            if (game->event_organizer == 54)
            {
                action_state = 1;
                timer = 0;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 2) frame = SCALEDFIRE01;
            else if (timer == 4)
            {
                frame = SCALEDFIRE02;
                play_sample((SAMPLE *)mydatafile[ROAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (timer == 6) frame = SCALEDFIRE03;
            else if (timer == 20) frame = SCALEDFIRE02;
            else if (timer == 22) frame = SCALEDFIRE01;
            else if (timer == 24)
            {
                game->event_organizer = 61;
                frame = SCALED01;
            }
            else if (game->event_organizer == 0)
            {
                timer = 0;
                action_state = 2;
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer % 12 == 3) frame = SCALED01;
            else if (timer % 12 == 6) frame = SCALED02;
            else if (timer % 12 == 9) frame = SCALED03;
            else if (timer % 12 == 0) frame = SCALED04;
            if (timer == 50)
            {
                extra_int = rand() % 3;
                if (extra_int == 0)
                {
                    timer = 0;
                    action_state = 3;
                    frame = SCALED01;
                }
                else if (extra_int == 1)
                {
                    timer = 0;
                    action_state = 4;
                    frame = SCALED01;
                }
                else
                {
                    timer = 0;
                    action_state = 5;
                    frame = SCALED01;
                }
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer % 6 == 0 && timer < 55) game->create_actor(46, (int)x_position + 12 + (rand() % 6), (int)y_position + 13 + (rand() % 6), direction, 0);
            if (timer == 1) frame = SCALEDFIRE01;
            else if (timer == 3) frame = SCALEDFIRE02;
            else if (timer == 5) frame = SCALEDFIRE03;
            else if (timer == 57) frame = SCALEDFIRE02;
            else if (timer == 59) frame = SCALEDFIRE01;
            else if (timer == 61)
            {
                timer = 3;
                frame = SCALED01;
                action_state = 2;
            }
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 1) frame = SCALEDFIRE01;
            else if (timer == 3) frame = SCALEDFIRE02;
            else if (timer == 5) frame = SCALEDFIRE03;
            else if (timer == 20) game->create_actor(47, (int)x_position + 30, (int)y_position + 15, direction, 0);
            else if (timer == 26) frame = SCALEDFIRE02;
            else if (timer == 28) frame = SCALEDFIRE01;
            else if (timer == 30)
            {
                timer = 3;
                frame = SCALED01;
                action_state = 2;
            }
        }
        else if (action_state == 5)
        {
            timer++;
            if (timer == 1)
            {
                frame = SCALEDCUT01;
                y_position -= 8;
            }
            else if (timer == 8)
            {
                game->create_actor(48, (int)x_position + 5, (int)y_position + 32, direction, 0);
                game->create_actor(49, (int)x_position + 5, (int)y_position + 32, direction, 0);
                frame = SCALEDCUT02;
            }
            else if (timer == 15)
            {
                y_position += 8;
                timer = 3;
                frame = SCALED01;
                action_state = 2;
            }
        }
        else if (action_state == 6)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 64, (int)y_position + 53, 0, 0);
                game->create_actor(1111, (int)x_position + 64, (int)y_position + 53, 0, 0);
                game->create_actor(1111, (int)x_position + 64, (int)y_position + 53, 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 128) - 6, (int)y_position + (rand() % 60) - 6, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 4);
                else game->lastageportal[5] = 1;
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->bossfight == 1) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1007)
    {
        if (action_state == 0)
        {
            timer++;
            if (timer % 4 == 1) frame = ICYSHADOW01;
            else if (timer % 4 == 2) frame = ICYSHADOW02;
            else if (timer % 4 == 3) frame = ICYSHADOW03;
            else if (timer % 4 == 0) frame = ICYSHADOW02;
            x_position -= 20;
            if (timer == 45)
            {
                action_state = 1;
                timer = 0;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer == 6)
            {
                frame = ICYSHADOW04;
                x_position += 690;
                y_position = 1220;
                width = 65;
                height = 154;
            }
            else if (timer > 6 && timer < 18)
            {
                y_position -= 30;
                if (y_position < 206) frame = ICYUP01;
            }
            else if (timer == 18)
            {
                frame = ICYUP02;
                x_position -= 5;
                width = 106;
                height = 140;
            }
            else if (timer == 20)
            {
                x_position -= 5;
                frame = ICYUP03;
                width = 120;
                height = 138;
            }
            else if (timer == 22)
            {
                game->event_organizer = 51;
            }
            else if (game->input_locked == 0 && game->bossfight == 1)
            {
                action_state = 2;
                timer = 0;
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 20)
            {
                game->create_actor(56, (int)x_position - 50, (int)y_position + 60, direction, 3);
            }
            else if (timer == 35)
            {
                game->create_actor(56, (int)x_position - 30, (int)y_position + 130, direction, 3);
            }
            else if (timer == 50)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 5;
            }
            else if (timer == 52)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 5;
            }
            else if (timer > 53)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 1)
            {
                frame = ICYSHADOW02;
                width = 154;
                height = 65;
                x_position = 3140;
                y_position = 1110;
                direction = 0;
            }
            else if (timer > 10 && timer < 16)
            {
                x_position += 30;
            }
            else if (timer > 15 && timer < 19)
            {
                x_position += 30;
                y_position -= 10;
            }
            else if (timer > 18 && timer < 40)
            {
                x_position += 30;
            }
            else if (timer == 40)
            {
                if (hit_points_left > 25)
                {
                    if (player->x_position > 3640) action_state = 6;
                    else action_state = 7;
                }
                else if (hit_points_left > 10)
                {
                    if (player->x_position > 3640) action_state = 10;
                    else action_state = 11;
                }
                else
                {
                    if (player->x_position > 3640) action_state = 14;
                    else action_state = 15;
                }
                timer = 0;
            }
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 1)
            {
                frame = ICYSHADOW02;
                width = 154;
                height = 65;
                x_position = 3140;
                y_position = 880;
                direction = 0;
            }
            else if (timer > 5 && timer < 18)
            {
                x_position += 12;
            }
            else if (timer == 18)
            {
                frame = ICYSIDE02;
                width = 140;
                height = 106;
                x_position += 20;
                y_position += 2;
            }
            else if (timer == 19)
            {
                x_position += 15;
                y_position += 4;
            }
            else if (timer == 20)
            {
                frame = ICYSIDE03;
                width = 138;
                height = 120;
                x_position += 15;
                y_position += 7;
            }
            else if (timer == 21)
            {
                x_position += 15;
                y_position += 8;
            }
            else if (timer == 22)
            {
                frame = ICYSIDE04;
                width = 90;
                height = 148;
                x_position += 50;
                y_position += 12;
            }
            else if (timer == 23)
            {
                x_position += 12;
                y_position += 14;
            }
            else if (timer == 24)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 26;
                y_position += 18;
            }
            else if (timer == 25)
            {
                x_position += 10;
                y_position += 20;
            }
            else if (timer > 25)
            {
                y_position += 20;
                if (y_position > 1260)
                {
                    if (hit_points_left > 25)
                    {
                        if (player->x_position > 3640) action_state = 6;
                        else action_state = 7;
                    }
                    else if (hit_points_left > 10)
                    {
                        if (player->x_position > 3640) action_state = 10;
                        else action_state = 11;
                    }
                    else
                    {
                        if (player->x_position > 3640) action_state = 14;
                        else action_state = 15;
                    }
                    timer = 0;
                }
            }
        }
        else if (action_state == 5)
        {
            timer++;
            if (timer == 1)
            {
                frame = ICYSHADOW02;
                width = 154;
                height = 65;
                x_position = 3966;
                y_position = 880;
                direction = 1;
            }
            else if (timer > 5 && timer < 18)
            {
                x_position -= 12;
            }
            else if (timer == 18)
            {
                frame = ICYSIDE02;
                width = 140;
                height = 106;
                x_position -= 6;
                y_position += 2;
            }
            else if (timer == 19)
            {
                x_position -= 15;
                y_position += 4;
            }
            else if (timer == 20)
            {
                frame = ICYSIDE03;
                width = 138;
                height = 120;
                x_position -= 13;
                y_position += 7;
            }
            else if (timer == 21)
            {
                x_position -= 15;
                y_position += 8;
            }
            else if (timer == 22)
            {
                frame = ICYSIDE04;
                width = 90;
                height = 148;
                x_position -= 2;
                y_position += 12;
            }
            else if (timer == 23)
            {
                x_position -= 12;
                y_position += 14;
            }
            else if (timer == 24)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position -= 1;
                y_position += 18;
            }
            else if (timer == 25)
            {
                x_position -= 10;
                y_position += 20;
            }
            else if (timer > 25)
            {
                y_position += 20;
                if (y_position > 1260)
                {
                    if (hit_points_left > 25)
                    {
                        if (player->x_position > 3640) action_state = 6;
                        else action_state = 7;
                    }
                    else if (hit_points_left > 10)
                    {
                        if (player->x_position > 3640) action_state = 10;
                        else action_state = 11;
                    }
                    else
                    {
                        if (player->x_position > 3640) action_state = 14;
                        else action_state = 15;
                    }
                    timer = 0;
                }
            }
        }
        else if (action_state == 6 || action_state == 10 || action_state == 14)
        {
            timer++;
            if (timer == 6)
            {
                frame = ICYSHADOW04;
                x_position = 3770;
                y_position = 1220;
                width = 65;
                height = 154;
                direction = 1;
            }
            else if (timer > 6 && timer < 18)
            {
                y_position -= 30;
                if (y_position < 206) frame = ICYUP01;
            }
            else if (timer == 18)
            {
                frame = ICYUP02;
                x_position -= 5;
                width = 106;
                height = 140;
            }
            else if (timer == 20)
            {
                x_position -= 5;
                frame = ICYUP03;
                width = 120;
                height = 138;
            }
            else if (timer == 30)
            {
                action_state += 2;
                timer = 0;
            }
        }
        else if (action_state == 7 || action_state == 11 || action_state == 15)
        {
            timer++;
            if (timer == 6)
            {
                frame = ICYSHADOW04;
                x_position = 3430;
                y_position = 1220;
                width = 65;
                height = 154;
                direction = 0;
            }
            else if (timer > 6 && timer < 18)
            {
                y_position -= 30;
                if (y_position < 206) frame = ICYUP01;
            }
            else if (timer == 18)
            {
                frame = ICYUP02;
                x_position -= 38;
                width = 106;
                height = 140;
            }
            else if (timer == 20)
            {
                x_position -= 12;
                frame = ICYUP03;
                width = 120;
                height = 138;
            }
            else if (timer == 30)
            {
                action_state += 2;
                timer = 0;
            }
        }
        else if (action_state == 8)
        {
            timer++;
            if (timer == 20)
            {
                game->create_actor(56, (int)x_position - 50, (int)y_position + 60, direction, 3);
            }
            else if (timer == 35)
            {
                game->create_actor(56, (int)x_position - 30, (int)y_position + 130, direction, 3);
            }
            else if (timer == 50)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 5;
            }
            else if (timer == 52)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 5;
            }
            else if (timer > 53)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 9)
        {
            timer++;
            if (timer == 20)
            {
                game->create_actor(56, (int)x_position + 123, (int)y_position + 60, direction, 3);
            }
            else if (timer == 35)
            {
                game->create_actor(56, (int)x_position + 103, (int)y_position + 130, direction, 3);
            }
            else if (timer == 50)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 12;
            }
            else if (timer == 52)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 38;
            }
            else if (timer > 53)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 12)
        {
            timer++;
            if (timer == 25)
            {
                game->create_actor(56, (int)x_position + 6, (int)y_position + 71, direction, 0);
                game->create_actor(56, (int)x_position - 25, (int)y_position + 67, direction, 1);
                game->create_actor(56, (int)x_position - 56, (int)y_position + 51, direction, 2);
                game->create_actor(56, (int)x_position - 67, (int)y_position + 26, direction, 3);
                game->create_actor(56, (int)x_position - 56, (int)y_position - 5, direction, 4);
            }
            else if (timer == 40)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 5;
            }
            else if (timer == 42)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 5;
            }
            else if (timer > 43)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 13)
        {
            timer++;
            if (timer == 25)
            {
                game->create_actor(56, (int)x_position + 67, (int)y_position + 71, direction, 0);
                game->create_actor(56, (int)x_position + 98, (int)y_position + 67, direction, 1);
                game->create_actor(56, (int)x_position + 129, (int)y_position + 51, direction, 2);
                game->create_actor(56, (int)x_position + 140, (int)y_position + 26, direction, 3);
                game->create_actor(56, (int)x_position + 129, (int)y_position - 5, direction, 4);
            }
            else if (timer == 40)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 5;
            }
            else if (timer == 42)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 5;
            }
            else if (timer > 43)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 16)
        {
            timer++;
            if (timer == 20)
            {
                game->create_actor(56, (int)x_position + 6, (int)y_position + 71, direction, 0);
                game->create_actor(56, (int)x_position - 25, (int)y_position + 67, direction, 1);
                game->create_actor(56, (int)x_position - 56, (int)y_position + 51, direction, 2);
                game->create_actor(56, (int)x_position - 67, (int)y_position + 26, direction, 3);
                game->create_actor(56, (int)x_position - 56, (int)y_position - 5, direction, 4);
            }
            if (timer == 35)
            {
                game->create_actor(56, (int)x_position - 50, (int)y_position + 60, direction, 3);
                game->create_actor(56, (int)x_position - 43, (int)y_position + 94, direction, 2);
                game->create_actor(56, (int)x_position - 43, (int)y_position + 94, direction, 4);
                game->create_actor(56, (int)x_position - 43, (int)y_position + 20, direction, 4);
                game->create_actor(56, (int)x_position - 43, (int)y_position + 20, direction, 2);
            }
            else if (timer == 60)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 5;
            }
            else if (timer == 62)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 5;
            }
            else if (timer > 63)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 17)
        {
            timer++;
            if (timer == 20)
            {
                game->create_actor(56, (int)x_position + 67, (int)y_position + 71, direction, 0);
                game->create_actor(56, (int)x_position + 98, (int)y_position + 67, direction, 1);
                game->create_actor(56, (int)x_position + 129, (int)y_position + 51, direction, 2);
                game->create_actor(56, (int)x_position + 140, (int)y_position + 26, direction, 3);
                game->create_actor(56, (int)x_position + 129, (int)y_position - 5, direction, 4);
            }
            if (timer == 35)
            {
                game->create_actor(56, (int)x_position + 123, (int)y_position + 60, direction, 3);
                game->create_actor(56, (int)x_position + 116, (int)y_position + 94, direction, 2);
                game->create_actor(56, (int)x_position + 116, (int)y_position + 94, direction, 4);
                game->create_actor(56, (int)x_position + 116, (int)y_position + 20, direction, 4);
                game->create_actor(56, (int)x_position + 116, (int)y_position + 20, direction, 2);
            }
            else if (timer == 60)
            {
                frame = ICYUP02;
                width = 106;
                height = 140;
                x_position += 5;
            }
            else if (timer == 62)
            {
                frame = ICYUP01;
                width = 65;
                height = 154;
                x_position += 5;
            }
            else if (timer > 63)
            {
                y_position -= 30;
                if (y_position <= 820) frame = ICYSHADOW04;
                if (y_position < 580)
                {
                    timer = 0;
                    if (player->y_position > 1010) action_state = 3;
                    else if (player->x_position < 3640) action_state = 4;
                    else action_state = 5;
                }
            }
        }
        else if (action_state == 18)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 60, (int)y_position + 35, 0, 0);
                game->create_actor(1111, (int)x_position + 60, (int)y_position + 35, 0, 0);
                game->create_actor(1111, (int)x_position + 60, (int)y_position + 35, 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 120) - 6, (int)y_position + (rand() % 140) - 6, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 5);
                else game->lastageportal[0] = 1;
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->bossfight == 1) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1008)
    {
        if (action_state == 0)
        {
            if (game->event_organizer == 3)
            {
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            extra_int -= 4;
            if (extra_int <= 0)
            {
                extra_int = 0;
                rest(50);
                if (game->event_organizer == 3) game->event_organizer = 61;
            }
            if (game->input_locked == 0)
            {
                timer = 20;
                action_state = 2;
                extra_int = 255;
            }
        }
        else if (action_state == 2)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1215;
                y_position = 276;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer % 15 == 0) game->create_actor(75, (int)player->x_position - 2, (int)player->y_position + 16, 0, 0);
            else if (timer == 160)
            {
                timer = 0;
                action_state = 20;
                animation_state = 2;
            }
        }
        else if (action_state == 3)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1075;
                y_position = 356;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->flash_screen = 1;
            else if (timer == 26) game->flash_screen = 2;
            else if (timer == 27) game->flash_screen = 1;
            else if (timer == 28) game->flash_screen = 0;
            else if (timer > 25 && timer % 10 == 0)
            {
                do
                {
                    animation_state = (rand() % 7) + 2;
                }
                while (animation_state == action_state);
                if (animation_state == 2) game->create_actor(76, 1218 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 3) game->create_actor(76, 1078 + (rand() % 10), 0, 0, 0);
                else if (animation_state == 4) game->create_actor(76, 1382 + (rand() % 6), 0, 0, 0);
                else if (animation_state == 5) game->create_actor(76, 1118 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 6) game->create_actor(76, 1318 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 7) game->create_actor(76, 1518 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 8) game->create_actor(76, 918 + (rand() % 30), 0, 0, 0);
            }
            else if (timer == 128)
            {
                timer = 0;
                action_state = 20;
                animation_state = 3;
            }
        }
        else if (action_state == 4)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1355;
                y_position = 356;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->flash_screen = 1;
            else if (timer == 26) game->flash_screen = 2;
            else if (timer == 27) game->flash_screen = 1;
            else if (timer == 28) game->flash_screen = 0;
            else if (timer > 25 && timer % 10 == 0)
            {
                do
                {
                    animation_state = (rand() % 7) + 2;
                }
                while (animation_state == action_state);
                if (animation_state == 2) game->create_actor(76, 1218 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 3) game->create_actor(76, 1078 + (rand() % 10), 0, 0, 0);
                else if (animation_state == 4) game->create_actor(76, 1382 + (rand() % 6), 0, 0, 0);
                else if (animation_state == 5) game->create_actor(76, 1118 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 6) game->create_actor(76, 1318 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 7) game->create_actor(76, 1518 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 8) game->create_actor(76, 918 + (rand() % 30), 0, 0, 0);
            }
            else if (timer == 128)
            {
                timer = 0;
                action_state = 20;
                animation_state = 4;
            }
        }
        else if (action_state == 5)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1115;
                y_position = 116;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 1);
            else if (timer == 29) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 2);
            else if (timer == 33) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 3);
            else if (timer == 39) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 4);
            else if (timer == 45) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 5);
            else if (timer == 51) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 6);
            else if (timer == 200)
            {
                timer = 0;
                action_state = 20;
                animation_state = 5;
            }
        }
        else if (action_state == 6)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1315;
                y_position = 116;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 1);
            else if (timer == 29) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 2);
            else if (timer == 33) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 3);
            else if (timer == 39) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 4);
            else if (timer == 45) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 5);
            else if (timer == 51) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 6);
            else if (timer == 200)
            {
                timer = 0;
                action_state = 20;
                animation_state = 6;
            }
        }
        else if (action_state == 7)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1515;
                y_position = 236;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25)
            {
                game->create_actor(79, (int)x_position - 30, (int)y_position + 9, 1, 1);
                game->create_actor(79, (int)x_position - 70, (int)y_position + 44, 1, 2);
                game->create_actor(79, (int)x_position - 80, (int)y_position + 70, 1, 3);
                game->create_actor(79, (int)x_position - 70, (int)y_position + 90, 1, 4);
                game->create_actor(79, (int)x_position - 30, (int)y_position + 110, 1, 5);
            }
            else if (timer == 60 || timer == 70 || timer == 80 || timer == 86 || timer == 96 || timer == 106 || timer == 120 ||
                     timer == 130 || timer == 140 || timer == 150 || timer == 160 || timer == 165 || timer == 180 || timer == 190)
            {
                if (player->y_position < 160 && player->x_position < 1240) game->create_actor(79, (int)x_position - 70, (int)y_position + 90, 1, 4);
                else if (player->y_position < 160) game->create_actor(79, (int)x_position - 30, (int)y_position + 110, 1, 5);
                else if (player->y_position <= 301) game->create_actor(79, (int)x_position - 80, (int)y_position + 70, 1, 3);
                else if (player->x_position < 1240) game->create_actor(79, (int)x_position - 70, (int)y_position + 44, 1, 2);
                else game->create_actor(79, (int)x_position - 30, (int)y_position + 9, 1, 1);
            }
            else if (timer == 200)
            {
                timer = 0;
                action_state = 20;
                animation_state = 7;
            }
        }
        else if (action_state == 8)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 915;
                y_position = 236;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25)
            {
                game->create_actor(79, (int)x_position + 87, (int)y_position + 9, 0, 1);
                game->create_actor(79, (int)x_position + 102, (int)y_position + 44, 0, 2);
                game->create_actor(79, (int)x_position + 106, (int)y_position + 70, 0, 3);
                game->create_actor(79, (int)x_position + 102, (int)y_position + 90, 0, 4);
                game->create_actor(79, (int)x_position + 87, (int)y_position + 110, 0, 5);
            }
            else if (timer == 60 || timer == 70 || timer == 80 || timer == 86 || timer == 96 || timer == 106 || timer == 120 ||
                     timer == 130 || timer == 140 || timer == 150 || timer == 160 || timer == 165 || timer == 180 || timer == 190)
            {
                if (player->y_position < 160 && player->x_position > 1240) game->create_actor(79, (int)x_position + 102, (int)y_position + 90, 0, 4);
                else if (player->y_position < 160) game->create_actor(79, (int)x_position + 87, (int)y_position + 110, 0, 5);
                else if (player->y_position <= 301) game->create_actor(79, (int)x_position + 106, (int)y_position + 70, 0, 3);
                else if (player->x_position > 1240) game->create_actor(79, (int)x_position + 102, (int)y_position + 44, 0, 2);
                else game->create_actor(79, (int)x_position + 87, (int)y_position + 9, 0, 1);
            }
            else if (timer == 200)
            {
                timer = 0;
                action_state = 20;
                animation_state = 8;
            }
        }
        else if (action_state == 20)
        {
            timer++;
            if (timer <= 10)
            {
                extra_int -= 32;
                if (extra_int <= 0) extra_int = 0;
            }
            else if (timer == 11)
            {
                x_position = 10;
                y_position = 10;
            }
            else if (timer == 50)
            {
                timer = 0;
                rotate_factor = 0;
                //if (hit_points_left <= 5 && cheats == 1) {
                //do { action_state = (rand() % 6) + 22; } while (action_state == (int)animation_state + 20);
                //  }
                //else {
                do
                {
                    action_state = (rand() % 7) + 2;
                }
                while (action_state == (int)animation_state);
                animation_state = 0;
                //  }
            }
        }
        else if (action_state == 22)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1215;
                y_position = 276;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->flash_screen = 1;
            else if (timer == 26) game->flash_screen = 2;
            else if (timer == 27) game->flash_screen = 1;
            else if (timer == 28) game->flash_screen = 0;
            else if (timer > 25 && timer % 10 == 0)
            {
                do
                {
                    animation_state = (rand() % 7) + 2;
                }
                while (animation_state == 2);
                if (animation_state == 2) game->create_actor(76, 1218 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 3) game->create_actor(76, 1078 + (rand() % 10), 0, 0, 0);
                else if (animation_state == 4) game->create_actor(76, 1382 + (rand() % 6), 0, 0, 0);
                else if (animation_state == 5) game->create_actor(76, 1118 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 6) game->create_actor(76, 1318 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 7) game->create_actor(76, 1518 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 8) game->create_actor(76, 918 + (rand() % 30), 0, 0, 0);
            }
            if (timer % 15 == 3 && timer > 30) game->create_actor(75, (int)player->x_position - 2, (int)player->y_position + 16, 0, 0);
            else if (timer == 160)
            {
                timer = 0;
                action_state = 40;
                animation_state = 22;
            }
        }
        else if (action_state == 23)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1115;
                y_position = 116;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->flash_screen = 1;
            else if (timer == 26) game->flash_screen = 2;
            else if (timer == 27) game->flash_screen = 1;
            else if (timer == 28) game->flash_screen = 0;
            else if (timer > 25 && timer % 10 == 0)
            {
                do
                {
                    animation_state = (rand() % 7) + 2;
                }
                while (animation_state == 5);
                if (animation_state == 2) game->create_actor(76, 1218 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 3) game->create_actor(76, 1078 + (rand() % 10), 0, 0, 0);
                else if (animation_state == 4) game->create_actor(76, 1382 + (rand() % 6), 0, 0, 0);
                else if (animation_state == 5) game->create_actor(76, 1118 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 6) game->create_actor(76, 1318 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 7) game->create_actor(76, 1518 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 8) game->create_actor(76, 918 + (rand() % 30), 0, 0, 0);
            }
            if (timer == 25) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 1);
            else if (timer == 29) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 2);
            else if (timer == 33) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 3);
            else if (timer == 39) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 4);
            else if (timer == 45) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 5);
            else if (timer == 51) game->create_actor(77, (int)x_position + 30, (int)y_position + 80, 0, 6);
            else if (timer == 190)
            {
                timer = 0;
                action_state = 40;
                animation_state = 23;
            }
        }
        else if (action_state == 24)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1315;
                y_position = 116;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 1);
            else if (timer == 29) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 2);
            else if (timer == 33) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 3);
            else if (timer == 39) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 4);
            else if (timer == 45) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 5);
            else if (timer == 51) game->create_actor(78, (int)x_position + 30, (int)y_position + 80, 0, 6);
            if (timer % 15 == 3 && timer > 30) game->create_actor(75, (int)player->x_position - 2, (int)player->y_position + 16, 0, 0);
            else if (timer == 200)
            {
                timer = 0;
                action_state = 40;
                animation_state = 24;
            }
        }
        else if (action_state == 25)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 915;
                y_position = 236;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25)
            {
                game->create_actor(79, (int)x_position + 87, (int)y_position + 9, 0, 1);
                game->create_actor(79, (int)x_position + 102, (int)y_position + 44, 0, 2);
                game->create_actor(79, (int)x_position + 106, (int)y_position + 70, 0, 3);
                game->create_actor(79, (int)x_position + 102, (int)y_position + 90, 0, 4);
                game->create_actor(79, (int)x_position + 87, (int)y_position + 110, 0, 5);
            }
            else if (timer == 60 || timer == 70 || timer == 80 || timer == 86 || timer == 96 || timer == 106 || timer == 120 ||
                     timer == 130 || timer == 140 || timer == 150 || timer == 160 || timer == 165 || timer == 180 || timer == 190)
            {
                if (player->y_position < 160 && player->x_position > 1240) game->create_actor(79, (int)x_position + 102, (int)y_position + 90, 0, 4);
                else if (player->y_position < 160) game->create_actor(79, (int)x_position + 87, (int)y_position + 110, 0, 5);
                else if (player->y_position <= 301) game->create_actor(79, (int)x_position + 106, (int)y_position + 70, 0, 3);
                else if (player->x_position > 1240) game->create_actor(79, (int)x_position + 102, (int)y_position + 44, 0, 2);
                else game->create_actor(79, (int)x_position + 87, (int)y_position + 9, 0, 1);
            }
            if (timer == 25) game->create_actor(77, 1115 + 30, 116 + 80, 0, 1);
            else if (timer == 29) game->create_actor(77, 1115 + 30, 116 + 80, 0, 2);
            else if (timer == 33) game->create_actor(77, 1115 + 30, 116 + 80, 0, 3);
            else if (timer == 39) game->create_actor(77, 1115 + 30, 116 + 80, 0, 4);
            else if (timer == 45) game->create_actor(77, 1115 + 30, 116 + 80, 0, 5);
            else if (timer == 51) game->create_actor(77, 1115 + 30, 116 + 80, 0, 6);
            else if (timer == 200)
            {
                timer = 0;
                action_state = 40;
                animation_state = 25;
            }
        }
        else if (action_state == 26)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1515;
                y_position = 236;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25)
            {
                game->create_actor(79, (int)x_position - 30, (int)y_position + 9, 1, 1);
                game->create_actor(79, (int)x_position - 70, (int)y_position + 44, 1, 2);
                game->create_actor(79, (int)x_position - 80, (int)y_position + 70, 1, 3);
                game->create_actor(79, (int)x_position - 70, (int)y_position + 90, 1, 4);
                game->create_actor(79, (int)x_position - 30, (int)y_position + 110, 1, 5);
            }
            else if (timer == 60 || timer == 70 || timer == 80 || timer == 86 || timer == 96 || timer == 106 || timer == 120 ||
                     timer == 130 || timer == 140 || timer == 150 || timer == 160 || timer == 165 || timer == 180 || timer == 190)
            {
                if (player->y_position < 160 && player->x_position < 1240) game->create_actor(79, (int)x_position - 70, (int)y_position + 90, 1, 4);
                else if (player->y_position < 160) game->create_actor(79, (int)x_position - 30, (int)y_position + 110, 1, 5);
                else if (player->y_position <= 301) game->create_actor(79, (int)x_position - 80, (int)y_position + 70, 1, 3);
                else if (player->x_position < 1240) game->create_actor(79, (int)x_position - 70, (int)y_position + 44, 1, 2);
                else game->create_actor(79, (int)x_position - 30, (int)y_position + 9, 1, 1);
            }
            if (timer % 15 == 3 && timer > 30) game->create_actor(75, (int)player->x_position - 2, (int)player->y_position + 16, 0, 0);
            else if (timer == 200)
            {
                timer = 0;
                action_state = 40;
                animation_state = 26;
            }
        }
        else if (action_state == 27)
        {
            timer++;
            if (timer == 1)
            {
                x_position = 1515;
                y_position = 236;
                extra_int = 0;
            }
            else if (timer <= 20)
            {
                extra_int += 16;
                if (extra_int > 255) extra_int = 255;
            }
            else if (timer == 25)
            {
                game->create_actor(79, (int)x_position - 30, (int)y_position + 9, 1, 1);
                game->create_actor(79, (int)x_position - 70, (int)y_position + 44, 1, 2);
                game->create_actor(79, (int)x_position - 80, (int)y_position + 70, 1, 3);
                game->create_actor(79, (int)x_position - 70, (int)y_position + 90, 1, 4);
                game->create_actor(79, (int)x_position - 30, (int)y_position + 110, 1, 5);
            }
            else if (timer == 60 || timer == 70 || timer == 80 || timer == 86 || timer == 96 || timer == 106 || timer == 120 ||
                     timer == 130 || timer == 140 || timer == 150 || timer == 160 || timer == 165 || timer == 180 || timer == 190)
            {
                if (player->y_position < 160 && player->x_position < 1240) game->create_actor(79, (int)x_position - 70, (int)y_position + 90, 1, 4);
                else if (player->y_position < 160) game->create_actor(79, (int)x_position - 30, (int)y_position + 110, 1, 5);
                else if (player->y_position <= 301) game->create_actor(79, (int)x_position - 80, (int)y_position + 70, 1, 3);
                else if (player->x_position < 1240) game->create_actor(79, (int)x_position - 70, (int)y_position + 44, 1, 2);
                else game->create_actor(79, (int)x_position - 30, (int)y_position + 9, 1, 1);
            }
            if (timer == 25) game->flash_screen = 1;
            else if (timer == 26) game->flash_screen = 2;
            else if (timer == 27) game->flash_screen = 1;
            else if (timer == 28) game->flash_screen = 0;
            else if (timer > 25 && timer % 10 == 0)
            {
                do
                {
                    animation_state = (rand() % 7) + 2;
                }
                while (animation_state == 7);
                if (animation_state == 2) game->create_actor(76, 1218 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 3) game->create_actor(76, 1078 + (rand() % 10), 0, 0, 0);
                else if (animation_state == 4) game->create_actor(76, 1382 + (rand() % 6), 0, 0, 0);
                else if (animation_state == 5) game->create_actor(76, 1118 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 6) game->create_actor(76, 1318 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 7) game->create_actor(76, 1518 + (rand() % 30), 0, 0, 0);
                else if (animation_state == 8) game->create_actor(76, 918 + (rand() % 30), 0, 0, 0);
            }
            else if (timer == 201)
            {
                timer = 0;
                action_state = 40;
                animation_state = 27;
            }
        }
        else if (action_state == 40)
        {
            timer++;
            if (timer <= 10)
            {
                extra_int -= 32;
                if (extra_int <= 0) extra_int = 0;
            }
            else if (timer == 11)
            {
                x_position = 10;
                y_position = 10;
            }
            else if (timer == 50)
            {
                timer = 0;
                rotate_factor = 0;
                do
                {
                    action_state = (rand() % 6) + 22;
                }
                while (action_state == (int)animation_state);
                animation_state = 0;
            }
        }
        else if (action_state == 666)
        {
            if (timer == 5)
            {
                game->create_actor(1111, (int)x_position + 40, (int)y_position + 60, 0, 0);
                game->create_actor(1111, (int)x_position + 40, (int)y_position + 60, 0, 0);
                game->create_actor(1111, (int)x_position + 40, (int)y_position + 60, 0, 0);
            }
            else if (timer % 7 == 3)
            {
                game->create_actor(113, (int)x_position + (rand() % 90) - 20, (int)y_position + (rand() % 120) - 10, 0, 0);
            }
            if (game->bosslife == -1)
            {
                if (game->lastageboss == 0) game->create_actor(1666, (int)x_position + (width / 2) - 11, (int)y_position + (height / 2) - 18, 0, 5);
                active = 0;
            }
            if (active) timer++;
        }
        if (hit_points_left == (int)hit_points_left && game->bossfight == 1) game->bosslife = (int)hit_points_left;
        else if (game->bosslife > hit_points_left && game->bossfight == 1) game->bosslife = (int)(hit_points_left + 0.5);
    }
    else if (type == 1666)
    {
        if (action_state == 0)
        {
            timer++;
            if (timer == 1) y_speed = 1;
            else if (timer == 2) y_speed = 2;
            else if (timer == 3) y_speed = 1;
            else if (timer == 4) y_speed = 0;
            else if (timer == 5) y_speed = -1;
            else if (timer == 6) y_speed = -2;
            else if (timer == 7) y_speed = -1;
            else if (timer == 8) y_speed = 0;
            else if (game->light_level == 1)
            {
                timer = 0;
                action_state = 1;
            }
        }
        else if (action_state == 1)
        {
            timer++;
            if (timer % 16 == 0)
            {
                frame = CARD01;
                direction = 0;
            }
            else if (timer % 16 == 2)
            {
                frame = CARD02;
                direction = 0;
            }
            else if (timer % 16 == 4)
            {
                frame = CARD03;
                direction = 0;
            }
            else if (timer % 16 == 6)
            {
                frame = CARD04;
                direction = 0;
            }
            else if (timer % 16 == 8)
            {
                frame = CARD05;
                direction = 0;
            }
            else if (timer % 16 == 10)
            {
                frame = CARD04;
                direction = 1;
            }
            else if (timer % 16 == 12)
            {
                frame = CARD03;
                direction = 1;
            }
            else if (timer % 16 == 14)
            {
                frame = CARD02;
                direction = 1;
            }
            if (x_position > player->x_position + (50 / 2) - 11 && x_position - (player->x_position + (50 / 2) - 11) > 5) x_position -= 5;
            else if (x_position < player->x_position + (50 / 2) - 11 && (player->x_position + (50 / 2) - 11) - x_position > 5) x_position += 5;
            else x_position = player->x_position + (50 / 2) - 11;
            if (y_position > player->y_position + (50 / 2) - 18 && y_position - (player->y_position + (80 / 2) - 18) > 5) y_position -= 5;
            else if (y_position < player->y_position + (80 / 2) - 18 && (player->y_position + (80 / 2) - 18) - y_position > 5) y_position += 5;
            else y_position = player->y_position + (80 / 2) - 18;
            if (y_position == player->y_position + (80 / 2) - 18 && x_position == player->x_position + (50 / 2) - 11 && timer % 16 == 0)
            {
                action_state = 2;
                timer = 0;
                play_sample((SAMPLE *)mydatafile[CARDGET].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
        }
        else if (action_state == 2)
        {
            strength -= 30;
            if (strength < 0)
            {
                player->shine = 1;
                player->cards[extra_int] = 1;
                player->score++;
                if (player->score == 10)
                {
                    player->hpmax = 16;
                    game->sparkmandril = 1;
                }
                else if (player->score == 20)
                {
                    player->hpmax = 17;
                    game->sparkmandril = 1;
                }
                else if (player->score == 30)
                {
                    player->hpmax = 18;
                    game->sparkmandril = 1;
                }
                else if (player->score == 40)
                {
                    player->hpmax = 19;
                    game->sparkmandril = 1;
                }
                else if (player->score == 52)
                {
                    player->hpmax = 20;
                    game->sparkmandril = 1;
                }
                active = 0;
            }
        }
    }
    */
}

void Actor::destroyactor()
{
    active = 0;
}

void Actor::damage(Actor *a)
{
    if (type == BOSS_WIND || type == BOSS_SHADOW || type == BOSS_THUNDER || type == BOSS_WATER || type == BOSS_FIRE || type == BOSS_ICE)
    {
        if (type == BOSS_SHADOW && action_state != 4 && action_state != 6) type = BOSS_SHADOW;
        else if (type == BOSS_ICE && ((action_state != 2 && action_state < 6) || frame < ICYSIDE01)) type = BOSS_ICE;
        else if ((type == BOSS_SHADOW || type == BOSS_SHADOW2) && hit_points_left > 0)
        {
            hit_points_left -= 3;
            if (hit_points_left < 0) hit_points_left = 0;
        }
        else if (type == LAST_BOSS) type = LAST_BOSS;
        else if (hit_points_left > 0) hit_points_left-=0.5;
        if (hit_points_left <= 0)
        {
            x_speed = y_speed = 0;
            for (ActorList::iterator it2 = game->actors.begin(); it2 != game->actors.end(); it2++)
            {
                if (it2->type == BOSS_SHADOW2)
                {
                    it2->x_speed = it2->y_speed = 0;
                    it2->action_state = 2;
                    action_state = 7;
                    it2->timer = timer = 0;
                }
            }
            if (type == BOSS_THUNDER)
            {
                action_state = 8;
                timer = 0;
            }
            else if (type == BOSS_WIND)
            {
                action_state = 13;
                timer = 0;
            }
            else if (type == BOSS_WATER)
            {
                action_state = 18;
                timer = 0;
            }
            else if (type == BOSS_FIRE)
            {
                action_state = 6;
                timer = 0;
            }
            else if (type == BOSS_ICE)
            {
                action_state = 18;
                timer = 0;
            }
            game->input_locked = 1;
            game->bosslife = 0;
            game->player.x_speed = game->player.y_speed = 0;
        }
    }
    else if (type == BOSS_SHADOW2)
    {
        for (ActorList::iterator it2 = game->actors.begin(); it2 != game->actors.end(); it2++)
        {
            if (it2->type == BOSS_SHADOW && (it2->action_state == 4 || it2->action_state == 6))
            {
                if (it2->hit_points_left > 0)
                {
                    it2->hit_points_left -= 3;
                    if (it2->hit_points_left < 0) it2->hit_points_left = 0;
                }
                if (it2->hit_points_left == 0)
                {
                    it2->x_speed = it2->y_speed = x_speed = y_speed = 0;
                    it2->action_state = 7;
                    action_state = 2;
                    it2->timer = timer = 0;
                    game->input_locked = 1;
                    game->bosslife = 0;
                }
            }
        }
    }
    else if (type == 55)
    {
        if (action_state == 0)
        {
            action_state = 1;
            extra_int = timer;
            if (timer % 6 < 4) frame = PUMPKIN05;
            else frame = PUMPKIN04;
        }
        timer = 0;
    }
    else if (type == 65)
    {
        if (action_state == 0)
        {
            action_state = 1;
            timer = 0;
            play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
            game->create_actor(CARD, (int)x_position + 9, (int)y_position + 12, 0, extra_int);
        }
    }
    else if (type == 66)
    {
        if (action_state != 1)
        {
            action_state = 1;
            frame = SANDMORRO2;
            direction = a->direction;
            play_sample((SAMPLE *)mydatafile[SANDS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
            if (game->player.cards[extra_int] == 0) game->create_actor(CARD, (int)x_position + 11, (int)y_position, 0, extra_int);
        }
    }
    else hit_points_left -= 2;
    actor_check();
}
