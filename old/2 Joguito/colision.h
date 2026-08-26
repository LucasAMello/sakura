int check_colision(int sprite_number, int loop, int sop) {
     
     if (sop == 1) {
          if (sprites[sprite_number].x_position > sprites[loop].x_position && sprites[sprite_number].x_position - sprites[loop].x_position >= sprites[loop].width) return 0;
		  else if (sprites[sprite_number].x_position <= sprites[loop].x_position && sprites[loop].x_position - sprites[sprite_number].x_position >= sprites[sprite_number].width) return 0;
		  if (sprites[sprite_number].y_position > sprites[loop].y_position && sprites[sprite_number].y_position - sprites[loop].y_position >= sprites[loop].height) return 0;
		  else if (sprites[sprite_number].y_position <= sprites[loop].y_position && sprites[loop].y_position - sprites[sprite_number].y_position >= sprites[sprite_number].height) return 0;
     }
     
     if (sop == 2) {
          if (sprites[sprite_number].x_position > walls[loop].x_position && sprites[sprite_number].x_position - walls[loop].x_position >= walls[loop].width) return 0;
		  else if (sprites[sprite_number].x_position <= walls[loop].x_position && walls[loop].x_position - sprites[sprite_number].x_position >= sprites[sprite_number].width) return 0;
		  if (sprites[sprite_number].y_position > walls[loop].y_position && sprites[sprite_number].y_position - walls[loop].y_position >= walls[loop].height) return 0;
		  else if (sprites[sprite_number].y_position <= walls[loop].y_position && walls[loop].y_position - sprites[sprite_number].y_position >= sprites[sprite_number].height) return 0;
     }
     
     if (sop == 3) {
          if (sprites[sprite_number].type == 1) {
              int x = (int)sprites[sprite_number].x_position - (int)sprites[loop].x_position;
              int y = (int)sprites[sprite_number].y_position - (int)sprites[loop].y_position;
          if (sprites[loop].direction == 0) {
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 1, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 1) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 1) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 8) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 2, y + 8) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 1) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 1) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 8) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 8) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 9) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 3, y + 9) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 1) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 1) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 8) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 8) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 9) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 4, y + 9) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 1) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 1) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 8) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 8) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 9) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 5, y + 9) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 1) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 1) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 8) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 8) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 9) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 6, y + 9) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 1) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 1) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 8) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 7, y + 8) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 2) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 2) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 6) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 7) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 8, y + 7) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 3) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 3) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 4) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 4) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 5) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 5) != -1) return 1;
              if (getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 6) != makecol(255, 0, 255) &&
                  getpixel((BITMAP*)mydatafile[sprites[loop].frame].dat, x + 9, y + 6) != -1) return 1;
              return 0;
          }
          else {
              BITMAP* temp = create_bitmap(sprites[loop].width, sprites[loop].height);
              clear_to_color(temp, bitmap_mask_color((BITMAP*)mydatafile[sprites[loop].frame].dat));
              draw_sprite_h_flip(temp, (BITMAP*)mydatafile[sprites[loop].frame].dat, 0, 0);
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
     
     if (sop == 4) {
          if (sprites[sprite_number].type == 1) {
              int x = (int)sprites[sprite_number].x_position;
              int y = (int)sprites[sprite_number].y_position;
              if (getpixel(scenario, x, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x, y + 3, 0)) return 1;
              if (getpixel(scenario, x, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x, y + 4, 0)) return 1;
              if (getpixel(scenario, x, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x, y + 5, 0)) return 1;
              if (getpixel(scenario, x, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 1, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 1, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 1, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 1, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 1, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 1, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 1, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 1, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 1, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 1, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 1, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 1, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 1) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 1, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 2, y + 8) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 2, y + 8, 0)) return 1;
              if (getpixel(scenario, x + 3, y) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 1) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 1, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 8) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 8, 0)) return 1;
              if (getpixel(scenario, x + 3, y + 9) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 3, y + 9, 0)) return 1;
              if (getpixel(scenario, x + 4, y) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 1) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 1, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 8) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 8, 0)) return 1;
              if (getpixel(scenario, x + 4, y + 9) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 4, y + 9, 0)) return 1;
              if (getpixel(scenario, x + 5, y) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 1) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 1, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 8) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 8, 0)) return 1;
              if (getpixel(scenario, x + 5, y + 9) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 5, y + 9, 0)) return 1;
              if (getpixel(scenario, x + 6, y) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 1) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 1, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 8) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 8, 0)) return 1;
              if (getpixel(scenario, x + 6, y + 9) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 6, y + 9, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 1) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 1, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 7, y + 8) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 7, y + 8, 0)) return 1;
              if (getpixel(scenario, x + 8, y + 2) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 8, y + 2, 0)) return 1;
              if (getpixel(scenario, x + 8, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 8, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 8, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 8, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 8, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 8, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 8, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 8, y + 6, 0)) return 1;
              if (getpixel(scenario, x + 8, y + 7) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 8, y + 7, 0)) return 1;
              if (getpixel(scenario, x + 9, y + 3) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 9, y + 3, 0)) return 1;
              if (getpixel(scenario, x + 9, y + 4) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 9, y + 4, 0)) return 1;
              if (getpixel(scenario, x + 9, y + 5) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 9, y + 5, 0)) return 1;
              if (getpixel(scenario, x + 9, y + 6) != makecol(255, 0, 255) &&
                  is_inside_bitmap(scenario, x + 9, y + 6, 0)) return 1;
              return 0;
          }
     }
     
     return 1;
}
                  

void sprite_colision(int sprite_number, int type) {
     int sprite_loop;
     int noisiloc;
     for (sprite_loop = 0; sprite_loop < number_of_sprites; sprite_loop++) {
         if (sprites[sprite_loop].active == 1) {
             if (type == 1 && sprites[sprite_number].type == 1 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43 && sprites[sprite_loop].type != 44 && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202 && sprites[sprite_loop].type != 75 && sprites[sprite_loop].type != 76) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      if (check_colision(sprite_number, sprite_loop, 3)) {
                      sprites[sprite_number].biba = 0;
                      if (sprites[sprite_number].direction == 0) {
                      while (check_colision(sprite_number, sprite_loop, 3) && sprites[sprite_number].biba < 5) { sprites[sprite_number].x_position--; sprites[sprite_number].biba++; }
                      }
                      else {
                      while (check_colision(sprite_number, sprite_loop, 3) && sprites[sprite_number].biba < 5) { sprites[sprite_number].x_position++; sprites[sprite_number].biba++; }
                      }
                      //if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (sprites[sprite_loop].x_position + sprites[sprite_loop].width - 8);
                      //else sprites[sprite_number].x_position = sprites[sprite_loop].x_position - 12;
                      animation(sprite_number);
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007 || sprites[sprite_loop].type == 1008) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007 || sprites[sprite_loop].type == 1008) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].hit_points_left > 0 && sprites[sprite_loop].type != 1008) sprites[sprite_loop].hit_points_left-=0.5;
                              else if (sprites[sprite_loop].type == 1008 && sprites[sprite_loop].rotate_factor == 0) { sprites[sprite_loop].hit_points_left -= 1; sprites[sprite_loop].rotate_factor = 1; }
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1008) { sprites[sprite_loop].action_state = 666; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else sprites[sprite_loop].hit_points_left -= 1;
                          sprite_update(sprite_loop);
                          break;
                      }
                      }
                 }
             }
             else if (type == 2 && sprites[sprite_number].type == 2 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202 && sprites[sprite_loop].type != 75 && sprites[sprite_loop].type != 76) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      animation(sprite_number);
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 66 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if ((sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003) && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 3; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      if (sprites[sprite_x].hit_points_left > 0) { sprites[sprite_x].hit_points_left -= 3; if (sprites[sprite_x].hit_points_left < 0) sprites[sprite_x].hit_points_left = 0; }
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else if (sprites[sprite_loop].type == 66) {
                            if (sprites[sprite_loop].action_state != 1) {
                              sprites[sprite_loop].action_state = 1;
                              sprites[sprite_loop].frame = SANDMORRO2;
                              sprites[sprite_loop].direction = sprites[sprite_number].direction;
                              play_sample((SAMPLE *)mydatafile[SANDS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                              if (player.cards[sprites[sprite_loop].biba] == 0) initialize_sprite(69, (int)sprites[sprite_loop].x_position + 11, (int)sprites[sprite_loop].y_position, 0, sprites[sprite_loop].biba);
                            }
                          }
                          else sprites[sprite_loop].hit_points_left -= 2;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if (type == 3 && sprites[sprite_number].type == 3 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202 && sprites[sprite_loop].type != 75 && sprites[sprite_loop].type != 76) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (sprites[sprite_loop].type == 1000) {
                 if (check_colision(sprite_number, sprite_loop, 1)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].x_speed < 0) { sprites[sprite_number].x_position = (sprites[sprite_loop].x_position + sprites[sprite_loop].width); }
                          else { sprites[sprite_number].x_position = sprites[sprite_loop].x_position - 30; }
                          sprites[sprite_number].x_speed *= -1;
                      }
                      else if (sprites[sprite_number].biba == 2) {
                         if (sprites[sprite_number].y_speed < 0) { sprites[sprite_number].y_position = (sprites[sprite_loop].y_position + sprites[sprite_loop].height); }
                         else { sprites[sprite_number].y_position = sprites[sprite_loop].y_position - 30; }
                         sprites[sprite_number].y_speed *= -1;
                      }
                      play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
                 }
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      animation(sprite_number);
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 4; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else sprites[sprite_loop].hit_points_left -= 3;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if (type == 4 && sprites[sprite_number].type == 4 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202 && sprites[sprite_loop].type != 75 && sprites[sprite_loop].type != 76) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 if (sprites[sprite_loop].type == 60 && (sprites[sprite_loop].action_state == 3 || sprites[sprite_loop].action_state == 4)) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      animation(sprite_number);
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007 || sprites[sprite_loop].type == 60) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].type == 1005 && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 3; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                                  sprites[sprite_loop].timer = 100;
                              }
                              else { sprites[sprite_loop].timer = 29; }
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else if (sprites[sprite_loop].type == 60) {
                            if (sprites[sprite_loop].action_state != 4) {
                              sprites[sprite_loop].action_state = 3;
                              sprites[sprite_loop].animation_state = 0;
                              sprites[sprite_loop].timer = 0;
                            }
                          }
                          else if (sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 30) {
                              sprites[sprite_loop].hit_points_left -= 4;
                          }
                          else sprites[sprite_loop].hit_points_left -= 2;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if (type == 5 && sprites[sprite_number].type == 5 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202 && sprites[sprite_loop].type != 75 && sprites[sprite_loop].type != 76) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (sprites[sprite_loop].x_position + sprites[sprite_loop].width - 7);
                          else sprites[sprite_number].x_position = sprites[sprite_loop].x_position - 29 + 14;
                      }
                      else if (sprites[sprite_number].biba == 2) {
                          if (sprites[sprite_number].y_speed <= 0) { sprites[sprite_number].biba = 3; sprites[sprite_number].y_position = sprites[sprite_loop].y_position + sprites[sprite_loop].height; }
                          else sprites[sprite_number].y_position = sprites[sprite_loop].y_position - 29;
                      }
                      sprites[sprite_number].strength = 1; animation(sprite_number);
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].type == 1006 && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 3; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else if (sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42 || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 21) {
                              sprites[sprite_loop].hit_points_left -= 3;
                          }
                          else sprites[sprite_loop].hit_points_left -= 1;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if ((type == 57 && sprites[sprite_number].type == 57 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011 && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202) ||
                           (type == 58 && sprites[sprite_number].type == 58 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011 && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202)) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      sprites[sprite_number].active = 0;
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].type == 1006 && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 3; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 21) {
                              sprites[sprite_loop].hit_points_left -= 3;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else sprites[sprite_loop].hit_points_left -= 1;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if (type == 6 && sprites[sprite_number].type == 6 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43   && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                          sprites[sprite_number].action_state = 2; sprites[sprite_number].timer = 0; play_sample((SAMPLE *)mydatafile[HADUEX].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                          if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = sprites[sprite_loop].x_position + sprites[sprite_loop].width;
                          else sprites[sprite_number].x_position = sprites[sprite_loop].x_position - 24;
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 67 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].type == 1007 && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 4; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else if (sprites[sprite_loop].type == 67) {
                               if (sprites[sprite_loop].action_state != 1) sprites[sprite_loop].action_state = 1;
                          }
                          else sprites[sprite_loop].hit_points_left -= 3;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if (type == 7 && sprites[sprite_number].type == 7 && sprites[sprite_loop].type != 100 && sprites[sprite_loop].type != 1 && sprites[sprite_loop].type != 2 && sprites[sprite_loop].type != 3 && sprites[sprite_loop].type != 4 && sprites[sprite_loop].type != 101 && sprites[sprite_loop].type != 102 && sprites[sprite_loop].type != 106 && sprites[sprite_loop].type != 73 && sprites[sprite_loop].type != 74 && sprites[sprite_loop].type != 2004
                           && sprites[sprite_loop].type != 5 && sprites[sprite_loop].type != 6 && sprites[sprite_loop].type != 7 && sprites[sprite_loop].type != 57 && sprites[sprite_loop].type != 58 && sprites[sprite_loop].type != 666 && sprites[sprite_loop].type != 667 && sprites[sprite_loop].type != 113 && sprites[sprite_loop].type != 200
                           && sprites[sprite_loop].type != 201 && sprites[sprite_loop].type != 400 && sprites[sprite_loop].type != 402 && sprites[sprite_loop].type != 403 && sprites[sprite_loop].type != 1010 && sprites[sprite_loop].type != 1011
                           && sprites[sprite_loop].type != 20 && sprites[sprite_loop].type != 26 && sprites[sprite_loop].type != 39 && sprites[sprite_loop].type != 40 && sprites[sprite_loop].type != 43 && sprites[sprite_loop].type != 16 && sprites[sprite_loop].type != 61
                           && sprites[sprite_loop].type != 59 && sprites[sprite_loop].type != 60 && sprites[sprite_loop].type != 104 && sprites[sprite_loop].type != 120 && sprites[sprite_loop].type != 404 && sprites[sprite_loop].type != 501 && sprites[sprite_loop].type != 305
                           && sprites[sprite_loop].type != 66 && sprites[sprite_loop].type != 67 && sprites[sprite_loop].type != 69 && sprites[sprite_loop].type != 70 && sprites[sprite_loop].type != 202) {
                 if (sprites[sprite_loop].type == 15 && sprites[sprite_loop].action_state == 0) continue;
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) continue;
                 else if (sprites[sprite_loop].type == 1004 && sprites[sprite_loop].frame > THUNDER05) continue;
                 else if (check_colision(sprite_number, sprite_loop, 1)) {
                      animation(sprite_number);
                      if (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
                       || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 72
                       || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 23 || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
                       || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 65
                       || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                          if (sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007) {
                              if (sprites[sprite_loop].type == 1002 && sprites[sprite_loop].action_state != 4 && sprites[sprite_loop].action_state != 6) sprites[sprite_loop].type = 1002;
                              else if (sprites[sprite_loop].type == 1007 && ((sprites[sprite_loop].action_state != 2 && sprites[sprite_loop].action_state < 6) || sprites[sprite_loop].frame < ICYSIDE01)) sprites[sprite_loop].type = 1007;
                              else if (sprites[sprite_loop].type == 1001 && sprites[sprite_loop].hit_points_left > 0) { sprites[sprite_loop].hit_points_left -= 4; if (sprites[sprite_loop].hit_points_left < 0) sprites[sprite_loop].hit_points_left = 0; }
                              else if (sprites[sprite_loop].type == 1008) sprites[sprite_loop].type = 1008;
                              else if (sprites[sprite_loop].hit_points_left > 0) sprites[sprite_loop].hit_points_left-=0.5;
                              if (sprites[sprite_loop].hit_points_left <= 0) {
                                  sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                  for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                      if (sprites[sprite_x].type == 1003) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = 0;
                                          sprites[sprite_x].action_state = 2;
                                          sprites[sprite_loop].action_state = 7;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                      }
                                  }
                                  if (sprites[sprite_loop].type == 1004) { sprites[sprite_loop].action_state = 8; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1001) { sprites[sprite_loop].action_state = 13; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1005) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1006) { sprites[sprite_loop].action_state = 6; sprites[sprite_loop].timer = 0; }
                                  else if (sprites[sprite_loop].type == 1007) { sprites[sprite_loop].action_state = 18; sprites[sprite_loop].timer = 0; }
                                  input_locked = 1; bosslife = 0;
                                  player.x_speed = player.y_speed = 0;
                              }
                          }
                          else if (sprites[sprite_loop].type == 1003) {
                              for (int sprite_x = 0; sprite_x < number_of_sprites; sprite_x++) {
                                  if (sprites[sprite_x].type == 1002 && (sprites[sprite_x].action_state == 4 || sprites[sprite_x].action_state == 6)) {
                                      sprites[sprite_x].hit_points_left-=0.5;
                                      if (sprites[sprite_x].hit_points_left == 0) {
                                          sprites[sprite_x].x_speed = sprites[sprite_x].y_speed = sprites[sprite_loop].x_speed = sprites[sprite_loop].y_speed = 0;
                                          sprites[sprite_x].action_state = 7; sprites[sprite_loop].action_state = 2;
                                          sprites[sprite_x].timer = sprites[sprite_loop].timer = 0;
                                          input_locked = 1; bosslife = 0;
                                      }
                                  }
                              }
                          }
                          else if (sprites[sprite_loop].type == 55) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].biba = sprites[sprite_loop].timer;
                                  if (sprites[sprite_loop].timer % 6 < 4) sprites[sprite_loop].frame = PUMPKIN05;
                                  else sprites[sprite_loop].frame = PUMPKIN04;
                              }
                              sprites[sprite_loop].timer = 0;
                          }
                          else if (sprites[sprite_loop].type == 65) {
                              if (sprites[sprite_loop].action_state == 0) {
                                  sprites[sprite_loop].action_state = 1;
                                  sprites[sprite_loop].timer = 0;
                                  play_sample((SAMPLE *)mydatafile[GLASS].dat, (int)(125 * sound_volume_set / 255), 128, 1000, 0);
                                  initialize_sprite(69, (int)sprites[sprite_loop].x_position + 9, (int)sprites[sprite_loop].y_position + 12, 0, sprites[sprite_loop].biba);
                              }
                          }
                          else sprites[sprite_loop].hit_points_left -= 2;
                          sprite_update(sprite_loop);
                          break;
                      }
                 }
             }
             else if (type == 1002 && sprites[sprite_loop].type == 1000) {
                 if (check_colision(sprite_number, sprite_loop, 1)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].x_speed > 0) sprites[sprite_number].x_position = sprites[sprite_loop].x_position - 50;
                          else sprites[sprite_number].x_position = sprites[sprite_loop].x_position + 30;
                          sprites[sprite_number].x_speed = sprites[sprite_number].x_speed * -1;
                      }
                      else {
                          if (sprites[sprite_number].y_speed > 0) sprites[sprite_number].y_position = sprites[sprite_loop].y_position - 50;
                          else sprites[sprite_number].y_position = sprites[sprite_loop].y_position + 20;
                          sprites[sprite_number].y_speed *= -1;
                      }
                      play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
             }
             else if (type == 1003 && sprites[sprite_loop].type == 1000) {
                 if (check_colision(sprite_number, sprite_loop, 1)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].x_speed > 0) sprites[sprite_number].x_position = sprites[sprite_loop].x_position - 50;
                          else sprites[sprite_number].x_position = sprites[sprite_loop].x_position + 30;
                          sprites[sprite_number].x_speed = sprites[sprite_number].x_speed * -1;
                      }
                      else {
                          if (sprites[sprite_number].y_speed > 0) sprites[sprite_number].y_position = sprites[sprite_loop].y_position - 50;
                          else sprites[sprite_number].y_position = sprites[sprite_loop].y_position + 20;
                          sprites[sprite_number].y_speed *= -1;
                      }
                      play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
             }
             else if (type == 26 && sprites[sprite_loop].type == 1000) {
                 if (check_colision(sprite_number, sprite_loop, 1)) sprites[sprite_number].active = 0;
             }
             else if (type == 56 && sprites[sprite_loop].type == 999) {
                 if (check_colision(sprite_number, sprite_loop, 1)) sprites[sprite_number].active = 0;
             }
             else if (type == 36 && sprites[sprite_loop].type == 1000) {
                 if (check_colision(sprite_number, sprite_loop, 1)) {
                     if (sprites[sprite_number].direction == 0) {
                         if (sprites[sprite_number].animation_state == 0) {
                             sprites[sprite_number].x_position = sprites[sprite_loop].x_position + 30;
                             sprites[sprite_number].biba -= 2;
                             sprites[sprite_number].width -= 32;
                             sprites[sprite_number].x_position -= 3;
                             if (sprites[sprite_number].biba <= 0) sprites[sprite_number].active = 0;
                         }
                         else {
                             if (sprites[sprite_number].action_state == 1) {
                                 sprites[sprite_number].biba -= 2;
                                 sprites[sprite_number].width -= 32;
                                 sprites[sprite_number].x_position = sprites[sprite_loop].x_position + 30;
                                 if (sprites[sprite_number].biba <= 0) sprites[sprite_number].active = 0;
                             }
                             else sprites[sprite_number].x_position = sprites[sprite_loop].x_position + 30;
                         }
                     }
                 }
             }
             else if (type == 1005 && sprites[sprite_loop].type == 1000) {
                 if (check_colision(sprite_number, sprite_loop, 1)) {
                     sprites[sprite_number].x_position = sprites[sprite_loop].x_position + 30;
                     sprites[sprite_number].action_state++;
                     sprites[sprite_number].timer = 0;
                 }
             }
         }
     }
     int wall_loop;
     for (wall_loop = 0; wall_loop < number_of_walls; wall_loop++) {
         if (walls[wall_loop].active == 1) {
             if (type == 1 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                 if (check_colision(sprite_number, wall_loop, 4)) {
                      if (sprites[sprite_number].direction == 0) {
                          if (check_colision(sprite_number, wall_loop, 4)) { sprites[sprite_number].x_position -= 1;}
                      }
                      else { 
                          if (check_colision(sprite_number, wall_loop, 4)) { sprites[sprite_number].x_position += 1;}
                      }
                      animation(sprite_number);
                 }
                 }
             }
             
             else if (type == 2 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width);
                      else sprites[sprite_number].x_position = walls[wall_loop].x_position - 65;
                      animation(sprite_number);
                 }
             }
             
             else if (type == 3 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].x_speed < 0) { sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width); }
                          else { sprites[sprite_number].x_position = walls[wall_loop].x_position - 30; }
                          sprites[sprite_number].x_speed *= -1;
                      }
                      else if (sprites[sprite_number].biba == 2) {
                         if (sprites[sprite_number].y_speed < 0) { sprites[sprite_number].y_position = (walls[wall_loop].y_position + walls[wall_loop].height); }
                         else { sprites[sprite_number].y_position = walls[wall_loop].y_position - 30; }
                         sprites[sprite_number].y_speed *= -1;
                      }
                      play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
             }
             
             else if (type == 4 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width - 5);
                      else sprites[sprite_number].x_position = walls[wall_loop].x_position - 21;
                      animation(sprite_number);
                 }
             }
             
             else if (type == 5 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width);
                          else sprites[sprite_number].x_position = walls[wall_loop].x_position - 29;
                          animation(sprite_number);
                      }
                      else if (sprites[sprite_number].biba == 2) {
                          if (sprites[sprite_number].y_speed <= 0) { sprites[sprite_number].biba = 3; sprites[sprite_number].y_position = walls[wall_loop].y_position + 20; }
                          else sprites[sprite_number].y_position = walls[wall_loop].y_position - 29;
                          animation(sprite_number);
                      }
                 }
             }
             
             else if (type == 6 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (check_colision(sprite_number, wall_loop, 4)) {
                         int y = 0;
                         while ((y < sprites[sprite_number].y_speed - 2) && check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].y_position--;
                             y++;
                         }
                         if (check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].action_state = 2; sprites[sprite_number].timer = 0;
                             if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                             else sprites[sprite_number].x_position = walls[wall_loop].x_position - 24;
                             play_sample((SAMPLE *)mydatafile[HADUEX].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                         }
                     }
                 }
             }
             
             else if (type == 7 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width);
                      else sprites[sprite_number].x_position = walls[wall_loop].x_position - 47;
                      animation(sprite_number);
                 }
             }
             
             else if (type == 17) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      sprites[sprite_number].animation_state = 1;
                 }
             }
             else if (type == 62) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      sprites[sprite_number].animation_state = 1;
                 }
             }
             
             else if (type == 57 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width);
                      else sprites[sprite_number].x_position = walls[wall_loop].x_position - 14;
                      sprites[sprite_number].active = 0;
                 }
             }

             else if (type == 58 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = (walls[wall_loop].x_position + walls[wall_loop].width);
                      else sprites[sprite_number].x_position = walls[wall_loop].x_position - 14;
                      sprites[sprite_number].active = 0;
                 }
             }
             
             else if (type == 200 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) { sprites[sprite_number].y_speed = 0; sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height; }
             }
             else if (type == 202 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) { sprites[sprite_number].y_speed = 0; sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height; }
             }
             
             else if (type == 69 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) { sprites[sprite_number].y_speed = 0; sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height - 10; }
             }
             
             else if (type == 13 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2))
                      animation(sprite_number);
             }

             else if (type == 20 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2))
                      animation(sprite_number);
             }
             
             else if (type == 22 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2))
                      animation(sprite_number);
             }
             
             else if (type == 26 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2))
                      sprites[sprite_number].active = 0;
             }
             
             else if (type == 28 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2))
                      if (sprites[sprite_number].biba == 0) sprites[sprite_number].biba = (int)walls[wall_loop].y_position;
             }
             else if (type == 76 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2))
                      if (sprites[sprite_number].biba == 0) sprites[sprite_number].biba = (int)walls[wall_loop].y_position;
             }

             else if (type == 35 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (check_colision(sprite_number, wall_loop, 4)) {
                         int y = 0;
                         while ((y < sprites[sprite_number].y_speed - 2) && check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].y_position--;
                             y++;
                         }
                         if (check_colision(sprite_number, wall_loop, 4)) sprites[sprite_number].active = 0;
                     }
                 }
             }
             
             else if (type == 36 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (sprites[sprite_number].direction == 1) {
                         if (sprites[sprite_number].animation_state == 1) {
                             if (sprites[sprite_number].action_state == 1) {
                                 sprites[sprite_number].biba -= 2;
                                 sprites[sprite_number].width -= 32;
                                 sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width;
                                 if (sprites[sprite_number].biba <= 0) sprites[sprite_number].active = 0;
                             }
                             else sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width;
                         }
                         else {
                             sprites[sprite_number].biba -= 2;
                             sprites[sprite_number].width -= 32;
                             sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width;
                             //sprites[sprite_number].x_position -= 3;
                             if (sprites[sprite_number].biba <= 0) sprites[sprite_number].active = 0;
                         }
                     }
                     else  {
                         if (sprites[sprite_number].animation_state == 0) {
                             sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                             sprites[sprite_number].biba -= 2;
                             sprites[sprite_number].width -= 32;
                             sprites[sprite_number].x_position -= 3;
                             if (sprites[sprite_number].biba <= 0) sprites[sprite_number].active = 0;
                         }
                         else {
                             if (sprites[sprite_number].action_state == 1) {
                                 sprites[sprite_number].biba -= 2;
                                 sprites[sprite_number].width -= 32;
                                 sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                                 if (sprites[sprite_number].biba <= 0) sprites[sprite_number].active = 0;
                             }
                             else sprites[sprite_number].x_position = walls[wall_loop].x_position + 30;
                         }
                     }
                 }
             }
             
             else if (type == 301 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].y_speed > 0) sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height;
                      else sprites[sprite_number].y_position = walls[wall_loop].y_position + 20;
                      animation(sprite_number);
                 }
             }
             else if (type == 1002 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].x_speed > 0) sprites[sprite_number].x_position = walls[wall_loop].x_position - 50;
                          else sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                          sprites[sprite_number].x_speed = sprites[sprite_number].x_speed * -1;
                      }
                      else {
                          if (sprites[sprite_number].y_speed > 0) sprites[sprite_number].y_position = walls[wall_loop].y_position - 50;
                          else sprites[sprite_number].y_position = walls[wall_loop].y_position + 20;
                          sprites[sprite_number].y_speed *= -1;
                      }
                      play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
             }
             else if (type == 1003 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].biba == 1) {
                          if (sprites[sprite_number].x_speed > 0) sprites[sprite_number].x_position = walls[wall_loop].x_position - 50;
                          else sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                          sprites[sprite_number].x_speed = sprites[sprite_number].x_speed * -1;
                      }
                      else {
                          if (sprites[sprite_number].y_speed > 0) sprites[sprite_number].y_position = walls[wall_loop].y_position - 50;
                          else sprites[sprite_number].y_position = walls[wall_loop].y_position + 20;
                          sprites[sprite_number].y_speed *= -1;
                      }
                      play_sample((SAMPLE *)mydatafile[QUICAR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
             }
             
             else if (type == 10 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) { sprites[sprite_number].direction = 0; sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width; }
                      else  { sprites[sprite_number].direction = 1; sprites[sprite_number].x_position = walls[wall_loop].x_position + walls[wall_loop].width; }
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 50) / 20)][(int)(sprites[sprite_number].x_position / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)((sprites[sprite_number].x_position + 20) / 20));
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 50) / 20)][(int)((sprites[sprite_number].x_position + 40) / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)(sprites[sprite_number].x_position / 20));
                      noisiloc = 1;
                 }
             }
             else if (type == 41 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) { sprites[sprite_number].direction = 0; sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width; }
                      else  { sprites[sprite_number].direction = 1; sprites[sprite_number].x_position = walls[wall_loop].x_position + walls[wall_loop].width; }
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 50) / 20)][(int)(sprites[sprite_number].x_position / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)((sprites[sprite_number].x_position + 20) / 20));
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 50) / 20)][(int)((sprites[sprite_number].x_position + 40) / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)(sprites[sprite_number].x_position / 20));
                      noisiloc = 1;
                 }
             }
             else if (type == 42 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) { sprites[sprite_number].direction = 0; sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width; }
                      else  { sprites[sprite_number].direction = 1; sprites[sprite_number].x_position = walls[wall_loop].x_position + walls[wall_loop].width; }
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position - 10) / 20)][(int)(sprites[sprite_number].x_position / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)((sprites[sprite_number].x_position + 20) / 20));
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position - 10) / 20)][(int)((sprites[sprite_number].x_position + 40) / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)(sprites[sprite_number].x_position / 20));
                      noisiloc = 1;
                 }
             }
             else if (type == 43 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) { sprites[sprite_number].y_speed = 0; sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height; sprites[sprite_number].action_state = 2; sprites[sprite_number].timer = 0; sprites[sprite_number].x_position -= 9; sprites[sprite_number].y_position -= 1; sprites[sprite_number].frame = FIRE5; }
             }
             else if (type == 30 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) sprites[sprite_number].active = 0;
             }
             else if (type == 31 && (walls[wall_loop].type == 20 || walls[wall_loop].type == 11 || walls[wall_loop].type == 12 || walls[wall_loop].type == 10)) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].y_position >= walls[wall_loop].y_position) { sprites[sprite_number].y_position = walls[wall_loop].y_position + 20; sprites[sprite_number].y_speed = 0;}
                      else  { sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height; sprites[sprite_number].y_speed = 0; }
                      noisiloc = 1;
                 }
             }
             else if (type == 32 && (walls[wall_loop].type == 20 || walls[wall_loop].type == 11 || walls[wall_loop].type == 12 || walls[wall_loop].type == 10)) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].x_position >= walls[wall_loop].x_position) { sprites[sprite_number].x_position = walls[wall_loop].x_position + 20; sprites[sprite_number].x_speed = 0;}
                      else  { sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width; sprites[sprite_number].x_speed = 0; }
                      noisiloc = 1;
                 }
             }
             
             else if (type == 46 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (check_colision(sprite_number, wall_loop, 4)) {
                         int y = 0;
                         while ((y < sprites[sprite_number].y_speed - 2) && check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].y_position--;
                             y++;
                         }
                         if (check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].direction = 0;
                             sprites[sprite_number].action_state = 2;
                             sprites[sprite_number].timer = 0;
                             if (sprites[sprite_number].biba == 1) sprites[sprite_number].y_position = walls[wall_loop].y_position - 40;
                             else sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                         }
                     }
                 }
             }
             
             else if (type == 47 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (check_colision(sprite_number, wall_loop, 4)) {
                         int y = 0;
                         while ((y < sprites[sprite_number].y_speed - 2) && check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].y_position--;
                             y++;
                         }
                         if (check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].action_state = 2; sprites[sprite_number].timer = 0;
                             sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                             play_sample((SAMPLE *)mydatafile[HADUEX].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                         }
                     }
                 }
             }

             else if (type == 48 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (check_colision(sprite_number, wall_loop, 4)) {
                         int y = 0;
                         while ((y < sprites[sprite_number].y_speed - 2) && check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].y_position--;
                             y++;
                         }
                         if (check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].active = 0;
                         }
                     }
                 }
             }
             
             else if (type == 49 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (check_colision(sprite_number, wall_loop, 4)) {
                         int y = 0;
                         while ((y < sprites[sprite_number].y_speed - 2) && check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].y_position--;
                             y++;
                         }
                         if (check_colision(sprite_number, wall_loop, 4)) {
                             sprites[sprite_number].active = 0;
                         }
                     }
                 }
             }
             
             else if (type == 50 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) { sprites[sprite_number].direction = 0; sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width; }
                      else  { sprites[sprite_number].direction = 1; sprites[sprite_number].x_position = walls[wall_loop].x_position + walls[wall_loop].width; }
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 50) / 20)][(int)(sprites[sprite_number].x_position / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)((sprites[sprite_number].x_position + 20) / 20));
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 50) / 20)][(int)((sprites[sprite_number].x_position + 40) / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)(sprites[sprite_number].x_position / 20));
                      noisiloc = 1;
                 }
             }
             
             else if (type == 51 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height;
                     sprites[sprite_number].action_state = 2;
                     sprites[sprite_number].timer = 0;
                 }
             }
             
             else if (type == 64) {
                 if (check_colision(sprite_number, wall_loop, 2)) sprites[sprite_number].active = 0;
                 else if (sprites[sprite_number].x_position > Map.limitright) sprites[sprite_number].active = 0;                 
             }
             
             else if (type == 52 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     sprites[sprite_number].y_position = walls[wall_loop].y_position - sprites[sprite_number].height;
                     sprites[sprite_number].action_state = 2;
                     sprites[sprite_number].timer = 0;
                 }
             }
             
             else if (type == 54 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     sprites[sprite_number].active = 0;
                 }
             }
             
             else if (type == 55 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                      if (sprites[sprite_number].direction == 1) { sprites[sprite_number].direction = 0; sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width; }
                      else  { sprites[sprite_number].direction = 1; sprites[sprite_number].x_position = walls[wall_loop].x_position + walls[wall_loop].width; }
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 20) / 20)][(int)(sprites[sprite_number].x_position / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)((sprites[sprite_number].x_position + 20) / 20));
                      noisiloc = 1;
                 }
                 if (map[(int)((sprites[sprite_number].y_position + 20) / 20)][(int)((sprites[sprite_number].x_position + 20) / 20)] == '1') {
                      if (sprites[sprite_number].direction == 1) sprites[sprite_number].direction = 0;
                      else sprites[sprite_number].direction = 1;
                      sprites[sprite_number].x_position = 20 * ((int)(sprites[sprite_number].x_position / 20)) - 4;
                      noisiloc = 1;
                 }
             }
             
             else if (type == 56 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     sprites[sprite_number].active = 0;
                 }
             }
             
             else if (type == 1005 && walls[wall_loop].type == 20) {
                 if (check_colision(sprite_number, wall_loop, 2)) {
                     if (sprites[sprite_number].direction == 1) sprites[sprite_number].x_position = walls[wall_loop].x_position - sprites[sprite_number].width;
                     else sprites[sprite_number].x_position = walls[wall_loop].x_position + 20;
                     sprites[sprite_number].action_state++;
                     sprites[sprite_number].timer = 0;
                 }
             }
         }
          if (noisiloc == 1) { noisiloc = 0; break; }
     }
}

void player_colision() {
     int sprite_loop;
     for (sprite_loop = 0; sprite_loop < 100; sprite_loop++) {
         if (sprites[sprite_loop].active == 1 && (sprites[sprite_loop].type == 10 || sprites[sprite_loop].type == 11 || sprites[sprite_loop].type == 12 || sprites[sprite_loop].type == 13 || sprites[sprite_loop].type == 14 || sprites[sprite_loop].type == 15
          || sprites[sprite_loop].type == 200 || sprites[sprite_loop].type == 201 || sprites[sprite_loop].type == 999 || sprites[sprite_loop].type == 1000 || sprites[sprite_loop].type == 1001 || sprites[sprite_loop].type == 1002 || sprites[sprite_loop].type == 1003 || sprites[sprite_loop].type == 1010 || sprites[sprite_loop].type == 1011
          || sprites[sprite_loop].type == 17 || sprites[sprite_loop].type == 18 || sprites[sprite_loop].type == 19 || sprites[sprite_loop].type == 20 || sprites[sprite_loop].type == 21 || sprites[sprite_loop].type == 22 || sprites[sprite_loop].type == 23
          || sprites[sprite_loop].type == 24 || sprites[sprite_loop].type == 26 || sprites[sprite_loop].type == 29 || sprites[sprite_loop].type == 30 || sprites[sprite_loop].type == 32 || sprites[sprite_loop].type == 33 || sprites[sprite_loop].type == 34
          || sprites[sprite_loop].type == 35 || sprites[sprite_loop].type == 1004 || sprites[sprite_loop].type == 36 || sprites[sprite_loop].type == 39 || sprites[sprite_loop].type == 40 || sprites[sprite_loop].type == 41 || sprites[sprite_loop].type == 42
          || sprites[sprite_loop].type == 43 || sprites[sprite_loop].type == 44 || sprites[sprite_loop].type == 45 || sprites[sprite_loop].type == 46 || sprites[sprite_loop].type == 47 || sprites[sprite_loop].type == 48 || sprites[sprite_loop].type == 49 || sprites[sprite_loop].type == 74
          || sprites[sprite_loop].type == 50 || sprites[sprite_loop].type == 51 || sprites[sprite_loop].type == 52 || sprites[sprite_loop].type == 53 || sprites[sprite_loop].type == 54 || sprites[sprite_loop].type == 55 || sprites[sprite_loop].type == 56 || sprites[sprite_loop].type == 73
          || sprites[sprite_loop].type == 62 || sprites[sprite_loop].type == 1005 || sprites[sprite_loop].type == 1006 || sprites[sprite_loop].type == 1007 || sprites[sprite_loop].type == 69 || sprites[sprite_loop].type == 64 || sprites[sprite_loop].type == 202
          || sprites[sprite_loop].type == 72 || sprites[sprite_loop].type == 75 || sprites[sprite_loop].type == 77 || sprites[sprite_loop].type == 78 || sprites[sprite_loop].type == 79 || sprites[sprite_loop].type == 80 || sprites[sprite_loop].type == 1008)) {
             char col = 'p';
             if (sprites[sprite_loop].type == 53) {
             if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
             else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
             if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position > 80)) col = 'n';
             else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';
             }
             else {
             if (((int)sprites[sprite_loop].x_position > (int)player.x_position) && ((int)sprites[sprite_loop].x_position - (int)player.x_position >= 40)) col = 'n';
             else if (((int)sprites[sprite_loop].x_position <= (int)player.x_position) && ((int)player.x_position - (int)sprites[sprite_loop].x_position >= sprites[sprite_loop].width)) col = 'n';
             if (((int)sprites[sprite_loop].y_position > (int)player.y_position) && ((int)sprites[sprite_loop].y_position - (int)player.y_position >= 80)) col = 'n';
             else if (((int)sprites[sprite_loop].y_position <= (int)player.y_position) && ((int)player.y_position - (int)sprites[sprite_loop].y_position >= sprites[sprite_loop].height)) col = 'n';
             }
             if (col != 'n') {
                 if (sprites[sprite_loop].type == 1000) {
                     if (player.direction == 0) {
                     if (sprites[sprite_loop].direction == 0)
                         player.x_position = sprites[sprite_loop].x_position - 40;
                     set_dvalues(sprites[sprite_loop].timer);
                     stopall = 1;
                     sprites[sprite_loop].height = 0;
                     input_locked = 1;
                     screen_locked = 1;
                     movingscreen = 1;
                     looper = 1;
                     }
                     else {
                         player.x_speed = 0;
                         if (player.direction == 0) player.x_position = sprites[sprite_loop].x_position - 40;
                         else player.x_position = sprites[sprite_loop].x_position + 30;
                     }
                 }
                 else if (sprites[sprite_loop].type == 999) {
                     if (player.direction == 0) {
                     if (sprites[sprite_loop].direction == 0)
                         player.x_position = sprites[sprite_loop].x_position - 40;
                     set_dvalues(sprites[sprite_loop].timer);
                     stopall = 1;
                     sprites[sprite_loop].height = 0;
                     input_locked = 1;
                     screen_locked = 1;
                     movingscreen = 1;
                     looper = 1;
                     }
                     else {
                         player.x_speed = 0;
                         if (player.direction == 0) player.x_position = sprites[sprite_loop].x_position - 40;
                         else player.x_position = sprites[sprite_loop].x_position + 30;
                     }
                 }
                 else if (sprites[sprite_loop].type == 53) {
                     if (input_locked == 0) { damage(sprites[sprite_loop].strength); }
                 }   
                 else if (sprites[sprite_loop].type == 1010) {
                     stopall = 1; input_locked = 1; screen_locked = 1;
                     if (player.on_ground == FALSE) {
                         if (player.timer >= 0) player.timer = -1;
                         if (player.on_ground == FALSE && player.timer < 0) {
                             if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                             else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                             else if (player.timer < -20 && player.timer > -31) player.y_speed+=0.1;
                             if (player.y_speed <= 0) player.timer = 0;
                             else move_player(0, player.y_speed);
                         }
                     }
                     else {
                         stopall = 1; input_locked = 1; screen_locked = 1;
                         player.x_speed = 2; player.x_position += 2;
                         next_level += 1;
                         if (next_level == 40) {
                             current_level = sprites[sprite_loop].timer;
                             stopall = 1; input_locked = 1; screen_locked = 1;
                             next_level = 0; paulaumfromhell = 1; setup_game();
                         }
                     }   
                 }
                 else if (sprites[sprite_loop].type == 73) {
                     stopall = 1; input_locked = 1; screen_locked = 1;
                     if (player.on_ground == FALSE) {
                         if (player.timer >= 0) player.timer = -1;
                         if (player.on_ground == FALSE && player.timer < 0) {
                             if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                             else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                             else if (player.timer < -20 && player.timer > -31) player.y_speed+=0.1;
                             if (player.y_speed <= 0) player.timer = 0;
                             else move_player(0, player.y_speed);
                         }
                     }
                     else {
                         if (player.x_position + 10 > sprites[sprite_loop].x_position) {
                             stopall = 1; input_locked = 1; screen_locked = 1;
                             player.direction = 1; player.x_speed = -2; player.x_position -= 2;
                         }
                         else {
                             current_level = sprites[sprite_loop].biba;
                             stopall = 1; input_locked = 1; screen_locked = 1;
                             paulaumfromhell = 1;
                             lastagedoor = sprites[sprite_loop].biba - 73;
                             setup_game();
                             finishing = 0;
                         }
                     }   
                 }
                 else if (sprites[sprite_loop].type == 74) {
                     stopall = 1; input_locked = 1; screen_locked = 1;
                     if (player.on_ground == FALSE) {
                         if (player.timer >= 0) player.timer = -1;
                         if (player.on_ground == FALSE && player.timer < 0) {
                             if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                             else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                             else if (player.timer < -20 && player.timer > -31) player.y_speed+=0.1;
                             if (player.y_speed <= 0) player.timer = 0;
                             else move_player(0, player.y_speed);
                         }
                     }
                     else {
                         if (player.x_position + 30 < sprites[sprite_loop].x_position + 65) {
                             stopall = 1; input_locked = 1; screen_locked = 1;
                             player.direction = 0; player.x_speed = 2; player.x_position += 2;
                         }
                         else {
                             current_level = sprites[sprite_loop].biba;
                             stopall = 1; input_locked = 1; screen_locked = 1;
                             paulaumfromhell = 1;
                             lastagedoor = sprites[sprite_loop].biba - 73;
                             setup_game();
                             finishing = 0;
                         }
                     }   
                 }
                 else if (sprites[sprite_loop].type == 1011) {
                     call_event = sprites[sprite_loop].timer;
                     callevent(call_event);
                     sprites[sprite_loop].active = 0;
                 }   
                 else if (sprites[sprite_loop].type == 1007 && sprites[sprite_loop].frame == ICYUP03) {
                     if (sprites[sprite_loop].direction == 0) {
                         if (player.x_position > sprites[sprite_loop].x_position + 58 && player.y_position > sprites[sprite_loop].y_position + 57) continue;
                         else if (input_locked == 0) { damage(sprites[sprite_loop].strength); }
                     }
                     else if (sprites[sprite_loop].direction == 1) {
                         if (player.x_position + 40 < sprites[sprite_loop].x_position + 61 && player.y_position > sprites[sprite_loop].y_position + 57) continue;
                         else if (input_locked == 0) { damage(sprites[sprite_loop].strength); }
                     }
                 }
                 else if (sprites[sprite_loop].type == 1008) {
                     if (sprites[sprite_loop].biba >= 128) {
                         damage(sprites[sprite_loop].strength);
                     }
                 }
                 else if (sprites[sprite_loop].type == 46 && sprites[sprite_loop].action_state == 2) {
                         rest(1);
                 }
                 else if (sprites[sprite_loop].type == 69) {
                   if (sprites[sprite_loop].action_state != 3) {
                     sprites[sprite_loop].action_state = 3;
                     player.score++;
                     if (player.score == 10) { player.hpmax = 16; sparkmandril = 1; play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     else if (player.score == 20) { player.hpmax = 17; sparkmandril = 1; play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     else if (player.score == 30) { player.hpmax = 18; sparkmandril = 1; play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     else if (player.score == 40) { player.hpmax = 19; sparkmandril = 1; play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     else if (player.score == 52) { player.hpmax = 20; sparkmandril = 1; play_sample((SAMPLE *)mydatafile[SPARKLE].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     play_sample((SAMPLE *)mydatafile[CARDGET].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                   }
                 }
                 else if (sprites[sprite_loop].type == 202) {
                     sprites[sprite_loop].active = 0;
                     if (player.vidas < 9) player.vidas++;
                     play_sample((SAMPLE *)mydatafile[RECUPERATORS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
                 }
                 else if (sprites[sprite_loop].type == 75) {
                     if (input_locked == 0 && sprites[sprite_loop].biba == 255) damage(sprites[sprite_loop].strength);
                 }
                 else if (sprites[sprite_loop].type == 77) {
                     if (input_locked == 0 && sprites[sprite_loop].biba == 255) damage(sprites[sprite_loop].strength);
                 }
                 else if (sprites[sprite_loop].type == 78) {
                     if (input_locked == 0 && sprites[sprite_loop].biba == 255) damage(sprites[sprite_loop].strength);
                 }
                 else if (input_locked == 0) {
                     damage(sprites[sprite_loop].strength);
                     if (sprites[sprite_loop].type == 13) animation(sprite_loop);
                     else if (sprites[sprite_loop].type == 20) animation(sprite_loop);
                     else if (sprites[sprite_loop].type == 22) sprites[sprite_loop].active = 0;
                     else if (sprites[sprite_loop].type == 200) { sprites[sprite_loop].active = 0; play_sample((SAMPLE *)mydatafile[RECUPERATORS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     else if (sprites[sprite_loop].type == 201) { sprites[sprite_loop].active = 0; play_sample((SAMPLE *)mydatafile[RECUPERATORS].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); }
                     else if (sprites[sprite_loop].type == 46) { sprites[sprite_loop].active = 0; }
                     else if (sprites[sprite_loop].type == 47 && sprites[sprite_loop].action_state == 0) {
                         sprites[sprite_loop].action_state = 2; sprites[sprite_loop].timer = 0;
                         sprites[sprite_loop].x_position = player.x_position + 40;
                     }
                 }
             }
         }
     }
}
