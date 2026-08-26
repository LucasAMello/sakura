void main_menu() {
    mainmenustart:
    while(osutatakaefadeout > 0) {
        draw_menu();
        osutatakaefadeout -= 15;
    }
    key_enter_rest = 1;
    key_f_rest = 1;
    do {
        while (speed_counter > 0) {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 105) player.y_position = 390;
                    else player.y_position -= 95;
                    key_rest = 10;
                }
                else key_rest--;
                player.timer = 0;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 390) player.y_position = 105;
                    else player.y_position += 95;
                    key_rest = 10;
                }
                else key_rest--;
                player.timer = 0;
            }
            else {
                if (key_rest > 0) key_rest = 0;
                player.timer++;
                if (player.timer == 105) player.timer = -90;
            }
            if (key[KEY_F] && key_f_rest == 0) {
                if (player.y_position == 105) menu = 1;
                else if (player.y_position == 200) menu = 2;
                else if (player.y_position == 295) menu = 3;
                else if (player.y_position == 390) menu = 4;
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0) {
                if (player.y_position == 105) menu = 1;
                else if (player.y_position == 200) menu = 2;
                else if (player.y_position == 295) menu = 3;
                else if (player.y_position == 390) menu = 4;
            }
            speed_counter--;
        }
        draw_menu();
        frame_counter++;
    } while (menu == 0);
    if (menu == 1) {
      //intro();    
      play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);  
    }
    else if (menu == 2) {
        if (!loadgame()) { menu = 0; goto mainmenustart; }
    }
    else if (menu == 3) {
        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); 
        while(osutatakaefadeout < 255) {
            draw_menu();
            osutatakaefadeout += 15;
        }
        player.x_position = 0;
        player.y_position = 0;
        player.imune = 0;
        while(osutatakaefadeout > 0) {
            draw_options();
            osutatakaefadeout -= 15;
        }
        myoptions();
        while(osutatakaefadeout < 255) {
            draw_options();
            osutatakaefadeout += 15;
        }
        menu = 0;
        player.y_position = 105;
        mainmenu = 0;
        goto mainmenustart;
    }  
    else if (menu == 4) {
        play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); 
        for(int i = 0; i < Map.height; i++)
            delete [] map[i];
        delete [] map;
        destroy_bitmap(scenario);
        destroy_bitmap(buffer);
        destroy_bitmap(background);
        destroy_bitmap(bakg);
        destroy_bitmap(title);
        destroy_bitmap(foreground);
        unload_datafile(mydatafile);
        return;
    }
    
}

void cselect() {
    cselectstart:
    key_enter_rest = 1;
    key_f_rest = 1;
    lastageportal[0] = lastageportal[1] = lastageportal[2] = lastageportal[3] = lastageportal[4] = lastageportal[5] = 0;
    do {
        while (speed_counter > 0) {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 0) player.y_position = 2;
                    else player.y_position--;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 2) player.y_position = 0;
                    else player.y_position++;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (key[KEY_RIGHT] && !key[KEY_LEFT] && player.y_position != 1) {
                if (key_rest == 0) {
                    if (player.x_position == 3) player.x_position = 0;
                    else player.x_position++;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (!key[KEY_RIGHT] && key[KEY_LEFT] && player.y_position != 1) {
                if (key_rest == 0) {
                    if (player.x_position == 0) player.x_position = 3;
                    else player.x_position--;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else {
                if (key_rest > 0) key_rest = 0;
            }
            if (key[KEY_F] && key_f_rest == 0) {
                if (player.y_position == 0) {
                    if (player.x_position == 0) { current_level = 10; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 1) { current_level = 40; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 2) { current_level = 50; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 3) { mainmenu = 1; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else if (player.y_position == 1) {
                    if (player.cards[0] == 1 && player.cards[1] == 1 && player.cards[2] == 1 && player.cards[3] == 1 && player.cards[4] == 1 && player.cards[5] == 1) {
                    current_level = 70; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else { stop_sample((SAMPLE *)mydatafile[DENY].dat); play_sample((SAMPLE *)mydatafile[DENY].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else {
                    if (player.x_position == 0) savegame();
                    else if (player.x_position == 1) { current_level = 30; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 2) { current_level = 60; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 3) { current_level = 20; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0) {
                if (player.y_position == 0) {
                    if (player.x_position == 0) { current_level = 10; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 1) { current_level = 40; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 2) { current_level = 50; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 3) { mainmenu = 1; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else if (player.y_position == 1) {
                    if (player.cards[0] == 1 && player.cards[1] == 1 && player.cards[2] == 1 && player.cards[3] == 1 && player.cards[4] == 1 && player.cards[5] == 1) {
                    current_level = 70; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else play_sample((SAMPLE *)mydatafile[DENY].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); 
                }
                else {
                    if (player.x_position == 0) savegame();
                    else if (player.x_position == 1) { current_level = 30; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 2) { current_level = 60; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position == 3) { current_level = 20; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
            }
            speed_counter--;
        }
        draw_cselect();
        frame_counter++;
    } while (current_level == 0 && mainmenu == 0);
    menu = 0;
    
}

void myoptions() {
    key_enter_rest = 1;
    key_f_rest = 1;
    do {
        while (speed_counter > 0) {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 0) player.y_position = 3;
                    else player.y_position--;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 3) player.y_position = 0;
                    else player.y_position++;
                    key_rest = 10;
                }
                else key_rest--;
            }
            else if (key[KEY_RIGHT] && !key[KEY_LEFT]) {
                if (key_rest == 0) {
                    if (player.y_position == 0) music_volume_set++;
                    else sound_volume_set++;
                    if (music_volume_set <= 0) { music_volume_set = 0; midi_pause(); }
                    else if (music_volume_set >= 1) { music_volume_set = 1; midi_resume(); }
                    if (sound_volume_set < 0) sound_volume_set = 0;
                    else if (sound_volume_set > 255) sound_volume_set = 255;
                    key_rest = 1;
                }
                else key_rest--;
            }
            else if (!key[KEY_RIGHT] && key[KEY_LEFT]) {
                if (key_rest == 0) {
                    if (player.y_position == 0) music_volume_set--;
                    else sound_volume_set--;
                    if (music_volume_set <= 0) { music_volume_set = 0; midi_pause(); }
                    else if (music_volume_set >= 1) { music_volume_set = 1; midi_resume(); }
                    if (sound_volume_set < 0) sound_volume_set = 0;
                    else if (sound_volume_set > 255) sound_volume_set = 255;
                    key_rest = 1;
                }
                else key_rest--;
            }
            else {
                if (key_rest > 0) key_rest = 0;
            }
            if (key[KEY_F] && key_f_rest == 0) {
                if (player.y_position == 2) { play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); set_controls(); }
                else if (player.y_position == 3) mainmenu = 1;
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0) {
                if (player.y_position == 2) { play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); set_controls(); }
                else if (player.y_position == 3) mainmenu = 1;
            }
            speed_counter--;
        }
        draw_options();
        frame_counter++;
    } while (mainmenu == 0);
    menu = 0;
}

void move_to_end() {
    if (current_level == 14 || current_level == 75) {
        if (player.on_ground == FALSE) {
            if (((int)(int)player.x_position >= 3100 && (int)(int)player.x_position < 3260) || ((int)(int)player.x_position >= 3460 && (int)(int)player.x_position < 3620)) {
                if (180 - (int)player.y_position >= 5) player.y_position += 5;
                else if (180 - (int)player.y_position > 0 && 180 - (int)player.y_position < 5)  { player.y_position = 180; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else if ((int)(int)player.x_position >= 3060 && (int)(int)player.x_position < 3660) {
                if (300 - (int)player.y_position >= 5) player.y_position += 5;
                else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 5) { player.y_position = 300; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else {
                if (480 - (int)player.y_position >= 5) player.y_position += 5;
                else if (480 - (int)player.y_position > 0 && 480 - (int)player.y_position < 5) { player.y_position = 480; player.on_ground = TRUE; }
                else player.on_ground = TRUE;    
                if ((int)player.y_position >= 480) { dead = 1; return; }
            }             
        }
        else if (howtoend == 0) {
            if ((int)player.x_position < 3100) howtoend = 1;
            else if ((int)player.x_position >= 3100 && (int)player.x_position < 3260) howtoend = 2;
            else if ((int)player.x_position >= 3260 && (int)player.x_position < 3460) howtoend = 3;
            else if ((int)player.x_position >= 3460 && (int)player.x_position < 3620) howtoend = 4;
            else howtoend = 5;
        }     
        else if (howtoend == 1) {
            if (3360 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3360 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3360; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 2) {
            if (3180 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3180 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3180; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 3) {
            if (3360 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3360 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3360; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 4) {
            if (3540 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3540 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3540; }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed <= 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 5) {
            if (3360 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3360 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3360; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 23 || current_level == 76) {
        if (player.on_ground == FALSE) {
            if (460 - (int)player.y_position >= 5) player.y_position += 5;
            else if (460 - (int)player.y_position > 0 && 460 - (int)player.y_position < 5)  { player.y_position = 460; player.on_ground = TRUE; }
            else player.on_ground = TRUE;     
        }
        else if (howtoend == 0) {
            if (5480 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5480 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 5480; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 32 || current_level == 77) {
        if (player.on_ground == FALSE) {
            if (400 - (int)player.y_position >= 5) player.y_position += 5;
            else if (400 - (int)player.y_position > 0 && 400 - (int)player.y_position < 5)  { player.y_position = 400; player.on_ground = TRUE; }
            else player.on_ground = TRUE;     
        }
        else if (howtoend == 0) {
            if (5460 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5460 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 5460; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 42  || current_level == 78) {
        if (player.on_ground == FALSE) {
            if (560 - (int)player.y_position >= 5) player.y_position += 5;
            else if (560 - (int)player.y_position > 0 && 560 - (int)player.y_position < 5)  { player.y_position = 560; player.on_ground = TRUE; }
            else player.on_ground = TRUE;     
        }
        else if (howtoend == 0) {
            if (9580 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 9580 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 9580; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 53  || current_level == 79) {
        if (player.on_ground == FALSE && howtoend == 0) {
            if ((int)player.x_position < 5340 || ((int)player.x_position >= 5540 && (int)player.x_position < 5640) || (int)player.x_position >= 5840) {
                if (2260 - (int)player.y_position >= 5) player.y_position += 5;
                else if (2260 - (int)player.y_position > 0 && 2260 - (int)player.y_position < 5)  { player.y_position = 2260; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else {
                if (2220 - (int)player.y_position >= 5) player.y_position += 5;
                else if (2220 - (int)player.y_position > 0 && 2220 - (int)player.y_position < 5) { player.y_position = 2220; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
        }
        else if (howtoend == 0) {
            if ((int)player.x_position < 5340) howtoend = 1;
            else if ((int)player.x_position >= 5340 && (int)player.x_position < 5540) howtoend = 2;
            else if ((int)player.x_position >= 5540 && (int)player.x_position < 5640) howtoend = 3;
            else if ((int)player.x_position >= 5640 && (int)player.x_position < 5840) howtoend = 4;
            else { howtoend = 5; player.on_ground = FALSE; }
        }
        else if (howtoend == 1) {   
            if (5320 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5320 >= 4) player.x_speed = -4;
            else player.x_position = 5320;
            if ((int)player.x_position == 5320) { player.on_ground = FALSE; howtoend = 6; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 2) {
            if ((int)player.x_position < 5420 && 5420 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5420 && player.x_position - 5420 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 5420; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 3) {
            if (5580 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5580 >= 4) player.x_speed = -4;
            else player.x_position = 5580;
            if ((int)player.x_position == 5580) { player.on_ground = FALSE; howtoend = 6; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 4) {
            if (5700 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 5700 >= 4) player.x_speed = -4;
            else player.x_position = 5700;
            if ((int)player.x_position == 5700) { player.on_ground = FALSE; howtoend = 7; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 5) {
            if ((int)player.y_position > 2220) player.y_speed = -4;
            else if ((int)player.y_position < 2220 && player.y_speed < 4) player.y_speed++;
            else if ((int)player.y_position == 2220) { player.on_ground = TRUE; player.y_speed = 0; }
            if ((int)player.x_position < 5700 && 5700 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5700 && player.x_position - 5700 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 5700; howtoend = 4; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 6) {
            if ((int)player.y_position > 2220) player.y_speed = -4;
            else if ((int)player.y_position < 2220 && player.y_speed < 4) player.y_speed++;
            else if ((int)player.y_position == 2220) { player.on_ground = TRUE; player.y_speed = 0; }
            if ((int)player.x_position < 5420 && 5420 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5420 && player.x_position - 5420 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 5420; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
        else if (howtoend == 7) {
            if ((int)player.x_position > 5600) player.y_speed = -4;
            else if ((int)player.y_position != 2220 && player.y_speed < 4) player.y_speed++;
            else if ((int)player.y_position >= 2220) { player.y_position = 2220; player.y_speed = 0; player.on_ground = TRUE; }
            if ((int)player.x_position < 5420 && 5420 - (int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position > 5420 && player.x_position - 5420 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 5420; }
            if (player.x_speed >= 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
            player.y_position += player.y_speed;
        }
    }   
    else if (current_level == 62 || current_level == 74) {
        if (player.on_ground == FALSE) {
            if (((int)player.x_position >= 3400 && (int)player.x_position < 3500) || ((int)player.x_position >= 3720 && (int)player.x_position < 3820)) {
                if (990 - (int)player.y_position >= 5) player.y_position += 5;
                else if (990 - (int)player.y_position > 0 && 990 - (int)player.y_position < 5)  { player.y_position = 990; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else {
                if (1020 - (int)player.y_position >= 5) player.y_position += 5;
                else if (1020 - (int)player.y_position > 0 && 1020 - (int)player.y_position < 5) { player.y_position = 1020; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }             
        }
        else if (howtoend == 0) {
            if ((int)player.x_position >= 3400 && (int)player.x_position < 3500) howtoend = 1;
            else if ((int)player.x_position >= 3720 && (int)player.x_position < 3820) howtoend = 2;
            else howtoend = 3;
        }     
        else if (howtoend == 1) {
            if (3450 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3450 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3450; }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 2) {
            if (3770 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3770 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3770; }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
        else if (howtoend == 3) {
            if (3600 - (int)(int)player.x_position >= 4) player.x_speed = 4;
            else if ((int)player.x_position - 3600 >= 4) player.x_speed = -4;
            else { player.x_speed = 0; player.x_position = 3600; }
            if (player.x_speed > 0) player.direction = 0;
            else if (player.x_speed < 0) player.direction = 1;
            player.x_position += player.x_speed;
        }
    }
    else if (current_level == 80) {
        if (player.on_ground == FALSE) {
            if ((int)player.x_position < 980 || (int)player.x_position > 1480) {
                if (260 - (int)player.y_position >= 5) player.y_position += 5;
                else if (260 - (int)player.y_position > 0 && 260 - (int)player.y_position < 5)  { player.y_position = 260; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else if ((int)player.x_position > 1180 && (int)player.x_position < 1280) {
                if (300 - (int)player.y_position >= 5) player.y_position += 5;
                else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 5) { player.y_position = 300; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else if (((int)player.x_position > 1040 && (int)player.x_position < 1140) || ((int)player.x_position > 1320 && (int)player.x_position < 1420)) {
                if (380 - (int)player.y_position >= 5) player.y_position += 5;
                else if (380 - (int)player.y_position > 0 && 380 - (int)player.y_position < 5) { player.y_position = 380; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else if (((int)player.x_position > 1080 && (int)player.x_position < 1180) || ((int)player.x_position > 1280 && (int)player.x_position < 1380)) {
                if (140 - (int)player.y_position >= 5) player.y_position += 5;
                else if (140 - (int)player.y_position > 0 && 140 - (int)player.y_position < 5) { player.y_position = 140; player.on_ground = TRUE; }
                else player.on_ground = TRUE;
            }
            else {
                if (520 - (int)player.y_position >= 5) player.y_position += 5;
                else if (520 - (int)player.y_position > 0 && 520 - (int)player.y_position < 5) { player.y_position = 520; player.on_ground = TRUE; }
                else player.on_ground = TRUE;    
                if ((int)player.y_position >= 520) { dead = 1; return; }
            }             
        }
    }
}

void set_controls() {
    int keycount;
    bool keyflag;
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Up Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_up = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Down Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_down = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Right Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_right = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Left Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_left = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Jump Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_jump = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Fire Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_fire = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Card", 320, 232, makecol(0,0,0), -1); 
    textout_centre_ex(screen, font, "Change(Right) Key", 320, 240, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_weapon1 = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Card", 320, 232, makecol(0,0,0), -1); 
    textout_centre_ex(screen, font, "Change(Left) Key", 320, 240, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_weapon2 = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Start Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_menu = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Press Quit Key", 320, 236, makecol(0,0,0), -1); 
    keyflag = TRUE;
    while(keyflag) { keycount = KEY_MAX; while(keycount--) {
            if(key[keycount]) {
                player.key_quit = keycount;
                keyflag = FALSE; break; } }
    }
    do { keyflag = FALSE; keycount = KEY_MAX;  while(keycount--) { if(key[keycount]) { keyflag = TRUE; break; } } } while(keyflag);
    clear_keybuf();
}


void gamemenu() {
    int xs;
    gamemenustart:
    while(osutatakaefadeout > 0) {
        drawgamemenu();
        osutatakaefadeout -= 15;
    }
    key_enter_rest = 1;
    key_f_rest = 1;
    do {
        while (speed_counter > 0) {
          if (menuposx == 0) {  
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_UP] && !key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 0) player.y_position = 5;
                    else player.y_position--;
                    key_rest = 10;
                    make:
                    if (player.y_position == 0 && player.x_position == 1) player.y_position = 5;
                    if (player.y_position == 0) {
                        if (player.x_position == 1 && player.cards[0] == 0) { player.y_position--; goto make; }
                    }
                    else if (player.y_position == 1) {
                        if (player.x_position == 0 && player.cards[2] == 0) { player.y_position--; goto make; }
                        if (player.x_position == 1 && player.cards[4] == 0) { player.y_position--; goto make; }
                    }
                    else if (player.y_position == 2) {
                         if (player.x_position == 0 && player.cards[5] == 0) { player.y_position--; goto make; }
                        if (player.x_position == 1 && player.cards[3] == 0) { player.y_position--; goto make; }
                    }
                    else if (player.y_position == 3) {
                        if (player.x_position == 0 && player.cards[1] == 0) { player.y_position--; goto make; }
                    }
                }
                else key_rest--;
            }
            else if (!key[KEY_UP] && key[KEY_DOWN]) {
                if (key_rest == 0) {
                    if (player.y_position == 5) player.y_position = 0;
                    else player.y_position++;
                    key_rest = 10;
                    makesure:
                    if (player.y_position == 0) {
                        if (player.x_position == 1 && player.cards[0] == 0) { player.y_position++; goto makesure; }
                    }
                    else if (player.y_position == 1) {
                        if (player.x_position == 0 && player.cards[2] == 0) { player.y_position++; goto makesure; }
                        if (player.x_position == 1 && player.cards[4] == 0) { player.y_position++; goto makesure; }
                    }
                    else if (player.y_position == 2) {
                         if (player.x_position == 0 && player.cards[5] == 0) { player.y_position++; goto makesure; }
                        if (player.x_position == 1 && player.cards[3] == 0) { player.y_position++; goto makesure; }
                    }
                    else if (player.y_position == 3) {
                        if (player.x_position == 0 && player.cards[1] == 0) { player.y_position++; goto makesure; }
                    }
                }
                else key_rest--;
            }
            else if (key[KEY_RIGHT] && !key[KEY_LEFT] && player.y_position != 4) {
                if (key_rest == 0) {
                    if (player.x_position == 1) player.x_position = 0;
                    else player.x_position++;
                    key_rest = 10;
                    checkcheck:
                    if (player.y_position == 0) {
                        if (player.x_position == 1 && player.cards[0] == 0) { player.y_position++; goto checkcheck; }
                    }
                    else if (player.y_position == 1) {
                        if (player.x_position == 0 && player.cards[2] == 0) { player.y_position--; goto checkcheck; }
                        if (player.x_position == 1 && player.cards[4] == 0) { player.y_position++; goto checkcheck; }
                    }
                    else if (player.y_position == 2) {
                         if (player.x_position == 0 && player.cards[5] == 0) { player.y_position--; goto checkcheck; }
                        if (player.x_position == 1 && player.cards[3] == 0) { player.y_position++; goto checkcheck; }
                    }
                    else if (player.y_position == 3) {
                        if (player.x_position == 0 && player.cards[1] == 0) { player.y_position--; goto checkcheck; }
                    }
                }
                else key_rest--;
            }
            else if (!key[KEY_RIGHT] && key[KEY_LEFT] && player.y_position != 4) {
                if (key_rest == 0) {
                    if (player.x_position == 0) player.x_position = 1;
                    else player.x_position--;
                    key_rest = 10;
                    check:
                    if (player.y_position == 0) {
                        if (player.x_position == 1 && player.cards[0] == 0) { player.y_position++; goto check; }
                    }
                    else if (player.y_position == 1) {
                        if (player.x_position == 0 && player.cards[2] == 0) { player.y_position--; goto check; }
                        if (player.x_position == 1 && player.cards[4] == 0) { player.y_position++; goto check; }
                    }
                    else if (player.y_position == 2) {
                         if (player.x_position == 0 && player.cards[5] == 0) { player.y_position--; goto check; }
                        if (player.x_position == 1 && player.cards[3] == 0) { player.y_position++; goto check; }
                    }
                    else if (player.y_position == 3) {
                        if (player.x_position == 0 && player.cards[1] == 0) { player.y_position--; goto check; }
                    }
                }
                else key_rest--;
            }
            else {
                if (key_rest > 0) key_rest = 0;
            }
            if (key[KEY_F] && key_f_rest == 0) {
                if (player.y_position == 0) {
                    if (player.x_position == 0 && fire_key == 0) player.current_weapon = 1;
                    else if (player.x_position == 1 && fire_key == 0) player.current_weapon = 2;
                }
                else if (player.y_position == 1) {
                    if (player.x_position == 0 && fire_key == 0) player.current_weapon = 4;
                    else if (player.x_position == 1 && fire_key == 0) player.current_weapon = 5;
                }
                else if (player.y_position == 2) {
                    if (player.x_position == 0 && fire_key == 0)player.current_weapon = 7;
                    else if (player.x_position == 1 && fire_key == 0) player.current_weapon = 6;
                }
                else if (player.y_position == 3) {
                    if (player.x_position == 0 && fire_key == 0) player.current_weapon = 3;
                    else if (player.x_position == 1) { characterscreen = 1; play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else if (player.y_position == 4) {
                    while(osutatakaefadeout < 255) {
                        drawgamemenu();
                        osutatakaefadeout += 15;
                    }
                    player.x_position = 0;
                    player.y_position = 0;
                    player.imune = 0;
                    while(osutatakaefadeout > 0) {
                        draw_options();
                        osutatakaefadeout -= 15;
                    }
                    myoptions();
                    while(osutatakaefadeout < 255) {
                        draw_options();
                        osutatakaefadeout += 15;
                    }
                    mainmenu = 0;
                    player.y_position = 0;
                    player.x_position = 0;
                    goto gamemenustart;
                }
                else if (player.y_position == 5) {
                    if (player.x_position == 0) { key_f_rest = 1; gamemenustat = 1; }
                    else if (player.x_position == 1) { xs = 10; menuposx += 10; }
                }
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0) {
                key_enter_rest = 1; gamemenustat = 1;
            }
            speed_counter--;
          }
          else if (menuposx == 640) {
            if (!key[KEY_ENTER]) key_enter_rest = 0;
            if (!key[KEY_F]) key_f_rest = 0;
            if (key[KEY_F] && key_f_rest == 0) {
                xs = -10; menuposx -= 10;
            }
            else if (key[KEY_ENTER] && key_enter_rest == 0) {
                key_enter_rest = 1; gamemenustat = 1;
            }
            speed_counter--;  
          }
          else {
              menuposx += xs;
              speed_counter--;
          }
        }
        drawgamemenu();
        frame_counter++;
    } while (gamemenustat == 0 && characterscreen == 0);
    gamemenustat = 0;
    
}

void savegame() {
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Saving...", 320, 236, makecol(0,0,0), -1); 
    fsav.open("save.sav");
    char dihtc[18];
    for(int x = 0; x < 51; x+=3) {
        if (player.cards[x] == 1 && player.cards[x+1] == 1 && player.cards[x+2] == 1) dihtc[x/3] = '1';
        else if (player.cards[x] == 1 && player.cards[x+1] == 1) dihtc[x/3] = '2';
        else if (player.cards[x] == 1 && player.cards[x+2] == 1) dihtc[x/3] = '3';
        else if (player.cards[x+1] == 1 && player.cards[x+2] == 1) dihtc[x/3] = '4';
        else if (player.cards[x] == 1) dihtc[x/3] = '5';
        else if (player.cards[x+1] == 1) dihtc[x/3] = '6';
        else if (player.cards[x+2] == 1) dihtc[x/3] = '7';
        else dihtc[x/3] = '8';
        fsav << dihtc[x/3];
    }
    if (player.cards[51] == 1 && something == 1 && something2 == 1) dihtc[17] = '1';
    else if (player.cards[51] == 1 && something == 1) dihtc[17] = '2';
    else if (player.cards[51] == 1 && something2 == 1) dihtc[17] = '3';
    else if (something == 1 && something2 == 1) dihtc[17] = '4';
    else if (player.cards[51] == 1) dihtc[17] = '5';
    else if (something == 1) dihtc[17] = '6';
    else if (something2 == 1) dihtc[17] = '7';
    else dihtc[17] = '8';
    fsav << dihtc[17];
    fsav.close();
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Game Saved.", 320, 236, makecol(0,0,0), -1); 
    rest(200);
}

int loadgame() {
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Loading...", 320, 236, makecol(0,0,0), -1); 
    for(int y = 0; y < 52; y++) {
        player.cards[y] = 0;        
    }
    something = 0;
    something2 = 0;
    player.score = 0;
    fload.open("save.sav");
    if (fload.peek() == EOF) {
        draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
        textout_centre_ex(screen, font, "File not found.", 320, 236, makecol(0,0,0), -1);
        play_sample((SAMPLE *)mydatafile[DENY].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        while(key[KEY_ENTER] || key[KEY_F]);
        while(!key[KEY_ENTER] && !key[KEY_F]);
        while(key[KEY_ENTER] || key[KEY_F]);
        rest(100);
        return 0;
    }
    play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    char dihtc[18];
    for(int z = 0; z < 18; z++) {
        dihtc[z] = fload.get();        
    }
    for(int x = 0; x < 51; x+=3) {
        if (dihtc[x/3] == '1') { player.cards[x] = 1; player.cards[x+1] = 1; player.cards[x+2] = 1; player.score+=3; }
        else if (dihtc[x/3] == '2') { player.cards[x] = 1; player.cards[x+1] = 1; player.score += 2; }
        else if (dihtc[x/3] == '3') { player.cards[x] = 1; player.cards[x+2] = 1; player.score += 2; }
        else if (dihtc[x/3] == '4') { player.cards[x+1] = 1; player.cards[x+2] = 1; player.score += 2; }
        else if (dihtc[x/3] == '5') { player.cards[x] = 1; player.score += 1; }
        else if (dihtc[x/3] == '6') { player.cards[x+1] = 1; player.score += 1; }
        else if (dihtc[x/3] == '7') { player.cards[x+2] = 1; player.score += 1; }
    }
    if (dihtc[17] == '1') { player.cards[51] = 1; something = 1; something2 = 1; player.score += 1; }
    else if (dihtc[17] == '2') { player.cards[51] = 1; something = 1; player.score += 1; }
    else if (dihtc[17] == '3') { player.cards[51] = 1; something2 = 1; player.score += 1; }
    else if (dihtc[17] == '4') { something = 1; something2 = 1; }
    else if (dihtc[17] == '5') { player.cards[51] = 1; player.score += 1; }
    else if (dihtc[17] == '6') { something = 1; }
    else if (dihtc[17] == '7') { something2 = 1; }
    if (player.score == 10) player.hpmax = 16;
    else if (player.score == 20) player.hpmax = 17;
    else if (player.score == 30) player.hpmax = 18;
    else if (player.score == 40) player.hpmax = 19;
    else if (player.score == 52) player.hpmax = 20;
    fload.close();
    draw_sprite(screen, (BITMAP*)mydatafile[WINDOW].dat, 240, 190);
    textout_centre_ex(screen, font, "Game Loaded.", 320, 236, makecol(0,0,0), -1);
    rest(200);
    return 1;
}

void myend() {
    int script_timer = 0;
    itsover = 0;
    screenx = 0;
    sparkmandril = 0;
    if (buffer != 0) destroy_bitmap(buffer);
    if (background != 0) destroy_bitmap(background);
    if (scenario != 0) destroy_bitmap(scenario);
    if (bakg != 0) destroy_bitmap(bakg);
    doorrecord = -1;
    create_bubbles = 160;
    bakg = load_bitmap("bg.bmp", NULL);
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
    endtext = (BITMAP *) mydatafile[CREDITS1].dat;
    endtextx = 0; endtextw = 313;
    rest(5000);
    midi_pause();
    rest(5000);
    if (stage_music != NULL) destroy_midi(stage_music);
    stage_music = load_midi("Ending.mid");
    play_midi(stage_music, 0);
    if (music_volume_set == 0) midi_pause();
    do {
        while (speed_counter > 0) {
		script_timer++;
		if (script_timer % 8 == 0) {
            if (player.x_speed != 0) {
                player.move++;
                if (player.frame == PLAYER_MOVING05 || player.frame == PLAYER_MOVING04 || player.frame == PLAYER_MOVING03 || player.frame == PLAYER_MOVING02 || player.frame == PLAYER_MOVING01) {
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
		} }
		screenx++; screeny+=2;
        if (screenx % 20 == 0) player.x_position--;
		if (screenx >= create_bubbles) { screenx = 0; }
		if (screeny == 600) endtextx = 1;
		else if (screeny >= 2800) { osutatakaefadeout++; }
		if (endtextx > 0) {
            if (screeny < 2600) endtextx++;
            else endtextx--;
            if (endtextx >= 255) endtextx = 255;
        }
        speed_counter--;
        }
        drawend();
        frame_counter++;
    } while (yeahyeah != 6666 || !key[KEY_ENTER]);
}

void drawend() {
    if (yeahyeah == 6666) {
        if (osutatakaefadeout > 0) osutatakaefadeout--;
        screenx = screeny = 0;
        draw_sprite( buffer, background, 0, 0);
        draw_sprite( buffer, (BITMAP *) mydatafile[THEEND].dat, 458, 439);
        draw_sprite( buffer, (BITMAP *) mydatafile[THANKS].dat, 125, 180);
        set_trans_blender(0,0,0,0); draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
    }
    else {
    if (light_level > 0) { yeahyeah++; if (yeahyeah % 3 == 0) light_level--; }
    if (yeahyeah < 0 && osutatakaefadeout > 0) { osutatakaefadeout--; if (osutatakaefadeout == 0) yeahyeah += 10; }
    draw_sprite( buffer, background, -160 + (screeny / 20), 0);
    if (sparkmandril == 20) { 
        draw_sprite_h_flip( buffer, background, -160 + (screeny / 20), 150);
        draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position, (int)player.y_position);
    }
    draw_sprite( buffer, scenario, -1 * create_bubbles + screenx, 380 - sparkmandril);
    draw_sprite( buffer, scenario, 0 * create_bubbles + screenx, 380 - sparkmandril);
    draw_sprite( buffer, scenario, 1 * create_bubbles + screenx, 380 - sparkmandril);
    draw_sprite( buffer, scenario, 2 * create_bubbles + screenx, 380 - sparkmandril);
    draw_sprite( buffer, scenario, 3 * create_bubbles + screenx, 380 - sparkmandril);
    if (create_bubbles == 120) draw_sprite( buffer, scenario, 4 * create_bubbles + screenx, 380);
    if (create_bubbles == 120) draw_sprite( buffer, scenario, 5 * create_bubbles + screenx, 380);
    if (sparkmandril == 0) draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position, (int)player.y_position);
    set_trans_blender(0,0,0,endtextx);
    draw_trans_sprite(buffer, endtext, (int)((640 - endtextw) / 2), 60);
    if (light_level > 0) { set_trans_blender(255,255,255,0); draw_lit_sprite(screen, buffer, 0, 0, light_level); }
    else { set_trans_blender(0,0,0,0); draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout); }
    if (osutatakaefadeout >= 255) {
      if (yeahyeah >= 10) { yeahyeah = -1;
        if (buffer != 0) destroy_bitmap(buffer);
        if (background != 0) destroy_bitmap(background);
        if (scenario != 0) destroy_bitmap(scenario);
        if (bakg != 0) destroy_bitmap(bakg);
        create_bubbles = 160;
        osutatakaefadeout = 255;
        bakg = load_bitmap("bg2.bmp", NULL);
        background = create_bitmap(800, 480);
        scenario = (BITMAP *) mydatafile[ENDING2].dat;
        buffer = create_bitmap(640, 480);
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        endtext = (BITMAP *) mydatafile[CREDITS2].dat;
        endtextx = 0; endtextw = 145;
        rest(1000);
        screenx = screeny = 0;
        speed_counter = 0;
      }
      else if (yeahyeah >= 9) { yeahyeah -= 11;
        if (buffer != 0) destroy_bitmap(buffer);
        if (background != 0) destroy_bitmap(background);
        if (scenario != 0) destroy_bitmap(scenario);
        if (bakg != 0) destroy_bitmap(bakg);
        create_bubbles = 160;
        osutatakaefadeout = 255;
        bakg = load_bitmap("bg4.bmp", NULL);
        background = create_bitmap(800, 480);
        scenario = (BITMAP *) mydatafile[ENDING3].dat;
        buffer = create_bitmap(640, 480);
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 608, 0);
        endtext = (BITMAP *) mydatafile[CREDITS3].dat;
        endtextx = 0; endtextw = 238;
        rest(1000);
        screenx = screeny = 0;
        speed_counter = 0;
      }
      else if (yeahyeah >= 8) { yeahyeah -= 11;
        if (buffer != 0) destroy_bitmap(buffer);
        if (background != 0) destroy_bitmap(background);
        if (scenario != 0) destroy_bitmap(scenario);
        if (bakg != 0) destroy_bitmap(bakg);
        create_bubbles = 160;
        osutatakaefadeout = 255;
        bakg = load_bitmap("bg5.bmp", NULL);
        background = create_bitmap(800, 480);
        scenario = (BITMAP *) mydatafile[ENDING4].dat;
        buffer = create_bitmap(640, 480);
        clear_to_color(background, makecol(0,0,161));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 400, 0);
        sparkmandril = 20;
        endtext = (BITMAP *) mydatafile[CREDITS4].dat;
        endtextx = 0; endtextw = 299;
        rest(1000);
        screenx = screeny = 0;
        speed_counter = 0;
      }
      else if (yeahyeah >= 7) { yeahyeah -= 11;
        if (buffer != 0) destroy_bitmap(buffer);
        if (background != 0) destroy_bitmap(background);
        if (scenario != 0) destroy_bitmap(scenario);
        if (bakg != 0) destroy_bitmap(bakg);
        create_bubbles = 160;
        osutatakaefadeout = 255;
        bakg = load_bitmap("bg.bmp", NULL);
        background = create_bitmap(800, 480);
        scenario = (BITMAP *) mydatafile[ENDING5].dat;
        buffer = create_bitmap(640, 480);
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        sparkmandril = 0;
        endtext = (BITMAP *) mydatafile[CREDITS5].dat;
        endtextx = 0; endtextw = 380;
        rest(1000);
        screenx = screeny = 0;
        speed_counter = 0;
      }
      else if (yeahyeah >= 6) { yeahyeah -= 11;
        if (buffer != 0) destroy_bitmap(buffer);
        if (background != 0) destroy_bitmap(background);
        if (scenario != 0) destroy_bitmap(scenario);
        if (bakg != 0) destroy_bitmap(bakg);
        create_bubbles = 120;
        osutatakaefadeout = 255;
        bakg = load_bitmap("bg6.bmp", NULL);
        background = create_bitmap(800, 480);
        scenario = (BITMAP *) mydatafile[ENDING6].dat;
        buffer = create_bitmap(640, 480);
        clear_to_color(background, makecol(15,0,0));
        draw_sprite(background, bakg, 0, 0);
        draw_sprite(background, bakg, 640, 0);
        endtext = (BITMAP *) mydatafile[CREDITS6].dat;
        endtextx = 0; endtextw = 281;
        rest(1000);
        screenx = screeny = 0;
        speed_counter = 0;
      }
      else if (yeahyeah >= 5) { yeahyeah = 6666;
        if (buffer != 0) destroy_bitmap(buffer);
        if (background != 0) destroy_bitmap(background);
        if (scenario != 0) destroy_bitmap(scenario);
        if (bakg != 0) destroy_bitmap(bakg);
        osutatakaefadeout = 255;
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
