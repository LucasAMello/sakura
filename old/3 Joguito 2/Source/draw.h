void draw() {
    
    if (screen_locked == 0) {
    if (player.x_position > Map.limitleft + 299 && player.x_position < Map.limitright - 340)
    {
           screenx = 300 - (int)player.x_position;
    }
    else if (player.x_position < Map.limitleft + 300) screenx = Map.limitleft * -1;
    else screenx = (Map.limitright - 640) * -1;
    if (player.y_position > Map.limitup + 239 && player.y_position < Map.limitdown - 240)
    {
           screeny = 240 - (int)player.y_position;
    }
    else if (player.y_position < Map.limitup + 240) screeny = Map.limitup * -1;
    else screeny = (Map.limitdown - 480) * -1;
    }
    
    if (lastageblack == 0) {
      if (Map.type == 1 || Map.type == 3) {
        if (Map.type == 3) masked_blit( background, buffer, (screenx / 5) * -1, screeny * -1, 0, 0, 640, 480);
        else if (current_level == 80) masked_blit( background, buffer, (screenx) * -1, (screeny / 5) * -1, 0, 0, 640, 480);
        else masked_blit( background, buffer, (screenx / 5) * -1, (screeny / 5) * -1, 0, 0, 640, 480);
      }
      masked_blit( scenario, buffer, screenx * -1, screeny * -1, 0, 0, 640, 480);
    }
    else {
      if (lastageblack == 255) {
        BITMAP* temp = create_bitmap(640, 480);
        clear_to_color(temp, makecol(0,0,0));
        draw_sprite( buffer, temp, 0, 0);
        destroy_bitmap(temp);
      }
      else {
        BITMAP* temp = create_bitmap(640, 480);
        BITMAP* temp2 = create_bitmap(640, 480);
        clear_to_color(temp, bitmap_mask_color(background));
        clear_to_color(temp2, bitmap_mask_color(scenario));
        masked_blit( background, temp, screenx * -1, (screeny / 5) * -1, 0, 0, 640, 480);
        masked_blit( scenario, temp2, screenx * -1, screeny * -1, 0, 0, 640, 480);
        set_trans_blender(0,0,0,0);
        draw_lit_sprite( buffer, temp, 0, 0, lastageblack);
        draw_lit_sprite( buffer, temp2, 0, 0, lastageblack);
        destroy_bitmap(temp); destroy_bitmap(temp2);
      }
    }

    for (int sprite_loop = 0; sprite_loop <= number_of_sprites; sprite_loop++) {
	    if (sprites[sprite_loop].active == 1) {
            
            if (sprites[sprite_loop].type == 35) {
                draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 36) {
                if (sprites[sprite_loop].direction == 0) {
                    if (sprites[sprite_loop].timer % 4 == 0) {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                    else if (sprites[sprite_loop].timer % 4 == 1) {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                    else if (sprites[sprite_loop].timer % 4 == 2) {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                    else if (sprites[sprite_loop].timer % 4 == 3) {
                        draw_sprite(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                            else draw_sprite(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)sprites[sprite_loop].x_position + screenx + 19 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                }
                else {
                    if (sprites[sprite_loop].timer % 4 == 0) {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 6);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                    else if (sprites[sprite_loop].timer % 4 == 1) {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 6);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA1].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                    else if (sprites[sprite_loop].timer % 4 == 2) {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 6);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO1].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                    else if (sprites[sprite_loop].timer % 4 == 3) {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_FIM2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 6);
                        for (int x = 0; x <= sprites[sprite_loop].biba; x++) {
                            if (x == sprites[sprite_loop].biba) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_PONTA2].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny);
                            else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WATER_MEIO2].dat, (int)sprites[sprite_loop].x_position + screenx + 14 + (16 * x), (int)sprites[sprite_loop].y_position + screeny + 6);
                        }
                    }
                }
            }
            else if (sprites[sprite_loop].type == 46) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			}
            else if (sprites[sprite_loop].type == 47) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			}
        }
	}

    for (int sprite_loop = 0; sprite_loop < number_of_sprites + 1; sprite_loop++) {
	    if (sprites[sprite_loop].active == 1) {
            if (sprites[sprite_loop].type == 1000) {
                 if (sprites[sprite_loop].timer == doorrecord) {
                     if (stopall == 1 && looper > 0 && looper < 9) masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, looper * 10, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 100 - (looper * 10));
                     else if (stopall == 1 && looper > 47 && looper < 56) masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, 80 - ((looper - 47) * 10), (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 20 + ((looper - 47) * 10));
                     else if (stopall == 1 && looper == 56) { masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, 80 - ((looper - 48) * 10), (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 20 + ((looper - 48) * 10)); call_event = sprites[sprite_loop].timer; if (call_event == 0) call_event = 13; sprites[sprite_loop].timer = -1; sprites[sprite_loop].height = 100; }
                     else if (stopall == 1 && starting == 0) masked_blit((BITMAP*)mydatafile[PORTA1].dat, buffer, 0, 80, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 20);
                     else draw_sprite( buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                 }
                 else draw_sprite( buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 999) {
                 if (sprites[sprite_loop].timer == doorrecord) {
                     if (stopall == 1 && looper > 0 && looper < 9) masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, looper * 13, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 140 - (looper * 13));
                     else if (stopall == 1 && looper > 47 && looper < 56) masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, 104 - ((looper - 47) * 13), (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 36 + ((looper - 47) * 13));
                     else if (stopall == 1 && looper == 56) { masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, 104 - ((looper - 48) * 13), (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 36 + ((looper - 47) * 13)); call_event = sprites[sprite_loop].timer; sprites[sprite_loop].timer = -1; sprites[sprite_loop].height = 140; }
                     else if (stopall == 1) masked_blit((BITMAP*)mydatafile[PORTA2].dat, buffer, 0, 104, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 36);
                     else draw_sprite( buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                 }
                 else draw_sprite( buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 401) {
                 if (sprites[sprite_loop].timer > 0)
                     masked_blit((BITMAP*)mydatafile[IRON_DOOR].dat, buffer, 0, sprites[sprite_loop].timer, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 30, 200 - sprites[sprite_loop].timer);
                 else draw_sprite( buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 403) {
                 set_trans_blender(0,0,0,100);
                 draw_trans_sprite(buffer, (BITMAP*)mydatafile[LUZ].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 65) {
               if (sprites[sprite_loop].action_state == 0) {
                 draw_sprite(buffer, (BITMAP*)mydatafile[CARDHOLDER].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                 if (sprites[sprite_loop].timer % 40 == 0) sprites[sprite_loop].frame = CARD01;
                 else if (sprites[sprite_loop].timer % 40 == 2) sprites[sprite_loop].frame = CARD02;
                 else if (sprites[sprite_loop].timer % 40 == 4) sprites[sprite_loop].frame = CARD03;
                 else if (sprites[sprite_loop].timer % 40 == 6) sprites[sprite_loop].frame = CARD04;
                 else if (sprites[sprite_loop].timer % 40 == 8) sprites[sprite_loop].frame = CARD05;
                 else if (sprites[sprite_loop].timer % 40 == 10) sprites[sprite_loop].frame = CARD04;
                 else if (sprites[sprite_loop].timer % 40 == 12) sprites[sprite_loop].frame = CARD03;
                 else if (sprites[sprite_loop].timer % 40 == 14) sprites[sprite_loop].frame = CARD02;
                 else if (sprites[sprite_loop].timer % 40 == 16) sprites[sprite_loop].frame = CARD01;
                 if (sprites[sprite_loop].timer % 40 < 10) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 9, (int)sprites[sprite_loop].y_position + screeny + 12);
                 else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 9, (int)sprites[sprite_loop].y_position + screeny + 12);
               }
               else {
                 if (sprites[sprite_loop].timer % 2 == 0) draw_sprite(buffer, (BITMAP*)mydatafile[CARDHOLDER2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
            }
            else if (sprites[sprite_loop].type == 69) {
               if (sprites[sprite_loop].action_state == 0) {
                 if (sprites[sprite_loop].timer % 40 == 0) sprites[sprite_loop].frame = CARD01;
                 else if (sprites[sprite_loop].timer % 40 == 2) sprites[sprite_loop].frame = CARD02;
                 else if (sprites[sprite_loop].timer % 40 == 4) sprites[sprite_loop].frame = CARD03;
                 else if (sprites[sprite_loop].timer % 40 == 6) sprites[sprite_loop].frame = CARD04;
                 else if (sprites[sprite_loop].timer % 40 == 8) sprites[sprite_loop].frame = CARD05;
                 else if (sprites[sprite_loop].timer % 40 == 10) sprites[sprite_loop].frame = CARD04;
                 else if (sprites[sprite_loop].timer % 40 == 12) sprites[sprite_loop].frame = CARD03;
                 else if (sprites[sprite_loop].timer % 40 == 14) sprites[sprite_loop].frame = CARD02;
                 else if (sprites[sprite_loop].timer % 40 == 16) sprites[sprite_loop].frame = CARD01;
                 if (sprites[sprite_loop].timer % 40 < 10) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                 else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
               else if (sprites[sprite_loop].action_state == 3) {
                 set_trans_blender(0,0,0,sprites[sprite_loop].strength);
                 draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
            }
            else if (sprites[sprite_loop].type == 23) {
                if (sprites[sprite_loop].action_state % 3 == 0) draw_sprite(buffer, (BITMAP*)mydatafile[ORANGEH01].dat, (int)sprites[sprite_loop].x_position + screenx + 4, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].action_state % 3 == 1) draw_sprite(buffer, (BITMAP*)mydatafile[ORANGEH02].dat, (int)sprites[sprite_loop].x_position + screenx + 4, (int)sprites[sprite_loop].y_position + screeny);
                else draw_sprite(buffer, (BITMAP*)mydatafile[ORANGEH03].dat, (int)sprites[sprite_loop].x_position + screenx + 4, (int)sprites[sprite_loop].y_position + screeny);
                if (sprites[sprite_loop].timer >= 9) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 10);
			    else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 10);
            }
            else if (sprites[sprite_loop].type == 15) {
                set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
			    if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else {
                    BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			        draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (sprites[sprite_loop].type == 67) {
              if (sprites[sprite_loop].action_state == 0) {
                if (player.cards[sprites[sprite_loop].biba] == 0) draw_sprite(buffer, (BITMAP*)mydatafile[CARD01].dat, (int)sprites[sprite_loop].x_position + screenx + 9, (int)sprites[sprite_loop].y_position + screeny + 6);
                set_trans_blender(0, 0, 0, (int)sprites[sprite_loop].x_speed);
			    draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
              }
              else {
                if (player.cards[sprites[sprite_loop].biba] == 0) draw_sprite(buffer, (BITMAP*)mydatafile[CARD01].dat, (int)sprites[sprite_loop].x_position + screenx + 9, (int)sprites[sprite_loop].y_position + screeny + 6);
                set_trans_blender(0, 0, 0, (int)sprites[sprite_loop].x_speed);
			    draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                set_trans_blender(0, 0, 0, (int)sprites[sprite_loop].y_speed);
			    draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].direction].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
              }
            }
            else if (sprites[sprite_loop].type == 17) {
                set_trans_blender(0, 0, 0, sprites[sprite_loop].action_state);
			    if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else {
                    BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			        draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (sprites[sprite_loop].type == 62) {
                set_trans_blender(0, 0, 0, sprites[sprite_loop].action_state);
			    if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else {
                    BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			        draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (sprites[sprite_loop].type == 400) {
                draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                rotate_sprite(buffer, (BITMAP*)mydatafile[WINDMILL1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
            }
            else if (sprites[sprite_loop].type == 202) {
                if (player.frame == PLAYERD) draw_sprite(buffer, (BITMAP*)mydatafile[VIDAZ].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (player.frame == NULO) rest(1);
                else if (sprites[sprite_loop].timer % 2 == 0) {
                    if (player.current_weapon == 1) draw_sprite(buffer, (BITMAP*)mydatafile[VIDA].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 2)draw_sprite(buffer, (BITMAP*)mydatafile[VIDAA].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 3)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAB].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 4)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAC].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 5)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAD].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 6)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAE].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 7)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAF].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
                else {
                    if (player.current_weapon == 1) draw_sprite(buffer, (BITMAP*)mydatafile[VIDA1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 2)draw_sprite(buffer, (BITMAP*)mydatafile[VIDAA1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 3)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAB1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 4)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAC1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 5)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAD1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 6)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAE1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else if (player.current_weapon == 7)  draw_sprite(buffer, (BITMAP*)mydatafile[VIDAF1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
            }
            else if (sprites[sprite_loop].type == 18) {
                masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx - 8, (int)sprites[sprite_loop].biba + screeny, 11, 150);
                masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 11, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position, 48, 22);
                masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 59, 0, (int)sprites[sprite_loop].x_position + screenx + 44, (int)sprites[sprite_loop].biba + screeny, 11, 150);
            }
            else if (sprites[sprite_loop].type == 19) {
                if (sprites[sprite_loop].direction == 0)
                    draw_sprite(buffer, (BITMAP*)mydatafile[WALLTURRET].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].direction == 1)
                    draw_sprite(buffer, (BITMAP*)mydatafile[WALLTURRET2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[WALLTURRET2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 22) {
                if (sprites[sprite_loop].timer < 2) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 8, 11);
                else if (sprites[sprite_loop].timer < 4) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 16, 11);
                else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 24) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].direction == 1) rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 5, (int)sprites[sprite_loop].y_position + screeny - 5, itofix(64));
                else if (sprites[sprite_loop].direction == 2) draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 5, (int)sprites[sprite_loop].y_position + screeny - 5, itofix(192));
            }
            else if (sprites[sprite_loop].type == 25) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].direction == 1) rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 3, (int)sprites[sprite_loop].y_position + screeny + 2, itofix(64));
                else if (sprites[sprite_loop].direction == 2) draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 3, (int)sprites[sprite_loop].y_position + screeny + 2, itofix(192));
            }
            else if (sprites[sprite_loop].type == 26) {
                if (sprites[sprite_loop].frame == ZOCK01) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].frame == ZOCK02) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].frame == ZOCK03) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].frame == ZOCK04) sprites[sprite_loop].frame = ZOCK01;
                draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 5, (int)sprites[sprite_loop].y_position + screeny - 8);
            }
		    else if (sprites[sprite_loop].type == 28) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 1) {
                    sprite_colision(sprite_loop, 28);
                    char col = 'p';
                    if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
                    else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
                    if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position >= 80)) col = 'n';
                    else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';
                    if (col != 'n') { sprites[sprite_loop].biba = (int)player.y_position; sprites[sprite_loop].animation_state = 1; if (input_locked == 0) damage(sprites[sprite_loop].strength); }
                    if (sprites[sprite_loop].biba != 0) sprites[sprite_loop].height = (int)(sprites[sprite_loop].biba - sprites[sprite_loop].y_position);
                }
                else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].frame = THUNDER_SHOT02;
                else if (sprites[sprite_loop].timer == 9) sprites[sprite_loop].frame = THUNDER_SHOT03;
                else if (sprites[sprite_loop].timer == 13) { sprites[sprite_loop].active = 0; sprite_loop--; }
            }
            else if (sprites[sprite_loop].type == 76) {
                sprites[sprite_loop].timer++;
                if (sprites[sprite_loop].timer == 1) {
                    sprite_colision(sprite_loop, 76);
                    char col = 'p';
                    if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
                    else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
                    if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position >= 80)) col = 'n';
                    else if (sprites[sprite_loop].biba == 0 && ((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';
                    else if (sprites[sprite_loop].biba > 0 && ((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].biba - (int)sprites[sprite_loop].y_position)) col = 'n';
                    if (col != 'n') { sprites[sprite_loop].biba = (int)player.y_position; sprites[sprite_loop].animation_state = 1; if (input_locked == 0) damage(sprites[sprite_loop].strength); }
                    if (sprites[sprite_loop].biba != 0) sprites[sprite_loop].height = (int)(sprites[sprite_loop].biba - sprites[sprite_loop].y_position);
                }
                else if (sprites[sprite_loop].timer == 5) sprites[sprite_loop].frame = THUNDER_SHOT02;
                else if (sprites[sprite_loop].timer == 9) sprites[sprite_loop].frame = THUNDER_SHOT03;
                else if (sprites[sprite_loop].timer == 13) { sprites[sprite_loop].active = 0; sprite_loop--; }
            }
            else if (sprites[sprite_loop].type == 29) {
                if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].direction == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width, sprites[sprite_loop].height);
                    else {
                        BITMAP* temp = create_bitmap(37, 34);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width, sprites[sprite_loop].height);
                        destroy_bitmap(temp);
                    }
                }
            }
            else if (sprites[sprite_loop].type == 30) {
                if (player.x_position > sprites[sprite_loop].x_position) sprites[sprite_loop].direction = 0;
                else sprites[sprite_loop].direction = 1;
                if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].direction == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width, sprites[sprite_loop].height);
                    else {
                        BITMAP* temp = create_bitmap(36, 51);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width, sprites[sprite_loop].height);
                        destroy_bitmap(temp);
                    }
                }
                else if (sprites[sprite_loop].frame == SEAHORSE3) {
                    rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
                    sprites[sprite_loop].rotate_factor += 24;
                }
                else if (sprites[sprite_loop].action_state == 2 || sprites[sprite_loop].action_state == 3) {
                    if (player.x_position > sprites[sprite_loop].x_position) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
            }
            else if (sprites[sprite_loop].type == 72) {
                if (player.x_position > sprites[sprite_loop].x_position) sprites[sprite_loop].direction = 0;
                else sprites[sprite_loop].direction = 1;
                if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].direction == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width, sprites[sprite_loop].height);
                    else {
                        BITMAP* temp = create_bitmap(36, 51);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width, sprites[sprite_loop].height);
                        destroy_bitmap(temp);
                    }
                }
                else if (sprites[sprite_loop].frame == SEAHORSE3) {
                    rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
                    sprites[sprite_loop].rotate_factor += 24;
                }
                else if (sprites[sprite_loop].action_state == 2 || sprites[sprite_loop].action_state == 3) {
                    if (player.x_position > sprites[sprite_loop].x_position) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
            }
            else if (sprites[sprite_loop].type == 73) {
                draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 74) {
                draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 33) {
                if (sprites[sprite_loop].action_state == 0) {
			        if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			        else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    }
			    else if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].direction == 0) rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
                    else rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT4].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT3].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[EWULOSTRAPT3].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
			    else if (sprites[sprite_loop].action_state == 3) {
                    if (sprites[sprite_loop].direction == 0) rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
                    else rotate_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT4].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
                }
                else if (sprites[sprite_loop].action_state == 4) {
			        if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			        else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[EWULOSTRAPT2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    }
                
            }
            else if (sprites[sprite_loop].type == 38) {
                 if (sprites[sprite_loop].direction == 1) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                 else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 40) {
                 if (sprites[sprite_loop].direction == 1) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                 else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 42) {
                 draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny - 3);
            }
            else if (sprites[sprite_loop].type == 44) {
                 if (sprites[sprite_loop].timer % 45 == 0) sprites[sprite_loop].frame = LAVA1;
                 else if (sprites[sprite_loop].timer % 45 == 15) sprites[sprite_loop].frame = LAVA2;
                 else if (sprites[sprite_loop].timer % 45 == 30) sprites[sprite_loop].frame = LAVA3;
                 sprites[sprite_loop].timer++;
                 for (int xyz = 0; sprites[sprite_loop].width - xyz > 0; xyz += 60) {
                     if (sprites[sprite_loop].width - xyz < 60) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx + xyz, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].width - xyz, 10);
                     else masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx + xyz, (int)sprites[sprite_loop].y_position + screeny, 60, 10);
                 }                 
            }
            else if (sprites[sprite_loop].type == 53) {
                masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 20, 28);         
                for (int xyz = 0; xyz < sprites[sprite_loop].width - 40; xyz += 20) {
                    masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 20, 0, (int)sprites[sprite_loop].x_position + screenx + 20 + xyz, (int)sprites[sprite_loop].y_position + screeny, 20, 28);
                }        
                masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 40, 0, (int)sprites[sprite_loop].x_position + screenx + sprites[sprite_loop].width - 20, (int)sprites[sprite_loop].y_position + screeny, 20, 28);
            }
            else if (sprites[sprite_loop].type == 45) {
                if (sprites[sprite_loop].action_state != 2) {
                    if (sprites[sprite_loop].timer % 4 == 0) sprites[sprite_loop].frame = EWUL_SQUID01;
                    else if (sprites[sprite_loop].timer % 4 == 1) sprites[sprite_loop].frame = EWUL_SQUID02;
                    else if (sprites[sprite_loop].timer % 4 == 2) sprites[sprite_loop].frame = EWUL_SQUID03;
                    else if (sprites[sprite_loop].timer % 4 == 3) sprites[sprite_loop].frame = EWUL_SQUID04;
                }
                if (sprites[sprite_loop].action_state == 1) {
                    if (sprites[sprite_loop].y_position + 59 > sprites[sprite_loop].biba)
                        { masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 25, sprites[sprite_loop].biba - (int)sprites[sprite_loop].y_position); }
                    else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
                else if (sprites[sprite_loop].action_state == 3) {
                    if (sprites[sprite_loop].y_position + 59 > sprites[sprite_loop].biba) {
                        BITMAP* temp = create_bitmap(25, 59);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_v_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 25, sprites[sprite_loop].biba - (int)sprites[sprite_loop].y_position);
                        destroy_bitmap(temp);
                    }
                    else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
                else if (sprites[sprite_loop].action_state == 2) {
                    if (sprites[sprite_loop].timer <= 2) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    else draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }
            }
            else if (sprites[sprite_loop].type == 56) {
                if (sprites[sprite_loop].action_state == 0) {
                    set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
			        if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			        else {
                        BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			            draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        destroy_bitmap(temp);
                    }
               }
               else {
                   if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			       else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
            }
            else if (sprites[sprite_loop].type == 79) {
                if (sprites[sprite_loop].action_state == 0) {
                    set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
			        if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			        else {
                        BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			            draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        destroy_bitmap(temp);
                    }
               }
               else {
                   if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			       else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
            }
            else if (sprites[sprite_loop].type == 59) {
               draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               if (player.x_position + 20 > sprites[sprite_loop].x_position) {
                   if (player.x_position + 20 > sprites[sprite_loop].x_position + 100) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame + 1].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                   else masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame + 1].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, (int)player.x_position + 20 - (int)sprites[sprite_loop].x_position, 100);
               }    
            }
            else if (sprites[sprite_loop].type == 60) {
               if (sprites[sprite_loop].action_state == 4) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               else if (sprites[sprite_loop].action_state == 1) {
                   draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);                       
                   if (sprites[sprite_loop].animation_state < 24) sprites[sprite_loop].animation_state++;
                   if (sprites[sprite_loop].animation_state <= 6) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES1].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
                   else if (sprites[sprite_loop].animation_state <= 12) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES2].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
                   else if (sprites[sprite_loop].animation_state <= 18) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES3].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
                   else if (sprites[sprite_loop].animation_state > 18) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES4].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
               }
               else if (sprites[sprite_loop].action_state == 2) {
                   draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);    
                   sprites[sprite_loop].animation_state--;
                   if (sprites[sprite_loop].animation_state == 0) sprites[sprite_loop].action_state = 0;
                   else if (sprites[sprite_loop].animation_state <= 6) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES1].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
                   else if (sprites[sprite_loop].animation_state <= 12) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES2].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
                   else if (sprites[sprite_loop].animation_state <= 18) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES3].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
                   else if (sprites[sprite_loop].animation_state <= 24) draw_sprite(buffer, (BITMAP*)mydatafile[ARMOREYES4].dat, (int)sprites[sprite_loop].x_position + screenx + 26, (int)sprites[sprite_loop].y_position + screeny + 17);
               }
               else if (sprites[sprite_loop].action_state == 3) {
                   sprites[sprite_loop].animation_state++;
                   if (sprites[sprite_loop].animation_state == 9) sprites[sprite_loop].animation_state = 1;
                   if (sprites[sprite_loop].animation_state <= 4) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame + 1].dat, (int)sprites[sprite_loop].x_position + screenx - 7, (int)sprites[sprite_loop].y_position + screeny);
                   else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
               else if (sprites[sprite_loop].action_state == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 1007) {
                if ((sprites[sprite_loop].frame == ICYSHADOW01 || sprites[sprite_loop].frame == ICYSHADOW02 || sprites[sprite_loop].frame == ICYSHADOW03 || sprites[sprite_loop].frame == ICYSHADOW04) && sprites[sprite_loop].action_state != 3 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 5) {
                    set_trans_blender(0, 0, 0, 50);
			        if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			        else {
                        BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			            draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        destroy_bitmap(temp);
                    }
                    if ((sprites[sprite_loop].action_state == 1 || sprites[sprite_loop].action_state == 6|| sprites[sprite_loop].action_state == 10 || sprites[sprite_loop].action_state == 14) && sprites[sprite_loop].y_position < 1100) {
                        BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[ICYUP01].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYUP01].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 65, 1100 - (int)sprites[sprite_loop].y_position);
                        destroy_bitmap(temp);
                    }
                    if ((sprites[sprite_loop].action_state == 7|| sprites[sprite_loop].action_state == 11 || sprites[sprite_loop].action_state == 15) && sprites[sprite_loop].y_position < 1100) {
                        masked_blit((BITMAP*)mydatafile[ICYUP01].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 65, 1100 - (int)sprites[sprite_loop].y_position);
                    }
                    if ((sprites[sprite_loop].action_state == 2 || sprites[sprite_loop].action_state == 8 || sprites[sprite_loop].action_state == 12 || sprites[sprite_loop].action_state == 16) && sprites[sprite_loop].y_position < 820) {
                        BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[ICYUP01].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYUP01].dat, 0, 0);
                        masked_blit(temp, buffer, 0, 820 - (int)sprites[sprite_loop].y_position, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 820 - (int)sprites[sprite_loop].y_position, 65, 154 - (820 - (int)sprites[sprite_loop].y_position));
                        destroy_bitmap(temp);
                    }
                    if ((sprites[sprite_loop].action_state == 9 || sprites[sprite_loop].action_state == 13 || sprites[sprite_loop].action_state == 17) && sprites[sprite_loop].y_position < 820) {
                        masked_blit((BITMAP*)mydatafile[ICYUP01].dat, buffer, 0, 820 - (int)sprites[sprite_loop].y_position, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 820 - (int)sprites[sprite_loop].y_position, 65, 154 - (820 - (int)sprites[sprite_loop].y_position));
                    }
               }
               else if (sprites[sprite_loop].action_state == 3) {
                   set_trans_blender(0, 0, 0, 50);
                   draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny); 
                   if (sprites[sprite_loop].x_position > 3726 && sprites[sprite_loop].x_position < 3880) {
                       masked_blit((BITMAP*)mydatafile[ICYSIDE01].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 3880 - (int)sprites[sprite_loop].x_position, 1100 - (int)sprites[sprite_loop].y_position);
                   }
                   else if (sprites[sprite_loop].y_position < 1100 && sprites[sprite_loop].x_position < 3880) {
                       masked_blit((BITMAP*)mydatafile[ICYSIDE01].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 154, 1100 - (int)sprites[sprite_loop].y_position);
                   }
               }
               else if (sprites[sprite_loop].action_state == 4) {
                    set_trans_blender(0, 0, 0, 50);
                    if (sprites[sprite_loop].frame == ICYSHADOW02) {
                        set_trans_blender(0, 0, 0, 50);
			            if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			            else {
                            BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			                draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                            destroy_bitmap(temp);
                        }
                        if (sprites[sprite_loop].x_position > 3226) {
                            masked_blit((BITMAP*)mydatafile[ICYSIDE01].dat, buffer, 3380 - (int)sprites[sprite_loop].x_position, 0, (int)sprites[sprite_loop].x_position + screenx + 3380 - (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position + screeny, 154 - 3380 + (int)sprites[sprite_loop].x_position, 65);
                        }
                   }
                   else if (sprites[sprite_loop].frame == ICYSIDE02 && sprites[sprite_loop].x_position < 3380) {
                        BITMAP* temp = create_bitmap(154, 65);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        masked_blit((BITMAP*)mydatafile[ICYSHADOW02].dat, temp, 0, 0, 0, 0, 3380 - (int)sprites[sprite_loop].x_position, 65);
                        draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        destroy_bitmap(temp);
                        masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 3380 - (int)sprites[sprite_loop].x_position, 0, (int)sprites[sprite_loop].x_position + screenx + 3380 - (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position + screeny, (int)sprites[sprite_loop].x_position - 3240, 106);
                   }
                   else if (sprites[sprite_loop].frame == ICYSIDE03) {
                        if (sprites[sprite_loop].x_position < 3380) {
                            BITMAP* temp = create_bitmap(154, 65);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            masked_blit((BITMAP*)mydatafile[ICYSHADOW02].dat, temp, 0, 0, 0, 0, 3380 - (int)sprites[sprite_loop].x_position, 65);
                            draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                            destroy_bitmap(temp);
                            masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 3380 - (int)sprites[sprite_loop].x_position, 0, (int)sprites[sprite_loop].x_position + screenx + 3380 - (int)sprites[sprite_loop].x_position, (int)sprites[sprite_loop].y_position + screeny, (int)sprites[sprite_loop].x_position - 3240, 120);
                        }
                        else draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                   }
                   else if (sprites[sprite_loop].frame == ICYSIDE04) {
                        draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                   }
                   else if (sprites[sprite_loop].frame == ICYUP01) {
                        if (sprites[sprite_loop].y_position > 946) {
                            BITMAP* temp = create_bitmap(65, 154);
                            BITMAP* temp2 = create_bitmap(65, 154);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSHADOW04].dat, 0, 0);
                            draw_sprite_v_flip(temp2, temp, 0, 0);
			                draw_trans_sprite(buffer, temp2, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                            draw_sprite_v_flip(temp2, temp, 0, 0);                            
                            masked_blit(temp2, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 65, 1100 - (int)sprites[sprite_loop].y_position);
                            destroy_bitmap(temp);
                            destroy_bitmap(temp2);                        
                        }
                        else {
                            BITMAP* temp = create_bitmap(65, 154);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                            draw_sprite_v_flip(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                            destroy_bitmap(temp);
                        }
                   }
               }
               else if (sprites[sprite_loop].action_state == 5) {
                    set_trans_blender(0, 0, 0, 50);
                    if (sprites[sprite_loop].frame == ICYSHADOW02) {
                        set_trans_blender(0, 0, 0, 50);
			            if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			            else {
                            BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			                draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                            destroy_bitmap(temp);
                        }
                        if (sprites[sprite_loop].x_position < 3880) {
                            BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSIDE01].dat, 0, 0);
			                masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 3880 - (int)sprites[sprite_loop].x_position, 65);
                            destroy_bitmap(temp);
                        }
                   }
                   else if (sprites[sprite_loop].frame == ICYSIDE02 && sprites[sprite_loop].x_position > 3726) {
                        BITMAP* temp = create_bitmap(154, 65);
                        BITMAP* temp2 = create_bitmap(154, 65);
                        clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSHADOW02].dat, -14, 0);
                        masked_blit(temp, temp2, 3880 - (int)sprites[sprite_loop].x_position, 0, 3880 - (int)sprites[sprite_loop].x_position, 0, 154 - (3880 - (int)sprites[sprite_loop].x_position), 65);
                        draw_trans_sprite(buffer, temp2, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        destroy_bitmap(temp2);
                        destroy_bitmap(temp);
                        BITMAP* temp3 = create_bitmap(140, 106);
                        clear_to_color(temp3, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                        draw_sprite_h_flip(temp3, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                        masked_blit(temp3, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 3880 - (int)sprites[sprite_loop].x_position, 106);
                        destroy_bitmap(temp3);
                   }
                   else if (sprites[sprite_loop].frame == ICYSIDE03) {
                        if (sprites[sprite_loop].x_position > 3726) {
                            BITMAP* temp = create_bitmap(154, 65);
                            BITMAP* temp2 = create_bitmap(154, 65);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            clear_to_color(temp2, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp, (BITMAP*)mydatafile[ICYSHADOW02].dat, -15, 0);
                            masked_blit(temp, temp2, 3880 - (int)sprites[sprite_loop].x_position, 0, 3880 - (int)sprites[sprite_loop].x_position, 0, 154 - (3880 - (int)sprites[sprite_loop].x_position), 65);
                            draw_trans_sprite(buffer, temp2, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny - 6);
                            destroy_bitmap(temp2);
                            destroy_bitmap(temp);
                            BITMAP* temp3 = create_bitmap(138, 120);
                            clear_to_color(temp3, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_h_flip(temp3, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                            masked_blit(temp3, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 3880 - (int)sprites[sprite_loop].x_position, 120);
                            destroy_bitmap(temp3);
                        }
                        else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                   }
                   else if (sprites[sprite_loop].frame == ICYSIDE04) {
                        draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                   }
                   else if (sprites[sprite_loop].frame == ICYUP01) {
                        if (sprites[sprite_loop].y_position > 946) {
                            BITMAP* temp = create_bitmap(65, 154);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_v_flip(temp, (BITMAP*)mydatafile[ICYSHADOW04].dat, 0, 0);
			                draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                            draw_sprite_v_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);                        
                            masked_blit(temp, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 65, 1100 - (int)sprites[sprite_loop].y_position);
                            destroy_bitmap(temp);                      
                        }
                        else {
                            draw_sprite_v_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                        }
                   }
               }
               else {
                    if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			        else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
            }
            else if (sprites[sprite_loop].type == 1008) {
              if (player.x_position + 20 < sprites[sprite_loop].x_position + 35 && sprites[sprite_loop].direction == 0) sprites[sprite_loop].direction = 1;
              if (player.x_position + 20 > sprites[sprite_loop].x_position + 35 && sprites[sprite_loop].direction == 1) sprites[sprite_loop].direction = 0;
              if (sprites[sprite_loop].direction == 0) {
                if (sprites[sprite_loop].action_state <= 1) {
                    set_trans_blender(0, 0, 0, 0);
                    draw_lit_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].biba);
                }
                else {
                    set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
                    draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                }  
              }
              else {
                BITMAP* temp = create_bitmap(80, 109);
                clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
                if (sprites[sprite_loop].action_state <= 1) {
                    set_trans_blender(0, 0, 0, 0);
                    draw_lit_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx - 10, (int)sprites[sprite_loop].y_position + screeny, sprites[sprite_loop].biba);
                }
                else {
                    set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
                    draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx - 10, (int)sprites[sprite_loop].y_position + screeny);
                }
                destroy_bitmap(temp);   
              }
            }
            else if (sprites[sprite_loop].type == 100) continue;
            else if (sprites[sprite_loop].type == 404) continue;
            else if (sprites[sprite_loop].type == 35) continue;
            else if (sprites[sprite_loop].type == 36) continue;
            else if (sprites[sprite_loop].type == 46) continue;
            else if (sprites[sprite_loop].type == 47) continue;
            else if (sprites[sprite_loop].type == 66) continue;
            else if (sprites[sprite_loop].type == 1) continue;
            else if (sprites[sprite_loop].type == 2) continue;
            else if (sprites[sprite_loop].type == 3) continue;
            else if (sprites[sprite_loop].type == 4) continue;
            else if (sprites[sprite_loop].type == 5) continue;
            else if (sprites[sprite_loop].type == 6) continue;
            else if (sprites[sprite_loop].type == 7) continue;
            else if (sprites[sprite_loop].type == 70) continue;
            else if (sprites[sprite_loop].type == 75) continue;
            else if (sprites[sprite_loop].type == 77) continue;
            else if (sprites[sprite_loop].type == 78) continue;
            else if (sprites[sprite_loop].type == 305) continue;
            else if (sprites[sprite_loop].type == 100) continue;
            else if (sprites[sprite_loop].type == 101) continue;
            else if (sprites[sprite_loop].type == 102) continue;
            else if (sprites[sprite_loop].type == 104) continue;
            else if (sprites[sprite_loop].type == 57) continue;
            else if (sprites[sprite_loop].type == 58) continue;
            else if (sprites[sprite_loop].type == 1666) continue;
            else if (sprites[sprite_loop].type == 2004) continue;
            //else if (sprites[sprite_loop].type == 1005) continue;
            else if (sprites[sprite_loop].rotate_factor == 0) {
			    if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			}
		    else rotate_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, itofix(sprites[sprite_loop].rotate_factor));
		}
	}
	
    player.x_position = (int)player.x_position;
    if (starting > 0) {
        if (starting > 15 && starting < 24 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
        else if (starting > 23 && starting < 31 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
        else if (starting > 30 && starting < 39 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
        else if (starting > 38 && starting < 47 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
        else if (starting > 46 && starting < 87) {
            if (starting > 46 && starting < 53) player.frame = PLAYER_MOVING02;
            else if (starting > 52 && starting < 59) player.frame = PLAYER_MOVING03;
            else if (starting > 58 && starting < 65) player.frame = PLAYER_MOVING02;
            else if (starting > 64 && starting < 71) player.frame = PLAYER_MOVING01;
            else if (starting > 70 && starting < 77) player.frame = PLAYER_MOVING04;
            else if (starting > 76 && starting < 83) player.frame = PLAYER_MOVING05;
            else if (starting > 82 && starting < 89) player.frame = PLAYER_MOVING04;           
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            masked_blit((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, buffer, 40 - (starting - 46), 0, (int)player.x_position + screenx, (int)player.y_position + screeny, (starting - 46) * 2, 80);
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (starting > 86 && starting < 95) {
            player.frame = PLAYER_MOVING01;
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 94 && starting < 103) {
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 102 && starting < 111) {
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 110 && starting < 119) {
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        else if (starting > 118 && starting < 130) {
            if (Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
            draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
        }
        if (starting > 5 && starting < 128 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[READY].dat, 240, 200);
        starting++;
        if (starting == 130) {
            input_locked = 0;
            stopall = 0;
            starting = 0;
            if (lastagedoor == 1) { input_locked = 1; call_event = 14; }
            else if (lastagedoor == 2) { input_locked = 1; call_event = 15; }
            else if (lastagedoor == 3) { input_locked = 1; call_event = 16; }
            else if (lastagedoor == 4) { input_locked = 1; call_event = 17; }
            else if (lastagedoor == 5) { input_locked = 1; call_event = 18; }
            else if (lastagedoor == 6) { input_locked = 1; call_event = 19; }
            else if (lastagedoor == 7) { input_locked = 1; call_event = 20; lastageblack = 255; }
        }
    }
    else if (starting2 > 0) {
        if (starting2 > 15 && starting2 < 24 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
        else if (starting2 > 23 && starting2 < 31 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
        else if (starting2 > 30 && starting2 < 39 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
        else if (starting2 > 38 && starting2 < 47 && Map.number == 1) draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
        else if (starting2 > 46 && starting2 < 87) {
            if (starting2 > 46 && starting2 < 53) player.frame = PLAYER_MOVING02;
            else if (starting2 > 52 && starting2 < 59) player.frame = PLAYER_MOVING03;
            else if (starting2 > 58 && starting2 < 65) player.frame = PLAYER_MOVING02;
            else if (starting2 > 64 && starting2 < 71) player.frame = PLAYER_MOVING01;
            else if (starting2 > 70 && starting2 < 77) player.frame = PLAYER_MOVING04;
            else if (starting2 > 76 && starting2 < 83) player.frame = PLAYER_MOVING05;
            else if (starting2 > 82 && starting2 < 89) player.frame = PLAYER_MOVING04;           
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            BITMAP* temp = create_bitmap(54, 80);
            clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat));
            masked_blit((BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, temp, 40 - (starting2 - 46), 0, 0, 0, (starting2 - 46) * 2, 80);
            draw_sprite_h_flip(buffer, temp, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
            destroy_bitmap(temp);
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (starting2 > 86 && starting2 < 95) {
            player.frame = PLAYER_MOVING01;
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position - 33 + screenx, (int)player.y_position - 20 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 94 && starting2 < 103) {
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position - 22 + screenx, (int)player.y_position + 3 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 102 && starting2 < 111) {
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position - 16 + screenx, (int)player.y_position + 23 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 110 && starting2 < 119) {
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position - 11 + screenx, (int)player.y_position + 32 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        else if (starting2 > 118 && starting2 < 130) {
            if (Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position - 5 + screenx, (int)player.y_position + 34 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx - 40, (int)player.y_position + screeny);
        }
        //if (starting2 > 5 && starting2 < 128 && Map.number == 1) draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[READY].dat, 240, 200);
        starting2++;
        if (starting2 == 130) {
            player.x_position -= 40;
            input_locked = 0;
            stopall = 0;
            starting2 = 0;
            if (lastagedoor == 1) { input_locked = 1; call_event = 14; }
            else if (lastagedoor == 2) { input_locked = 1; call_event = 15; }
            else if (lastagedoor == 3) { input_locked = 1; call_event = 16; }
            else if (lastagedoor == 4) { input_locked = 1; call_event = 17; }
            else if (lastagedoor == 5) { input_locked = 1; call_event = 18; }
            else if (lastagedoor == 6) { input_locked = 1; call_event = 19; }
        }
    }
    else if (finishing > 0) {
        if (finishing > 0 && finishing < 16) { draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny); rest(50); }
        else if (finishing > 15 && finishing < 24) { draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position + 45 + screenx, (int)player.y_position + 34 + screeny); draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny); }
        else if (finishing > 23 && finishing < 31) { draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position + 39 + screenx, (int)player.y_position + 32 + screeny); draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny); }
        else if (finishing > 30 && finishing < 39) { draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position + 34 + screenx, (int)player.y_position + 23 + screeny); draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny); }
        else if (finishing > 38 && finishing < 47) { draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position + 28 + screenx, (int)player.y_position + 3 + screeny); draw_sprite(buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny); }
        else if (finishing > 46 && finishing < 87) {
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
        else if (finishing > 86 && finishing < 95) {
            player.frame = NULO;
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL1].dat, (int)player.x_position + 17 + screenx, (int)player.y_position - 20 + screeny);
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)player.x_position + 17 + screenx, (int)player.y_position - 20 + screeny);
        }
        else if (finishing > 94 && finishing < 103) {
            draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL6].dat, (int)player.x_position + 28 + screenx, (int)player.y_position + 3 + screeny);
        }
        else if (finishing > 102 && finishing < 111) {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL5].dat, (int)player.x_position + 34 + screenx, (int)player.y_position + 23 + screeny);
        }
        else if (finishing > 110 && finishing < 119) {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL4].dat, (int)player.x_position + 39 + screenx, (int)player.y_position + 32 + screeny);
        }
        else if (finishing > 118 && finishing < 130) {
            draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL3].dat, (int)player.x_position + 45 + screenx, (int)player.y_position + 34 + screeny);
        }
        finishing++;
        if (finishing >= 131) {
            if (osutatakaefadeout < 255) osutatakaefadeout += 15;
            else {
                if (lastageboss == 0) {
                    characterscreen = 1;
                    speed_counter = 1;
                    finishing = 0;
                    current_level = 0;
                    menu = 0;
                    player.x_position = 0;
                    player.y_position = 0;
                    player.imune = 0;
                    return;
                }
                else {
                    current_level = 73;
                    if (lastageportal[0] == 1 && lastageportal[1] == 1 && lastageportal[2] == 1 && lastageportal[3] == 1 && lastageportal[4] == 1 && lastageportal[5] == 1) { current_level = 80; lastagedoor = 7; lastageblack = 255; }
                    stopall = 1; input_locked = 1; screen_locked = 1;
                    next_level = 0; paulaumfromhell = 1; setup_game(); 
                    while(osutatakaefadeout > 0) {
                        draw();
                        osutatakaefadeout -= 15;
                    }
                    finishing = 0;
                }
            }
        }
    }
    else if (player.shine > 0) {
        if (player.shine == 1) {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 60);
            rest(50);
        }
        else if (player.shine == 2) {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 120);
            rest(50);
        }
        else if (player.shine == 3) {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 180);
            rest(50);
        }
        else if (player.shine == 4) {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 120);
            rest(50);
        }
        else if (player.shine == 5) {
            player.shine++;
            set_trans_blender(255,255,255,0);
            draw_lit_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny, 60);
            rest(50);
            player.shine = 0;
            finishing = 1;
        }
    }
    else {
        if (player.frame != PLAYERD && player.frame != NULO) {
          if (player.direction == 0) {
            draw_sprite( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
          }
          else {
            draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame + (player.current_weapon - 1)].dat, (int)player.x_position - 10 + screenx, (int)player.y_position + screeny);
          }
        }
        else {
          if (player.direction == 0) {
            draw_sprite( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position + screenx, (int)player.y_position + screeny);
          }
          else {
            draw_sprite_h_flip( buffer, (BITMAP*)mydatafile[player.frame].dat, (int)player.x_position - 10 + screenx, (int)player.y_position + screeny);
          }        
        }
    }
	    
    if (Map.type == 2 || Map.type == 3)
    masked_blit( foreground, buffer, screenx * -1, screeny * -1, 0, 0, 640, 480);
    
    for (int sprite_loop = 0; sprite_loop < number_of_sprites + 1; sprite_loop++) {
	    if (sprites[sprite_loop].active == 1) {
            if (sprites[sprite_loop].type == 403) {
                 set_trans_blender(0,0,0,100);
                 draw_trans_sprite(buffer, (BITMAP*)mydatafile[LUZ].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 100) {
                 draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 66) {
               if (sprites[sprite_loop].action_state == 0) {
                   draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
               }
               else {
                   if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny - 24);
                   else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 24, (int)sprites[sprite_loop].y_position + screeny - 24);
               }
            }
            else if (sprites[sprite_loop].type == 73) {
                draw_sprite(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 74) {
                draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[PORTAL2].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 2004) {
                draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 1) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 2) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 3) {
                draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 305) {
                if (sprites[sprite_loop].timer % 2 == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 4) {
                if (sprites[sprite_loop].frame == ZOCK01) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].frame == ZOCK02) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].frame == ZOCK03) sprites[sprite_loop].frame++;
                else if (sprites[sprite_loop].frame == ZOCK04) sprites[sprite_loop].frame = ZOCK01;
                draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 5, (int)sprites[sprite_loop].y_position + screeny - 8);
            }
            else if (sprites[sprite_loop].type == 5) {
                sprites[sprite_loop].animation_state++;
                if (sprites[sprite_loop].animation_state <= 3) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].animation_state <= 6) stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 32, 29);
                else if (sprites[sprite_loop].animation_state <= 9) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 3, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].animation_state <= 12) stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 3, (int)sprites[sprite_loop].y_position + screeny, 29, 32);
                else if (sprites[sprite_loop].animation_state <= 15) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 3, (int)sprites[sprite_loop].y_position + screeny + 3);
                else if (sprites[sprite_loop].animation_state <= 18) stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 3, (int)sprites[sprite_loop].y_position + screeny + 3, 32, 29);
                else if (sprites[sprite_loop].animation_state <= 21) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 3);
                else if (sprites[sprite_loop].animation_state <= 24) { stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny - 3, 29, 32); sprites[sprite_loop].animation_state = 0; }
            }
            else if (sprites[sprite_loop].type == 57 || sprites[sprite_loop].type == 58) {
                sprites[sprite_loop].animation_state++;
                if (sprites[sprite_loop].animation_state <= 3) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].animation_state <= 6) stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 16, 14);
                else if (sprites[sprite_loop].animation_state <= 9) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 2, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].animation_state <= 12) stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 2, (int)sprites[sprite_loop].y_position + screeny, 14, 16);
                else if (sprites[sprite_loop].animation_state <= 15) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx + 2, (int)sprites[sprite_loop].y_position + screeny + 2);
                else if (sprites[sprite_loop].animation_state <= 18) stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx - 2, (int)sprites[sprite_loop].y_position + screeny + 2, 16, 14);
                else if (sprites[sprite_loop].animation_state <= 21) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 2);
                else if (sprites[sprite_loop].animation_state <= 24) { stretch_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny - 2, 14, 16); sprites[sprite_loop].animation_state = 0; }
            }
            else if (sprites[sprite_loop].type == 6) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 7) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 70) {
                if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 75) {
                sprites[sprite_loop].animation_state++;
                if (sprites[sprite_loop].animation_state == 6) {
                    sprites[sprite_loop].frame++;
                    if (sprites[sprite_loop].frame == LASTSMALL4 + 1) sprites[sprite_loop].frame = LASTSMALL1;
                    if (sprites[sprite_loop].frame == LASTBALL4 + 1) sprites[sprite_loop].frame = LASTBALL1;
                    sprites[sprite_loop].animation_state = 0;
                }
                set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 77) {
                sprites[sprite_loop].animation_state++;
                if (sprites[sprite_loop].animation_state == 8) {
                    sprites[sprite_loop].frame++;
                    if (sprites[sprite_loop].frame == FIRE4 + 1) sprites[sprite_loop].frame = FIRE1;
                    sprites[sprite_loop].animation_state = 0;
                }
                set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 78) {
                sprites[sprite_loop].animation_state++;
                if (sprites[sprite_loop].animation_state == 12) {
                    sprites[sprite_loop].frame++;
                    if (sprites[sprite_loop].frame == FIRE4 + 1) sprites[sprite_loop].frame = FIRE1;
                    sprites[sprite_loop].animation_state = 0;
                }
                set_trans_blender(0, 0, 0, sprites[sprite_loop].biba);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 101) {
                set_trans_blender(0, 0, 0, sprites[sprite_loop].strength);
			    if (sprites[sprite_loop].direction == 0) draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else {
                    BITMAP* temp = create_bitmap(sprites[sprite_loop].width, sprites[sprite_loop].height);
                    clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat));
                    draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, 0, 0);
			        draw_trans_sprite(buffer, temp, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                    destroy_bitmap(temp);
                }
            }
            else if (sprites[sprite_loop].type == 102) {
                set_trans_blender(0, 0, 0, sprites[sprite_loop].strength);
                draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 104) {
                if (sprites[sprite_loop].frame == WATERSHOTHIT4) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                else if (sprites[sprite_loop].direction == 0) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
			    else draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 1666) {
                 set_trans_blender(0,0,0,sprites[sprite_loop].strength);
                 draw_trans_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 404) {
                 draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
            }
            else if (sprites[sprite_loop].type == 44) {
                 for (int xyz = 0; sprites[sprite_loop].width - xyz > 0; xyz += 60) {
                     if (sprites[sprite_loop].width - xyz < 60) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 10, (int)sprites[sprite_loop].x_position + screenx + xyz, (int)sprites[sprite_loop].y_position + screeny + 10, sprites[sprite_loop].width - xyz, 10);
                     else masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 10, (int)sprites[sprite_loop].x_position + screenx + xyz, (int)sprites[sprite_loop].y_position + screeny + 10, 60, 10);
                 }                 
            }
            else if (sprites[sprite_loop].type == 28) {
                 if (sprites[sprite_loop].animation_state == 1) {
                     sprites[sprite_loop].height += 10;
                     if (sprites[sprite_loop].height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                     if (sprites[sprite_loop].height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128);
                     if (sprites[sprite_loop].height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256);
                     if (sprites[sprite_loop].height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384);
                     if (sprites[sprite_loop].height % 128 != 0) {
                         sprites[sprite_loop].action_state = (int)(sprites[sprite_loop].height / 128);
                         if (sprites[sprite_loop].action_state == 0) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 2) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 3) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384, 34, (sprites[sprite_loop].height % 128));
                     }
                     sprites[sprite_loop].height -= 10;
                 }
                 else {
                     if (sprites[sprite_loop].height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                     if (sprites[sprite_loop].height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128);
                     if (sprites[sprite_loop].height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256);
                     if (sprites[sprite_loop].height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384);
                     if (sprites[sprite_loop].height % 128 != 0) {
                         sprites[sprite_loop].action_state = (int)(sprites[sprite_loop].height / 128);
                         if (sprites[sprite_loop].action_state == 0) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 2) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 3) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384, 34, (sprites[sprite_loop].height % 128));
                     }
                 }
            }
            else if (sprites[sprite_loop].type == 76) {
                 if (sprites[sprite_loop].animation_state == 1) {
                     sprites[sprite_loop].height += 10;
                     if (sprites[sprite_loop].height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                     if (sprites[sprite_loop].height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128);
                     if (sprites[sprite_loop].height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256);
                     if (sprites[sprite_loop].height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384);
                     if (sprites[sprite_loop].height % 128 != 0) {
                         sprites[sprite_loop].action_state = (int)(sprites[sprite_loop].height / 128);
                         if (sprites[sprite_loop].action_state == 0) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 2) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 3) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384, 34, (sprites[sprite_loop].height % 128));
                     }
                     sprites[sprite_loop].height -= 10;
                 }
                 else {
                     if (sprites[sprite_loop].height >= 128) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny);
                     if (sprites[sprite_loop].height >= 256) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128);
                     if (sprites[sprite_loop].height >= 384) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256);
                     if (sprites[sprite_loop].height == 512) draw_sprite(buffer, (BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384);
                     if (sprites[sprite_loop].height % 128 != 0) {
                         sprites[sprite_loop].action_state = (int)(sprites[sprite_loop].height / 128);
                         if (sprites[sprite_loop].action_state == 0) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 1) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 128, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 2) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 256, 34, (sprites[sprite_loop].height % 128));
                         else if (sprites[sprite_loop].action_state == 3) masked_blit((BITMAP*)mydatafile[sprites[sprite_loop].frame].dat, buffer, 0, 0, (int)sprites[sprite_loop].x_position + screenx, (int)sprites[sprite_loop].y_position + screeny + 384, 34, (sprites[sprite_loop].height % 128));
                     }
                 }
            }
            else if (sprites[sprite_loop].type == 1111) {
                 if (sprites[sprite_loop].timer % 7 == 0) {
                     sprites[sprite_loop].direction = rand() % 12;
                     if (sprites[sprite_loop].direction == 0) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position + (rand() % 100) + 150;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 100) + 150;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position + (rand() % 30) + 45;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 30) + 45;
                         sprites[sprite_loop].biba = 3 + (rand() % 3);
                         sprites[sprite_loop].strength = 3 + (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 1) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position + (rand() % 100) + 150;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 100) + 150;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 30) - 45;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position - (rand() % 30) - 45;
                         sprites[sprite_loop].biba = 3 + (rand() % 3);
                         sprites[sprite_loop].strength = -3 - (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 2) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 100) - 150;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position - (rand() % 100) - 150;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position + (rand() % 30) + 45;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 30) + 45;
                         sprites[sprite_loop].biba = -3 - (rand() % 3);
                         sprites[sprite_loop].strength = 3 + (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 3) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 100) - 150;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position - (rand() % 100) - 150;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 30) - 45;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position - (rand() % 30) - 45;
                         sprites[sprite_loop].biba = -3 - (rand() % 3);
                         sprites[sprite_loop].strength = -3 - (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 4) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position + (rand() % 30) + 45;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 30) + 45;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position + (rand() % 100) + 150;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 100) + 150;
                         sprites[sprite_loop].biba = 3 + (rand() % 3);
                         sprites[sprite_loop].strength = 3 + (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 5) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position + (rand() % 30) + 45;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 30) + 45;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 100) - 150;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position - (rand() % 100) - 150;
                         sprites[sprite_loop].biba = 3 + (rand() % 3);
                         sprites[sprite_loop].strength = -3 - (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 6) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 30) - 45;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position - (rand() % 30) - 45;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position + (rand() % 100) + 150;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 100) + 150;
                         sprites[sprite_loop].biba = -3 - (rand() % 3);
                         sprites[sprite_loop].strength = 3 + (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 7) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 30) - 45;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position - (rand() % 30) - 45;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 100) - 150;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position - (rand() % 100) - 150;
                         sprites[sprite_loop].biba = -3 - (rand() % 3);
                         sprites[sprite_loop].strength = -3 - (rand() % 3);
                     }
                     else if (sprites[sprite_loop].direction == 8) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position + (rand() % 100) + 150;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 100) + 150;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 15) - 5;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 15) + 5;
                         sprites[sprite_loop].biba = 5 + (rand() % 2);
                         sprites[sprite_loop].strength = 0;
                     }
                     else if (sprites[sprite_loop].direction == 9) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 100) - 150;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position - (rand() % 100) - 150;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 15) - 5;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 15) + 5;
                         sprites[sprite_loop].biba = -5 - (rand() % 2);
                         sprites[sprite_loop].strength = 0;
                     }
                     else if (sprites[sprite_loop].direction == 10) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 15) - 5;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 15) + 5;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position + (rand() % 100) + 150;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position + (rand() % 100) + 150;
                         sprites[sprite_loop].biba = 0;
                         sprites[sprite_loop].strength = 5 + (rand() % 2);
                     }
                     else if (sprites[sprite_loop].direction == 11) {
                         sprites[sprite_loop].width = (int)sprites[sprite_loop].x_position - (rand() % 15) - 5;
                         sprites[sprite_loop].height = (int)sprites[sprite_loop].x_position + (rand() % 15) + 5;
                         sprites[sprite_loop].x_speed = sprites[sprite_loop].y_position - (rand() % 100) - 150;
                         sprites[sprite_loop].y_speed = sprites[sprite_loop].y_position - (rand() % 100) - 150;
                         sprites[sprite_loop].biba = 0;
                         sprites[sprite_loop].strength = -5 - (rand() % 2);
                     }
                 }
                 triangle(buffer, (int)sprites[sprite_loop].x_position + (int)sprites[sprite_loop].biba + screenx, (int)sprites[sprite_loop].y_position + (int)sprites[sprite_loop].strength + screeny,
                                  (int)sprites[sprite_loop].width + screenx, (int)sprites[sprite_loop].x_speed + screeny,
                                  (int)sprites[sprite_loop].height + screenx, (int)sprites[sprite_loop].y_speed + screeny, makecol(255,255,20));
                 if (bosslife == -1) sprites[sprite_loop].active = 0;
                 sprites[sprite_loop].timer++;
            }
        }
	}

    if (dieanimation == 1) {
        if (player.timer > -1000) player.timer = -1000;
        else player.timer--;
        if ((int)player.timer % 20 == 0) play_sample((SAMPLE *)mydatafile[DIE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
        if (bframe == PDIE5) bframe = PDIE1;
        else if ((int)player.timer % 5 == 0) bframe++;
        if (player.timer > -1100) {
            bolas[0][0] += 2.5; bolas[0][1] -= 3.5;
            bolas[1][0] += 3.5; bolas[1][1] -= 2.5;
            bolas[2][0] += 4;
            bolas[3][0] += 3.5; bolas[3][1] += 2.5;
            bolas[4][0] += 2.5; bolas[4][1] += 3.5;
            bolas[5][1] += 4;
            bolas[6][0] -= 2.5; bolas[6][1] += 3.5;
            bolas[7][0] -= 3.5; bolas[7][1] += 2.5;
            bolas[8][0] -= 4;
            bolas[9][0] -= 3.5; bolas[9][1] -= 2.5;
            bolas[10][0] -= 2.5; bolas[10][1] -= 3.5;
            bolas[11][1] -= 4;
        }
        else { 
            player.vidas--;
            if (player.vidas < 0) {
                characterscreen = 1;
                player.vidas = 5;
                return;    
            } 
            else { dead = 1; initiate_level(current_level); light_level = 0; return; }
        }
        for (int i = 0; i <= 11; i++)
            draw_sprite(buffer, (BITMAP*)mydatafile[bframe].dat, (int)(bolas[i][0] + screenx), (int)(bolas[i][1] + screeny));
    }
	
	if (Map.water_position > 0) {
      if (current_level == 40) {
        set_trans_blender(0, 0, 0, 128);
        int y_adjuster = screeny;
        int x_adjuster = screenx;
        while (y_adjuster < -19) y_adjuster += 20;
        while (x_adjuster < -19) x_adjuster += 20;
        for (int q = 0; q < 33; q++) {
            for (int w = (int)(screeny / 20); w < 4; w++) {
                if (w == (int)(screeny / 20)) {
                    if (aguaa % 60 >= 40) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 20) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 0) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                }
                else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster);
            }
        }
        aguaa++;
      }
      else if (current_level == 41) {
        set_trans_blender(0, 0, 0, 128);
        int y_adjuster = screeny;
        int x_adjuster = screenx;
        while (y_adjuster < -19) y_adjuster += 20;
        while (x_adjuster < -19) x_adjuster += 20;
        for (int q = 0; q < 33; q++) {
            for (int w = (int)(screeny / 20); w < 15; w++) {
                if (w == (int)(screeny / 20)) {
                    if (aguaa % 60 >= 40) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 20) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 0) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                }
                else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster);
            }
        }
        aguaa++;
      }
      else if (current_level == 42) {
        set_trans_blender(0, 0, 0, 128);
        int y_adjuster = screeny;
        int x_adjuster = screenx;
        while (y_adjuster < -19) y_adjuster += 20;
        while (x_adjuster < -19) x_adjuster += 20;
        for (int q = 0; q < 33; q++) {
            for (int w = (int)(screeny / 20); w < 10; w++) {
                if (w == (int)(screeny / 20)) {
                    if (aguaa % 60 >= 40) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 20) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 0) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                }
                else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster);
            }
        }
        aguaa++;
      }
      else if (current_level == 78) {
        set_trans_blender(0, 0, 0, 128);
        int y_adjuster = screeny;
        int x_adjuster = screenx;
        while (y_adjuster < -19) y_adjuster += 20;
        while (x_adjuster < -19) x_adjuster += 20;
        for (int q = 0; q < 33; q++) {
            for (int w = (int)(screeny / 20); w < 10; w++) {
                if (w == (int)(screeny / 20)) {
                    if (aguaa % 60 >= 40) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT1].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 20) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT2].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                    else if (aguaa % 60 >= 0) { draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUAT3].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster); }
                }
                else draw_trans_sprite(buffer, (BITMAP*)mydatafile[AGUA].dat, (q * 20) + x_adjuster, Map.water_position + (w * 20) + y_adjuster);
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
    
    if (sparkmandril > 0) {
        if (sparkmandril < 9) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE1].dat, 0, 185 - (5 * (player.hpmax - 15)));
        if (sparkmandril < 17) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE2].dat, 0, 185 - (5 * (player.hpmax - 15)));
        if (sparkmandril < 25) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE3].dat, 0, 185 - (5 * (player.hpmax - 15)));
        if (sparkmandril < 33) draw_sprite( buffer, (BITMAP*)mydatafile[SPARKLE4].dat, 0, 185 - (5 * (player.hpmax - 15)));
        sparkmandril++;
        if (sparkmandril == 33) sparkmandril = 0;
    }
    
    if (bosslife >= 0) {
        draw_sprite( buffer, (BITMAP*)mydatafile[LIFEMETERBOSS].dat, 610, 100);
        for (int hp = 1; hp != bosslife + 1; hp++)
            draw_sprite( buffer, (BITMAP*)mydatafile[LIFEBAR].dat, 613, 259 - (hp * 5));
    }
    
    /*bibinhalinda = howtoend;
    sprintf(txt,"PX: %f PY: %f XA: %f YA: %f FPS: %d", player.x_position, player.y_position, player.x_speed, player.y_speed, last_fps);
    sprintf(txt2, "PT: %f NS: %d W: %d B: %d B: %d PN: %d SX: %d SY: %d", player.timer, number_of_sprites, w84go, bibinhalinda, bibinhafeia, number_of_walls, screenx, screeny);    
    textout_ex(buffer, font, txt, 5, 5, makecol(255,0,0), 0);
    textout_ex(buffer, font, txt2, 5, 15, makecol(255,0,0), 0);*/
    
    if (bosslife == 0) {
        move_to_end();
        if (light_level < 255) light_level++;
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, light_level);
        if (light_level == 255) {
            rest(500);
            bosslife = -1; bossfight = 0;
            if (lastagedoor == 7) { itsover = 1; }
        }
    }
    else if (light_level > 1) {
        light_level--;
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, light_level);
        if (light_level == 1) {
            if (lastageboss == 1) finishing = 1;
        }
    }
    else if (flash_screen == 1) {
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, 200);
    }
    else if (flash_screen == 2) {
        set_trans_blender(255, 255, 255, 0);
        draw_lit_sprite(screen, buffer, 0, 0, 255);
    }
    else if (osutatakaefadeout > 0) {
        set_trans_blender(0, 0, 0, 0);
        draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
    }
    else draw_sprite(screen, buffer, 0, 0);
    w84go = 0;
}

void draw_menu() {
    draw_sprite( buffer, (BITMAP*)mydatafile[MAINMENU].dat, 0, 0);
    if (player.y_position == 105) {
        draw_sprite( buffer, (BITMAP*)mydatafile[LOAD1].dat, 220, 160);
        draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS1].dat, 220, 255);
        draw_sprite( buffer, (BITMAP*)mydatafile[QUIT1].dat, 220, 350);
        if (player.timer - 50 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME1].dat, 220, 65);
        else if (player.timer - 55 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME2].dat, 220, 65);
        else if (player.timer - 60 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME3].dat, 220, 65);
        else if (player.timer - 65 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME4].dat, 220, 65);
        else if (player.timer - 70 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 65);
        else if (player.timer - 75 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 65);
        else if (player.timer - 80 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK1].dat, 220, 65);
        else if (player.timer - 85 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 65);
        else if (player.timer - 90 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 65);
        else if (player.timer - 95 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME4].dat, 220, 65);
        else if (player.timer - 100 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME3].dat, 220, 65);
        else if (player.timer - 105 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME2].dat, 220, 65);
    }
    else if (player.y_position == 200) {
        draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME1].dat, 220, 65);
        draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS1].dat, 220, 255);
        draw_sprite( buffer, (BITMAP*)mydatafile[QUIT1].dat, 220, 350);
        if (player.timer - 50 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD1].dat, 220, 160);
        else if (player.timer - 55 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD2].dat, 220, 160);
        else if (player.timer - 60 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD3].dat, 220, 160);
        else if (player.timer - 65 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD4].dat, 220, 160);
        else if (player.timer - 70 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 160);
        else if (player.timer - 75 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 160);
        else if (player.timer - 80 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK1].dat, 220, 160);
        else if (player.timer - 85 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 160);
        else if (player.timer - 90 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 160);
        else if (player.timer - 95 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD4].dat, 220, 160);
        else if (player.timer - 100 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD3].dat, 220, 160);
        else if (player.timer - 105 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[LOAD2].dat, 220, 160);
    }
    else if (player.y_position == 295) {
        draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME1].dat, 220, 65);
        draw_sprite( buffer, (BITMAP*)mydatafile[LOAD1].dat, 220, 160);
        draw_sprite( buffer, (BITMAP*)mydatafile[QUIT1].dat, 220, 350);
        if (player.timer - 50 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS1].dat, 220, 255);
        else if (player.timer - 55 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS2].dat, 220, 255);
        else if (player.timer - 60 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS3].dat, 220, 255);
        else if (player.timer - 65 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS4].dat, 220, 255);
        else if (player.timer - 70 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 255);
        else if (player.timer - 75 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 255);
        else if (player.timer - 80 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK1].dat, 220, 255);
        else if (player.timer - 85 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 255);
        else if (player.timer - 90 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 255);
        else if (player.timer - 95 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS4].dat, 220, 255);
        else if (player.timer - 100 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS3].dat, 220, 255);
        else if (player.timer - 105 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS2].dat, 220, 255);
    }
    else if (player.y_position == 390) {
        draw_sprite( buffer, (BITMAP*)mydatafile[NEWGAME1].dat, 220, 65);
        draw_sprite( buffer, (BITMAP*)mydatafile[LOAD1].dat, 220, 160);
        draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS1].dat, 220, 255);
        if (player.timer - 50 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT1].dat, 220, 350);
        else if (player.timer - 55 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT2].dat, 220, 350);
        else if (player.timer - 60 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT3].dat, 220, 350);
        else if (player.timer - 65 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT4].dat, 220, 350);
        else if (player.timer - 70 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 350);
        else if (player.timer - 75 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 350);
        else if (player.timer - 80 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK1].dat, 220, 350);
        else if (player.timer - 85 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK2].dat, 220, 350);
        else if (player.timer - 90 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[CARDBACK3].dat, 220, 350);
        else if (player.timer - 95 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT4].dat, 220, 350);
        else if (player.timer - 100 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT3].dat, 220, 350);
        else if (player.timer - 105 < 0) draw_sprite( buffer, (BITMAP*)mydatafile[QUIT2].dat, 220, 350);
    }
    draw_sprite(buffer, (BITMAP*)mydatafile[BACULO].dat, 70, (int)player.y_position - 40);
    draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[BACULO].dat, 461, (int)player.y_position - 40);
    set_trans_blender(0, 0, 0, 0);
    draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
}

void draw_cselect() {
    if (player.imune % 10 == 0) pisca = PISK1;
    else if (player.imune % 10 == 5) pisca = PISK2;
    player.imune++;
    draw_sprite( buffer, (BITMAP*)mydatafile[CSELECT].dat, 0, 0);
    if (player.cards[0] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWIND2].dat, 121, 88);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWIND].dat, 121, 88);
    if (player.cards[3] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWATER2].dat, 226, 88);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEWATER].dat, 226, 88);
    if (player.cards[4] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEFIRE2].dat, 332, 88);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEFIRE].dat, 332, 88);
    draw_sprite( buffer, (BITMAP*)mydatafile[QUITGAME].dat, 439, 88);
    if (player.cards[2] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGETHUNDER2].dat, 226, 312);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGETHUNDER].dat, 226, 312);
    if (player.cards[5] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGEICE2].dat, 332, 312);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGEICE].dat, 332, 312);
    if (player.cards[1] == 1) draw_sprite( buffer, (BITMAP*)mydatafile[STAGESHADOW2].dat, 439, 312);
    else draw_sprite( buffer, (BITMAP*)mydatafile[STAGESHADOW].dat, 439, 312);
    if (player.y_position == 0) {
        if(player.x_position == 0) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 274, 230);
        else if (player.x_position == 1) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 256, 265);
        else if (player.x_position == 2) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 220, 217);
    }
    else if (player.y_position == 1 && player.cards[0] == 1 && player.cards[1] == 1 && player.cards[2] == 1 && player.cards[3] == 1 && player.cards[4] == 1 && player.cards[5] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 249, 212);
    }
    else if (player.y_position == 2) {
        if(player.x_position == 1) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 318, 246);
        else if (player.x_position == 2) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 314, 205);
        else if (player.x_position == 3) draw_sprite( buffer, (BITMAP*)mydatafile[pisca].dat, 362, 217);
    }
    draw_sprite( buffer, (BITMAP*)mydatafile[SAVEGAME].dat, 121, 312);
    if (player.y_position != 1) draw_sprite(buffer, (BITMAP*)mydatafile[SELECT].dat, (int)(player.x_position * 105.5) + 120, (int)player.y_position * 112 + 87);
    else { draw_sprite(buffer, (BITMAP*)mydatafile[SELECT2].dat, 120, 178); draw_sprite_h_flip(buffer, (BITMAP*)mydatafile[SELECT2].dat, 501, 178); }
    set_trans_blender(0, 0, 0, 0);
    draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
}

void draw_options() {
    draw_sprite( buffer, (BITMAP*)mydatafile[OPTIONS].dat, 0, 0);
    if (player.y_position == 0) {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 132, 158);
    }
    else if (player.y_position == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 132, 215);
    }
    else if (player.y_position == 2) {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 132, 268);
    }
    else {
        draw_sprite( buffer, (BITMAP*)mydatafile[PISK1].dat, 216, 332);
    }
    rectfill(buffer, 381, 152, 381 + (int)(((music_volume_set) * 100)), 170, makecol(98,78,253));
    rectfill(buffer, 381, 207, 381 + (int)(((sound_volume_set + 1) * 100) / 256), 225, makecol(98,78,253));
    set_trans_blender(0,0,0,0);
    draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
}

void drawgamemenu() {
    masked_blit((BITMAP*)mydatafile[MENU].dat, buffer, menuposx, menuposy, 0, 0, 640, 480);
    if (player.cards[0] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 353 - menuposx, 92);
    }
    if (player.cards[2] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 63 - menuposx, 152);
    }
    if (player.cards[3] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 353 - menuposx, 152);
    }
    if (player.cards[5] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 63 - menuposx, 212);
    }
    if (player.cards[4] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 353 - menuposx, 212);
    }
    if (player.cards[1] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW2].dat, 63 - menuposx, 272);
    }
    if (player.y_position == 0) {
        if (player.x_position == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 92);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 92);
    }
    else if (player.y_position == 1) {
        if (player.x_position == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 152);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 152);
    }
    else if (player.y_position == 2) {
        if (player.x_position == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 212);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 212);
    }
    else if (player.y_position == 3) {
        if (player.x_position == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 63 - menuposx, 272);
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDOW].dat, 353 - menuposx, 272);
    }
    else if (player.y_position == 4) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUOPTIONS].dat, 67 - menuposx, 347);
    }
    else if (player.y_position == 5) {
        if (player.x_position == 0) draw_sprite( buffer, (BITMAP*)mydatafile[MENUBACK].dat, 179 - menuposx, 425);
        else if (menuposx == 640) draw_sprite( buffer, (BITMAP*)mydatafile[SETA2].dat, 667 - menuposx, 404);
        else if (menuposx == 0) draw_sprite( buffer, (BITMAP*)mydatafile[SETA].dat, 513 - menuposx, 404);
    }
    draw_sprite( buffer, (BITMAP*)mydatafile[YELLOW_TOSKO_SHOT].dat, 89 - menuposx, 109);
    if (player.current_weapon == 1) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_MA2].dat, 140 - menuposx, 104); }
    if (player.cards[2] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[ZOCK01].dat, 83 - menuposx, 159);
        if (player.current_weapon == 4) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_TH2].dat, 140 - menuposx, 164); }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_TH].dat, 140 - menuposx, 164);
    }
    if (player.cards[5] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[ICYATTACK04].dat, 71 - menuposx, 225);
        if (player.current_weapon == 7) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FR2].dat, 140 - menuposx, 224); }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FR].dat, 140 - menuposx, 224);
    }
    if (player.cards[1] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[SHADOWSHOT].dat, 80 - menuposx, 279);
        if (player.current_weapon == 3) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_SH2].dat, 140 - menuposx, 284); }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_SH].dat, 140 - menuposx, 284);
    }
    if (player.cards[0] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[MENUWINDY].dat, 359 - menuposx, 103);
        if (player.current_weapon == 2) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WI2].dat, 429 - menuposx, 104); }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WI].dat, 429 - menuposx, 104);
    }
    if (player.cards[3] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[WATERSHOT].dat, 370 - menuposx, 160);
        if (player.current_weapon == 5) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WA2].dat, 429 - menuposx, 164); }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_WA].dat, 429 - menuposx, 164);
    }
    if (player.cards[4] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[HADOUKEN01].dat, 366 - menuposx, 222);
        if (player.current_weapon == 6) { draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FI2].dat, 429 - menuposx, 224); }
        else draw_sprite( buffer, (BITMAP*)mydatafile[MENU_FI].dat, 429 - menuposx, 224);
    }
    draw_sprite( buffer, (BITMAP*)mydatafile[EXIT].dat, 360 - menuposx, 284);
    draw_sprite( buffer, (BITMAP*)mydatafile[VIDA + (player.current_weapon * 2) - 2].dat, 364 - menuposx, 341);
    draw_sprite( buffer, (BITMAP*)mydatafile[V0 + player.vidas].dat, 421 - menuposx, 349);
    if (player.cards[0] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[WINDY].dat, 1172 - menuposx, 343);                
    }
    if (player.cards[1] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[SHADOW].dat, 1034 - menuposx, 243);                
    }
    if (player.cards[2] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[THUNDER].dat, 1169 - menuposx, 193);                
    }
    if (player.cards[3] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[WATERY].dat, 1172 - menuposx, 294);                
    }
    if (player.cards[4] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[FIREY].dat, 755 - menuposx, 369);                
    }
    if (player.cards[5] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[FREEZE].dat, 894 - menuposx, 144);                
    }
    if (player.cards[6] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[ARROW].dat, 754 - menuposx, 69);                
    }
    if (player.cards[7] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[BIG].dat, 755 - menuposx, 94);                
    }
    if (player.cards[8] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[BUBBLES].dat, 755 - menuposx, 118);                
    }
    if (player.cards[9] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[CHANGE].dat, 755 - menuposx, 143);                
    }
    if (player.cards[10] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[CLOUD].dat, 755 - menuposx, 168);                
    }
    if (player.cards[11] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[CREATE].dat, 755 - menuposx, 194);                
    }
    if (player.cards[12] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[DARK].dat, 755 - menuposx, 218);                
    }
    if (player.cards[13] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[DASH].dat, 755 - menuposx, 243);                
    }
    if (player.cards[14] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[DREAM].dat, 755 - menuposx, 269);                
    }
    if (player.cards[15] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[EARTHY].dat, 755 - menuposx, 293);                
    }
    if (player.cards[16] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[ERASE].dat, 755 - menuposx, 319);                
    }
    if (player.cards[17] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 711 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[FIGHT].dat, 755 - menuposx, 343);                
    }
    if (player.cards[18] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[FLOAT].dat, 894 - menuposx, 68);                
    }
    if (player.cards[19] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[FLOWER].dat, 894 - menuposx, 93);                
    }
    if (player.cards[20] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[FLY].dat, 894 - menuposx, 118);                
    }
    if (player.cards[21] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[GLOW].dat, 894 - menuposx, 168);                
    }
    if (player.cards[22] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[ILLUSION].dat, 894 - menuposx, 193);                
    }
    if (player.cards[23] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[JUMP].dat, 894 - menuposx, 219);                
    }
    if (player.cards[24] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[LIBRA].dat, 894 - menuposx, 243);                
    }
    if (player.cards[25] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[LIGHT].dat, 894 - menuposx, 268);                
    }
    if (player.cards[26] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[LITTLE].dat, 894 - menuposx, 293);                
    }
    if (player.cards[27] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[LOCK].dat, 894 - menuposx, 318);                
    }
    if (player.cards[28] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[LOOP].dat, 894 - menuposx, 344);                
    }
    if (player.cards[29] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 850 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[MAZE].dat, 894 - menuposx, 369);                
    }
    if (player.cards[30] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[MIRROR].dat, 1034 - menuposx, 69);                
    }
    if (player.cards[31] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[MIST].dat, 1034 - menuposx, 94);                
    }
    if (player.cards[32] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[MOVE].dat, 1034 - menuposx, 119);                
    }
    if (player.cards[33] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[POWER].dat, 1034 - menuposx, 144);                
    }
    if (player.cards[34] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[RAIN].dat, 1034 - menuposx, 169);                
    }
    if (player.cards[35] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 193);
        draw_sprite( buffer, (BITMAP*)mydatafile[RETURN].dat, 1034 - menuposx, 194);                
    }
    if (player.cards[36] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[SAND].dat, 1034 - menuposx, 218);                
    }
    if (player.cards[37] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[SHIELD].dat, 1034 - menuposx, 268);                
    }
    if (player.cards[38] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 293);
        draw_sprite( buffer, (BITMAP*)mydatafile[SHOT].dat, 1034 - menuposx, 293);                
    }
    if (player.cards[39] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[SILENT].dat, 1034 - menuposx, 318);                
    }
    if (player.cards[40] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 343);
        draw_sprite( buffer, (BITMAP*)mydatafile[SLEEP].dat, 1034 - menuposx, 343);                
    }
    if (player.cards[41] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 990 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[SNOW].dat, 1034 - menuposx, 369);                
    }
    if (player.cards[42] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 68);
        draw_sprite( buffer, (BITMAP*)mydatafile[SONG].dat, 1173 - menuposx, 69);                
    }
    if (player.cards[43] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 93);
        draw_sprite( buffer, (BITMAP*)mydatafile[STORM].dat, 1173 - menuposx, 94);                
    }
    if (player.cards[44] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 118);
        draw_sprite( buffer, (BITMAP*)mydatafile[SWEET].dat, 1173 - menuposx, 119);                
    }
    if (player.cards[45] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 143);
        draw_sprite( buffer, (BITMAP*)mydatafile[SWORD].dat, 1173 - menuposx, 143);                
    }
    if (player.cards[46] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 168);
        draw_sprite( buffer, (BITMAP*)mydatafile[THROUGH].dat, 1169 - menuposx, 168);                
    }
    if (player.cards[47] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 218);
        draw_sprite( buffer, (BITMAP*)mydatafile[TIME].dat, 1173 - menuposx, 219);                
    }
    if (player.cards[48] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 243);
        draw_sprite( buffer, (BITMAP*)mydatafile[TWIN].dat, 1173 - menuposx, 244);                
    }
    if (player.cards[49] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 268);
        draw_sprite( buffer, (BITMAP*)mydatafile[VOICE].dat, 1172 - menuposx, 269);                
    }
    if (player.cards[50] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 318);
        draw_sprite( buffer, (BITMAP*)mydatafile[WAVE].dat, 1172 - menuposx, 319);                
    }
    if (player.cards[51] == 1) {
        draw_sprite( buffer, (BITMAP*)mydatafile[THE].dat, 1129 - menuposx, 368);
        draw_sprite( buffer, (BITMAP*)mydatafile[WOOD].dat, 1172 - menuposx, 368);                
    }
    set_trans_blender(0,0,0,0);
    draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
}
