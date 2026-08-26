void initialize_wall(int framex, int framey, int type, int w, int h, int x, int y) {
    if (type == 20) {
        walls[number_of_walls].type = 20;
        walls[number_of_walls].active = 1;
        walls[number_of_walls].width = w; walls[number_of_walls].height = h;
        walls[number_of_walls].x_position = x; walls[number_of_walls].y_position = y;
        masked_blit((BITMAP*)mydatafile[texture].dat, scenario, framex, framey, x, y, w, h);
        number_of_walls++;
    }
    if (type == 10) {
        walls[number_of_walls].type = 10;
        walls[number_of_walls].active = 1;
        walls[number_of_walls].width = w; walls[number_of_walls].height = h;
        walls[number_of_walls].x_position = x; walls[number_of_walls].y_position = y;
        masked_blit((BITMAP*)mydatafile[texture].dat, foreground, framex, framey, x, y, w, h);
        number_of_walls++;
    }
    if (type == 11) {
        walls[number_of_walls].type = 11;
        walls[number_of_walls].active = 1;
        walls[number_of_walls].width = w; walls[number_of_walls].height = h;
        walls[number_of_walls].x_position = x; walls[number_of_walls].y_position = y;
        masked_blit((BITMAP*)mydatafile[texture].dat, scenario, framex - 20, framey, x, y, w, h);
        masked_blit((BITMAP*)mydatafile[texture].dat, foreground, framex, framey, x, y, w, h);
        number_of_walls++;
    }
    if (type == 12) {
        walls[number_of_walls].type = 12;
        walls[number_of_walls].active = 1;
        walls[number_of_walls].width = w; walls[number_of_walls].height = h;
        walls[number_of_walls].x_position = x; walls[number_of_walls].y_position = y;
        masked_blit((BITMAP*)mydatafile[texture].dat, scenario, framex, framey, x, y, w, h);
        masked_blit((BITMAP*)mydatafile[texture].dat, foreground, framex - 40, framey, x, y, w, h);
        number_of_walls++;
    }
    else if (type == 1) {
        blit((BITMAP*)mydatafile[texture].dat, scenario, framex, framey, x, y, w, h);
    }
    else if (type == 2) {
        blit((BITMAP*)mydatafile[texture].dat, foreground, framex, framey, x, y, w, h);
    }
}

void initialize_sprite(int type, int x_position, int y_position, int direction, int time) {
    int sprite_loop = number_of_sprites;
    if (type == 1) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1;
        sprites[sprite_loop].width = 10; sprites[sprite_loop].height = 10;
        sprites[sprite_loop].frame = YELLOW_TOSKO_SHOT;
        if (direction == 0) sprites[sprite_loop].x_position = (int)player.x_position + 40;
        else sprites[sprite_loop].x_position = (int)player.x_position - 21;
        sprites[sprite_loop].y_position = (int)player.y_position + 35;
        if (direction == 0) sprites[sprite_loop].x_speed = 5;
        else sprites[sprite_loop].x_speed = -5;
        sprites[sprite_loop].direction = player.direction;
        play_sample((SAMPLE *)mydatafile[TIRO1].dat, (int)(205 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 2) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 2;
        sprites[sprite_loop].width = 65; sprites[sprite_loop].height = 32;
        sprites[sprite_loop].frame = WIND_SHOT01;
        if (direction == 0) sprites[sprite_loop].x_position = player.x_position + 25;
        else sprites[sprite_loop].x_position = player.x_position - 15;
        sprites[sprite_loop].y_position = player.y_position + 20;
        if (direction == 0) sprites[sprite_loop].x_speed = 5;
        else sprites[sprite_loop].x_speed = -5;
        sprites[sprite_loop].direction = player.direction;
        sprites[sprite_loop].timer = 1;
        play_sample((SAMPLE *)mydatafile[TIRO2].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 3) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 3;
        sprites[sprite_loop].width = 30; sprites[sprite_loop].height = 30;
        sprites[sprite_loop].frame = SHADOWSHOT;
        if (direction == 0) sprites[sprite_loop].x_position = (int)player.x_position + 50;
        else sprites[sprite_loop].x_position = (int)player.x_position - 21;
        sprites[sprite_loop].y_position = (int)player.y_position + 0;
        if (direction == 0) sprites[sprite_loop].x_speed = 5;
        else sprites[sprite_loop].x_speed = -5;
        sprites[sprite_loop].direction = player.direction;
        sprites[sprite_loop].y_speed = 3;
        play_sample((SAMPLE *)mydatafile[TIRO3].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 4) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 4;
        sprites[sprite_loop].width = 16; sprites[sprite_loop].height = 16;
        sprites[sprite_loop].frame = ZOCK01;
        if (direction == 0) sprites[sprite_loop].x_position = (int)player.x_position + 40;
        else sprites[sprite_loop].x_position = (int)player.x_position - 21;
        sprites[sprite_loop].y_position = (int)player.y_position + 35;
        if (direction == 0) sprites[sprite_loop].x_speed = 5;
        else sprites[sprite_loop].x_speed = -5;
        sprites[sprite_loop].direction = player.direction;
        play_sample((SAMPLE *)mydatafile[TIRO4].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 5) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 5;
        sprites[sprite_loop].width = 29; sprites[sprite_loop].height = 29;
        sprites[sprite_loop].frame = WATERSHOT;
        if (direction == 0) sprites[sprite_loop].x_position = (int)player.x_position + 40;
        else sprites[sprite_loop].x_position = (int)player.x_position - 21;
        sprites[sprite_loop].y_position = (int)player.y_position + 20;
        if (direction == 0) sprites[sprite_loop].x_speed = 5;
        else sprites[sprite_loop].x_speed = -5;
        sprites[sprite_loop].y_speed = -1;
        sprites[sprite_loop].direction = player.direction;
        play_sample((SAMPLE *)mydatafile[TIRO5].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 6) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 6;
        sprites[sprite_loop].width = 34; sprites[sprite_loop].height = 24;
        sprites[sprite_loop].frame = HADOUKEN01;
        if (direction == 0) sprites[sprite_loop].x_position = (int)player.x_position + 40;
        else sprites[sprite_loop].x_position = (int)player.x_position - 21;
        sprites[sprite_loop].y_position = (int)player.y_position + 28;
        if (direction == 0) sprites[sprite_loop].x_speed = -8;
        else sprites[sprite_loop].x_speed = +8;
        sprites[sprite_loop].direction = player.direction;
        play_sample((SAMPLE *)mydatafile[TIRO6].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 7) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 7;
        sprites[sprite_loop].width = 47; sprites[sprite_loop].height = 19;
        sprites[sprite_loop].frame = ICYATTACK04;
        if (direction == 0) sprites[sprite_loop].x_position = (int)player.x_position + 40;
        else sprites[sprite_loop].x_position = (int)player.x_position - 21;
        sprites[sprite_loop].y_position = (int)player.y_position + 30;
        sprites[sprite_loop].direction = player.direction;
        play_sample((SAMPLE *)mydatafile[TIRO7].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 10) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 10;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 40;
        sprites[sprite_loop].frame = REDBALL01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 0.8;
        sprites[sprite_loop].hit_points_left = 5;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 1;
    }
    else if (type == 11) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 11;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 60;
        sprites[sprite_loop].frame = MOLA_FELIZ;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = 3;
        sprites[sprite_loop].hit_points_left = 6;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].biba = y_position;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 12) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 12;
        sprites[sprite_loop].width = 60;
        sprites[sprite_loop].height = 60;
        sprites[sprite_loop].frame = GREEN_TURRET;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 10;
        sprites[sprite_loop].strength = 5;
        sprites[sprite_loop].direction = direction;
    }
    else if (type == 13) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 13;
        sprites[sprite_loop].timer = 20;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 10;
        sprites[sprite_loop].frame = TURRET_SHOT;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 4;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 4;
        sprites[sprite_loop].direction = direction;
        if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[TURRET].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 14) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 14;
        sprites[sprite_loop].width = 37;
        sprites[sprite_loop].height = 33;
        sprites[sprite_loop].frame = PIRIKITO;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = 0;
        sprites[sprite_loop].hit_points_left = 3;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].biba = y_position;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 15) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 15;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 51;
        sprites[sprite_loop].frame = GHOST01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 5;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 16) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 16;
        sprites[sprite_loop].width = 1;
        sprites[sprite_loop].height = 1;
        sprites[sprite_loop].frame = NULO;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = time;
        sprites[sprite_loop].x_speed = direction;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = 0;
        sprites[sprite_loop].timer = 40;
    }
    else if (type == 17) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 17;
        sprites[sprite_loop].width = 70;
        sprites[sprite_loop].height = 30;
        sprites[sprite_loop].frame = GHOSTMASK01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 5;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].hit_points_left = 2;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].action_state = 160;
    }
    else if (type == 61) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 61;
        sprites[sprite_loop].width = 1;
        sprites[sprite_loop].height = 1;
        sprites[sprite_loop].frame = NULO;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = time;
        sprites[sprite_loop].x_speed = direction;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = 1;
        sprites[sprite_loop].timer = 40;
    }
    else if (type == 62) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 62;
        sprites[sprite_loop].width = 70;
        sprites[sprite_loop].height = 30;
        sprites[sprite_loop].frame = GHOSTMASK01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 5;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].hit_points_left = 2;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].action_state = 160;
    }
    else if (type == 63) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 40;
        sprites[sprite_loop].frame = WALLMAGIC;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 18) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 18;
        sprites[sprite_loop].width = 48;
        sprites[sprite_loop].height = 22;
        sprites[sprite_loop].frame = GUILHOTINA;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].biba = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 6;
    }
    else if (type == 19) {
        if (direction == 0) {
            sprites[sprite_loop].active = 1;
            sprites[sprite_loop].type = 19;
            sprites[sprite_loop].width = 40;
            sprites[sprite_loop].height = 20;
            sprites[sprite_loop].frame = WALLTURRET;
            sprites[sprite_loop].x_position = x_position;
            sprites[sprite_loop].y_position = y_position;
            sprites[sprite_loop].direction = direction;
            sprites[sprite_loop].hit_points_left = 5;
            sprites[sprite_loop].strength = 2;
            sprites[sprite_loop].timer = time;
        }
        else if (direction == 1) {
            sprites[sprite_loop].active = 1;
            sprites[sprite_loop].type = 19;
            sprites[sprite_loop].width = 20;
            sprites[sprite_loop].height = 40;
            sprites[sprite_loop].frame = WALLTURRET;
            sprites[sprite_loop].x_position = x_position;
            sprites[sprite_loop].y_position = y_position;
            sprites[sprite_loop].direction = direction;
            sprites[sprite_loop].hit_points_left = 5;
            sprites[sprite_loop].strength = 2;
            sprites[sprite_loop].rotate_factor = 192;
            sprites[sprite_loop].timer = time;
        }
        else if (direction == 2) {
            sprites[sprite_loop].active = 1;
            sprites[sprite_loop].type = 19;
            sprites[sprite_loop].width = 20;
            sprites[sprite_loop].height = 40;
            sprites[sprite_loop].frame = WALLTURRET;
            sprites[sprite_loop].x_position = x_position;
            sprites[sprite_loop].y_position = y_position;
            sprites[sprite_loop].direction = direction;
            sprites[sprite_loop].hit_points_left = 5;
            sprites[sprite_loop].strength = 2;
            sprites[sprite_loop].rotate_factor = 64;
            sprites[sprite_loop].timer = time;
        }
    }
    else if (type == 20) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 20;
        sprites[sprite_loop].width = 8;
        sprites[sprite_loop].height = 8;
        sprites[sprite_loop].frame = WTSHOT01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 2;
        if (direction == 0) { sprites[sprite_loop].x_speed = -10; sprites[sprite_loop].y_speed = 10; }
        else if (direction == 3) { sprites[sprite_loop].x_speed = 10; sprites[sprite_loop].y_speed = 10; }
        else if (direction == 1) { sprites[sprite_loop].x_speed = 10; sprites[sprite_loop].y_speed = -10; }
        else if (direction == 4) { sprites[sprite_loop].x_speed = 10; sprites[sprite_loop].y_speed = 10; }
        else if (direction == 2) { sprites[sprite_loop].x_speed = -10; sprites[sprite_loop].y_speed = -10; }
        else if (direction == 5) { sprites[sprite_loop].x_speed = -10; sprites[sprite_loop].y_speed = 10; }
        else if (direction == 6) sprites[sprite_loop].x_speed = -16;
        else if (direction == 7) sprites[sprite_loop].x_speed = 16;
        else if (direction == 8) sprites[sprite_loop].y_speed = 12;
        if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[WTS].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 21) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 21;
        sprites[sprite_loop].width = 64;
        sprites[sprite_loop].height = 70;
        sprites[sprite_loop].frame = EWULMACHINE01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].hit_points_left = 12;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 22) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 22;
        sprites[sprite_loop].width = 25;
        sprites[sprite_loop].height = 13;
        sprites[sprite_loop].frame = EWULMISSILE01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].x_speed = -8;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 4;
        if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[EWULMISSILE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 23) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 23;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 51;
        sprites[sprite_loop].frame = ORANGE01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 5;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 24) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 24;
        sprites[sprite_loop].frame = SHOCKER01;
        sprites[sprite_loop].width = 37;
        sprites[sprite_loop].height = 47;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 6;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].direction = direction;
        if (direction == 1 || direction == 3) {
            sprites[sprite_loop].width = 47;
            sprites[sprite_loop].height = 37;
        }
        sprites[sprite_loop].timer = time;
    }
    else if (type == 25) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 25;
        sprites[sprite_loop].frame = SHOCKING01;
        sprites[sprite_loop].width = 22;
        sprites[sprite_loop].height = 17;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 0;
        sprites[sprite_loop].direction = direction;
        if (direction == 1 || direction == 3) {
            sprites[sprite_loop].width = 17;
            sprites[sprite_loop].height = 22;
        }
        sprites[sprite_loop].timer = time;
    }
    else if (type == 26) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 26;
        sprites[sprite_loop].frame = ZOCK01;
        sprites[sprite_loop].width = 16;
        sprites[sprite_loop].height = 16;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].direction = direction;
        if (direction == 0) sprites[sprite_loop].y_speed = 10;
        else if (direction == 1) sprites[sprite_loop].x_speed = -10;
        else if (direction == 2) sprites[sprite_loop].y_speed = -10;
        else if (direction == 3) sprites[sprite_loop].x_speed = 10;
        sprites[sprite_loop].timer = time;
        if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[TIRO4].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 27) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 27;
        sprites[sprite_loop].frame = THUNDERRAIO01;
        sprites[sprite_loop].width = 64;
        sprites[sprite_loop].height = 320;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        play_sample((SAMPLE *)mydatafile[BIGTHUNDER].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 28) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = THUNDER_SHOT01;
        sprites[sprite_loop].width = 34;
        sprites[sprite_loop].height = 512;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 3;
        play_sample((SAMPLE *)mydatafile[THUNDERSOUND].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 29) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 29;
        sprites[sprite_loop].width = 37;
        sprites[sprite_loop].height = 0;
        sprites[sprite_loop].frame = RESETTI;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 30) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 30;
        sprites[sprite_loop].width = 36;
        sprites[sprite_loop].height = 0;
        sprites[sprite_loop].frame = SEAHORSE1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].biba = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 3;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 31) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 31;
        sprites[sprite_loop].width = 1;
        sprites[sprite_loop].height = 1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].timer = 0;
        sprites[sprite_loop].frame = NULO;
    }
    else if (type == 32) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 32;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 3;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].timer = time;
        sprites[sprite_loop].strength = 2;
        bibinhalinda = rand() % 4;
        if (bibinhalinda == 0) { sprites[sprite_loop].frame = EWULFISH_11; sprites[sprite_loop].biba = 1; }
        else if (bibinhalinda == 1) { sprites[sprite_loop].frame = EWULFISH_21; sprites[sprite_loop].biba = 2; }
        else if (bibinhalinda == 2) { sprites[sprite_loop].frame = EWULFISH_31; sprites[sprite_loop].biba = 3; }
        else if (bibinhalinda == 3) { sprites[sprite_loop].frame = EWULFISH_41; sprites[sprite_loop].biba = 4; }
    }
    else if (type == 33) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 33;
        sprites[sprite_loop].frame = EWULOSTRAPT2;
        sprites[sprite_loop].width = 43;
        sprites[sprite_loop].height = 27;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 2;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 34) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 34;
        sprites[sprite_loop].frame = EWULOSTRAPT1;
        sprites[sprite_loop].width = 36;
        sprites[sprite_loop].height = 14;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 35) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 35;
        sprites[sprite_loop].frame = EWULOSTRABALLB;
        sprites[sprite_loop].width = 12;
        sprites[sprite_loop].height = 12;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 36) {
        if (direction == 10) direction = 1;
        else if (direction == 11) direction = 0;
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = WATER_PONTA1;
        if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].width = 33;
        else sprites[sprite_loop].width = 33;
        sprites[sprite_loop].height = 30;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        if (direction == 0) sprites[sprite_loop].x_speed = -32;
        else sprites[sprite_loop].x_speed = 32;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].animation_state = time;
        play_sample((SAMPLE *)mydatafile[TURTLEJATO].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 37) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FLAMETHROWER1;
        sprites[sprite_loop].width = 80;
        sprites[sprite_loop].height = 40;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 0;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 38) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FLAMETHROWER2;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 80;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 0;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 39) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FLAMES01;
        sprites[sprite_loop].width = 90;
        sprites[sprite_loop].height = 58;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 40) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FLAMES11;
        sprites[sprite_loop].width = 58;
        sprites[sprite_loop].height = 90;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 41) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FLAMEMET1;
        sprites[sprite_loop].width = 42;
        sprites[sprite_loop].height = 33;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 2;
        sprites[sprite_loop].y_speed = 1;
        sprites[sprite_loop].hit_points_left = 5;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 42) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FLAMEMET1;
        sprites[sprite_loop].width = 42;
        sprites[sprite_loop].height = 33;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 2;
        sprites[sprite_loop].hit_points_left = 5;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 43) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FIRE1;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 39;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = 8;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
        if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(128 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 44) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = time;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 4;
    }
    else if (type == 45) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 25;
        sprites[sprite_loop].frame = EWUL_SQUID01;
        sprites[sprite_loop].height = 59;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 3;
        sprites[sprite_loop].strength = 2;
        sprites[sprite_loop].biba = y_position;
        sprites[sprite_loop].action_state = 0;
    }
    else if (type == 46) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].timer = rand() % 4;
        if (sprites[sprite_loop].timer == 0) sprites[sprite_loop].frame = SFIRE1;
        else if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = SFIRE2;
        else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = SFIRE3;
        else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SFIRE4;
        sprites[sprite_loop].width = 25;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 16 + (rand() % 12);
        sprites[sprite_loop].y_speed = -3 + (rand() % 4);
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
        play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 47) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = HADOUKEN01;
        sprites[sprite_loop].width = 31;
        sprites[sprite_loop].height = 24;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 40;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 7;
    }
    else if (type == 48) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = SLASH01;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 40;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 20;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
        play_sample((SAMPLE *)mydatafile[FIRESLASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 49) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = SLASH02;
        sprites[sprite_loop].width = 27;
        sprites[sprite_loop].height = 37;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 17;
        sprites[sprite_loop].y_speed = 8;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
        play_sample((SAMPLE *)mydatafile[FIRESLASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 50) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = ICEMET01;
        sprites[sprite_loop].width = 55;
        sprites[sprite_loop].height = 43;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 2;
        sprites[sprite_loop].hit_points_left = 4;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 51) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = ICE01;
        sprites[sprite_loop].width = 12;
        sprites[sprite_loop].height = 30;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = 2;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 52) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = ICE02;
        sprites[sprite_loop].width = 16;
        sprites[sprite_loop].height = 32;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].y_speed = 2;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 53) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        if (direction == 0) sprites[sprite_loop].frame = ICESPIKE;
        else sprites[sprite_loop].frame = SHADOWSPIKE;
        sprites[sprite_loop].width = time;
        sprites[sprite_loop].height = 29;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 20;
    }
    else if (type == 54) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        if (time == 0) {
            sprites[sprite_loop].frame = ICENEEDLE01;
            sprites[sprite_loop].width = 9;
            sprites[sprite_loop].height = 7;
            sprites[sprite_loop].x_speed = 20;
            sprites[sprite_loop].y_speed = 0;
        }
        else if (time == 1) {
            sprites[sprite_loop].frame = ICENEEDLE02;
            sprites[sprite_loop].width = 11;
            sprites[sprite_loop].height = 11;
            sprites[sprite_loop].x_speed = 15;
            sprites[sprite_loop].y_speed = 10;
        }
        else if (time == 2) {
            sprites[sprite_loop].frame = ICENEEDLE03;
            sprites[sprite_loop].width = 8;
            sprites[sprite_loop].height = 12;
            sprites[sprite_loop].x_speed = 10;
            sprites[sprite_loop].y_speed = 15;
        }
        else if (time == 3) {
            sprites[sprite_loop].frame = ICENEEDLE04;
            sprites[sprite_loop].width = 9;
            sprites[sprite_loop].height = 12;
            sprites[sprite_loop].x_speed = 0;
            sprites[sprite_loop].y_speed = 20;
        }
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 1;
    }
    else if (type == 55) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = PUMPKIN01;
        sprites[sprite_loop].width = 24;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 4;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 56) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        if (time == 0) {
            sprites[sprite_loop].frame = ICYATTACK01;
            sprites[sprite_loop].width = 19;
            sprites[sprite_loop].height = 47;
            sprites[sprite_loop].x_speed = 0;
            sprites[sprite_loop].y_speed = 24;
        }
        else if (time == 1) {
            sprites[sprite_loop].frame = ICYATTACK02;
            sprites[sprite_loop].width = 25;
            sprites[sprite_loop].height = 40;
            sprites[sprite_loop].x_speed = 8;
            sprites[sprite_loop].y_speed = 14;
        }
        else if (time == 2) {
            sprites[sprite_loop].frame = ICYATTACK03;
            sprites[sprite_loop].width = 40;
            sprites[sprite_loop].height = 25;
            sprites[sprite_loop].x_speed = 16;
            sprites[sprite_loop].y_speed = 8;
        }
        else if (time == 3) {
            sprites[sprite_loop].frame = ICYATTACK04;
            sprites[sprite_loop].width = 47;
            sprites[sprite_loop].height = 19;
            sprites[sprite_loop].x_speed = 24;
            sprites[sprite_loop].y_speed = 0;
        }
        else if (time == 4) {
            sprites[sprite_loop].frame = ICYATTACK05;
            sprites[sprite_loop].width = 40;
            sprites[sprite_loop].height = 25;
            sprites[sprite_loop].x_speed = 16;
            sprites[sprite_loop].y_speed = -8;
        }
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 57) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = WATERSHOTSMALL;
        sprites[sprite_loop].width = 14;
        sprites[sprite_loop].height = 14;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        if (direction == 0) sprites[sprite_loop].x_speed = 8;
        else sprites[sprite_loop].x_speed = -8;
        sprites[sprite_loop].y_speed = -4;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
    }
    else if (type == 58) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = WATERSHOTSMALL;
        sprites[sprite_loop].width = 14;
        sprites[sprite_loop].height = 14;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        if (direction == 0) sprites[sprite_loop].x_speed = time * -1;
        else sprites[sprite_loop].x_speed = time;
        sprites[sprite_loop].y_speed = 10;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
    }
    else if (type == 59) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = PAINTING1;
        sprites[sprite_loop].width = 100;
        sprites[sprite_loop].height = 100;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 60) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = EWULARMOR1;
        sprites[sprite_loop].width = 63;
        sprites[sprite_loop].height = 70;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].biba = time;
    }
    else if (type == 64) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = PENA;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 9;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
        play_sample((SAMPLE *)mydatafile[PENASOUND].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 65) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = CARDHOLDER;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 60;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].x_speed = 9;
        sprites[sprite_loop].biba = time;
    }
    else if (type == 66) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = SANDMORRO1;
        sprites[sprite_loop].width = 46;
        sprites[sprite_loop].height = 36;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].biba = time;
    }
    else if (type == 67) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = ICEHOLDER1;
        sprites[sprite_loop].width = 40;
        sprites[sprite_loop].height = 50;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = ICEHOLDER2;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].x_speed = 200;
    }
    else if (type == 69) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = CARD01;
        sprites[sprite_loop].width = 22;
        sprites[sprite_loop].height = 36;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].strength = 255;
        if (direction == 0) sprites[sprite_loop].y_speed = 10;
        else sprites[sprite_loop].y_speed = 0;
    }
    else if (type == 70) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 70;
        sprites[sprite_loop].width = 10;
        sprites[sprite_loop].height = 12;
        sprites[sprite_loop].frame = BOLHAS;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].y_speed = -6;
    }
    else if (type == 71) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 71;
        sprites[sprite_loop].width = 1;
        sprites[sprite_loop].height = 1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].timer = 0;
        sprites[sprite_loop].frame = NULO;
    }
    else if (type == 72) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 72;
        sprites[sprite_loop].width = 36;
        sprites[sprite_loop].height = 0;
        sprites[sprite_loop].frame = SEAHORSE1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].biba = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 3;
        sprites[sprite_loop].strength = 2;
    }
    else if (type == 73) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 65;
        sprites[sprite_loop].height = 120;
        sprites[sprite_loop].frame = PORTAL1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 74) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 65;
        sprites[sprite_loop].height = 120;
        sprites[sprite_loop].frame = PORTAL1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 75) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 48;
        sprites[sprite_loop].height = 46;
        sprites[sprite_loop].frame = LASTSMALL1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].biba = 0;
        play_sample((SAMPLE *)mydatafile[LASTS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 76) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = THUNDER_SHOT01;
        sprites[sprite_loop].width = 34;
        sprites[sprite_loop].height = 512;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 3;
        play_sample((SAMPLE *)mydatafile[THUNDERSOUND].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 77) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FIRE1;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 39;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].direction = time;
        play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 78) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].frame = FIRE1;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 39;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].direction = time;
        play_sample((SAMPLE *)mydatafile[FIREYFLAME].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 79) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        if (time == 0) {
            sprites[sprite_loop].frame = ICYATTACK01;
            sprites[sprite_loop].width = 19;
            sprites[sprite_loop].height = 47;
            sprites[sprite_loop].x_speed = 0;
            sprites[sprite_loop].y_speed = 24;
        }
        else if (time == 1) {
            sprites[sprite_loop].frame = ICYATTACK02;
            sprites[sprite_loop].width = 25;
            sprites[sprite_loop].height = 40;
            sprites[sprite_loop].x_speed = 10;
            sprites[sprite_loop].y_speed = 12;
        }
        else if (time == 2) {
            sprites[sprite_loop].frame = ICYATTACK03;
            sprites[sprite_loop].width = 40;
            sprites[sprite_loop].height = 25;
            sprites[sprite_loop].x_speed = 17;
            sprites[sprite_loop].y_speed = 7;
        }
        else if (time == 3) {
            sprites[sprite_loop].frame = ICYATTACK04;
            sprites[sprite_loop].width = 47;
            sprites[sprite_loop].height = 19;
            sprites[sprite_loop].x_speed = 24;
            sprites[sprite_loop].y_speed = 0;
        }
        else if (time == 4) {
            sprites[sprite_loop].frame = ICYATTACK05;
            sprites[sprite_loop].width = 40;
            sprites[sprite_loop].height = 25;
            sprites[sprite_loop].x_speed = 17;
            sprites[sprite_loop].y_speed = -7;
        }
        else if (time == 5) {
            sprites[sprite_loop].frame = ICYATTACK06;
            sprites[sprite_loop].width = 25;
            sprites[sprite_loop].height = 40;
            sprites[sprite_loop].x_speed = 10;
            sprites[sprite_loop].y_speed = -12;
        }
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
        play_sample((SAMPLE *)mydatafile[TIRO7].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 113) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 113;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].width = 25;
        sprites[sprite_loop].height = 25;
        sprites[sprite_loop].timer = 0;
        sprites[sprite_loop].frame = SHOT_13_1;
        sprites[sprite_loop].hit_points_left = 1;
        play_sample((SAMPLE *)mydatafile[ANIM13].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 200) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 200;
        sprites[sprite_loop].width = 10;
        sprites[sprite_loop].height = 10;
        sprites[sprite_loop].frame = RECOVERY_S;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = -1;
        sprites[sprite_loop].y_speed = 3;
    }
    else if (type == 201) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 201;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].frame = RECOVERY_M;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].strength = -3;
        sprites[sprite_loop].y_speed = 3;
    }else if (type == 202) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 202;
        sprites[sprite_loop].width = 37;
        sprites[sprite_loop].height = 31;
        sprites[sprite_loop].frame = VIDA;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].hit_points_left = 1;
        sprites[sprite_loop].y_speed = 3;
    }
    else if (type == 301) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 301;
        sprites[sprite_loop].width = 10;
        sprites[sprite_loop].height = 10;
        sprites[sprite_loop].frame = PARTICLES01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = -6;
        sprites[sprite_loop].y_speed = 0;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 302) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 302;
        sprites[sprite_loop].width = 9;
        sprites[sprite_loop].height = 9;
        sprites[sprite_loop].frame = PARTICLES02;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 1;
        sprites[sprite_loop].y_speed = -3;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 303) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 303;
        sprites[sprite_loop].width = 13;
        sprites[sprite_loop].height = 11;
        sprites[sprite_loop].frame = PARTICLES03;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = -4;
        sprites[sprite_loop].y_speed = 1;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 304) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 304;
        sprites[sprite_loop].width = 13;
        sprites[sprite_loop].height = 12;
        sprites[sprite_loop].frame = PARTICLES04;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].x_speed = 7;
        sprites[sprite_loop].y_speed = -1;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 305) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 305;
        sprites[sprite_loop].width = 15;
        sprites[sprite_loop].height = 15;
        sprites[sprite_loop].frame = ICEDESTROY;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].direction = direction;
        if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_speed = rand() % 2 + 1;
        else sprites[sprite_loop].x_speed = (rand() % 2 + 1) * -1;
        sprites[sprite_loop].y_speed = ((rand() % 7) + 4) * -1;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 400) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 400;
        sprites[sprite_loop].width = 40; sprites[sprite_loop].height = 40;
        sprites[sprite_loop].frame = WINDMILL0;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].biba = time;
    }
    else if (type == 401) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 401;
        sprites[sprite_loop].width = 30; sprites[sprite_loop].height = 200;
        sprites[sprite_loop].frame = IRON_DOOR;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].biba = time;
    }
    else if (type == 402) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 402;
        sprites[sprite_loop].width = 26; sprites[sprite_loop].height = 120;
        sprites[sprite_loop].frame = POSTE;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
    }
    else if (type == 403) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 403;
        sprites[sprite_loop].width = 96; sprites[sprite_loop].height = 96;
        sprites[sprite_loop].frame = LUZ;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
    }
    else if (type == 404) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 404;
        sprites[sprite_loop].width = 42; sprites[sprite_loop].height = 44;
        sprites[sprite_loop].frame = SPLASH1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        play_sample((SAMPLE *)mydatafile[SPLASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (type == 500) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 500;
        sprites[sprite_loop].width = 20; sprites[sprite_loop].height = 20;
        if (time == 0) sprites[sprite_loop].frame = BLOCK;
        else if (time == 1) sprites[sprite_loop].frame = ICEBLOCK1;
        else if (time == 2) sprites[sprite_loop].frame = ICEBLOCK2;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
    }
    else if (type == 501) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 501;
        sprites[sprite_loop].width = 8; sprites[sprite_loop].height = 21;
        sprites[sprite_loop].frame = HA;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].timer = time;
    }
    else if (type == 999) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 999;
        sprites[sprite_loop].width = 30;
        sprites[sprite_loop].height = 140;
        sprites[sprite_loop].timer = time;
        sprites[sprite_loop].frame = PORTA2;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 1000) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1000;
        sprites[sprite_loop].width = 30;
        sprites[sprite_loop].height = 100;
        sprites[sprite_loop].timer = time;
        sprites[sprite_loop].frame = PORTA1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 1001) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1001;
        sprites[sprite_loop].width = 83;
        sprites[sprite_loop].height = 117;
        sprites[sprite_loop].frame = BIRD1;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].action_state = 0;
        sprites[sprite_loop].timer = 0;
        sprites[sprite_loop].biba = time;
    }
    else if (type == 1002) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1002;
        sprites[sprite_loop].width = 50;
        sprites[sprite_loop].height = 50;
        sprites[sprite_loop].frame = SHADOW01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].x_speed = -15;
        sprites[sprite_loop].y_speed = -15;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].action_state = 0;
        sprites[sprite_loop].timer = 0;
    }
    else if (type == 1003) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1003;
        sprites[sprite_loop].width = 50;
        sprites[sprite_loop].height = 50;
        sprites[sprite_loop].frame = SHADOWBALL;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].x_speed = 15;
        sprites[sprite_loop].y_speed = 15;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].action_state = 0;
        sprites[sprite_loop].timer = 0;
    }
    else if (type == 1004) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1004;
        sprites[sprite_loop].width = 98;
        sprites[sprite_loop].height = 69;
        sprites[sprite_loop].frame = THUNDER01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].strength = 3;
    }
    else if (type == 1005) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 128;
        sprites[sprite_loop].height = 60;
        sprites[sprite_loop].frame = TURTLE;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].strength = 4;
    }
    else if (type == 1006) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 129;
        sprites[sprite_loop].height = 106;
        sprites[sprite_loop].frame = SCALED01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 4;
    }
    else if (type == 1007) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 154;
        sprites[sprite_loop].height = 65;
        sprites[sprite_loop].frame = ICYSHADOW02;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 4;
    }
    else if (type == 1008) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 80;
        sprites[sprite_loop].height = 109;
        sprites[sprite_loop].frame = LASTBOSS;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 30;
        sprites[sprite_loop].direction = direction;
        sprites[sprite_loop].strength = 3;
        sprites[sprite_loop].biba = 255;
    }
    else if (type == 1010) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1010;
        sprites[sprite_loop].width = 80; sprites[sprite_loop].height = 200;
        sprites[sprite_loop].frame = NULO;
        sprites[sprite_loop].timer = time;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
    }
    else if (type == 1011) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = type;
        sprites[sprite_loop].width = 360;
        sprites[sprite_loop].height = 40;
        sprites[sprite_loop].timer = time;
        sprites[sprite_loop].frame = NULO;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
    }
    else if (type == 1111) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1111;
        sprites[sprite_loop].frame = NULO;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
    }
    else if (type == 1666) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 1666;
        sprites[sprite_loop].frame = CARD01;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].biba = time;
        sprites[sprite_loop].strength = 255;
    }
    else if (type == 2000) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 2000;
        sprites[sprite_loop].width = 80;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].frame = DESTROYABLEPAREDE;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 2001) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 2001;
        sprites[sprite_loop].width = 20;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].frame = DESTROYABLEPAREDE2;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 2002) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 2002;
        sprites[sprite_loop].width = 60;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].frame = ICETOP;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 2003) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 2003;
        sprites[sprite_loop].width = 60;
        sprites[sprite_loop].height = 20;
        sprites[sprite_loop].frame = ICETOP2;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    else if (type == 2004) {
        sprites[sprite_loop].active = 1;
        sprites[sprite_loop].type = 2004;
        sprites[sprite_loop].width = 62;
        sprites[sprite_loop].height = 120;
        if (time == 0) sprites[sprite_loop].frame = PPP1;
        else if (time == 1) sprites[sprite_loop].frame = PPP2;
        else if (time == 2) sprites[sprite_loop].frame = PPP3;
        else if (time == 3) sprites[sprite_loop].frame = PPP4;
        else if (time == 4) sprites[sprite_loop].frame = PPP5;
        else if (time == 5) sprites[sprite_loop].frame = PPP6;
        sprites[sprite_loop].x_position = x_position;
        sprites[sprite_loop].y_position = y_position;
        sprites[sprite_loop].hit_points_left = 1;
    }
    number_of_sprites++;
}

void animation(int sprite_number) {
    if (sprites[sprite_number].type == 1) {
        sprites[sprite_number].type = 100;
        sprites[sprite_number].y_position -= 5;
        sprites[sprite_number].x_position -= 5;
        sprites[sprite_number].width = 20;
        sprites[sprite_number].height = 20;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = SHOT_0_1;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
        player.shots--;
    }
    else if (sprites[sprite_number].type == 2) {
        sprites[sprite_number].type = 101;
        sprites[sprite_number].width = 65;
        sprites[sprite_number].height = 36;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].strength = 255;
    }
    else if (sprites[sprite_number].type == 3) {
        sprites[sprite_number].type = 102;
        sprites[sprite_number].width = 30;
        sprites[sprite_number].height = 30;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].strength = 255;
        sprites[sprite_number].frame = SHADOWSHOT;
    }
    else if (sprites[sprite_number].type == 4) {
        sprites[sprite_number].active = 0;
        player.shots--;
    }
    else if (sprites[sprite_number].type == 5) {
        sprites[sprite_number].type = 104;
        sprites[sprite_number].timer = 0;
        if (sprites[sprite_number].biba == 1) {
          if (sprites[sprite_number].strength == 0) {
            sprites[sprite_number].frame = WATERSHOTHIT1;
            sprites[sprite_number].action_state = 1;
            if (sprites[sprite_number].direction == 0) sprites[sprite_number].x_position += 7;
            sprites[sprite_number].width = 22;
            sprites[sprite_number].height = 29;
          }
          else {
            initialize_sprite(58, (int)sprites[sprite_number].x_position, (int)sprites[sprite_number].y_position, sprites[sprite_number].direction, 13);
            initialize_sprite(58, (int)sprites[sprite_number].x_position, (int)sprites[sprite_number].y_position + 15, sprites[sprite_number].direction, 8);
          }
        }
        else if (sprites[sprite_number].biba == 2) {
          if (sprites[sprite_number].strength == 0) {
            sprites[sprite_number].frame = WATERSHOTHIT4;
            sprites[sprite_number].action_state = 2;
            sprites[sprite_number].y_position += 7;
            sprites[sprite_number].width = 29;
            sprites[sprite_number].height = 22;
          }
          else {
            initialize_sprite(57, (int)sprites[sprite_number].x_position, (int)sprites[sprite_number].y_position, 0, 0);
            initialize_sprite(57, (int)sprites[sprite_number].x_position + 15, (int)sprites[sprite_number].y_position, 1, 0);
          }
        }
        else if (sprites[sprite_number].biba == 3) {
          if (sprites[sprite_number].strength == 0) {
            sprites[sprite_number].frame = WATERSHOTHIT7;
            sprites[sprite_number].action_state = 3;
            //sprites[sprite_number].y_position += 7;
            sprites[sprite_number].width = 29;
            sprites[sprite_number].height = 22;
          }
          else {
            initialize_sprite(57, (int)sprites[sprite_number].x_position, (int)sprites[sprite_number].y_position + 16, 0, 666);
            initialize_sprite(57, (int)sprites[sprite_number].x_position + 15, (int)sprites[sprite_number].y_position + 16, 1, 666);
          }
        }
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
        play_sample((SAMPLE *)mydatafile[SPLAASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (sprites[sprite_number].type == 7) {
        sprites[sprite_number].active = 0;
        sprites[sprite_number].type = 106;
        initialize_sprite(305, (int)sprites[sprite_number].x_position + (rand() % 15), (int)sprites[sprite_number].y_position + (rand() % 5), 1, 0);
        initialize_sprite(305, (int)sprites[sprite_number].x_position + (rand() % 15), (int)sprites[sprite_number].y_position + (rand() % 5), 0, 0);
        initialize_sprite(305, (int)sprites[sprite_number].x_position + (rand() % 15), (int)sprites[sprite_number].y_position + (rand() % 5), 1, 0);
        initialize_sprite(305, (int)sprites[sprite_number].x_position + (rand() % 15), (int)sprites[sprite_number].y_position + (rand() % 5), 0, 0);
        if (inpl(sprite_number)) play_sample((SAMPLE *)mydatafile[ICEANIM].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (sprites[sprite_number].type == 13 || sprites[sprite_number].type == 22) {
        sprites[sprite_number].type = 113;
        sprites[sprite_number].x_position += 10;
        sprites[sprite_number].y_position -= 7;
        sprites[sprite_number].width = 25;
        sprites[sprite_number].height = 25;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = SHOT_13_1;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
        if (inpl(sprite_number)) play_sample((SAMPLE *)mydatafile[ANIM13].dat, (int)(150 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (sprites[sprite_number].type == 12) {
        if (rand() % 4 == 0) initialize_sprite(201, (int)sprites[sprite_number].x_position + 20, (int)sprites[sprite_number].y_position + 20, 0, 0);
        else if (rand() % 4 == 0) initialize_sprite(202, (int)sprites[sprite_number].x_position + 20, (int)sprites[sprite_number].y_position + 10, 0, 0);
        sprites[sprite_number].type = 112;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = TOLETED_1;
        initialize_sprite(301, (int)sprites[sprite_number].x_position, (int)sprites[sprite_number].y_position, 1, 0);
        initialize_sprite(302, (int)sprites[sprite_number].x_position + 60, (int)sprites[sprite_number].y_position, 0, 0);
        initialize_sprite(303, (int)sprites[sprite_number].x_position, (int)sprites[sprite_number].y_position + 20, 1, 0);
        initialize_sprite(304, (int)sprites[sprite_number].x_position + 60, (int)sprites[sprite_number].y_position + 20, 0, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
        play_sample((SAMPLE *)mydatafile[ANIM60].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (sprites[sprite_number].type == 10) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 41) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 42) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 45) {
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_position -= 8;
        sprites[sprite_number].y_position += 2;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 11) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 25, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 32) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
        sprites[sprite_number].y_position -= 8;
    }
    else if (sprites[sprite_number].type == 14) {
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 15) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 20, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 17) {
        if (rand() % 5 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 5, (int)sprites[sprite_number].y_position + 5, 0, 0);
        else if (rand() % 5 == 0) initialize_sprite(202, (int)sprites[sprite_number].x_position + 5, (int)sprites[sprite_number].y_position + 5, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 72) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].x_position -= 5;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 62) {
        if (rand() % 5 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 35, (int)sprites[sprite_number].y_position + 5, 0, 0);
        else if (rand() % 5 == 0) initialize_sprite(202, (int)sprites[sprite_number].x_position + 5, (int)sprites[sprite_number].y_position + 5, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_position += 30;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 19) {
        //if (rand() % 5 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 5, (int)sprites[sprite_number].y_position + 5, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].y_position -= 10;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 21) {
        if (rand() % 4 == 0) initialize_sprite(201, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        else if (rand() % 4 == 0) initialize_sprite(201, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 667;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = DA600;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
        play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    }
    else if (sprites[sprite_number].type == 23) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 24) {
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 30) {
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].x_position -= 5;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 20) {
        sprites[sprite_number].type = 120;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = WTSHOT02;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 50) {
        sprites[sprite_number].x_position += 7;
        if (rand() % 3 == 0) initialize_sprite(200, (int)sprites[sprite_number].x_position + 10, (int)sprites[sprite_number].y_position + 15, 0, 0);
        initialize_sprite(54, (int)sprites[sprite_number].x_position - 7, (int)sprites[sprite_number].y_position + 22, 0, 0);
        initialize_sprite(54, (int)sprites[sprite_number].x_position - 4, (int)sprites[sprite_number].y_position + 9, 0, 1);
        initialize_sprite(54, (int)sprites[sprite_number].x_position + 5, (int)sprites[sprite_number].y_position + 1, 0, 2);
        initialize_sprite(54, (int)sprites[sprite_number].x_position + 15, (int)sprites[sprite_number].y_position - 1, 0, 3);
        initialize_sprite(54, (int)sprites[sprite_number].x_position + 27, (int)sprites[sprite_number].y_position + 1, 1, 2);
        initialize_sprite(54, (int)sprites[sprite_number].x_position + 34, (int)sprites[sprite_number].y_position + 9, 1, 1);
        initialize_sprite(54, (int)sprites[sprite_number].x_position + 39, (int)sprites[sprite_number].y_position + 22, 1, 0);
        sprites[sprite_number].type = 666;
        sprites[sprite_number].timer = 0;
                sprites[sprite_number].frame = DA400; play_sample((SAMPLE *)mydatafile[ANIM40].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
    else if (sprites[sprite_number].type == 301 || sprites[sprite_number].type == 302 || sprites[sprite_number].type == 303 || sprites[sprite_number].type == 304) {
        sprites[sprite_number].type = 310;
        sprites[sprite_number].timer = 0;
        sprites[sprite_number].frame = PARTICLEDESTROY1;
        sprites[sprite_number].x_speed = 0;
        sprites[sprite_number].y_speed = 0;
    }
}

void destroysprite(int spritee) {
   for (int x = spritee; x <= number_of_sprites + 1; x++) {
     sprites[x].active = sprites[x + 1].active;
     sprites[x].type = sprites[x + 1].type;
     sprites[x].timer = sprites[x + 1].timer;
     sprites[x].animation_state = sprites[x + 1].animation_state;
     sprites[x].width = sprites[x + 1].width;
     sprites[x].height = sprites[x + 1].height;
     sprites[x].action_state = sprites[x + 1].action_state;
     sprites[x].frame = sprites[x + 1].frame;
     sprites[x].hit_points_left = sprites[x + 1].hit_points_left;
     sprites[x].x_position = sprites[x + 1].x_position;
     sprites[x].y_position = sprites[x + 1].y_position;
     sprites[x].x_speed = sprites[x + 1].x_speed;
     sprites[x].y_speed = sprites[x + 1].y_speed;
     sprites[x].direction = sprites[x + 1].direction;
     sprites[x].rotate_factor = sprites[x + 1].rotate_factor;
     sprites[x].biba = sprites[x + 1].biba;
     sprites[x].strength = sprites[x + 1].strength;
   }  
   number_of_sprites--;
}

void destroysprite() {
   for (int x = 0; sprites[x].active == 1 ; x++) {
     sprites[x].active = 0;
     sprites[x].type = 0;
     sprites[x].timer = 0;
     sprites[x].animation_state = 0;
     sprites[x].width = 0;
     sprites[x].height = 0;
     sprites[x].action_state = 0;
     sprites[x].frame = 0;
     sprites[x].hit_points_left = 0;
     sprites[x].x_position = 0;
     sprites[x].y_position = 0;
     sprites[x].x_speed = 0;
     sprites[x].y_speed = 0;
     sprites[x].direction = 0;
     sprites[x].rotate_factor = 0;
     sprites[x].biba = 0;
     sprites[x].strength = 0;
   }  
   number_of_sprites = 0;
}

void destroywall() {
   for (int x = 1; walls[x].active == 1; x++) {
     walls[x].active = 0;
     walls[x].type = 0;
     walls[x].width = 0;
     walls[x].height = 0;
     walls[x].x_position = 0;
     walls[x].y_position = 0;
   }  
   number_of_walls = 0;
}

void sprite_update(int spriten) {
     if (sprites[spriten].hit_points_left <= 0) {
         if (sprites[spriten].type != 1001 && sprites[spriten].type != 1002 && sprites[spriten].type != 1003 && sprites[spriten].type != 1004 && sprites[spriten].type != 1005 && sprites[spriten].type != 1006 && sprites[spriten].type != 1007 && sprites[spriten].type != 1008) {
             if (sprites[spriten].type == 10 || sprites[spriten].type == 14 || sprites[spriten].type == 11 || sprites[spriten].type == 15 || sprites[spriten].type == 17 || sprites[spriten].type == 19 || sprites[spriten].type == 32
              || sprites[spriten].type == 23 || sprites[spriten].type == 24 || sprites[spriten].type == 30 || sprites[spriten].type == 72 || sprites[spriten].type == 41 || sprites[spriten].type == 42 || sprites[spriten].type == 45 || sprites[spriten].type == 62 || sprites[spriten].type == 21) animation(spriten);
             else if (sprites[spriten].type == 12) animation(spriten);
             else if (sprites[spriten].type == 46) destroysprite(spriten);
             else if (sprites[spriten].type == 50) animation(spriten);
             else destroysprite(spriten);
         }
     }
}
