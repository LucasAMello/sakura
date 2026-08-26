void move_player(float x_amount, float y_amount) {
     
     if (x_amount > 0) {
         for (int sprite_loop = 0; sprite_loop < number_of_sprites; sprite_loop++) {
             if (sprites[sprite_loop].type == 2000 || sprites[sprite_loop].type == 2001 || sprites[sprite_loop].type == 401) {
                 char col = 'n';
                 if (((int)sprites[sprite_loop].y_position > (int)player.y_position) 
                 && ((int)sprites[sprite_loop].y_position - (int)player.y_position <= 80))
                     { if (player.x_position + 40 <= sprites[sprite_loop].x_position && player.x_position + 40 + x_amount > sprites[sprite_loop].x_position) col = 'p'; }
                 else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position)
                 && ((int)player.y_position - (int)sprites[sprite_loop].y_position <= sprites[sprite_loop].height))
                     { if (player.x_position + 40 <= sprites[sprite_loop].x_position && player.x_position + 40 + x_amount > sprites[sprite_loop].x_position) col = 'p'; }
                 if (col != 'n') {
                     player.x_position = sprites[sprite_loop].x_position - 40;
                     player.x_speed = 0;
                     return;
                 }
             }
         }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39 +(x_amount)) / 20)] == '.') {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79 - x_amount) / 20)][(int)((player.x_position + 39 +(x_amount)) / 20)] == '.') {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39 +(x_amount)) / 20)] == '}') {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79 - x_amount) / 20)][(int)((player.x_position + 39 +(x_amount)) / 20)] == '}') {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39 +(x_amount)) / 20)] == '{') {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79 - x_amount) / 20)][(int)((player.x_position + 39 +(x_amount)) / 20)] == '{') {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position++;
                          if (player.y_speed == 0) {
                              y_amount = 1;
                              if (player.in_water == 0) player.timer = -21;
                              else { player.timer = -10; player.y_speed = 0.40; }
                              i_like_pizza = 1;
                              if (player.on_ground == FALSE) i_like_pizza = 0;
                              player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position++;
                          if (player.y_speed == 0) {
                              y_amount = 1;
                              if (player.in_water == 0) player.timer = -21;
                              else { player.timer = -10; player.y_speed = 0.40; }
                              i_like_pizza = 1;
                              if (player.on_ground == FALSE) i_like_pizza = 0;
                              player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position++;
                          if (player.y_speed == 0) {
                              y_amount = 1;
                              if (player.in_water == 0) player.timer = -21;
                              else { player.timer = -10; player.y_speed = 0.40; }
                              i_like_pizza = 1;
                              if (player.on_ground == FALSE) i_like_pizza = 0;
                              player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position++;
                          if (player.y_speed == 0) {
                              y_amount = 1;
                              if (player.in_water == 0) player.timer = -21;
                              else { player.timer = -10; player.y_speed = 0.40; }
                              i_like_pizza = 1;
                              if (player.on_ground == FALSE) i_like_pizza = 0;
                              player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 79 + x_amount) / 20)][(int)((player.x_position + 39 + (x_amount)) / 20)] == '1' && Map.water_position != 0) {
                      player.x_position += x_amount;
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.y_speed == 0) {
                          y_amount = 1;
                          if (player.in_water == 0) player.timer = -21;
                          else { player.timer = -10; player.y_speed = 0.40; }
                          i_like_pizza = 1;
                          if (player.on_ground == FALSE) i_like_pizza = 0;
                          player.on_ground = FALSE;
                      }
                  }
                  else if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 40 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position++;
                  }
                  else {
                      player.x_position += x_amount;
                      if (player.y_speed == 0) {
                          y_amount = 1;
                          if (player.in_water == 0) player.timer = -21;
                          else { player.timer = -10; player.y_speed = 0.40; }
                          i_like_pizza = 1;
                          if (player.on_ground == FALSE) i_like_pizza = 0;
                          player.on_ground = FALSE;
                      }
                  }
     }
     
     if (x_amount < 0) {
         for (int sprite_loop = 0; sprite_loop < number_of_sprites; sprite_loop++) {
             if (sprites[sprite_loop].type == 2000 || sprites[sprite_loop].type == 2001 || sprites[sprite_loop].type == 401) {
                 char col = 'p';
                 player.x_position += x_amount;
                 if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
                 else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
                 if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position >= 80)) col = 'n';
                 else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';
                 if (col != 'n') {
                     player.x_position = sprites[sprite_loop].x_position + sprites[sprite_loop].width;
                     player.x_speed = 0;
                     return;
                 }
                 player.x_position -= x_amount;
             }
         }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + (x_amount)) / 20)] == ',') {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79 + x_amount) / 20)][(int)((player.x_position + (x_amount)) / 20)] == ',') {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + (x_amount)) / 20)] == '[') {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79 + x_amount) / 20)][(int)((player.x_position + (x_amount)) / 20)] == '[') {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + (x_amount)) / 20)] == ']') {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position + 79 + x_amount) / 20)][(int)((player.x_position + (x_amount)) / 20)] == ']') {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
                  else if (map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position--;
                          if (player.x_position < 0) player.x_position = 0;
                          if (player.y_speed == 0) {
                             y_amount = 1;
                             if (player.in_water == 0) player.timer = -21;
                             else { player.timer = -10; player.y_speed = 0.40; }
                             i_like_pizza = 1;
                             if (player.on_ground == FALSE) i_like_pizza = 0;
                             player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 20) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position--;
                          if (player.x_position < 0) player.x_position = 0;
                          if (player.y_speed == 0) {
                             y_amount = 1;
                             if (player.in_water == 0) player.timer = -21;
                             else { player.timer = -10; player.y_speed = 0.40; }
                             i_like_pizza = 1;
                             if (player.on_ground == FALSE) i_like_pizza = 0;
                             player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 40) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position--;
                          if (player.x_position < 0) player.x_position = 0;
                          if (player.y_speed == 0) {
                             y_amount = 1;
                             if (player.in_water == 0) player.timer = -21;
                             else { player.timer = -10; player.y_speed = 0.40; }
                             i_like_pizza = 1;
                             if (player.on_ground == FALSE) i_like_pizza = 0;
                             player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 60) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position--;
                          if (player.x_position < 0) player.x_position = 0;
                          if (player.y_speed == 0) {
                             y_amount = 1;
                             if (player.in_water == 0) player.timer = -21;
                             else { player.timer = -10; player.y_speed = 0.40; }
                             i_like_pizza = 1;
                             if (player.on_ground == FALSE) i_like_pizza = 0;
                             player.on_ground = FALSE;
                          }
                  }
                  else if (map[(int)((player.y_position + 79 + x_amount) / 20)][(int)((player.x_position + (x_amount)) / 20)] == '1' && Map.water_position != 0) {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) player.y_position--;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                      if (player.y_speed == 0) {
                          y_amount = 1;
                          if (player.in_water == 0) player.timer = -21;
                          else { player.timer = -10; player.y_speed = 0.40; }
                          i_like_pizza = 1;
                          if (player.on_ground == FALSE) i_like_pizza = 0;
                          player.on_ground = FALSE;
                      }
                  }
                  else if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '1' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '.' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '[' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ']' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '}' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != '{' &&
                           map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 0.1 + (x_amount)) / 20)] != ',') {
                          player.x_speed = 0;
                          while ((int)player.x_position % 20 != 0) player.x_position--;
                          if (player.x_position < 0) player.x_position = 0;
                  }
                  else {
                      player.x_position += x_amount;
                      if (player.x_position < 0) player.x_position = 0;
                      if (player.y_speed == 0) {
                          y_amount = 1;
                          if (player.in_water == 0) player.timer = -21;
                          else { player.timer = -10; player.y_speed = 0.40; }
                          i_like_pizza = 1;
                          if (player.on_ground == FALSE) i_like_pizza = 0;
                          player.on_ground = FALSE;
                      }
                  }
     }
     
     if (y_amount < 0) {
         for (int sprite_loop = 0; sprite_loop < number_of_sprites; sprite_loop++) {
             if (sprites[sprite_loop].type == 2000 || sprites[sprite_loop].type == 2001 || sprites[sprite_loop].type == 401) {
                 char col = 'n';
                 if (((int)sprites[sprite_loop].x_position > (int)player.x_position) 
                 && ((int)sprites[sprite_loop].x_position - (int)player.x_position <= 40))
                     { if ((int)player.y_position >= (sprites[sprite_loop].y_position + sprites[sprite_loop].height) && player.y_position + (y_amount * 5) < (sprites[sprite_loop].y_position + sprites[sprite_loop].height)) col = 'p'; }
                 else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position)
                 && ((int)player.x_position - (int)sprites[sprite_loop].x_position <= sprites[sprite_loop].width))
                     { if ((int)player.y_position >= (sprites[sprite_loop].y_position + sprites[sprite_loop].height) && player.y_position + (y_amount * 5) < (sprites[sprite_loop].y_position + sprites[sprite_loop].height)) col = 'p'; }
                 if (col != 'n') {
                     player.y_position = sprites[sprite_loop].y_position + sprites[sprite_loop].height;
                     if (player.y_position < 0) player.y_position = 0;
                     player.on_ground = FALSE;
                     player.timer++;
                     return;
                 }
             }
         }
                  if (map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)(player.x_position / 20)] != '1' &&
                      map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)(player.x_position / 20)] != '.' &&
                      map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)(player.x_position / 20)] != ',') {
                          while ((int)player.y_position % 20 != 0) player.y_position--;
                          player.on_ground = FALSE;
                          player.timer++;
                  }
                  else if (map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)((player.x_position + 20) / 20)] != '1' &&
                           map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)((player.x_position + 20) / 20)] != '.' &&
                           map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)((player.x_position + 20) / 20)] != ',') {
                          while ((int)player.y_position % 20 != 0) player.y_position--;
                          player.on_ground = FALSE;
                          player.timer++;
                  }
                  else if (map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)((player.x_position + 39) / 20)] != '1' &&
                           map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)((player.x_position + 39) / 20)] != '.' &&
                           map[(int)((player.y_position + (y_amount * 5)) / 20)][(int)((player.x_position + 39) / 20)] != ',') {
                          while ((int)player.y_position % 20 != 0) player.y_position--;
                          player.on_ground = FALSE;
                          player.timer++;
                  }
                  else {
                      player.y_position += (y_amount * 5);
                      if (player.y_position < 0) player.y_position = 0;
                      player.on_ground = FALSE;
                      player.timer++;
                      if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
                  }
     }
     
     if (y_amount > 0 && player.on_ground == FALSE) {
         for (int sprite_loop = 0; sprite_loop < number_of_sprites; sprite_loop++) {
             if (sprites[sprite_loop].type == 2000 || sprites[sprite_loop].type == 2001 || sprites[sprite_loop].type == 500 || sprites[sprite_loop].type == 53) {
                 char col = 'n';
                 if (((int)sprites[sprite_loop].x_position > (int)player.x_position) 
                 && ((int)sprites[sprite_loop].x_position - (int)player.x_position <= 40))
                     { if ((int)player.y_position + 80 <= (int)sprites[sprite_loop].y_position && (int)player.y_position + 80 + (y_amount * 5) > (int)sprites[sprite_loop].y_position) col = 'p'; }
                 else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position)
                 && ((int)player.x_position - (int)sprites[sprite_loop].x_position <= sprites[sprite_loop].width))
                     { if ((int)player.y_position + 80 <= (int)sprites[sprite_loop].y_position && (int)player.y_position + 80 + (y_amount * 5) > (int)sprites[sprite_loop].y_position) col = 'p'; }
                 /*player.y_position += (y_amount * 5);
                 if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
                 else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
                 if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position >= 80)) col = 'n';
                 else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';*/
                 if (col != 'n') {
                     player.y_position = sprites[sprite_loop].y_position - 80;
                     player.y_speed = 0;
                     player.on_ground = TRUE; 
                     player.timer = 0;
                     if (i_like_pizza == 1) i_like_pizza = 0;
                     else w84go = 1;
                     return;
                 }
                 //player.y_position -= (y_amount * 5);
             }
         }
                  if (map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != '1' &&
                      map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != '.' &&
                      map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != '[' &&
                      map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != ']' &&
                      map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != '}' &&
                      map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != '{' &&
                      map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] != ',') {
                          if (map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)(player.x_position / 20))] == '0') { dead = 1; return; }
                          while ((int)player.y_position % 20 != 0) player.y_position++;
                          player.y_speed = 0;
                          player.on_ground = TRUE; 
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                          else w84go = 1;
                  }
                  else if (map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != '1' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != '.' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != '[' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != ']' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != '}' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != '{' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] != ',') {
                          if (map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 20) / 20))] == '0') { dead = 1; return; }
                          while ((int)player.y_position % 20 != 0) player.y_position++;
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                          else w84go = 1;
                  }
                  else if (map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != '1' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != '.' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != '[' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != ']' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != '}' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != '{' &&
                           map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] != ',') {
                          if (map[(int)((player.y_position + 79 + (y_amount * 5)) / 20)][((int)((player.x_position + 39) / 20))] == '0') { dead = 1; return; }
                          while ((int)player.y_position % 20 != 0) player.y_position++;
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                          else w84go = 1;
                  }
                  else {
                      player.y_position += (y_amount * 5);
                      player.on_ground = FALSE;
                      player.timer--;
                      i_like_pizza = 0;
                      if (player.in_water == 0 && player.y_position + 24 >= Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 1; }
                  }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position) / 20)] == ',' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 20) / 20)] == ',' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39) / 20)] == ',') {
                      int tcheck = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 20, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      if (tcheck > 0) {
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                      }
                  }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position) / 20)] == '.' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 20) / 20)] == '.' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39) / 20)] == '.') {
                      int tcheck = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 20, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      if (tcheck > 0) {
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                      }
                  }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position) / 20)] == '[' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 20) / 20)] == '[' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39) / 20)] == '[') {
                      int tcheck = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 20, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      if (tcheck > 0) {
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                      }
                  }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position) / 20)] == ']' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 20) / 20)] == ']' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39) / 20)] == ']') {
                      int tcheck = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 20, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      if (tcheck > 0) {
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                      }
                  }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position) / 20)] == '}' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 20) / 20)] == '}' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39) / 20)] == '}') {
                      int tcheck = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 20, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      if (tcheck > 0) {
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                      }
                  }
                  if (map[(int)((player.y_position + 79) / 20)][(int)((player.x_position) / 20)] == '{' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 20) / 20)] == '{' ||
                      map[(int)((player.y_position + 79) / 20)][(int)((player.x_position + 39) / 20)] == '{') {
                      int tcheck = 0;
                      while (getpixel(scenario, (int)player.x_position, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 20, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      while (getpixel(scenario, (int)player.x_position + 39, (int)player.y_position + 79) != makecol(255,0,255)) { player.y_position--; tcheck++; }
                      if (tcheck > 0) {
                          player.y_speed = 0;
                          player.on_ground = TRUE;
                          player.timer = 0;
                          if (i_like_pizza == 1) i_like_pizza = 0;
                      }
                  }
     }
     if (player.in_water == 0 && player.y_position + 24 >= Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 1; }   
     else if (player.in_water == 1 && player.y_position + 29 < Map.water_position && Map.water_position != 0) { initialize_sprite(404, (int)player.x_position - 4, Map.water_position - 14, 0, 0); player.in_water = 0; }
     if (player.x_position < 0) player.x_position = 0;
}

int inpl(int x) {
    if (sprites[x].x_position - player.x_position > -520 && sprites[x].x_position - player.x_position < 520 && sprites[x].y_position - player.y_position > -380 && sprites[x].y_position - player.y_position < 380) return 1;
    return 0;
}
