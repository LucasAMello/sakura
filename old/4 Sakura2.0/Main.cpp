#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include "data.h"
#include "game.h"
#include "menu.h"
#include "intro.h"

// lembrar de colocar if(key[KEY_ENTER] && fire_key == 0) na hora de chamar menu
// Menu escolhendo normal/hard automaticamente qnd vem de outro lugar
// algo errado com o speed_counter para fazer fade_out
//

int volatile speed_counter;
int volatile last_fps;
int volatile frame_counter;
int volatile cheats;
int volatile sound_volume_set;
int volatile music_volume_set;
DATAFILE * volatile mydatafile;
MIDI* stage_music;

Game *game;

void increment_speed_counter()
{
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);

void count_frames()
{
    last_fps = frame_counter;
    frame_counter = 0;
}
END_OF_FUNCTION(count_frames);

int init_game(int argc, COLOR_MAP *global_light_table)
{
    allegro_init();
    install_keyboard();
    install_timer();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    srand(time(0));

    LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));
    LOCK_VARIABLE(last_fps);
    LOCK_VARIABLE(frame_counter);
    LOCK_FUNCTION(count_frames);
    install_int_ex(count_frames, BPS_TO_TIMER(1));

    if (argc > 1)
    {
        install_mouse();
        if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0)
        {
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
            allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
            return 1;
        }
        set_palette(desktop_palette);
        int c = GFX_AUTODETECT;
        int w, h, bpp;
        w = SCREEN_W;
        h = SCREEN_H;
        bpp = bitmap_color_depth(screen);
        if (!gfx_mode_select_ex(&c, &w, &h, &bpp))
        {
            allegro_exit();
            return 1;
        }
        set_color_depth(bpp);
        if (set_gfx_mode(c, w, h, 0, 0) != 0)
        {
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
            allegro_message("Error setting graphics mode\n%s\n", allegro_error);
            return 1;
        }
        set_palette(desktop_palette);
    }
    else
    {
        set_color_depth(desktop_color_depth());
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
        set_display_switch_mode(SWITCH_BACKGROUND);
        set_palette(desktop_palette);
    }

    create_light_table(global_light_table, desktop_palette, 10, 10, 60, NULL);
    set_trans_blender(0, 0, 0, 0);
    return 0;
}

int main(int argc, char* argv[])
{
    COLOR_MAP global_light_table;
    COLOR_MAP global_trans_table;

    BITMAP* buffer;
    BITMAP* title;
    BITMAP* logo;

    DATAFILE *music_object;

    MIDI* title_music;
    MIDI* select_music;

    int gamestartmusic = 1;

    int menu;

    int sound_volume_set = 255;
    int music_volume_set = 1;
    unsigned script_timer = 0;

    if (init_game(argc, &global_light_table))
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error during init\n%s\n", allegro_error);
        exit(1);
    }

    game = new Game(buffer);

logodraw:
    logo = load_bitmap("Bin\\Data\\DoftSoft.bmp", NULL);
    clear_to_color(screen, makecol(0,0,0));
    draw_sprite(screen, logo, 241, 170);

    title = load_bitmap("Bin\\Data\\Title.bmp", NULL);
    music_object = load_datafile_object("Bin\\Data\\files.dat", "BGM1");

    create_trans_table(&global_trans_table, desktop_palette, 128, 128, 128, NULL);
    if (get_color_depth() == 8)
        color_map = &global_trans_table;
    else
        set_trans_blender(0, 0, 0, 128);

    buffer = create_bitmap(640, 480);
    clear_to_color(buffer, makecol(0,0,0));
    draw_sprite(buffer, logo, 241, 170);

    // Wait 2 seconds
    for (speed_counter = 0; speed_counter < 120; );

    // Fade out
    speed_counter = 0;
    do
    {
        draw_lit_sprite(screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    }
    while (speed_counter <= 20);

    mydatafile = load_datafile("Bin\\Data\\files.dat");
    if (mydatafile == NULL)
    {
        set_gfx_mode(GFX_TEXT,0,0,0,0);
        allegro_message("Could not load datafile!");
        exit(EXIT_FAILURE);
    }

    select_music = (MIDI *) mydatafile[BGM2].dat;

    // Draw main title
    draw_sprite(buffer, title, 0, 0);

    // Load and play music
    play_looped_midi((MIDI *) music_object->dat, 93, 237);
    midi_pos = 6;
    midi_seek(midi_pos);
    gamestartmusic = 1;

    // Fade in
    speed_counter = 0;
    do
    {
        draw_lit_sprite(screen, buffer, 0, 0, (int)((100 - speed_counter) * 2.55));
    }
    while ((100 - speed_counter) > 0);

    // Wait for Enter key
    while (!key[KEY_ENTER])
    {
        draw_sprite(buffer, title, 0, 0);
        draw_sprite(buffer, (BITMAP *)mydatafile[START01 + ((speed_counter/4) % 6)].dat, 220, 400);
        draw_sprite(screen, buffer, 0, 0);
    }

    play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    draw_sprite(buffer, title, 0, 0);

    // Fade out
    speed_counter = 0;
    do
    {
        draw_lit_sprite(screen, buffer, 0, 0, (int)(speed_counter * 12.75));
    }
    while (speed_counter <= 20);

    speed_counter = 0;

startofgame:

    if (gamestartmusic == 0)
    {
        play_looped_midi(title_music, 93, 237);
        midi_pos = 6;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();
    }
    gamestartmusic = 0;

    game->menu->fadein = true;
    speed_counter = 0;
    do
    {
        game->menu->draw_main_menu();
    }
    while (speed_counter <= 20);
    game->menu->fadein = false;

    menu = game->menu->main_menu();

    if (menu == 4)
    {
        delete game;
        if (title != NULL) destroy_bitmap(title);
        if (mydatafile != NULL) unload_datafile(mydatafile);
        if (music_object != NULL) unload_datafile_object (music_object);
        return 0;
    }
    menu = 0;


stage_select:

    while (key[KEY_ENTER] || key[KEY_F]);

    menu = 0;

    game->current_level = 0;

    play_looped_midi(select_music, 149, 277);
    midi_pos = 10;
    midi_seek(midi_pos);
    if (music_volume_set == 0) midi_pause();

    game->menu->fadein = true;
    speed_counter = 0;
    do
    {
        game->menu->draw_stage_select_menu();
    }
    while (speed_counter <= 20);
    game->menu->fadein = false;

    menu = game->menu->stage_select_menu();

    game->menu->fadeout = true;
    speed_counter = 0;
    do
    {
        game->menu->draw_stage_select_menu();
    }
    while (speed_counter <= 20);
    game->menu->fadeout = false;

    if (menu == 1)
    {
        menu = 0;
        game->menu->position = 105;
        game->menu->timer = 0;
        goto startofgame;
    }
    else game->current_level = menu;

    if (buffer != NULL) destroy_bitmap(buffer);

    /*lastagedoor = 0;
    if (gotolastage == 1)
    {
        current_level = 80;
        lastagedoor = 7;
        gotolastage = 0;
    }

    lastageblack = 0;*/

    game->setup_game();

    speed_counter = 0;
    do
    {
        game->draw();
    }
    while (speed_counter < 100);

    speed_counter = 1;
    do
    {
        /*while (speed_counter > 0)
        {
            game->input();
            script_timer++;
            if (script_timer % 4 == 1)
            {
                game->run_scripts();
                if (game->itsover == 1)
                {
                    if (game->hard_mode == 1) myendsp();
                    else myend();
                    goto logodraw;
                    break;
                }
            }
            for (ActorList::iterator it = game->actors.begin(); it != game->actors.end(); it++)
            {
                if (it->active && it->type == 44) it->timer++;
            }
            speed_counter--;
            if (game->player.y_position == (int)game->player.y_position) game->player.y_position += 0.01;
            if (game->stage_screen == 1)
            {
                game->stage_screen = 0;
                goto stage_select;
                break;
            }
        }*/
        while (speed_counter > 0)
        {
            script_timer++;
            game->input();
            game->run_scripts();
            if (game->itsover == 1)
            {
                if (game->hard_mode == 1) myendsp();
                else myend();
                goto logodraw;
                break;
            }
            speed_counter--;
            if (game->player.y_position == (int)game->player.y_position) game->player.y_position += 0.01;
            if (game->stage_screen == 1)
            {
                game->stage_screen = 0;
                game->menu->position = game->menu->position2 = 0;
                goto stage_select;
            }
        }
        game->draw();
        frame_counter++;
    }
    while (!game->time_to_quit);

    delete game;
    if (title != NULL) destroy_bitmap(title);
    if (mydatafile != NULL) unload_datafile(mydatafile);
    if (music_object != NULL) unload_datafile_object (music_object);

    return 0;
}
END_OF_MAIN();
