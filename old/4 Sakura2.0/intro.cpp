#include "intro.h"
#include "game.h"

void intro_sequence(BITMAP *buffer)
{
    int pivot_n;
    int midi_pos;

    double center;
    double timer;
    double fade_n;

    bool fadein;
    bool fadeout;

    MIDI* intro_music;

    timer = 1;
    midi_pause();

    for (speed_counter = 0; speed_counter < 120; );

    while (key[KEY_ENTER] || key[KEY_F]);

    intro_music = (MIDI *) mydatafile[INTRO].dat;
    play_midi(intro_music, 0);
    midi_pos = 4;
    midi_seek(midi_pos);

    if (music_volume_set == 0) midi_pause();

    timer = 1;
    fade_n = 255;
    fadein = fadeout = false;
    speed_counter = 0;

    do
    {
        while (speed_counter > 0)
        {
            if ((int)timer > 0)
            {
                timer+=1.5;
                fade_n-=0.75;
            }
            if ((int)timer > 0 && (int)timer % 501 == 1) fade_n = 255;
            if ((int)fade_n <= 0) fade_n = 0;
            if ((int)timer == -10)
            {
                fade_n = 10;
                timer = -30;
            }
            if (key[KEY_ENTER] || key[KEY_F]) goto exit;
            speed_counter--;
        }
        draw_intro_sequence(buffer, &timer, fade_n, fadein, fadeout);
    }
    while ((int)timer >= -20);

    fadeout = true;
    speed_counter = 0;
    do
    {
        draw_intro_sequence(buffer, &timer, fade_n, fadein, fadeout);
    }
    while (speed_counter < 100);
    fadeout = false;

    timer = 1;
    fade_n = 255;
    pivot_n = 0;
    center = 6;

    fadein = true;
    speed_counter = 0;
    do
    {
        draw_fall_sequence(buffer, pivot_n, center, fadein, fadeout);
    }
    while (speed_counter < 100);
    fadein = false;

    speed_counter = 0;

    do
    {
        while (speed_counter > 0)
        {
            speed_counter--;
            timer+=1;
            pivot_n += 3;
            if (pivot_n % 24 == 0) center -= 0.1;
            if (center < 0) timer = -20;
            if (key[KEY_ENTER] || key[KEY_F]) goto exit;
        }
        draw_fall_sequence(buffer, pivot_n, center, fadein, fadeout);
    }
    while ((int)timer >= -10);

    fadeout = true;
    speed_counter = 0;
    do
    {
        draw_fall_sequence(buffer, pivot_n, center, fadein, fadeout);
    }
    while (speed_counter < 100);
    fadeout = false;

    for (speed_counter = 0; speed_counter < 300; );

exit:

    speed_counter = 0;
}

void draw_intro_sequence(BITMAP *buffer, double *timer, double fade_n, bool fadein, bool fadeout)
{
    set_trans_blender(0,0,0,0);
    clear_to_color(buffer, makecol(0,0,0));
    if ((int)*timer > 0 && (int)*timer <= 501)
    {
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO1].dat, 160, 330, (int)fade_n);
    }
    else if ((int)*timer > 0 && (int)*timer <= 1002)
    {
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO1].dat, 160, 330, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO2].dat, 30, 100, (int)fade_n);
    }
    else if ((int)*timer > 0 && (int)*timer <= 1503)
    {
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO1].dat, 160, 330, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO2].dat, 30, 100, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO3].dat, 320, 230, (int)fade_n);
    }
    else if ((int)*timer > 0 && (int)*timer <= 1700)
    {
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO1].dat, 160, 330, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO2].dat, 30, 100, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO3].dat, 320, 230, 10);
    }
    else if ((int)*timer > 0 && (int)*timer >= 1701)
    {
        *timer = -10;
        fade_n = 10;
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO1].dat, 160, 330, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO2].dat, 30, 100, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO3].dat, 320, 230, 10);
    }
    else if ((int)*timer < 0)
    {
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO1].dat, 160, 330, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO2].dat, 30, 100, 10);
        draw_lit_sprite( buffer, (BITMAP*)mydatafile[INTRO3].dat, 320, 230, 10);
    }
    if (fadein) draw_lit_sprite (screen, buffer, 0, 0, (int)((20 - speed_counter) * 12.75));
    else if (fadeout) draw_lit_sprite (screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    else draw_sprite (screen, buffer, 0, 0);
}

void draw_fall_sequence(BITMAP *buffer, int pivot_n, double center, bool fadein, bool fadeout)
{
    set_trans_blender(0,0,0,0);
    clear_to_color(buffer, makecol(48,113,176));
    stretch_sprite(buffer, (BITMAP*)mydatafile[INTRO5].dat, 20, 150, 600, 180);
    if (pivot_n > 0) pivot_scaled_sprite(buffer, (BITMAP*)mydatafile[INTRO4].dat, 320, 215, -20, -20, itofix(pivot_n), ftofix(center));
    if (fadein) draw_lit_sprite(screen, buffer, 0, 0, (int)((20 - speed_counter) * 12.75));
    else if (fadeout) draw_lit_sprite(screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    else draw_sprite(screen, buffer, 0, 0);
}

void myend()
{
    int script_timer = 0;
    int endtextx, endtextw;
    int screenx, screeny;

    int light_level, fadeout;

    int scenario_width;
    int sealevel;

    int ending;

    BITMAP* endtext;

    BITMAP *bakg = (BITMAP *) mydatafile[BG1].dat;
    BITMAP *background = create_bitmap(800, 480);
    BITMAP *scenario = (BITMAP *) mydatafile[ENDING1].dat;
    BITMAP *buffer = create_bitmap(640, 480);

    clear_to_color(background, makecol(15,0,0));
    draw_sprite(background, bakg, 0, 0);

    speed_counter = 0;

    Player player;

    player.frame = PLAYER_MOVING01;
    player.x_position = 540;
    player.y_position = 300;
    player.move = 0;
    player.direction = 1;
    player.x_speed = 5;

    endtext = (BITMAP *) mydatafile[CREDITS1].dat;
    endtextx = 0;
    endtextw = 313;

    rest(5000);
    midi_pause();
    rest(5000);

    stage_music = (MIDI *) mydatafile[BGMB].dat;
    if (music_volume_set != 0) play_midi(stage_music, 0);

    do
    {
        while (speed_counter > 0)
        {
            script_timer++;
            if (script_timer % 8 == 0)
            {
                if (player.x_speed != 0)
                {
                    player.move++;
                    if (player.frame == PLAYER_MOVING05 || player.frame == PLAYER_MOVING04 || player.frame == PLAYER_MOVING03 || player.frame == PLAYER_MOVING02 || player.frame == PLAYER_MOVING01)
                    {
                        if (player.move == 0) player.frame = PLAYER_MOVING01;
                        else if (player.move == 1) player.frame = PLAYER_MOVING02;
                        else if (player.move == 2) player.frame = PLAYER_MOVING03;
                        else if (player.move == 3) player.frame = PLAYER_MOVING02;
                        else if (player.move == 4) player.frame = PLAYER_MOVING01;
                        else if (player.move == 5) player.frame = PLAYER_MOVING04;
                        else if (player.move == 6) player.frame = PLAYER_MOVING05;
                        else if (player.move == 7) player.frame = PLAYER_MOVING04;
                    }
                    if (player.move == 7) player.move = -1;
                }
            }
            screenx++;
            screeny+=2;

            if (screenx % 20 == 0) player.x_position--;

            if (screenx >= 160)
            {
                screenx = 0;
            }

            if (screeny == 600) endtextx = 1;
            else if (screeny >= 2800) fadeout++;

            if (endtextx > 0)
            {
                if (screeny < 2600) endtextx++;
                else endtextx--;
                if (endtextx >= 255) endtextx = 255;
            }

            if (ending == 6666)
            {
                screenx = screeny = 0;
                if (fadeout > 0) fadeout--;
            }

            if (light_level > 0)
            {
                ending++;
                if (ending % 3 == 0) light_level--;
            }
            if (ending < 0 && fadeout > 0)
            {
                fadeout--;
                if (fadeout == 0) ending += 10;
            }

            if (fadeout >= 255)
            {
                if (ending >= 10)
                {
                    ending = -1;
                    if (buffer != NULL) destroy_bitmap(buffer);
                    if (background != NULL) destroy_bitmap(background);
                    scenario_width = 160;
                    fadeout = 255;
                    bakg = (BITMAP *) mydatafile[BG2].dat;
                    background = create_bitmap(800, 480);
                    scenario = (BITMAP *) mydatafile[ENDING2].dat;
                    buffer = create_bitmap(640, 480);
                    clear_to_color(background, makecol(15,0,0));
                    draw_sprite(background, bakg, 0, 0);
                    endtext = (BITMAP *) mydatafile[CREDITS2].dat;
                    endtextx = 0;
                    endtextw = 145;
                    rest(1000);
                    screenx = screeny = 0;
                    speed_counter = 0;
                }
                else if (ending >= 9)
                {
                    ending -= 11;
                    if (buffer != NULL) destroy_bitmap(buffer);
                    if (background != NULL) destroy_bitmap(background);
                    scenario_width = 160;
                    fadeout = 255;
                    bakg = (BITMAP *) mydatafile[BG4].dat;
                    background = create_bitmap(800, 480);
                    scenario = (BITMAP *) mydatafile[ENDING3].dat;
                    buffer = create_bitmap(640, 480);
                    clear_to_color(background, makecol(15,0,0));
                    draw_sprite(background, bakg, 0, 0);
                    draw_sprite(background, bakg, 608, 0);
                    endtext = (BITMAP *) mydatafile[CREDITS3].dat;
                    endtextx = 0;
                    endtextw = 238;
                    rest(1000);
                    screenx = screeny = 0;
                    speed_counter = 0;
                }
                else if (ending >= 8)
                {
                    ending -= 11;
                    if (buffer != NULL) destroy_bitmap(buffer);
                    if (background != NULL) destroy_bitmap(background);
                    scenario_width = 160;
                    fadeout = 255;
                    bakg = (BITMAP *) mydatafile[BG5].dat;
                    background = create_bitmap(800, 480);
                    scenario = (BITMAP *) mydatafile[ENDING4].dat;
                    buffer = create_bitmap(640, 480);
                    clear_to_color(background, makecol(0,0,161));
                    draw_sprite(background, bakg, 0, 0);
                    draw_sprite(background, bakg, 400, 0);
                    sealevel = 20;
                    endtext = (BITMAP *) mydatafile[CREDITS4].dat;
                    endtextx = 0;
                    endtextw = 299;
                    rest(1000);
                    screenx = screeny = 0;
                    speed_counter = 0;
                }
                else if (ending >= 7)
                {
                    ending -= 11;
                    if (buffer != NULL) destroy_bitmap(buffer);
                    if (background != NULL) destroy_bitmap(background);
                    scenario_width = 160;
                    fadeout = 255;
                    bakg = (BITMAP *) mydatafile[BG1].dat;
                    background = create_bitmap(800, 480);
                    scenario = (BITMAP *) mydatafile[ENDING5].dat;
                    buffer = create_bitmap(640, 480);
                    clear_to_color(background, makecol(15,0,0));
                    draw_sprite(background, bakg, 0, 0);
                    sealevel = 0;
                    endtext = (BITMAP *) mydatafile[CREDITS5].dat;
                    endtextx = 0;
                    endtextw = 380;
                    rest(1000);
                    screenx = screeny = 0;
                    speed_counter = 0;
                }
                else if (ending >= 6)
                {
                    ending -= 11;
                    if (buffer != NULL) destroy_bitmap(buffer);
                    if (background != NULL) destroy_bitmap(background);
                    scenario_width = 120;
                    fadeout = 255;
                    bakg = (BITMAP *) mydatafile[BG6].dat;
                    background = create_bitmap(800, 480);
                    scenario = (BITMAP *) mydatafile[ENDING6].dat;
                    buffer = create_bitmap(640, 480);
                    clear_to_color(background, makecol(15,0,0));
                    draw_sprite(background, bakg, 0, 0);
                    draw_sprite(background, bakg, 640, 0);
                    endtext = (BITMAP *) mydatafile[CREDITS6].dat;
                    endtextx = 0;
                    endtextw = 281;
                    rest(1000);
                    screenx = screeny = 0;
                    speed_counter = 0;
                }
                else if (ending >= 5)
                {
                    ending = 6666;
                    if (buffer != NULL) destroy_bitmap(buffer);
                    if (background != NULL) destroy_bitmap(background);
                    fadeout = 255;
                    background = create_bitmap(640, 480);
                    clear_to_color(background, makecol(0,0,0));
                    buffer = create_bitmap(640, 480);
                    rest(1000);
                    screenx = screeny = 0;
                    speed_counter = 0;
                }
            }

            speed_counter--;
        }
        drawend(player, ending, fadeout, light_level, sealevel, scenario_width, screenx, screeny, endtextw, endtextw, endtext, buffer, background, scenario);
    }
    while (ending != 6666 || !key[KEY_ENTER] || fadeout > 0);

    if (player.score == 52)
    {
        clear_to_color(buffer,makecol(0,0,0));
        draw_sprite(buffer, (BITMAP *) mydatafile[CHEAT].dat, 240, 190);
        draw_sprite(screen, buffer, 0, 0);
        while (key[KEY_ENTER]);
        while (!key[KEY_ENTER]);
    }

    while (key[KEY_ENTER]);
}

void drawend(Player player, int ending, int fadeout, int light_level, int sealevel, int scenario_width, int screenx, int screeny, int endtextx, int endtextw, BITMAP *endtext, BITMAP *buffer, BITMAP *background, BITMAP *scenario)
{
    if (ending == 6666)
    {
        draw_sprite( buffer, background, 0, 0);
        draw_sprite( buffer, (BITMAP *) mydatafile[THEEND].dat, 458, 439);
        draw_sprite( buffer, (BITMAP *) mydatafile[THANKS].dat, 125, 180);
        set_trans_blender(0,0,0,0);
        draw_lit_sprite(screen, buffer, 0, 0, fadeout);
    }
    else
    {
        draw_sprite( buffer, background, -160 + (screeny / 20), 0);

        if (sealevel == 20)
        {
            draw_sprite_h_flip( buffer, background, -160 + (screeny / 20), 150);
            draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position, (int)player.y_position);
        }
        draw_sprite( buffer, scenario, -1 * scenario_width + screenx, 380 - sealevel);
        draw_sprite( buffer, scenario, 0 * scenario_width + screenx, 380 - sealevel);
        draw_sprite( buffer, scenario, 1 * scenario_width + screenx, 380 - sealevel);
        draw_sprite( buffer, scenario, 2 * scenario_width + screenx, 380 - sealevel);
        draw_sprite( buffer, scenario, 3 * scenario_width + screenx, 380 - sealevel);
        if (scenario_width == 120) draw_sprite( buffer, scenario, 4 * scenario_width + screenx, 380);
        if (scenario_width == 120) draw_sprite( buffer, scenario, 5 * scenario_width + screenx, 380);
        if (sealevel == 0) draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position, (int)player.y_position);
        set_trans_blender(0,0,0,endtextx);
        draw_trans_sprite(buffer, endtext, (int)((640 - endtextw) / 2), 60);
        if (light_level > 0)
        {
            set_trans_blender(255,255,255,0);
            draw_lit_sprite(screen, buffer, 0, 0, light_level);
        }
        else
        {
            set_trans_blender(0,0,0,0);
            draw_lit_sprite(screen, buffer, 0, 0, fadeout);
        }
    }
}

void myendsp(){}

/*
void myendsp()
{
    //int script_timer = 0;
    itsover = 0;
    screenx = 0;
    sealevel = 0;
    if (buffer != NULL) destroy_bitmap(buffer);
    if (background != NULL) destroy_bitmap(background);
    if (scenario != NULL) destroy_bitmap(scenario);
    if (bakg != NULL) destroy_bitmap(bakg);
    doorrecord = -1;
    scenario_width = 160;
    bakg = (BITMAP *) mydatafile[BG1].dat;
    background = create_bitmap(800, 480);
    scenario = (BITMAP *) mydatafile[ENDING1].dat;
    buffer = create_bitmap(640, 480);
    clear_to_color(background, makecol(15,0,0));
    draw_sprite(background, bakg, 0, 0);
    speed_counter = 0;
    player.frame = PLAYER_MOVING01;
    player.x_position = 540;
    player.y_position = 300;
    player.move = 0;
    player.direction = 1;
    player.x_speed = 5;
    drawendchar = 1;
    endtext = (BITMAP *) mydatafile[CREDITS1].dat;
    endtextx = 0;
    endtextw = 313;
    rest(5000);
    midi_pause();
    rest(5000);
    //if (stage_music != NULL) destroy_midi(stage_music);
    stage_music = (MIDI *) mydatafile[BGMB].dat;
    play_midi(stage_music, 0);
    if (music_volume_set == 0) midi_pause();
    do
    {
        while (speed_counter > 0)
        {
            screenx++;
            screeny+=2;
            if (screeny == 600) endtextx = 1;
            else if (screeny >= 2800)
            {
                fadeout++;
            }
            if (endtextx > 0)
            {
                if (screeny < 2600) endtextx++;
                else endtextx--;
                if (endtextx >= 255) endtextx = 255;
            }
            speed_counter--;
        }
        drawendsp();
    }
    while (ending != 6666 || !key[KEY_ENTER] || fadeout > 0);

    if (player.score == 52)
    {
        clear_to_color(buffer,makecol(0,0,0));
        draw_sprite(buffer, (BITMAP *) mydatafile[CHEAT].dat, 240, 190);
        draw_sprite(screen, buffer, 0, 0);
        while (key[KEY_ENTER]);
        while (!key[KEY_ENTER]);
    }

    while (key[KEY_ENTER]);
}

void drawendsp()
{
    if (ending == 6666)
    {
        if (fadeout > 0) fadeout--;
        screenx = screeny = 0;
        draw_sprite( buffer, background, 0, 0);
        draw_sprite( buffer, (BITMAP *) mydatafile[THEEND].dat, 458, 439);
        draw_sprite( buffer, (BITMAP *) mydatafile[THANKS].dat, 125, 180);
        draw_sprite( buffer, (BITMAP *) mydatafile[EWULINSETO].dat, 45, 300);
        draw_sprite( buffer, (BITMAP *) mydatafile[INIMIGODUMAL].dat, 45, 400);
        sprintf(txt, "Ewul Inseto =(");
        textout_ex(buffer, font, txt, 25, 345, makecol(255,0,0), 1);
        sprintf(txt, "Inimigo Dumal (WTF?)");
        textout_ex(buffer, font, txt, 20, 445, makecol(255,0,0), 1);
        set_trans_blender(0,0,0,0);
        draw_lit_sprite(screen, buffer, 0, 0, fadeout);
    }
    else
    {
        if (light_level > 0)
        {
            ending++;
            if (ending % 3 == 0) light_level--;
        }
        if (ending < 0 && fadeout > 0)
        {
            fadeout--;
            if (fadeout == 0) ending += 10;
        }
        if (drawendchar == 2) draw_sprite( buffer, background, -150, -80);
        else draw_sprite( buffer, background, 0, 0);
        if (sealevel == 20)
        {
            draw_sprite_h_flip( buffer, background, -160, 150);
            //draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position, (int)player.y_position);
        }
        draw_sprite( buffer, scenario, -1 * scenario_width, 380 - sealevel);
        draw_sprite( buffer, scenario, 0 * scenario_width, 380 - sealevel);
        draw_sprite( buffer, scenario, 1 * scenario_width, 380 - sealevel);
        draw_sprite( buffer, scenario, 2 * scenario_width, 380 - sealevel);
        draw_sprite( buffer, scenario, 3 * scenario_width, 380 - sealevel);
        if (scenario_width == 120) draw_sprite( buffer, scenario, 4 * scenario_width, 380);
        if (scenario_width == 120) draw_sprite( buffer, scenario, 5 * scenario_width, 380);
        //if (sealevel == 0) draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position, (int)player.y_position);
        if (drawendchar == 1)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[REDBALL01].dat, 67, 340);
            draw_sprite( buffer, (BITMAP*)mydatafile[MOLA_FELIZ].dat, 190, 260);
            draw_sprite( buffer, (BITMAP*)mydatafile[GREEN_TURRET].dat, 300, 320);
            draw_sprite( buffer, (BITMAP*)mydatafile[PIRIKITO].dat, 420, 300);
            draw_sprite( buffer, (BITMAP*)mydatafile[BIRD1].dat, 540, 260);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFA].dat, 30, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFB].dat, 150, 345);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFC].dat, 260, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFD].dat, 400, 340);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFE].dat, 530, 400);
        }
        else if (drawendchar == 2)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[GHOST01].dat, 50, 300);
            draw_sprite( buffer, (BITMAP*)mydatafile[GHOSTMASK01].dat, 460, 280);
            draw_sprite( buffer, (BITMAP*)mydatafile[SHADOWBALL].dat, 230, 320);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFF].dat, 40, 360);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFG].dat, 400, 340);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFH].dat, 190, 400);
        }
        else if (drawendchar == 3)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[WALLTURRET].dat, 38, 0);
            draw_sprite( buffer, (BITMAP*)mydatafile[ORANGE01].dat, 580, 18);
            draw_sprite( buffer, (BITMAP*)mydatafile[ORANGEH03].dat, 584, 10);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULMACHINE01].dat, 110, 310);
            draw_sprite_v_flip( buffer, (BITMAP*)mydatafile[SHOCKER01].dat, 300, 356);
            draw_sprite( buffer, (BITMAP*)mydatafile[THUNDER01].dat, 480, 311);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFI].dat, 5, 30);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFJ].dat, 80, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFK].dat, 560, 80);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFL].dat, 280, 420);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFM].dat, 440, 400);
        }
        else if (drawendchar == 4)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[RESETTI].dat, 20, 346);
            draw_sprite( buffer, (BITMAP*)mydatafile[SEAHORSE1].dat, 140, 280);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULFISH_11].dat, 240, 240);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULFISH_22].dat, 240, 270);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULFISH_31].dat, 240, 300);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULFISH_42].dat, 240, 330);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULOSTRAPT1].dat, 365 + 6, 350 + 13);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, 365, 350);
            draw_sprite( buffer, (BITMAP*)mydatafile[TURTLE].dat, 480, 310);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFN].dat, 5, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFO].dat, 100, 350);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFP].dat, 210, 390);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFQ].dat, 340, 390);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFR].dat, 485, 400);
        }
        else if (drawendchar == 5)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[FLAMETHROWER2].dat, 50, 380);
            draw_sprite( buffer, (BITMAP*)mydatafile[FLAMEMET1].dat, 157, 350);
            draw_sprite( buffer, (BITMAP*)mydatafile[EWUL_SQUID01].dat, 300, 260);
            draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[SCALED01].dat, 450, 285);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFS].dat, 15, 455);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFT].dat, 110, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFU].dat, 255, 330);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFV].dat, 440, 390);
        }
        else if (drawendchar == 6)
        {
            draw_sprite( buffer, (BITMAP*)mydatafile[ICEMET01].dat, 40, 337);
            draw_sprite( buffer, (BITMAP*)mydatafile[ICE01].dat, 207, 260);
            draw_sprite( buffer, (BITMAP*)mydatafile[ICE02].dat, 247, 260);
            draw_sprite( buffer, (BITMAP*)mydatafile[PUMPKIN01].dat, 390, 360);
            draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[ICYUP03].dat, 500, 200);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFW].dat, 10, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFX].dat, 200, 320);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFY].dat, 360, 400);
            draw_sprite( buffer, (BITMAP*)mydatafile[STAFFZ].dat, 510, 350);
        }
        set_trans_blender(0,0,0,endtextx);
        draw_trans_sprite(buffer, endtext, (int)((640 - endtextw) / 2), 60);
        if (light_level > 0)
        {
            set_trans_blender(255,255,255,0);
            draw_lit_sprite(screen, buffer, 0, 0, light_level);
        }
        else
        {
            set_trans_blender(0,0,0,0);
            draw_lit_sprite(screen, buffer, 0, 0, fadeout);
        }
        if (fadeout >= 255)
        {
            if (ending >= 10)
            {
                ending = -1;
                if (buffer != NULL) destroy_bitmap(buffer);
                if (background != NULL) destroy_bitmap(background);
                //if (scenario != 0) destroy_bitmap(scenario);
                //if (bakg != 0) destroy_bitmap(bakg);
                scenario_width = 160;
                fadeout = 255;
                bakg = (BITMAP *) mydatafile[BG2].dat;
                background = create_bitmap(800, 480);
                scenario = (BITMAP *) mydatafile[ENDING2].dat;
                drawendchar = 2;
                buffer = create_bitmap(640, 480);
                clear_to_color(background, makecol(15,0,0));
                draw_sprite(background, bakg, 0, 0);
                endtext = (BITMAP *) mydatafile[CREDITS2].dat;
                endtextx = 0;
                endtextw = 145;
                rest(1000);
                screenx = screeny = 0;
                speed_counter = 0;
            }
            else if (ending >= 9)
            {
                ending -= 11;
                if (buffer != NULL) destroy_bitmap(buffer);
                if (background != NULL) destroy_bitmap(background);
                //if (scenario != 0) destroy_bitmap(scenario);
                //if (bakg != 0) destroy_bitmap(bakg);
                scenario_width = 160;
                fadeout = 255;
                bakg = (BITMAP *) mydatafile[BG4].dat;
                background = create_bitmap(800, 480);
                scenario = (BITMAP *) mydatafile[ENDING3].dat;
                drawendchar = 3;
                buffer = create_bitmap(640, 480);
                clear_to_color(background, makecol(15,0,0));
                draw_sprite(background, bakg, 0, 0);
                draw_sprite(background, bakg, 608, 0);
                endtext = (BITMAP *) mydatafile[CREDITS3].dat;
                endtextx = 0;
                endtextw = 238;
                rest(1000);
                screenx = screeny = 0;
                speed_counter = 0;
            }
            else if (ending >= 8)
            {
                ending -= 11;
                if (buffer != NULL) destroy_bitmap(buffer);
                if (background != NULL) destroy_bitmap(background);
                //if (scenario != 0) destroy_bitmap(scenario);
                //if (bakg != 0) destroy_bitmap(bakg);
                scenario_width = 160;
                fadeout = 255;
                bakg = (BITMAP *) mydatafile[BG5].dat;
                background = create_bitmap(800, 480);
                scenario = (BITMAP *) mydatafile[ENDING4].dat;
                drawendchar = 4;
                buffer = create_bitmap(640, 480);
                clear_to_color(background, makecol(0,0,161));
                draw_sprite(background, bakg, 0, 0);
                draw_sprite(background, bakg, 400, 0);
                sealevel = 20;
                endtext = (BITMAP *) mydatafile[CREDITS4].dat;
                endtextx = 0;
                endtextw = 299;
                rest(1000);
                screenx = screeny = 0;
                speed_counter = 0;
            }
            else if (ending >= 7)
            {
                ending -= 11;
                if (buffer != NULL) destroy_bitmap(buffer);
                if (background != NULL) destroy_bitmap(background);
                //if (scenario != 0) destroy_bitmap(scenario);
                //if (bakg != 0) destroy_bitmap(bakg);
                scenario_width = 160;
                fadeout = 255;
                bakg = (BITMAP *) mydatafile[BG1].dat;
                background = create_bitmap(800, 480);
                scenario = (BITMAP *) mydatafile[ENDING5].dat;
                drawendchar = 5;
                buffer = create_bitmap(640, 480);
                clear_to_color(background, makecol(15,0,0));
                draw_sprite(background, bakg, 0, 0);
                sealevel = 0;
                endtext = (BITMAP *) mydatafile[CREDITS5].dat;
                endtextx = 0;
                endtextw = 380;
                rest(1000);
                screenx = screeny = 0;
                speed_counter = 0;
            }
            else if (ending >= 6)
            {
                ending -= 11;
                if (buffer != NULL) destroy_bitmap(buffer);
                if (background != NULL) destroy_bitmap(background);
                //if (scenario != 0) destroy_bitmap(scenario);
                //if (bakg != 0) destroy_bitmap(bakg);
                scenario_width = 120;
                fadeout = 255;
                bakg = (BITMAP *) mydatafile[BG6].dat;
                background = create_bitmap(800, 480);
                scenario = (BITMAP *) mydatafile[ENDING6].dat;
                drawendchar = 6;
                buffer = create_bitmap(640, 480);
                clear_to_color(background, makecol(15,0,0));
                draw_sprite(background, bakg, 0, 0);
                draw_sprite(background, bakg, 640, 0);
                endtext = (BITMAP *) mydatafile[CREDITS6].dat;
                endtextx = 0;
                endtextw = 281;
                rest(1000);
                screenx = screeny = 0;
                speed_counter = 0;
            }
            else if (ending >= 5)
            {
                ending = 6666;
                if (buffer != NULL) destroy_bitmap(buffer);
                if (background != NULL) destroy_bitmap(background);
                //if (scenario != 0) destroy_bitmap(scenario);
                //if (bakg != 0) destroy_bitmap(bakg);
                fadeout = 255;
                background = create_bitmap(640, 480);
                clear_to_color(background, makecol(0,0,0));
                buffer = create_bitmap(640, 480);
                rest(1000);
                screenx = screeny = 0;
                speed_counter = 0;
            }
        }
    }
}
*/
