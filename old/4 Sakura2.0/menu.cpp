#include "menu.h"

Menu::Menu(int *hm, Player *pl)
{
    player = pl;
    position = 105;
    choice = 0;
    key_enter_rest = 1;
    key_rest = 1;
    buffer = create_bitmap(640, 480);
    clear_to_color (buffer, makecol (0, 0, 0));
    hard_mode = hm;
    fadein = false;
    fadeout = false;
    timer = 0;
    stage_select_boulder = 0;
}

Menu::~Menu()
{
    destroy_bitmap(buffer);
}

int Menu::main_menu()
{
mainmenustart:

    key_enter_rest = 1;
    key_f_rest = 1;
    key_rest = 1;
    choice = 0;
    timer = 0;

    speed_counter = 0;

    do
    {
        while (speed_counter > 0)
        {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;

            if (key[KEY_UP] && !key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 105) position = 390;
                    else position -= 95;
                    key_rest = 10;
                }
                else key_rest--;
                timer = 0;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 390) position = 105;
                    else position += 95;
                    key_rest = 10;
                }
                else key_rest--;
                timer = 0;
            }
            else
            {
                if (key_rest > 0) key_rest = 0;
                timer++;
                if (timer == 105) timer = -90;
            }

            if (key[KEY_F] && key_f_rest == 0)
            {
                if (position == 105) choice = 1;
                else if (position == 200) choice = 2;
                else if (position == 295) choice = 3;
                else if (position == 390) choice = 4;
            }

            else if (key[KEY_ENTER] && key_enter_rest == 0)
            {
                if (position == 105) choice = 1;
                else if (position == 200) choice = 2;
                else if (position == 295) choice = 3;
                else if (position == 390) choice = 4;
            }

            speed_counter--;
        }
        draw_main_menu();
    }
    while (choice == 0);

    if (choice == 1)
    {
        play_sample((SAMPLE *) mydatafile[ACCEPT].dat, (int) (255 * sound_volume_set / 255), 128, 1000, 0);

        fadeout = true;
        speed_counter = 0;
        do
        {
            draw_main_menu();
        }
        while (speed_counter <= 20);
        fadeout = false;

        position = 234;

        fadein = true;
        speed_counter = 0;
        do
        {
            draw_intro_menu();
        }
        while (speed_counter <= 20);
        fadein = false;

        speed_counter = 0;
        intro_menu();
    }
    else if (choice == 2)
    {
        if (loadgame())
        {
            return choice;
        }
    }
    else if (choice == 3)
    {
        play_sample((SAMPLE *) mydatafile[ACCEPT].dat, (int) (255 * sound_volume_set / 255), 128, 1000, 0);

        fadeout = true;
        speed_counter = 0;
        do
        {
            draw_main_menu();
        }
        while (speed_counter <= 20);
        fadeout = false;

        position = 0;
        timer = 0;

        fadein = true;
        speed_counter = 0;
        do
        {
            draw_options();
        }
        while (speed_counter <= 20);
        fadein = false;

        options();

        fadeout = true;
        speed_counter = 0;
        do
        {
            draw_options();
        }
        while (speed_counter <= 20);
        fadeout = false;

        fadein = true;
        position = 105;
        speed_counter = 0;
        do
        {
            draw_main_menu();
        }
        while (speed_counter <= 20);
        fadein = false;

        speed_counter = 0;

        choice = 0;
        position = 105;

        goto mainmenustart;
    }
    else if (choice == 4)
    {
        play_sample((SAMPLE *) mydatafile[ACCEPT].dat, (int) (255 * sound_volume_set / 255), 128, 1000, 0);

        fadeout = true;
        speed_counter = 0;
        do
        {
            draw_main_menu();
        }
        while (speed_counter <= 20);
        fadeout = false;
    }
    return choice;
}

void Menu::draw_main_menu()
{
    draw_sprite (buffer, (BITMAP*) mydatafile[MAINMENU].dat, 0, 0);
    if (position == 105)
    {
        draw_sprite (buffer, (BITMAP*) mydatafile[LOAD1].dat, 220, 160);
        draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS1].dat, 220, 255);
        draw_sprite (buffer, (BITMAP*) mydatafile[QUIT1].dat, 220, 350);
        if (timer - 50 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME1].dat, 220, 65);
        else if (timer - 55 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME2].dat, 220, 65);
        else if (timer - 60 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME3].dat, 220, 65);
        else if (timer - 65 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME4].dat, 220, 65);
        else if (timer - 70 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 65);
        else if (timer - 75 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 65);
        else if (timer - 80 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK1].dat, 220, 65);
        else if (timer - 85 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 65);
        else if (timer - 90 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 65);
        else if (timer - 95 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME4].dat, 220, 65);
        else if (timer - 100 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME3].dat, 220, 65);
        else if (timer - 105 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME2].dat, 220, 65);
    }
    else if (position == 200)
    {
        draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME1].dat, 220, 65);
        draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS1].dat, 220, 255);
        draw_sprite (buffer, (BITMAP*) mydatafile[QUIT1].dat, 220, 350);
        if (timer - 50 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD1].dat, 220, 160);
        else if (timer - 55 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD2].dat, 220, 160);
        else if (timer - 60 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD3].dat, 220, 160);
        else if (timer - 65 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD4].dat, 220, 160);
        else if (timer - 70 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 160);
        else if (timer - 75 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 160);
        else if (timer - 80 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK1].dat, 220, 160);
        else if (timer - 85 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 160);
        else if (timer - 90 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 160);
        else if (timer - 95 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD4].dat, 220, 160);
        else if (timer - 100 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD3].dat, 220, 160);
        else if (timer - 105 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[LOAD2].dat, 220, 160);
    }
    else if (position == 295)
    {
        draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME1].dat, 220, 65);
        draw_sprite (buffer, (BITMAP*) mydatafile[LOAD1].dat, 220, 160);
        draw_sprite (buffer, (BITMAP*) mydatafile[QUIT1].dat, 220, 350);
        if (timer - 50 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS1].dat, 220, 255);
        else if (timer - 55 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS2].dat, 220, 255);
        else if (timer - 60 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS3].dat, 220, 255);
        else if (timer - 65 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS4].dat, 220, 255);
        else if (timer - 70 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 255);
        else if (timer - 75 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 255);
        else if (timer - 80 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK1].dat, 220, 255);
        else if (timer - 85 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 255);
        else if (timer - 90 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 255);
        else if (timer - 95 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS4].dat, 220, 255);
        else if (timer - 100 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS3].dat, 220, 255);
        else if (timer - 105 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS2].dat, 220, 255);
    }
    else if (position == 390)
    {
        draw_sprite (buffer, (BITMAP*) mydatafile[NEWGAME1].dat, 220, 65);
        draw_sprite (buffer, (BITMAP*) mydatafile[LOAD1].dat, 220, 160);
        draw_sprite (buffer, (BITMAP*) mydatafile[OPTIONS1].dat, 220, 255);
        if (timer - 50 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT1].dat, 220, 350);
        else if (timer - 55 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT2].dat, 220, 350);
        else if (timer - 60 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT3].dat, 220, 350);
        else if (timer - 65 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT4].dat, 220, 350);
        else if (timer - 70 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 350);
        else if (timer - 75 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 350);
        else if (timer - 80 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK1].dat, 220, 350);
        else if (timer - 85 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK2].dat, 220, 350);
        else if (timer - 90 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[CARDBACK3].dat, 220, 350);
        else if (timer - 95 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT4].dat, 220, 350);
        else if (timer - 100 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT3].dat, 220, 350);
        else if (timer - 105 < 0) draw_sprite (buffer, (BITMAP*) mydatafile[QUIT2].dat, 220, 350);
    }
    draw_sprite (buffer, (BITMAP*) mydatafile[BACULO].dat, 70, (int) position - 40);
    draw_sprite_h_flip (buffer, (BITMAP*) mydatafile[BACULO].dat, 461, (int) position - 40);
    set_trans_blender (0, 0, 0, 0);
    if (fadein) draw_lit_sprite (screen, buffer, 0, 0, (int)((20 - speed_counter) * 12.75));
    else if (fadeout) draw_lit_sprite (screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    else draw_sprite (screen, buffer, 0, 0);
}

void Menu::options()
{
    key_enter_rest = 1;
    key_f_rest = 1;

    doft[0] = doft[1] = doft[2] = doft[3] = 0;

    choice = 0;
    speed_counter = 0;

    do
    {
        while (speed_counter > 0)
        {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 0) position = 3;
                    else position--;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 3) position = 0;
                    else position++;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (key[KEY_RIGHT] && !key[KEY_LEFT])
            {
                if (key_rest == 0)
                {
                    if (position == 0) music_volume_set++;
                    else sound_volume_set++;
                    if (music_volume_set <= 0)
                    {
                        music_volume_set = 0;
                        midi_pause();
                    }
                    else if (music_volume_set >= 1)
                    {
                        music_volume_set = 1;
                        midi_resume();
                    }
                    if (sound_volume_set < 0) sound_volume_set = 0;
                    else if (sound_volume_set > 255) sound_volume_set = 255;
                    key_rest = 1;
                }
                else key_rest--;
            }
            else if (!key[KEY_RIGHT] && key[KEY_LEFT])
            {
                if (key_rest == 0)
                {
                    if (position == 0) music_volume_set--;
                    else sound_volume_set--;
                    if (music_volume_set <= 0)
                    {
                        music_volume_set = 0;
                        midi_pause();
                    }
                    else if (music_volume_set >= 1)
                    {
                        music_volume_set = 1;
                        midi_resume();
                    }
                    if (sound_volume_set < 0) sound_volume_set = 0;
                    else if (sound_volume_set > 255) sound_volume_set = 255;
                    key_rest = 1;
                }
                else key_rest--;
            }
            else
            {
                if (key_rest > 0) key_rest = 0;
            }
            if (key[KEY_F] && key_f_rest == 0)
            {
                if (position == 2)
                {
                    play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    set_controls();
                }
                else if (position == 3) choice = 1;
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0)
            {
                if (position == 2)
                {
                    play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    set_controls();
                }
                else if (position == 3) choice = 1;
            }
            else if (key[KEY_K])
            {
                doft[1] = 0;
                doft[2] = 0;
                doft[3] = 0;
                doft[0] = 1;
            }
            else if (key[KEY_E])
            {
                doft[3] = 0;
                doft[2] = 0;
                doft[1] = 1;
            }
            else if (key[KEY_R])
            {
                doft[2] = 1;
                doft[3] = 0;
            }
            else if (key[KEY_O])
            {
                doft[3] = 1;
            }
            if (doft[0] == 1 && doft[1] == 1 && doft[2] == 1 && doft[3] == 1 && cheats == 0)
            {
                cheats = 1;
                play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            if (key[KEY_W])
            {
                bool bFullScreen = !bFullScreen;
                set_gfx_mode(
                    (bFullScreen)?GFX_AUTODETECT_FULLSCREEN:GFX_AUTODETECT_WINDOWED,
                    640, 480, 0, 0
                );
                while (key[KEY_W]);
            }
            speed_counter--;
        }
        draw_options();
    }
    while (choice == 0);
    choice = 0;
}

void Menu::draw_options()
{
    draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS].dat, 0, 0);
    if (position == 0)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 132, 158);
    }
    else if (position == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 132, 215);
    }
    else if (position == 2)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 132, 268);
    }
    else
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 216, 332);
    }
    rectfill(buffer, 381, 152, 381 + (int)(music_volume_set * 100), 170, makecol(98,78,253));
    rectfill(buffer, 381, 207, 381 + (int)(((sound_volume_set + 1) * 100) / 256), 225, makecol(98,78,253));
    set_trans_blender(0,0,0,0);
    if (fadein) draw_lit_sprite (screen, buffer, 0, 0, (int)((20 - speed_counter) * 12.75));
    else if (fadeout) draw_lit_sprite (screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    else draw_sprite (screen, buffer, 0, 0);
}

void Menu::set_controls()
{
    int keycount;
    bool keyflag;
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Up Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_up = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Down Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_down = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Right Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_right = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Left Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_left = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Jump Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_jump = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Fire Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_fire = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Card", 320, 232, makecol(0,0,0), -1);
    textout_centre_ex(screen, font, "Change(Right) Key", 320, 240, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_weapon1 = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Card", 320, 232, makecol(0,0,0), -1);
    textout_centre_ex(screen, font, "Change(Left) Key", 320, 240, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_weapon2 = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Start Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_menu = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Quit Key", 320, 236, makecol(0,0,0), -1);
    keyflag = true;
    while (keyflag)
    {
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                player->key_quit = keycount;
                keyflag = false;
                break;
            }
        }
    }
    do
    {
        keyflag = false;
        keycount = KEY_MAX;
        while (keycount--)
        {
            if (key[keycount])
            {
                keyflag = true;
                break;
            }
        }
    }
    while (keyflag);
    clear_keybuf();
}

void Menu::intro_menu()
{
    key_enter_rest = 1;
    key_f_rest = 1;

    speed_counter = 0;

    do
    {
        while (speed_counter > 0)
        {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 234) position = 294;
                    else position -= 60;
                    key_rest = 10;
                }
                else key_rest--;
                timer = 0;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 294) position = 234;
                    else position += 60;
                    key_rest = 10;
                }
                else key_rest--;
                timer = 0;
            }
            else
            {
                if (key_rest > 0) key_rest = 0;
                timer++;
                if (timer == 105) timer = -90;
            }
            if (key[KEY_F] && key_f_rest == 0)
            {
                if (position == 234) (*hard_mode) = 0;
                else if (position == 294) (*hard_mode) = 1;
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0)
            {
                if (position == 234) (*hard_mode) = 0;
                else if (position == 294) (*hard_mode) = 1;
            }
            speed_counter--;
        }
        draw_intro_menu();
    }
    while ((*hard_mode) == 2);

    play_sample((SAMPLE *)mydatafile[CARDGET].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);

    fadeout = true;
    speed_counter = 0;
    do
    {
        draw_intro_menu();
    }
    while (speed_counter <= 20);
    fadeout = false;

    position = position2 = 0;

    intro_sequence(buffer);
}

void Menu::draw_intro_menu()
{
    clear_to_color(buffer, makecol(0,0,0));
    draw_sprite( buffer, (BITMAP*)mydatafile[INTRO0].dat, 177, 160);
    if (position == 234)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[INTROA].dat, 232, 234);
    }
    else if (position == 294)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[INTROA].dat, 232, 294);
    }
    set_trans_blender(0,0,0,0);
    if (fadein) draw_lit_sprite (screen, buffer, 0, 0, (int)((20 - speed_counter) * 12.75));
    else if (fadeout) draw_lit_sprite (screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    else draw_sprite (screen, buffer, 0, 0);
}

int Menu::stage_select_menu()
{
    key_enter_rest = 1;
    key_f_rest = 1;
    choice = 0;
    position = position2 = 0;
    //lastageportal[0] = lastageportal[1] = lastageportal[2] = lastageportal[3] = lastageportal[4] = lastageportal[5] = 0;

    do
    {
        while (speed_counter > 0)
        {
            if (stage_select_boulder == 0 && player->cards[0] == 1 && player->cards[1] == 1 && player->cards[2] == 1 && player->cards[3] == 1 && player->cards[4] == 1 && player->cards[5] == 1)
            {
                stage_select_boulder = 1;
                speed_counter = 0;
                do
                {
                    draw_stage_select_menu();
                }
                while (speed_counter <= 20);
                stage_select_boulder = 2;
            }
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 0) position = 2;
                    else position--;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN])
            {
                if (key_rest == 0)
                {
                    if (position == 2) position = 0;
                    else position++;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (key[KEY_RIGHT] && !key[KEY_LEFT] && position != 1)
            {
                if (key_rest == 0)
                {
                    if (position2 == 3) position2 = 0;
                    else position2++;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (!key[KEY_RIGHT] && key[KEY_LEFT] && position != 1)
            {
                if (key_rest == 0)
                {
                    if (position2 == 0) position2 = 3;
                    else position2--;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else
            {
                if (key_rest > 0) key_rest = 0;
            }
            if ((key[KEY_F] && key_f_rest == 0) || (key[KEY_ENTER] && key_enter_rest == 0))
            {
                if (position == 0)
                {
                    if (position2 == 0)
                    {
                        choice = 10;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (position2 == 1)
                    {
                        choice = 40;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (position2 == 2)
                    {
                        choice = 50;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (position2 == 3)
                    {
                        choice = 1;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                }
                else if (position == 1)
                {
                    if (player->cards[0] == 1 && player->cards[1] == 1 && player->cards[2] == 1 && player->cards[3] == 1 && player->cards[4] == 1 && player->cards[5] == 1)
                    {
                        choice = 70;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else
                    {
                        stop_sample((SAMPLE *)mydatafile[DENY].dat);
                        play_sample((SAMPLE *)mydatafile[DENY].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        key_f_rest = 1;
                    }
                }
                else
                {
                    if (position2 == 0) savegame();
                    else if (position2 == 1)
                    {
                        choice = 30;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (position2 == 2)
                    {
                        choice = 60;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                    else if (position2 == 3)
                    {
                        choice = 20;
                        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                    }
                }
            }
            speed_counter--;
            timer++;
        }
        draw_stage_select_menu();
    }
    while (choice == 0);

    return choice;
}

void Menu::draw_stage_select_menu()
{
    int pisca;
    if (timer % 10 < 5) pisca = PISK1;
    else pisca = PISK2;
    draw_sprite( buffer, (BITMAP*)mydatafile[CSELECT].dat, 0, 0);
    if (player->cards[0] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWIND2].dat, 121, 88);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWIND].dat, 121, 88);
    if (player->cards[3] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWATER2].dat, 226, 88);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWATER].dat, 226, 88);
    if (player->cards[4] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEFIRE2].dat, 332, 88);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEFIRE].dat, 332, 88);
    draw_sprite( buffer, (BITMAP*)mydatafile[QUITGAME].dat, 439, 88);
    if (player->cards[2] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGETHUNDER2].dat, 226, 312);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGETHUNDER].dat, 226, 312);
    if (player->cards[5] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEICE2].dat, 332, 312);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEICE].dat, 332, 312);
    if (player->cards[1] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGESHADOW2].dat, 439, 312);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGESHADOW].dat, 439, 312);
    if (position == 0)
    {
        if (position2 == 0) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 274, 230);
        else if (position2 == 1) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 256, 265);
        else if (position2 == 2) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 220, 217);
    }
    else if (position == 1 && player->cards[0] == 1 && player->cards[1] == 1 && player->cards[2] == 1 && player->cards[3] == 1 && player->cards[4] == 1 && player->cards[5] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 249, 212);
    }
    else if (position == 2)
    {
        if (position2 == 1) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 318, 246);
        else if (position2 == 2) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 314, 205);
        else if (position2 == 3) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 362, 217);
    }
    if (stage_select_boulder == 0) draw_sprite( buffer, (BITMAP*)mydatafile[BOULDERLOL].dat, 244, 211);
    else if (stage_select_boulder == 1)
    {
        set_trans_blender(0, 0, 0, (int)((20 - speed_counter) * 12.75));
        draw_trans_sprite( buffer, (BITMAP*)mydatafile[BOULDERLOL].dat, 244, 211);
    }
    draw_sprite( buffer, (BITMAP*)mydatafile[SAVEGAME].dat, 121, 312);
    if (position != 1) draw_sprite(buffer, (BITMAP*)mydatafile[SELECT].dat, (int)(position2 * 105.5) + 120, (int)position * 112 + 87);
    else
    {
        draw_sprite(buffer, (BITMAP*)mydatafile[SELECT2].dat, 120, 178);
        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[SELECT2].dat, 501, 178);
    }
    set_trans_blender(0, 0, 0, 0);
    set_trans_blender(0,0,0,0);
    if (fadein) draw_lit_sprite (screen, buffer, 0, 0, ((int)((20 - speed_counter) * 12.75) > 255 ? 255 : (int)((20 - speed_counter) * 12.75)));
    else if (fadeout) draw_lit_sprite (screen, buffer, 0, 0, ((int)(speed_counter * 12.75) > 255 ? 255 : (int)(speed_counter * 12.75)));
    else draw_sprite (screen, buffer, 0, 0);
}

int Menu::game_menu()
{
    int xs;
    int menuposx;

gamemenustart:

    menuposx = 0;

    fadein = true;
    speed_counter = 0;
    do
    {
        draw_game_menu(menuposx);
    }
    while (speed_counter <= 20);
    fadein = false;
    speed_counter = 0;

    key_enter_rest = 1;
    key_f_rest = 1;

    choice = 0;

    do
    {
        while (speed_counter > 0)
        {
            if (menuposx == 0)
            {
                if (!key[KEY_ENTER]) key_enter_rest = 0;
                if (!key[KEY_F]) key_f_rest = 0;
                if (key[KEY_UP] && !key[KEY_DOWN])
                {
                    if (key_rest == 0)
                    {
                        if (position == 0) position = 5;
                        else position--;
                        key_rest = 10;
fix_position1:
                        if (position == 0 && position2 == 1) position = 5;
                        if (position == 0)
                        {
                            if (position2 == 1 && player->cards[0] == 0)
                            {
                                position--;
                                goto fix_position1;
                            }
                        }
                        else if (position == 1)
                        {
                            if (position2 == 0 && player->cards[2] == 0)
                            {
                                position--;
                                goto fix_position1;
                            }
                            if (position2 == 1 && player->cards[4] == 0)
                            {
                                position--;
                                goto fix_position1;
                            }
                        }
                        else if (position == 2)
                        {
                            if (position2 == 0 && player->cards[5] == 0)
                            {
                                position--;
                                goto fix_position1;
                            }
                            if (position2 == 1 && player->cards[3] == 0)
                            {
                                position--;
                                goto fix_position1;
                            }
                        }
                        else if (position == 3)
                        {
                            if (position2 == 0 && player->cards[1] == 0)
                            {
                                position--;
                                goto fix_position1;
                            }
                        }
                    }
                    else key_rest--;
                }
                else if (!key[KEY_UP] && key[KEY_DOWN])
                {
                    if (key_rest == 0)
                    {
                        if (position == 5) position = 0;
                        else position++;
                        key_rest = 10;
fix_position2:
                        if (position == 0)
                        {
                            if (position2 == 1 && player->cards[0] == 0)
                            {
                                position++;
                                goto fix_position2;
                            }
                        }
                        else if (position == 1)
                        {
                            if (position2 == 0 && player->cards[2] == 0)
                            {
                                position++;
                                goto fix_position2;
                            }
                            if (position2 == 1 && player->cards[4] == 0)
                            {
                                position++;
                                goto fix_position2;
                            }
                        }
                        else if (position == 2)
                        {
                            if (position2 == 0 && player->cards[5] == 0)
                            {
                                position++;
                                goto fix_position2;
                            }
                            if (position2 == 1 && player->cards[3] == 0)
                            {
                                position++;
                                goto fix_position2;
                            }
                        }
                        else if (position == 3)
                        {
                            if (position2 == 0 && player->cards[1] == 0)
                            {
                                position++;
                                goto fix_position2;
                            }
                        }
                    }
                    else key_rest--;
                }
                else if (key[KEY_RIGHT] && !key[KEY_LEFT] && position != 4)
                {
                    if (key_rest == 0)
                    {
                        if (position2 == 1) position2 = 0;
                        else position2++;
                        key_rest = 10;
fix_position3:
                        if (position == 0)
                        {
                            if (position2 == 1 && player->cards[0] == 0)
                            {
                                position++;
                                goto fix_position3;
                            }
                        }
                        else if (position == 1)
                        {
                            if (position2 == 0 && player->cards[2] == 0)
                            {
                                position--;
                                goto fix_position3;
                            }
                            if (position2 == 1 && player->cards[4] == 0)
                            {
                                position++;
                                goto fix_position3;
                            }
                        }
                        else if (position == 2)
                        {
                            if (position2 == 0 && player->cards[5] == 0)
                            {
                                position--;
                                goto fix_position3;
                            }
                            if (position2 == 1 && player->cards[3] == 0)
                            {
                                position++;
                                goto fix_position3;
                            }
                        }
                        else if (position == 3)
                        {
                            if (position2 == 0 && player->cards[1] == 0)
                            {
                                position--;
                                goto fix_position3;
                            }
                        }
                    }
                    else key_rest--;
                }
                else if (!key[KEY_RIGHT] && key[KEY_LEFT] && position != 4)
                {
                    if (key_rest == 0)
                    {
                        if (position2 == 0) position2 = 1;
                        else position2--;
                        key_rest = 10;
fix_position4:
                        if (position == 0)
                        {
                            if (position2 == 1 && player->cards[0] == 0)
                            {
                                position++;
                                goto fix_position4;
                            }
                        }
                        else if (position == 1)
                        {
                            if (position2 == 0 && player->cards[2] == 0)
                            {
                                position--;
                                goto fix_position4;
                            }
                            if (position2 == 1 && player->cards[4] == 0)
                            {
                                position++;
                                goto fix_position4;
                            }
                        }
                        else if (position == 2)
                        {
                            if (position2 == 0 && player->cards[5] == 0)
                            {
                                position--;
                                goto fix_position4;
                            }
                            if (position2 == 1 && player->cards[3] == 0)
                            {
                                position++;
                                goto fix_position4;
                            }
                        }
                        else if (position == 3)
                        {
                            if (position2 == 0 && player->cards[1] == 0)
                            {
                                position--;
                                goto fix_position4;
                            }
                        }
                    }
                    else key_rest--;
                }
                else
                {
                    if (key_rest > 0) key_rest = 0;
                }
                if (key[KEY_F] && key_f_rest == 0)
                {
                    if (position == 0)
                    {
                        if (position2 == 0) player->current_weapon = 1;
                        else if (position2 == 1) player->current_weapon = 2;
                    }
                    else if (position == 1)
                    {
                        if (position2 == 0) player->current_weapon = 4;
                        else if (position2 == 1) player->current_weapon = 5;
                    }
                    else if (position == 2)
                    {
                        if (position2 == 0)player->current_weapon = 7;
                        else if (position2 == 1) player->current_weapon = 6;
                    }
                    else if (position == 3)
                    {
                        if (position2 == 0) player->current_weapon = 3;
                        else if (position2 == 1)
                        {
                            choice = 2;
                            play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                        }
                    }
                    else if (position == 4)
                    {
                        fadeout = true;
                        speed_counter = 0;
                        do
                        {
                            draw_game_menu(menuposx);
                        }
                        while (speed_counter <= 20);
                        fadeout = false;

                        position2 = 0;
                        position = 0;
                        player->imune = 0;

                        fadein = true;
                        speed_counter = 0;
                        do
                        {
                            draw_options();
                        }
                        while (speed_counter <= 20);
                        fadein = false;

                        speed_counter = 0;
                        options();

                        fadeout = true;
                        speed_counter = 0;
                        do
                        {
                            draw_options();
                        }
                        while (speed_counter <= 20);
                        fadeout = false;

                        position = 0;
                        position2 = 0;
                        goto gamemenustart;
                    }
                    else if (position == 5)
                    {
                        if (position2 == 0)
                        {
                            key_f_rest = 1;
                            choice = 1;
                        }
                        else if (position2 == 1)
                        {
                            xs = 10;
                            menuposx += 10;
                        }
                    }
                }
                else if (key[KEY_ENTER] && key_enter_rest == 0)
                {
                    key_enter_rest = 1;
                    choice = 1;
                }
                speed_counter--;
            }
            else if (menuposx == 640)
            {
                if (!key[KEY_ENTER]) key_enter_rest = 0;
                if (!key[KEY_F]) key_f_rest = 0;
                if (key[KEY_F] && key_f_rest == 0)
                {
                    xs = -10;
                    menuposx -= 10;
                }
                else if (key[KEY_ENTER] && key_enter_rest == 0)
                {
                    key_enter_rest = 1;
                    choice = 1;
                }
                speed_counter--;
            }
            else
            {
                menuposx += xs;
                speed_counter--;
            }
        }
        draw_game_menu(menuposx);
    }
    while (choice == 0);

    while (key[KEY_ENTER]);

    return choice;
}

void Menu::draw_game_menu(int menuposx)
{
    masked_blit((BITMAP*)mydatafile[MENU].dat, buffer, menuposx, 0, 0, 0, 640, 480);
    if (player->cards[0] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 353 - menuposx, 92);
    }
    if (player->cards[2] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 63 - menuposx, 152);
    }
    if (player->cards[3] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 353 - menuposx, 152);
    }
    if (player->cards[5] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 63 - menuposx, 212);
    }
    if (player->cards[4] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 353 - menuposx, 212);
    }
    if (player->cards[1] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 63 - menuposx, 272);
    }
    if (position == 0)
    {
        if (position2 == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 92);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 92);
    }
    else if (position == 1)
    {
        if (position2 == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 152);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 152);
    }
    else if (position == 2)
    {
        if (position2 == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 212);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 212);
    }
    else if (position == 3)
    {
        if (position2 == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 272);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 272);
    }
    else if (position == 4)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUOPTIONS].dat, 67 - menuposx, 347);
    }
    else if (position == 5)
    {
        if (position2 == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUBACK].dat, 179 - menuposx, 425);
        else if (menuposx == 640) draw_sprite( buffer, (BITMAP*)mydatafile[SETA2].dat, 667 - menuposx, 404);
        else if (menuposx == 0) draw_sprite( buffer, (BITMAP*)mydatafile[SETA].dat, 513 - menuposx, 404);
    }
    draw_sprite( buffer, (BITMAP*)mydatafile[YELLOW_TOSKO_SHOT].dat, 89 - menuposx, 109);
    if (player->current_weapon == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENU_MA2].dat, 140 - menuposx, 104);
    }
    if (player->cards[2] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[ZOCK01].dat, 83 - menuposx, 159);
        if (player->current_weapon == 4)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[MENU_TH2].dat, 140 - menuposx, 164);
        }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_TH].dat, 140 - menuposx, 164);
    }
    if (player->cards[5] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[ICYATTACK04].dat, 71 - menuposx, 225);
        if (player->current_weapon == 7)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FR2].dat, 140 - menuposx, 224);
        }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FR].dat, 140 - menuposx, 224);
    }
    if (player->cards[1] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[SHADOWSHOT].dat, 80 - menuposx, 279);
        if (player->current_weapon == 3)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[MENU_SH2].dat, 140 - menuposx, 284);
        }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_SH].dat, 140 - menuposx, 284);
    }
    if (player->cards[0] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDY].dat, 359 - menuposx, 103);
        if (player->current_weapon == 2)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WI2].dat, 429 - menuposx, 104);
        }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WI].dat, 429 - menuposx, 104);
    }
    if (player->cards[3] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[WATERSHOT].dat, 370 - menuposx, 160);
        if (player->current_weapon == 5)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WA2].dat, 429 - menuposx, 164);
        }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WA].dat, 429 - menuposx, 164);
    }
    if (player->cards[4] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[HADOUKEN01].dat, 366 - menuposx, 222);
        if (player->current_weapon == 6)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FI2].dat, 429 - menuposx, 224);
        }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FI].dat, 429 - menuposx, 224);
    }
    draw_sprite( buffer, (BITMAP*)mydatafile[EXIT].dat, 360 - menuposx, 284);
    draw_sprite( buffer, (BITMAP*)mydatafile[VIDA + (player->current_weapon * 2) - 2].dat, 364 - menuposx, 341);
    draw_sprite( buffer, (BITMAP*)mydatafile[V0 + player->vidas].dat, 421 - menuposx, 349);
    if (player->cards[0] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[WINDY].dat, 1172 - menuposx, 343);
    }
    if (player->cards[1] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[SHADOW].dat, 1034 - menuposx, 243);
    }
    if (player->cards[2] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[THUNDER].dat, 1169 - menuposx, 193);
    }
    if (player->cards[3] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[WATERY].dat, 1172 - menuposx, 294);
    }
    if (player->cards[4] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[FIREY].dat, 755 - menuposx, 369);
    }
    if (player->cards[5] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[FREEZE].dat, 894 - menuposx, 144);
    }
    if (player->cards[6] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[ARROW].dat, 754 - menuposx, 69);
    }
    if (player->cards[7] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[BIG].dat, 755 - menuposx, 94);
    }
    if (player->cards[8] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[BUBBLES].dat, 755 - menuposx, 118);
    }
    if (player->cards[9] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[CHANGE].dat, 755 - menuposx, 143);
    }
    if (player->cards[10] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[CLOUD].dat, 755 - menuposx, 168);
    }
    if (player->cards[11] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[CREATE].dat, 755 - menuposx, 194);
    }
    if (player->cards[12] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[DARK].dat, 755 - menuposx, 218);
    }
    if (player->cards[13] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[DASH].dat, 755 - menuposx, 243);
    }
    if (player->cards[14] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[DREAM].dat, 755 - menuposx, 269);
    }
    if (player->cards[15] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[EARTHY].dat, 755 - menuposx, 293);
    }
    if (player->cards[16] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[ERASE].dat, 755 - menuposx, 319);
    }
    if (player->cards[17] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[FIGHT].dat, 755 - menuposx, 343);
    }
    if (player->cards[18] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[FLOAT].dat, 894 - menuposx, 68);
    }
    if (player->cards[19] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[FLOWER].dat, 894 - menuposx, 93);
    }
    if (player->cards[20] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[FLY].dat, 894 - menuposx, 118);
    }
    if (player->cards[21] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[GLOW].dat, 894 - menuposx, 168);
    }
    if (player->cards[22] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[ILLUSION].dat, 894 - menuposx, 193);
    }
    if (player->cards[23] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[JUMP].dat, 894 - menuposx, 219);
    }
    if (player->cards[24] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[LIBRA].dat, 894 - menuposx, 243);
    }
    if (player->cards[25] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[LIGHT].dat, 894 - menuposx, 268);
    }
    if (player->cards[26] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[LITTLE].dat, 894 - menuposx, 293);
    }
    if (player->cards[27] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[LOCK].dat, 894 - menuposx, 318);
    }
    if (player->cards[28] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[LOOP].dat, 894 - menuposx, 344);
    }
    if (player->cards[29] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[MAZE].dat, 894 - menuposx, 369);
    }
    if (player->cards[30] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[MIRROR].dat, 1034 - menuposx, 69);
    }
    if (player->cards[31] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[MIST].dat, 1034 - menuposx, 94);
    }
    if (player->cards[32] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[MOVE].dat, 1034 - menuposx, 119);
    }
    if (player->cards[33] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[POWER].dat, 1034 - menuposx, 144);
    }
    if (player->cards[34] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[RAIN].dat, 1034 - menuposx, 169);
    }
    if (player->cards[35] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[RETURN].dat, 1034 - menuposx, 194);
    }
    if (player->cards[36] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[SAND].dat, 1034 - menuposx, 218);
    }
    if (player->cards[37] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[SHIELD].dat, 1034 - menuposx, 268);
    }
    if (player->cards[38] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[SHOT].dat, 1034 - menuposx, 293);
    }
    if (player->cards[39] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[SILENT].dat, 1034 - menuposx, 318);
    }
    if (player->cards[40] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[SLEEP].dat, 1034 - menuposx, 343);
    }
    if (player->cards[41] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[SNOW].dat, 1034 - menuposx, 369);
    }
    if (player->cards[42] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[SONG].dat, 1173 - menuposx, 69);
    }
    if (player->cards[43] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[STORM].dat, 1173 - menuposx, 94);
    }
    if (player->cards[44] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[SWEET].dat, 1173 - menuposx, 119);
    }
    if (player->cards[45] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[SWORD].dat, 1173 - menuposx, 143);
    }
    if (player->cards[46] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[THROUGH].dat, 1169 - menuposx, 168);
    }
    if (player->cards[47] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[TIME].dat, 1173 - menuposx, 219);
    }
    if (player->cards[48] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[TWIN].dat, 1173 - menuposx, 244);
    }
    if (player->cards[49] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[VOICE].dat, 1172 - menuposx, 269);
    }
    if (player->cards[50] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[WAVE].dat, 1172 - menuposx, 319);
    }
    if (player->cards[51] == 1)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[WOOD].dat, 1172 - menuposx, 368);
    }
    set_trans_blender(0,0,0,0);
    if (fadein) draw_lit_sprite (screen, buffer, 0, 0, (int)((20 - speed_counter) * 12.75));
    else if (fadeout) draw_lit_sprite (screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    else draw_sprite (screen, buffer, 0, 0);
}

void Menu::savegame()
{
    ofstream fsav;
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Saving...", 320, 236, makecol(0,0,0), -1);
    fsav.open("save.sav");
    char savecode[18];
    for (int x = 0; x < 51; x+=3)
    {
        if (player->cards[x] == 1 && player->cards[x+1] == 1 && player->cards[x+2] == 1) savecode[x/3] = '1';
        else if (player->cards[x] == 1 && player->cards[x+1] == 1) savecode[x/3] = '2';
        else if (player->cards[x] == 1 && player->cards[x+2] == 1) savecode[x/3] = '3';
        else if (player->cards[x+1] == 1 && player->cards[x+2] == 1) savecode[x/3] = '4';
        else if (player->cards[x] == 1) savecode[x/3] = '5';
        else if (player->cards[x+1] == 1) savecode[x/3] = '6';
        else if (player->cards[x+2] == 1) savecode[x/3] = '7';
        else savecode[x/3] = '8';
        fsav << savecode[x/3];
    }
    if (player->cards[51] == 1 && stage_select_boulder == 2 && (*hard_mode) == 1) savecode[17] = '1';
    else if (player->cards[51] == 1 && stage_select_boulder == 2) savecode[17] = '2';
    else if (player->cards[51] == 1 && (*hard_mode) == 1) savecode[17] = '3';
    else if (stage_select_boulder == 2 && (*hard_mode) == 1) savecode[17] = '4';
    else if (player->cards[51] == 1) savecode[17] = '5';
    else if (stage_select_boulder == 2) savecode[17] = '6';
    else if ((*hard_mode) == 1) savecode[17] = '7';
    else savecode[17] = '8';
    fsav << savecode[17];
    fsav.close();
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Game Saved.", 320, 236, makecol(0,0,0), -1);
    for (speed_counter = 0; speed_counter < 120; );
}

int Menu::loadgame()
{
    ifstream fload;
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Loading...", 320, 236, makecol(0,0,0), -1);
    for (int y = 0; y < 52; y++)
    {
        player->cards[y] = 0;
    }
    stage_select_boulder = 0;
    (*hard_mode) = 0;
    player->score = 0;
    fload.open("save.sav");
    if (fload.peek() == EOF)
    {
        draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
        textout_centre_ex(screen, font, "File not found.", 320, 236, makecol(0,0,0), -1);
        play_sample((SAMPLE *)mydatafile[DENY].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        while (key[KEY_ENTER] || key[KEY_F]);
        while (!key[KEY_ENTER] && !key[KEY_F]);
        while (key[KEY_ENTER] || key[KEY_F]);
        for (speed_counter = 0; speed_counter < 60; );
        return 0;
    }
    play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    char savecode[18];
    for (int z = 0; z < 18; z++)
    {
        savecode[z] = fload.get();
    }
    for (int x = 0; x < 51; x+=3)
    {
        if (savecode[x/3] == '1')
        {
            player->cards[x] = 1;
            player->cards[x+1] = 1;
            player->cards[x+2] = 1;
            player->score+=3;
        }
        else if (savecode[x/3] == '2')
        {
            player->cards[x] = 1;
            player->cards[x+1] = 1;
            player->score += 2;
        }
        else if (savecode[x/3] == '3')
        {
            player->cards[x] = 1;
            player->cards[x+2] = 1;
            player->score += 2;
        }
        else if (savecode[x/3] == '4')
        {
            player->cards[x+1] = 1;
            player->cards[x+2] = 1;
            player->score += 2;
        }
        else if (savecode[x/3] == '5')
        {
            player->cards[x] = 1;
            player->score += 1;
        }
        else if (savecode[x/3] == '6')
        {
            player->cards[x+1] = 1;
            player->score += 1;
        }
        else if (savecode[x/3] == '7')
        {
            player->cards[x+2] = 1;
            player->score += 1;
        }
    }
    if (savecode[17] == '1')
    {
        player->cards[51] = 1;
        stage_select_boulder = 2;
        (*hard_mode) = 1;
        player->score += 1;
    }
    else if (savecode[17] == '2')
    {
        player->cards[51] = 1;
        stage_select_boulder = 2;
        player->score += 1;
    }
    else if (savecode[17] == '3')
    {
        player->cards[51] = 1;
        (*hard_mode) = 1;
        player->score += 1;
    }
    else if (savecode[17] == '4')
    {
        stage_select_boulder = 2;
        (*hard_mode) = 1;
    }
    else if (savecode[17] == '5')
    {
        player->cards[51] = 1;
        player->score += 1;
    }
    else if (savecode[17] == '6')
    {
        stage_select_boulder = 2;
    }
    else if (savecode[17] == '7')
    {
        (*hard_mode) = 1;
    }
    player->hpmax = 15 + (player->score / 10);
    if (player->score != 52 && player->hpmax == 20) player->hpmax = 19;
    fload.close();
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Game Loaded.", 320, 236, makecol(0,0,0), -1);
    for (speed_counter = 0; speed_counter < 120; );
    return 1;
}
