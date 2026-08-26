void run_scripts() {
     
    int tchubasa = 0;
    
    if (player.imune > 0) {
        player.imune--;
        if (player.imune == 29 || player.imune == 27 || player.imune == 25) player.frame = PLAYERD;
        else if (player.frame != NULO && player.frame != PLAYERD) player.frame = NULO;
        else player.frame = PLAYER_MOVING01;
    }
    
    if (looper == 0 || (looper > 8 && looper < 47)) {
    if (player.x_speed != 0) {
        player.move++;
        if (player.frame == PLAYER_MOVING05 || player.frame == PLAYER_MOVING04 || player.frame == PLAYER_MOVING03 || player.frame == PLAYER_MOVING02 || player.frame == PLAYER_MOVING01  || player.frame == PLAYER_MOVING12  || player.frame == PLAYER_MOVING22  || player.frame == PLAYER_MOVING32  || player.frame == PLAYER_MOVING42  || player.frame == PLAYER_MOVING52) {
           if (player.move == 0) {
                if (player.frame != PLAYER_MOVING42) player.frame = PLAYER_MOVING01;
                else player.frame = PLAYER_MOVING12;
           }
           else if (player.move == 1) player.frame = PLAYER_MOVING02;
           else if (player.move == 2) player.frame = PLAYER_MOVING03;
           else if (player.move == 3) player.frame = PLAYER_MOVING02;
           else if (player.move == 4) player.frame = PLAYER_MOVING01;
           else if (player.move == 5) {
                if (player.frame != PLAYER_MOVING12) player.frame = PLAYER_MOVING04;
                else player.frame = PLAYER_MOVING42;
           }
           else if (player.move == 6) {
                if (player.frame != PLAYER_MOVING42) player.frame = PLAYER_MOVING05;
                else player.frame = PLAYER_MOVING52;
           }
           else if (player.move == 7) {
                if (player.frame != PLAYER_MOVING52) player.frame = PLAYER_MOVING04;
                else player.frame = PLAYER_MOVING42;
           }
           if (player.on_ground == FALSE) player.frame = PLAYER_MOVING03;
        }
        if (player.move == 7) player.move = -1;
    }
    else if (player.frame != PLAYERD && player.frame != NULO) player.frame = PLAYER_MOVING01;
    if (fire_key > 0) {
        if (player.frame == PLAYER_MOVING01) { player.frame = PLAYER_MOVING12; player.shooting = 5; }
        else if (player.frame == PLAYER_MOVING02) { player.frame = PLAYER_MOVING22; player.shooting = 5; }
        else if (player.frame == PLAYER_MOVING03) { player.frame = PLAYER_MOVING32; player.shooting = 5; }
        else if (player.frame == PLAYER_MOVING04) { player.frame = PLAYER_MOVING42; player.shooting = 5; }
        else if (player.frame == PLAYER_MOVING05) { player.frame = PLAYER_MOVING52; player.shooting = 5; }
    }
    else if (player.frame == PLAYER_MOVING01 && player.shooting > 0) {
        player.frame = PLAYER_MOVING12;
        player.shooting--;
    }
    else player.shooting = 0;
    }
    
    for (int sprite_loop = 0; sprite_loop < 100; sprite_loop++) {
        if (sprites[sprite_loop].active == 1) {
            if (sprites[sprite_loop].type == 1) {
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 1);
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 1);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 1);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 1);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 1);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 1);
                }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].x_position > player.x_position && sprites[sprite_loop].x_position - player.x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < player.x_position && player.x_position - sprites[sprite_loop].x_position > 640) animation(sprite_loop);
                }
            }
            else if (sprites[sprite_loop].type == 2) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 0)
                sprites[sprite_loop].frame = WIND_SHOT01; 
                else if (sprites[sprite_loop].timer == 3)
                sprites[sprite_loop].frame = WIND_SHOT02;
                else if (sprites[sprite_loop].timer == 6)
                sprites[sprite_loop].frame = WIND_SHOT03;
                else if (sprites[sprite_loop].timer == 8)
                sprites[sprite_loop].timer = -1;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 5;
                sprite_colision(sprite_loop, 2);
            }
            else if (sprites[sprite_loop].type == 3) {
                sprites[sprite_loop].biba = 1;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 3);
		    if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 3);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 3);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 3);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 3);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 3);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 3);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 3);
                }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].x_position > player.x_position && sprites[sprite_loop].x_position - player.x_position > 640) { sprites[sprite_loop].active = 0;fire_key = 0; }
                    else if (sprites[sprite_loop].x_position < player.x_position && player.x_position - sprites[sprite_loop].x_position > 640) { sprites[sprite_loop].active = 0;fire_key = 0; }
                    else if (sprites[sprite_loop].x_position < 0) animation(sprite_loop);
		    }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].y_position > player.y_position && sprites[sprite_loop].y_position - player.y_position > 560) { sprites[sprite_loop].active = 0;fire_key = 0; }
                    else if (sprites[sprite_loop].y_position < player.y_position && player.y_position - sprites[sprite_loop].y_position > 480) { sprites[sprite_loop].active = 0;fire_key = 0; }
                    else if (sprites[sprite_loop].y_position < 0) animation(sprite_loop);
                }
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer >= 65) animation(sprite_loop);
            }
            else if (sprites[sprite_loop].type == 4) {
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 4);
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 4);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 4);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 4);
                }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].x_position > player.x_position && sprites[sprite_loop].x_position - player.x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < player.x_position && player.x_position - sprites[sprite_loop].x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < 0) animation(sprite_loop);
                }
            }
            else if (sprites[sprite_loop].type == 5) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer % 3 == 0) sprites[sprite_loop].y_speed++;
                sprites[sprite_loop].biba = 1;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 5);
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 5);
			  }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 5);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 5);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 5);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 5);
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 5);
		    }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 5);
                }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].x_position > player.x_position && sprites[sprite_loop].x_position - player.x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < player.x_position && player.x_position - sprites[sprite_loop].x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < 0) animation(sprite_loop);
		    }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].y_position > player.y_position && sprites[sprite_loop].y_position - player.y_position > 560) animation(sprite_loop);
                    else if (sprites[sprite_loop].y_position < player.y_position && player.y_position - sprites[sprite_loop].y_position > 480) animation(sprite_loop);
                    else if (sprites[sprite_loop].y_position < 0) animation(sprite_loop);
                }
            }
            else
            if (sprites[sprite_loop].type == 6) {
                if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 0) {
                        sprites[sprite_loop].x_position -= 18;
                        sprites[sprite_loop].y_position -= 17;
                        sprites[sprite_loop].frame = HADOUKEN03;
                    }
                    else if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = HADOUKEN04;
                    else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = HADOUKEN05;
                    else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = HADOUKEN06;
                    else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].frame = HADOUKEN07;
                    if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].active = 0;
                    else if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                else {
                    if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].frame = HADOUKEN01;
                    else if (sprites[sprite_loop].timer % 4 == 2) sprites[sprite_loop].frame = HADOUKEN02;
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 6);
                    if (sprites[sprite_loop].active == 1 && sprites[sprite_loop].action_state == 0) { 
                        sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                        sprite_colision(sprite_loop, 6);
                    }
                    if (sprites[sprite_loop].active == 1 && sprites[sprite_loop].action_state == 0) { 
                        sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                        sprite_colision(sprite_loop, 6);
                    }
                    if (sprites[sprite_loop].active == 1 && sprites[sprite_loop].action_state == 0) { 
                        sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                        sprite_colision(sprite_loop, 6);
                    }
                    if (sprites[sprite_loop].active == 1) {
                       if (sprites[sprite_loop].x_position > player.x_position && sprites[sprite_loop].x_position - player.x_position > 640) animation(sprite_loop);
                       else if (sprites[sprite_loop].x_position < player.x_position && player.x_position - sprites[sprite_loop].x_position > 640) animation(sprite_loop);
                       else if (sprites[sprite_loop].x_position < 0) animation(sprite_loop);
	                }
                }
            }
            else if (sprites[sprite_loop].type == 7) {
                if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_speed += 0.25;
                else sprites[sprite_loop].x_speed -= 0.25;
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer % 3 == 0) sprites[sprite_loop].x_speed *= 2;
                if (sprites[sprite_loop].x_speed > 20) sprites[sprite_loop].x_speed = 20;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 7);
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 7);
                }
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].x_position > player.x_position && sprites[sprite_loop].x_position - player.x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < player.x_position && player.x_position - sprites[sprite_loop].x_position > 640) animation(sprite_loop);
                    else if (sprites[sprite_loop].x_position < 0) animation(sprite_loop);
                }
            }
            else if (sprites[sprite_loop].type == 10) {
               sprites[sprite_loop].timer++;
               if (sprites[sprite_loop].timer == 0) {
               sprites[sprite_loop].frame = REDBALL01;
               }
               else if (sprites[sprite_loop].timer == 2) {
               sprites[sprite_loop].frame = REDBALL02;
               }                              
               else if (sprites[sprite_loop].timer == 4) {
               sprites[sprite_loop].frame = REDBALL03;
               }
               else if (sprites[sprite_loop].timer == 6) {
               sprites[sprite_loop].frame = REDBALL02;
               }
               else if (sprites[sprite_loop].timer == 8) {
               sprites[sprite_loop].frame = REDBALL01;
               }
               else if (sprites[sprite_loop].timer == 10) {
               sprites[sprite_loop].frame = REDBALL04;
               }                              
               else if (sprites[sprite_loop].timer == 12) {
               sprites[sprite_loop].frame = REDBALL05;
               }
               else if (sprites[sprite_loop].timer == 14) {
               sprites[sprite_loop].frame = REDBALL04;
               sprites[sprite_loop].timer = -1;
               }
               if (sprites[sprite_loop].direction == 1) {
               sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 5;
               sprite_colision(sprite_loop, 10);
               }
               else {
               sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed * 5;
               sprite_colision(sprite_loop, 10);
               }
            }
            else
            if (sprites[sprite_loop].type == 11) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer >= 40 && sprites[sprite_loop].timer < 48) {
                sprites[sprite_loop].frame = MOLA_FELIZ2;
                sprites[sprite_loop].height = 73;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed * 5;
                sprites[sprite_loop].y_speed -= 0.16; 
                }
                else if (sprites[sprite_loop].timer >= 48 && sprites[sprite_loop].timer < 56) {
                sprites[sprite_loop].y_speed -= 0.16;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed * 5;
                }
                else if (sprites[sprite_loop].timer >= 56 && sprites[sprite_loop].timer < 60) {
                sprites[sprite_loop].y_speed -= 0.16;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed * 5;
                }
                else if (sprites[sprite_loop].timer >= 80 && sprites[sprite_loop].timer < 88) {
                sprites[sprite_loop].frame = MOLA_FELIZ2;
                sprites[sprite_loop].height = 73;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed * 5;
                sprites[sprite_loop].y_speed -= 0.14;
                }
                else if (sprites[sprite_loop].timer >= 88 && sprites[sprite_loop].timer < 96) {
                sprites[sprite_loop].y_speed -= 0.13;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed * 5;
                }
                else if (sprites[sprite_loop].timer >= 96 && sprites[sprite_loop].timer < 100) {
                sprites[sprite_loop].y_speed -= 0.12;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed * 5;
                }
                if (sprites[sprite_loop].timer == 59) {
                sprites[sprite_loop].timer = 79;
                sprites[sprite_loop].y_speed = 0;
                }
                if (sprites[sprite_loop].timer == 99) {
                sprites[sprite_loop].y_speed = 3;
                while (sprites[sprite_loop].y_position > sprites[sprite_loop].biba) sprites[sprite_loop].y_position -= 0.1;
                while (sprites[sprite_loop].y_position < sprites[sprite_loop].biba) sprites[sprite_loop].y_position += 0.1;
                sprites[sprite_loop].timer = 0;
                sprites[sprite_loop].frame = MOLA_FELIZ;
                sprites[sprite_loop].height = 60;
                }
                if (player.x_position >= sprites[sprite_loop].x_position + 20) sprites[sprite_loop].direction = 1;
                else sprites[sprite_loop].direction = 0;
            }
            else if (sprites[sprite_loop].type == 12) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 30) {
                    if (sprites[sprite_loop].direction == 0) initialize_sprite(13, (int)(sprites[sprite_loop].x_position), (int)(sprites[sprite_loop].y_position + 16), sprites[sprite_loop].direction, 0);
                    else initialize_sprite(13, (int)(sprites[sprite_loop].x_position + 59), (int)(sprites[sprite_loop].y_position + 16), sprites[sprite_loop].direction, 0);
                    sprites[sprite_loop].timer = 0;
                }
            }
            else
            if (sprites[sprite_loop].type == 13) {
                sprites[sprite_loop].timer--;
                if (sprites[sprite_loop].direction == 1) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 5;
                    sprite_colision(sprite_loop, 13);
                }
                else {
                    sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed * 5;
                    sprite_colision(sprite_loop, 13);
                }
		    if (sprites[sprite_loop].active == 1 && sprites[sprite_loop].timer <= 0) animation(sprite_loop);
            }
            else if (sprites[sprite_loop].type == 14) {
                 sprites[sprite_loop].timer++;
                 if (sprites[sprite_loop].timer >= 1 && sprites[sprite_loop].timer < 46) {
                 if (sprites[sprite_loop].y_speed != 2.5) sprites[sprite_loop].y_speed += 0.25;
                 sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                 }
                 if (sprites[sprite_loop].timer >= 46 && sprites[sprite_loop].timer < 76) {
                 if (sprites[sprite_loop].y_speed == 2.5) sprites[sprite_loop].y_speed = -6;
                 sprites[sprite_loop].y_speed += 0.176;
                 sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                 }
                 if (sprites[sprite_loop].timer == 45) {
                 sprites[sprite_loop].frame = PIRIKITO2;
                 }
                 if (sprites[sprite_loop].timer == 46) {
                 sprites[sprite_loop].frame = PIRIKITO3;
                 }
                 if (sprites[sprite_loop].timer == 48) {
                 sprites[sprite_loop].frame = PIRIKITO2;
                 }
                 if (sprites[sprite_loop].timer == 49) {
                 sprites[sprite_loop].frame = PIRIKITO;
                 }
                 else if (sprites[sprite_loop].timer == 76) {
                 sprites[sprite_loop].timer = 0;
                 sprites[sprite_loop].y_speed = 0;
                 sprites[sprite_loop].y_position = sprites[sprite_loop].biba;
                 }
                 if (sprites[sprite_loop].x_position < 0) tchubasa = 1;
                 if (sprites[sprite_loop].x_position > 480) tchubasa = 2;
            }
            else
            if (sprites[sprite_loop].type == 15) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].biba = 20;
                    sprites[sprite_loop].frame = GHOST04;
                    if (player.y_position < sprites[sprite_loop].y_position + 290 && player.y_position > sprites[sprite_loop].y_position - 250) {
                    if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position < 300) { sprites[sprite_loop].action_state = 1; sprites[sprite_loop].frame = GHOST03; }
                    else if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position < 300) { sprites[sprite_loop].action_state = 1; sprites[sprite_loop].frame = GHOST03; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position > 300 && (player.y_position < sprites[sprite_loop].y_position + 290 && player.y_position > sprites[sprite_loop].y_position - 250)) {
                        if (sprites[sprite_loop].x_speed > 1 || sprites[sprite_loop].x_speed < -1) sprites[sprite_loop].frame = GHOST03;
                        else sprites[sprite_loop].frame = GHOST04;
                        if (sprites[sprite_loop].biba > 10) sprites[sprite_loop].biba -= 10;
                        if (sprites[sprite_loop].y_speed > 0.4) sprites[sprite_loop].y_speed -= 0.2;
                        else if (sprites[sprite_loop].y_speed < -0.4) sprites[sprite_loop].y_speed += 0.2;
                        if (sprites[sprite_loop].x_speed > 0.4) sprites[sprite_loop].x_speed -= 0.2;
                        else if (sprites[sprite_loop].x_speed < -0.4) sprites[sprite_loop].x_speed += 0.2;
                        else { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_speed = 0; }
                    }
                    else if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position > 300 && (player.y_position < sprites[sprite_loop].y_position + 290 && player.y_position > sprites[sprite_loop].y_position - 250)) {
                        if (sprites[sprite_loop].x_speed > 1 || sprites[sprite_loop].x_speed < -1) sprites[sprite_loop].frame = GHOST03;
                        else sprites[sprite_loop].frame = GHOST04;
                        if (sprites[sprite_loop].biba > 10) sprites[sprite_loop].biba -= 10;
                        if (sprites[sprite_loop].y_speed > 0.4) sprites[sprite_loop].y_speed -= 0.2;
                        else if (sprites[sprite_loop].y_speed < -0.4) sprites[sprite_loop].y_speed += 0.2;
                        if (sprites[sprite_loop].x_speed > 0.4) sprites[sprite_loop].x_speed -= 0.2;
                        else if (sprites[sprite_loop].x_speed < -0.4) sprites[sprite_loop].x_speed += 0.2;
                        else { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_speed = 0; }
                    }
                    else if (player.y_position >= sprites[sprite_loop].y_position + 290 || player.y_position <= sprites[sprite_loop].y_position - 250) {
                        if (sprites[sprite_loop].x_speed > 1 || sprites[sprite_loop].x_speed < -1) sprites[sprite_loop].frame = GHOST03;
                        else sprites[sprite_loop].frame = GHOST04;
                        if (sprites[sprite_loop].biba > 10) sprites[sprite_loop].biba -= 10;
                        if (sprites[sprite_loop].y_speed > 0.4) sprites[sprite_loop].y_speed -= 0.2;
                        else if (sprites[sprite_loop].y_speed < -0.4) sprites[sprite_loop].y_speed += 0.2;
                        if (sprites[sprite_loop].x_speed > 0.4) sprites[sprite_loop].x_speed -= 0.2;
                        else if (sprites[sprite_loop].x_speed < -0.4) sprites[sprite_loop].x_speed += 0.2;
                        else { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_speed = 0; }
                    }
                    else {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer % 5 == 0) {
                            if (sprites[sprite_loop].frame == GHOST03) sprites[sprite_loop].frame = GHOST02;
                            else if (sprites[sprite_loop].frame == GHOST01) sprites[sprite_loop].frame = GHOST02;
                            else sprites[sprite_loop].frame = GHOST01;
                        }
                        if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_speed > 0) { sprites[sprite_loop].x_speed -= 0.4; sprites[sprite_loop].direction = 0; sprites[sprite_loop].biba = (int)(((sprites[sprite_loop].x_position - player.x_position + 20) / 2) * -1) + 150; }
                        else if (player.x_position > sprites[sprite_loop].x_position && sprites[sprite_loop].x_speed < 0) { sprites[sprite_loop].x_speed += 0.4; sprites[sprite_loop].direction = 1; sprites[sprite_loop].biba = (int)(((player.x_position - sprites[sprite_loop].x_position + 20) / 2) * -1) + 150; }
                        else if (player.x_position < sprites[sprite_loop].x_position) { sprites[sprite_loop].x_speed -= 0.3; sprites[sprite_loop].direction = 0; sprites[sprite_loop].biba = (int)(((sprites[sprite_loop].x_position - player.x_position + 20) / 2) * -1) + 170; }
                        else if (player.x_position > sprites[sprite_loop].x_position) { sprites[sprite_loop].x_speed += 0.3; sprites[sprite_loop].direction = 1; sprites[sprite_loop].biba = (int)(((player.x_position - sprites[sprite_loop].x_position + 20) / 2) * -1) + 170; }
                        if (player.y_position < sprites[sprite_loop].y_position) sprites[sprite_loop].y_speed -= 0.3;
                        else if (player.y_position > sprites[sprite_loop].y_position) sprites[sprite_loop].y_speed += 0.3;
                        if (sprites[sprite_loop].x_speed > 5) sprites[sprite_loop].x_speed = 5;
                        else if (sprites[sprite_loop].x_speed < -5) sprites[sprite_loop].x_speed = -5;
                        if (sprites[sprite_loop].y_speed > 5) sprites[sprite_loop].y_speed = 5;
                        else if (sprites[sprite_loop].y_speed < -5) sprites[sprite_loop].y_speed = -5;
                    }
                    if (sprites[sprite_loop].biba > 128) sprites[sprite_loop].biba = 128;
                    else if (sprites[sprite_loop].biba < 20) sprites[sprite_loop].biba = 20;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                }
            }
            else
            if (sprites[sprite_loop].type == 16) {
              if (player.x_position < sprites[sprite_loop].x_position - 350) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer >= (rand() % 10) + 41) {
                    initialize_sprite(17, (int)sprites[sprite_loop].x_position, (rand() % (int)sprites[sprite_loop].y_speed) + (int)sprites[sprite_loop].y_position, sprites[sprite_loop].direction, (int)sprites[sprite_loop].x_speed);
                    sprites[sprite_loop].timer = 0;
                }
              }
            }
            else
            if (sprites[sprite_loop].type == 17) {
              if (sprites[sprite_loop].animation_state == 0) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = GHOSTMASK01;
                else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].frame = GHOSTMASK02;
                else if (sprites[sprite_loop].timer == 7) sprites[sprite_loop].frame = GHOSTMASK03;
                else if (sprites[sprite_loop].timer >= 10) { sprites[sprite_loop].frame = GHOSTMASK02; sprites[sprite_loop].timer = -2; }
                if (sprites[sprite_loop].rotate_factor == 0) {
                    if (sprites[sprite_loop].y_speed == 2) sprites[sprite_loop].rotate_factor = 1;
                    else sprites[sprite_loop].y_speed += 0.5;
                }
                else if (sprites[sprite_loop].rotate_factor == 1) {
                    if (sprites[sprite_loop].y_speed == -2) sprites[sprite_loop].rotate_factor = 0;
                    else sprites[sprite_loop].y_speed -= 0.5;
                }
                if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                if (sprites[sprite_loop].x_position + sprites[sprite_loop].width < Map.limitleft) sprites[sprite_loop].active = 0;
                else if (sprites[sprite_loop].x_position < sprites[sprite_loop].biba) sprites[sprite_loop].animation_state = 1;
                else sprite_colision(sprite_loop, 17);
              }
              else if (sprites[sprite_loop].animation_state == 1) {
                sprites[sprite_loop].action_state -= 20;
                if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                if (sprites[sprite_loop].action_state <= 0) sprites[sprite_loop].active = 0;    
              }
            }
            else if (sprites[sprite_loop].type == 61) {
              if (player.x_position > sprites[sprite_loop].x_position + 420) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer >= (rand() % 10) + 41) {
                    initialize_sprite(62, (int)sprites[sprite_loop].x_position, (rand() % (int)sprites[sprite_loop].y_speed) + (int)sprites[sprite_loop].y_position, sprites[sprite_loop].direction, (int)sprites[sprite_loop].x_speed);
                    sprites[sprite_loop].timer = 0;
                }
              }
            }
            else if (sprites[sprite_loop].type == 62) {
              if (sprites[sprite_loop].animation_state == 0) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = GHOSTMASK01;
                else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].frame = GHOSTMASK02;
                else if (sprites[sprite_loop].timer == 7) sprites[sprite_loop].frame = GHOSTMASK03;
                else if (sprites[sprite_loop].timer >= 10) { sprites[sprite_loop].frame = GHOSTMASK02; sprites[sprite_loop].timer = -2; }
                if (sprites[sprite_loop].rotate_factor == 0) {
                    if (sprites[sprite_loop].y_speed == 2) sprites[sprite_loop].rotate_factor = 1;
                    else sprites[sprite_loop].y_speed += 0.5;
                }
                else if (sprites[sprite_loop].rotate_factor == 1) {
                    if (sprites[sprite_loop].y_speed == -2) sprites[sprite_loop].rotate_factor = 0;
                    else sprites[sprite_loop].y_speed -= 0.5;
                }
                if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                if (sprites[sprite_loop].x_position + sprites[sprite_loop].width < Map.limitleft) sprites[sprite_loop].active = 0;
                else if (sprites[sprite_loop].x_position > sprites[sprite_loop].biba) sprites[sprite_loop].animation_state = 1;
                else sprite_colision(sprite_loop, 62);
              }
              else if (sprites[sprite_loop].animation_state == 1) {
                sprites[sprite_loop].action_state -= 20;
                if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                if (sprites[sprite_loop].action_state <= 0) sprites[sprite_loop].active = 0;    
              }
            }
            else if (sprites[sprite_loop].type == 18) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer >= 20) {
                    sprites[sprite_loop].x_speed += 8.55;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].x_speed;
                    if (sprites[sprite_loop].y_position - sprites[sprite_loop].biba > 150) { sprites[sprite_loop].action_state = 1; sprites[sprite_loop].timer = -30; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_position = sprites[sprite_loop].biba + 129; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].timer >= -20) {
                        sprites[sprite_loop].y_position -= 6;
                        if (sprites[sprite_loop].timer == 0) sprites[sprite_loop].action_state = 0;
                    }
                }
            }
            else if (sprites[sprite_loop].type == 19) {
                if (sprites[sprite_loop].timer == 50) {
                    sprites[sprite_loop].timer = 0;
                    if (sprites[sprite_loop].direction == 0) {
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position - 4, (int)sprites[sprite_loop].y_position + 16, sprites[sprite_loop].direction, 0);
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position + 36, (int)sprites[sprite_loop].y_position + 16, sprites[sprite_loop].direction + 3, 0);
                    }
                    else if (sprites[sprite_loop].direction == 1) {
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position + 16, (int)sprites[sprite_loop].y_position - 4, sprites[sprite_loop].direction, 0);
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position + 16, (int)sprites[sprite_loop].y_position + 36, sprites[sprite_loop].direction + 3, 0);
                    }
                    else {
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position - 4, (int)sprites[sprite_loop].y_position - 4, sprites[sprite_loop].direction, 0);
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position - 4, (int)sprites[sprite_loop].y_position + 36, sprites[sprite_loop].direction + 3, 0);
                    }
                }
                sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 20) {
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprites[sprite_loop].biba = 1;
                sprite_colision(sprite_loop, 20);
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprites[sprite_loop].biba = 2;
                    sprite_colision(sprite_loop, 20);
                    if (sprites[sprite_loop].active == 1) { if (sprites[sprite_loop].x_position < 0) sprites[sprite_loop].active = 0; }
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 30) animation(sprite_loop);
                }
            }
            else if (sprites[sprite_loop].type == 21) {
                if (sprites[sprite_loop].timer == 50) {
                    sprites[sprite_loop].timer = rand() % 3;
                    if (sprites[sprite_loop].timer == 0) initialize_sprite(22, (int)sprites[sprite_loop].x_position + 22, (int)sprites[sprite_loop].y_position + 27, sprites[sprite_loop].direction, 0);
                    else if (sprites[sprite_loop].timer == 1) initialize_sprite(22, (int)sprites[sprite_loop].x_position - 2, (int)sprites[sprite_loop].y_position + 26, sprites[sprite_loop].direction, 0);
                    else if (sprites[sprite_loop].timer == 2) {
                        if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].biba = 6;
                        else sprites[sprite_loop].biba = 7;
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position + 23, (int)sprites[sprite_loop].y_position + 17, sprites[sprite_loop].biba, 0);
                        initialize_sprite(20, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position + 16, sprites[sprite_loop].biba, 0);
                    }
                    sprites[sprite_loop].timer = 0;
                }
                sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 22) {
                if (sprites[sprite_loop].timer == 10) sprites[sprite_loop].x_speed = -22;
                if (sprites[sprite_loop].timer != 0) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprites[sprite_loop].timer++;
                sprite_colision(sprite_loop, 22);
                if (sprites[sprite_loop].active == 1) {
                    if (sprites[sprite_loop].timer == 30) animation(sprite_loop);
                }
            }
            else if (sprites[sprite_loop].type == 23) {
                if (sprites[sprite_loop].x_position > player.x_position + 55) sprites[sprite_loop].direction = 1;
                else if (sprites[sprite_loop].x_position + 40 < player.x_position - 15) sprites[sprite_loop].direction = 3;
                else sprites[sprite_loop].direction = 2;
                if (sprites[sprite_loop].timer == 0)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE01;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE04;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE07;
                }
                else if (sprites[sprite_loop].timer == 2)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE02;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE05;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE08;
                }
                else if (sprites[sprite_loop].timer == 4)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE03;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE06;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE09;
                }
                else if (sprites[sprite_loop].timer == 6)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE02;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE05;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE08;
                }
                else if (sprites[sprite_loop].timer == 8)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE07;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE04;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE01;
                }
                else if (sprites[sprite_loop].timer == 10)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE08;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE05;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE02;
                }
                else if (sprites[sprite_loop].timer == 12)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE09;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE06;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE03;
                }
                else if (sprites[sprite_loop].timer == 14)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE08;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE05;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE02;
                }
                else if (sprites[sprite_loop].timer == 16)  {
                    if (sprites[sprite_loop].direction == 1) sprites[sprite_loop].frame = ORANGE01;
                    else if (sprites[sprite_loop].direction == 2) sprites[sprite_loop].frame = ORANGE04;
                    else if (sprites[sprite_loop].direction == 3) sprites[sprite_loop].frame = ORANGE07;
                    sprites[sprite_loop].timer = 0;
                }
                if (sprites[sprite_loop].biba < 2) sprites[sprite_loop].y_position -= 1;
                else if (sprites[sprite_loop].biba < 8) sprites[sprite_loop].y_position -= 2;
                else if (sprites[sprite_loop].biba < 10) sprites[sprite_loop].y_position -= 1;
                else if (sprites[sprite_loop].biba < 11) sprites[sprite_loop].y_position = sprites[sprite_loop].y_position;
                else if (sprites[sprite_loop].biba < 13) sprites[sprite_loop].y_position += 1;
                else if (sprites[sprite_loop].biba < 19) sprites[sprite_loop].y_position += 2;
                else if (sprites[sprite_loop].biba < 21) sprites[sprite_loop].y_position += 1;
                else sprites[sprite_loop].biba = -1;
                if (sprites[sprite_loop].timer == 8) {
                    if (sprites[sprite_loop].direction == 1) initialize_sprite(20, (int)sprites[sprite_loop].x_position - 3, (int)sprites[sprite_loop].y_position + 46, 5, 0);
                    else if (sprites[sprite_loop].direction == 2) initialize_sprite(20, (int)sprites[sprite_loop].x_position + 16, (int)sprites[sprite_loop].y_position + 50, 8, 0);
                    else initialize_sprite(20, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 46, 3, 0);
                }
                sprites[sprite_loop].biba++;
                sprites[sprite_loop].timer++;
                sprites[sprite_loop].action_state++;
            }
            else if (sprites[sprite_loop].type == 24) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer > 9 && sprites[sprite_loop].timer < 14) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].timer == 16) {
                    if (sprites[sprite_loop].direction == 0) initialize_sprite(25, (int)sprites[sprite_loop].x_position + 7, (int)sprites[sprite_loop].y_position + 21, 0, 0);
                    else if (sprites[sprite_loop].direction == 1) initialize_sprite(25, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 7, 1, 0);
                    else if (sprites[sprite_loop].direction == 2) initialize_sprite(25, (int)sprites[sprite_loop].x_position + 7, (int)sprites[sprite_loop].y_position + 9, 2, 0);
                    else if (sprites[sprite_loop].direction == 3) initialize_sprite(25, (int)sprites[sprite_loop].x_position + 21, (int)sprites[sprite_loop].y_position + 8, 3, 0);
                }
                else if (sprites[sprite_loop].timer > 30 && sprites[sprite_loop].timer < 35) sprites[sprite_loop].frame--;
                else if (sprites[sprite_loop].timer == 60) sprites[sprite_loop].timer = 0;
            }
            else if (sprites[sprite_loop].type == 25) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer % 5 == 1) sprites[sprite_loop].frame = SHOCKING02;
                else if (sprites[sprite_loop].timer % 5 == 2) sprites[sprite_loop].frame = SHOCKING03;
                else if (sprites[sprite_loop].timer % 5 == 3) sprites[sprite_loop].frame = SHOCKING04;
                else if (sprites[sprite_loop].timer % 5 == 4) sprites[sprite_loop].frame = SHOCKING05;
                else if (sprites[sprite_loop].timer % 5 == 0) sprites[sprite_loop].frame = SHOCKING01;
                if (sprites[sprite_loop].timer == 16) {
                    if (sprites[sprite_loop].direction == 0) initialize_sprite(26, (int)sprites[sprite_loop].x_position + 4, (int)sprites[sprite_loop].y_position + 3, sprites[sprite_loop].direction, 0);
                    else if (sprites[sprite_loop].direction == 1) initialize_sprite(26, (int)sprites[sprite_loop].x_position - 2, (int)sprites[sprite_loop].y_position + 4, sprites[sprite_loop].direction, 0);
                    else if (sprites[sprite_loop].direction == 2) initialize_sprite(26, (int)sprites[sprite_loop].x_position + 4, (int)sprites[sprite_loop].y_position - 2, sprites[sprite_loop].direction, 0);
                    else if (sprites[sprite_loop].direction == 3) initialize_sprite(26, (int)sprites[sprite_loop].x_position + 3, (int)sprites[sprite_loop].y_position + 2, sprites[sprite_loop].direction, 0);
                    sprites[sprite_loop].active = 0;
                }
            }
            else if (sprites[sprite_loop].type == 26) {
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprites[sprite_loop].biba = 1;
                sprite_colision(sprite_loop, 26);
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprites[sprite_loop].biba = 2;
                    sprite_colision(sprite_loop, 26);
                    if (sprites[sprite_loop].active == 1) { if (sprites[sprite_loop].x_position < 0) sprites[sprite_loop].active = 0;}
                }
                if (sprites[sprite_loop].active == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 60) sprites[sprite_loop].active = 0;
                }
            }
            else if (sprites[sprite_loop].type == 27) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 1) { sprites[sprite_loop].x_position -= 4; sprites[sprite_loop].frame++; }
                else if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].x_position -= 14; sprites[sprite_loop].frame++; }
                else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].x_position -= 2; sprites[sprite_loop].frame++; }
                else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].active = 0;
            }
            else if (sprites[sprite_loop].type == 29) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.direction == 0 && sprites[sprite_loop].x_position - player.x_position-40 > 24 && sprites[sprite_loop].x_position - player.x_position-40 < 56) {
                        sprites[sprite_loop].action_state = 1;
                        sprites[sprite_loop].direction = 1;
                    }
                    else if (player.direction == 1 && player.x_position - sprites[sprite_loop].x_position-37 > 24 && player.x_position - sprites[sprite_loop].x_position-37  < 56) {
                        sprites[sprite_loop].action_state = 1;
                        sprites[sprite_loop].direction = 0;
                    }
                }
                if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) { sprites[sprite_loop].y_position -= 6; sprites[sprite_loop].height += 6; }
                    else if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].y_position -= 7; sprites[sprite_loop].height += 7; }
                    else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].y_position -= 7; sprites[sprite_loop].height += 7; }
                    else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].y_position -= 7; sprites[sprite_loop].height += 7; }
                    else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].y_position -= 7; sprites[sprite_loop].height += 7; }
                    else if (sprites[sprite_loop].timer == 16) { sprites[sprite_loop].y_position += 7; sprites[sprite_loop].height -= 7; }
                    else if (sprites[sprite_loop].timer == 17) { sprites[sprite_loop].y_position += 7; sprites[sprite_loop].height -= 7; }
                    else if (sprites[sprite_loop].timer == 18) { sprites[sprite_loop].y_position += 7; sprites[sprite_loop].height -= 7; }
                    else if (sprites[sprite_loop].timer == 19) { sprites[sprite_loop].y_position += 7; sprites[sprite_loop].height -= 7; }
                    else if (sprites[sprite_loop].timer == 20) { sprites[sprite_loop].y_position += 6; sprites[sprite_loop].height -= 6; }
                    else if (sprites[sprite_loop].timer >= 24) {
                        if (player.x_position - sprites[sprite_loop].x_position - 37 > 70 || sprites[sprite_loop].x_position - player.x_position - 40  > 70) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 0; }
                    }
                }
            }
            else if (sprites[sprite_loop].type == 31) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.x_position - sprites[sprite_loop].x_position - 36 > 0 && player.x_position - sprites[sprite_loop].x_position - 36 < 140) { initialize_sprite(30, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, 0, 0); sprites[sprite_loop].action_state = 1; }
                    else if (sprites[sprite_loop].x_position - player.x_position - 40 > 0 && sprites[sprite_loop].x_position - player.x_position - 40 < 140) { initialize_sprite(30, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, 0, 0); sprites[sprite_loop].action_state = 1; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 90) { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].timer = 0; }
                }
            }
            else if (sprites[sprite_loop].type == 30) {
                if (sprites[sprite_loop].action_state == 0) sprites[sprite_loop].action_state = 1;
                if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) { sprites[sprite_loop].height+=17; sprites[sprite_loop].y_position-=17; }
                    else if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].height+=17; sprites[sprite_loop].y_position-=17; }
                    else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].height+=17; sprites[sprite_loop].y_position-=17; }
                    else if (sprites[sprite_loop].timer >= 4) {
                        if (sprites[sprite_loop].y_position <= player.y_position) { sprites[sprite_loop].action_state = 2; sprites[sprite_loop].timer = 0; }
                        else if (sprites[sprite_loop].y_position <= Map.water_position + 20) { sprites[sprite_loop].y_position = Map.water_position + 20; sprites[sprite_loop].action_state = 2; sprites[sprite_loop].timer = 0; }
                        else { sprites[sprite_loop].y_position-=17; sprites[sprite_loop].y_speed+=17; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].action_state = 3; sprites[sprite_loop].frame = SEAHORSE2; sprites[sprite_loop].width = 40; sprites[sprite_loop].height = 41; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
                        sprites[sprite_loop].width = 30; sprites[sprite_loop].height = 30; sprites[sprite_loop].frame = SEAHORSE3;
                        if (player.x_position > sprites[sprite_loop].x_position) sprites[sprite_loop].x_speed = 25;
                        else sprites[sprite_loop].x_speed = -25;
                    }
                    else if (sprites[sprite_loop].timer >= 10) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    if (sprites[sprite_loop].x_position - player.x_position - 40 > 640) sprites[sprite_loop].active = 0;
                    else if (player.x_position - sprites[sprite_loop].x_position - 30 > 640) sprites[sprite_loop].active = 0;
                }
                sprite_colision(sprite_loop, 30);
            }
            else if (sprites[sprite_loop].type == 32) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position - 40 < 260) {
                        sprites[sprite_loop].action_state = 1;
                        sprites[sprite_loop].frame++;
                        if (sprites[sprite_loop].direction == 1) initialize_sprite(501, (int)sprites[sprite_loop].x_position + 50, (int)sprites[sprite_loop].y_position - 23, 0, 5);
                        else initialize_sprite(501, (int)sprites[sprite_loop].x_position - 10, (int)sprites[sprite_loop].y_position - 23, 0, 5);
                        sprites[sprite_loop].timer = 0;
                    }
                    else if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position - 20 < 260) {
                        sprites[sprite_loop].action_state = 1;
                        sprites[sprite_loop].frame++;
                        if (sprites[sprite_loop].direction == 1) initialize_sprite(501, (int)sprites[sprite_loop].x_position + 50, (int)sprites[sprite_loop].y_position - 23, 0, 5);
                        else initialize_sprite(501, (int)sprites[sprite_loop].x_position - 10, (int)sprites[sprite_loop].y_position - 23, 0, 5);
                        sprites[sprite_loop].timer = 0;
                    }
                    else {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer % 20 == 0) sprites[sprite_loop].y_position += 0;
                        else if (sprites[sprite_loop].timer % 20 == 2) sprites[sprite_loop].y_position += 1;
                        else if (sprites[sprite_loop].timer % 20 == 4) sprites[sprite_loop].y_position += 1;
                        else if (sprites[sprite_loop].timer % 20 == 6) sprites[sprite_loop].y_position += 2;
                        else if (sprites[sprite_loop].timer % 20 == 8) sprites[sprite_loop].y_position += 1;
                        else if (sprites[sprite_loop].timer % 20 == 10) sprites[sprite_loop].y_position -= 0;
                        else if (sprites[sprite_loop].timer % 20 == 12) sprites[sprite_loop].y_position -= 1;
                        else if (sprites[sprite_loop].timer % 20 == 14) sprites[sprite_loop].y_position -= 1;
                        else if (sprites[sprite_loop].timer % 20 == 16) sprites[sprite_loop].y_position -= 2;
                        else if (sprites[sprite_loop].timer % 20 == 18) sprites[sprite_loop].y_position -= 1;
                    }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position - 40 > 300) {
                        if (sprites[sprite_loop].x_speed > 1 || sprites[sprite_loop].x_speed < -1) {
                            if (sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = EWULFISH_12;
                            else if (sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = EWULFISH_22;
                            else if (sprites[sprite_loop].biba == 3) sprites[sprite_loop].frame = EWULFISH_32;
                            else if (sprites[sprite_loop].biba == 4) sprites[sprite_loop].frame = EWULFISH_42;
                        }
                        else {
                            if (sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = EWULFISH_11;
                            else if (sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = EWULFISH_21;
                            else if (sprites[sprite_loop].biba == 3) sprites[sprite_loop].frame = EWULFISH_31;
                            else if (sprites[sprite_loop].biba == 4) sprites[sprite_loop].frame = EWULFISH_41;
                        }
                        if (sprites[sprite_loop].y_speed > 0.4) sprites[sprite_loop].y_speed -= 0.2;
                        else if (sprites[sprite_loop].y_speed < -0.4) sprites[sprite_loop].y_speed += 0.2;
                        if (sprites[sprite_loop].x_speed > 0.4) sprites[sprite_loop].x_speed -= 0.2;
                        else if (sprites[sprite_loop].x_speed < -0.4) sprites[sprite_loop].x_speed += 0.2;
                        else { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_speed = 0; sprites[sprite_loop].timer = 0; }
                    }
                    else if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position - 20 > 300) {
                        if (sprites[sprite_loop].x_speed > 1 || sprites[sprite_loop].x_speed < -1) {
                            if (sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = EWULFISH_12;
                            else if (sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = EWULFISH_22;
                            else if (sprites[sprite_loop].biba == 3) sprites[sprite_loop].frame = EWULFISH_32;
                            else if (sprites[sprite_loop].biba == 4) sprites[sprite_loop].frame = EWULFISH_42;
                        }
                        else {
                            if (sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = EWULFISH_11;
                            else if (sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = EWULFISH_21;
                            else if (sprites[sprite_loop].biba == 3) sprites[sprite_loop].frame = EWULFISH_31;
                            else if (sprites[sprite_loop].biba == 4) sprites[sprite_loop].frame = EWULFISH_41;
                        }
                        if (sprites[sprite_loop].y_speed > 0.4) sprites[sprite_loop].y_speed -= 0.2;
                        else if (sprites[sprite_loop].y_speed < -0.4) sprites[sprite_loop].y_speed += 0.2;
                        if (sprites[sprite_loop].x_speed > 0.4) sprites[sprite_loop].x_speed -= 0.2;
                        else if (sprites[sprite_loop].x_speed < -0.4) sprites[sprite_loop].x_speed += 0.2;
                        else { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_speed = 0; sprites[sprite_loop].timer = 0; }
                    }
                    else {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer % 4 == 0) {
                            if (sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = EWULFISH_12;
                            else if (sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = EWULFISH_22;
                            else if (sprites[sprite_loop].biba == 3) sprites[sprite_loop].frame = EWULFISH_32;
                            else if (sprites[sprite_loop].biba == 4) sprites[sprite_loop].frame = EWULFISH_42;
                        }
                        else if (sprites[sprite_loop].timer % 2 == 0) {
                            if (sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = EWULFISH_13;
                            else if (sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = EWULFISH_23;
                            else if (sprites[sprite_loop].biba == 3) sprites[sprite_loop].frame = EWULFISH_33;
                            else if (sprites[sprite_loop].biba == 4) sprites[sprite_loop].frame = EWULFISH_43;
                        }
                        if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_speed > 0) { sprites[sprite_loop].x_speed -= 0.4; sprites[sprite_loop].direction = 0; }
                        else if (player.x_position > sprites[sprite_loop].x_position && sprites[sprite_loop].x_speed < 0) { sprites[sprite_loop].x_speed += 0.4; sprites[sprite_loop].direction = 1; }
                        else if (player.x_position < sprites[sprite_loop].x_position) { sprites[sprite_loop].x_speed -= 0.3; sprites[sprite_loop].direction = 0; }
                        else if (player.x_position > sprites[sprite_loop].x_position) { sprites[sprite_loop].x_speed += 0.3; sprites[sprite_loop].direction = 1; }
                        if (player.y_position < sprites[sprite_loop].y_position) sprites[sprite_loop].y_speed -= 0.3;
                        else if (player.y_position > sprites[sprite_loop].y_position) sprites[sprite_loop].y_speed += 0.3;
                        if (sprites[sprite_loop].x_speed > 5) sprites[sprite_loop].x_speed = 5;
                        else if (sprites[sprite_loop].x_speed < -5) sprites[sprite_loop].x_speed = -5;
                        if (sprites[sprite_loop].y_speed > 5) sprites[sprite_loop].y_speed = 5;
                        else if (sprites[sprite_loop].y_speed < -5) sprites[sprite_loop].y_speed = -5;
                    }
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 32);
                    if (sprites[sprite_loop].active == 1) {
                        sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                        sprite_colision(sprite_loop, 31);
                    }
                }
                if (sprites[sprite_loop].y_position <  Map.water_position) sprites[sprite_loop].y_position = Map.water_position;
            }
            else if (sprites[sprite_loop].type == 33) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (sprites[sprite_loop].direction == 0 && sprites[sprite_loop].x_position - player.x_position > 0 && sprites[sprite_loop].x_position - player.x_position - 40 < 360) sprites[sprite_loop].action_state = 1;
                    else if (sprites[sprite_loop].direction == 1 && player.x_position - sprites[sprite_loop].x_position > 0 && player.x_position - sprites[sprite_loop].x_position - 36 < 360) sprites[sprite_loop].action_state = 1;
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
                        initialize_sprite(35, (int)sprites[sprite_loop].x_position + 17, (int)sprites[sprite_loop].y_position + 4, sprites[sprite_loop].direction, 0);
                    }
                    if (sprites[sprite_loop].direction == 0) {
                        if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].rotate_factor += 11; sprites[sprite_loop].x_position += 2; sprites[sprite_loop].y_position += -5; sprites[sprite_loop].width = 46; sprites[sprite_loop].height = 38; }
                        else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].rotate_factor += 11; sprites[sprite_loop].x_position += 3; sprites[sprite_loop].y_position += -4; }
                        else if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].rotate_factor += 11; sprites[sprite_loop].x_position += 4; sprites[sprite_loop].y_position += -3; }
                        else if (sprites[sprite_loop].timer == 7) { sprites[sprite_loop].action_state = 2; sprites[sprite_loop].x_position += 6; sprites[sprite_loop].y_position += -6; sprites[sprite_loop].timer = 0; sprites[sprite_loop].width = 31; sprites[sprite_loop].height = 37; sprites[sprite_loop].frame = EWULOSTRAPT3; }
                    }
                    else if (sprites[sprite_loop].direction == 1) {
                        if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].rotate_factor -= 11; sprites[sprite_loop].x_position += -2; sprites[sprite_loop].y_position += -5; sprites[sprite_loop].width = 46; sprites[sprite_loop].height = 38; }
                        else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].rotate_factor -= 11; sprites[sprite_loop].x_position += -3; sprites[sprite_loop].y_position += -4; }
                        else if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].rotate_factor -= 11; sprites[sprite_loop].x_position += -4; sprites[sprite_loop].y_position += -3; }
                        else if (sprites[sprite_loop].timer == 7) { sprites[sprite_loop].action_state = 2; sprites[sprite_loop].x_position += 6; sprites[sprite_loop].y_position += -6; sprites[sprite_loop].timer = 0; sprites[sprite_loop].width = 31; sprites[sprite_loop].height = 37; sprites[sprite_loop].frame = EWULOSTRAPT3; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 10) {
                        if (sprites[sprite_loop].direction == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 3; sprites[sprite_loop].x_position += -6; sprites[sprite_loop].y_position += 6; sprites[sprite_loop].width = 46; sprites[sprite_loop].height = 38; }
                        else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 3; sprites[sprite_loop].x_position += -6; sprites[sprite_loop].y_position += 6; sprites[sprite_loop].width = 46; sprites[sprite_loop].height = 38; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].direction == 0) {
                        if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].rotate_factor -= 11; sprites[sprite_loop].x_position += -4; sprites[sprite_loop].y_position += 3; }
                        else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].rotate_factor -= 11; sprites[sprite_loop].x_position += -3; sprites[sprite_loop].y_position += 4; }
                        else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].rotate_factor -= 11; sprites[sprite_loop].x_position += -2; sprites[sprite_loop].y_position += 5; sprites[sprite_loop].width = 43; sprites[sprite_loop].height = 21; }
                        else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].action_state = 4; sprites[sprite_loop].timer = 0; }
                    }
                    if (sprites[sprite_loop].direction == 1) {
                        if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].rotate_factor += 11; sprites[sprite_loop].x_position += 4; sprites[sprite_loop].y_position += 3; }
                        else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].rotate_factor += 11; sprites[sprite_loop].x_position += 3; sprites[sprite_loop].y_position += 4; }
                        else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].rotate_factor += 11; sprites[sprite_loop].x_position += 2; sprites[sprite_loop].y_position += 5; sprites[sprite_loop].width = 43; sprites[sprite_loop].height = 21; }
                        else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].action_state = 4; sprites[sprite_loop].timer = 0; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 4) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 40) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 0; }
                }
            }
            else if (sprites[sprite_loop].type == 35) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].action_state = 1; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
                        if (sprites[sprite_loop].direction == 0) {
                            if (sprites[sprite_loop].x_position - player.x_position - 40 >= 180) sprites[sprite_loop].x_speed = -20;
                            else if (sprites[sprite_loop].x_position - player.x_position - 40 >= 125) sprites[sprite_loop].x_speed = -15;
                            else sprites[sprite_loop].x_speed = -10;
                        }
                        else {
                            if (player.x_position - sprites[sprite_loop].x_position - 20 >= 180) sprites[sprite_loop].x_speed = 20;
                            else if (player.x_position - sprites[sprite_loop].x_position - 20 >= 125) sprites[sprite_loop].x_speed = 15;
                            else sprites[sprite_loop].x_speed = 10;
                        }
                        if (player.y_position < sprites[sprite_loop].y_position - 20) sprites[sprite_loop].y_speed = -14;
                        else if (player.y_position < sprites[sprite_loop].y_position) sprites[sprite_loop].y_speed = -10;
                        else sprites[sprite_loop].y_speed = -6;
                    }
                    else sprites[sprite_loop].y_speed += 2;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 35);
                }
            }
            else if (sprites[sprite_loop].type == 36) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].direction != 1 || sprites[sprite_loop].animation_state != 0) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprites[sprite_loop].biba += 2;
                    sprites[sprite_loop].width += 32;
                    if (sprites[sprite_loop].biba >= 10) {
                        if (sprites[sprite_loop].direction == 0) { sprites[sprite_loop].x_position += -16; sprites[sprite_loop].biba++; sprites[sprite_loop].width += 16; sprites[sprite_loop].action_state = 1; }
                        else { sprites[sprite_loop].x_position += 16; sprites[sprite_loop].biba++; sprites[sprite_loop].width += 16; sprites[sprite_loop].action_state = 1; }
                    }
                    sprite_colision(sprite_loop, 36);
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 36);
                }
            }
            else if (sprites[sprite_loop].type == 37) {
                if (sprites[sprite_loop].timer == 45) {
                    if (sprites[sprite_loop].direction == 0) initialize_sprite(39, (int)sprites[sprite_loop].x_position + 80, (int)sprites[sprite_loop].y_position - 9, 1, 0); 
                    else initialize_sprite(39, (int)sprites[sprite_loop].x_position - 90, (int)sprites[sprite_loop].y_position - 9, 0, 0); 
                }
                if (sprites[sprite_loop].timer == 76) sprites[sprite_loop].timer = 0;
                sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 38) {
                if (sprites[sprite_loop].timer == 45) {
                    if (sprites[sprite_loop].direction == 0) initialize_sprite(40, (int)sprites[sprite_loop].x_position - 9, (int)sprites[sprite_loop].y_position + 80, 0, 0); 
                    else initialize_sprite(40, (int)sprites[sprite_loop].x_position - 9, (int)sprites[sprite_loop].y_position - 90, 1, 0); 
                }
                if (sprites[sprite_loop].timer == 76) sprites[sprite_loop].timer = 0;
                sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 39) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 27) sprites[sprite_loop].frame = FLAMES08;
                else if (sprites[sprite_loop].timer == 28) sprites[sprite_loop].frame = FLAMES09;
                else if (sprites[sprite_loop].timer == 29) sprites[sprite_loop].active = 0;
                else if (sprites[sprite_loop].timer % 7 == 1) { sprites[sprite_loop].frame = FLAMES01; if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[FLAMETHROWER].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0); }
                else if (sprites[sprite_loop].timer % 7 == 2) sprites[sprite_loop].frame = FLAMES02;
                else if (sprites[sprite_loop].timer % 7 == 3) sprites[sprite_loop].frame = FLAMES03;
                else if (sprites[sprite_loop].timer % 7 == 4) sprites[sprite_loop].frame = FLAMES04;
                else if (sprites[sprite_loop].timer % 7 == 5) sprites[sprite_loop].frame = FLAMES05;
                else if (sprites[sprite_loop].timer % 7 == 6) sprites[sprite_loop].frame = FLAMES06;
                else if (sprites[sprite_loop].timer % 7 == 0) sprites[sprite_loop].frame = FLAMES07;
            }
            else if (sprites[sprite_loop].type == 40) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 27) sprites[sprite_loop].frame = FLAMES18;
                else if (sprites[sprite_loop].timer == 28) sprites[sprite_loop].frame = FLAMES19;
                else if (sprites[sprite_loop].timer == 29) sprites[sprite_loop].active = 0;
                else if (sprites[sprite_loop].timer % 7 == 1) { sprites[sprite_loop].frame = FLAMES11; if (inpl(sprite_loop)) play_sample((SAMPLE *)mydatafile[FLAMETHROWER].dat, (int)(100 * sound_volume_set / 255), 128, 1000, 0); }
                else if (sprites[sprite_loop].timer % 7 == 2) sprites[sprite_loop].frame = FLAMES12;
                else if (sprites[sprite_loop].timer % 7 == 3) sprites[sprite_loop].frame = FLAMES13;
                else if (sprites[sprite_loop].timer % 7 == 4) sprites[sprite_loop].frame = FLAMES14;
                else if (sprites[sprite_loop].timer % 7 == 5) sprites[sprite_loop].frame = FLAMES15;
                else if (sprites[sprite_loop].timer % 7 == 6) sprites[sprite_loop].frame = FLAMES16;
                else if (sprites[sprite_loop].timer % 7 == 0) sprites[sprite_loop].frame = FLAMES17;
            }
            else if (sprites[sprite_loop].type == 41) {
               if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = FLAMEMET1;
               else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = FLAMEMET2;
               else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = FLAMEMET3;
               else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = FLAMEMET4;
               sprites[sprite_loop].timer++;
               if (sprites[sprite_loop].direction == 1) {
               sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
               sprite_colision(sprite_loop, 41);
               }
               else {
               sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
               sprite_colision(sprite_loop, 41);
               }
            }
            else if (sprites[sprite_loop].type == 42) {
               if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = FLAMEMET1;
               else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = FLAMEMET2;
               else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = FLAMEMET3;
               else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = FLAMEMET4;
               if (sprites[sprite_loop].timer % 70 == 69) initialize_sprite(43, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position - 2, 0, 0);
               sprites[sprite_loop].timer++;
               if (sprites[sprite_loop].direction == 1) {
                   sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                   sprite_colision(sprite_loop, 42);
               }
               else {
                   sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                   sprite_colision(sprite_loop, 42);
               }
            }
            else if (sprites[sprite_loop].type == 43) {
                if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 0) sprites[sprite_loop].frame = FIRE6;
                    else if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = FIRE7;
                    else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].active = 0;
                    sprites[sprite_loop].timer++;
                }
                else {
                    if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].frame = FIRE1;
                    else if (sprites[sprite_loop].timer % 4 == 1) sprites[sprite_loop].frame = FIRE2;
                    else if (sprites[sprite_loop].timer % 4 == 2) sprites[sprite_loop].frame = FIRE3;
                    else if (sprites[sprite_loop].timer % 4 == 3) sprites[sprite_loop].frame = FIRE4;
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 43);
                }
            }
            else if (sprites[sprite_loop].type == 45) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.direction == 0 && sprites[sprite_loop].x_position - player.x_position-40 > 15 && sprites[sprite_loop].x_position - player.x_position-40 < 80) {
                        if (player.y_position + 400 > sprites[sprite_loop].y_position &&
                            player.y_position - 80 <= sprites[sprite_loop].y_position) {
                            sprites[sprite_loop].action_state = 1;
                            sprites[sprite_loop].y_speed = -25;
                        }
                    }
                    else if (player.direction == 1 && player.x_position - sprites[sprite_loop].x_position-37 > 15 && player.x_position - sprites[sprite_loop].x_position-37 < 80) {
                        if (player.y_position + 400 > sprites[sprite_loop].y_position &&
                            player.y_position - 80 <= sprites[sprite_loop].y_position) {
                            sprites[sprite_loop].action_state = 1;
                            sprites[sprite_loop].y_speed = -25;
                        }
                    }
                }
                if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].timer < 7) sprites[sprite_loop].y_speed +=1;
                    else if (sprites[sprite_loop].timer < 16) sprites[sprite_loop].y_speed +=2;
                    else sprites[sprite_loop].y_speed +=4;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].y_speed == -4) {
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 2;
                        sprites[sprite_loop].y_speed = 0;
                    }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) { 
                        sprites[sprite_loop].frame = EWUL_SQUID05;
                        sprites[sprite_loop].width = 27;
                        sprites[sprite_loop].height = 33;
                        sprites[sprite_loop].y_position += 6;
                        sprites[sprite_loop].x_position -= 2;
                    }
                    else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = EWUL_SQUID06;
                    else if (sprites[sprite_loop].timer == 3) {
                        sprites[sprite_loop].frame = EWUL_SQUID06;
                        sprites[sprite_loop].y_position += 4;                    
                    }
                    else if (sprites[sprite_loop].timer == 4) {
                        sprites[sprite_loop].y_position += 6;
                        sprites[sprite_loop].frame = EWUL_SQUID05;
                    }
                    else if (sprites[sprite_loop].timer == 5) {
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].width = 25;
                        sprites[sprite_loop].height = 59;
                        sprites[sprite_loop].y_position -=20;
                        sprites[sprite_loop].x_position += 2;
                        sprites[sprite_loop].action_state = 3;
                    }
                }
                if (sprites[sprite_loop].action_state == 3) {
                    if (sprites[sprite_loop].timer < 8) sprites[sprite_loop].y_speed +=1;
                    else if (sprites[sprite_loop].timer < 16) sprites[sprite_loop].y_speed +=2;
                    else sprites[sprite_loop].y_speed +=4;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].y_speed == 44) {
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 4;
                        sprites[sprite_loop].y_position = sprites[sprite_loop].biba;
                    }     
                }
                else if (sprites[sprite_loop].action_state == 4) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 10) {
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 0;
                    }
                }
            }
            else if (sprites[sprite_loop].type == 46) {
                if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 0 && sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = FIRE5;
                    else if (sprites[sprite_loop].timer == 2 && sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = FIRE6;
                    else if (sprites[sprite_loop].timer == 4 && sprites[sprite_loop].biba == 1) sprites[sprite_loop].frame = FIRE7;
                    else if (sprites[sprite_loop].timer >= 6 && sprites[sprite_loop].biba == 1) { sprites[sprite_loop].active = 0;  }
                    if (sprites[sprite_loop].timer == 0 && sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = SFIRE5;
                    else if (sprites[sprite_loop].timer == 2 && sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = SFIRE6;
                    else if (sprites[sprite_loop].timer == 4 && sprites[sprite_loop].biba == 2) sprites[sprite_loop].frame = SFIRE7;
                    else if (sprites[sprite_loop].timer >= 6 && sprites[sprite_loop].biba == 2) { sprites[sprite_loop].active = 0;  }
                    if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                else if (sprites[sprite_loop].action_state == 0) {
                    if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].frame = SFIRE1;
                    else if (sprites[sprite_loop].timer % 4 == 1) { sprites[sprite_loop].frame = SFIRE2; sprites[sprite_loop].y_speed++; }
                    else if (sprites[sprite_loop].timer % 4 == 2) sprites[sprite_loop].frame = SFIRE3;
                    else if (sprites[sprite_loop].timer % 4 == 3) { sprites[sprite_loop].frame = SFIRE4; sprites[sprite_loop].y_speed++; }
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].biba = 1;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 46);
                    if (sprites[sprite_loop].active == 1) { 
                        sprites[sprite_loop].biba = 2;
                        sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                        sprite_colision(sprite_loop, 46);
                    }
                }
            }
            else if (sprites[sprite_loop].type == 47) {
                if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 0) {
                        sprites[sprite_loop].x_position -= 18;
                        sprites[sprite_loop].y_position -= 17;
                        sprites[sprite_loop].frame = HADOUKEN03;
                    }
                    else if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = HADOUKEN04;
                    else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = HADOUKEN05;
                    else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = HADOUKEN06;
                    else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].frame = HADOUKEN07;
                    else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].active = 0;
                    if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                else {
                    if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].frame = HADOUKEN01;
                    else if (sprites[sprite_loop].timer % 4 == 2) sprites[sprite_loop].frame = HADOUKEN02;
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].biba = 2;
                    sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed / 2;
                    sprite_colision(sprite_loop, 47);
                    if (sprites[sprite_loop].active == 1) { 
                        sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed / 2;
                        sprite_colision(sprite_loop, 47);
                    }
                }
            }
            else if (sprites[sprite_loop].type == 48) {
                sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 48);
            }
            else if (sprites[sprite_loop].type == 49) {
                sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                sprite_colision(sprite_loop, 49);
                if (sprites[sprite_loop].active == 1) { 
                    sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed;
                    sprite_colision(sprite_loop, 49);
                }
            }
            else if (sprites[sprite_loop].type == 50) {
               if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = ICEMET01;
               else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = ICEMET02;
               else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = ICEMET03;
               else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = ICEMET04;
               sprites[sprite_loop].timer++;
               if (sprites[sprite_loop].direction == 1) {
               sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
               sprite_colision(sprite_loop, 50);
               }
               else {
               sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
               sprite_colision(sprite_loop, 50);
               }
            }
            else if (sprites[sprite_loop].type == 51) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position < 140 && player.y_position > sprites[sprite_loop].y_position && player.y_position - sprites[sprite_loop].y_position < 300) { sprites[sprite_loop].action_state = 1; play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position < 100 && player.y_position > sprites[sprite_loop].y_position && player.y_position - sprites[sprite_loop].y_position < 300) { sprites[sprite_loop].action_state = 1; play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].y_speed < 39) sprites[sprite_loop].y_speed += 4;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                    if (sprites[sprite_loop].timer > 5) sprite_colision(sprite_loop, 51);
                    if (sprites[sprite_loop].active == 1) {
                        sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                        if (sprites[sprite_loop].timer > 5) sprite_colision(sprite_loop, 51);
                    }
                }    
                else if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].active = 0;
                    else sprites[sprite_loop].timer++;
                }
            }
            else if (sprites[sprite_loop].type == 52) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position < 140 && player.y_position > sprites[sprite_loop].y_position && player.y_position - sprites[sprite_loop].y_position < 300) { sprites[sprite_loop].action_state = 1; play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position < 100 && player.y_position > sprites[sprite_loop].y_position && player.y_position - sprites[sprite_loop].y_position < 300) { sprites[sprite_loop].action_state = 1; play_sample((SAMPLE *)mydatafile[ICEFALL].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].y_speed < 39) sprites[sprite_loop].y_speed += 4;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                    if (sprites[sprite_loop].timer > 5) sprite_colision(sprite_loop, 52);
                    if (sprites[sprite_loop].active == 1) {
                        sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                        if (sprites[sprite_loop].timer > 5) sprite_colision(sprite_loop, 52);
                    }
                }    
                else if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].active = 0;
                    else sprites[sprite_loop].timer++;
                }
            }
            else if (sprites[sprite_loop].type == 54) {
                if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                else sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprites[sprite_loop].y_position -= sprites[sprite_loop].y_speed;
                if (sprites[sprite_loop].x_position < 0 || sprites[sprite_loop].y_position < 0 || sprites[sprite_loop].x_position - player.x_position > 640) sprites[sprite_loop].active = 0;
                else sprite_colision(sprite_loop, 54);
            }
            else if (sprites[sprite_loop].type == 55) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 6 == 1) sprites[sprite_loop].frame = PUMPKIN01;
                    else if (sprites[sprite_loop].timer % 6 == 3) sprites[sprite_loop].frame = PUMPKIN02;
                    else if (sprites[sprite_loop].timer % 6 == 5) sprites[sprite_loop].frame = PUMPKIN03;
                    sprites[sprite_loop].x_speed = 10;
                    if (player.on_ground == TRUE && (int)player.y_position + 60 == (int)sprites[sprite_loop].y_position) {
                        if (player.x_position > sprites[sprite_loop].x_position && player.x_position - sprites[sprite_loop].x_position - 24 < 200) sprites[sprite_loop].x_speed = 20;
                        else if (player.x_position < sprites[sprite_loop].x_position && sprites[sprite_loop].x_position - player.x_position - 40 < 200) sprites[sprite_loop].x_speed = 20;
                    }
                    if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed;
                    else sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprite_colision(sprite_loop, 55);
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 30) { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].timer = sprites[sprite_loop].biba; }
                }
            }
            else if (sprites[sprite_loop].type == 56) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].biba += 30;
                    if (sprites[sprite_loop].biba > 256) sprites[sprite_loop].biba = 256;                    
                    if (sprites[sprite_loop].timer == 13) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed / 2;
                    else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed / 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                    sprite_colision(sprite_loop, 56);
                    if (sprites[sprite_loop].active == 1) {
                        if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed / 2;
                        else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed / 2;
                        sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                        sprite_colision(sprite_loop, 56);
                    }
                }
            }
            else if (sprites[sprite_loop].type == 57) {
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                sprites[sprite_loop].y_speed++;
                sprite_colision(sprite_loop, 57);
            }
            else if (sprites[sprite_loop].type == 58) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer % 2 == 0 && sprites[sprite_loop].x_speed != 0) {
                    if (sprites[sprite_loop].x_speed > 0) sprites[sprite_loop].x_speed--;
                    else sprites[sprite_loop].x_speed++;
                }
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                sprites[sprite_loop].y_speed += 0.5;
                sprite_colision(sprite_loop, 58);
            }
            else if (sprites[sprite_loop].type == 60) {    
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.x_position + 40 < sprites[sprite_loop].x_position + 31 && sprites[sprite_loop].x_position + 31 - player.x_position + 40 <= 200) sprites[sprite_loop].action_state = 1;
                    else if (player.x_position > sprites[sprite_loop].x_position + 31 && player.x_position - sprites[sprite_loop].x_position + 31 <= 200) sprites[sprite_loop].action_state = 1;
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (player.x_position + 40 < sprites[sprite_loop].x_position + 31 && sprites[sprite_loop].x_position + 31 - player.x_position + 40 > 200) sprites[sprite_loop].action_state = 2;
                    else if (player.x_position > sprites[sprite_loop].x_position + 31 && player.x_position - sprites[sprite_loop].x_position + 31 > 200) sprites[sprite_loop].action_state = 2;
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    if (player.x_position + 40 < sprites[sprite_loop].x_position + 31 && sprites[sprite_loop].x_position + 31 - player.x_position + 40 <= 200) sprites[sprite_loop].action_state = 1;
                    else if (player.x_position > sprites[sprite_loop].x_position + 31 && player.x_position - sprites[sprite_loop].x_position + 31 <= 200) sprites[sprite_loop].action_state = 1;
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 12) {
                        if (sprites[sprite_loop].biba == 0) initialize_sprite(200, (int)sprites[sprite_loop].x_position + 28, (int)sprites[sprite_loop].y_position + 50, 0, 0);
                        else if (sprites[sprite_loop].biba > 5) if (player.cards[sprites[sprite_loop].biba] == 0) initialize_sprite(69, (int)sprites[sprite_loop].x_position + 28, (int)sprites[sprite_loop].y_position + 20, 0, sprites[sprite_loop].biba);
                        }
                    else if (sprites[sprite_loop].timer == 18) sprites[sprite_loop].action_state = 4;
                }
            }
            else if (sprites[sprite_loop].type == 64) {
                if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position -= 20;
                else sprites[sprite_loop].x_position += 20;
                sprite_colision(sprite_loop, 64);
                if (sprites[sprite_loop].active == 1) {
                      if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position -= 20;
                      else sprites[sprite_loop].x_position += 20;
                      sprite_colision(sprite_loop, 64);                          
                }
            }
            else if (sprites[sprite_loop].type == 65) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].direction == 0) {
                        sprites[sprite_loop].y_speed++;
                        if (sprites[sprite_loop].y_speed == 2) sprites[sprite_loop].direction = 1;
                    }
                    else {
                        sprites[sprite_loop].y_speed--;
                        if (sprites[sprite_loop].y_speed == -2) sprites[sprite_loop].direction = 0;
                    }
                }
                else {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) sprites[sprite_loop].active = 0;
                }
            }
            else if (sprites[sprite_loop].type == 66) {
                if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SANDMORRO3;
                    else if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].frame = SANDMORRO4;
                    else if (sprites[sprite_loop].timer == 9) sprites[sprite_loop].active = 0;
                }
            }
            else if (sprites[sprite_loop].type == 67) {
                if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].x_speed-=18;
                    sprites[sprite_loop].y_speed+=20;
                    if (sprites[sprite_loop].x_speed == 2) {
                        sprites[sprite_loop].x_speed = 200;
                        sprites[sprite_loop].y_speed = 0;
                        sprites[sprite_loop].frame++;
                        sprites[sprite_loop].direction++;
                        if (sprites[sprite_loop].direction > ICEHOLDER4) sprites[sprite_loop].direction = NULO;
                        if (sprites[sprite_loop].frame > ICEHOLDER4) { sprites[sprite_loop].active = 0; if (player.cards[sprites[sprite_loop].biba] == 0) initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 6, 0, sprites[sprite_loop].biba); }
                    }
                }
            }
            else if (sprites[sprite_loop].type == 69) {
              if (sprites[sprite_loop].action_state == 0) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].y_speed > 4) sprites[sprite_loop].y_position = (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].y_speed);
                else if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].y_position = (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].y_speed);
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                sprite_colision(sprite_loop, 69);
                if (sprites[sprite_loop].timer % 4 == 0) {
                  if (sprites[sprite_loop].direction == 0) {
                    sprites[sprite_loop].y_speed++;
                    if (sprites[sprite_loop].y_speed == 2) sprites[sprite_loop].direction = 1;
                  }
                  else {
                    sprites[sprite_loop].y_speed--;
                    if (sprites[sprite_loop].y_speed == -2) sprites[sprite_loop].direction = 0;
                  }
                }
              }
              else if (sprites[sprite_loop].action_state == 3) {
                  sprites[sprite_loop].strength -= 30;
                  if (sprites[sprite_loop].strength < 0) { player.cards[sprites[sprite_loop].biba] = 1; sprites[sprite_loop].active = 0;}
              }
            }
            else if (sprites[sprite_loop].type == 70) {
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                if (sprites[sprite_loop].y_position < Map.water_position) sprites[sprite_loop].active = 0;
            }
            else if (sprites[sprite_loop].type == 71) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (player.x_position - sprites[sprite_loop].x_position - 36 > 0 && player.x_position - sprites[sprite_loop].x_position - 36 < 140) { initialize_sprite(72, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, 0, 0); sprites[sprite_loop].action_state = 1; }
                    else if (sprites[sprite_loop].x_position - player.x_position - 40 > 0 && sprites[sprite_loop].x_position - player.x_position - 40 < 140) { initialize_sprite(72, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, 0, 0); sprites[sprite_loop].action_state = 1; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 90) { sprites[sprite_loop].action_state = 0; sprites[sprite_loop].timer = 0; }
                }
            }
            else if (sprites[sprite_loop].type == 72) {
                if (sprites[sprite_loop].action_state == 0) sprites[sprite_loop].action_state = 1;
                if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) { sprites[sprite_loop].height+=17; sprites[sprite_loop].y_position-=17; }
                    else if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].height+=17; sprites[sprite_loop].y_position-=17; }
                    else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].height+=17; sprites[sprite_loop].y_position-=17; }
                    else if (sprites[sprite_loop].timer >= 4) {
                        if (sprites[sprite_loop].y_position <= player.y_position) { sprites[sprite_loop].action_state = 2; sprites[sprite_loop].timer = 0; }
                        else { sprites[sprite_loop].y_position-=17; sprites[sprite_loop].y_speed+=17; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].action_state = 3; sprites[sprite_loop].frame = SEAHORSE2; sprites[sprite_loop].width = 40; sprites[sprite_loop].height = 41; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
                        sprites[sprite_loop].width = 30; sprites[sprite_loop].height = 30; sprites[sprite_loop].frame = SEAHORSE3;
                        if (player.x_position > sprites[sprite_loop].x_position) sprites[sprite_loop].x_speed = 25;
                        else sprites[sprite_loop].x_speed = -25;
                    }
                    else if (sprites[sprite_loop].timer >= 10) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    if (sprites[sprite_loop].x_position - player.x_position - 40 > 640) sprites[sprite_loop].active = 0;
                    else if (player.x_position - sprites[sprite_loop].x_position - 30 > 640) sprites[sprite_loop].active = 0;
                }
            }
            else if (sprites[sprite_loop].type == 75) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
			  sprites[sprite_loop].biba += 42;
                    if (sprites[sprite_loop].timer == 6) {
			      sprites[sprite_loop].biba = 255;
				sprites[sprite_loop].timer = 0;
				sprites[sprite_loop].action_state = 1;
				sprites[sprite_loop].frame = LASTBALL1;
                    }
                }
		    else if (sprites[sprite_loop].action_state == 1) {
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer >= 8) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
            }
            else if (sprites[sprite_loop].type == 77) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
			        sprites[sprite_loop].biba += 32;
                    if (sprites[sprite_loop].timer == 8) {
			            sprites[sprite_loop].biba = 255;
				        sprites[sprite_loop].timer = 0;
				        sprites[sprite_loop].action_state = 1;
                    }
                }
		        else if (sprites[sprite_loop].action_state == 1) {
			        sprites[sprite_loop].timer++;
			        if (sprites[sprite_loop].timer == 1) {
				        sprites[sprite_loop].x_position += -15;
				        sprites[sprite_loop].y_position += -3;
                    }
			        else if (sprites[sprite_loop].timer == 3) {
				        sprites[sprite_loop].x_position += -13;
				        sprites[sprite_loop].y_position += -9;
	                }
			  else if (sprites[sprite_loop].timer == 5) {
				sprites[sprite_loop].x_position += -8;
				sprites[sprite_loop].y_position += -12;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 6) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 16; }
			  }
			  else if (sprites[sprite_loop].timer == 7) {
				sprites[sprite_loop].x_position += -3;
				sprites[sprite_loop].y_position += -15;
			  }
			  else if (sprites[sprite_loop].timer == 9) {
				sprites[sprite_loop].x_position += 3;
				sprites[sprite_loop].y_position += -15;
			  }
			  else if (sprites[sprite_loop].timer == 11) {
				sprites[sprite_loop].x_position += 9;
				sprites[sprite_loop].y_position += -13;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 5) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 15; }
			  }
			  else if (sprites[sprite_loop].timer == 13) {
				sprites[sprite_loop].x_position += 12;
				sprites[sprite_loop].y_position += -8;
			  }
			  else if (sprites[sprite_loop].timer == 15) {
				sprites[sprite_loop].x_position += 15;
				sprites[sprite_loop].y_position += -3;
			  }
			  else if (sprites[sprite_loop].timer == 17) {
				sprites[sprite_loop].x_position += 15;
				sprites[sprite_loop].y_position += 3;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 4) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 14; }
			  }
			  else if (sprites[sprite_loop].timer == 19) {
				sprites[sprite_loop].x_position += 13;
				sprites[sprite_loop].y_position += 9;
			  }
			  else if (sprites[sprite_loop].timer == 21) {
				sprites[sprite_loop].x_position += 8;
				sprites[sprite_loop].y_position += 12;
			  }
			  else if (sprites[sprite_loop].timer == 23) {
				sprites[sprite_loop].x_position += 3;
				sprites[sprite_loop].y_position += 15;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 3) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 13; }
			  }
			  else if (sprites[sprite_loop].timer == 25) {
				sprites[sprite_loop].x_position += -3;
				sprites[sprite_loop].y_position += 15;
			  }
			  else if (sprites[sprite_loop].timer == 27) {
				sprites[sprite_loop].x_position += -9;
				sprites[sprite_loop].y_position += 13;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 2) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 12; }
			  }
			  else if (sprites[sprite_loop].timer == 29) {
				sprites[sprite_loop].x_position += -12;
				sprites[sprite_loop].y_position += 8;
			  }
			  else if (sprites[sprite_loop].timer == 31) {
				sprites[sprite_loop].x_position += -15;
				sprites[sprite_loop].y_position += 3;
				sprites[sprite_loop].timer = -1;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 1) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 11; }
			  	sprites[sprite_loop].rotate_factor++;
				}
		    }
		    else if (sprites[sprite_loop].action_state == 11) {
			  if (sprites[sprite_loop].x_position > 1080) sprites[sprite_loop].x_position -= 2;
			  if (sprites[sprite_loop].x_position < 1080) sprites[sprite_loop].x_position = 1080;
			  if (sprites[sprite_loop].y_position < 410) sprites[sprite_loop].y_position += 6;
			  if (sprites[sprite_loop].y_position > 410) sprites[sprite_loop].y_position = 410;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 12) {
			  if (sprites[sprite_loop].x_position < 1240) sprites[sprite_loop].x_position += 2;
			  if (sprites[sprite_loop].x_position > 1240) sprites[sprite_loop].x_position = 1240;
			  if (sprites[sprite_loop].y_position < 330) sprites[sprite_loop].y_position += 4;
			  if (sprites[sprite_loop].y_position > 330) sprites[sprite_loop].y_position = 330;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 13) {
			  if (sprites[sprite_loop].x_position < 1400) sprites[sprite_loop].x_position += 6;
			  if (sprites[sprite_loop].x_position > 1400) sprites[sprite_loop].x_position = 1400;
			  if (sprites[sprite_loop].y_position < 410) sprites[sprite_loop].y_position += 6;
			  if (sprites[sprite_loop].y_position > 410) sprites[sprite_loop].y_position = 410;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 14) {
			  if (sprites[sprite_loop].x_position < 1560) sprites[sprite_loop].x_position += 10;
			  if (sprites[sprite_loop].x_position > 1560) sprites[sprite_loop].x_position = 1560;
			  if (sprites[sprite_loop].y_position < 290) sprites[sprite_loop].y_position += 4;
			  if (sprites[sprite_loop].y_position > 290) sprites[sprite_loop].y_position = 290;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 15) {
			  if (sprites[sprite_loop].x_position < 1360) sprites[sprite_loop].x_position += 6;
			  if (sprites[sprite_loop].x_position > 1360) sprites[sprite_loop].x_position = 1360;
			  if (sprites[sprite_loop].y_position < 170) sprites[sprite_loop].y_position += 2;
			  if (sprites[sprite_loop].y_position > 170) sprites[sprite_loop].y_position = 170;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 16) {
			  if (sprites[sprite_loop].x_position > 920) sprites[sprite_loop].x_position -= 6;
			  if (sprites[sprite_loop].x_position < 920) sprites[sprite_loop].x_position = 920;
			  if (sprites[sprite_loop].y_position < 290) sprites[sprite_loop].y_position += 4;
			  if (sprites[sprite_loop].y_position > 290) sprites[sprite_loop].y_position = 290;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
            }
            else if (sprites[sprite_loop].type == 78) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
			        sprites[sprite_loop].biba += 32;
                    if (sprites[sprite_loop].timer == 8) {
			            sprites[sprite_loop].biba = 255;
				        sprites[sprite_loop].timer = 0;
				        sprites[sprite_loop].action_state = 1;
                    }
                }
		        else if (sprites[sprite_loop].action_state == 1) {
			        sprites[sprite_loop].timer++;
			        if (sprites[sprite_loop].timer == 1) {
				        sprites[sprite_loop].x_position -= -15;
				        sprites[sprite_loop].y_position += -3;
                    }
			        else if (sprites[sprite_loop].timer == 3) {
				        sprites[sprite_loop].x_position -= -13;
				        sprites[sprite_loop].y_position += -9;
	                }
			  else if (sprites[sprite_loop].timer == 5) {
				sprites[sprite_loop].x_position -= -8;
				sprites[sprite_loop].y_position += -12;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 6) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 16; }
			  }
			  else if (sprites[sprite_loop].timer == 7) {
				sprites[sprite_loop].x_position -= -3;
				sprites[sprite_loop].y_position += -15;
			  }
			  else if (sprites[sprite_loop].timer == 9) {
				sprites[sprite_loop].x_position -= 3;
				sprites[sprite_loop].y_position += -15;
			  }
			  else if (sprites[sprite_loop].timer == 11) {
				sprites[sprite_loop].x_position -= 9;
				sprites[sprite_loop].y_position += -13;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 5) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 15; }
			  }
			  else if (sprites[sprite_loop].timer == 13) {
				sprites[sprite_loop].x_position -= 12;
				sprites[sprite_loop].y_position += -8;
			  }
			  else if (sprites[sprite_loop].timer == 15) {
				sprites[sprite_loop].x_position -= 15;
				sprites[sprite_loop].y_position += -3;
			  }
			  else if (sprites[sprite_loop].timer == 17) {
				sprites[sprite_loop].x_position -= 15;
				sprites[sprite_loop].y_position += 3;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 4) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 14; }
			  }
			  else if (sprites[sprite_loop].timer == 19) {
				sprites[sprite_loop].x_position -= 13;
				sprites[sprite_loop].y_position += 9;
			  }
			  else if (sprites[sprite_loop].timer == 21) {
				sprites[sprite_loop].x_position -= 8;
				sprites[sprite_loop].y_position += 12;
			  }
			  else if (sprites[sprite_loop].timer == 23) {
				sprites[sprite_loop].x_position -= 3;
				sprites[sprite_loop].y_position += 15;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 3) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 13; }
			  }
			  else if (sprites[sprite_loop].timer == 25) {
				sprites[sprite_loop].x_position -= -3;
				sprites[sprite_loop].y_position += 15;
			  }
			  else if (sprites[sprite_loop].timer == 27) {
				sprites[sprite_loop].x_position -= -9;
				sprites[sprite_loop].y_position += 13;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 2) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 12; }
			  }
			  else if (sprites[sprite_loop].timer == 29) {
				sprites[sprite_loop].x_position -= -12;
				sprites[sprite_loop].y_position += 8;
			  }
			  else if (sprites[sprite_loop].timer == 31) {
				sprites[sprite_loop].x_position -= -15;
				sprites[sprite_loop].y_position += 3;
				sprites[sprite_loop].timer = -1;
				if (sprites[sprite_loop].rotate_factor == 2 && sprites[sprite_loop].direction == 1) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 11; }
			  	sprites[sprite_loop].rotate_factor++;
				}
		    }
		    else if (sprites[sprite_loop].action_state == 13) {
			  if (sprites[sprite_loop].x_position > 1080) sprites[sprite_loop].x_position -= 6;
			  if (sprites[sprite_loop].x_position < 1080) sprites[sprite_loop].x_position = 1080;
			  if (sprites[sprite_loop].y_position < 410) sprites[sprite_loop].y_position += 6;
			  if (sprites[sprite_loop].y_position > 410) sprites[sprite_loop].y_position = 410;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 12) {
			  if (sprites[sprite_loop].x_position > 1240) sprites[sprite_loop].x_position -= 2;
			  if (sprites[sprite_loop].x_position < 1240) sprites[sprite_loop].x_position = 1240;
			  if (sprites[sprite_loop].y_position < 330) sprites[sprite_loop].y_position += 4;
			  if (sprites[sprite_loop].y_position > 330) sprites[sprite_loop].y_position = 330;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 11) {
			  if (sprites[sprite_loop].x_position < 1400) sprites[sprite_loop].x_position += 2;
			  if (sprites[sprite_loop].x_position > 1400) sprites[sprite_loop].x_position = 1400;
			  if (sprites[sprite_loop].y_position < 410) sprites[sprite_loop].y_position += 6;
			  if (sprites[sprite_loop].y_position > 410) sprites[sprite_loop].y_position = 410;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 16) {
			  if (sprites[sprite_loop].x_position < 1560) sprites[sprite_loop].x_position += 6;
			  if (sprites[sprite_loop].x_position > 1560) sprites[sprite_loop].x_position = 1560;
			  if (sprites[sprite_loop].y_position < 290) sprites[sprite_loop].y_position += 4;
			  if (sprites[sprite_loop].y_position > 290) sprites[sprite_loop].y_position = 290;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 15) {
			  if (sprites[sprite_loop].x_position > 1120) sprites[sprite_loop].x_position -= 6;
			  if (sprites[sprite_loop].x_position < 1120) sprites[sprite_loop].x_position = 1120;
			  if (sprites[sprite_loop].y_position < 170) sprites[sprite_loop].y_position += 2;
			  if (sprites[sprite_loop].y_position > 170) sprites[sprite_loop].y_position = 170;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
		    else if (sprites[sprite_loop].action_state == 14) {
			  if (sprites[sprite_loop].x_position > 920) sprites[sprite_loop].x_position -= 10;
			  if (sprites[sprite_loop].x_position < 920) sprites[sprite_loop].x_position = 920;
			  if (sprites[sprite_loop].y_position < 290) sprites[sprite_loop].y_position += 4;
			  if (sprites[sprite_loop].y_position > 290) sprites[sprite_loop].y_position = 290;
			  sprites[sprite_loop].timer++;
			  if (sprites[sprite_loop].timer > 85) {
				sprites[sprite_loop].biba -= 42;
				if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].active = 0;
			  }
		    }
            }
            else if (sprites[sprite_loop].type == 79) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    sprites[sprite_loop].biba += 60;
                    if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;                    
                    if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed / 2;
                    else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed / 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                    sprite_colision(sprite_loop, 79);
                    if (sprites[sprite_loop].active == 1) {
                        if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed / 2;
                        else sprites[sprite_loop].x_position -= sprites[sprite_loop].x_speed / 2;
                        sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed / 2;
                        sprite_colision(sprite_loop, 79);
                    }
                }
		    if (sprites[sprite_loop].x_position < 840 || sprites[sprite_loop].y_position < -80 || sprites[sprite_loop].y_position > 680) sprites[sprite_loop].active = 0;
            }
            else if (sprites[sprite_loop].type == 100) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = SHOT_0_2;
                else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SHOT_0_3;
                else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].active = 0;  }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 101) {
                sprites[sprite_loop].strength -= 16;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 2;
                if (sprites[sprite_loop].timer == 2) {
                    if (sprites[sprite_loop].frame == WIND_SHOT01) sprites[sprite_loop].frame = WIND_SHOT03;
                    else if (sprites[sprite_loop].frame == WIND_SHOT02) sprites[sprite_loop].frame = WIND_SHOT03;
                    else sprites[sprite_loop].frame = WIND_SHOT01;
                }
                else if (sprites[sprite_loop].timer == 5) {
                    if (sprites[sprite_loop].frame == WIND_SHOT01) sprites[sprite_loop].frame = WIND_SHOT03;
                    else if (sprites[sprite_loop].frame == WIND_SHOT02) sprites[sprite_loop].frame = WIND_SHOT03;
                    else sprites[sprite_loop].frame = WIND_SHOT02;
                }
                else if (sprites[sprite_loop].timer == 10) {
                    if (sprites[sprite_loop].frame == WIND_SHOT01) sprites[sprite_loop].frame = WIND_SHOT03;
                    else if (sprites[sprite_loop].frame == WIND_SHOT02) sprites[sprite_loop].frame = WIND_SHOT03;
                    else sprites[sprite_loop].frame = WIND_SHOT01;
                }
                if (sprites[sprite_loop].timer == 16) sprites[sprite_loop].active = 0;
                else sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 102) {
                sprites[sprite_loop].strength -= 16;
                if (sprites[sprite_loop].timer < 16) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                }
                else if (sprites[sprite_loop].timer < 9) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 2;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 2;
                }
                else if (sprites[sprite_loop].timer < 4) {
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 3;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 3;
                }
                if (sprites[sprite_loop].timer == 16) { sprites[sprite_loop].active = 0; fire_key = 0; }
                else sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 104) {
              if (sprites[sprite_loop].strength == 1) sprites[sprite_loop].active = 0;
              else if (sprites[sprite_loop].action_state == 1) {
                if (sprites[sprite_loop].timer == 2) {
                    sprites[sprite_loop].frame = WATERSHOTHIT2;
                    sprites[sprite_loop].width = 16;
                    sprites[sprite_loop].height = 32;
                    if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].x_position += 6;
                    sprites[sprite_loop].y_position -= 2;
                }
                else if (sprites[sprite_loop].timer == 4) {
                    sprites[sprite_loop].frame = WATERSHOTHIT3;
                    initialize_sprite(58, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, sprites[sprite_loop].direction, 13);
                    initialize_sprite(58, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position + 15, sprites[sprite_loop].direction, 8);
                }
                if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].active = 0;
                else sprites[sprite_loop].timer++;
              }
              else if (sprites[sprite_loop].action_state == 2) {
                if (sprites[sprite_loop].timer == 2) {
                    sprites[sprite_loop].frame = WATERSHOTHIT5;
                    sprites[sprite_loop].width = 32;
                    sprites[sprite_loop].height = 16;
                    sprites[sprite_loop].y_position += 6;
                    sprites[sprite_loop].x_position -= 2;
                }
                else if (sprites[sprite_loop].timer == 4) {
                    sprites[sprite_loop].frame = WATERSHOTHIT6;
                    initialize_sprite(57, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, 0, 0);
                    initialize_sprite(57, (int)sprites[sprite_loop].x_position + 15, (int)sprites[sprite_loop].y_position, 1, 0);
                }
                if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].active = 0;
                else sprites[sprite_loop].timer++;
              }
              else if (sprites[sprite_loop].action_state == 3) {
                if (sprites[sprite_loop].timer == 2) {
                    sprites[sprite_loop].frame = WATERSHOTHIT8;
                    sprites[sprite_loop].width = 32;
                    sprites[sprite_loop].height = 16;
                    //sprites[sprite_loop].y_position += 6;
                    sprites[sprite_loop].x_position -= 2;
                }
                else if (sprites[sprite_loop].timer == 4) {
                    sprites[sprite_loop].frame = WATERSHOTHIT9;
                    initialize_sprite(57, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position + 16, 0, 666);
                    initialize_sprite(57, (int)sprites[sprite_loop].x_position + 15, (int)sprites[sprite_loop].y_position + 16, 1, 666);
                }
                if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].active = 0;
                else sprites[sprite_loop].timer++;
              }
            }
            else if (sprites[sprite_loop].type == 200) {
                sprites[sprite_loop].y_position = (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].y_speed * 5);
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                sprite_colision(sprite_loop, 200);
            }
            else if (sprites[sprite_loop].type == 201) {
                sprites[sprite_loop].y_position = (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].y_speed * 5);
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                sprite_colision(sprite_loop, 200);
            }
            else if (sprites[sprite_loop].type == 202) {
                sprites[sprite_loop].timer++;
                sprites[sprite_loop].y_position = (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].y_speed * 5);
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                sprite_colision(sprite_loop, 202);
            }
            else if (sprites[sprite_loop].type == 113) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = SHOT_13_2;
                else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SHOT_13_3;
                else if (sprites[sprite_loop].timer >= 5) { sprites[sprite_loop].active = 0; }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 120) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = WTSHOT03;
                else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].active = 0;  }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 112) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = TOLETED_2;
                else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = TOLETED_3;
                else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].active = 0;  }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 404) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SPLASH2;
                else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].frame = SPLASH3;
                else if (sprites[sprite_loop].timer == 7) sprites[sprite_loop].active = 0;
            }
            else if (sprites[sprite_loop].type == 501) {
                if (sprites[sprite_loop].timer <= 0) sprites[sprite_loop].active = 0;
                else sprites[sprite_loop].timer--;
            }
            else if (sprites[sprite_loop].type == 666) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = DA401;
                else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = DA402;
                else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].active = 0;  }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 667) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = DA601;
                else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = DA602;
                else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].active = 0;  }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 301) {
                sprites[sprite_loop].rotate_factor += 16;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 3;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 3;
                sprites[sprite_loop].y_speed++;
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                if (sprites[sprite_loop].active == 1) sprite_colision(sprite_loop, 301);
            }
            else if (sprites[sprite_loop].type == 302) {
                sprites[sprite_loop].rotate_factor += 4;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 3;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 3;
                sprites[sprite_loop].y_speed++;
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                if (sprites[sprite_loop].active == 1) sprite_colision(sprite_loop, 301);
            }
            else if (sprites[sprite_loop].type == 303) {
                sprites[sprite_loop].rotate_factor += 8;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 3;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 3;
                sprites[sprite_loop].y_speed++;
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                sprite_colision(sprite_loop, 301);
            }
            else if (sprites[sprite_loop].type == 304) {
                sprites[sprite_loop].rotate_factor += 32;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 3;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 3;
                sprites[sprite_loop].y_speed++;
                if (sprites[sprite_loop].y_position > (Map.height * 20) || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
                if (sprites[sprite_loop].active == 1) sprite_colision(sprite_loop, 301);
            }
            else if (sprites[sprite_loop].type == 305) {
                sprites[sprite_loop].timer++;
                sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed * 2;
                sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed * 2;
                sprites[sprite_loop].y_speed++;
                if (sprites[sprite_loop].y_position > Map.limitdown || sprites[sprite_loop].y_position < 0) sprites[sprite_loop].active = 0;
            }
            else if (sprites[sprite_loop].type == 310) {
                if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = PARTICLEDESTROY2;
                else if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].active = 0;  }
                if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
            }
            else if (sprites[sprite_loop].type == 400) {
                if (sprites[sprite_loop].x_speed > 0) {
                    if (sprites[sprite_loop].x_speed > 48) sprites[sprite_loop].x_speed = 48;
                    else sprites[sprite_loop].x_speed -=2;
                    sprites[sprite_loop + 1].timer += 4;
                }
                if (sprites[sprite_loop].x_speed < 0) sprites[sprite_loop].x_speed = 0;
                //bibinhalinda = sprites[sprite_loop].rotate_factor += (unsigned char)sprites[sprite_loop].x_speed;
            }
            else if (sprites[sprite_loop].type == 401) {
                if (sprites[sprite_loop].timer > 0) {
                    sprites[sprite_loop].height = 200 - sprites[sprite_loop].timer;
                    if (sprites[sprite_loop].timer > 180) sprites[sprite_loop].timer = 180;
                    char col = 'p';
                    if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
                    else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
                    if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position >= 80)) col = 'n';
                    else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';
                    if (col == 'n')
                    sprites[sprite_loop].timer--;
                    else {
                        sprites[sprite_loop].height = (int)(player.y_position - sprites[sprite_loop].y_position);
                        bibinhalinda = (int)(sprites[sprite_loop].height + sprites[sprite_loop].y_position);
                    }
                }
                else sprites[sprite_loop].height = 200;
            }
            else if (sprites[sprite_loop].type == 999) {
                 if (sprites[sprite_loop].timer == doorrecord) {
                     if (stopall == 1 && looper > 0 && looper < 9) rest(1);
                     else if (stopall == 1 && looper > 47 && looper < 56) rest(1);
                     else if (stopall == 1 && looper == 56) { call_event = sprites[sprite_loop].timer; sprites[sprite_loop].timer = -1; }
                     else if (stopall == 1) rest(1);
                 }
            }
            else if (sprites[sprite_loop].type == 1000 && sprites[sprite_loop].x_position < 2500) {
                 if (sprites[sprite_loop].timer == doorrecord) {
                     if (stopall == 1 && looper > 0 && looper < 9) rest(1);
                     else if (stopall == 1 && looper > 47 && looper < 56) rest(1);
                     else if (stopall == 1 && looper == 56) {
				 call_event = sprites[sprite_loop].timer;
				 sprites[sprite_loop].timer = -1;
			   }
                     else if (stopall == 1)rest(1);
                 }
            }
            else if (sprites[sprite_loop].type == 2000) {
                 if (sprites[sprite_loop].timer > 0 && sprites[sprite_loop].timer <= 10) {
                     sprites[sprite_loop].timer++;
                 }
                 else if (sprites[sprite_loop].timer > 10) {
                      if ((sprites[sprite_loop].timer % 4) == 0) { initialize_sprite(113, ((int)sprites[sprite_loop].x_position - 5), ((int)sprites[sprite_loop].y_position - 7), 0, 0); initialize_sprite(113, ((int)sprites[sprite_loop].x_position + 63), ((int)sprites[sprite_loop].y_position), 0, 0); }
                      sprites[sprite_loop].y_position += 12;
                      if (sprites[sprite_loop].y_position >= 540) sprites[sprite_loop].active = 0;
                      else sprites[sprite_loop].timer++;
                 }
            }
            else if (sprites[sprite_loop].type == 2001) {
                 if (sprites[sprite_loop].timer > 0 && sprites[sprite_loop].timer <= 10) {
                     sprites[sprite_loop].timer++;
                 }
                 else if (sprites[sprite_loop].timer > 10) {
                      if ((sprites[sprite_loop].timer % 4) == 0) { initialize_sprite(113, ((int)sprites[sprite_loop].x_position - 5), ((int)sprites[sprite_loop].y_position - 7), 0, 0); initialize_sprite(113, ((int)sprites[sprite_loop].x_position + 13), ((int)sprites[sprite_loop].y_position), 0, 0); }
                      sprites[sprite_loop].y_position += 12;
                      if (sprites[sprite_loop].y_position >= 540) sprites[sprite_loop].active = 0;
                      else sprites[sprite_loop].timer++;
                 }
            }
            else if (sprites[sprite_loop].type == 1001) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (sprites[sprite_loop].timer == 0) sprites[sprite_loop].x_position += 180;
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    sprites[sprite_loop].y_position += 5;
                    if (sprites[sprite_loop].timer == 50) { sprites[sprite_loop].action_state = 1; event_organizer = sprites[sprite_loop].biba + 1; sprites[sprite_loop].timer = 2; sprites[sprite_loop].y_position+=7; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    if (sprites[sprite_loop].timer == 42) {
                        sprites[sprite_loop].action_state = 2;
                        sprites[sprite_loop].timer = 3;
                        if (input_locked == 1) input_locked = 0;
                    }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    sprites[sprite_loop].y_position -= 12;
                    if (sprites[sprite_loop].timer == 28) { sprites[sprite_loop].action_state = 3; sprites[sprite_loop].timer = 0; sprites[sprite_loop].y_position-=7; }
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 10) {
                        if (sprites[sprite_loop].biba != 0) { sprites[sprite_loop].x_position -= 180; sprites[sprite_loop].biba = 0; }
                        if (rand() % 2 == 0) sprites[sprite_loop].y_position = 305;
				        else sprites[sprite_loop].y_position = 195;
                        sprites[sprite_loop].x_position += 840;
                        sprites[sprite_loop].width = 113;
                        sprites[sprite_loop].height = 43;
                        sprites[sprite_loop].frame = BIRDFLY1;
                        sprites[sprite_loop].direction = 0;
                    }
                    else if (sprites[sprite_loop].timer == 46) {
                        if (rand() % 2 == 0) sprites[sprite_loop].y_position = 305;
				        else sprites[sprite_loop].y_position = 195;
                        sprites[sprite_loop].direction = 1;
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 4;
                    }
                    else if (sprites[sprite_loop].timer > 10) {
                        sprites[sprite_loop].x_position -= 39;
                    }
                    else if (sprites[sprite_loop].timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (sprites[sprite_loop].action_state == 4) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 46) {
                        if (rand() % 2 == 0) sprites[sprite_loop].y_position = 305;
				else sprites[sprite_loop].y_position = 195;
                        sprites[sprite_loop].direction = 0;
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 5;
                    }
                    else if (sprites[sprite_loop].timer > 10) {
                        sprites[sprite_loop].x_position += 39;
                    }
                    else if (sprites[sprite_loop].timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (sprites[sprite_loop].action_state == 5) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 46) {
                        sprites[sprite_loop].y_position = -100;
                        sprites[sprite_loop].x_position += 865;
                        sprites[sprite_loop].direction = 0;
                        sprites[sprite_loop].width = 83;
                        sprites[sprite_loop].height = 110;
                        sprites[sprite_loop].frame = BIRD1;
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 6;
                    }
                    else if (sprites[sprite_loop].timer > 10) {
                        sprites[sprite_loop].x_position -= 39;
                    }
                    else if (sprites[sprite_loop].timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (sprites[sprite_loop].action_state == 6) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    sprites[sprite_loop].y_position += 10;
                    if (sprites[sprite_loop].timer == 25) { sprites[sprite_loop].action_state = 7; sprites[sprite_loop].timer = 0; sprites[sprite_loop].frame = BIRDSTAND; sprites[sprite_loop].y_position += 7; }
                }
                else if (sprites[sprite_loop].action_state == 7) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 50) {
                        sprites[sprite_loop].action_state = 8;
                        sprites[sprite_loop].timer = 3;
                    }
                    else if (sprites[sprite_loop].timer >= 12) {
                        if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRDSTAND1;
                        else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRDSTAND2;
                        else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRDSTAND3;
                        else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRDSTAND2;
                        if (sprites[sprite_loop].timer == 20) { initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 80, sprites[sprite_loop].direction, 0); initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 40, sprites[sprite_loop].direction, 0); }
                        else if (sprites[sprite_loop].timer == 28) initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 0);
                        else if (sprites[sprite_loop].timer == 36) { initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 80, sprites[sprite_loop].direction, 0); initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 40, sprites[sprite_loop].direction, 0); }
                        else if (sprites[sprite_loop].timer == 44) initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 0);
                    }
                }
                else if (sprites[sprite_loop].action_state == 8) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    sprites[sprite_loop].y_position -= 12;
                    if (sprites[sprite_loop].timer == 28) { sprites[sprite_loop].action_state = 9; sprites[sprite_loop].timer = 0; sprites[sprite_loop].y_position -= 7; }
                }
                else if (sprites[sprite_loop].action_state == 9) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 10) {
                        if (rand() % 2 == 0) sprites[sprite_loop].y_position = 305;
				else sprites[sprite_loop].y_position = 195;
                        sprites[sprite_loop].x_position -= 905;
                        sprites[sprite_loop].width = 113;
                        sprites[sprite_loop].height = 43;
                        sprites[sprite_loop].frame = BIRDFLY1;
                        sprites[sprite_loop].direction = 1;
                    }
                    else if (sprites[sprite_loop].timer == 46) {
                        if (rand() % 2 == 0) sprites[sprite_loop].y_position = 305;
				else sprites[sprite_loop].y_position = 195;
                        sprites[sprite_loop].direction = 0;
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 10;
                    }
                    else if (sprites[sprite_loop].timer > 10) {
                        sprites[sprite_loop].x_position += 39;
                    }
                    else if (sprites[sprite_loop].timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (sprites[sprite_loop].action_state == 10) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 46) {
                        if (rand() % 2 == 0) sprites[sprite_loop].y_position = 305;
				else sprites[sprite_loop].y_position = 195;
                        sprites[sprite_loop].direction = 1;
                        sprites[sprite_loop].timer = 0;
                        sprites[sprite_loop].action_state = 11;
                    }
                    else if (sprites[sprite_loop].timer > 10) {
                        sprites[sprite_loop].x_position -= 39;
                    }
                    else if (sprites[sprite_loop].timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (sprites[sprite_loop].action_state == 11) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 46) {
                        sprites[sprite_loop].x_position -= 820;
                        sprites[sprite_loop].y_position = -100;
                        sprites[sprite_loop].direction = 1;
                        sprites[sprite_loop].timer = 3;
                        sprites[sprite_loop].height = 117;
                        sprites[sprite_loop].width = 83;
                        sprites[sprite_loop].frame = BIRD1;
                        sprites[sprite_loop].action_state = 12;
                    }
                    else if (sprites[sprite_loop].timer > 10) {
                        sprites[sprite_loop].x_position += 39;
                    }
                    else if (sprites[sprite_loop].timer == 25) play_sample((SAMPLE *)mydatafile[WINDYDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                }
                else if (sprites[sprite_loop].action_state == 12) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    sprites[sprite_loop].y_position += 10;
                    if (sprites[sprite_loop].timer == 28) { sprites[sprite_loop].action_state = 15; sprites[sprite_loop].timer = 0; sprites[sprite_loop].y_position+=7; sprites[sprite_loop].frame = BIRDSTAND; }
                }
                else if (sprites[sprite_loop].action_state == 15) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 50) {
                        sprites[sprite_loop].action_state = 16;
                        sprites[sprite_loop].timer = 3;
                    }
                    else if (sprites[sprite_loop].timer >= 12) {
                        if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRDSTAND1;
                        else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRDSTAND2;
                        else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRDSTAND3;
                        else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRDSTAND2;
                        if (sprites[sprite_loop].timer == 20) initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 0);
                        else if (sprites[sprite_loop].timer == 28) { initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 80, sprites[sprite_loop].direction, 0); initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 40, sprites[sprite_loop].direction, 0); }
                        else if (sprites[sprite_loop].timer == 36) initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 0);
                        else if (sprites[sprite_loop].timer == 44) { initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 80, sprites[sprite_loop].direction, 0); initialize_sprite(64, (int)sprites[sprite_loop].x_position + 35, (int)sprites[sprite_loop].y_position + 40, sprites[sprite_loop].direction, 0); }
                    }
                }
		    else if (sprites[sprite_loop].action_state == 16) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = BIRD1;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = BIRD2;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = BIRD3;
                    else if (sprites[sprite_loop].timer % 8 == 6) sprites[sprite_loop].frame = BIRD2;
                    sprites[sprite_loop].y_position -= 12;
                    if (sprites[sprite_loop].timer == 28) { sprites[sprite_loop].action_state = 3; sprites[sprite_loop].timer = 0; sprites[sprite_loop].y_position-=7; sprites[sprite_loop].x_position += 20;}
                }
                else if (sprites[sprite_loop].action_state == 13) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2), (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2), 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2), (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2), 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2), (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2), 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 128) - 6, (int)sprites[sprite_loop].y_position + (rand() % 60) - 6, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 0);
                         else lastageportal[1] = 1;
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && input_locked == 0) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
            else if (sprites[sprite_loop].type == 1002) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = SHADOW01;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = SHADOW02;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = SHADOW03;
                    else if (sprites[sprite_loop].timer % 8 == 6) {
                         if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].direction = 1;
                         else sprites[sprite_loop].direction = 0;
                         sprites[sprite_loop].frame = SHADOW02;
                    }
                    sprites[sprite_loop].timer++;
                    if (event_organizer == 45) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 8 == 0) sprites[sprite_loop].frame = SHADOW01;
                    else if (sprites[sprite_loop].timer % 8 == 2) sprites[sprite_loop].frame = SHADOW02;
                    else if (sprites[sprite_loop].timer % 8 == 4) sprites[sprite_loop].frame = SHADOW03;
                    else if (sprites[sprite_loop].timer % 8 == 6) {
                         if (sprites[sprite_loop].direction == 0) sprites[sprite_loop].direction = 1;
                         else sprites[sprite_loop].direction = 0;
                         sprites[sprite_loop].frame = SHADOW02;
                    }
                    if (sprites[sprite_loop].frame == SHADOW01 && sprites[sprite_loop].direction == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].animation_state == 4) { sprites[sprite_loop].y_position -= 50; sprites[sprite_loop].frame = SC01;  play_sample((SAMPLE *)mydatafile[TIRO3].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (sprites[sprite_loop].animation_state == 6) sprites[sprite_loop].frame = SC02;
                    else if (sprites[sprite_loop].animation_state == 8) sprites[sprite_loop].frame = SC03;
                    else if (sprites[sprite_loop].animation_state == 10) sprites[sprite_loop].frame = SC04;
                    else if (sprites[sprite_loop].animation_state == 12) sprites[sprite_loop].frame = SC05;
                    else if (sprites[sprite_loop].animation_state == 14) sprites[sprite_loop].frame = SC06;
                    else if (sprites[sprite_loop].animation_state == 16) sprites[sprite_loop].frame = SC07;
                    else if (sprites[sprite_loop].animation_state == 18) sprites[sprite_loop].frame = SC08;
                    else if (sprites[sprite_loop].animation_state == 20) sprites[sprite_loop].frame = SC09;
                    else if (sprites[sprite_loop].animation_state == 22) sprites[sprite_loop].frame = SC10;
                    else if (sprites[sprite_loop].animation_state == 24) sprites[sprite_loop].frame = SC11;
                    else if (sprites[sprite_loop].animation_state == 26) sprites[sprite_loop].frame = SC12;
                    else if (sprites[sprite_loop].animation_state == 28) {
                        sprites[sprite_loop].x_position += 25;
                        sprites[sprite_loop].frame = SHADOWBALL;
                    }
                    else if (sprites[sprite_loop].animation_state > 29 && sprites[sprite_loop].animation_state < 39) sprites[sprite_loop].y_position -= 5;
                    else if (sprites[sprite_loop].animation_state == 40) {
                        sprites[sprite_loop].y_position -= 3;
                        event_organizer = 106;
                    }
                    else if (event_organizer == 0) { sprites[sprite_loop].animation_state = 0; sprites[sprite_loop].action_state = 3; }
                    sprites[sprite_loop].animation_state++;
                }
                else if (sprites[sprite_loop].action_state == 3) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) {  input_locked = 0; sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 4; }
                }
                else if (sprites[sprite_loop].action_state == 4) {
                     sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                     sprites[sprite_loop].biba = 1;
                     sprite_colision(sprite_loop, 1002);
                     sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                     sprites[sprite_loop].biba = 2;
                     sprite_colision(sprite_loop, 1002);
                     if (sprites[sprite_loop].hit_points_left <= 15) {
                         if (sprites[sprite_loop].y_position > 200 && sprites[sprite_loop].y_position < 300) { sprites[sprite_loop].action_state = 5; input_locked = 1; } }
                }
                else if (sprites[sprite_loop].action_state == 5) {
                     if (sprites[sprite_loop].timer == 6) initialize_sprite(1003, (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position, 0, 0);
                     else if (sprites[sprite_loop].timer == 36) {
                          if (sprites[sprite_loop].x_speed < 0) sprites[sprite_loop].x_speed = 15;
                          if (sprites[sprite_loop].y_speed > 0) sprites[sprite_loop].y_speed = -15;
                          input_locked = 0;
                          sprites[sprite_loop].action_state = 6;
                     }
                     sprites[sprite_loop].timer++;
                }
                else if (sprites[sprite_loop].action_state == 6) {
                     sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                     sprites[sprite_loop].biba = 1;
                     sprite_colision(sprite_loop, 1002);
                     sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                     sprites[sprite_loop].biba = 2;
                     sprite_colision(sprite_loop, 1002);
                }
                else if (sprites[sprite_loop].action_state == 7) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 25, (int)sprites[sprite_loop].y_position + 25, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 25, (int)sprites[sprite_loop].y_position + 25, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 25, (int)sprites[sprite_loop].y_position + 25, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 50) - 6, (int)sprites[sprite_loop].y_position + (rand() % 50) - 6, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 1);
                         else lastageportal[2] = 1;
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
            else if (sprites[sprite_loop].type == 1003) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (sprites[sprite_loop].timer == 0) {
                        if (sprites[sprite_loop].x_position < Map.limitright - 300) sprites[sprite_loop].biba = 3;
                        else { sprites[sprite_loop].biba = -3; sprites[sprite_loop].x_speed *= -1; sprites[sprite_loop].y_speed *= -1; }
                    }
                    if (sprites[sprite_loop].timer > 0 && sprites[sprite_loop].timer < 25) sprites[sprite_loop].x_position += sprites[sprite_loop].biba;
                    else if (sprites[sprite_loop].timer == 30) sprites[sprite_loop].action_state = 1;
                    sprites[sprite_loop].timer++;
                }
                else if (sprites[sprite_loop].action_state == 1) {
                     sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                     sprites[sprite_loop].biba = 1;
                     sprite_colision(sprite_loop, 1003);
                     sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                     sprites[sprite_loop].biba = 2;
                     sprite_colision(sprite_loop, 1003);
                }
                else if (sprites[sprite_loop].action_state == 2) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 25, (int)sprites[sprite_loop].y_position + 25, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 25, (int)sprites[sprite_loop].y_position + 25, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 25, (int)sprites[sprite_loop].y_position + 25, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 6) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 47), (int)sprites[sprite_loop].y_position + (rand() % 47), 0, 0);
                     }
                     if (bosslife == -1) sprites[sprite_loop].active = 0;
                     else lastageportal[2] = 1;
                         sprites[sprite_loop].timer++;
                }
            }
            else if (sprites[sprite_loop].type == 1004) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (event_organizer == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; input_locked = 0; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].timer % 4 < 2) sprites[sprite_loop].frame = THUNDER02;
                    else sprites[sprite_loop].frame = THUNDER01;
                    if (sprites[sprite_loop].timer == 40) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 2; }
                    else sprites[sprite_loop].timer++;
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer == 0) { sprites[sprite_loop].frame = THUNDER03; sprites[sprite_loop].width = 100; sprites[sprite_loop].height = 63; sprites[sprite_loop].y_position +=6; }
                    if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 3; }
                    else sprites[sprite_loop].timer++;
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    if (sprites[sprite_loop].timer == 0) { sprites[sprite_loop].frame = THUNDER04; sprites[sprite_loop].width = 96; sprites[sprite_loop].height = 64; sprites[sprite_loop].x_speed = -35; sprites[sprite_loop].y_speed = -2; play_sample((SAMPLE *)mydatafile[ROAR2].dat, (int)(155 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (sprites[sprite_loop].timer == 1) { sprites[sprite_loop].x_speed = -55; sprites[sprite_loop].y_speed = -2; }
                    else if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = THUNDER05; sprites[sprite_loop].width = 130; sprites[sprite_loop].x_speed = -55; sprites[sprite_loop].y_speed = -1; }
                    else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].x_speed = -55; sprites[sprite_loop].y_speed = -1; }
                    else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].x_speed = -55; sprites[sprite_loop].y_speed = 1; }
                    else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].x_speed = -42; sprites[sprite_loop].y_speed = 1; }
                    else if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].frame = THUNDER04; sprites[sprite_loop].width = 96; sprites[sprite_loop].x_speed = -26; sprites[sprite_loop].y_speed = 2; }
                    else if (sprites[sprite_loop].timer == 7) { sprites[sprite_loop].x_speed = -15; sprites[sprite_loop].y_speed = 2; }
                    if (sprites[sprite_loop].timer == 8) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 4; sprites[sprite_loop].direction = 1; sprites[sprite_loop].frame = THUNDER03; sprites[sprite_loop].width = 100; sprites[sprite_loop].height = 63; sprites[sprite_loop].x_speed = 0; sprites[sprite_loop].y_speed = 0; }
                    else { 
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprites[sprite_loop].timer++;
                    }
                }
                else if (sprites[sprite_loop].action_state == 4) {
                    if (sprites[sprite_loop].timer == 7) { sprites[sprite_loop].frame = THUNDER04; sprites[sprite_loop].width = 96; sprites[sprite_loop].height = 64; sprites[sprite_loop].x_speed = 35; sprites[sprite_loop].y_speed = -2; }
                    else if (sprites[sprite_loop].timer == 8) { sprites[sprite_loop].x_speed = 55; sprites[sprite_loop].y_speed = -2; }
                    else if (sprites[sprite_loop].timer == 9) { sprites[sprite_loop].frame = THUNDER05; sprites[sprite_loop].width = 130; sprites[sprite_loop].x_speed = 55; sprites[sprite_loop].y_speed = -1; }
                    else if (sprites[sprite_loop].timer == 10) { sprites[sprite_loop].x_speed = 55; sprites[sprite_loop].y_speed = -1; }
                    else if (sprites[sprite_loop].timer == 11) { sprites[sprite_loop].x_speed = 55; sprites[sprite_loop].y_speed = 1; }
                    else if (sprites[sprite_loop].timer == 12) { sprites[sprite_loop].x_speed = 42; sprites[sprite_loop].y_speed = 1; }
                    else if (sprites[sprite_loop].timer == 13) { sprites[sprite_loop].frame = THUNDER04; sprites[sprite_loop].width = 96; sprites[sprite_loop].x_speed = 26; sprites[sprite_loop].y_speed = 2; }
                    else if (sprites[sprite_loop].timer == 14) { sprites[sprite_loop].x_speed = 15; sprites[sprite_loop].y_speed = 2; }
                    if (sprites[sprite_loop].timer == 15) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 5; sprites[sprite_loop].direction = 0; sprites[sprite_loop].frame = THUNDER03; sprites[sprite_loop].width = 100; sprites[sprite_loop].height = 63; }
                    else { 
                    sprites[sprite_loop].x_position += sprites[sprite_loop].x_speed;
                    sprites[sprite_loop].y_position += sprites[sprite_loop].y_speed;
                    sprites[sprite_loop].timer++;
                    }
                }
                else if (sprites[sprite_loop].action_state == 5) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = THUNDER02; sprites[sprite_loop].width = 98; sprites[sprite_loop].height = 69; sprites[sprite_loop].y_position -= 6; }
                    else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].frame = THUNDER01;
                    else if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].frame = THUNDER02;
                    else if (sprites[sprite_loop].timer == 8) sprites[sprite_loop].frame = THUNDER01;
                    else if (sprites[sprite_loop].timer == 10) sprites[sprite_loop].frame = THUNDER02;
                    else if (sprites[sprite_loop].timer == 12) sprites[sprite_loop].frame = THUNDER01;
                    else if (sprites[sprite_loop].timer == 14) sprites[sprite_loop].frame = THUNDER02;
                    else if (sprites[sprite_loop].timer == 16) sprites[sprite_loop].frame = THUNDER01;
                    else if (sprites[sprite_loop].timer == 18) sprites[sprite_loop].frame = THUNDER02;
                    else if (sprites[sprite_loop].timer == 20) sprites[sprite_loop].frame = THUNDER01;
                    else if (sprites[sprite_loop].timer == 22) sprites[sprite_loop].frame = THUNDER02;
                    else if (sprites[sprite_loop].timer == 24) { sprites[sprite_loop].frame = THUNDER03; sprites[sprite_loop].y_position += 6; }
                    else if (sprites[sprite_loop].timer == 28) { sprites[sprite_loop].frame = THUNDERUP01; sprites[sprite_loop].y_position += 13; sprites[sprite_loop].x_position += 15; }
                    else if (sprites[sprite_loop].timer == 29) { sprites[sprite_loop].frame = THUNDERUP02; sprites[sprite_loop].y_position += 11; sprites[sprite_loop].x_position -= 4; }
                    else if (sprites[sprite_loop].timer == 30) { sprites[sprite_loop].frame = THUNDERUP03; sprites[sprite_loop].y_position -= 46; sprites[sprite_loop].x_position += 16; }
                    else if (sprites[sprite_loop].timer == 31) { sprites[sprite_loop].frame = THUNDERUP04; sprites[sprite_loop].y_position -= 44; sprites[sprite_loop].x_position += 17; }
                    else if (sprites[sprite_loop].timer == 32) sprites[sprite_loop].y_position -= 100;
                    else if (sprites[sprite_loop].timer == 33) sprites[sprite_loop].y_position -= 100;
                    else if (sprites[sprite_loop].timer == 34) {
                        sprites[sprite_loop].timer = 0;
                        if (bosslife > 15) sprites[sprite_loop].action_state = 6;
                        else { sprites[sprite_loop].action_state = 7; sprites[sprite_loop].animation_state = rand() % 2; }
                        sprites[sprite_loop].frame = NULO;
                        sprites[sprite_loop].x_position += 200;
                    }
                }
                else if (sprites[sprite_loop].action_state == 6) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) initialize_sprite(27, 5570, 160, 0, 0);
                    else if (sprites[sprite_loop].timer == 24) flash_screen = 1;
                    else if (sprites[sprite_loop].timer == 25) { flash_screen = 2; initialize_sprite(26, 5580, 460, 1, 0); initialize_sprite(26, 5590, 460, 3, 0); initialize_sprite(26, 5585, 440, 1, 0); initialize_sprite(26, 5585, 440, 3, 0); }
                    else if (sprites[sprite_loop].timer == 26) flash_screen = 1;
                    else if (sprites[sprite_loop].timer == 27) flash_screen = 0;
                    else if (sprites[sprite_loop].timer == 57) initialize_sprite(27, 5740, 160, 0, 0);
                    else if (sprites[sprite_loop].timer == 58) flash_screen = 1;
                    else if (sprites[sprite_loop].timer == 59) { flash_screen = 2; sprites[sprite_loop].x_position = 5720; sprites[sprite_loop].y_position = 411; sprites[sprite_loop].frame = THUNDER01; }
                    else if (sprites[sprite_loop].timer == 60) flash_screen = 1;
                    else if (sprites[sprite_loop].timer == 61) { flash_screen = 0; sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; }
                }
                else if (sprites[sprite_loop].action_state == 7) {
                    if (sprites[sprite_loop].animation_state == 0) {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer == 20) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 21) flash_screen = 2;
                        else if (sprites[sprite_loop].timer == 22) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 23) flash_screen = 0;
                        else if (sprites[sprite_loop].timer == 26) { initialize_sprite(28, 5377, 160, 0, 0); initialize_sprite(28, 5790, 160, 0, 0); }
                        else if (sprites[sprite_loop].timer == 34) { initialize_sprite(28, 5445, 160, 0, 0); initialize_sprite(28, 5722, 160, 0, 0); }
                        else if (sprites[sprite_loop].timer == 42) { initialize_sprite(28, 5513, 160, 0, 0); initialize_sprite(28, 5654, 160, 0, 0); }
                        else if (sprites[sprite_loop].timer == 50) initialize_sprite(28, 5583, 160, 0, 0);
                        else if (sprites[sprite_loop].timer == 67) initialize_sprite(27, 5740, 160, 0, 0);
                        else if (sprites[sprite_loop].timer == 71) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 72) { flash_screen = 2; sprites[sprite_loop].x_position = 5720; sprites[sprite_loop].y_position = 411; sprites[sprite_loop].frame = THUNDER01; }
                        else if (sprites[sprite_loop].timer == 73) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 74) { flash_screen = 0; sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; }
                    }
                    else {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer == 20) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 21) flash_screen = 2;
                        else if (sprites[sprite_loop].timer == 22) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 23) flash_screen = 0;
                        else if (sprites[sprite_loop].timer == 26) { initialize_sprite(28, 5377, 160, 0, 0); initialize_sprite(28, 5654, 160, 0, 0); }
                        else if (sprites[sprite_loop].timer == 34) { initialize_sprite(28, 5445, 160, 0, 0); initialize_sprite(28, 5722, 160, 0, 0); }
                        else if (sprites[sprite_loop].timer == 42) { initialize_sprite(28, 5513, 160, 0, 0); initialize_sprite(28, 5790, 160, 0, 0); }
                        else if (sprites[sprite_loop].timer == 50) initialize_sprite(28, 5583, 160, 0, 0);
                        else if (sprites[sprite_loop].timer == 67) initialize_sprite(27, 5740, 160, 0, 0);
                        else if (sprites[sprite_loop].timer == 71) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 72) { flash_screen = 2; sprites[sprite_loop].x_position = 5720; sprites[sprite_loop].y_position = 411; sprites[sprite_loop].frame = THUNDER01; }
                        else if (sprites[sprite_loop].timer == 73) flash_screen = 1;
                        else if (sprites[sprite_loop].timer == 74) { flash_screen = 0; sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 8) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 48, (int)sprites[sprite_loop].y_position + 30, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 48, (int)sprites[sprite_loop].y_position + 30, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 48, (int)sprites[sprite_loop].y_position + 30, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 98) - 6, (int)sprites[sprite_loop].y_position + (rand() % 69) - 6, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 2);
                         else lastageportal[3] = 1;
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
            else if (sprites[sprite_loop].type == 1005) {
                if (sprites[sprite_loop].action_state == 0) {
                    if (event_organizer == 44) sprites[sprite_loop].action_state = 1;
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = TURTLE_OPEN1; play_sample((SAMPLE *)mydatafile[ROAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = TURTLE_OPEN2;
                    else if (sprites[sprite_loop].timer == 10) sprites[sprite_loop].frame = TURTLE_OPEN1;
                    else if (sprites[sprite_loop].timer == 11) { event_organizer = 51; sprites[sprite_loop].frame = TURTLE; }
                    else if (event_organizer == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 30) {
                         sprites[sprite_loop].biba = rand() % 2;
                         if (sprites[sprite_loop].hit_points_left > 20) {
                             if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 3; }
                             else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 4; }
                         }
                         else {
                             if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 11; }
                             else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 12; }
                         }
                     }
                }
                else if (sprites[sprite_loop].action_state == 3) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = TURTLE_OPEN2;
                     else if (sprites[sprite_loop].timer == 6) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 31, (int)sprites[sprite_loop].y_position + 31, sprites[sprite_loop].direction, 0);
                     else if (sprites[sprite_loop].timer == 16) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 17) sprites[sprite_loop].frame = TURTLE;
                     else if (sprites[sprite_loop].timer == 27) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 4) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position++; }
                     else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position += 2; }
                     else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = TURTLE_ENTER3; sprites[sprite_loop].y_position += 3; sprites[sprite_loop].x_position += 32; sprites[sprite_loop].width -= 32; }
                     else if (sprites[sprite_loop].timer == 7) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 40, (int)sprites[sprite_loop].y_position + 25, sprites[sprite_loop].direction + 10, 1);
                     else if (sprites[sprite_loop].timer >= 8) { 
                         sprites[sprite_loop].x_position -= 32;
                         if (sprites[sprite_loop].timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                         sprite_colision(sprite_loop, 1005);
                     }
                }
                else if (sprites[sprite_loop].action_state == 5) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].direction = 1;
                     else if (sprites[sprite_loop].timer == 10) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position -= 3; }
                     else if (sprites[sprite_loop].timer == 11) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position -= 2; }
                     else if (sprites[sprite_loop].timer == 12) { sprites[sprite_loop].frame = TURTLE; sprites[sprite_loop].width += 32; sprites[sprite_loop].y_position--; }
                     else if (sprites[sprite_loop].timer == 13) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 6) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 30) {
                         sprites[sprite_loop].biba = rand() % 2;
                         if (sprites[sprite_loop].hit_points_left > 20) {
                             if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 7; }
                             else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 8; }
                         }
                         else {
                             if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 15; }
                             else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 16; }
                         }
                     }
                }
                else if (sprites[sprite_loop].action_state == 7) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = TURTLE_OPEN2;
                     else if (sprites[sprite_loop].timer == 6) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 77, (int)sprites[sprite_loop].y_position + 31, sprites[sprite_loop].direction, 0);
                     else if (sprites[sprite_loop].timer == 16) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 17) sprites[sprite_loop].frame = TURTLE;
                     else if (sprites[sprite_loop].timer == 27) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 6; }
                }
                else if (sprites[sprite_loop].action_state == 8) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position++; }
                     else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position += 2; }
                     else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = TURTLE_ENTER3; sprites[sprite_loop].y_position += 3; sprites[sprite_loop].width -= 32; }
                     else if (sprites[sprite_loop].timer == 7) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 58, (int)sprites[sprite_loop].y_position + 25, sprites[sprite_loop].direction + 10, 1);
                     else if (sprites[sprite_loop].timer >= 8) { 
                         sprites[sprite_loop].x_position += 32;
                         if (sprites[sprite_loop].timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                         sprite_colision(sprite_loop, 1005);
                     }
                }
                else if (sprites[sprite_loop].action_state == 9) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].direction = 0;
                     else if (sprites[sprite_loop].timer == 10) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position -= 3; sprites[sprite_loop].x_position -= 32; sprites[sprite_loop].width += 32; }
                     else if (sprites[sprite_loop].timer == 11) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position -= 2; }
                     else if (sprites[sprite_loop].timer == 12) { sprites[sprite_loop].frame = TURTLE; sprites[sprite_loop].y_position--; }
                     else if (sprites[sprite_loop].timer == 13) { sprites[sprite_loop].action_state = 2; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 10) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) {
                         sprites[sprite_loop].biba = rand() % 2;
                         if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 11; }
                         else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 12; }
                     }
                }
                else if (sprites[sprite_loop].action_state == 11) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = TURTLE_OPEN2;
                     else if (sprites[sprite_loop].timer == 6) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 31, (int)sprites[sprite_loop].y_position + 31, sprites[sprite_loop].direction, 0);
                     else if (sprites[sprite_loop].timer == 13) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 14) sprites[sprite_loop].frame = TURTLE;
                     else if (sprites[sprite_loop].timer == 15) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 10; }
                }
                else if (sprites[sprite_loop].action_state == 12) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position++; }
                     else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position += 2; }
                     else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = TURTLE_ENTER3; sprites[sprite_loop].y_position += 3; sprites[sprite_loop].x_position += 32; sprites[sprite_loop].width -= 32; }
                     else if (sprites[sprite_loop].timer == 7) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 40, (int)sprites[sprite_loop].y_position + 25, sprites[sprite_loop].direction + 10, 1);
                     else if (sprites[sprite_loop].timer >= 8) { 
                         sprites[sprite_loop].x_position -= 32;
                         if (sprites[sprite_loop].timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                         sprite_colision(sprite_loop, 1005);
                     }
                }
                else if (sprites[sprite_loop].action_state == 13) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].direction = 1;
                     else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position -= 3; }
                     else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position -= 2; }
                     else if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].frame = TURTLE; sprites[sprite_loop].width += 32; sprites[sprite_loop].y_position--; }
                     else if (sprites[sprite_loop].timer == 7) { sprites[sprite_loop].action_state = 14; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 14) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) {
                         sprites[sprite_loop].biba = rand() % 2;
                         if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 15; }
                         else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 16; }
                     }
                }
                else if (sprites[sprite_loop].action_state == 15) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = TURTLE_OPEN2;
                     else if (sprites[sprite_loop].timer == 6) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 77, (int)sprites[sprite_loop].y_position + 31, sprites[sprite_loop].direction, 0);
                     else if (sprites[sprite_loop].timer == 13) sprites[sprite_loop].frame = TURTLE_OPEN1;
                     else if (sprites[sprite_loop].timer == 14) sprites[sprite_loop].frame = TURTLE;
                     else if (sprites[sprite_loop].timer == 15) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 14; }
                }
                else if (sprites[sprite_loop].action_state == 16) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 2) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position++; }
                     else if (sprites[sprite_loop].timer == 3) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position += 2; }
                     else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = TURTLE_ENTER3; sprites[sprite_loop].y_position += 3; sprites[sprite_loop].width -= 32; }
                     else if (sprites[sprite_loop].timer == 7) initialize_sprite(36, (int)sprites[sprite_loop].x_position + 58, (int)sprites[sprite_loop].y_position + 25, sprites[sprite_loop].direction + 10, 1);
                     else if (sprites[sprite_loop].timer >= 8) { 
                         sprites[sprite_loop].x_position += 32;
                         if (sprites[sprite_loop].timer == 10) play_sample((SAMPLE *)mydatafile[TURTLEDASH].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                         sprite_colision(sprite_loop, 1005);
                     }
                }
                else if (sprites[sprite_loop].action_state == 17) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].direction = 0;
                     else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = TURTLE_ENTER2; sprites[sprite_loop].y_position -= 3; sprites[sprite_loop].x_position -= 32; sprites[sprite_loop].width += 32; }
                     else if (sprites[sprite_loop].timer == 5) { sprites[sprite_loop].frame = TURTLE_ENTER1; sprites[sprite_loop].y_position -= 2; }
                     else if (sprites[sprite_loop].timer == 6) { sprites[sprite_loop].frame = TURTLE; sprites[sprite_loop].y_position--; }
                     else if (sprites[sprite_loop].timer == 7) { sprites[sprite_loop].action_state = 11; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 18) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 55, (int)sprites[sprite_loop].y_position + 30, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 55, (int)sprites[sprite_loop].y_position + 30, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 55, (int)sprites[sprite_loop].y_position + 30, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 128) - 6, (int)sprites[sprite_loop].y_position + (rand() % 60) - 6, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 3);
                         else lastageportal[4] = 1;
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
            else if (sprites[sprite_loop].type == 1006) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 12 == 3) sprites[sprite_loop].frame = SCALED01;
                    else if (sprites[sprite_loop].timer % 12 == 6) sprites[sprite_loop].frame = SCALED02;
                    else if (sprites[sprite_loop].timer % 12 == 9) sprites[sprite_loop].frame = SCALED03;
                    else if (sprites[sprite_loop].timer % 12 == 0) sprites[sprite_loop].frame = SCALED04;
                    if (event_organizer == 54) { sprites[sprite_loop].action_state = 1; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].frame = SCALEDFIRE01;
                    else if (sprites[sprite_loop].timer == 4) { sprites[sprite_loop].frame = SCALEDFIRE02; play_sample((SAMPLE *)mydatafile[ROAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                    else if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].frame = SCALEDFIRE03;
                    else if (sprites[sprite_loop].timer == 20) sprites[sprite_loop].frame = SCALEDFIRE02;
                    else if (sprites[sprite_loop].timer == 22) sprites[sprite_loop].frame = SCALEDFIRE01;
                    else if (sprites[sprite_loop].timer == 24) { event_organizer = 61; sprites[sprite_loop].frame = SCALED01; }
                    else if (event_organizer == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 12 == 3) sprites[sprite_loop].frame = SCALED01;
                    else if (sprites[sprite_loop].timer % 12 == 6) sprites[sprite_loop].frame = SCALED02;
                    else if (sprites[sprite_loop].timer % 12 == 9) sprites[sprite_loop].frame = SCALED03;
                    else if (sprites[sprite_loop].timer % 12 == 0) sprites[sprite_loop].frame = SCALED04;
                    if (sprites[sprite_loop].timer == 50) {
                         sprites[sprite_loop].biba = rand() % 3;
                         if (sprites[sprite_loop].biba == 0) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 3; sprites[sprite_loop].frame = SCALED01; }
                         else if (sprites[sprite_loop].biba == 1) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 4; sprites[sprite_loop].frame = SCALED01; }
                         else { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 5; sprites[sprite_loop].frame = SCALED01; }
                    }
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 6 == 0 && sprites[sprite_loop].timer < 55) initialize_sprite(46, (int)sprites[sprite_loop].x_position + 12 + (rand() % 6), (int)sprites[sprite_loop].y_position + 13 + (rand() % 6), sprites[sprite_loop].direction, 0);
                    if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = SCALEDFIRE01; 
                    else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SCALEDFIRE02; 
                    else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].frame = SCALEDFIRE03; 
                    else if (sprites[sprite_loop].timer == 57) sprites[sprite_loop].frame = SCALEDFIRE02;
                    else if (sprites[sprite_loop].timer == 59) sprites[sprite_loop].frame = SCALEDFIRE01;
                    else if (sprites[sprite_loop].timer == 61) { sprites[sprite_loop].timer = 3; sprites[sprite_loop].frame = SCALED01; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 4) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].frame = SCALEDFIRE01; 
                    else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].frame = SCALEDFIRE02; 
                    else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].frame = SCALEDFIRE03; 
                    else if (sprites[sprite_loop].timer == 20) initialize_sprite(47, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 15, sprites[sprite_loop].direction, 0);
                    else if (sprites[sprite_loop].timer == 26) sprites[sprite_loop].frame = SCALEDFIRE02;
                    else if (sprites[sprite_loop].timer == 28) sprites[sprite_loop].frame = SCALEDFIRE01;
                    else if (sprites[sprite_loop].timer == 30) { sprites[sprite_loop].timer = 3; sprites[sprite_loop].frame = SCALED01; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 5) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) { sprites[sprite_loop].frame = SCALEDCUT01; sprites[sprite_loop].y_position -= 8; }
                    else if (sprites[sprite_loop].timer == 8) {
                        initialize_sprite(48, (int)sprites[sprite_loop].x_position + 5, (int)sprites[sprite_loop].y_position + 32, sprites[sprite_loop].direction, 0);
                        initialize_sprite(49, (int)sprites[sprite_loop].x_position + 5, (int)sprites[sprite_loop].y_position + 32, sprites[sprite_loop].direction, 0);
                        sprites[sprite_loop].frame = SCALEDCUT02;
                    }
                    else if (sprites[sprite_loop].timer == 15) { sprites[sprite_loop].y_position += 8; sprites[sprite_loop].timer = 3; sprites[sprite_loop].frame = SCALED01; sprites[sprite_loop].action_state = 2; }
                }
                else if (sprites[sprite_loop].action_state == 6) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 64, (int)sprites[sprite_loop].y_position + 53, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 64, (int)sprites[sprite_loop].y_position + 53, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 64, (int)sprites[sprite_loop].y_position + 53, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 128) - 6, (int)sprites[sprite_loop].y_position + (rand() % 60) - 6, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 4);
                         else lastageportal[5] = 1;
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
            else if (sprites[sprite_loop].type == 1007) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer % 4 == 1) sprites[sprite_loop].frame = ICYSHADOW01;
                    else if (sprites[sprite_loop].timer % 4 == 2) sprites[sprite_loop].frame = ICYSHADOW02;
                    else if (sprites[sprite_loop].timer % 4 == 3) sprites[sprite_loop].frame = ICYSHADOW03;
                    else if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].frame = ICYSHADOW02;
                    sprites[sprite_loop].x_position -= 20;
                    if (sprites[sprite_loop].timer == 45) { sprites[sprite_loop].action_state = 1; sprites[sprite_loop].timer = 0; }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 6) {
                        sprites[sprite_loop].frame = ICYSHADOW04;
                        sprites[sprite_loop].x_position += 690;
                        sprites[sprite_loop].y_position = 1220;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                    }
                    else if (sprites[sprite_loop].timer > 6 && sprites[sprite_loop].timer < 18) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position < 206) sprites[sprite_loop].frame = ICYUP01;
                    }
                    else if (sprites[sprite_loop].timer == 18) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].x_position -= 5;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                    }
                    else if (sprites[sprite_loop].timer == 20) {
                        sprites[sprite_loop].x_position -= 5;
                        sprites[sprite_loop].frame = ICYUP03;
                        sprites[sprite_loop].width = 120;
                        sprites[sprite_loop].height = 138;
                    }
                    else if (sprites[sprite_loop].timer == 22) {
                        event_organizer = 51;
                    }
                    else if (input_locked == 0 && bossfight == 1) {
                        sprites[sprite_loop].action_state = 2;
                        sprites[sprite_loop].timer = 0;
                    }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 50, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 3);
                    }
                    else if (sprites[sprite_loop].timer == 35) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 130, sprites[sprite_loop].direction, 3);
                    }
                    else if (sprites[sprite_loop].timer == 50) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer == 52) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer > 53) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    } 
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
                        sprites[sprite_loop].frame = ICYSHADOW02;
                        sprites[sprite_loop].width = 154;
                        sprites[sprite_loop].height = 65;
                        sprites[sprite_loop].x_position = 3140;
                        sprites[sprite_loop].y_position = 1110;
                        sprites[sprite_loop].direction = 0;
                    }
                    else if (sprites[sprite_loop].timer > 10 && sprites[sprite_loop].timer < 16) {
                        sprites[sprite_loop].x_position += 30;
                    }
                    else if (sprites[sprite_loop].timer > 15 && sprites[sprite_loop].timer < 19) {
                        sprites[sprite_loop].x_position += 30;
                        sprites[sprite_loop].y_position -= 10;
                    }
                    else if (sprites[sprite_loop].timer > 18 && sprites[sprite_loop].timer < 40) {
                        sprites[sprite_loop].x_position += 30;
                    }
                    else if (sprites[sprite_loop].timer == 40) {
                        if (sprites[sprite_loop].hit_points_left > 25) {
                            if (player.x_position > 3640) sprites[sprite_loop].action_state = 6;
                            else sprites[sprite_loop].action_state = 7;
                        }
                        else if (sprites[sprite_loop].hit_points_left > 10) {
                            if (player.x_position > 3640) sprites[sprite_loop].action_state = 10;
                            else sprites[sprite_loop].action_state = 11;
                        }
                        else {
                            if (player.x_position > 3640) sprites[sprite_loop].action_state = 14;
                            else sprites[sprite_loop].action_state = 15;
                        }
                        sprites[sprite_loop].timer = 0;
                    } 
                }
                else if (sprites[sprite_loop].action_state == 4) {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer == 1) {
                            sprites[sprite_loop].frame = ICYSHADOW02;
                            sprites[sprite_loop].width = 154;
                            sprites[sprite_loop].height = 65;
                            sprites[sprite_loop].x_position = 3140;
                            sprites[sprite_loop].y_position = 880;
                            sprites[sprite_loop].direction = 0;
                        }
                        else if (sprites[sprite_loop].timer > 5 && sprites[sprite_loop].timer < 18) {
                            sprites[sprite_loop].x_position += 12;
                        }
                        else if (sprites[sprite_loop].timer == 18) { sprites[sprite_loop].frame = ICYSIDE02; sprites[sprite_loop].width = 140; sprites[sprite_loop].height = 106; sprites[sprite_loop].x_position += 20; sprites[sprite_loop].y_position += 2; }
                        else if (sprites[sprite_loop].timer == 19) { sprites[sprite_loop].x_position += 15; sprites[sprite_loop].y_position += 4; }
                        else if (sprites[sprite_loop].timer == 20) { sprites[sprite_loop].frame = ICYSIDE03; sprites[sprite_loop].width = 138; sprites[sprite_loop].height = 120; sprites[sprite_loop].x_position += 15; sprites[sprite_loop].y_position += 7; }
                        else if (sprites[sprite_loop].timer == 21) { sprites[sprite_loop].x_position += 15; sprites[sprite_loop].y_position += 8; }
                        else if (sprites[sprite_loop].timer == 22) { sprites[sprite_loop].frame = ICYSIDE04; sprites[sprite_loop].width = 90; sprites[sprite_loop].height = 148; sprites[sprite_loop].x_position += 50; sprites[sprite_loop].y_position += 12; }
                        else if (sprites[sprite_loop].timer == 23) { sprites[sprite_loop].x_position += 12; sprites[sprite_loop].y_position += 14; }
                        else if (sprites[sprite_loop].timer == 24) { sprites[sprite_loop].frame = ICYUP01; sprites[sprite_loop].width = 65; sprites[sprite_loop].height = 154; sprites[sprite_loop].x_position += 26; sprites[sprite_loop].y_position += 18; }
                        else if (sprites[sprite_loop].timer == 25) { sprites[sprite_loop].x_position += 10; sprites[sprite_loop].y_position += 20; }
                        else if (sprites[sprite_loop].timer > 25) {
                             sprites[sprite_loop].y_position += 20; 
                             if (sprites[sprite_loop].y_position > 1260) { 
                                 if (sprites[sprite_loop].hit_points_left > 25) {
                                     if (player.x_position > 3640) sprites[sprite_loop].action_state = 6;
                                     else sprites[sprite_loop].action_state = 7;  
                                 } 
                                 else if (sprites[sprite_loop].hit_points_left > 10) {
                                     if (player.x_position > 3640) sprites[sprite_loop].action_state = 10;
                                     else sprites[sprite_loop].action_state = 11;
                                 }
                                 else {
                                     if (player.x_position > 3640) sprites[sprite_loop].action_state = 14;
                                     else sprites[sprite_loop].action_state = 15;
                                 }
                                 sprites[sprite_loop].timer = 0;
                             }
                        }                                             
                }
                else if (sprites[sprite_loop].action_state == 5) {
                        sprites[sprite_loop].timer++;
                        if (sprites[sprite_loop].timer == 1) {
                            sprites[sprite_loop].frame = ICYSHADOW02;
                            sprites[sprite_loop].width = 154;
                            sprites[sprite_loop].height = 65;
                            sprites[sprite_loop].x_position = 3966;
                            sprites[sprite_loop].y_position = 880;
                            sprites[sprite_loop].direction = 1;
                        }
                        else if (sprites[sprite_loop].timer > 5 && sprites[sprite_loop].timer < 18) {
                            sprites[sprite_loop].x_position -= 12;
                        }
                        else if (sprites[sprite_loop].timer == 18) { sprites[sprite_loop].frame = ICYSIDE02; sprites[sprite_loop].width = 140; sprites[sprite_loop].height = 106; sprites[sprite_loop].x_position -= 6; sprites[sprite_loop].y_position += 2; }
                        else if (sprites[sprite_loop].timer == 19) { sprites[sprite_loop].x_position -= 15; sprites[sprite_loop].y_position += 4; }
                        else if (sprites[sprite_loop].timer == 20) { sprites[sprite_loop].frame = ICYSIDE03; sprites[sprite_loop].width = 138; sprites[sprite_loop].height = 120; sprites[sprite_loop].x_position -= 13; sprites[sprite_loop].y_position += 7; }
                        else if (sprites[sprite_loop].timer == 21) { sprites[sprite_loop].x_position -= 15; sprites[sprite_loop].y_position += 8; }
                        else if (sprites[sprite_loop].timer == 22) { sprites[sprite_loop].frame = ICYSIDE04; sprites[sprite_loop].width = 90; sprites[sprite_loop].height = 148; sprites[sprite_loop].x_position -= 2; sprites[sprite_loop].y_position += 12; }
                        else if (sprites[sprite_loop].timer == 23) { sprites[sprite_loop].x_position -= 12; sprites[sprite_loop].y_position += 14; }
                        else if (sprites[sprite_loop].timer == 24) { sprites[sprite_loop].frame = ICYUP01; sprites[sprite_loop].width = 65; sprites[sprite_loop].height = 154; sprites[sprite_loop].x_position -= 1; sprites[sprite_loop].y_position += 18; }
                        else if (sprites[sprite_loop].timer == 25) { sprites[sprite_loop].x_position -= 10; sprites[sprite_loop].y_position += 20; }
                        else if (sprites[sprite_loop].timer > 25) {
                             sprites[sprite_loop].y_position += 20;
                             if (sprites[sprite_loop].y_position > 1260) {
                                 if (sprites[sprite_loop].hit_points_left > 25) {
                                     if (player.x_position > 3640) sprites[sprite_loop].action_state = 6;
                                     else sprites[sprite_loop].action_state = 7;
                                 }
                                 else if (sprites[sprite_loop].hit_points_left > 10) {
                                     if (player.x_position > 3640) sprites[sprite_loop].action_state = 10;
                                     else sprites[sprite_loop].action_state = 11;
                                 }
                                 else {
                                     if (player.x_position > 3640) sprites[sprite_loop].action_state = 14;
                                     else sprites[sprite_loop].action_state = 15;
                                 }
                             sprites[sprite_loop].timer = 0;
                             }
                        }                                             
                }
                else if (sprites[sprite_loop].action_state == 6 || sprites[sprite_loop].action_state == 10 || sprites[sprite_loop].action_state == 14) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 6) {
                        sprites[sprite_loop].frame = ICYSHADOW04;
                        sprites[sprite_loop].x_position = 3770;
                        sprites[sprite_loop].y_position = 1220;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].direction = 1;
                    }
                    else if (sprites[sprite_loop].timer > 6 && sprites[sprite_loop].timer < 18) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position < 206) sprites[sprite_loop].frame = ICYUP01;
                    }
                    else if (sprites[sprite_loop].timer == 18) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].x_position -= 5;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                    }
                    else if (sprites[sprite_loop].timer == 20) {
                        sprites[sprite_loop].x_position -= 5;
                        sprites[sprite_loop].frame = ICYUP03;
                        sprites[sprite_loop].width = 120;
                        sprites[sprite_loop].height = 138;
                    }
                    else if (sprites[sprite_loop].timer == 30) {
                        sprites[sprite_loop].action_state += 2;
                        sprites[sprite_loop].timer = 0;
                    }
                }
                else if (sprites[sprite_loop].action_state == 7 || sprites[sprite_loop].action_state == 11 || sprites[sprite_loop].action_state == 15) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 6) {
                        sprites[sprite_loop].frame = ICYSHADOW04;
                        sprites[sprite_loop].x_position = 3430;
                        sprites[sprite_loop].y_position = 1220;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].direction = 0;
                    }
                    else if (sprites[sprite_loop].timer > 6 && sprites[sprite_loop].timer < 18) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position < 206) sprites[sprite_loop].frame = ICYUP01;
                    }
                    else if (sprites[sprite_loop].timer == 18) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].x_position -= 38;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                    }
                    else if (sprites[sprite_loop].timer == 20) {
                        sprites[sprite_loop].x_position -= 12;
                        sprites[sprite_loop].frame = ICYUP03;
                        sprites[sprite_loop].width = 120;
                        sprites[sprite_loop].height = 138;
                    }
                    else if (sprites[sprite_loop].timer == 30) {
                        sprites[sprite_loop].action_state += 2;
                        sprites[sprite_loop].timer = 0;
                    }
                }
                else if (sprites[sprite_loop].action_state == 8) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 50, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 3);
                    }
                    else if (sprites[sprite_loop].timer == 35) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 130, sprites[sprite_loop].direction, 3);
                    }
                    else if (sprites[sprite_loop].timer == 50) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer == 52) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer > 53) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    } 
                }
                else if (sprites[sprite_loop].action_state == 9) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 123, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 3);
                    }
                    else if (sprites[sprite_loop].timer == 35) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 103, (int)sprites[sprite_loop].y_position + 130, sprites[sprite_loop].direction, 3);
                    }
                    else if (sprites[sprite_loop].timer == 50) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 12;
                    }
                    else if (sprites[sprite_loop].timer == 52) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 38;
                    }
                    else if (sprites[sprite_loop].timer > 53) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    } 
                }
                else if (sprites[sprite_loop].action_state == 12) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 6, (int)sprites[sprite_loop].y_position + 71, sprites[sprite_loop].direction, 0);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 25, (int)sprites[sprite_loop].y_position + 67, sprites[sprite_loop].direction, 1);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 56, (int)sprites[sprite_loop].y_position + 51, sprites[sprite_loop].direction, 2);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 67, (int)sprites[sprite_loop].y_position + 26, sprites[sprite_loop].direction, 3);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 56, (int)sprites[sprite_loop].y_position - 5, sprites[sprite_loop].direction, 4);
                    }
                    else if (sprites[sprite_loop].timer == 40) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer == 42) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer > 43) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    }   
                }
                else if (sprites[sprite_loop].action_state == 13) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 67, (int)sprites[sprite_loop].y_position + 71, sprites[sprite_loop].direction, 0);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 98, (int)sprites[sprite_loop].y_position + 67, sprites[sprite_loop].direction, 1);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 129, (int)sprites[sprite_loop].y_position + 51, sprites[sprite_loop].direction, 2);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 140, (int)sprites[sprite_loop].y_position + 26, sprites[sprite_loop].direction, 3);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 129, (int)sprites[sprite_loop].y_position - 5, sprites[sprite_loop].direction, 4);
                    }
                    else if (sprites[sprite_loop].timer == 40) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer == 42) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer > 43) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    }   
                }
                else if (sprites[sprite_loop].action_state == 16) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 6, (int)sprites[sprite_loop].y_position + 71, sprites[sprite_loop].direction, 0);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 25, (int)sprites[sprite_loop].y_position + 67, sprites[sprite_loop].direction, 1);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 56, (int)sprites[sprite_loop].y_position + 51, sprites[sprite_loop].direction, 2);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 67, (int)sprites[sprite_loop].y_position + 26, sprites[sprite_loop].direction, 3);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 56, (int)sprites[sprite_loop].y_position - 5, sprites[sprite_loop].direction, 4);
                    }
                    if (sprites[sprite_loop].timer == 35) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 50, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 3);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 43, (int)sprites[sprite_loop].y_position + 94, sprites[sprite_loop].direction, 2);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 43, (int)sprites[sprite_loop].y_position + 94, sprites[sprite_loop].direction, 4);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 43, (int)sprites[sprite_loop].y_position + 20, sprites[sprite_loop].direction, 4);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position - 43, (int)sprites[sprite_loop].y_position + 20, sprites[sprite_loop].direction, 2);
                    }
                    else if (sprites[sprite_loop].timer == 60) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer == 62) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer > 63) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    } 
                }
                else if (sprites[sprite_loop].action_state == 17) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 20) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 67, (int)sprites[sprite_loop].y_position + 71, sprites[sprite_loop].direction, 0);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 98, (int)sprites[sprite_loop].y_position + 67, sprites[sprite_loop].direction, 1);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 129, (int)sprites[sprite_loop].y_position + 51, sprites[sprite_loop].direction, 2);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 140, (int)sprites[sprite_loop].y_position + 26, sprites[sprite_loop].direction, 3);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 129, (int)sprites[sprite_loop].y_position - 5, sprites[sprite_loop].direction, 4);
                    }
                    if (sprites[sprite_loop].timer == 35) {
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 123, (int)sprites[sprite_loop].y_position + 60, sprites[sprite_loop].direction, 3);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 116, (int)sprites[sprite_loop].y_position + 94, sprites[sprite_loop].direction, 2);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 116, (int)sprites[sprite_loop].y_position + 94, sprites[sprite_loop].direction, 4);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 116, (int)sprites[sprite_loop].y_position + 20, sprites[sprite_loop].direction, 4);
                        initialize_sprite(56, (int)sprites[sprite_loop].x_position + 116, (int)sprites[sprite_loop].y_position + 20, sprites[sprite_loop].direction, 2);
                    }
                    else if (sprites[sprite_loop].timer == 60) {
                        sprites[sprite_loop].frame = ICYUP02;
                        sprites[sprite_loop].width = 106;
                        sprites[sprite_loop].height = 140;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer == 62) {
                        sprites[sprite_loop].frame = ICYUP01;
                        sprites[sprite_loop].width = 65;
                        sprites[sprite_loop].height = 154;
                        sprites[sprite_loop].x_position += 5;
                    }
                    else if (sprites[sprite_loop].timer > 63) {
                        sprites[sprite_loop].y_position -= 30;
                        if (sprites[sprite_loop].y_position <= 820) sprites[sprite_loop].frame = ICYSHADOW04;
                        if (sprites[sprite_loop].y_position < 580) {
                            sprites[sprite_loop].timer = 0;
                            if (player.y_position > 1010) sprites[sprite_loop].action_state = 3;
                            else if (player.x_position < 3640) sprites[sprite_loop].action_state = 4;
                            else sprites[sprite_loop].action_state = 5;
                        }
                    } 
                }
                else if (sprites[sprite_loop].action_state == 18) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 60, (int)sprites[sprite_loop].y_position + 35, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 60, (int)sprites[sprite_loop].y_position + 35, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 60, (int)sprites[sprite_loop].y_position + 35, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 120) - 6, (int)sprites[sprite_loop].y_position + (rand() % 140) - 6, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 5);
                         else lastageportal[0] = 1;
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
	      else if (sprites[sprite_loop].type == 1008) {
                if (sprites[sprite_loop].action_state == 0) {
			  if (event_organizer == 3) { sprites[sprite_loop].action_state = 1; }
		    }
		    else if (sprites[sprite_loop].action_state == 1) {
                    sprites[sprite_loop].biba -= 4;
			  if (sprites[sprite_loop].biba <= 0) { sprites[sprite_loop].biba = 0; rest(50); if (event_organizer == 3) event_organizer = 61; }
                    if (input_locked == 0) { sprites[sprite_loop].timer = 20; sprites[sprite_loop].action_state = 2; sprites[sprite_loop].biba = 255; }
		    }
		    else if (sprites[sprite_loop].action_state == 2) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1215;
				sprites[sprite_loop].y_position = 276;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer % 15 == 0) initialize_sprite(75, (int)player.x_position - 2, (int)player.y_position + 16, 0, 0);
			  else if (sprites[sprite_loop].timer == 160) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 2; }
		    }
		    else if (sprites[sprite_loop].action_state == 3) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1075;
				sprites[sprite_loop].y_position = 356;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 26) flash_screen = 2;
			  else if (sprites[sprite_loop].timer == 27) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 28) flash_screen = 0;
			  else if (sprites[sprite_loop].timer > 25 && sprites[sprite_loop].timer % 10 == 0) {
				do { sprites[sprite_loop].animation_state = (rand() % 7) + 2; } while (sprites[sprite_loop].animation_state == sprites[sprite_loop].action_state);
				if (sprites[sprite_loop].animation_state == 2) initialize_sprite(76, 1218 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 3) initialize_sprite(76, 1078 + (rand() % 10), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 4) initialize_sprite(76, 1382 + (rand() % 6), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 5) initialize_sprite(76, 1118 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 6) initialize_sprite(76, 1318 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 7) initialize_sprite(76, 1518 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 8) initialize_sprite(76, 918 + (rand() % 30), 0, 0, 0);
			  }
			  else if (sprites[sprite_loop].timer == 128) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 3; }
		    }
		    else if (sprites[sprite_loop].action_state == 4) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1355;
				sprites[sprite_loop].y_position = 356;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 26) flash_screen = 2;
			  else if (sprites[sprite_loop].timer == 27) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 28) flash_screen = 0;
			  else if (sprites[sprite_loop].timer > 25 && sprites[sprite_loop].timer % 10 == 0) {
				do { sprites[sprite_loop].animation_state = (rand() % 7) + 2; } while (sprites[sprite_loop].animation_state == sprites[sprite_loop].action_state);
				if (sprites[sprite_loop].animation_state == 2) initialize_sprite(76, 1218 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 3) initialize_sprite(76, 1078 + (rand() % 10), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 4) initialize_sprite(76, 1382 + (rand() % 6), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 5) initialize_sprite(76, 1118 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 6) initialize_sprite(76, 1318 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 7) initialize_sprite(76, 1518 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 8) initialize_sprite(76, 918 + (rand() % 30), 0, 0, 0);
			  }
			  else if (sprites[sprite_loop].timer == 128) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 4; }
		    }
		    else if (sprites[sprite_loop].action_state == 5) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1115;
				sprites[sprite_loop].y_position = 116;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 1);
			  else if (sprites[sprite_loop].timer == 29) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 2);
			  else if (sprites[sprite_loop].timer == 33) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 3);
			  else if (sprites[sprite_loop].timer == 39) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 4);
			  else if (sprites[sprite_loop].timer == 45) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 5);
			  else if (sprites[sprite_loop].timer == 51) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 6);
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 5; }
		    }
		    else if (sprites[sprite_loop].action_state == 6) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1315;
				sprites[sprite_loop].y_position = 116;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 1);
			  else if (sprites[sprite_loop].timer == 29) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 2);
			  else if (sprites[sprite_loop].timer == 33) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 3);
			  else if (sprites[sprite_loop].timer == 39) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 4);
			  else if (sprites[sprite_loop].timer == 45) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 5);
			  else if (sprites[sprite_loop].timer == 51) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 6);
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 6; }
		    }
		    else if (sprites[sprite_loop].action_state == 7) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1515;
				sprites[sprite_loop].y_position = 236;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 9, 1, 1);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 44, 1, 2);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 80, (int)sprites[sprite_loop].y_position + 70, 1, 3);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 90, 1, 4);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 110, 1, 5);
			  }
			  else if (sprites[sprite_loop].timer == 60 || sprites[sprite_loop].timer == 70 || sprites[sprite_loop].timer == 80 || sprites[sprite_loop].timer == 86 || sprites[sprite_loop].timer == 96 || sprites[sprite_loop].timer == 106 || sprites[sprite_loop].timer == 120 || 
				     sprites[sprite_loop].timer == 130 || sprites[sprite_loop].timer == 140 || sprites[sprite_loop].timer == 150 || sprites[sprite_loop].timer == 160 || sprites[sprite_loop].timer == 165 || sprites[sprite_loop].timer == 180 || sprites[sprite_loop].timer == 190) {
				if (player.y_position < 160 && player.x_position < 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 90, 1, 4);
				else if (player.y_position < 160) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 110, 1, 5);
				else if (player.y_position <= 301) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 80, (int)sprites[sprite_loop].y_position + 70, 1, 3);
				else if (player.x_position < 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 44, 1, 2);
				else initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 9, 1, 1);
			  }
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 7; }
		    }
		    else if (sprites[sprite_loop].action_state == 8) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 915;
				sprites[sprite_loop].y_position = 236;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 9, 0, 1);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 44, 0, 2);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 106, (int)sprites[sprite_loop].y_position + 70, 0, 3);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 90, 0, 4);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 110, 0, 5);
			  }
			  else if (sprites[sprite_loop].timer == 60 || sprites[sprite_loop].timer == 70 || sprites[sprite_loop].timer == 80 || sprites[sprite_loop].timer == 86 || sprites[sprite_loop].timer == 96 || sprites[sprite_loop].timer == 106 || sprites[sprite_loop].timer == 120 || 
				     sprites[sprite_loop].timer == 130 || sprites[sprite_loop].timer == 140 || sprites[sprite_loop].timer == 150 || sprites[sprite_loop].timer == 160 || sprites[sprite_loop].timer == 165 || sprites[sprite_loop].timer == 180 || sprites[sprite_loop].timer == 190) {
				if (player.y_position < 160 && player.x_position > 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 90, 0, 4);
				else if (player.y_position < 160) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 110, 0, 5);
				else if (player.y_position <= 301) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 106, (int)sprites[sprite_loop].y_position + 70, 0, 3);
				else if (player.x_position > 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 44, 0, 2);
				else initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 9, 0, 1);
			  }
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 20; sprites[sprite_loop].animation_state = 8; }
		    }
		    else if (sprites[sprite_loop].action_state == 20) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer <= 10) { sprites[sprite_loop].biba -= 32; if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].biba = 0; }
			  else if (sprites[sprite_loop].timer == 11) {
				sprites[sprite_loop].x_position = 10;
				sprites[sprite_loop].y_position = 10;
			  }
			  else if (sprites[sprite_loop].timer == 50) {
			      sprites[sprite_loop].timer = 0;
				sprites[sprite_loop].rotate_factor = 0;
				/*if (sprites[sprite_loop].hit_points_left <= 5) {
				do { sprites[sprite_loop].action_state = (rand() % 6) + 22; } while (sprites[sprite_loop].action_state == (int)sprites[sprite_loop].animation_state + 20);
			      }*/
				do { sprites[sprite_loop].action_state = (rand() % 7) + 2; } while (sprites[sprite_loop].action_state == (int)sprites[sprite_loop].animation_state);
			      sprites[sprite_loop].animation_state = 0;
                    }
		    }
		    else if (sprites[sprite_loop].action_state == 22) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1215;
				sprites[sprite_loop].y_position = 276;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 26) flash_screen = 2;
			  else if (sprites[sprite_loop].timer == 27) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 28) flash_screen = 0;
			  else if (sprites[sprite_loop].timer > 25 && sprites[sprite_loop].timer % 10 == 0) {
				do { sprites[sprite_loop].animation_state = (rand() % 7) + 2; } while (sprites[sprite_loop].animation_state == 2);
				if (sprites[sprite_loop].animation_state == 2) initialize_sprite(76, 1218 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 3) initialize_sprite(76, 1078 + (rand() % 10), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 4) initialize_sprite(76, 1382 + (rand() % 6), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 5) initialize_sprite(76, 1118 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 6) initialize_sprite(76, 1318 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 7) initialize_sprite(76, 1518 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 8) initialize_sprite(76, 918 + (rand() % 30), 0, 0, 0);
			  }
			  if (sprites[sprite_loop].timer % 15 == 3) initialize_sprite(75, (int)player.x_position - 2, (int)player.y_position + 16, 0, 0);
			  else if (sprites[sprite_loop].timer == 160) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 40; sprites[sprite_loop].animation_state = 22; }
		    }
		    else if (sprites[sprite_loop].action_state == 23) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1115;
				sprites[sprite_loop].y_position = 116;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 26) flash_screen = 2;
			  else if (sprites[sprite_loop].timer == 27) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 28) flash_screen = 0;
			  else if (sprites[sprite_loop].timer > 25 && sprites[sprite_loop].timer % 10 == 0) {
				do { sprites[sprite_loop].animation_state = (rand() % 7) + 2; } while (sprites[sprite_loop].animation_state == 5);
				if (sprites[sprite_loop].animation_state == 2) initialize_sprite(76, 1218 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 3) initialize_sprite(76, 1078 + (rand() % 10), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 4) initialize_sprite(76, 1382 + (rand() % 6), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 5) initialize_sprite(76, 1118 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 6) initialize_sprite(76, 1318 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 7) initialize_sprite(76, 1518 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 8) initialize_sprite(76, 918 + (rand() % 30), 0, 0, 0);
			  }
			  if (sprites[sprite_loop].timer == 25) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 1);
			  else if (sprites[sprite_loop].timer == 29) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 2);
			  else if (sprites[sprite_loop].timer == 33) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 3);
			  else if (sprites[sprite_loop].timer == 39) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 4);
			  else if (sprites[sprite_loop].timer == 45) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 5);
			  else if (sprites[sprite_loop].timer == 51) initialize_sprite(77, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 6);
			  else if (sprites[sprite_loop].timer == 190) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 40; sprites[sprite_loop].animation_state = 23; }
		    }
		    else if (sprites[sprite_loop].action_state == 24) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1315;
				sprites[sprite_loop].y_position = 116;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 1);
			  else if (sprites[sprite_loop].timer == 29) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 2);
			  else if (sprites[sprite_loop].timer == 33) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 3);
			  else if (sprites[sprite_loop].timer == 39) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 4);
			  else if (sprites[sprite_loop].timer == 45) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 5);
			  else if (sprites[sprite_loop].timer == 51) initialize_sprite(78, (int)sprites[sprite_loop].x_position + 30, (int)sprites[sprite_loop].y_position + 80, 0, 6);
			  if (sprites[sprite_loop].timer % 15 == 3) initialize_sprite(75, (int)player.x_position - 2, (int)player.y_position + 16, 0, 0);
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 40; sprites[sprite_loop].animation_state = 24; }
		    }
		    else if (sprites[sprite_loop].action_state == 25) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 915;
				sprites[sprite_loop].y_position = 236;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 9, 0, 1);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 44, 0, 2);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 106, (int)sprites[sprite_loop].y_position + 70, 0, 3);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 90, 0, 4);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 110, 0, 5);
			  }
			  else if (sprites[sprite_loop].timer == 60 || sprites[sprite_loop].timer == 70 || sprites[sprite_loop].timer == 80 || sprites[sprite_loop].timer == 86 || sprites[sprite_loop].timer == 96 || sprites[sprite_loop].timer == 106 || sprites[sprite_loop].timer == 120 || 
				     sprites[sprite_loop].timer == 130 || sprites[sprite_loop].timer == 140 || sprites[sprite_loop].timer == 150 || sprites[sprite_loop].timer == 160 || sprites[sprite_loop].timer == 165 || sprites[sprite_loop].timer == 180 || sprites[sprite_loop].timer == 190) {
				if (player.y_position < 160 && player.x_position > 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 90, 0, 4);
				else if (player.y_position < 160) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 110, 0, 5);
				else if (player.y_position <= 301) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 106, (int)sprites[sprite_loop].y_position + 70, 0, 3);
				else if (player.x_position > 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position + 102, (int)sprites[sprite_loop].y_position + 44, 0, 2);
				else initialize_sprite(79, (int)sprites[sprite_loop].x_position + 87, (int)sprites[sprite_loop].y_position + 9, 0, 1);
			  }
			  if (sprites[sprite_loop].timer == 25) initialize_sprite(77, 1115 + 30, 116 + 80, 0, 1);
			  else if (sprites[sprite_loop].timer == 29) initialize_sprite(77, 1115 + 30, 116 + 80, 0, 2);
			  else if (sprites[sprite_loop].timer == 33) initialize_sprite(77, 1115 + 30, 116 + 80, 0, 3);
			  else if (sprites[sprite_loop].timer == 39) initialize_sprite(77, 1115 + 30, 116 + 80, 0, 4);
			  else if (sprites[sprite_loop].timer == 45) initialize_sprite(77, 1115 + 30, 116 + 80, 0, 5);
			  else if (sprites[sprite_loop].timer == 51) initialize_sprite(77, 1115 + 30, 116 + 80, 0, 6);
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 40; sprites[sprite_loop].animation_state = 25; }
		    }
		    else if (sprites[sprite_loop].action_state == 26) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1515;
				sprites[sprite_loop].y_position = 236;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 9, 1, 1);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 44, 1, 2);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 80, (int)sprites[sprite_loop].y_position + 70, 1, 3);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 90, 1, 4);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 110, 1, 5);
			  }
			  else if (sprites[sprite_loop].timer == 60 || sprites[sprite_loop].timer == 70 || sprites[sprite_loop].timer == 80 || sprites[sprite_loop].timer == 86 || sprites[sprite_loop].timer == 96 || sprites[sprite_loop].timer == 106 || sprites[sprite_loop].timer == 120 || 
				     sprites[sprite_loop].timer == 130 || sprites[sprite_loop].timer == 140 || sprites[sprite_loop].timer == 150 || sprites[sprite_loop].timer == 160 || sprites[sprite_loop].timer == 165 || sprites[sprite_loop].timer == 180 || sprites[sprite_loop].timer == 190) {
				if (player.y_position < 160 && player.x_position < 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 90, 1, 4);
				else if (player.y_position < 160) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 110, 1, 5);
				else if (player.y_position <= 301) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 80, (int)sprites[sprite_loop].y_position + 70, 1, 3);
				else if (player.x_position < 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 44, 1, 2);
				else initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 9, 1, 1);
			  }
			  if (sprites[sprite_loop].timer % 15 == 3) initialize_sprite(75, (int)player.x_position - 2, (int)player.y_position + 16, 0, 0);
			  else if (sprites[sprite_loop].timer == 200) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 40; sprites[sprite_loop].animation_state = 26; }
		    }
		    else if (sprites[sprite_loop].action_state == 27) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) {
				sprites[sprite_loop].x_position = 1515;
				sprites[sprite_loop].y_position = 236;
				sprites[sprite_loop].biba = 0;
			  }
                    else if (sprites[sprite_loop].timer <= 20) {
				sprites[sprite_loop].biba += 16;
				if (sprites[sprite_loop].biba > 255) sprites[sprite_loop].biba = 255;
			  }
			  else if (sprites[sprite_loop].timer == 25) {
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 9, 1, 1);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 44, 1, 2);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 80, (int)sprites[sprite_loop].y_position + 70, 1, 3);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 90, 1, 4);
                        initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 110, 1, 5);
			  }
			  else if (sprites[sprite_loop].timer == 60 || sprites[sprite_loop].timer == 70 || sprites[sprite_loop].timer == 80 || sprites[sprite_loop].timer == 86 || sprites[sprite_loop].timer == 96 || sprites[sprite_loop].timer == 106 || sprites[sprite_loop].timer == 120 || 
				     sprites[sprite_loop].timer == 130 || sprites[sprite_loop].timer == 140 || sprites[sprite_loop].timer == 150 || sprites[sprite_loop].timer == 160 || sprites[sprite_loop].timer == 165 || sprites[sprite_loop].timer == 180 || sprites[sprite_loop].timer == 190) {
				if (player.y_position < 160 && player.x_position < 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 90, 1, 4);
				else if (player.y_position < 160) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 110, 1, 5);
				else if (player.y_position <= 301) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 80, (int)sprites[sprite_loop].y_position + 70, 1, 3);
				else if (player.x_position < 1240) initialize_sprite(79, (int)sprites[sprite_loop].x_position - 70, (int)sprites[sprite_loop].y_position + 44, 1, 2);
				else initialize_sprite(79, (int)sprites[sprite_loop].x_position - 30, (int)sprites[sprite_loop].y_position + 9, 1, 1);
			  }
			  if (sprites[sprite_loop].timer == 25) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 26) flash_screen = 2;
			  else if (sprites[sprite_loop].timer == 27) flash_screen = 1;
			  else if (sprites[sprite_loop].timer == 28) flash_screen = 0;
			  else if (sprites[sprite_loop].timer > 25 && sprites[sprite_loop].timer % 10 == 0) {
				do { sprites[sprite_loop].animation_state = (rand() % 7) + 2; } while (sprites[sprite_loop].animation_state == 7);
				if (sprites[sprite_loop].animation_state == 2) initialize_sprite(76, 1218 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 3) initialize_sprite(76, 1078 + (rand() % 10), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 4) initialize_sprite(76, 1382 + (rand() % 6), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 5) initialize_sprite(76, 1118 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 6) initialize_sprite(76, 1318 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 7) initialize_sprite(76, 1518 + (rand() % 30), 0, 0, 0);
				else if (sprites[sprite_loop].animation_state == 8) initialize_sprite(76, 918 + (rand() % 30), 0, 0, 0);
			  }
			  else if (sprites[sprite_loop].timer == 201) { sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 40; sprites[sprite_loop].animation_state = 27; }
		    }
		    else if (sprites[sprite_loop].action_state == 40) {
			  sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer <= 10) { sprites[sprite_loop].biba -= 32; if (sprites[sprite_loop].biba <= 0) sprites[sprite_loop].biba = 0; }
			  else if (sprites[sprite_loop].timer == 11) {
				sprites[sprite_loop].x_position = 10;
				sprites[sprite_loop].y_position = 10;
			  }
			  else if (sprites[sprite_loop].timer == 50) {
			      sprites[sprite_loop].timer = 0;
				sprites[sprite_loop].rotate_factor = 0;
				do { sprites[sprite_loop].action_state = (rand() % 6) + 22; } while (sprites[sprite_loop].action_state == (int)sprites[sprite_loop].animation_state);
			      sprites[sprite_loop].animation_state = 0;
                    }
		    }
		    else if (sprites[sprite_loop].action_state == 666) {
                     if (sprites[sprite_loop].timer == 5) {
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 40, (int)sprites[sprite_loop].y_position + 60, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 40, (int)sprites[sprite_loop].y_position + 60, 0, 0);
                         initialize_sprite(1111, (int)sprites[sprite_loop].x_position + 40, (int)sprites[sprite_loop].y_position + 60, 0, 0);
                     }
                     else if (sprites[sprite_loop].timer % 7 == 3) {
                         initialize_sprite(113, (int)sprites[sprite_loop].x_position + (rand() % 90) - 20, (int)sprites[sprite_loop].y_position + (rand() % 120) - 10, 0, 0);
                     }
                     if (bosslife == -1) {
                         if (lastageboss == 0) initialize_sprite(1666, (int)sprites[sprite_loop].x_position + (sprites[sprite_loop].width / 2) - 11, (int)sprites[sprite_loop].y_position + (sprites[sprite_loop].height / 2) - 18, 0, 5);
                         sprites[sprite_loop].active = 0;
                     }
                     if (sprites[sprite_loop].active == 1) sprites[sprite_loop].timer++;
                }
                if (sprites[sprite_loop].hit_points_left == (int)sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)sprites[sprite_loop].hit_points_left;
                else if (bosslife > sprites[sprite_loop].hit_points_left && bossfight == 1) bosslife = (int)(sprites[sprite_loop].hit_points_left + 0.5);
            }
            else if (sprites[sprite_loop].type == 1666) {
                if (sprites[sprite_loop].action_state == 0) {
                    sprites[sprite_loop].timer++;
                    if (sprites[sprite_loop].timer == 1) sprites[sprite_loop].y_speed = 1;
                    else if (sprites[sprite_loop].timer == 2) sprites[sprite_loop].y_speed = 2;
                    else if (sprites[sprite_loop].timer == 3) sprites[sprite_loop].y_speed = 1;
                    else if (sprites[sprite_loop].timer == 4) sprites[sprite_loop].y_speed = 0;
                    else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].y_speed = -1;
                    else if (sprites[sprite_loop].timer == 6) sprites[sprite_loop].y_speed = -2;
                    else if (sprites[sprite_loop].timer == 7) sprites[sprite_loop].y_speed = -1;
                    else if (sprites[sprite_loop].timer == 8) sprites[sprite_loop].y_speed = 0;
                    else if (light_level == 1) {
                         sprites[sprite_loop].timer = 0; sprites[sprite_loop].action_state = 1;
                    }
                }
                else if (sprites[sprite_loop].action_state == 1) {
                     sprites[sprite_loop].timer++;
                     if (sprites[sprite_loop].timer % 16 == 0) { sprites[sprite_loop].frame = CARD01; sprites[sprite_loop].direction = 0; }
                     else if (sprites[sprite_loop].timer % 16 == 2) { sprites[sprite_loop].frame = CARD02; sprites[sprite_loop].direction = 0; }
                     else if (sprites[sprite_loop].timer % 16 == 4) { sprites[sprite_loop].frame = CARD03; sprites[sprite_loop].direction = 0; }
                     else if (sprites[sprite_loop].timer % 16 == 6) { sprites[sprite_loop].frame = CARD04; sprites[sprite_loop].direction = 0; }
                     else if (sprites[sprite_loop].timer % 16 == 8) { sprites[sprite_loop].frame = CARD05; sprites[sprite_loop].direction = 0; }
                     else if (sprites[sprite_loop].timer % 16 == 10) { sprites[sprite_loop].frame = CARD04; sprites[sprite_loop].direction = 1; }
                     else if (sprites[sprite_loop].timer % 16 == 12) { sprites[sprite_loop].frame = CARD03; sprites[sprite_loop].direction = 1; }
                     else if (sprites[sprite_loop].timer % 16 == 14) { sprites[sprite_loop].frame = CARD02; sprites[sprite_loop].direction = 1; }
                     if (sprites[sprite_loop].x_position > player.x_position + (50 / 2) - 11 && sprites[sprite_loop].x_position - (player.x_position + (50 / 2) - 11) > 5) sprites[sprite_loop].x_position -= 5;
                     else if (sprites[sprite_loop].x_position < player.x_position + (50 / 2) - 11 && (player.x_position + (50 / 2) - 11) - sprites[sprite_loop].x_position > 5) sprites[sprite_loop].x_position += 5;
                     else sprites[sprite_loop].x_position = player.x_position + (50 / 2) - 11;
                     if (sprites[sprite_loop].y_position > player.y_position + (50 / 2) - 18 && sprites[sprite_loop].y_position - (player.y_position + (80 / 2) - 18) > 5) sprites[sprite_loop].y_position -= 5;
                     else if (sprites[sprite_loop].y_position < player.y_position + (80 / 2) - 18 && (player.y_position + (80 / 2) - 18) - sprites[sprite_loop].y_position > 5) sprites[sprite_loop].y_position += 5;
                     else sprites[sprite_loop].y_position = player.y_position + (80 / 2) - 18;
                     if (sprites[sprite_loop].y_position == player.y_position + (80 / 2) - 18 && sprites[sprite_loop].x_position == player.x_position + (50 / 2) - 11 && sprites[sprite_loop].timer % 16 == 0) { sprites[sprite_loop].action_state = 2; sprites[sprite_loop].timer = 0; play_sample((SAMPLE *)mydatafile[CARDGET].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                }
                else if (sprites[sprite_loop].action_state == 2) {
                     sprites[sprite_loop].strength -= 30;
                     if (sprites[sprite_loop].strength < 0) { player.shine = 1; player.cards[sprites[sprite_loop].biba] = 1;
                     player.score++;
                     if (player.score == 10) { player.hpmax = 16; sparkmandril = 1; }
                     else if (player.score == 20) { player.hpmax = 17; sparkmandril = 1; }
                     else if (player.score == 30) { player.hpmax = 18; sparkmandril = 1; }
                     else if (player.score == 40) { player.hpmax = 19; sparkmandril = 1; }
                     else if (player.score == 52) { player.hpmax = 20; sparkmandril = 1; }
                     sprites[sprite_loop].active = 0;}
                }
            }
        }
    }
    
    for (int sprite_loop = 0; sprite_loop < number_of_sprites; sprite_loop++) {
        checkif:
        if (sprites[sprite_loop].active == 0 && sprite_loop < number_of_sprites) { destroysprite(sprite_loop); goto checkif; }
    }
    
    if (movingscreen == 1) {
        if (looper > 0) {
            if (looper > 8 && looper < 46) {
                if (looper == 9) {
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
            if (looper == 46) {
                player.x_position += 2;
                if (doorrecord != 5 && doorrecord != 11) screenx -= 14;
            }
            if (looper == 56) {
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
    
    if (dead == 1) { die(); dead = 0; }
}
