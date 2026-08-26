#include "game.h"

Game::Game(BITMAP *b)
{
    buffer = b;

    hard_mode = 2;
    music_volume_set = 1;
    sound_volume_set = 255;
    lastageportal[0] = lastageportal[1] = lastageportal[2] = lastageportal[3] = lastageportal[4] = lastageportal[5] = 0;

    menu = new Menu(&hard_mode, &player);
    map = new Map(&player, &walls);

    jump_key_state = 0;
    fire_key = 0;
    screenx = screeny = 0;
    number_of_actors = 0;
    current_level = 0;
    desired_weapon = 0;
    force_draw = 0;
    //i_like_pizza = 0;
    doorrecord = -1;
    bosslife = -1;
    key_enter_rest = 1;
    key_f_rest = 1;
    player_col = 0;

    buffer = NULL;
    scenario = NULL;
    bakg = NULL;
    background = NULL;
    foreground = NULL;
}

Game::~Game()
{
    delete menu;
    delete map;
    stop_midi();
    if (scenario != NULL) destroy_bitmap(scenario);
    if (buffer != NULL) destroy_bitmap(buffer);
    if (background != NULL) destroy_bitmap(background);
    if (bakg != NULL) destroy_bitmap(bakg);
    if (foreground != NULL) destroy_bitmap(foreground);
    //if (title_music != NULL) destroy_midi(title_music);
    //if (select_music != NULL) destroy_midi(select_music);
    //if (stage_music != NULL) destroy_midi(stage_music);
    //if (intro_music != NULL) destroy_midi(intro_music);
}

void Game::setup_game()
{
    if (buffer != NULL) destroy_bitmap(buffer);
    //if (background != NULL) destroy_bitmap(background);
    //if (scenario != NULL) destroy_bitmap(scenario);
    //if (bakg != 0) destroy_bitmap(bakg);
    doorrecord = -1;
    create_bubbles = 0;

    if (current_level == 10)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(3000, 580);
        scenario = create_bitmap( 9000, 580);
        buffer = create_bitmap( 640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, PORTA_1, 0);
        draw_sprite(background, bakg, 2000, 0);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM7].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 10, restart);
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        clear_keybuf();
        speed_counter = 1;
        play_looped_midi(stage_music, 13, 165);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();
        restart = 0;
        player.dead = false;
        player.hp = player.hpmax;
    }
    /*else if (current_level == 11)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(800, 1400);
        scenario = create_bitmap( 800, 2000);
        buffer = create_bitmap( 640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 0, 520);
        draw_sprite(background, bakg, 0, 1040);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 11, restart);
    }
    else if (current_level == 12)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(3000, 600);
        scenario = create_bitmap( 8400, 600);
        buffer = create_bitmap( 640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, 0, 80);
        draw_sprite(background, bakg, PORTA_1, 80);
        draw_sprite(background, bakg, 2000, 80);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 12, restart);
    }
    else if (current_level == 13)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(800, 1400);
        scenario = create_bitmap( 800, 1800);
        buffer = create_bitmap( 640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 0, 520);
        draw_sprite(background, bakg, 0, 1040);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 13, restart);
    }
    else if (current_level == 14)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(3000, 560);
        scenario = create_bitmap( 4000, 560);
        buffer = create_bitmap( 640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, PORTA_1, 0);
        draw_sprite(background, bakg, 2000, 20);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 14, restart);
    }
    else if (current_level == 20)
    {
        bakg = (BITMAP *) mydatafile[BG3].dat;
        background = create_bitmap(2000, 480);
        scenario = create_bitmap(2000, 480);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(56,72,96));
        draw_sprite(background, bakg, 0, 0);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM8].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 20, restart);
    }
    else if (current_level == 21)
    {
        //bakg = load_bitmap("bg3.bmp", NULL);
        //background = create_bitmap(4200, 560);
        scenario = create_bitmap(4200, 560);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        //clear_to_color(background, makecol(56,72,96));
        //draw_sprite(background, bakg, 0, 0);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 21, restart);
    }
    else if (current_level == 22)
    {
        scenario = create_bitmap(2400, 1400);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 22, restart);
    }
    else if (current_level == 23)
    {
        scenario = create_bitmap(6000, 720);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 23, restart);
    }
    else if (current_level == 30)
    {
        bakg = (BITMAP *) mydatafile[BG4].dat;
        background = create_bitmap(3000, 600);
        scenario = create_bitmap(PORTA_10, 600);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 60);
        draw_sprite(background, bakg, 608, 60);
        draw_sprite(background, bakg, 1216, 60);
        draw_sprite(background, bakg, 1824, 60);
        draw_sprite(background, bakg, 2432, 60);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM5].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 30, restart);
    }
    else if (current_level == 31)
    {
        bakg = (BITMAP *) mydatafile[BG4].dat;
        background = create_bitmap(2000, 1600);
        scenario = create_bitmap(2000, 1600);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 608, 0);
        draw_sprite(background, bakg, 1216, 0);
        draw_sprite(background, bakg, 0, 480);
        draw_sprite(background, bakg, 608, 480);
        draw_sprite(background, bakg, 1216, 480);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 31, restart);
    }
    else if (current_level == 32)
    {
        bakg = (BITMAP *) mydatafile[BG4].dat;
        background = create_bitmap(4000, 640);
        scenario = create_bitmap(6000, 640);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 608, 0);
        draw_sprite(background, bakg, 1216, 0);
        draw_sprite(background, bakg, 1824, 0);
        draw_sprite(background, bakg, 2432, 0);
        draw_sprite(background, bakg, 3240, 0);
        draw_sprite(background, bakg, 0, 480);
        draw_sprite(background, bakg, 608, 480);
        draw_sprite(background, bakg, 1216, 480);
        draw_sprite(background, bakg, 1824, 480);
        draw_sprite(background, bakg, 2432, 480);
        draw_sprite(background, bakg, 3240, 480);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 32, restart);
    }
    else if (current_level == 40)
    {
        bakg = (BITMAP *) mydatafile[BG5].dat;
        background = create_bitmap(3000, 800);
        scenario = create_bitmap(9000, 800);
        foreground = create_bitmap(9000, 800);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,161));
        clear_to_color(foreground, makecol(255,0,255));
        draw_sprite(background, bakg, -100, 20);
        draw_sprite(background, bakg, 300, 20);
        draw_sprite(background, bakg, 700, 20);
        draw_sprite(background, bakg, 1100, 20);
        draw_sprite(background, bakg, 1500, 20);
        draw_sprite(background, bakg, 1900, 20);
        draw_sprite(background, bakg, 0, 180);
        draw_sprite(background, bakg, 400, 180);
        draw_sprite(background, bakg, 800, 180);
        draw_sprite(background, bakg, 1200, 180);
        draw_sprite(background, bakg, 1600, 180);
        draw_sprite(background, bakg, 2000, 180);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM3].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 40, restart);
    }
    else if (current_level == 41)
    {
        bakg = (BITMAP *) mydatafile[BG5].dat;
        background = create_bitmap(3000, 800);
        scenario = create_bitmap(9000, 800);
        foreground = create_bitmap(9000, 800);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,161));
        clear_to_color(foreground, makecol(255,0,255));
        draw_sprite(background, bakg, 0, -40);
        draw_sprite(background, bakg, 400, -40);
        draw_sprite(background, bakg, 800, -40);
        draw_sprite(background, bakg, 1200, -40);
        draw_sprite(background, bakg, 1600, -40);
        draw_sprite(background, bakg, 2000, -40);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 41, restart);
    }
    else if (current_level == 42)
    {
        bakg = (BITMAP *) mydatafile[BG5].dat;
        background = create_bitmap(3000, 800);
        scenario = create_bitmap(PORTA_10, 800);
        foreground = create_bitmap(PORTA_10, 800);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,161));
        clear_to_color(foreground, makecol(255,0,255));
        draw_sprite(background, bakg, 0, 60);
        draw_sprite(background, bakg, 400, 60);
        draw_sprite(background, bakg, 800, 60);
        draw_sprite(background, bakg, 1200, 60);
        draw_sprite(background, bakg, 1600, 60);
        draw_sprite(background, bakg, 2000, 60);
        draw_sprite(background, bakg, 2400, 60);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 42, restart);
    }
    else if (current_level == 50)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(800, 1600);
        scenario = create_bitmap(800, 1600);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, -100, 0);
        draw_sprite(background, bakg, -100, 520);
        draw_sprite(background, bakg, -100, 1040);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM4].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 50, restart);
    }
    else if (current_level == 51)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(7200, 720);
        scenario = create_bitmap(7200, 720);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(48,16,31));
        draw_sprite(background, bakg, -600, 0);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 51, restart);
    }
    else if (current_level == 52)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(1200, 1600);
        scenario = create_bitmap(1200, 1600);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(48,16,31));
        draw_sprite(background, bakg, 0, -80);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 52, restart);
    }
    else if (current_level == 53)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(6000, 2400);
        scenario = create_bitmap(6000, 2400);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(48,16,31));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 53, restart);
    }
    else if (current_level == 60)
    {
        bakg = (BITMAP *) mydatafile[BG6].dat;
        background = create_bitmap(8000, 680);
        scenario = create_bitmap(8000, 680);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(111,200,239));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 640, 0);
        draw_sprite(background, bakg, 1280, 0);
        draw_sprite(background, bakg, 1920, 0);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM6].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 60, restart);
    }
    else if (current_level == 61)
    {
        bakg = (BITMAP *) mydatafile[BG6].dat;
        background = create_bitmap(8000, PORTA_1);
        scenario = create_bitmap(8000, PORTA_1);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(111,200,239));
        draw_sprite(background, bakg, 640, -20);
        draw_sprite(background, bakg, 1280, -20);
        draw_sprite(background, bakg, 1920, -20);
        draw_sprite(background, bakg, 2560, -20);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 61, restart);
    }
    else if (current_level == 62)
    {
        bakg = (BITMAP *) mydatafile[BG6].dat;
        background = create_bitmap(4000, 1200);
        scenario = create_bitmap(4000, 1200);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,16,63));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 62, restart);
    }
    else if (current_level == 70)
    {
        bakg = (BITMAP *) mydatafile[BG7].dat;
        background = create_bitmap(PORTA_10, 720);
        scenario = create_bitmap(PORTA_10, 720);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,0));
        draw_sprite(background, bakg, 0, 40);
        draw_sprite(background, bakg, 640, 40);
        draw_sprite(background, bakg, 1280, 40);
        draw_sprite(background, bakg, 1920, 40);
        draw_sprite(background, bakg, 2560, 40);
        draw_sprite(background, bakg, 3200, 40);
        draw_sprite(background, bakg, 3840, 40);
        draw_sprite(background, bakg, 4480, 40);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGM9].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 70, restart);
    }
    else if (current_level == 71)
    {
        bakg = (BITMAP *) mydatafile[BG7].dat;
        background = create_bitmap(PORTA_10, 800);
        scenario = create_bitmap(PORTA_10, 800);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,0));
        draw_sprite(background, bakg, 0, 70);
        draw_sprite(background, bakg, 640, 70);
        draw_sprite(background, bakg, 1280, 70);
        draw_sprite(background, bakg, 1920, 70);
        draw_sprite(background, bakg, 2560, 70);
        draw_sprite(background, bakg, 3200, 70);
        draw_sprite(background, bakg, 3840, 70);
        draw_sprite(background, bakg, 4480, 70);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 71, restart);
    }
    else if (current_level == 72)
    {
        bakg = (BITMAP *) mydatafile[BG7].dat;
        background = create_bitmap(15000, 800);
        scenario = create_bitmap(15000, 800);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,0));
        draw_sprite(background, bakg, 0, 70);
        draw_sprite(background, bakg, 640, 70);
        draw_sprite(background, bakg, 1280, 70);
        draw_sprite(background, bakg, 1920, 70);
        draw_sprite(background, bakg, 2560, 70);
        draw_sprite(background, bakg, 3200, 70);
        draw_sprite(background, bakg, 3840, 70);
        draw_sprite(background, bakg, 4480, 70);
        draw_sprite(background, bakg, 5120, 70);
        draw_sprite(background, bakg, 5760, 70);
        draw_sprite(background, bakg, 6400, 70);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 72, restart);
    }
    else if (current_level == 73)
    {
        bakg = (BITMAP *) mydatafile[BG7].dat;
        background = create_bitmap(3000, 1600);
        scenario = create_bitmap(3000, 1600);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,0));
        draw_sprite(background, bakg, 0, 100);
        draw_sprite(background, bakg, 640, 100);
        draw_sprite(background, bakg, 1280, 100);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 73, restart);
    }
    else if (current_level == 74)
    {
        bakg = (BITMAP *) mydatafile[BG6].dat;
        background = create_bitmap(4000, 1200);
        scenario = create_bitmap(4000, 1200);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,16,63));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 74, restart);
    }
    else if (current_level == 75)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(3000, 560);
        scenario = create_bitmap( 4000, 560);
        buffer = create_bitmap( 640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(47,128,255));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, PORTA_1, 0);
        draw_sprite(background, bakg, 2000, 20);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 75, restart);
    }
    else if (current_level == 76)
    {
        scenario = create_bitmap(6000, 720);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 76, restart);
    }
    else if (current_level == 77)
    {
        bakg = (BITMAP *) mydatafile[BG4].dat;
        background = create_bitmap(4000, 640);
        scenario = create_bitmap(6000, 640);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 608, 0);
        draw_sprite(background, bakg, 1216, 0);
        draw_sprite(background, bakg, 1824, 0);
        draw_sprite(background, bakg, 2432, 0);
        draw_sprite(background, bakg, 3240, 0);
        draw_sprite(background, bakg, 0, 480);
        draw_sprite(background, bakg, 608, 480);
        draw_sprite(background, bakg, 1216, 480);
        draw_sprite(background, bakg, 1824, 480);
        draw_sprite(background, bakg, 2432, 480);
        draw_sprite(background, bakg, 3240, 480);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 77, restart);
    }
    else if (current_level == 78)
    {
        bakg = (BITMAP *) mydatafile[BG5].dat;
        background = create_bitmap(3000, 800);
        scenario = create_bitmap(PORTA_10, 800);
        foreground = create_bitmap(PORTA_10, 800);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(0,0,161));
        clear_to_color(foreground, makecol(255,0,255));
        draw_sprite(background, bakg, 0, 60);
        draw_sprite(background, bakg, 400, 60);
        draw_sprite(background, bakg, 800, 60);
        draw_sprite(background, bakg, 1200, 60);
        draw_sprite(background, bakg, 1600, 60);
        draw_sprite(background, bakg, 2000, 60);
        draw_sprite(background, bakg, 2400, 60);
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 78, restart);
    }
    else if (current_level == 79)
    {
        bakg = (BITMAP *) mydatafile[BG1].dat;
        background = create_bitmap(6000, 2400);
        scenario = create_bitmap(6000, 2400);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(48,16,31));
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 79, restart);
    }
    else if (current_level == 80)
    {
        bakg = (BITMAP *) mydatafile[BG8].dat;
        background = create_bitmap(2500, 600);
        scenario = create_bitmap(2500, 600);
        buffer = create_bitmap(640, 480);
        clear_to_color(scenario, makecol(255,0,255));
        clear_to_color(background, makecol(20,15,60));
        draw_sprite(background, bakg, 865, 0);
        //draw_sprite(background, bakg, 640, 0);
        //draw_sprite(background, bakg, 1280, 0);
        //draw_sprite(background, bakg, 1920, 0);
        //if (stage_music != NULL) destroy_midi(stage_music);
        stage_music = (MIDI *) mydatafile[BGMA].dat;
        restart = 1;
        limpation = 0;
        dieanimation = 0;
        input_locked = 0;
        screen_locked = 0;
        bosslife = -1;
        bossfight = 0;
        map->create_level(this, 80, restart);
    }*/
}

void Game::die()
{
    bframe = PDIE1;
    input_locked = 1;
    screen_locked = 1;
    player.frame = NULO;
    player.imune = 0;
    dieanimation = 1;
    int x = (int)player.x_position;
    int y = (int)player.y_position;
    bolas[0][0] = x + 7;
    bolas[0][1] = y + 5;
    bolas[1][0] = x + 12;
    bolas[1][1] = y + 10;
    bolas[2][0] = x + 17;
    bolas[2][1] = y + 17;
    bolas[3][0] = x + 12;
    bolas[3][1] = y + 24;
    bolas[4][0] = x + 7;
    bolas[4][1] = y + 29;
    bolas[5][0] = x;
    bolas[5][1] = y + 34;
    bolas[6][0] = x - 7;
    bolas[6][1] = y + 29;
    bolas[7][0] = x - 12;
    bolas[7][1] = y + 24;
    bolas[8][0] = x - 17;
    bolas[8][1] = y + 17;
    bolas[9][0] = x - 12;
    bolas[9][1] = y + 10;
    bolas[10][0] = x - 7;
    bolas[10][1] = y + 5;
    bolas[11][0] = x;
    bolas[11][1] = y;
}

void Game::damage(int howmuch)
{
    if (howmuch < 0 || player.imune == 0)
    {
        if (hard_mode == 1 && howmuch > 0)
        {
            if (player.hp > 1) player.hp = 1;
            else
            {
                player.hp = 0;
                restart = 1;
                player.dead = true;
            }
        }
        else if (god_mode != 1) player.hp = player.hp - howmuch;
        if (howmuch > 0) player.imune = 40;
        if (player.hp > player.hpmax) player.hp = player.hpmax;
        else if (player.hp <= 0)
        {
            player.hp = 0;
            restart = 1;
            player.dead = true;
        }
    }
}

void Game::callevent(int event_number)
{
    if (event_number == 1)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (300 - (int)player.y_position >= 10) player.y_position += 10;
            else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 10) player.y_position = 300;
            else
            {
                player.y_position = 300;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 5;
                player.x_position += 5;
                event_organizer++;
            }
        }
        else if (event_organizer == 75)
        {
            player.x_speed = 0;
            int a = 10;
            ActorList::iterator it;
            for (it = actors.begin(); it != actors.end(); it++)
            {
                if (it->type == 2000)
                {
                    it->timer = a;
                    a -= 2;
                }
                if (it->type == 2001)
                {
                    it->timer = a;
                    a -= 2;
                }
            }
            event_organizer++;
        }
        else if (event_organizer < 75)
        {
            player.x_speed = 5;
            player.x_position += 5;
            event_organizer++;
        }
        else if (event_organizer > 75 && event_organizer < 105) event_organizer++;
        else if (event_organizer == 105)
        {
            create_actor(BOSS_WIND, 3180, -100, 0, 105);
            event_organizer = 200;
        }
        else if (event_organizer >= 106 && event_organizer < 136)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 136)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
        }
    }
    else if (event_number == 13)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (300 - (int)player.y_position >= 10) player.y_position += 10;
            else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 10) player.y_position = 300;
            else
            {
                player.y_position = 300;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 0;
                event_organizer++;
            }
        }
        else if (event_organizer == 1)
        {
            if (player.cards[0] == 1)
            {
                input_locked = 1;
                finishing = 1;
            }
            else
            {
                input_locked = 0;
            }
            event_organizer = 0;
            call_event = 0;
        }
    }
    else if (event_number == 2)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (460 - (int)player.y_position >= 10) player.y_position += 10;
            else if (460 - (int)player.y_position > 0 && 460 - (int)player.y_position < 10) player.y_position = 460;
            else
            {
                player.y_position = 460;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 0;
                event_organizer++;
            }
        }
        else if (event_organizer == 1)
        {
            if (player.cards[1] == 1)
            {
                input_locked = 1;
                finishing = 1;
            }
            else
            {
                input_locked = 0;
            }
            event_organizer = 0;
            call_event = 0;
        }
    }
    else if (event_number == 3)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (460 - (int)player.y_position >= 10) player.y_position += 10;
            else if (460 - (int)player.y_position > 0 && 460 - (int)player.y_position < 10) player.y_position = 460;
            else
            {
                player.y_speed = 0;
                player.timer = 0;
                player.y_position = 460;
                player.on_ground = true;
                player.x_speed = 5;
                player.x_position += 5;
                event_organizer++;
            }
        }
        else if (event_organizer == 45)
        {
            player.x_speed = 0;
        }
        else if (event_organizer < 45)
        {
            player.x_speed = 5;
            player.x_position += 5;
            event_organizer++;
        }
        else if (event_organizer >= 106 && event_organizer < 136)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 136)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
        }
    }
    else if (event_number == 4)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (400 - (int)player.y_position >= 10) player.y_position += 10;
            else if (400 - (int)player.y_position > 0 && 400 - (int)player.y_position < 10) player.y_position = 400;
            else
            {
                player.y_position = 400;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 0;
                event_organizer++;
            }
        }
        else if (event_organizer == 1)
        {
            if (player.cards[2] == 1)
            {
                input_locked = 1;
                finishing = 1;
            }
            else
            {
                input_locked = 0;
            }
            event_organizer = 0;
            call_event = 0;
        }
    }
    else if (event_number == 5)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (400 - (int)player.y_position >= 10) player.y_position += 10;
            else if (400 - (int)player.y_position > 0 && 400 - (int)player.y_position < 10) player.y_position = 400;
            else
            {
                player.y_speed = 0;
                player.timer = 0;
                player.y_position = 400;
                player.on_ground = true;
                player.x_speed = 5;
                player.x_position += 5;
                event_organizer++;
            }
        }
        else if (event_organizer == 40)
        {
            player.x_speed = 0;
            event_organizer++;
        }
        else if (event_organizer < 40)
        {
            player.x_speed = 5;
            player.x_position += 5;
            event_organizer++;
        }
        else if (event_organizer > 40 && event_organizer < 57) event_organizer++;
        else if (event_organizer == 57)
        {
            create_actor(BIG_THUNDER, 5750, 160, 0, 0);
            event_organizer++;
        }
        else if (event_organizer > 57 && event_organizer < 60) event_organizer++;
        else if (event_organizer == 60)
        {
            flash_screen = 1;
            event_organizer++;
        }
        else if (event_organizer == 61)
        {
            flash_screen = 2;
            event_organizer++;
            create_actor(BOSS_THUNDER, 5720, 411, 0, 0);
        }
        else if (event_organizer == 62)
        {
            flash_screen = 1;
            event_organizer++;
        }
        else if (event_organizer == 63)
        {
            flash_screen = 0;
            event_organizer++;
        }
        else if (event_organizer > 63 && event_organizer < 68) event_organizer++;
        else if (event_organizer >= 68 && event_organizer < 98)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 98)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
        }
    }
    else if (event_number == 6)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (560 - (int)player.y_position >= 10) player.y_position += 10;
            else if (560 - (int)player.y_position > 0 && 560 - (int)player.y_position < 10) player.y_position = 560;
            else
            {
                player.y_position = 560;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 0;
                event_organizer++;
            }
        }
        else if (event_organizer == 1)
        {
            if (player.cards[3] == 1)
            {
                input_locked = 1;
                finishing = 1;
            }
            else
            {
                input_locked = 0;
            }
            event_organizer = 0;
            call_event = 0;
        }
    }
    else if (event_number == 7)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (560 - (int)player.y_position >= 10) player.y_position += 10;
            else if (560 - (int)player.y_position > 0 && 560 - (int)player.y_position < 10) player.y_position = 560;
            else
            {
                player.y_speed = 0;
                player.timer = 0;
                player.y_position = 560;
                player.on_ground = true;
                player.x_speed = 5;
                player.x_position += 5;
                event_organizer++;
            }
        }
        else if (event_organizer == 34)
        {
            player.x_speed = 0;
            event_organizer++;
        }
        else if (event_organizer < 34)
        {
            player.x_speed = 5;
            player.x_position += 5;
            event_organizer++;
        }
        else if (event_organizer > 34 && event_organizer < 44) event_organizer++;
        else if (event_organizer >= 51 && event_organizer < 81)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 81)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            input_locked = 0;
        }
    }
    else if (event_number == 8)
    {
        map->set_dvalues(8);
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (1340 - (int)player.y_position >= 10) player.y_position += 10;
            else if (1340 - (int)player.y_position > 0 && 1340 - (int)player.y_position < 10) player.y_position = 1340;
            else
            {
                player.y_position = 1340;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 0;
                event_organizer++;
            }
        }
        else
        {
            if (player.cards[4] == 1)
            {
                input_locked = 1;
                finishing = 1;
            }
            else
            {
                input_locked = 0;
            }
            event_organizer = 0;
            call_event = 0;
        }
    }
    else if (event_number == 9)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            event_organizer++;
            if (player.on_ground == false && player.timer > 0 && player.in_water == 0)
            {
                if (player.timer > 0 && player.timer < 11) player.y_speed+=0.1;
                else if (player.timer > 10 && player.timer < 21) player.y_speed+=0.06;
                else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
                else if (player.timer == 39) player.y_speed = (int)player.y_speed;
                if (player.y_speed >= 0) player.timer = -1;
                else
                {
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                }
            }
            if (jump_key_state == 0 && player.on_ground == false && player.timer > 0)
            {
                player.timer = -1;
                player.y_speed = 0.4;
            }
            if (player.on_ground == false && player.timer < 0 && player.in_water == 0)
            {
                if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                else if (player.timer < -20) player.y_speed+=0.1;
                if (player.y_speed > 2) player.y_speed = 2;
                if (player.y_speed <= 0) player.timer = 0;
                else
                {
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                }
            }
        }
        else if (event_organizer == 33)
        {
            player.x_speed = 0;
            event_organizer++;
        }
        else if (event_organizer < 33)
        {
            if ((int)player.x_position > 5460)
            {
                player.direction = 1;
                if ((int)player.x_position - 5460 > 4) player.x_position -= 4;
                else player.x_position = 5460;
            }
            else if ((int)player.x_position < 5460)
            {
                player.direction = 0;
                if (5460 - player.x_position > 4) player.x_position += 4;
                else player.x_position = 5460;
            }
            else
            {
                player.direction = 0;
                player.x_speed = 0;
            }
            if (player.on_ground == false && player.timer > 0 && player.in_water == 0)
            {
                if (player.timer > 0 && player.timer < 11) player.y_speed+=0.1;
                else if (player.timer > 10 && player.timer < 21) player.y_speed+=0.06;
                else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
                else if (player.timer == 39) player.y_speed = (int)player.y_speed;
                if (player.y_speed >= 0) player.timer = -1;
                else
                {
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                }
            }
            if (jump_key_state == 0 && player.on_ground == false && player.timer > 0)
            {
                player.timer = -1;
                player.y_speed = 0.4;
            }
            if (player.on_ground == false && player.timer < 0 && player.in_water == 0)
            {
                if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                else if (player.timer < -20) player.y_speed+=0.1;
                if (player.y_speed > 2) player.y_speed = 2;
                if (player.y_speed <= 0) player.timer = 0;
                else
                {
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                    player.move_player(scenario, map, false, true);
                }
            }
            event_organizer++;
        }
        else if (event_organizer > 33 && event_organizer < 54)
        {
            screen_locked = 1;
            if (screenx > -5280)
            {
                if (screenx - 15 > -5280) screenx -= 10;
                else screenx = -5280;
            }
            else
            {
                map->set_dvalues(9);
                screen_locked = 0;
            }
            event_organizer++;
        }
        else if (event_organizer >= 61 && event_organizer < 91)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 91)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            input_locked = 0;
        }
    }
    else if (event_number == 10)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (1020 - (int)player.y_position >= 10) player.y_position += 10;
            else if (1020 - (int)player.y_position > 0 && 1020 - (int)player.y_position < 10) player.y_position = 1020;
            else
            {
                player.y_position = 1020;
                player.y_speed = 0;
                player.timer = 0;
                player.on_ground = true;
                player.x_speed = 0;
                event_organizer++;
            }
        }
        else if (event_organizer == 1)
        {
            if (player.cards[5] == 1)
            {
                input_locked = 1;
                finishing = 1;
            }
            else
            {
                input_locked = 0;
            }
            event_organizer = 0;
            call_event = 0;
        }
    }
    else if (event_number == 11)
    {
        if (event_organizer == 0)
        {
            input_locked = 1;
            if (1020 - (int)player.y_position >= 10) player.y_position += 10;
            else if (1020 - (int)player.y_position > 0 && 1020 - (int)player.y_position < 10) player.y_position = 1020;
            else
            {
                player.y_speed = 0;
                player.timer = 0;
                player.y_position = 1020;
                player.on_ground = true;
                player.x_speed = 5;
                player.x_position += 5;
                event_organizer++;
            }
        }
        else if (event_organizer == 34)
        {
            player.x_speed = 0;
            event_organizer++;
            create_actor(BOSS_ICE, 3980, 1120, 1, 0);
        }
        else if (event_organizer < 34)
        {
            player.x_speed = 5;
            player.x_position += 5;
            event_organizer++;
        }
        else if (event_organizer >= 51 && event_organizer < 81)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 81)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            input_locked = 0;
        }
    }
    else if (event_number == 12)
    {
        map->set_dvalues(12);
        call_event = 0;
        input_locked = 0;
    }
    else if (event_number == 14)
    {
        if (event_organizer < 40)
        {
            input_locked = 1;
            player.x_speed = 0;
            event_organizer++;
        }
        else if (event_organizer == 40)
        {
            input_locked = 1;
            player.x_speed = 0;
            create_actor(BOSS_ICE, 3980, 1120, 1, 0);
            event_organizer++;
        }
        else if (event_organizer >= 51 && event_organizer < 81)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 81)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
            input_locked = 0;
        }
    }
    else if (event_number == 15)
    {
        if (event_organizer >= 0 && event_organizer < 35) event_organizer++;
        else if (event_organizer == 35)
        {
            create_actor(BOSS_WIND, 3180, -100, 0, 105);
            event_organizer = 200;
        }
        else if (event_organizer >= 106 && event_organizer < 136)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 136)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
        }
    }
    else if (event_number == 16)
    {
        if (event_organizer == 0)
        {
            event_organizer = 45;
        }
        else if (event_organizer >= 106 && event_organizer < 136)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 136)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
        }
    }
    else if (event_number == 17)
    {
        if (event_organizer == 0)
        {
            player.x_speed = 0;
            event_organizer = 41;
        }
        else if (event_organizer > 40 && event_organizer < 57) event_organizer++;
        else if (event_organizer == 57)
        {
            create_actor(BIG_THUNDER, 5750, 160, 0, 0);
            event_organizer++;
        }
        else if (event_organizer > 57 && event_organizer < 60) event_organizer++;
        else if (event_organizer == 60)
        {
            flash_screen = 1;
            event_organizer++;
        }
        else if (event_organizer == 61)
        {
            flash_screen = 2;
            event_organizer++;
            create_actor(BOSS_THUNDER, 5720, 411, 0, 0);
        }
        else if (event_organizer == 62)
        {
            flash_screen = 1;
            event_organizer++;
        }
        else if (event_organizer == 63)
        {
            flash_screen = 0;
            event_organizer++;
        }
        else if (event_organizer > 63 && event_organizer < 68) event_organizer++;
        else if (event_organizer >= 68 && event_organizer < 98)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 98)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
        }
    }
    else if (event_number == 18)
    {
        if (event_organizer == 0)
        {
            player.x_speed = 0;
            event_organizer = 35;
        }
        else if (event_organizer > 34 && event_organizer < 44) event_organizer++;
        else if (event_organizer >= 51 && event_organizer < 81)
        {
            if (bosslife == -1) bosslife = 0;

            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 81)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
            input_locked = 0;
        }
    }
    else if (event_number == 19)
    {
        if (event_organizer == 0)
        {
            event_organizer = 54;
        }
        else if (event_organizer >= 61 && event_organizer < 91)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 91)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
            input_locked = 0;
        }
    }
    else if (event_number == 20)
    {
        if (event_organizer == 0)
        {
            lastageblack-=4;
            if (lastageblack <= 0)
            {
                lastageblack = 0;
                event_organizer = 3;
            }
        }
        else if (event_organizer >= 61 && event_organizer < 91)
        {
            if (bosslife == -1) bosslife = 0;
            bosslife++;
            play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            event_organizer++;
        }
        else if (event_organizer == 91)
        {
            event_organizer = 0;
            call_event = 0;
            bossfight = 1;
            lastageboss = 1;
            input_locked = 0;
        }
    }

    else call_event = 0;
}

void Game::input()
{
    if (dieanimation == 1)
    {
        if (player.timer > -PORTA_1) player.timer = -PORTA_1;
        else player.timer--;
        if ((int)player.timer % 20 == 0) play_sample((SAMPLE *)mydatafile[DIE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        if (bframe == PDIE5) bframe = PDIE1;
        else if ((int)player.timer % 5 == 0) bframe++;
        if (player.timer > -1100)
        {
            bolas[0][0] += 2.5;
            bolas[0][1] -= 3.5;
            bolas[1][0] += 3.5;
            bolas[1][1] -= 2.5;
            bolas[2][0] += 4;
            bolas[3][0] += 3.5;
            bolas[3][1] += 2.5;
            bolas[4][0] += 2.5;
            bolas[4][1] += 3.5;
            bolas[5][1] += 4;
            bolas[6][0] -= 2.5;
            bolas[6][1] += 3.5;
            bolas[7][0] -= 3.5;
            bolas[7][1] += 2.5;
            bolas[8][0] -= 4;
            bolas[9][0] -= 3.5;
            bolas[9][1] -= 2.5;
            bolas[10][0] -= 2.5;
            bolas[10][1] -= 3.5;
            bolas[11][1] -= 4;
        }
    }
    if (starting > 0) starting++;
    else if (starting2 > 0) starting2++;
    else if (finishing > 0) finishing++;
    if (input_locked == 1)
    {
        player.player_colision();
        return;
    }

    if ( key[KEY_P])
    {
        stop_midi();
        //midi_pos += 10;
        //midi_seek(midi_pos);
    }

    if (!key[KEY_F]) key_f_rest = 0;
    if (key[player.key_jump] && key_f_rest == 0)
    {
        if (jump_key_state == 0) jump_key_state = 1;
        else if (jump_key_state == 1) jump_key_state = 2;
    }
    else jump_key_state = 0;

    if (key[KEY_O])
    {
        if (fps_rest == 0)
        {
            if (show_fps == 0) show_fps = 1;
            else show_fps = 0;
        }
        fps_rest = 1;
    }
    else fps_rest = 0;

    if (key[player.key_fire] && player.shots < 4) fire_key++;
    else if (fire_key >= 1) fire_key++;
    else fire_key = 0;

    if (fire_key == 0)
    {
        if (key[player.key_weapon1])
        {
            if (weaponlock == 0)
            {
                player.current_weapon++;
                if (player.current_weapon == 8) player.current_weapon = 1;
                if (player.current_weapon != 1)
                {
                    for (int x = player.current_weapon; x <= 8; x++)
                    {
                        if (x == 8)
                        {
                            player.current_weapon = 1;
                            break;
                        }
                        else if (player.cards[x-2] == 1)
                        {
                            player.current_weapon = x;
                            break;
                        }
                    }
                }
            }
            weaponlock++;
        }
        else if (key[player.key_weapon2])
        {
            if (weaponlock == 0)
            {
                player.current_weapon--;
                if (player.current_weapon == 0) player.current_weapon = 7;
                if (player.current_weapon != 1)
                {
                    for (int x = player.current_weapon; x >= 0; x--)
                    {
                        if (x == 0)
                        {
                            player.current_weapon = 1;
                            break;
                        }
                        else if (player.cards[x-2] == 1)
                        {
                            player.current_weapon = x;
                            break;
                        }
                    }
                }
            }
            weaponlock++;
        }
    }

    if (!key[player.key_weapon1] && !key[player.key_weapon2]) weaponlock = 0;

    if (key[KEY_K] && cheats == 1)
    {
        player.hp = 1;
        damage(20);
    }
    else if (key[KEY_L] && cheats == 1) player.hp = player.hpmax;
    else if (key[KEY_J] && cheats == 1)
    {
        gotolastage = 1;
        stage_screen = 1;
    }
    else if (key[KEY_M] && cheats == 1)
    {
        for (int x = 0; x < 52; x++) player.cards[x] = 1;
        player.score = 52;
    }
    else if (key[KEY_G] && cheats == 1)
    {
        god_mode = 1;
        hard_mode = 0;
    }
    //else if (key[KEY_H] && cheats == 1) { god_mode = 0; hard_mode = 1; }
    else if (key[KEY_N] && cheats == 1)
    {
        god_mode = 0;
    }
    else if (key[KEY_V] && cheats == 1)
    {
        player.vidas = 9;
    }
    else if (key[KEY_B] && cheats == 1)
    {
        god_mode = 0;
        cheats = 0;
    }
    else if (key[KEY_PLUS_PAD] && cheats == 1 && midi_pos > 10)
    {
        desired_music++;
        if (desired_music > BGMB) desired_music = BGM1;
        stage_music = (MIDI *) mydatafile[desired_music].dat;
        if (desired_music == BGM1) play_looped_midi(stage_music, 93, 237);
        if (desired_music == BGM2) play_looped_midi(stage_music, 149, 277);
        if (desired_music == BGM3) play_looped_midi(stage_music, 185, 357);
        if (desired_music == BGM4) play_looped_midi(stage_music, 45, 193);
        if (desired_music == BGM5) play_looped_midi(stage_music, 77, 277);
        if (desired_music == BGM6) play_looped_midi(stage_music, 27, 155);
        if (desired_music == BGM7) play_looped_midi(stage_music, 13, 165);
        if (desired_music == BGM8) play_looped_midi(stage_music, 13, 177);
        if (desired_music == BGM9) play_looped_midi(stage_music, 110, 278);
        if (desired_music == BGMA) play_looped_midi(stage_music, 37, 389);
        if (desired_music == BGMB) play_midi(stage_music, 1);
        if (music_volume_set == 0) midi_pause();
    }
    else if (key[KEY_MINUS_PAD] && cheats == 1 && midi_pos > 10)
    {
        desired_music--;
        if (desired_music < BGM1) desired_music = BGMB;
        stage_music = (MIDI *) mydatafile[desired_music].dat;
        if (desired_music == BGM1) play_looped_midi(stage_music, 93, 237);
        if (desired_music == BGM2) play_looped_midi(stage_music, 149, 277);
        if (desired_music == BGM3) play_looped_midi(stage_music, 185, 357);
        if (desired_music == BGM4) play_looped_midi(stage_music, 45, 193);
        if (desired_music == BGM5) play_looped_midi(stage_music, 77, 277);
        if (desired_music == BGM6) play_looped_midi(stage_music, 27, 155);
        if (desired_music == BGM7) play_looped_midi(stage_music, 13, 165);
        if (desired_music == BGM8) play_looped_midi(stage_music, 13, 177);
        if (desired_music == BGM9) play_looped_midi(stage_music, 110, 278);
        if (desired_music == BGMA) play_looped_midi(stage_music, 37, 389);
        if (desired_music == BGMB) play_midi(stage_music, 1);
        if (music_volume_set == 0) midi_pause();
    }

    if (key[KEY_ESC])
    {
        draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
        textout_centre_ex(screen, font, "Quit game? Y/N", 320, 236, makecol(0,0,0), -1);
        while (!key[KEY_Y] && !key[KEY_N]);
        if (key[KEY_Y]) time_to_quit = true;
        else if (key[KEY_N]) time_to_quit = false;
        speed_counter = 1;
    }

    if (key[player.key_menu] && key_enter_rest == 0)
    {
        float x = player.x_position;
        float y = player.y_position;
        player.x_position = 0;
        player.y_position = 0;
        int c = menu->game_menu();
        if (c == 2)
        {
            stage_screen = 1;
            return;
        }
        player.x_position = x;
        player.y_position = y;
    }
    if (!key[player.key_menu]) key_enter_rest = 0;
    if (key[player.key_quit]) timetoquit = 1;

    if (fire_key == 0)
    {
        if (key[KEY_1]) player.current_weapon = 1;
        else if (key[KEY_2] && player.cards[0] == 1) player.current_weapon = 2;
        else if (key[KEY_3] && player.cards[1] == 1) player.current_weapon = 3;
        else if (key[KEY_4] && player.cards[2] == 1) player.current_weapon = 4;
        else if (key[KEY_5] && player.cards[3] == 1) player.current_weapon = 5;
        else if (key[KEY_6] && player.cards[4] == 1) player.current_weapon = 6;
        else if (key[KEY_7] && player.cards[5] == 1) player.current_weapon = 7;
    }

    if (player.current_weapon == 1)
    {
        if (fire_key == 1)
        {
            player.shots++;
            if (player.direction == 0) create_actor(YELLOW_SHOT, (int)player.x_position + 40, (int)player.y_position + 35, 0, 0);
            else create_actor(YELLOW_SHOT, (int)player.x_position - 5, (int)player.y_position + 35, 1, 0);
        }
        if ((fire_key >= 10 && !key[player.key_fire]) || (fire_key >= 25 && player.shots == 0)) fire_key = 0;
    }
    else if (player.current_weapon == 2)
    {
        if (fire_key == 1)
        {
            if (player.direction == 0) create_actor(WIND_SHOT, (int)player.x_position + 25, (int)player.y_position + 10, 0, 0);
            else create_actor(WIND_SHOT, (int)player.x_position - 35, (int)player.y_position + 10, 1, 0);
        }
        if (fire_key >= 50) fire_key = 0;
    }
    else if (player.current_weapon == 3)
    {
        if (fire_key == 1)
        {
            if (player.direction == 0) create_actor(SHADOW_SHOT, (int)player.x_position - 50, (int)player.y_position, 0, 0);
            else create_actor(SHADOW_SHOT, (int)player.x_position - 21, (int)player.y_position, 1, 0);
        }
    }
    else if (player.current_weapon == 4)
    {
        if (fire_key == 1)
        {
            player.shots++;
            if (player.direction == 0) create_actor(THUNDER_SHOT, (int)player.x_position + 40, (int)player.y_position + 35, 0, 0);
            else create_actor(THUNDER_SHOT, (int)player.x_position - 21, (int)player.y_position + 35, 1, 0);
        }
        if ((fire_key >= 35 && !key[player.key_fire]) || (fire_key >= 50 && player.shots == 0)) fire_key = 0;
    }
    else if (player.current_weapon == 5)
    {
        if (fire_key == 1)
        {
            if (player.direction == 0) create_actor(WATER_SHOT, (int)player.x_position + 40, (int)player.y_position + 20, 0, 0);
            else create_actor(WATER_SHOT, (int)player.x_position - 21, (int)player.y_position + 20, 1, 0);
        }
        if (fire_key >= 40) fire_key = 0;
    }
    else if (player.current_weapon == 6)
    {
        if (fire_key == 1)
        {
            if (player.direction == 0) create_actor(FIRE_SHOT, (int)player.x_position + 40, (int)player.y_position + 28, 0, 0);
            else create_actor(FIRE_SHOT, (int)player.x_position - 21, (int)player.y_position + 28, 1, 0);
        }
        if (fire_key >= 70) fire_key = 0;
    }
    else if (player.current_weapon == 7)
    {
        if (fire_key == 1)
        {
            if (player.direction == 0) create_actor(ICE_SHOT, (int)player.x_position + 40, (int)player.y_position + 30, 0, 0);
            else create_actor(ICE_SHOT, (int)player.x_position - 21, (int)player.y_position + 30, 1, 0);
        }
        if (fire_key >= 50) fire_key = 0;
    }

    if ((key[player.key_right]) && !(key[player.key_left]))
    {
        if (player.direction == 1) player.direction = 0;
        if (player.x_speed < 0) player.x_speed = 0;
        else if (player.x_speed >= 1) player.x_speed += 1;
        else player.x_speed += 0.2;
    }

    else if ((key[player.key_left]) && !(key[player.key_right]))
    {
        if (player.direction == 0) player.direction = 1;
        if (player.x_speed > 0) player.x_speed = 0;
        else if (player.x_speed <= -1) player.x_speed += -1;
        else player.x_speed += -0.2;
    }

    else if (!key[player.key_right] && !key[player.key_left]) player.x_speed = 0;
    else if (key[player.key_right] && key[player.key_left]) player.x_speed = 0;

    if (player.x_speed > 4) player.x_speed = 4;
    else if (player.x_speed < -4) player.x_speed = -4;
    player.move_player(scenario, map, true, false);

    if (player.on_ground == false && player.timer > 0 && player.in_water == 0)
    {
        if (player.timer > 0 && player.timer < 11) player.y_speed+=0.1;
        else if (player.timer > 10 && player.timer < 21) player.y_speed+=0.06;
        else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
        else if (player.timer == 39) player.y_speed = (int)player.y_speed;
        if (player.y_speed >= 0) player.timer = -1;
        else  player.move_player(scenario, map, 0, 1);
    }
    else if (player.on_ground == false && player.timer > 0 && player.in_water == 1)
    {
        if (player.timer > 0 && player.timer < 3) player.y_speed+=0.1;
        else if (player.timer > 2 && player.timer < 21) player.y_speed+=0.06;
        else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
        else if (player.timer == 39) player.y_speed = (int)player.y_speed;
        if (player.y_speed >= 0) player.timer = -1;
        else  player.move_player(scenario, map, 0, 1);
    }

    if (jump_key_state != 0 && force_draw == 0 && player.on_ground == true)
    {
        player.y_speed = -2.0;
        player.move_player(scenario, map, 0, 1);
    }

    if (jump_key_state == 0 && player.on_ground == false && player.timer > 0)
    {
        player.timer = -1;
        player.y_speed = 0.4;
    }

    if (player.on_ground == false && player.timer < 0 && player.in_water == 0)
    {
        if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
        else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
        else if (player.timer < -20) player.y_speed+=0.1;
        if (player.y_speed > 2) player.y_speed = 2;
        if (player.y_speed <= 0) player.timer = 0;
        else player.move_player(scenario, map, 0, 1);
    }
    else if (player.on_ground == false && player.timer < 0 && player.in_water == 1)
    {
        if (player.timer < 0) player.y_speed+=0.04;
        if (player.y_speed > 1.2) player.y_speed = 1.2;
        if (player.y_speed <= 0) player.timer = 0;
        else player.move_player(scenario, map, 0, 1);
    }

    player.player_colision();
    if (player.in_water == 1)
    {
        create_bubbles++;
        if (create_bubbles == 160)
        {
            if (player.direction == 0) create_actor(AIR_BUBBLE, (int)player.x_position + 30, (int)player.y_position + 15, player.direction, 0);
            else create_actor(AIR_BUBBLE, (int)player.x_position + 4, (int)player.y_position + 15, player.direction, 0);
            create_bubbles = 0;
        }
    }
    else create_bubbles = 0;
    if (music_volume_set == 0) midi_pause();
}

void Game::run_scripts()
{
    if (player.imune > 0)
    {
        player.imune--;
        if (player.imune == 29 || player.imune == 27 || player.imune == 25) player.frame = PLAYERD;
        else if (player.frame != NULO && player.frame != PLAYERD) player.frame = NULO;
        else player.frame = PLAYER_MOVING01;
    }

    if (looper == 0 || (looper > 8 && looper < 47))
    {
        if (player.x_speed != 0)
        {
            player.move++;
            if (player.frame == PLAYER_MOVING05 || player.frame == PLAYER_MOVING04 || player.frame == PLAYER_MOVING03 || player.frame == PLAYER_MOVING02 || player.frame == PLAYER_MOVING01  || player.frame == PLAYER_MOVING12  || player.frame == PLAYER_MOVING22  || player.frame == PLAYER_MOVING32  || player.frame == PLAYER_MOVING42  || player.frame == PLAYER_MOVING52)
            {
                if (player.move == 0)
                {
                    if (player.frame != PLAYER_MOVING42) player.frame = PLAYER_MOVING01;
                    else player.frame = PLAYER_MOVING12;
                }
                else if (player.move == 4) player.frame = PLAYER_MOVING02;
                else if (player.move == 8) player.frame = PLAYER_MOVING03;
                else if (player.move == 12) player.frame = PLAYER_MOVING02;
                else if (player.move == 16) player.frame = PLAYER_MOVING01;
                else if (player.move == 20)
                {
                    if (player.frame != PLAYER_MOVING12) player.frame = PLAYER_MOVING04;
                    else player.frame = PLAYER_MOVING42;
                }
                else if (player.move == 24)
                {
                    if (player.frame != PLAYER_MOVING42) player.frame = PLAYER_MOVING05;
                    else player.frame = PLAYER_MOVING52;
                }
                else if (player.move == 28)
                {
                    if (player.frame != PLAYER_MOVING52) player.frame = PLAYER_MOVING04;
                    else player.frame = PLAYER_MOVING42;
                }
                if (player.on_ground == false) player.frame = PLAYER_MOVING03;
            }
            if (player.move == 28) player.move = -4;
        }
        else if (player.frame != PLAYERD && player.frame != NULO) player.frame = PLAYER_MOVING01;

        if (fire_key > 0)
        {
            if (player.frame == PLAYER_MOVING01)
            {
                player.frame = PLAYER_MOVING12;
                player.shooting = 5;
            }
            else if (player.frame == PLAYER_MOVING02)
            {
                player.frame = PLAYER_MOVING22;
                player.shooting = 5;
            }
            else if (player.frame == PLAYER_MOVING03)
            {
                player.frame = PLAYER_MOVING32;
                player.shooting = 5;
            }
            else if (player.frame == PLAYER_MOVING04)
            {
                player.frame = PLAYER_MOVING42;
                player.shooting = 5;
            }
            else if (player.frame == PLAYER_MOVING05)
            {
                player.frame = PLAYER_MOVING52;
                player.shooting = 5;
            }
        }
        else if (player.frame == PLAYER_MOVING01 && player.shooting > 0)
        {
            player.frame = PLAYER_MOVING12;
            player.shooting--;
        }
        else player.shooting = 0;
    }

    ActorList::iterator it;
    for (it = actors.begin(); it != actors.end(); it++)
    {
        it->actor_update(&player);
    }

    for (it = actors.begin(); it != actors.end(); it++)
    {
checkif:
        if (it->active == 0)
        {
            it = actors.erase(it);
            goto checkif;
        }
    }

    if (movingscreen == 1)
    {
        if (looper > 0)
        {
            if (looper > 8 && looper < 46)
            {
                if (looper == 9)
                {
                    player.shooting = 0;
                    fire_key = 0;
                    if (player.frame == PLAYER_MOVING12) player.frame = PLAYER_MOVING01;
                    if (player.frame == PLAYER_MOVING22) player.frame = PLAYER_MOVING02;
                    if (player.frame == PLAYER_MOVING32) player.frame = PLAYER_MOVING03;
                    if (player.frame == PLAYER_MOVING42) player.frame = PLAYER_MOVING04;
                    if (player.frame == PLAYER_MOVING52) player.frame = PLAYER_MOVING05;
                }
                player.x_position += 2;
                screenx -= 16;
                if (doorrecord == 5 && looper > 37)  screenx +=4;
                if (doorrecord == 11 && looper > 34)  screenx +=2;
            }
            if (looper == 46)
            {
                player.x_position += 2;
                if (doorrecord != 5 && doorrecord != 11) screenx -= 14;
            }
            if (looper == 56)
            {
                looper = 0;
                stopall = 0;
                movingscreen = 0;
                input_locked = 0;
                screen_locked = 0;
                if (call_event > 0) callevent(call_event);
            }
            else looper++;
        }
    }
    else if (call_event > 0) callevent(call_event);

    if (restart == 1)
    {
        die();
        restart = 0;
    }
}

void Game::draw()
{
    if (screen_locked == 0)
    {
        if (player.x_position > map->limitleft + 299 && player.x_position < map->limitright - 340)
        {
            screenx = 300 - (int)player.x_position;
        }
        else if (player.x_position < map->limitleft + 300) screenx = map->limitleft * -1;
        else screenx = (map->limitright - 640) * -1;
        if (player.y_position > map->limitup + 239 && player.y_position < map->limitdown - 240)
        {
            screeny = 240 - (int)player.y_position;
        }
        else if (player.y_position < map->limitup + 240) screeny = map->limitup * -1;
        else screeny = (map->limitdown - 480) * -1;
    }

    if (lastageblack == 0)
    {
        if (map->type == 1 || map->type == 3)
        {
            if (map->type == 3) masked_blit( background, buffer, (screenx / 5) * -1, screeny * -1, 0, 0, 640, 480);
            else if (current_level == 80) masked_blit( background, buffer, (screenx) * -1, (screeny / 5) * -1, 0, 0, 640, 480);
            else masked_blit( background, buffer, (screenx / 5) * -1, (screeny / 5) * -1, 0, 0, 640, 480);
        }
        masked_blit( scenario, buffer, screenx * -1, screeny * -1, 0, 0, 640, 480);
    }
    else
    {
        if (lastageblack == 255)
        {
            BITMAP* temp = create_bitmap(640, 480);
            clear_to_color(temp, makecol(0,0,0));
            draw_sprite( buffer, temp, 0, 0);
            destroy_bitmap(temp);
        }
        else
        {
            BITMAP* temp = create_bitmap(640, 480);
            BITMAP* temp2 = create_bitmap(640, 480);
            clear_to_color(temp, bitmap_mask_color(background));
            clear_to_color(temp2, bitmap_mask_color(scenario));
            masked_blit( background, temp, screenx * -1, (screeny / 5) * -1, 0, 0, 640, 480);
            masked_blit( scenario, temp2, screenx * -1, screeny * -1, 0, 0, 640, 480);
            set_trans_blender(0,0,0,0);
            draw_lit_sprite( buffer, temp, 0, 0, lastageblack);
            draw_lit_sprite( buffer, temp2, 0, 0, lastageblack);
            destroy_bitmap(temp);
            destroy_bitmap(temp2);
        }
    }

    ActorList::iterator it;
    for (it = actors.begin(); it != actors.end(); it++)
    {
        if (it->active)
        {
            if (it->type == 35)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 36)
            {
                if (it->direction == 0)
                {
                    if (it->timer % 4 == 0)
                    {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                    else if (it->timer % 4 == 1)
                    {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                    else if (it->timer % 4 == 2)
                    {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                    else if (it->timer % 4 == 3)
                    {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)it->x_position + screenx + 19 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                }
                else
                {
                    if (it->timer % 4 == 0)
                    {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 6);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                    else if (it->timer % 4 == 1)
                    {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 6);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                    else if (it->timer % 4 == 2)
                    {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 6);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                    else if (it->timer % 4 == 3)
                    {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 6);
                        for (int x = 0; x <= it->extra_int; x++)
                        {
                            if (x == it->extra_int) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)it->x_position + screenx + 14 + (16 * x), (int)it->y_position + screeny + 6);
                        }
                    }
                }
            }
            else if (it->type == 46)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 47)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
        }
    }

    for (it = actors.begin(); it != actors.end(); it++)
    {
        if (it->active)
        {
            if (it->type == PORTA_1)
            {
                if (it->timer == doorrecord)
                {
                    if (stopall == 1 && looper > 0 && looper < 9) masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, looper * 10, (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 100 - (looper * 10));
                    else if (stopall == 1 && looper > 47 && looper < 56) masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, 80 - ((looper - 47) * 10), (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 20 + ((looper - 47) * 10));
                    else if (stopall == 1 && looper == 56)
                    {
                        masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, 80 - ((looper - 48) * 10), (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 20 + ((looper - 48) * 10));
                        call_event = it->timer;
                        if (call_event == 0) call_event = 13;
                        it->timer = -1;
                        it->height = 100;
                    }
                    else if (stopall == 1 && starting == 0) masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, 80, (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 20);
                    else draw_sprite( buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else draw_sprite( buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 999)
            {
                if (it->timer == doorrecord)
                {
                    if (stopall == 1 && looper > 0 && looper < 9) masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, looper * 13, (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 140 - (looper * 13));
                    else if (stopall == 1 && looper > 47 && looper < 56) masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, 104 - ((looper - 47) * 13), (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 36 + ((looper - 47) * 13));
                    else if (stopall == 1 && looper == 56)
                    {
                        masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, 104 - ((looper - 48) * 13), (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 36 + ((looper - 47) * 13));
                        call_event = it->timer;
                        it->timer = -1;
                        it->height = 140;
                    }
                    else if (stopall == 1) masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, 104, (int)it->x_position + screenx, (int)it->y_position + screeny, 30, 36);
                    else draw_sprite( buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else draw_sprite( buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 403)
            {
                set_trans_blender(0,0,0,100);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[LUZ].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 65)
            {
                if (it->action_state == 0)
                {
                    draw_sprite(buffer, (BITMAP*)mydatafile[CARDHOLDER].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->timer % 40 == 0) it->frame = CARD01;
                    else if (it->timer % 40 == 2) it->frame = CARD02;
                    else if (it->timer % 40 == 4) it->frame = CARD03;
                    else if (it->timer % 40 == 6) it->frame = CARD04;
                    else if (it->timer % 40 == 8) it->frame = CARD05;
                    else if (it->timer % 40 == 10) it->frame = CARD04;
                    else if (it->timer % 40 == 12) it->frame = CARD03;
                    else if (it->timer % 40 == 14) it->frame = CARD02;
                    else if (it->timer % 40 == 16) it->frame = CARD01;
                    if (it->timer % 40 < 10) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 9, (int)it->y_position + screeny + 12);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 9, (int)it->y_position + screeny + 12);
                }
                else
                {
                    if (it->timer % 2 == 0) draw_sprite(buffer, (BITMAP*)mydatafile[CARDHOLDER2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 69)
            {
                if (it->action_state == 0)
                {
                    if (it->timer % 40 == 0) it->frame = CARD01;
                    else if (it->timer % 40 == 2) it->frame = CARD02;
                    else if (it->timer % 40 == 4) it->frame = CARD03;
                    else if (it->timer % 40 == 6) it->frame = CARD04;
                    else if (it->timer % 40 == 8) it->frame = CARD05;
                    else if (it->timer % 40 == 10) it->frame = CARD04;
                    else if (it->timer % 40 == 12) it->frame = CARD03;
                    else if (it->timer % 40 == 14) it->frame = CARD02;
                    else if (it->timer % 40 == 16) it->frame = CARD01;
                    if (it->timer % 40 < 10) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else if (it->action_state == 3)
                {
                    set_trans_blender(0,0,0,it->strength);
                    draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 23)
            {
                if (it->action_state % 3 == 0) draw_sprite(buffer, (BITMAP*)mydatafile[ORANGEH01].dat, (int)it->x_position + screenx + 4, (int)it->y_position + screeny);
                else if (it->action_state % 3 == 1) draw_sprite(buffer, (BITMAP*)mydatafile[ORANGEH02].dat, (int)it->x_position + screenx + 4, (int)it->y_position + screeny);
                else draw_sprite(buffer, (BITMAP*)mydatafile[ORANGEH03].dat, (int)it->x_position + screenx + 4, (int)it->y_position + screeny);
                if (it->timer >= 9) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 10);
                else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 10);
            }
            else if (it->type == 15)
            {
                set_trans_blender(0, 0, 0, it->extra_int);
                if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else
                {
                    BITMAP* temp = create_bitmap(it->width, it->height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                    draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (it->type == 67)
            {
                if (it->action_state == 0)
                {
                    if (player.cards[it->extra_int] == 0) draw_sprite(buffer, (BITMAP*)mydatafile[CARD01].dat, (int)it->x_position + screenx + 9, (int)it->y_position + screeny + 6);
                    set_trans_blender(0, 0, 0, (int)it->x_speed);
                    draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else
                {
                    if (player.cards[it->extra_int] == 0) draw_sprite(buffer, (BITMAP*)mydatafile[CARD01].dat, (int)it->x_position + screenx + 9, (int)it->y_position + screeny + 6);
                    set_trans_blender(0, 0, 0, (int)it->x_speed);
                    draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    set_trans_blender(0, 0, 0, (int)it->y_speed);
                    draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->direction].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 17)
            {
                set_trans_blender(0, 0, 0, it->action_state);
                if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else
                {
                    BITMAP* temp = create_bitmap(it->width, it->height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                    draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (it->type == 62)
            {
                set_trans_blender(0, 0, 0, it->action_state);
                if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else
                {
                    BITMAP* temp = create_bitmap(it->width, it->height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                    draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (it->type == 400)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                rotate_sprite(buffer, (BITMAP*)mydatafile[WINDMILL1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
            }
            else if (it->type == LIFE)
            {
                if (player.frame == PLAYERD) draw_sprite(buffer, (BITMAP*)mydatafile[VIDAZ].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (player.frame == NULO) rest(1);
                else if (it->timer % 2 == 0)
                {
                    if (player.current_weapon == 1) draw_sprite(buffer, (BITMAP*)mydatafile[VIDA].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 2)draw_sprite(buffer, (BITMAP*)mydatafile[VIDAA].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 3)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAB].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 4)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAC].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 5)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAD].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 6)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAE].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 7)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAF].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else
                {
                    if (player.current_weapon == 1) draw_sprite(buffer, (BITMAP*)mydatafile[VIDA1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 2)draw_sprite(buffer, (BITMAP*)mydatafile[VIDAA1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 3)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAB1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 4)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAC1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 5)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAD1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 6)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAE1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else if (player.current_weapon == 7)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAF1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 18)
            {
                masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx - 8, (int)it->extra_int + screeny, 11, 150);
                masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 11, 0, (int)it->x_position + screenx, (int)it->y_position, 48, 22);
                masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 59, 0, (int)it->x_position + screenx + 44, (int)it->extra_int + screeny, 11, 150);
            }
            else if (it->type == 19)
            {
                if (it->direction == 0)
                    draw_sprite(buffer, (BITMAP*)mydatafile[WALLTURRET].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->direction == 1)
                    draw_sprite(buffer, (BITMAP*)mydatafile[WALLTURRET2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WALLTURRET2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 22)
            {
                if (it->timer < 2) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 8, 11);
                else if (it->timer < 4) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 16, 11);
                else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 24)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->direction == 1) rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 5, (int)it->y_position + screeny - 5, itofix(64));
                else if (it->direction == 2) draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 5, (int)it->y_position + screeny - 5, itofix(192));
            }
            else if (it->type == 25)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->direction == 1) rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 3, (int)it->y_position + screeny + 2, itofix(64));
                else if (it->direction == 2) draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 3, (int)it->y_position + screeny + 2, itofix(192));
            }
            else if (it->type == 26)
            {
                if (it->frame == ZOCK01) it->frame++;
                else if (it->frame == ZOCK02) it->frame++;
                else if (it->frame == ZOCK03) it->frame++;
                else if (it->frame == ZOCK04) it->frame = ZOCK01;
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 5, (int)it->y_position + screeny - 8);
            }
            else if (it->type == 28)
            {
                it->timer++;
                if (it->timer == 1)
                {
                    actor_colision(&(*it));
                    char col = 'p';
                    if (((int)it->x_position > (int)player.x_position) && ((int)it->x_position - (int)player.x_position >= 40)) col = 'n';
                    else if (((int)it->x_position <= (int)player.x_position) && ((int)player.x_position - (int)it->x_position >= it->width)) col = 'n';
                    if (((int)it->y_position > (int)player.y_position) && ((int)it->y_position - (int)player.y_position >= 80)) col = 'n';
                    else if (((int)it->y_position <= (int)player.y_position) && ((int)player.y_position - (int)it->y_position >= it->height)) col = 'n';
                    if (col != 'n')
                    {
                        it->extra_int = (int)player.y_position;
                        it->animation_state = 1;
                        if (input_locked == 0) damage(it->strength);
                    }
                    if (it->extra_int != 0) it->height = (int)(it->extra_int - it->y_position);
                }
                else if (it->timer == 5) it->frame = THUNDER_SHOT02;
                else if (it->timer == 9) it->frame = THUNDER_SHOT03;
                else if (it->timer == 13)
                {
                    it->active = 0;
                    it--;
                }
            }
            else if (it->type == 76)
            {
                it->timer++;
                if (it->timer == 1)
                {
                    actor_colision(&(*it));
                    char col = 'p';
                    if (((int)it->x_position > (int)player.x_position) && ((int)it->x_position - (int)player.x_position >= 40)) col = 'n';
                    else if (((int)it->x_position <= (int)player.x_position) && ((int)player.x_position - (int)it->x_position >= it->width)) col = 'n';
                    if (((int)it->y_position > (int)player.y_position) && ((int)it->y_position - (int)player.y_position >= 80)) col = 'n';
                    else if (it->extra_int == 0 && ((int)it->y_position <= (int)player.y_position) && ((int)player.y_position - (int)it->y_position >= it->height)) col = 'n';
                    else if (it->extra_int > 0 && ((int)it->y_position <= (int)player.y_position) && ((int)player.y_position - (int)it->y_position >= it->extra_int - (int)it->y_position)) col = 'n';
                    if (col != 'n')
                    {
                        it->extra_int = (int)player.y_position;
                        it->animation_state = 1;
                        if (input_locked == 0) damage(it->strength);
                    }
                    if (it->extra_int != 0) it->height = (int)(it->extra_int - it->y_position);
                }
                else if (it->timer == 5) it->frame = THUNDER_SHOT02;
                else if (it->timer == 9) it->frame = THUNDER_SHOT03;
                else if (it->timer == 13)
                {
                    it->active = 0;
                    it--;
                }
            }
            else if (it->type == 29)
            {
                if (it->action_state == 1)
                {
                    if (it->direction == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, it->width, it->height);
                    else
                    {
                        BITMAP* temp = create_bitmap(37, 34);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, it->width, it->height);
                        destroy_bitmap(temp);
                    }
                }
            }
            else if (it->type == 30)
            {
                if (player.x_position > it->x_position) it->direction = 0;
                else it->direction = 1;
                if (it->action_state == 1)
                {
                    if (it->direction == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, it->width, it->height);
                    else
                    {
                        BITMAP* temp = create_bitmap(36, 51);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, it->width, it->height);
                        destroy_bitmap(temp);
                    }
                }
                else if (it->frame == SEAHORSE3)
                {
                    rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
                    it->rotate_factor += 24;
                }
                else if (it->action_state == 2 || it->action_state == 3)
                {
                    if (player.x_position > it->x_position) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 72)
            {
                if (player.x_position > it->x_position) it->direction = 0;
                else it->direction = 1;
                if (it->action_state == 1)
                {
                    if (it->direction == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, it->width, it->height);
                    else
                    {
                        BITMAP* temp = create_bitmap(36, 51);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, it->width, it->height);
                        destroy_bitmap(temp);
                    }
                }
                else if (it->frame == SEAHORSE3)
                {
                    rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
                    it->rotate_factor += 24;
                }
                else if (it->action_state == 2 || it->action_state == 3)
                {
                    if (player.x_position > it->x_position) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 73)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 74)
            {
                draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 33)
            {
                if (it->action_state == 0)
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else if (it->action_state == 1)
                {
                    if (it->direction == 0) rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
                    else rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT4].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
                }
                else if (it->action_state == 2)
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT3].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[EWULOSTRAPT3].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else if (it->action_state == 3)
                {
                    if (it->direction == 0) rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
                    else rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT4].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
                }
                else if (it->action_state == 4)
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }

            }
            else if (it->type == 38)
            {
                if (it->direction == 1) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 40)
            {
                if (it->direction == 1) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 42)
            {
                draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny - 3);
            }
            else if (it->type == 44)
            {
                if (it->timer % 45 == 0) it->frame = LAVA1;
                else if (it->timer % 45 == 15) it->frame = LAVA2;
                else if (it->timer % 45 == 30) it->frame = LAVA3;
                //it->timer++;
                for (int xyz = 0; it->width - xyz > 0; xyz += 60)
                {
                    if (it->width - xyz < 60) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx + xyz, (int)it->y_position + screeny, it->width - xyz, 10);
                    else masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx + xyz, (int)it->y_position + screeny, 60, 10);
                }
            }
            else if (it->type == 53)
            {
                masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 20, 28);
                for (int xyz = 0; xyz < it->width - 40; xyz += 20)
                {
                    masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 20, 0, (int)it->x_position + screenx + 20 + xyz, (int)it->y_position + screeny, 20, 28);
                }
                masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 40, 0, (int)it->x_position + screenx + it->width - 20, (int)it->y_position + screeny, 20, 28);
            }
            else if (it->type == 45)
            {
                if (it->action_state != 2)
                {
                    if (it->timer % 4 == 0) it->frame = EWUL_SQUID01;
                    else if (it->timer % 4 == 1) it->frame = EWUL_SQUID02;
                    else if (it->timer % 4 == 2) it->frame = EWUL_SQUID03;
                    else if (it->timer % 4 == 3) it->frame = EWUL_SQUID04;
                }
                if (it->action_state == 1)
                {
                    if (it->y_position + 59 > it->extra_int)
                    {
                        masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 25, it->extra_int - (int)it->y_position);
                    }
                    else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else if (it->action_state == 3)
                {
                    if (it->y_position + 59 > it->extra_int)
                    {
                        BITMAP* temp = create_bitmap(25, 59);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_v_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 25, it->extra_int - (int)it->y_position);
                        destroy_bitmap(temp);
                    }
                    else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else if (it->action_state == 2)
                {
                    if (it->timer <= 2) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 56)
            {
                if (it->action_state == 0)
                {
                    set_trans_blender(0, 0, 0, it->extra_int);
                    if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else
                    {
                        BITMAP* temp = create_bitmap(it->width, it->height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        destroy_bitmap(temp);
                    }
                }
                else
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 79)
            {
                if (it->action_state == 0)
                {
                    set_trans_blender(0, 0, 0, it->extra_int);
                    if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else
                    {
                        BITMAP* temp = create_bitmap(it->width, it->height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        destroy_bitmap(temp);
                    }
                }
                else
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == 59)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                if (player.x_position + 20 > it->x_position)
                {
                    if (player.x_position + 20 > it->x_position + 100) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame + 1].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else masked_blit((BITMAP*)mydatafile[it->frame + 1].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, (int)player.x_position + 20 - (int)it->x_position, 100);
                }
            }
            else if (it->type == 60)
            {
                if (it->action_state == 4) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->action_state == 1)
                {
                    draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->animation_state < 24) it->animation_state++;
                    if (it->animation_state <= 6) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES1].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                    else if (it->animation_state <= 12) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES2].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                    else if (it->animation_state <= 18) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES3].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                    else if (it->animation_state > 18) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES4].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                }
                else if (it->action_state == 2)
                {
                    draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    it->animation_state--;
                    if (it->animation_state == 0) it->action_state = 0;
                    else if (it->animation_state <= 6) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES1].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                    else if (it->animation_state <= 12) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES2].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                    else if (it->animation_state <= 18) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES3].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                    else if (it->animation_state <= 24) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES4].dat, (int)it->x_position + screenx + 26, (int)it->y_position + screeny + 17);
                }
                else if (it->action_state == 3)
                {
                    it->animation_state++;
                    if (it->animation_state == 9) it->animation_state = 1;
                    if (it->animation_state <= 4) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame + 1].dat, (int)it->x_position + screenx - 7, (int)it->y_position + screeny);
                    else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else if (it->action_state == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == BOSS_ICE)
            {
                if ((it->frame == ICYSHADOW01 || it->frame == ICYSHADOW02 || it->frame == ICYSHADOW03 || it->frame == ICYSHADOW04) && it->action_state != 3 && it->action_state != 4 && it->action_state != 5)
                {
                    set_trans_blender(0, 0, 0, 50);
                    if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else
                    {
                        BITMAP* temp = create_bitmap(it->width, it->height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        destroy_bitmap(temp);
                    }
                    if ((it->action_state == 1 || it->action_state == 6|| it->action_state == 10 || it->action_state == 14) && it->y_position < 1100)
                    {
                        BITMAP* temp = create_bitmap(it->width, it->height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[ICYUP01].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYUP01].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 65, 1100 - (int)it->y_position);
                        destroy_bitmap(temp);
                    }
                    if ((it->action_state == 7|| it->action_state == 11 || it->action_state == 15) && it->y_position < 1100)
                    {
                        masked_blit((BITMAP*)mydatafile[ICYUP01].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 65, 1100 - (int)it->y_position);
                    }
                    if ((it->action_state == 2 || it->action_state == 8 || it->action_state == 12 || it->action_state == 16) && it->y_position < 820)
                    {
                        BITMAP* temp = create_bitmap(it->width, it->height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[ICYUP01].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYUP01].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 820 - (int)it->y_position, (int)it->x_position + screenx, (int)it->y_position + screeny + 820 - (int)it->y_position, 65, 154 - (820 - (int)it->y_position));
                        destroy_bitmap(temp);
                    }
                    if ((it->action_state == 9 || it->action_state == 13 || it->action_state == 17) && it->y_position < 820)
                    {
                        masked_blit((BITMAP*)mydatafile[ICYUP01].dat, buffer, 0, 820 - (int)it->y_position, (int)it->x_position + screenx, (int)it->y_position + screeny + 820 - (int)it->y_position, 65, 154 - (820 - (int)it->y_position));
                    }
                }
                else if (it->action_state == 3)
                {
                    set_trans_blender(0, 0, 0, 50);
                    draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->x_position > 3726 && it->x_position < 3880)
                    {
                        masked_blit((BITMAP*)mydatafile[ICYSIDE01].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 3880 - (int)it->x_position, 1100 - (int)it->y_position);
                    }
                    else if (it->y_position < 1100 && it->x_position < 3880)
                    {
                        masked_blit((BITMAP*)mydatafile[ICYSIDE01].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 154, 1100 - (int)it->y_position);
                    }
                }
                else if (it->action_state == 4)
                {
                    set_trans_blender(0, 0, 0, 50);
                    if (it->frame == ICYSHADOW02)
                    {
                        set_trans_blender(0, 0, 0, 50);
                        if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        else
                        {
                            BITMAP* temp = create_bitmap(it->width, it->height);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                            draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                            destroy_bitmap(temp);
                        }
                        if (it->x_position > 3226)
                        {
                            masked_blit((BITMAP*)mydatafile[ICYSIDE01].dat, buffer, 3380 - (int)it->x_position, 0, (int)it->x_position + screenx + 3380 - (int)it->x_position, (int)it->y_position + screeny, 154 - 3380 + (int)it->x_position, 65);
                        }
                    }
                    else if (it->frame == ICYSIDE02 && it->x_position < 3380)
                    {
                        BITMAP* temp = create_bitmap(154, 65);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        masked_blit((BITMAP*)mydatafile[ICYSHADOW02].dat, temp, 0, 0, 0, 0, 3380 - (int)it->x_position, 65);
                        draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        destroy_bitmap(temp);
                        masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 3380 - (int)it->x_position, 0, (int)it->x_position + screenx + 3380 - (int)it->x_position, (int)it->y_position + screeny, (int)it->x_position - 3240, 106);
                    }
                    else if (it->frame == ICYSIDE03)
                    {
                        if (it->x_position < 3380)
                        {
                            BITMAP* temp = create_bitmap(154, 65);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            masked_blit((BITMAP*)mydatafile[ICYSHADOW02].dat, temp, 0, 0, 0, 0, 3380 - (int)it->x_position, 65);
                            draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                            destroy_bitmap(temp);
                            masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 3380 - (int)it->x_position, 0, (int)it->x_position + screenx + 3380 - (int)it->x_position, (int)it->y_position + screeny, (int)it->x_position - 3240, 120);
                        }
                        else draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    }
                    else if (it->frame == ICYSIDE04)
                    {
                        draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    }
                    else if (it->frame == ICYUP01)
                    {
                        if (it->y_position > 946)
                        {
                            BITMAP* temp = create_bitmap(65, 154);
                            BITMAP* temp2 = create_bitmap(65, 154);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSHADOW04].dat, 0, 0);
                            draw_sprite_v_flip(temp2, temp, 0, 0);
                            draw_trans_sprite(buffer, temp2, (int)it->x_position + screenx, (int)it->y_position + screeny);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                            draw_sprite_v_flip(temp2, temp, 0, 0);
                            masked_blit(temp2, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 65, 1100 - (int)it->y_position);
                            destroy_bitmap(temp);
                            destroy_bitmap(temp2);
                        }
                        else
                        {
                            BITMAP* temp = create_bitmap(65, 154);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                            draw_sprite_v_flip(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                            destroy_bitmap(temp);
                        }
                    }
                }
                else if (it->action_state == 5)
                {
                    set_trans_blender(0, 0, 0, 50);
                    if (it->frame == ICYSHADOW02)
                    {
                        set_trans_blender(0, 0, 0, 50);
                        if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        else
                        {
                            BITMAP* temp = create_bitmap(it->width, it->height);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                            draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                            destroy_bitmap(temp);
                        }
                        if (it->x_position < 3880)
                        {
                            BITMAP* temp = create_bitmap(it->width, it->height);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSIDE01].dat, 0, 0);
                            masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 3880 - (int)it->x_position, 65);
                            destroy_bitmap(temp);
                        }
                    }
                    else if (it->frame == ICYSIDE02 && it->x_position > 3726)
                    {
                        BITMAP* temp = create_bitmap(154, 65);
                        BITMAP* temp2 = create_bitmap(154, 65);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSHADOW02].dat, -14, 0);
                        masked_blit(temp, temp2, 3880 - (int)it->x_position, 0, 3880 - (int)it->x_position, 0, 154 - (3880 - (int)it->x_position), 65);
                        draw_trans_sprite(buffer, temp2, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        destroy_bitmap(temp2);
                        destroy_bitmap(temp);
                        BITMAP* temp3 = create_bitmap(140, 106);
                        clear_to_color(temp3, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                        draw_sprite_h_flip(temp3, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                        masked_blit(temp3, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 3880 - (int)it->x_position, 106);
                        destroy_bitmap(temp3);
                    }
                    else if (it->frame == ICYSIDE03)
                    {
                        if (it->x_position > 3726)
                        {
                            BITMAP* temp = create_bitmap(154, 65);
                            BITMAP* temp2 = create_bitmap(154, 65);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSHADOW02].dat, -15, 0);
                            masked_blit(temp, temp2, 3880 - (int)it->x_position, 0, 3880 - (int)it->x_position, 0, 154 - (3880 - (int)it->x_position), 65);
                            draw_trans_sprite(buffer, temp2, (int)it->x_position + screenx, (int)it->y_position + screeny - 6);
                            destroy_bitmap(temp2);
                            destroy_bitmap(temp);
                            BITMAP* temp3 = create_bitmap(138, 120);
                            clear_to_color(temp3, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_h_flip(temp3, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                            masked_blit(temp3, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 3880 - (int)it->x_position, 120);
                            destroy_bitmap(temp3);
                        }
                        else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    }
                    else if (it->frame == ICYSIDE04)
                    {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    }
                    else if (it->frame == ICYUP01)
                    {
                        if (it->y_position > 946)
                        {
                            BITMAP* temp = create_bitmap(65, 154);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_v_flip(temp, (BITMAP*)mydatafile[ICYSHADOW04].dat, 0, 0);
                            draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                            draw_sprite_v_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                            masked_blit(temp, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 65, 1100 - (int)it->y_position);
                            destroy_bitmap(temp);
                        }
                        else
                        {
                            draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                        }
                    }
                }
                else
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
            }
            else if (it->type == LAST_BOSS)
            {
                if (player.x_position + 20 < it->x_position + 35 && it->direction == 0) it->direction = 1;
                if (player.x_position + 20 > it->x_position + 35 && it->direction == 1) it->direction = 0;
                if (it->direction == 0)
                {
                    if (it->action_state <= 1)
                    {
                        set_trans_blender(0, 0, 0, 0);
                        draw_lit_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, it->extra_int);
                    }
                    else
                    {
                        set_trans_blender(0, 0, 0, it->extra_int);
                        draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    }
                }
                else
                {
                    BITMAP* temp = create_bitmap(80, 109);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                    if (it->action_state <= 1)
                    {
                        set_trans_blender(0, 0, 0, 0);
                        draw_lit_sprite(buffer, temp, (int)it->x_position + screenx - 10, (int)it->y_position + screeny, it->extra_int);
                    }
                    else
                    {
                        set_trans_blender(0, 0, 0, it->extra_int);
                        draw_trans_sprite(buffer, temp, (int)it->x_position + screenx - 10, (int)it->y_position + screeny);
                    }
                    destroy_bitmap(temp);
                }
            }
            else if (it->type == 100) continue;
            else if (it->type == 404) continue;
            else if (it->type == 35) continue;
            else if (it->type == 36) continue;
            else if (it->type == 46) continue;
            else if (it->type == 47) continue;
            else if (it->type == 66) continue;
            else if (it->type == 1) continue;
            else if (it->type == 2) continue;
            else if (it->type == 3) continue;
            else if (it->type == 4) continue;
            else if (it->type == 5) continue;
            else if (it->type == 6) continue;
            else if (it->type == 7) continue;
            else if (it->type == 70) continue;
            else if (it->type == 75) continue;
            else if (it->type == 77) continue;
            else if (it->type == 78) continue;
            else if (it->type == 305) continue;
            else if (it->type == 100) continue;
            else if (it->type == 101) continue;
            else if (it->type == 102) continue;
            else if (it->type == 104) continue;
            else if (it->type == 57) continue;
            else if (it->type == 58) continue;
            else if (it->type == 1666) continue;
            else if (it->type == 2004) continue;
            //else if (it->type == BOSS_WATER) continue;
            else if (it->rotate_factor == 0)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else rotate_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, itofix(it->rotate_factor));
        }
    }

    player.x_position = (int)player.x_position;
    if (starting > 0)
    {
        if (starting > 15 && starting < 24 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
        else if (starting > 23 && starting < 31 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
        else if (starting > 30 && starting < 39 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
        else if (starting > 38 && starting < 47 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
        else if (starting > 46 && starting < 87)
        {
            if (starting > 46 && starting < 53) player.frame = PLAYER_MOVING02;
            else if (starting > 52 && starting < 59) player.frame = PLAYER_MOVING03;
            else if (starting > 58 && starting < 65) player.frame = PLAYER_MOVING02;
            else if (starting > 64 && starting < 71) player.frame = PLAYER_MOVING01;
            else if (starting > 70 && starting < 77) player.frame = PLAYER_MOVING04;
            else if (starting > 76 && starting < 83) player.frame = PLAYER_MOVING05;
            else if (starting > 82 && starting < 89) player.frame = PLAYER_MOVING04;
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            masked_blit((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, buffer, 40 - (starting - 46), 0, (int)player.x_position + screenx, (int)player.y_position + screeny, (starting - 46) * 2, 80);
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (starting > 86 && starting < 95)
        {
            player.frame = PLAYER_MOVING01;
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 94 && starting < 103)
        {
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 102 && starting < 111)
        {
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 110 && starting < 119)
        {
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 118 && starting < 130)
        {
            if (map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        if (starting > 5 && starting < 128 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[READY].dat, 240, 200);
        //starting++;
        if (starting == 130)
        {
            input_locked = 0;
            stopall = 0;
            starting = 0;
            if (lastagedoor == 1)
            {
                input_locked = 1;
                call_event = 14;
            }
            else if (lastagedoor == 2)
            {
                input_locked = 1;
                call_event = 15;
            }
            else if (lastagedoor == 3)
            {
                input_locked = 1;
                call_event = 16;
            }
            else if (lastagedoor == 4)
            {
                input_locked = 1;
                call_event = 17;
            }
            else if (lastagedoor == 5)
            {
                input_locked = 1;
                call_event = 18;
            }
            else if (lastagedoor == 6)
            {
                input_locked = 1;
                call_event = 19;
            }
            else if (lastagedoor == 7)
            {
                input_locked = 1;
                call_event = 20;
                lastageblack = 255;
            }
        }
    }
    else if (starting2 > 0)
    {
        if (starting2 > 15 && starting2 < 24 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
        else if (starting2 > 23 && starting2 < 31 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
        else if (starting2 > 30 && starting2 < 39 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
        else if (starting2 > 38 && starting2 < 47 && map->number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
        else if (starting2 > 46 && starting2 < 87)
        {
            if (starting2 > 46 && starting2 < 53) player.frame = PLAYER_MOVING02;
            else if (starting2 > 52 && starting2 < 59) player.frame = PLAYER_MOVING03;
            else if (starting2 > 58 && starting2 < 65) player.frame = PLAYER_MOVING02;
            else if (starting2 > 64 && starting2 < 71) player.frame = PLAYER_MOVING01;
            else if (starting2 > 70 && starting2 < 77) player.frame = PLAYER_MOVING04;
            else if (starting2 > 76 && starting2 < 83) player.frame = PLAYER_MOVING05;
            else if (starting2 > 82 && starting2 < 89) player.frame = PLAYER_MOVING04;
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            BITMAP* temp = create_bitmap(54, 80);
            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat));
            masked_blit((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, temp, 40 - (starting2 - 46), 0, 0, 0, (starting2 - 46) * 2, 80);
            draw_sprite_h_flip(buffer, temp, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
            destroy_bitmap(temp);
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (starting2 > 86 && starting2 < 95)
        {
            player.frame = PLAYER_MOVING01;
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 94 && starting2 < 103)
        {
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 102 && starting2 < 111)
        {
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 110 && starting2 < 119)
        {
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 118 && starting2 < 130)
        {
            if (map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        //if (starting2 > 5 && starting2 < 128 && map->number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[READY].dat, 240, 200);
        //starting2++;
        if (starting2 == 130)
        {
            player.x_position -= 40;
            input_locked = 0;
            stopall = 0;
            starting2 = 0;
            if (lastagedoor == 1)
            {
                input_locked = 1;
                call_event = 14;
            }
            else if (lastagedoor == 2)
            {
                input_locked = 1;
                call_event = 15;
            }
            else if (lastagedoor == 3)
            {
                input_locked = 1;
                call_event = 16;
            }
            else if (lastagedoor == 4)
            {
                input_locked = 1;
                call_event = 17;
            }
            else if (lastagedoor == 5)
            {
                input_locked = 1;
                call_event = 18;
            }
            else if (lastagedoor == 6)
            {
                input_locked = 1;
                call_event = 19;
            }
        }
    }
    else if (finishing > 0)
    {
        if (finishing > 0 && finishing < 16)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
            rest(50);
        }
        else if (finishing > 15 && finishing < 24)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position + 45 + screenx, (int)player.y_position + 34 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (finishing > 23 && finishing < 31)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position + 39 + screenx, (int)player.y_position + 32 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (finishing > 30 && finishing < 39)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position + 34 + screenx, (int)player.y_position + 23 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (finishing > 38 && finishing < 47)
        {
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position + 28 + screenx, (int)player.y_position + 3 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (finishing > 46 && finishing < 87)
        {
            if (finishing > 46 && finishing < 53) player.frame = PLAYER_MOVING02;
            else if (finishing > 52 && finishing < 59) player.frame = PLAYER_MOVING03;
            else if (finishing > 58 && finishing < 65) player.frame = PLAYER_MOVING02;
            else if (finishing > 64 && finishing < 71) player.frame = PLAYER_MOVING01;
            else if (finishing > 70 && finishing < 77) player.frame = PLAYER_MOVING04;
            else if (finishing > 76 && finishing < 83) player.frame = PLAYER_MOVING05;
            else if (finishing > 82 && finishing < 89) player.frame = PLAYER_MOVING04;
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position + 17 + screenx, (int)player.y_position - 20 + screeny);
            masked_blit((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, buffer, 0, 0, (int)player.x_position + screenx + (finishing - 46) * 2, (int)player.y_position + screeny, 50 - ((finishing - 46) * 2), 80);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position + 17 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (finishing > 86 && finishing < 95)
        {
            player.frame = NULO;
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position + 17 + screenx, (int)player.y_position - 20 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position + 17 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (finishing > 94 && finishing < 103)
        {
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position + 28 + screenx, (int)player.y_position + 3 + screeny);
        }
        else if (finishing > 102 && finishing < 111)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position + 34 + screenx, (int)player.y_position + 23 + screeny);
        }
        else if (finishing > 110 && finishing < 119)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position + 39 + screenx, (int)player.y_position + 32 + screeny);
        }
        else if (finishing > 118 && finishing < 130)
        {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position + 45 + screenx, (int)player.y_position + 34 + screeny);
        }
        //finishing++;
        if (finishing >= 131)
        {
            if (osutatakaefadeout < 255) osutatakaefadeout += 15;
            else
            {
                if (lastageboss == 0)
                {
                    stage_screen = 1;
                    speed_counter = 1;
                    finishing = 0;
                    current_level = 0;
                    menu = 0;
                    player.x_position = 0;
                    player.y_position = 0;
                    player.imune = 0;
                    return;
                }
                else
                {
                    current_level = 73;
                    if (lastageportal[0] == 1 && lastageportal[1] == 1 && lastageportal[2] == 1 && lastageportal[3] == 1 && lastageportal[4] == 1 && lastageportal[5] == 1)
                    {
                        current_level = 80;
                        lastagedoor = 7;
                        lastageblack = 255;
                    }
                    stopall = 1;
                    input_locked = 1;
                    screen_locked = 1;
                    next_level = 0;
                    setup_game();
                    while (osutatakaefadeout > 0)
                    {
                        draw();
                        osutatakaefadeout -= 15;
                    }
                    finishing = 0;
                }
            }
        }
    }
    else if (player.shine > 0)
    {
        if (player.shine == 1)
        {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 60);
            rest(50);
        }
        else if (player.shine == 2)
        {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 120);
            rest(50);
        }
        else if (player.shine == 3)
        {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 180);
            rest(50);
        }
        else if (player.shine == 4)
        {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 120);
            rest(50);
        }
        else if (player.shine == 5)
        {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 60);
            rest(50);
            player.shine = 0;
            finishing = 1;
        }
    }
    else
    {
        if (player.frame != PLAYERD && player.frame != NULO)
        {
            if (player.direction == 0)
            {
                draw_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
                if (player.frame >= PLAYER_MOVING32 && player.frame <= PLAYER_MOVING32F) draw_sprite( buffer, (BITMAP*)mydatafile[AAA].dat, (int)player.x_position + screenx + 2, (int)player.y_position + screeny + 28);
                else if (player.frame >= PLAYER_MOVING52 && player.frame <= PLAYER_MOVING52F) draw_sprite( buffer, (BITMAP*)mydatafile[AAA].dat, (int)player.x_position + screenx + 2, (int)player.y_position + screeny + 28);
                else if (player.frame >= PLAYER_MOVING12) draw_sprite( buffer, (BITMAP*)mydatafile[AAA].dat, (int)player.x_position + screenx + 2, (int)player.y_position + screeny + 26);
            }
            else
            {
                draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position - 10 + screenx, (int)player.y_position + screeny);
                if (player.frame >= PLAYER_MOVING32 && player.frame <= PLAYER_MOVING32F) draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[AAA].dat, (int)player.x_position + screenx + 26, (int)player.y_position + screeny + 28);
                else if (player.frame >= PLAYER_MOVING52 && player.frame <= PLAYER_MOVING52F) draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[AAA].dat, (int)player.x_position + screenx + 26, (int)player.y_position + screeny + 28);
                else if (player.frame >= PLAYER_MOVING12) draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[AAA].dat, (int)player.x_position + screenx + 26, (int)player.y_position + screeny + 26);
            }
        }
        else
        {
            if (player.direction == 0)
            {
                draw_sprite( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
            }
            else
            {
                draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position - 10 + screenx, (int)player.y_position + screeny);
            }
        }
    }

    if (map->type == 2 || map->type == 3)
        masked_blit( foreground, buffer, screenx * -1, screeny * -1, 0, 0, 640, 480);

    for (it = actors.begin(); it != actors.end(); it++)
    {
        if (it->active)
        {
            if (it->type == 403)
            {
                set_trans_blender(0,0,0,100);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[LUZ].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 100)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 66)
            {
                if (it->action_state == 0)
                {
                    draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                }
                else
                {
                    if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny - 24);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 24, (int)it->y_position + screeny - 24);
                }
            }
            else if (it->type == 73)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 74)
            {
                draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 2004)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 1)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 2)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 3)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 305)
            {
                if (it->timer % 2 == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 4)
            {
                if (it->frame == ZOCK01) it->frame++;
                else if (it->frame == ZOCK02) it->frame++;
                else if (it->frame == ZOCK03) it->frame++;
                else if (it->frame == ZOCK04) it->frame = ZOCK01;
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 5, (int)it->y_position + screeny - 8);
            }
            else if (it->type == 5)
            {
                it->animation_state++;
                if (it->animation_state <= 3) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->animation_state <= 6) stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, 32, 29);
                else if (it->animation_state <= 9) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 3, (int)it->y_position + screeny);
                else if (it->animation_state <= 12) stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 3, (int)it->y_position + screeny, 29, 32);
                else if (it->animation_state <= 15) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 3, (int)it->y_position + screeny + 3);
                else if (it->animation_state <= 18) stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 3, (int)it->y_position + screeny + 3, 32, 29);
                else if (it->animation_state <= 21) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 3);
                else if (it->animation_state <= 24)
                {
                    stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny - 3, 29, 32);
                    it->animation_state = 0;
                }
            }
            else if (it->type == 57 || it->type == 58)
            {
                it->animation_state++;
                if (it->animation_state <= 3) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->animation_state <= 6) stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny, 16, 14);
                else if (it->animation_state <= 9) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 2, (int)it->y_position + screeny);
                else if (it->animation_state <= 12) stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 2, (int)it->y_position + screeny, 14, 16);
                else if (it->animation_state <= 15) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx + 2, (int)it->y_position + screeny + 2);
                else if (it->animation_state <= 18) stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx - 2, (int)it->y_position + screeny + 2, 16, 14);
                else if (it->animation_state <= 21) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 2);
                else if (it->animation_state <= 24)
                {
                    stretch_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny - 2, 14, 16);
                    it->animation_state = 0;
                }
            }
            else if (it->type == 6)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 7)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 70)
            {
                if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 75)
            {
                it->animation_state++;
                if (it->animation_state == 6)
                {
                    it->frame++;
                    if (it->frame == LASTSMALL4 + 1) it->frame = LASTSMALL1;
                    if (it->frame == LASTBALL4 + 1) it->frame = LASTBALL1;
                    it->animation_state = 0;
                }
                set_trans_blender(0, 0, 0, it->extra_int);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 77)
            {
                set_trans_blender(0, 0, 0, it->extra_int);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 78)
            {
                set_trans_blender(0, 0, 0, it->extra_int);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 101)
            {
                set_trans_blender(0, 0, 0, it->strength);
                if (it->direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else
                {
                    BITMAP* temp = create_bitmap(it->width, it->height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[it->frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[it->frame].dat, 0, 0);
                    draw_trans_sprite(buffer, temp, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (it->type == 102)
            {
                set_trans_blender(0, 0, 0, it->strength);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 104)
            {
                if (it->frame == WATERSHOTHIT4) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else if (it->direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 1666)
            {
                set_trans_blender(0,0,0,it->strength);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 404)
            {
                draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
            }
            else if (it->type == 44)
            {
                for (int xyz = 0; it->width - xyz > 0; xyz += 60)
                {
                    if (it->width - xyz < 60) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 10, (int)it->x_position + screenx + xyz, (int)it->y_position + screeny + 10, it->width - xyz, 10);
                    else masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 10, (int)it->x_position + screenx + xyz, (int)it->y_position + screeny + 10, 60, 10);
                }
            }
            else if (it->type == 28)
            {
                if (it->animation_state == 1)
                {
                    it->height += 10;
                    if (it->height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 128);
                    if (it->height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 256);
                    if (it->height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 384);
                    if (it->height % 128 != 0)
                    {
                        it->action_state = (int)(it->height / 128);
                        if (it->action_state == 0) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 34, (it->height % 128));
                        else if (it->action_state == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 128, 34, (it->height % 128));
                        else if (it->action_state == 2) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 256, 34, (it->height % 128));
                        else if (it->action_state == 3) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 384, 34, (it->height % 128));
                    }
                    it->height -= 10;
                }
                else
                {
                    if (it->height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 128);
                    if (it->height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 256);
                    if (it->height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 384);
                    if (it->height % 128 != 0)
                    {
                        it->action_state = (int)(it->height / 128);
                        if (it->action_state == 0) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 34, (it->height % 128));
                        else if (it->action_state == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 128, 34, (it->height % 128));
                        else if (it->action_state == 2) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 256, 34, (it->height % 128));
                        else if (it->action_state == 3) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 384, 34, (it->height % 128));
                    }
                }
            }
            else if (it->type == 76)
            {
                if (it->animation_state == 1)
                {
                    it->height += 10;
                    if (it->height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 128);
                    if (it->height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 256);
                    if (it->height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 384);
                    if (it->height % 128 != 0)
                    {
                        it->action_state = (int)(it->height / 128);
                        if (it->action_state == 0) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 34, (it->height % 128));
                        else if (it->action_state == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 128, 34, (it->height % 128));
                        else if (it->action_state == 2) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 256, 34, (it->height % 128));
                        else if (it->action_state == 3) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 384, 34, (it->height % 128));
                    }
                    it->height -= 10;
                }
                else
                {
                    if (it->height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny);
                    if (it->height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 128);
                    if (it->height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 256);
                    if (it->height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[it->frame].dat, (int)it->x_position + screenx, (int)it->y_position + screeny + 384);
                    if (it->height % 128 != 0)
                    {
                        it->action_state = (int)(it->height / 128);
                        if (it->action_state == 0) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny, 34, (it->height % 128));
                        else if (it->action_state == 1) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 128, 34, (it->height % 128));
                        else if (it->action_state == 2) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 256, 34, (it->height % 128));
                        else if (it->action_state == 3) masked_blit((BITMAP*)mydatafile[it->frame].dat, buffer, 0, 0, (int)it->x_position + screenx, (int)it->y_position + screeny + 384, 34, (it->height % 128));
                    }
                }
            }
            else if (it->type == 1111)
            {
                if (it->timer % 7 == 0)
                {
                    it->direction = rand() % 12;
                    if (it->direction == 0)
                    {
                        it->width = (int)it->x_position + (rand() % 100) + 150;
                        it->height = (int)it->x_position + (rand() % 100) + 150;
                        it->x_speed = it->y_position + (rand() % 30) + 45;
                        it->y_speed = it->y_position + (rand() % 30) + 45;
                        it->extra_int = 3 + (rand() % 3);
                        it->strength = 3 + (rand() % 3);
                    }
                    else if (it->direction == 1)
                    {
                        it->width = (int)it->x_position + (rand() % 100) + 150;
                        it->height = (int)it->x_position + (rand() % 100) + 150;
                        it->x_speed = it->y_position - (rand() % 30) - 45;
                        it->y_speed = it->y_position - (rand() % 30) - 45;
                        it->extra_int = 3 + (rand() % 3);
                        it->strength = -3 - (rand() % 3);
                    }
                    else if (it->direction == 2)
                    {
                        it->width = (int)it->x_position - (rand() % 100) - 150;
                        it->height = (int)it->x_position - (rand() % 100) - 150;
                        it->x_speed = it->y_position + (rand() % 30) + 45;
                        it->y_speed = it->y_position + (rand() % 30) + 45;
                        it->extra_int = -3 - (rand() % 3);
                        it->strength = 3 + (rand() % 3);
                    }
                    else if (it->direction == 3)
                    {
                        it->width = (int)it->x_position - (rand() % 100) - 150;
                        it->height = (int)it->x_position - (rand() % 100) - 150;
                        it->x_speed = it->y_position - (rand() % 30) - 45;
                        it->y_speed = it->y_position - (rand() % 30) - 45;
                        it->extra_int = -3 - (rand() % 3);
                        it->strength = -3 - (rand() % 3);
                    }
                    else if (it->direction == 4)
                    {
                        it->width = (int)it->x_position + (rand() % 30) + 45;
                        it->height = (int)it->x_position + (rand() % 30) + 45;
                        it->x_speed = it->y_position + (rand() % 100) + 150;
                        it->y_speed = it->y_position + (rand() % 100) + 150;
                        it->extra_int = 3 + (rand() % 3);
                        it->strength = 3 + (rand() % 3);
                    }
                    else if (it->direction == 5)
                    {
                        it->width = (int)it->x_position + (rand() % 30) + 45;
                        it->height = (int)it->x_position + (rand() % 30) + 45;
                        it->x_speed = it->y_position - (rand() % 100) - 150;
                        it->y_speed = it->y_position - (rand() % 100) - 150;
                        it->extra_int = 3 + (rand() % 3);
                        it->strength = -3 - (rand() % 3);
                    }
                    else if (it->direction == 6)
                    {
                        it->width = (int)it->x_position - (rand() % 30) - 45;
                        it->height = (int)it->x_position - (rand() % 30) - 45;
                        it->x_speed = it->y_position + (rand() % 100) + 150;
                        it->y_speed = it->y_position + (rand() % 100) + 150;
                        it->extra_int = -3 - (rand() % 3);
                        it->strength = 3 + (rand() % 3);
                    }
                    else if (it->direction == 7)
                    {
                        it->width = (int)it->x_position - (rand() % 30) - 45;
                        it->height = (int)it->x_position - (rand() % 30) - 45;
                        it->x_speed = it->y_position - (rand() % 100) - 150;
                        it->y_speed = it->y_position - (rand() % 100) - 150;
                        it->extra_int = -3 - (rand() % 3);
                        it->strength = -3 - (rand() % 3);
                    }
                    else if (it->direction == 8)
                    {
                        it->width = (int)it->x_position + (rand() % 100) + 150;
                        it->height = (int)it->x_position + (rand() % 100) + 150;
                        it->x_speed = it->y_position - (rand() % 15) - 5;
                        it->y_speed = it->y_position + (rand() % 15) + 5;
                        it->extra_int = 5 + (rand() % 2);
                        it->strength = 0;
                    }
                    else if (it->direction == 9)
                    {
                        it->width = (int)it->x_position - (rand() % 100) - 150;
                        it->height = (int)it->x_position - (rand() % 100) - 150;
                        it->x_speed = it->y_position - (rand() % 15) - 5;
                        it->y_speed = it->y_position + (rand() % 15) + 5;
                        it->extra_int = -5 - (rand() % 2);
                        it->strength = 0;
                    }
                    else if (it->direction == 10)
                    {
                        it->width = (int)it->x_position - (rand() % 15) - 5;
                        it->height = (int)it->x_position + (rand() % 15) + 5;
                        it->x_speed = it->y_position + (rand() % 100) + 150;
                        it->y_speed = it->y_position + (rand() % 100) + 150;
                        it->extra_int = 0;
                        it->strength = 5 + (rand() % 2);
                    }
                    else if (it->direction == 11)
                    {
                        it->width = (int)it->x_position - (rand() % 15) - 5;
                        it->height = (int)it->x_position + (rand() % 15) + 5;
                        it->x_speed = it->y_position - (rand() % 100) - 150;
                        it->y_speed = it->y_position - (rand() % 100) - 150;
                        it->extra_int = 0;
                        it->strength = -5 - (rand() % 2);
                    }
                }
                triangle(buffer, (int)it->x_position + (int)it->extra_int + screenx, (int)it->y_position + (int)it->strength + screeny,
                         (int)it->width + screenx, (int)it->x_speed + screeny,
                         (int)it->height + screenx, (int)it->y_speed + screeny, makecol(255,255,20));
                if (bosslife == -1) it->active = 0;
                it->timer++;
            }
        }
    }

    if (dieanimation == 1)
    {
        if (player.timer <= -1100)
        {
            player.vidas--;
            if (player.vidas < 0)
            {
                stage_screen = 1;
                player.vidas = 5;
                return;
            }
            else
            {
                restart = 1;
                limpation = 0;
                dieanimation = 0;
                input_locked = 0;
                screen_locked = 0;
                bosslife = -1;
                bossfight = 0;
                map->create_level(this, current_level, restart);
                restart = 0;
                light_level = 0;
                return;
            }
        }
        for (int i = 0; i <= 11; i++)
            draw_sprite(buffer, (BITMAP*)mydatafile[bframe].dat, (int)(bolas[i][0] + screenx), (int)(bolas[i][1] + screeny));
    }

    if (map->water_position > 0)
    {
        if (current_level == 40)
        {
            set_trans_blender(0, 0, 0, 128);
            int y_adjuster = screeny;
            int x_adjuster = screenx;
            while (y_adjuster < -19) y_adjuster += 20;
            while (x_adjuster < -19) x_adjuster += 20;
            for (int q = 0; q < 33; q++)
            {
                for (int w = (int)(screeny / 20); w < 4; w++)
                {
                    if (w == (int)(screeny / 20))
                    {
                        if (aguaa % 60 >= 40)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 20)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 0)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                    }
                    else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                }
            }
            aguaa++;
        }
        else if (current_level == 41)
        {
            set_trans_blender(0, 0, 0, 128);
            int y_adjuster = screeny;
            int x_adjuster = screenx;
            while (y_adjuster < -19) y_adjuster += 20;
            while (x_adjuster < -19) x_adjuster += 20;
            for (int q = 0; q < 33; q++)
            {
                for (int w = (int)(screeny / 20); w < 15; w++)
                {
                    if (w == (int)(screeny / 20))
                    {
                        if (aguaa % 60 >= 40)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 20)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 0)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                    }
                    else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                }
            }
            aguaa++;
        }
        else if (current_level == 42)
        {
            set_trans_blender(0, 0, 0, 128);
            int y_adjuster = screeny;
            int x_adjuster = screenx;
            while (y_adjuster < -19) y_adjuster += 20;
            while (x_adjuster < -19) x_adjuster += 20;
            for (int q = 0; q < 33; q++)
            {
                for (int w = (int)(screeny / 20); w < 10; w++)
                {
                    if (w == (int)(screeny / 20))
                    {
                        if (aguaa % 60 >= 40)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 20)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 0)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                    }
                    else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                }
            }
            aguaa++;
        }
        else if (current_level == 78)
        {
            set_trans_blender(0, 0, 0, 128);
            int y_adjuster = screeny;
            int x_adjuster = screenx;
            while (y_adjuster < -19) y_adjuster += 20;
            while (x_adjuster < -19) x_adjuster += 20;
            for (int q = 0; q < 33; q++)
            {
                for (int w = (int)(screeny / 20); w < 10; w++)
                {
                    if (w == (int)(screeny / 20))
                    {
                        if (aguaa % 60 >= 40)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 20)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                        else if (aguaa % 60 >= 0)
                        {
                            draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                        }
                    }
                    else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, map->water_position + (w * 20) + y_adjuster);
                }
            }
            aguaa++;
        }
    }

    draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETER].dat, 10, 180);
    if (player.hpmax == 16) draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETER2].dat, 10, 175);
    else if (player.hpmax == 17) draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETER2].dat, 10, 170);
    else if (player.hpmax == 18) draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETER2].dat, 10, 165);
    else if (player.hpmax == 19) draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETER2].dat, 10, 160);
    else if (player.hpmax == 20) draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETER2].dat, 10, 155);
    for (int hp = 1; player.hp > 0 && hp != player.hp + 1; hp++)
        draw_sprite( buffer, (BITMAP*)mydatafile[LIFEBAR].dat, 13, 264 - (hp * 5));

    if (sparkmandril > 0)
    {
        if (sparkmandril < 9) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE1].dat, 0, 185 - (5 * (player.hpmax - 15)));
        if (sparkmandril < 17) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE2].dat, 0, 185 - (5 * (player.hpmax - 15)));
        if (sparkmandril < 25) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE3].dat, 0, 185 - (5 * (player.hpmax - 15)));
        if (sparkmandril < 33) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE4].dat, 0, 185 - (5 * (player.hpmax - 15)));
        sparkmandril++;
        if (sparkmandril == 33) sparkmandril = 0;
    }

    if (bosslife >= 0)
    {
        draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETERBOSS].dat, 610, 100);
        for (int hp = 1; hp != bosslife + 1; hp++)
            draw_sprite( buffer, (BITMAP*)mydatafile[LIFEBAR].dat, 613, 259 - (hp * 5));
    }

    //bibinhalinda = howtoend;
    sprintf(txt,"PT: %f XA: %f YA: %f OG: %d", player.timer, player.x_speed, player.y_speed, player.on_ground);
    if (show_fps == 1)
    {
        sprintf(txt, "FPS: %d", last_fps);
        textout_ex(buffer, font, txt, 5, 5, makecol(255,0,0), 1);
    }
    textout_ex(buffer, font, txt, 5, 15, makecol(255,0,0), 0);

    if (bosslife == 0)
    {
        move_to_end();
        if (light_level < 255) light_level++;
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, light_level);
        if (light_level == 255)
        {
            rest(500);
            bosslife = -1;
            bossfight = 0;
            if (lastagedoor == 7)
            {
                itsover = 1;
            }
        }
    }
    else if (light_level > 1)
    {
        light_level--;
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, light_level);
        if (light_level == 1)
        {
            if (lastageboss == 1) finishing = 1;
        }
    }
    else if (flash_screen == 1)
    {
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, 200);
    }
    else if (flash_screen == 2)
    {
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, 255);
    }
    else if (osutatakaefadeout > 0)
    {
        set_trans_blender(0, 0, 0, 0);
        draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
    }
    else draw_sprite(screen, buffer, 0, 0);
    force_draw = 0;
}

int Game::check_colision(Actor a, WallList::iterator b, int sop)
{
    if (sop == 2)
    {
        if (a.x_position > b->x_position && a.x_position - b->x_position >= b->width) return 0;
        else if (a.x_position <= b->x_position && b->x_position - a.x_position >= a.width) return 0;
        if (a.y_position > b->y_position && a.y_position - b->y_position >= b->height) return 0;
        else if (a.y_position <= b->y_position && b->y_position - a.y_position >= a.height) return 0;
    }

    return 1;
}

int Game::check_colision(Actor a, ActorList::iterator b, int sop)
{
    if (sop == 1)
    {
        if (a.x_position > b->x_position && a.x_position - b->x_position >= b->width) return 0;
        else if (a.x_position <= b->x_position && b->x_position - a.x_position >= a.width) return 0;
        if (a.y_position > b->y_position && a.y_position - b->y_position >= b->height) return 0;
        else if (a.y_position <= b->y_position && b->y_position - a.y_position >= a.height) return 0;
    }

    else if (sop == 3)
    {
        if (a.type == 1)
        {
            int x = (int)a.x_position - (int)b->x_position;
            int y = (int)a.y_position - (int)b->y_position;
            if (b->direction == 0)
            {
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 1, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 1) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 1) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 8) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 2, y + 8) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 1) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 1) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 8) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 8) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 9) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 3, y + 9) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 1) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 1) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 8) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 8) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 9) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 4, y + 9) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 1) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 1) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 8) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 8) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 9) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 5, y + 9) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 1) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 1) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 8) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 8) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 9) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 6, y + 9) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 1) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 1) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 8) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 7, y + 8) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 2) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 2) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 6) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 7) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 8, y + 7) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 3) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 3) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 4) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 4) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 5) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 5) != -1) return 1;
                if (getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 6) != makecol(255, 0, 255) &&
                        getpixel((BITMAP*)mydatafile[b->frame].dat, x + 9, y + 6) != -1) return 1;
                return 0;
            }
            else
            {
                BITMAP* temp = create_bitmap(b->width, b->height);
                clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[b->frame].dat));
                draw_sprite_h_flip(temp, (BITMAP*)mydatafile[b->frame].dat, 0, 0);
                if (getpixel(temp, x, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x, y + 3) != -1) return 1;
                if (getpixel(temp, x, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x, y + 4) != -1) return 1;
                if (getpixel(temp, x, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x, y + 5) != -1) return 1;
                if (getpixel(temp, x, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x, y + 6) != -1) return 1;
                if (getpixel(temp, x + 1, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 1, y + 2) != -1) return 1;
                if (getpixel(temp, x + 1, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 1, y + 3) != -1) return 1;
                if (getpixel(temp, x + 1, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 1, y + 4) != -1) return 1;
                if (getpixel(temp, x + 1, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 1, y + 5) != -1) return 1;
                if (getpixel(temp, x + 1, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 1, y + 6) != -1) return 1;
                if (getpixel(temp, x + 1, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 1, y + 7) != -1) return 1;
                if (getpixel(temp, x + 2, y + 1) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 1) != -1) return 1;
                if (getpixel(temp, x + 2, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 2) != -1) return 1;
                if (getpixel(temp, x + 2, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 3) != -1) return 1;
                if (getpixel(temp, x + 2, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 4) != -1) return 1;
                if (getpixel(temp, x + 2, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 5) != -1) return 1;
                if (getpixel(temp, x + 2, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 6) != -1) return 1;
                if (getpixel(temp, x + 2, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 7) != -1) return 1;
                if (getpixel(temp, x + 2, y + 8) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 2, y + 8) != -1) return 1;
                if (getpixel(temp, x + 3, y) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y) != -1) return 1;
                if (getpixel(temp, x + 3, y + 1) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 1) != -1) return 1;
                if (getpixel(temp, x + 3, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 2) != -1) return 1;
                if (getpixel(temp, x + 3, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 3) != -1) return 1;
                if (getpixel(temp, x + 3, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 4) != -1) return 1;
                if (getpixel(temp, x + 3, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 5) != -1) return 1;
                if (getpixel(temp, x + 3, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 6) != -1) return 1;
                if (getpixel(temp, x + 3, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 7) != -1) return 1;
                if (getpixel(temp, x + 3, y + 8) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 8) != -1) return 1;
                if (getpixel(temp, x + 3, y + 9) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 3, y + 9) != -1) return 1;
                if (getpixel(temp, x + 4, y) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y) != -1) return 1;
                if (getpixel(temp, x + 4, y + 1) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 1) != -1) return 1;
                if (getpixel(temp, x + 4, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 2) != -1) return 1;
                if (getpixel(temp, x + 4, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 3) != -1) return 1;
                if (getpixel(temp, x + 4, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 4) != -1) return 1;
                if (getpixel(temp, x + 4, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 5) != -1) return 1;
                if (getpixel(temp, x + 4, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 6) != -1) return 1;
                if (getpixel(temp, x + 4, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 7) != -1) return 1;
                if (getpixel(temp, x + 4, y + 8) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 8) != -1) return 1;
                if (getpixel(temp, x + 4, y + 9) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 4, y + 9) != -1) return 1;
                if (getpixel(temp, x + 5, y) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y) != -1) return 1;
                if (getpixel(temp, x + 5, y + 1) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 1) != -1) return 1;
                if (getpixel(temp, x + 5, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 2) != -1) return 1;
                if (getpixel(temp, x + 5, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 3) != -1) return 1;
                if (getpixel(temp, x + 5, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 4) != -1) return 1;
                if (getpixel(temp, x + 5, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 5) != -1) return 1;
                if (getpixel(temp, x + 5, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 6) != -1) return 1;
                if (getpixel(temp, x + 5, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 7) != -1) return 1;
                if (getpixel(temp, x + 5, y + 8) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 8) != -1) return 1;
                if (getpixel(temp, x + 5, y + 9) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 5, y + 9) != -1) return 1;
                if (getpixel(temp, x + 6, y) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y) != -1) return 1;
                if (getpixel(temp, x + 6, y + 1) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 1) != -1) return 1;
                if (getpixel(temp, x + 6, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 2) != -1) return 1;
                if (getpixel(temp, x + 6, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 3) != -1) return 1;
                if (getpixel(temp, x + 6, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 4) != -1) return 1;
                if (getpixel(temp, x + 6, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 5) != -1) return 1;
                if (getpixel(temp, x + 6, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 6) != -1) return 1;
                if (getpixel(temp, x + 6, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 7) != -1) return 1;
                if (getpixel(temp, x + 6, y + 8) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 8) != -1) return 1;
                if (getpixel(temp, x + 6, y + 9) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 6, y + 9) != -1) return 1;
                if (getpixel(temp, x + 7, y + 1) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 1) != -1) return 1;
                if (getpixel(temp, x + 7, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 2) != -1) return 1;
                if (getpixel(temp, x + 7, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 3) != -1) return 1;
                if (getpixel(temp, x + 7, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 4) != -1) return 1;
                if (getpixel(temp, x + 7, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 5) != -1) return 1;
                if (getpixel(temp, x + 7, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 6) != -1) return 1;
                if (getpixel(temp, x + 7, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 7) != -1) return 1;
                if (getpixel(temp, x + 7, y + 8) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 7, y + 8) != -1) return 1;
                if (getpixel(temp, x + 8, y + 2) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 8, y + 2) != -1) return 1;
                if (getpixel(temp, x + 8, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 8, y + 3) != -1) return 1;
                if (getpixel(temp, x + 8, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 8, y + 4) != -1) return 1;
                if (getpixel(temp, x + 8, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 8, y + 5) != -1) return 1;
                if (getpixel(temp, x + 8, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 8, y + 6) != -1) return 1;
                if (getpixel(temp, x + 8, y + 7) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 8, y + 7) != -1) return 1;
                if (getpixel(temp, x + 9, y + 3) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 9, y + 3) != -1) return 1;
                if (getpixel(temp, x + 9, y + 4) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 9, y + 4) != -1) return 1;
                if (getpixel(temp, x + 9, y + 5) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 9, y + 5) != -1) return 1;
                if (getpixel(temp, x + 9, y + 6) != makecol(255, 0, 255) &&
                        getpixel(temp, x + 9, y + 6) != -1) return 1;
                destroy_bitmap(temp);
                return 0;
            }
        }
    }

    else if (sop == 4)
    {
        if (a.type == 1)
        {
            int x = (int)a.x_position;
            int y = (int)a.y_position;
            if (getpixel(game->scenario, x, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 1, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 1, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 1, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 1, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 1, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 1, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 1, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 1, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 1, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 1, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 1, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 1, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 1) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 1, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 2, y + 8) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 2, y + 8, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 1) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 1, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 8) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 8, 0)) return 1;
            if (getpixel(game->scenario, x + 3, y + 9) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 3, y + 9, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 1) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 1, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 8) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 8, 0)) return 1;
            if (getpixel(game->scenario, x + 4, y + 9) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 4, y + 9, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 1) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 1, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 8) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 8, 0)) return 1;
            if (getpixel(game->scenario, x + 5, y + 9) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 5, y + 9, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 1) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 1, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 8) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 8, 0)) return 1;
            if (getpixel(game->scenario, x + 6, y + 9) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 6, y + 9, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 1) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 1, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 7, y + 8) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 7, y + 8, 0)) return 1;
            if (getpixel(game->scenario, x + 8, y + 2) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 8, y + 2, 0)) return 1;
            if (getpixel(game->scenario, x + 8, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 8, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 8, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 8, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 8, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 8, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 8, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 8, y + 6, 0)) return 1;
            if (getpixel(game->scenario, x + 8, y + 7) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 8, y + 7, 0)) return 1;
            if (getpixel(game->scenario, x + 9, y + 3) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 9, y + 3, 0)) return 1;
            if (getpixel(game->scenario, x + 9, y + 4) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 9, y + 4, 0)) return 1;
            if (getpixel(game->scenario, x + 9, y + 5) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 9, y + 5, 0)) return 1;
            if (getpixel(game->scenario, x + 9, y + 6) != makecol(255, 0, 255) &&
                    is_inside_bitmap(game->scenario, x + 9, y + 6, 0)) return 1;
            return 0;
        }
    }

    return 1;
}

void Game::actor_colision(Actor *actor)
{
    for (ActorList::iterator it = actors.begin(); it != actors.end(); it++)
    {
        if (it->active && check_colision(*actor, it, 1))
        {
            if (it->type == GHOST && it->action_state == 0) continue;
            if (it->type == FIRES && it->action_state == 2) continue;
            if (it->type == BOSS_THUNDER && it->frame > THUNDER05) continue;
            if (actor->type == YELLOW_SHOT && it->hittable[0])
            {
                if (check_colision(*actor, it, 3))
                {
                    actor->extra_int = 0;
                    if (actor->direction == 0)
                    {
                        while (check_colision(*actor, it, 3) && actor->extra_int < 5)
                        {
                            actor->x_position--;
                            actor->extra_int++;
                        }
                    }
                    else
                    {
                        while (check_colision(*actor, it, 3) && actor->extra_int < 5)
                        {
                            actor->x_position++;
                            actor->extra_int++;
                        }
                    }
                    actor->animation();
                    it->damage(actor);
                    break;
                }
            }
            else if (actor->type == WIND_SHOT && it->hittable[1])
            {
                actor->animation();
                it->damage(actor);
                break;
            }
            else if (actor->type == SHADOW_SHOT && it->hittable[2])
            {
                if (it->type == PORTA_1)
                {
                    if (actor->extra_int == 1)
                    {
                        if (actor->x_speed < 0) actor->x_position = (it->x_position + it->width);
                        else actor->x_position = it->x_position - 30;
                        actor->x_speed *= -1;
                    }
                    else if (actor->extra_int == 2)
                    {
                        if (actor->y_speed < 0) actor->y_position = (it->y_position + it->height);
                        else actor->y_position = it->y_position - 30;
                        actor->y_speed *= -1;
                    }
                    play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else
                {
                    actor->animation();
                    it->damage(actor);
                    break;
                }
            }
            else if (actor->type == THUNDER_SHOT && it->hittable[3])
            {
                if (it->type == 60 && (it->action_state == 3 || it->action_state == 4)) continue;
                actor->animation();
                it->damage(actor);
                break;
            }
            else if (actor->type == WATER_SHOT && it->hittable[4])
            {
                if (actor->extra_int == 1)
                {
                    if (actor->direction == 1) actor->x_position = (it->x_position + it->width - 7);
                    else actor->x_position = it->x_position - 29 + 14;
                }
                else if (actor->extra_int == 2)
                {
                    if (actor->y_speed <= 0)
                    {
                        actor->extra_int = 3;
                        actor->y_position = it->y_position + it->height;
                    }
                    else actor->y_position = it->y_position - 29;
                }
                actor->strength = 1;
                actor->animation();
                it->damage(actor);
                break;
            }
            else if ((actor->type == WATER_SHOT_SMALL1 || actor->type == WATER_SHOT_SMALL2) && it->hittable[4])
            {
                actor->active = 0;
                it->damage(actor);
                break;
            }
            else if (actor->type == FIRE_SHOT && it->hittable[5])
            {
                if (actor->direction == 1) actor->x_position = it->x_position + it->width;
                else actor->x_position = it->x_position - 24;
                actor->animation();
                it->damage(actor);
                break;
            }
            else if (actor->type == ICE_SHOT && it->hittable[6])
            {
                actor->animation();
                it->damage(actor);
                break;
            }
            else if (actor->type == BOSS_SHADOW && it->type == PORTA_1)
            {
                if (actor->extra_int == 1)
                {
                    if (actor->x_speed > 0) actor->x_position = it->x_position - 50;
                    else actor->x_position = it->x_position + 30;
                    actor->x_speed = actor->x_speed * -1;
                }
                else
                {
                    if (actor->y_speed > 0) actor->y_position = it->y_position - 50;
                    else actor->y_position = it->y_position + 20;
                    actor->y_speed *= -1;
                }
                play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (actor->type == BOSS_SHADOW2 && it->type == PORTA_1)
            {
                if (actor->extra_int == 1)
                {
                    if (actor->x_speed > 0) actor->x_position = it->x_position - 50;
                    else actor->x_position = it->x_position + 30;
                    actor->x_speed = actor->x_speed * -1;
                }
                else
                {
                    if (actor->y_speed > 0) actor->y_position = it->y_position - 50;
                    else actor->y_position = it->y_position + 20;
                    actor->y_speed *= -1;
                }
                play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (actor->type == SHOCKER_SHOT && it->type == PORTA_1)
            {
                actor->active = 0;
            }
            else if (actor->type == ICY_ATTACK && it->type == PORTA_2)
            {
                actor->active = 0;
            }
            else if (actor->type == WATER_JET && it->type == PORTA_1)
            {
                if (actor->direction == 0)
                {
                    if (actor->animation_state == 0)
                    {
                        actor->x_position = it->x_position + 30;
                        actor->extra_int -= 2;
                        actor->width -= 32;
                        actor->x_position -= 3;
                        if (actor->extra_int <= 0) actor->active = 0;
                    }
                    else
                    {
                        if (actor->action_state == 1)
                        {
                            actor->extra_int -= 2;
                            actor->width -= 32;
                            actor->x_position = it->x_position + 30;
                            if (actor->extra_int <= 0) actor->active = 0;
                        }
                        else actor->x_position = it->x_position + 30;
                    }
                }
            }
            else if (actor->type == BOSS_WATER && it->type == PORTA_1)
            {
                actor->x_position = it->x_position + 30;
                actor->action_state++;
                actor->timer = 0;
            }
        }
    }
}

void Game::wall_colision(Actor *actor)
{
    int noisiloc = 0;
    for (WallList::iterator itw = walls.begin(); itw != walls.end(); itw++)
    {
        if (itw->active && check_colision(*actor, itw, 2))
        {
            if (actor->type == YELLOW_SHOT && itw->type == 20)
            {
                if (check_colision(*actor, itw, 4))
                {
                    actor->extra_int = 0;
                    if (actor->direction == 0)
                    {
                        while (check_colision(*actor, itw, 4) && actor->extra_int < 5)
                        {
                            actor->x_position--;
                            actor->extra_int++;
                        }
                    }
                    else
                    {
                        while (check_colision(*actor, itw, 4) && actor->extra_int < 5)
                        {
                            actor->x_position++;
                            actor->extra_int++;
                        }
                    }
                    actor->animation();
                    break;
                }
            }
            else if (actor->type == WIND_SHOT && itw->type == 20)
            {
                if (actor->direction == 1) actor->x_position = (itw->x_position + itw->width);
                else actor->x_position = itw->x_position - 65;
                actor->animation();
            }
            else if (actor->type == SHADOW_SHOT && itw->type == 20)
            {
                if (actor->extra_int == 1)
                {
                    if (actor->x_speed < 0) actor->x_position = (itw->x_position + itw->width);
                    else actor->x_position = itw->x_position - 30;
                    actor->x_speed *= -1;
                }
                else if (actor->extra_int == 2)
                {
                    if (actor->y_speed < 0) actor->y_position = (itw->y_position + itw->height);
                    else actor->y_position = itw->y_position - 30;
                    actor->y_speed *= -1;
                }
                play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (actor->type == THUNDER_SHOT && itw->type == 20)
            {
                if (actor->direction == 1) actor->x_position = (itw->x_position + itw->width - 5);
                else actor->x_position = itw->x_position - 21;
                actor->animation();
            }
            else if (actor->type == WATER_SHOT && itw->type == 20)
            {
                if (actor->extra_int == 1)
                {
                    if (actor->direction == 1) actor->x_position = (itw->x_position + itw->width);
                    else actor->x_position = itw->x_position - 29;
                    actor->animation();
                }
                else if (actor->extra_int == 2)
                {
                    if (actor->y_speed <= 0)
                    {
                        actor->extra_int = 3;
                        actor->y_position = itw->y_position + 20;
                    }
                    else actor->y_position = itw->y_position - 29;
                    actor->animation();
                }
            }
            else if (actor->type == FIRE_SHOT && itw->type == 20 && actor->action_state != 2)
            {
                if (check_colision(*actor, itw, 4))
                {
                    int y = 0;
                    while ((y < actor->y_speed - 2) && check_colision(*actor, itw, 4))
                    {
                        actor->y_position--;
                        y++;
                    }
                    if (check_colision(*actor, itw, 4))
                    {
                        if (actor->direction == 1) actor->x_position = itw->x_position + 20;
                        else actor->x_position = itw->x_position - 24;
                        actor->animation();
                    }
                }
            }
            else if (actor->type == ICE_SHOT && itw->type == 20)
            {
                if (actor->direction == 1) actor->x_position = (itw->x_position + itw->width);
                else actor->x_position = itw->x_position - 47;
                actor->animation();
            }
            else if (actor->type == PHANTOM)
            {
                actor->animation_state = 1;
            }
            else if (actor->type == PHANTOM2)
            {
                actor->animation_state = 1;
            }
            else if (actor->type == WATER_SHOT_SMALL1 && itw->type == 20)
            {
                if (actor->direction == 1) actor->x_position = (itw->x_position + itw->width);
                else actor->x_position = itw->x_position - 14;
                actor->active = 0;
            }
            else if (actor->type == WATER_SHOT_SMALL2 && itw->type == 20)
            {
                if (actor->direction == 1) actor->x_position = (itw->x_position + itw->width);
                else actor->x_position = itw->x_position - 14;
                actor->active = 0;
            }
            else if (actor->type == RECOVERY_SMALL && (itw->type == 20 || itw->type == 11 || itw->type == 12 || itw->type == 10))
            {
                if (actor->y_position >= itw->y_position)
                {
                    actor->y_position = itw->y_position - 10;
                    actor->y_speed = 0;
                }
                else
                {
                    actor->y_position = itw->y_position - actor->height;
                    actor->y_speed = 0;
                }
                noisiloc = 1;
            }
            else if (actor->type == VIDA && itw->type == 20)
            {
                actor->y_speed = 0;
                actor->y_position = itw->y_position - actor->height;
            }
            else if (actor->type == CARD && itw->type == 20)
            {
                actor->y_speed = 0;
                actor->y_position = itw->y_position - actor->height - 10;
            }
            else if (actor->type == TURRET_ENEMY_SHOT && itw->type == 20)
            {
                actor->animation();
            }
            else if (actor->type == WALL_TURRET_SHOT && itw->type == 20)
            {
                actor->animation();
            }
            else if (actor->type == MISSILE && itw->type == 20)
            {
                actor->animation();
            }
            else if (actor->type == SHOCKER_SHOT && itw->type == 20)
            {
                actor->active = 0;
            }
            else if (actor->type == THUNDER_SHOT && itw->type == 20)
            {
                if (actor->extra_int == 0) actor->extra_int = (int)itw->y_position;
            }
            else if (actor->type == LAST_THUNDER && itw->type == 20)
            {
                if (actor->extra_int == 0) actor->extra_int = (int)itw->y_position;
            }
            else if (actor->type == OYSTER_BALL && itw->type == 20)
            {
                if (check_colision(*actor, itw, 4))
                {
                    int y = 0;
                    while ((y < actor->y_speed - 2) && check_colision(*actor, itw, 4))
                    {
                        actor->y_position--;
                        y++;
                    }
                    if (check_colision(*actor, itw, 4)) actor->active = 0;
                }
            }
            else if (actor->type == WATER_JET && itw->type == 20)
            {
                if (actor->direction == 1)
                {
                    if (actor->animation_state == 1)
                    {
                        if (actor->action_state == 1)
                        {
                            actor->extra_int -= 2;
                            actor->width -= 32;
                            actor->x_position = itw->x_position - actor->width;
                            if (actor->extra_int <= 0) actor->active = 0;
                        }
                        else actor->x_position = itw->x_position - actor->width;
                    }
                    else
                    {
                        actor->extra_int -= 2;
                        actor->width -= 32;
                        actor->x_position = itw->x_position - actor->width;
                        if (actor->extra_int <= 0) actor->active = 0;
                    }
                }
                else
                {
                    if (actor->animation_state == 0)
                    {
                        actor->x_position = itw->x_position + 20;
                        actor->extra_int -= 2;
                        actor->width -= 32;
                        actor->x_position -= 3;
                        if (actor->extra_int <= 0) actor->active = 0;
                    }
                    else
                    {
                        if (actor->action_state == 1)
                        {
                            actor->extra_int -= 2;
                            actor->width -= 32;
                            actor->x_position = itw->x_position + 20;
                            if (actor->extra_int <= 0) actor->active = 0;
                        }
                        else actor->x_position = itw->x_position + 30;
                    }
                }
            }
            else if (actor->type == PARTICLES1 && itw->type == 20)
            {
                if (actor->y_speed > 0) actor->y_position = itw->y_position - actor->height;
                else actor->y_position = itw->y_position + 20;
                actor->animation();
            }
            else if (actor->type == BOSS_SHADOW && itw->type == 20)
            {
                if (actor->extra_int == 1)
                {
                    if (actor->x_speed > 0) actor->x_position = itw->x_position - 50;
                    else actor->x_position = itw->x_position + 20;
                    actor->x_speed = actor->x_speed * -1;
                }
                else
                {
                    if (actor->y_speed > 0) actor->y_position = itw->y_position - 50;
                    else actor->y_position = itw->y_position + 20;
                    actor->y_speed *= -1;
                }
                play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (actor->type == BOSS_SHADOW2 && itw->type == 20)
            {
                if (actor->extra_int == 1)
                {
                    if (actor->x_speed > 0) actor->x_position = itw->x_position - 50;
                    else actor->x_position = itw->x_position + 20;
                    actor->x_speed = actor->x_speed * -1;
                }
                else
                {
                    if (actor->y_speed > 0) actor->y_position = itw->y_position - 50;
                    else actor->y_position = itw->y_position + 20;
                    actor->y_speed *= -1;
                }
                play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
            }
            else if (actor->type == RED_BALL && itw->type == 20)
            {
                if (actor->direction == 1)
                {
                    actor->direction = 0;
                    actor->x_position = itw->x_position - actor->width;
                }
                else
                {
                    actor->direction = 1;
                    actor->x_position = itw->x_position + itw->width;
                }
                noisiloc = 1;
            }
            else if (actor->type == FLAME_METROID && itw->type == 20)
            {
                if (actor->direction == 1)
                {
                    actor->direction = 0;
                    actor->x_position = itw->x_position - actor->width;
                }
                else
                {
                    actor->direction = 1;
                    actor->x_position = itw->x_position + itw->width;
                }
                noisiloc = 1;
            }
            else if (actor->type == FLAME_METROID_WALL && itw->type == 20)
            {
                if (actor->direction == 1)
                {
                    actor->direction = 0;
                    actor->x_position = itw->x_position - actor->width;
                }
                else
                {
                    actor->direction = 1;
                    actor->x_position = itw->x_position + itw->width;
                }
                noisiloc = 1;
            }
            else if (actor->type == FIRE && itw->type == 20)
            {
                actor->y_speed = 0;
                actor->y_position = itw->y_position - actor->height;
                actor->action_state = 2;
                actor->timer = 0;
                actor->x_position -= 9;
                actor->y_position -= 1;
                actor->frame = FIRE5;
            }
            else if (actor->type == SEA_HORSE && itw->type == 20)
            {
                actor->active = 0;
            }
            else if (actor->type == SEA_HORSE_SPAWNER && (itw->type == 20 || itw->type == 11 || itw->type == 12 || itw->type == 10))
            {
                if (actor->y_position >= itw->y_position)
                {
                    actor->y_position = itw->y_position + 20;
                    actor->y_speed = 0;
                }
                else
                {
                    actor->y_position = itw->y_position - actor->height;
                    actor->y_speed = 0;
                }
                noisiloc = 1;
            }
            else if (actor->type == FISH && (itw->type == 20 || itw->type == 11 || itw->type == 12 || itw->type == 10))
            {
                if (actor->x_position >= itw->x_position)
                {
                    actor->x_position = itw->x_position + 20;
                    actor->x_speed = 0;
                }
                else
                {
                    actor->x_position = itw->x_position - actor->width;
                    actor->x_speed = 0;
                }
                noisiloc = 1;
            }
            else if (actor->type == FIRES && itw->type == 20)
            {
                if (check_colision(*actor, itw, 4))
                {
                    int y = 0;
                    while ((y < actor->y_speed - 2) && check_colision(*actor, itw, 4))
                    {
                        actor->y_position--;
                        y++;
                    }
                    if (check_colision(*actor, itw, 4))
                    {
                        actor->direction = 0;
                        actor->action_state = 2;
                        actor->timer = 0;
                        if (actor->extra_int == 1) actor->y_position = itw->y_position - 40;
                        else actor->x_position = itw->x_position + 20;
                    }
                }
            }
            else if (actor->type == FIRE_BALL && itw->type == 20)
            {
                if (check_colision(*actor, itw, 4))
                {
                    int y = 0;
                    while ((y < actor->y_speed - 2) && check_colision(*actor, itw, 4))
                    {
                        actor->y_position--;
                        y++;
                    }
                    if (check_colision(*actor, itw, 4))
                    {
                        actor->x_position = itw->x_position + 20;
                        actor->animation();
                    }
                }
            }
            else if (actor->type == SLASH1 && itw->type == 20)
            {
                if (check_colision(*actor, itw, 4))
                {
                    int y = 0;
                    while ((y < actor->y_speed - 2) && check_colision(*actor, itw, 4))
                    {
                        actor->y_position--;
                        y++;
                    }
                    if (check_colision(*actor, itw, 4))
                    {
                        actor->active = 0;
                    }
                }
            }
            else if (actor->type == SLASH2 && itw->type == 20)
            {
                if (check_colision(*actor, itw, 4))
                {
                    int y = 0;
                    while ((y < actor->y_speed - 2) && check_colision(*actor, itw, 4))
                    {
                        actor->y_position--;
                        y++;
                    }
                    if (check_colision(*actor, itw, 4))
                    {
                        actor->active = 0;
                    }
                }
            }
            else if (actor->type == ICE_METROID && itw->type == 20)
            {
                if (actor->direction == 1)
                {
                    actor->direction = 0;
                    actor->x_position = itw->x_position - actor->width;
                }
                else
                {
                    actor->direction = 1;
                    actor->x_position = itw->x_position + itw->width;
                }
                noisiloc = 1;
            }
            else if (actor->type == ICE_TOP1 && itw->type == 20)
            {
                actor->y_position = itw->y_position - actor->height;
                actor->action_state = 2;
                actor->timer = 0;
            }
            else if (actor->type == ICE_TOP2 && itw->type == 20)
            {
                actor->y_position = itw->y_position - actor->height;
                actor->action_state = 2;
                actor->timer = 0;
            }
            else if (actor->type == ICE_NEEDLE && itw->type == 20)
            {
                actor->active = 0;
            }
            else if (actor->type == PUMPKIN && itw->type == 20)
            {
                if (actor->direction == 1)
                {
                    actor->direction = 0;
                    actor->x_position = itw->x_position - actor->width;
                }
                else
                {
                    actor->direction = 1;
                    actor->x_position = itw->x_position + itw->width;
                }
                noisiloc = 1;
            }
            else if (actor->type == ICE_SHOT && itw->type == 20)
            {
                actor->active = 0;
            }
            else if (actor->type == PENA)
            {
                actor->active = 0;
            }
            else if (actor->type == BOSS_WATER && itw->type == 20)
            {
                if (actor->direction == 1) actor->x_position = itw->x_position - actor->width;
                else actor->x_position = itw->x_position + 20;
                actor->action_state++;
                actor->timer = 0;
            }
        }
        if (noisiloc == 1)
        {
            noisiloc = 0;
            break;
        }
    }
}

void Game::move_to_end()
{
    if (current_level == 14 || current_level == 75)
    {
        if (player.on_ground == false)
        {
            if (((int)(int)player.x_position >= 3100 && (int)(int)player.x_position < 3260) || ((int)(int)player.x_position >= 3460 && (int)(int)player.x_position < 3620))
            {
                if (180 - (int)player.y_position >= 5) player.y_position += 5;
                else if (180 - (int)player.y_position > 0 && 180 - (int)player.y_position < 5)
                {
                    player.y_position = 180;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else if ((int)(int)player.x_position >= 3060 && (int)(int)player.x_position < 3660)
            {
                if (300 - (int)player.y_position >= 5) player.y_position += 5;
                else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 5)
                {
                    player.y_position = 300;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else
            {
                if (480 - (int)player.y_position >= 5) player.y_position += 5;
                else if (480 - (int)player.y_position > 0 && 480 - (int)player.y_position < 5)
                {
                    player.y_position = 480;
                    player.on_ground = true;
                }
                else player.on_ground = true;
                if ((int)player.y_position >= 480)
                {
                    restart = 1;
                    return;
                }
            }
        }
        else if (howtoend == 0)
        {
            if ((int)player.x_position < 3100) howtoend = 1;
            else if ((int)player.x_position >= 3100 && (int)player.x_position < 3260) howtoend = 2;
            else if ((int)player.x_position >= 3260 && (int)player.x_position < 3460) howtoend = 3;
            else if ((int)player.x_position >= 3460 && (int)player.x_position < 3620) howtoend = 4;
            else howtoend = 5;
        }
        else if (howtoend == 1)
        {
            if (3360 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3360 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3360;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 2)
        {
            if (3180 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3180 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3180;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 3)
        {
            if (3360 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3360 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3360;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 4)
        {
            if (3540 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3540 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3540;
            }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed <= 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 5)
        {
            if (3360 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3360 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3360;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 23 || current_level == 76)
    {
        if (player.on_ground == false)
        {
            if (460 - (int)player.y_position >= 5) player.y_position += 5;
            else if (460 - (int)player.y_position > 0 && 460 - (int)player.y_position < 5)
            {
                player.y_position = 460;
                player.on_ground = true;
            }
            else player.on_ground = true;
        }
        else if (howtoend == 0)
        {
            if (5480 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5480 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 5480;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 32 || current_level == 77)
    {
        if (player.on_ground == false)
        {
            if (400 - (int)player.y_position >= 5) player.y_position += 5;
            else if (400 - (int)player.y_position > 0 && 400 - (int)player.y_position < 5)
            {
                player.y_position = 400;
                player.on_ground = true;
            }
            else player.on_ground = true;
        }
        else if (howtoend == 0)
        {
            if (5460 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5460 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 5460;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 42  || current_level == 78)
    {
        if (player.on_ground == false)
        {
            if (560 - (int)player.y_position >= 5) player.y_position += 5;
            else if (560 - (int)player.y_position > 0 && 560 - (int)player.y_position < 5)
            {
                player.y_position = 560;
                player.on_ground = true;
            }
            else player.on_ground = true;
        }
        else if (howtoend == 0)
        {
            if (9580 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 9580 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 9580;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 53  || current_level == 79)
    {
        if (player.on_ground == false && howtoend == 0)
        {
            if ((int)player.x_position < 5340 || ((int)player.x_position >= 5540 && (int)player.x_position < 5640) || (int)player.x_position >= 5840)
            {
                if (2260 - (int)player.y_position >= 5) player.y_position += 5;
                else if (2260 - (int)player.y_position > 0 && 2260 - (int)player.y_position < 5)
                {
                    player.y_position = 2260;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else
            {
                if (2220 - (int)player.y_position >= 5) player.y_position += 5;
                else if (2220 - (int)player.y_position > 0 && 2220 - (int)player.y_position < 5)
                {
                    player.y_position = 2220;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
        }
        else if (howtoend == 0)
        {
            if ((int)player.x_position < 5340) howtoend = 1;
            else if ((int)player.x_position >= 5340 && (int)player.x_position < 5540) howtoend = 2;
            else if ((int)player.x_position >= 5540 && (int)player.x_position < 5640) howtoend = 3;
            else if ((int)player.x_position >= 5640 && (int)player.x_position < 5840) howtoend = 4;
            else
            {
                howtoend = 5;
                player.on_ground = false;
            }
        }
        else if (howtoend == 1)
        {
            if (5320 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5320 >= 4) player.x_speed = -4;
            else player.x_position = 5320;
            if ((int)player.x_position == 5320)
            {
                player.on_ground = false;
                howtoend = 6;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 2)
        {
            if ((int)player.x_position < 5420 && 5420 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5420 && player.x_position - 5420 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 5420;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 3)
        {
            if (5580 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5580 >= 4) player.x_speed = -4;
            else player.x_position = 5580;
            if ((int)player.x_position == 5580)
            {
                player.on_ground = false;
                howtoend = 6;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 4)
        {
            if (5700 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5700 >= 4) player.x_speed = -4;
            else player.x_position = 5700;
            if ((int)player.x_position == 5700)
            {
                player.on_ground = false;
                howtoend = 7;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 5)
        {
            if ((int)player.y_position > 2220) player.y_speed = -4;
            else if ((int)player.y_position < 2220 && player.y_speed < 4) player.y_speed++;
            else if ((int)player.y_position == 2220)
            {
                player.on_ground = true;
                player.y_speed = 0;
            }
            if ((int)player.x_position < 5700 && 5700 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5700 && player.x_position - 5700 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 5700;
                howtoend = 4;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 6)
        {
            if ((int)player.y_position > 2220) player.y_speed = -4;
            else if ((int)player.y_position < 2220 && player.y_speed < 4) player.y_speed++;
            else if ((int)player.y_position == 2220)
            {
                player.on_ground = true;
                player.y_speed = 0;
            }
            if ((int)player.x_position < 5420 && 5420 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5420 && player.x_position - 5420 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 5420;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 7)
        {
            if ((int)player.x_position > 5600) player.y_speed = -4;
            else if ((int)player.y_position != 2220 && player.y_speed < 4) player.y_speed++;
            else if ((int)player.y_position >= 2220)
            {
                player.y_position = 2220;
                player.y_speed = 0;
                player.on_ground = true;
            }
            if ((int)player.x_position < 5420 && 5420 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5420 && player.x_position - 5420 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 5420;
            }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
    }
    else if (current_level == 62 || current_level == 74)
    {
        if (player.on_ground == false)
        {
            if (((int)player.x_position >= 3400 && (int)player.x_position < 3500) || ((int)player.x_position >= 3720 && (int)player.x_position < 3820))
            {
                if (990 - (int)player.y_position >= 5) player.y_position += 5;
                else if (990 - (int)player.y_position > 0 && 990 - (int)player.y_position < 5)
                {
                    player.y_position = 990;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else
            {
                if (1020 - (int)player.y_position >= 5) player.y_position += 5;
                else if (1020 - (int)player.y_position > 0 && 1020 - (int)player.y_position < 5)
                {
                    player.y_position = 1020;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
        }
        else if (howtoend == 0)
        {
            if ((int)player.x_position >= 3400 && (int)player.x_position < 3500) howtoend = 1;
            else if ((int)player.x_position >= 3720 && (int)player.x_position < 3820) howtoend = 2;
            else howtoend = 3;
        }
        else if (howtoend == 1)
        {
            if (3450 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3450 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3450;
            }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 2)
        {
            if (3770 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3770 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3770;
            }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 3)
        {
            if (3600 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3600 >= 4) player.x_speed = -4;
            else
            {
                player.x_speed = 0;
                player.x_position = 3600;
            }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 80)
    {
        if (player.on_ground == false)
        {
            if ((int)player.x_position < 980 || (int)player.x_position > 1480)
            {
                if (260 - (int)player.y_position >= 5) player.y_position += 5;
                else if (260 - (int)player.y_position > 0 && 260 - (int)player.y_position < 5)
                {
                    player.y_position = 260;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else if ((int)player.x_position > 1180 && (int)player.x_position < 1280)
            {
                if (300 - (int)player.y_position >= 5) player.y_position += 5;
                else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 5)
                {
                    player.y_position = 300;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else if (((int)player.x_position > 1040 && (int)player.x_position < 1140) || ((int)player.x_position > 1320 && (int)player.x_position < 1420))
            {
                if (380 - (int)player.y_position >= 5) player.y_position += 5;
                else if (380 - (int)player.y_position > 0 && 380 - (int)player.y_position < 5)
                {
                    player.y_position = 380;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else if (((int)player.x_position > 1080 && (int)player.x_position < 1180) || ((int)player.x_position > 1280 && (int)player.x_position < 1380))
            {
                if (140 - (int)player.y_position >= 5) player.y_position += 5;
                else if (140 - (int)player.y_position > 0 && 140 - (int)player.y_position < 5)
                {
                    player.y_position = 140;
                    player.on_ground = true;
                }
                else player.on_ground = true;
            }
            else
            {
                if (520 - (int)player.y_position >= 5) player.y_position += 5;
                else if (520 - (int)player.y_position > 0 && 520 - (int)player.y_position < 5)
                {
                    player.y_position = 520;
                    player.on_ground = true;
                }
                else player.on_ground = true;
                if ((int)player.y_position >= 520)
                {
                    player.y_position = 520;
                    return;
                }
            }
        }
    }
}

void Game::create_actor(ActorType type, int x_position, int y_position, int direction, int time)
{
    Actor a = Actor(type, x_position, y_position, direction, time);
    actors.push_back(a);
}

int Game::in_player_view(Actor *a)
{
    if (a->x_position - player.x_position > -520 && a->x_position - player.x_position < 520 && a->y_position - player.y_position > -380 && a->y_position - player.y_position < 380) return 1;
    return 0;
}
