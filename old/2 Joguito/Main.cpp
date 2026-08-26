#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <iostream>
#include <fstream.h>
#include <time.h>
#include "data.h"
#include "globals.h"
#include "sprite.h"
#include "colision.h"
#include "player.h"
#include "draw.h"
#include "scripts.h"
#include "menu.h"
#include "maps.h"

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

void load_map(char mapnumber) {
     
     if (mapnumber == 10) {
         Map.width = 450;
         Map.height = 28;
         Map.limitleft = 0;
         Map.limitright = 9000;
         Map.limitup = 0;
         Map.limitdown = 560;
         Map.number = 1;
         Map.startingpointx = 60;
         Map.startingpointy = 200;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [28];

         for(int i = 0; i < 28; i++)
             map[i] = new unsigned char[450];
         
         fmap = fopen("map10.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 11) {
         Map.width = 40;
         Map.height = 100;
         Map.limitleft = 0;
         Map.limitright = 800;
         Map.limitup = 0;
         Map.limitdown = 2000;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 60;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [100];

         for(int i = 0; i < 100; i++)
             map[i] = new unsigned char[40];
         
         fmap = fopen("map11.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 12) {
         Map.width = 420;
         Map.height = 30;
         Map.limitleft = 0;
         Map.limitright = 8400;
         Map.limitup = 0;
         Map.limitdown = 600;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 400;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [30];

         for(int i = 0; i < 30; i++)
             map[i] = new unsigned char[420];
         
         fmap = fopen("map12.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 13) {
         Map.width = 40;
         Map.height = 90;
         Map.limitleft = 0;
         Map.limitright = 800;
         Map.limitup = 0;
         Map.limitdown = 1800;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 1680;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [90];

         for(int i = 0; i < 90; i++)
             map[i] = new unsigned char[40];
         
         fmap = fopen("map13.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 14) {
         Map.width = 200;
         Map.height = 28;
         Map.limitleft = 0;
         Map.limitright = 2150;
         Map.limitup = 0;
         Map.limitdown = 560;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 380;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [28];

         for(int i = 0; i < 28; i++)
             map[i] = new unsigned char[200];
         
         fmap = fopen("map14.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 20) {
         Map.width = 100;
         Map.height = 24;
         Map.limitleft = 0;
         Map.limitright = 2000;
         Map.limitup = 0;
         Map.limitdown = 480;
         Map.number = 0;
         Map.startingpointx = 40;
         Map.startingpointy = 260;
         Map.water_position = 0;
         Map.type = 1;
         Map.number = 1;
         map = new unsigned char* [24];

         for(int i = 0; i < 24; i++)
             map[i] = new unsigned char[100];
         
         fmap = fopen("map20.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 21) {
         Map.width = 210;
         Map.height = 28;
         Map.limitleft = 0;
         Map.limitright = 4200;
         Map.limitup = 0;
         Map.limitdown = 560;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 300;
         Map.water_position = 0;
         Map.type = 0;
         map = new unsigned char* [28];

         for(int i = 0; i < 28; i++)
             map[i] = new unsigned char[210];
         
         fmap = fopen("map21.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 22) {
         Map.width = 120;
         Map.height = 70;
         Map.limitleft = 0;
         Map.limitright = 2400;
         Map.limitup = 0;
         Map.limitdown = 1400;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 120;
         Map.water_position = 0;
         Map.type = 0;
         map = new unsigned char* [70];

         for(int i = 0; i < 70; i++)
             map[i] = new unsigned char[120];
         
         fmap = fopen("map22.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 23) {
         Map.width = 300;
         Map.height = 36;
         Map.limitleft = 0;
         Map.limitright = 4730;
         Map.limitup = 0;
         Map.limitdown = 720;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 440;
         Map.water_position = 0;
         Map.type = 0;
         map = new unsigned char* [36];

         for(int i = 0; i < 36; i++)
             map[i] = new unsigned char[300];
         
         fmap = fopen("map23.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 30) {
         Map.width = 500;
         Map.height = 30;
         Map.limitleft = 0;
         Map.limitright = 10000;
         Map.limitup = 0;
         Map.limitdown = 600;
         Map.number = 1;
         Map.startingpointx = 60;
         Map.startingpointy = 400;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [30];

         for(int i = 0; i < 30; i++)
             map[i] = new unsigned char[500];
         
         fmap = fopen("map30.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 31) {
         Map.width = 100;
         Map.height = 80;
         Map.limitleft = 0;
         Map.limitright = 2000;
         Map.limitup = 0;
         Map.limitdown = 1600;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 140;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [80];

         for(int i = 0; i < 80; i++)
             map[i] = new unsigned char[100];
         
         fmap = fopen("map31.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 32) {
         Map.width = 300;
         Map.height = 32;
         Map.limitleft = 0;
         Map.limitright = 4750;
         Map.limitup = 0;
         Map.limitdown = 640;
         Map.number = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 320;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [32];

         for(int i = 0; i < 32; i++)
             map[i] = new unsigned char[300];
         
         fmap = fopen("map32.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 40) {
         Map.width = 450;
         Map.height = 40;
         Map.limitleft = 0;
         Map.limitright = 9000;
         Map.limitup = 0;
         Map.limitdown = 800;
         Map.number = 1;
         Map.water_position = 420;
         Map.startingpointx = 380;
         Map.startingpointy = 220;
         Map.type = 3;
         map = new unsigned char* [40];

         for(int i = 0; i < 40; i++)
             map[i] = new unsigned char[450];
         
         fmap = fopen("map40.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 41) {
         Map.width = 450;
         Map.height = 40;
         Map.limitleft = 0;
         Map.limitright = 9000;
         Map.limitup = 0;
         Map.limitdown = 800;
         Map.number = 0;
         Map.water_position = 200;
         Map.startingpointx = 0;
         Map.startingpointy = 320;
         Map.type = 3;
         map = new unsigned char* [40];

         for(int i = 0; i < 40; i++)
             map[i] = new unsigned char[450];
         
         fmap = fopen("map41.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 42) {
         Map.width = 500;
         Map.height = 40;
         Map.limitleft = 0;
         Map.limitright = 8750;
         Map.limitup = 0;
         Map.limitdown = 800;
         Map.number = 0;
         Map.water_position = 300;
         Map.startingpointx = 0;
         Map.startingpointy = 260;
         Map.type = 3;
         map = new unsigned char* [40];

         for(int i = 0; i < 40; i++)
             map[i] = new unsigned char[500];
         
         fmap = fopen("map42.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 50) {
         Map.width = 40;
         Map.height = 80;
         Map.limitleft = 0;
         Map.limitright = 800;
         Map.limitup = 0;
         Map.limitdown = 1600;
         Map.number = 1;
         Map.water_position = 0;
         Map.startingpointx = 40;
         Map.startingpointy = 100;
         Map.type = 1;
         map = new unsigned char* [80];

         for(int i = 0; i < 80; i++)
             map[i] = new unsigned char[40];
         
         fmap = fopen("map50.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 51) {
         Map.width = 360;
         Map.height = 36;
         Map.limitleft = 0;
         Map.limitright = 7200;
         Map.limitup = 0;
         Map.limitdown = 720;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 340;
         Map.type = 1;
         map = new unsigned char* [36];

         for(int i = 0; i < 36; i++)
             map[i] = new unsigned char[360];
         
         fmap = fopen("map51.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 52) {
         Map.width = 60;
         Map.height = 80;
         Map.limitleft = 0;
         Map.limitright = 1200;
         Map.limitup = 0;
         Map.limitdown = 1600;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 1420;
         Map.type = 1;
         map = new unsigned char* [80];

         for(int i = 0; i < 80; i++)
             map[i] = new unsigned char[60];
         
         fmap = fopen("map52.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 53) {
         Map.width = 300;
         Map.height = 120;
         Map.limitleft = 0;
         Map.limitright = 6000;
         Map.limitup = 0;
         Map.limitdown = 2400;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 140;
         Map.type = 1;
         map = new unsigned char* [120];

         for(int i = 0; i < 120; i++)
             map[i] = new unsigned char[300];
         
         fmap = fopen("map53.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 60) {
         Map.width = 400;
         Map.height = 34;
         Map.limitleft = 0;
         Map.limitright = 8000;
         Map.limitup = 0;
         Map.limitdown = 680;
         Map.number = 1;
         Map.water_position = 0;
         Map.startingpointx = 60;
         Map.startingpointy = 160;
         Map.type = 1;
         map = new unsigned char* [34];

         for(int i = 0; i < 34; i++)
             map[i] = new unsigned char[400];
         
         fmap = fopen("map60.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 61) {
         Map.width = 400;
         Map.height = 50;
         Map.limitleft = 0;
         Map.limitright = 8000;
         Map.limitup = 0;
         Map.limitdown = 1000;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 740;
         Map.type = 1;
         map = new unsigned char* [50];

         for(int i = 0; i < 50; i++)
             map[i] = new unsigned char[400];
         
         fmap = fopen("map61.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 62) {
         Map.width = 200;
         Map.height = 60;
         Map.limitleft = 0;
         Map.limitright = 4000;
         Map.limitup = 0;
         Map.limitdown = 1200;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 140;
         Map.type = 1;
         map = new unsigned char* [60];

         for(int i = 0; i < 60; i++)
             map[i] = new unsigned char[200];
         
         fmap = fopen("map62.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 70) {
         Map.width = 500;
         Map.height = 36;
         Map.limitleft = 0;
         Map.limitright = 10000;
         Map.limitup = 0;
         Map.limitdown = 720;
         Map.number = 1;
         Map.water_position = 0;
         Map.startingpointx = 100;
         Map.startingpointy = 460;
         Map.type = 1;
         map = new unsigned char* [36];

         for(int i = 0; i < 36; i++)
             map[i] = new unsigned char[500];
         
         fmap = fopen("map70.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 71) {
         Map.width = 500;
         Map.height = 40;
         Map.limitleft = 0;
         Map.limitright = 10000;
         Map.limitup = 0;
         Map.limitdown = 800;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 280;
         Map.type = 1;
         map = new unsigned char* [40];

         for(int i = 0; i < 40; i++)
             map[i] = new unsigned char[500];
         
         fmap = fopen("map71.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 72) {
         Map.width = 750;
         Map.height = 40;
         Map.limitleft = 0;
         Map.limitright = 15000;
         Map.limitup = 0;
         Map.limitdown = 800;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 480;
         Map.type = 1;
         map = new unsigned char* [40];

         for(int i = 0; i < 40; i++)
             map[i] = new unsigned char[750];
         
         fmap = fopen("map72.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 73) {
         Map.width = 150;
         Map.height = 80;
         Map.limitleft = 0;
         Map.limitright = 3000;
         Map.limitup = 0;
         Map.limitdown = 1600;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 0;
         Map.startingpointy = 240;
         if (lastagedoor == 1) { 
             Map.number = 1;
             Map.startingpointx = 100; Map.startingpointy = 1160;
	   }
         else if (lastagedoor == 2) { 
             Map.number = 1;
             Map.startingpointx = 580; Map.startingpointy = 1280;
	   }
         else if (lastagedoor == 3) { 
             Map.number = 1;
             Map.startingpointx = 1180; Map.startingpointy = 1480;
	   }
         else if (lastagedoor == 4) { 
             Map.number = 1;
             Map.startingpointx = 1828; Map.startingpointy = 1480;
	   }
         else if (lastagedoor == 5) { 
             Map.number = 1;
             Map.startingpointx = 2428; Map.startingpointy = 1280;
	   }
         else if (lastagedoor == 6) { 
             Map.number = 1;
             Map.startingpointx = 2908; Map.startingpointy = 1160;
	   }
         Map.type = 1;
         map = new unsigned char* [80];

         for(int i = 0; i < 80; i++)
             map[i] = new unsigned char[150];
         
         fmap = fopen("map73.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 74) {
         Map.width = 200;
         Map.height = 60;
         Map.limitleft = 3320;
         Map.limitright = 3960;
         Map.limitup = 720;
         Map.limitdown = 1200;
         Map.number = 1;
         Map.water_position = 0;
         Map.startingpointx = 3620;
         Map.startingpointy = 1020;
         Map.type = 1;
         map = new unsigned char* [60];

         for(int i = 0; i < 60; i++)
             map[i] = new unsigned char[200];
         
         fmap = fopen("map74.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 75) {
         Map.width = 200;
         Map.height = 28;
         Map.limitleft = 2740;
         Map.limitright = 4000;
         Map.limitup = 0;
         Map.limitdown = 560;
         Map.number = 1;
         Map.startingpointx = 3380;
         Map.startingpointy = 300;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [28];

         for(int i = 0; i < 28; i++)
             map[i] = new unsigned char[200];
         
         fmap = fopen("map75.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 76) {
         Map.width = 300;
         Map.height = 36;
         Map.limitleft = 5320;
         Map.limitright = 5960;
         Map.limitup = 120;
         Map.limitdown = 600;
         Map.number = 1;
         Map.startingpointx = 5500;
         Map.startingpointy = 460;
         Map.water_position = 0;
         Map.type = 0;
         map = new unsigned char* [36];

         for(int i = 0; i < 36; i++)
             map[i] = new unsigned char[300];
         
         fmap = fopen("map76.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 77) {
         Map.width = 300;
         Map.height = 32;
         Map.limitleft = 5280;
         Map.limitright = 5920;
         Map.limitup = 160;
         Map.limitdown = 640;
         Map.number = 1;
         Map.startingpointx = 5400;
         Map.startingpointy = 400;
         Map.water_position = 0;
         Map.type = 1;
         map = new unsigned char* [32];

         for(int i = 0; i < 32; i++)
             map[i] = new unsigned char[300];
         
         fmap = fopen("map77.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 78) {
         Map.width = 500;
         Map.height = 40;
         Map.limitleft = 9320;
         Map.limitright = 9960;
         Map.limitup = 260;
         Map.limitdown = 740;
         Map.number = 1;
         Map.water_position = 300;
         Map.startingpointx = 9500;
         Map.startingpointy = 560;
         Map.type = 3;
         map = new unsigned char* [40];

         for(int i = 0; i < 40; i++)
             map[i] = new unsigned char[500];
         
         fmap = fopen("map78.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 79) {
         Map.width = 300;
         Map.height = 120;
         Map.limitleft = 5280;
         Map.limitright = 5920;
         Map.limitup = 1920;
         Map.limitdown = 2400;
         Map.number = 1;
         Map.water_position = 0;
         Map.startingpointx = 5400;
         Map.startingpointy = 2220;
         Map.type = 1;
         map = new unsigned char* [120];

         for(int i = 0; i < 120; i++)
             map[i] = new unsigned char[300];
         
         fmap = fopen("map79.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     else if (mapnumber == 80) {
         Map.width = 125;
         Map.height = 30;
         Map.limitleft = 840;
         Map.limitright = 1660;
         Map.limitup = 0;
         Map.limitdown = 600;
         Map.number = 1;
         Map.water_position = 0;
         Map.startingpointx = 930;
         Map.startingpointy = 260;
         Map.type = 1;
         map = new unsigned char* [30];

         for(int i = 0; i < 30; i++)
             map[i] = new unsigned char[125];
         
         fmap = fopen("map80.map", "rb");
         char mychar = ' ';

         for(int i = 0; i < Map.height; i++) {
             for(int j = 0; j < Map.width; j++) {
                 do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (j == 0 && i != 0) do { mychar = getc(fmap); } while (mychar == ' ' || mychar == '\n'/*mychar != 1 && mychar != 2 && mychar != 3 && mychar != 4 && mychar != 5 && mychar != 6 && mychar != 7 && mychar != 8 && mychar != 9 && mychar != 0 && mychar != 'a' && mychar != 'b' && mychar != 'c' && mychar != 'd' && mychar != 'e' && mychar != 'f' && mychar != 'g' && mychar != 'h' && mychar != 'i' && mychar != 'j' && mychar != 'k' && mychar != 'l'*/);
                 if (mychar != EOF) map[i][j] = mychar;
             }
         }
         
         fclose(fmap);

     }
     
}

void setup_game(){
    if (buffer != 0) destroy_bitmap(buffer);
    if (background != 0) destroy_bitmap(background);
    if (scenario != 0) destroy_bitmap(scenario);
    if (bakg != 0) destroy_bitmap(bakg);
    doorrecord = -1;
    create_bubbles = 0;
    
    if (current_level == 10) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(3000, 580);
       scenario = create_bitmap( 9000, 580);
       buffer = create_bitmap( 640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, 0, 0);
       draw_sprite(background, bakg, 1000, 0);
       draw_sprite(background, bakg, 2000, 0);
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Tek.mid");
       dead = 1;
       initiate_level(10);
    }
    else if (current_level == 11) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(800, 1400);
       scenario = create_bitmap( 800, 2000);
       buffer = create_bitmap( 640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, 0, 0);
       draw_sprite(background, bakg, 0, 520);
       draw_sprite(background, bakg, 0, 1040);
       dead = 1;
       initiate_level(11);
    }
    else if (current_level == 12) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(3000, 600);
       scenario = create_bitmap( 8400, 600);
       buffer = create_bitmap( 640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, 0, 80);
       draw_sprite(background, bakg, 1000, 80);
       draw_sprite(background, bakg, 2000, 80);
       dead = 1;
       initiate_level(12);
    }
    else if (current_level == 13) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(800, 1400);
       scenario = create_bitmap( 800, 1800);
       buffer = create_bitmap( 640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, 0, 0);
       draw_sprite(background, bakg, 0, 520);
       draw_sprite(background, bakg, 0, 1040);
       dead = 1;
       initiate_level(13);
    }
    else if (current_level == 14) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(3000, 560);
       scenario = create_bitmap( 4000, 560);
       buffer = create_bitmap( 640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, 0, 0);
       draw_sprite(background, bakg, 1000, 0);
       draw_sprite(background, bakg, 2000, 20);
       dead = 1;
       initiate_level(14);
    }
    else if (current_level == 20) {
       bakg = load_bitmap("bg3.bmp", NULL);
       background = create_bitmap(2000, 480);
       scenario = create_bitmap(2000, 480);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(56,72,96));
       draw_sprite(background, bakg, 0, 0);
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Wkn.mid");
       dead = 1;
       initiate_level(20);
    }
    else if (current_level == 21) {
       //bakg = load_bitmap("bg3.bmp", NULL);
       //background = create_bitmap(4200, 560);
       scenario = create_bitmap(4200, 560);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       //clear_to_color(background, makecol(56,72,96));
       //draw_sprite(background, bakg, 0, 0);
       dead = 1;
       initiate_level(21);
    }
    else if (current_level == 22) {
       scenario = create_bitmap(2400, 1400);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       dead = 1;
       initiate_level(22);
    }
    else if (current_level == 23) {
       scenario = create_bitmap(6000, 720);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       dead = 1;
       initiate_level(23);
    }
    else if (current_level == 30) {
       bakg = load_bitmap("bg4.bmp", NULL);
       background = create_bitmap(3000, 600);
       scenario = create_bitmap(10000, 600);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(15,0,0));
       draw_sprite(background, bakg, 0, 60);
       draw_sprite(background, bakg, 608, 60);
       draw_sprite(background, bakg, 1216, 60);
       draw_sprite(background, bakg, 1824, 60);
       draw_sprite(background, bakg, 2432, 60);
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Emr.mid");
       dead = 1;
       initiate_level(30);
    }
    else if (current_level == 31) {
       bakg = load_bitmap("bg4.bmp", NULL);
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
       dead = 1;
       initiate_level(31);
    }
    else if (current_level == 32) {
       bakg = load_bitmap("bg4.bmp", NULL);
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
       dead = 1;
       initiate_level(32);
    }
    else if (current_level == 40) {
       bakg = load_bitmap("bg5.bmp", NULL);
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
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Ask.mid");
       dead = 1;
       initiate_level(40);
    }
    else if (current_level == 41) {
       bakg = load_bitmap("bg5.bmp", NULL);
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
       dead = 1;
       initiate_level(41);
    }
    else if (current_level == 42) {
       bakg = load_bitmap("bg5.bmp", NULL);
       background = create_bitmap(3000, 800);
       scenario = create_bitmap(10000, 800);
       foreground = create_bitmap(10000, 800);
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
       dead = 1;
       initiate_level(42);
    }
    else if (current_level == 50) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(800, 1600);
       scenario = create_bitmap(800, 1600);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, -100, 0);
       draw_sprite(background, bakg, -100, 520);
       draw_sprite(background, bakg, -100, 1040);
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Ce.mid");
       dead = 1;
       initiate_level(50);
    }
    else if (current_level == 51) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(7200, 720);
       scenario = create_bitmap(7200, 720);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(48,16,31));
       draw_sprite(background, bakg, -600, 0);
       dead = 1;
       initiate_level(51);
    }
    else if (current_level == 52) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(1200, 1600);
       scenario = create_bitmap(1200, 1600);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(48,16,31));
       draw_sprite(background, bakg, 0, -80);
       dead = 1;
       initiate_level(52);
    }
    else if (current_level == 53) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(6000, 2400);
       scenario = create_bitmap(6000, 2400);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(48,16,31));
       dead = 1;
       initiate_level(53);
    }
    else if (current_level == 60) {
       bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(8000, 680);
       scenario = create_bitmap(8000, 680);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(111,200,239));
       draw_sprite(background, bakg, 0, 0);
       draw_sprite(background, bakg, 640, 0);
       draw_sprite(background, bakg, 1280, 0);
       draw_sprite(background, bakg, 1920, 0);
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Myk.mid");
       dead = 1;
       initiate_level(60);
    }
    else if (current_level == 61) {
       bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(8000, 1000);
       scenario = create_bitmap(8000, 1000);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(111,200,239));
       draw_sprite(background, bakg, 640, -20);
       draw_sprite(background, bakg, 1280, -20);
       draw_sprite(background, bakg, 1920, -20);
       draw_sprite(background, bakg, 2560, -20);
       dead = 1;
       initiate_level(61);
    }
    else if (current_level == 62) {
       bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(4000, 1200);
       scenario = create_bitmap(4000, 1200);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(0,16,63));
       dead = 1;
       initiate_level(62);
    }
    else if (current_level == 70) {
       bakg = load_bitmap("bg7.bmp", NULL);
       background = create_bitmap(10000, 720);
       scenario = create_bitmap(10000, 720);
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
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Rrk.mid");
       dead = 1;
       initiate_level(70);
    }
    else if (current_level == 71) {
       bakg = load_bitmap("bg7.bmp", NULL);
       background = create_bitmap(10000, 800);
       scenario = create_bitmap(10000, 800);
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
       dead = 1;
       initiate_level(71);
    }
    else if (current_level == 72) {
       bakg = load_bitmap("bg7.bmp", NULL);
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
       dead = 1;
       initiate_level(72);
    }
    else if (current_level == 73) {
       bakg = load_bitmap("bg7.bmp", NULL);
       background = create_bitmap(3000, 1600);
       scenario = create_bitmap(3000, 1600);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(0,0,0));
       draw_sprite(background, bakg, 0, 100);
       draw_sprite(background, bakg, 640, 100);
       draw_sprite(background, bakg, 1280, 100);
       dead = 1;
       initiate_level(73);
    }
    else if (current_level == 74) {
       bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(4000, 1200);
       scenario = create_bitmap(4000, 1200);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(0,16,63));
       dead = 1;
       initiate_level(74);
    }
    else if (current_level == 75) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(3000, 560);
       scenario = create_bitmap( 4000, 560);
       buffer = create_bitmap( 640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(47,128,255));
       draw_sprite(background, bakg, 0, 0);
       draw_sprite(background, bakg, 1000, 0);
       draw_sprite(background, bakg, 2000, 20);
       dead = 1;
       initiate_level(75);
    }
    else if (current_level == 76) {
       scenario = create_bitmap(6000, 720);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       dead = 1;
       initiate_level(76);
    }
    else if (current_level == 77) {
       bakg = load_bitmap("bg4.bmp", NULL);
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
       dead = 1;
       initiate_level(77);
    }
    else if (current_level == 78) {
       bakg = load_bitmap("bg5.bmp", NULL);
       background = create_bitmap(3000, 800);
       scenario = create_bitmap(10000, 800);
       foreground = create_bitmap(10000, 800);
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
       dead = 1;
       initiate_level(78);
    }
    else if (current_level == 79) {
       bakg = load_bitmap("bg.bmp", NULL);
       background = create_bitmap(6000, 2400);
       scenario = create_bitmap(6000, 2400);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(48,16,31));
       dead = 1;
       initiate_level(79);
    }
    else if (current_level == 80) {
       bakg = load_bitmap("bg8.bmp", NULL);
       background = create_bitmap(2500, 600);
       scenario = create_bitmap(2500, 600);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(20,15,60));
       draw_sprite(background, bakg, 865, 0);
       //draw_sprite(background, bakg, 640, 0);
       //draw_sprite(background, bakg, 1280, 0);
       //draw_sprite(background, bakg, 1920, 0);
       if (stage_music != NULL) destroy_midi(stage_music);
       stage_music = load_midi("Omoide.mid");
       dead = 1;
       initiate_level(80);
    }

}

void die() {
     bframe = PDIE1;
     input_locked = 1;
     screen_locked = 1;
     player.frame = NULO;
     player.imune = 0;
     dieanimation = 1;
     int x = (int)player.x_position;
     int y = (int)player.y_position;
     bolas[0][0] = x + 7; bolas[0][1] = y + 5;
     bolas[1][0] = x + 12; bolas[1][1] = y + 10;
     bolas[2][0] = x + 17; bolas[2][1] = y + 17;
     bolas[3][0] = x + 12; bolas[3][1] = y + 24;
     bolas[4][0] = x + 7; bolas[4][1] = y + 29;
     bolas[5][0] = x; bolas[5][1] = y + 34;
     bolas[6][0] = x - 7; bolas[6][1] = y + 29;
     bolas[7][0] = x - 12; bolas[7][1] = y + 24;
     bolas[8][0] = x - 17; bolas[8][1] = y + 17;
     bolas[9][0] = x - 12; bolas[9][1] = y + 10;
     bolas[10][0] = x - 7; bolas[10][1] = y + 5;
     bolas[11][0] = x; bolas[11][1] = y;
}

void damage(int howmuch) {
     if (howmuch < 0 || player.imune == 0) {
         player.hp = player.hp - howmuch;
         if (howmuch > 0) player.imune = 40;
         if (player.hp > player.hpmax) player.hp = player.hpmax;
         else if (player.hp <= 0) { player.hp = 0; dead = 1; }
     }
}

void set_dvalues(int number) {
     if (number == 0) {
         Map.limitleft = 2120;
         Map.limitright = 2760;
         Map.limitup = 0;
         Map.limitdown = 560;
         Map.startingpointx = 2300;
         Map.startingpointy = 300;
         Map.number = 1;
         doorrecord = 0;
     }
     else if (number == 1) {
         Map.limitleft = 2740;
         Map.limitright = 4000;
         Map.limitup = 0;
         Map.limitdown = 560;
         doorrecord = 1;
     }
     else if (number == 2) {
         Map.limitleft = 4700;
         Map.limitright = 5340;
         Map.limitup = 140;
         Map.limitdown = 620;
         Map.startingpointx = 4840;
         Map.startingpointy = 460;
         Map.number = 1;
         doorrecord = 2;
     }
     else if (number == 3) {
         Map.limitleft = 5320;
         Map.limitright = 5960;
         Map.limitup = 140;
         Map.limitdown = 620;
         doorrecord = 3;
     }
     else if (number == 4) {
         Map.limitleft = 4720;
         Map.limitright = 5360;
         Map.limitup = 160;
         Map.limitdown = 640;
         Map.startingpointx = 4840;
         Map.startingpointy = 400;
         Map.number = 1;
         doorrecord = number;
     }
     else if (number == 5) {
         Map.limitleft = 5280;
         Map.limitright = 5920;
         Map.limitup = 160;
         Map.limitdown = 640;
         doorrecord = number;
     }
     else if (number == 6) {
         Map.limitleft = 8720;
         Map.limitright = 9360;
         Map.limitup = 280;
         Map.limitdown = 760;
         Map.startingpointx = 8800;
         Map.startingpointy = 560;
         Map.number = 1;
         doorrecord = number;
     }
     else if (number == 7) {
         Map.limitleft = 9330;
         Map.limitright = 9970;
         Map.limitup = 280;
         Map.limitdown = 760;
         doorrecord = number;
     }
     else if (number == 8) {
         Map.startingpointx = 5160;
         Map.startingpointy = 1340;
         Map.number = 1;
         doorrecord = number;
     }
     else if (number == 9) {
         Map.limitleft = 5280;
         Map.limitright = 5920;
         Map.limitup = 1920;
         Map.limitdown = 2400;
         doorrecord = number;
     }
     else if (number == 10) {
         Map.limitleft = 2740;
         Map.limitright = 3380;
         Map.limitup = 720;
         Map.limitdown = 1200;
         Map.startingpointx = 2940;
         Map.startingpointy = 1020;
         Map.number = 1;
         doorrecord = number;
     }
     else if (number == 11) {
         Map.limitleft = 3310;
         Map.limitright = 3950;
         Map.limitup = 720;
         Map.limitdown = 1200;
         doorrecord = number;
     }
     else if (number == 12) {
         Map.limitright = 2770;
         doorrecord = number;
     }
}

void callevent(int event_number) {
     if (event_number == 1) {
         if (event_organizer == 0) {
             input_locked = 1;
             if (300 - (int)player.y_position >= 10) player.y_position += 10;
             else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 10) player.y_position = 300;
             else {
                 player.y_position = 300;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 5;
                 player.x_position += 5;
                 event_organizer++;
             }
         }
         else if (event_organizer == 75) {
              player.x_speed = 0;
              int a = 10;
              for (int sprite_loop = 0; sprite_loop < 100; sprite_loop++) {
                  if (sprites[sprite_loop].type == 2000) {
                      sprites[sprite_loop].timer = a; a -= 2; }
                  if (sprites[sprite_loop].type == 2001) {
                      sprites[sprite_loop].timer = a; a -= 2; }
              }
              event_organizer++;
         }
         else if (event_organizer < 75) { player.x_speed = 5; player.x_position += 5; event_organizer++; }
         else if (event_organizer > 75 && event_organizer < 105) event_organizer++;
         else if (event_organizer == 105) { initialize_sprite(1001, 3180, -100, 0, 105); event_organizer = 200; }
         else if (event_organizer >= 106 && event_organizer < 136) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 136)  { event_organizer = 0; call_event = 0; bossfight = 1;}
     }
     else if (event_number == 13) {
          if (event_organizer == 0) {
             input_locked = 1;
             if (300 - (int)player.y_position >= 10) player.y_position += 10;
             else if (300 - (int)player.y_position > 0 && 300 - (int)player.y_position < 10) player.y_position = 300;
             else {
                 player.y_position = 300;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 0;
                 event_organizer++;
             }
         }
         else if (event_organizer == 1) {
             if (player.cards[0] == 1) {
                 input_locked = 1;
                 finishing = 1;
             }
             else { input_locked = 0; }
             event_organizer = 0;
             call_event = 0;
         }
     }
     else if (event_number == 2) {
          if (event_organizer == 0) {
             input_locked = 1;
             if (460 - (int)player.y_position >= 10) player.y_position += 10;
             else if (460 - (int)player.y_position > 0 && 460 - (int)player.y_position < 10) player.y_position = 460;
             else {
                 player.y_position = 460;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 0;
                 event_organizer++;
             }
         }
         else if (event_organizer == 1) {
             if (player.cards[1] == 1) {
                 input_locked = 1;
                 finishing = 1;
             }
             else { input_locked = 0; }
             event_organizer = 0;
             call_event = 0;
         }
     }
     else if (event_number == 3) {
         if (event_organizer == 0) {
             input_locked = 1;
             if (460 - (int)player.y_position >= 10) player.y_position += 10;
             else if (460 - (int)player.y_position > 0 && 460 - (int)player.y_position < 10) player.y_position = 460;
             else {
                 player.y_speed = 0;
                 player.timer = 0;
                 player.y_position = 460;
                 player.on_ground = TRUE;
                 player.x_speed = 5;
                 player.x_position += 5;
                 event_organizer++;
             }
         }
         else if (event_organizer == 45) {
              player.x_speed = 0;
         }
         else if (event_organizer < 45) { player.x_speed = 5; player.x_position += 5; event_organizer++; }
         else if (event_organizer >= 106 && event_organizer < 136) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 136)  { event_organizer = 0; call_event = 0; bossfight = 1;}
     }
     else if (event_number == 4) {
          if (event_organizer == 0) {
             input_locked = 1;
             if (400 - (int)player.y_position >= 10) player.y_position += 10;
             else if (400 - (int)player.y_position > 0 && 400 - (int)player.y_position < 10) player.y_position = 400;
             else {
                 player.y_position = 400;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 0;
                 event_organizer++;
             }
         }
         else if (event_organizer == 1) {
             if (player.cards[2] == 1) {
                 input_locked = 1;
                 finishing = 1;
             }
             else { input_locked = 0; }
             event_organizer = 0;
             call_event = 0;
         }
     }
     else if (event_number == 5) {
         if (event_organizer == 0) {
             input_locked = 1;
             if (400 - (int)player.y_position >= 10) player.y_position += 10;
             else if (400 - (int)player.y_position > 0 && 400 - (int)player.y_position < 10) player.y_position = 400;
             else {
                 player.y_speed = 0;
                 player.timer = 0;
                 player.y_position = 400;
                 player.on_ground = TRUE;
                 player.x_speed = 5;
                 player.x_position += 5;
                 event_organizer++;
             }
         }
         else if (event_organizer == 40) {
              player.x_speed = 0;
              event_organizer++;
         }
         else if (event_organizer < 40) { player.x_speed = 5; player.x_position += 5; event_organizer++; }
         else if (event_organizer > 40 && event_organizer < 57) event_organizer++;
         else if (event_organizer == 57) { initialize_sprite(27, 5750, 160, 0, 0); event_organizer++; }
         else if (event_organizer > 57 && event_organizer < 60) event_organizer++;
         else if (event_organizer == 60) { flash_screen = 1; event_organizer++; }
         else if (event_organizer == 61) { flash_screen = 2; event_organizer++; initialize_sprite(1004, 5720, 411, 0, 0); }
         else if (event_organizer == 62) { flash_screen = 1; event_organizer++; }
         else if (event_organizer == 63) { flash_screen = 0; event_organizer++; }
         else if (event_organizer > 63 && event_organizer < 68) event_organizer++;
         else if (event_organizer >= 68 && event_organizer < 98) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 98)  { event_organizer = 0; call_event = 0; bossfight = 1;}
     }
     else if (event_number == 6) {
          if (event_organizer == 0) {
             input_locked = 1;
             if (560 - (int)player.y_position >= 10) player.y_position += 10;
             else if (560 - (int)player.y_position > 0 && 560 - (int)player.y_position < 10) player.y_position = 560;
             else {
                 player.y_position = 560;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 0;
                 event_organizer++;
             }
         }
         else if (event_organizer == 1) {
             if (player.cards[3] == 1) {
                 input_locked = 1;
                 finishing = 1;
             }
             else { input_locked = 0; }
             event_organizer = 0;
             call_event = 0;
         }
     }
     else if (event_number == 7) {
         if (event_organizer == 0) {
             input_locked = 1;
             if (560 - (int)player.y_position >= 10) player.y_position += 10;
             else if (560 - (int)player.y_position > 0 && 560 - (int)player.y_position < 10) player.y_position = 560;
             else {
                 player.y_speed = 0;
                 player.timer = 0;
                 player.y_position = 560;
                 player.on_ground = TRUE;
                 player.x_speed = 5;
                 player.x_position += 5;
                 event_organizer++;
             }
         }
         else if (event_organizer == 34) {
              player.x_speed = 0;
              event_organizer++;
         }
         else if (event_organizer < 34) { player.x_speed = 5; player.x_position += 5; event_organizer++; }
         else if (event_organizer > 34 && event_organizer < 44) event_organizer++;
         else if (event_organizer >= 51 && event_organizer < 81) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 81)  { event_organizer = 0; call_event = 0; bossfight = 1; input_locked = 0; }
     }
     else if (event_number == 8) {
         set_dvalues(8);
         if (event_organizer == 0) {
             input_locked = 1;
             if (1340 - (int)player.y_position >= 10) player.y_position += 10;
             else if (1340 - (int)player.y_position > 0 && 1340 - (int)player.y_position < 10) player.y_position = 1340;
             else {
                 player.y_position = 1340;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 0;
                 event_organizer++;
             }
         }
         else {
             if (player.cards[4] == 1) {
                 input_locked = 1;
                 finishing = 1;
             }
             else { input_locked = 0; }
             event_organizer = 0;
             call_event = 0;
         }
     }
     else if (event_number == 9) {
         if (event_organizer == 0) {
             input_locked = 1;
             event_organizer++;    
             if (player.on_ground == FALSE && player.timer > 0 && player.in_water == 0) {
                 if (player.timer > 0 && player.timer < 11) player.y_speed+=0.1;
                 else if (player.timer > 10 && player.timer < 21) player.y_speed+=0.06;
                 else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
                 else if (player.timer == 39) player.y_speed = (int)player.y_speed;
                 if (player.y_speed >= 0) player.timer = -1;
                 else  { move_player(0, player.y_speed); move_player(0, player.y_speed); move_player(0, player.y_speed); }
             }
             if (jump_key_state == 0 && player.on_ground == FALSE && player.timer > 0) {
                 player.timer = -1;
                 player.y_speed = 0.4;
             }
             if (player.on_ground == FALSE && player.timer < 0 && player.in_water == 0) {
                 if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                 else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                 else if (player.timer < -20) player.y_speed+=0.1;
                 if (player.y_speed > 2) player.y_speed = 2;
                 if (player.y_speed <= 0) player.timer = 0;
                 else { move_player(0, player.y_speed); move_player(0, player.y_speed); move_player(0, player.y_speed); }
             }
         }
         else if (event_organizer == 33) {
              player.x_speed = 0;
              event_organizer++;
         }
         else if (event_organizer < 33) {
              if ((int)player.x_position > 5460) {
                  player.direction = 1;
                  if ((int)player.x_position - 5460 > 4) player.x_position -= 4;
                  else player.x_position = 5460;
              }
              else if ((int)player.x_position < 5460) {
                  player.direction = 0;
                  if (5460 - player.x_position > 4) player.x_position += 4;
                  else player.x_position = 5460;
              }
              else { player.direction = 0; player.x_speed = 0; }
              if (player.on_ground == FALSE && player.timer > 0 && player.in_water == 0) {
                 if (player.timer > 0 && player.timer < 11) player.y_speed+=0.1;
                 else if (player.timer > 10 && player.timer < 21) player.y_speed+=0.06;
                 else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
                 else if (player.timer == 39) player.y_speed = (int)player.y_speed;
                 if (player.y_speed >= 0) player.timer = -1;
                 else  { move_player(0, player.y_speed); move_player(0, player.y_speed); move_player(0, player.y_speed); }
             }
             if (jump_key_state == 0 && player.on_ground == FALSE && player.timer > 0) {
                 player.timer = -1;
                 player.y_speed = 0.4;
             }
             if (player.on_ground == FALSE && player.timer < 0 && player.in_water == 0) {
                 if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
                 else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
                 else if (player.timer < -20) player.y_speed+=0.1;
                 if (player.y_speed > 2) player.y_speed = 2;
                 if (player.y_speed <= 0) player.timer = 0;
                 else { move_player(0, player.y_speed); move_player(0, player.y_speed); move_player(0, player.y_speed); }
             }
             event_organizer++;
         }
         else if (event_organizer > 33 && event_organizer < 54) {
             screen_locked = 1;
             if (screenx > -5280) {
                 if (screenx - 15 > -5280) screenx -= 10;
                 else screenx = -5280;
             }
             else { set_dvalues(9); screen_locked = 0; }
             event_organizer++;
         }
         else if (event_organizer >= 61 && event_organizer < 91) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 91)  { event_organizer = 0; call_event = 0; bossfight = 1; input_locked = 0; }
     }
     else if (event_number == 10) {
          if (event_organizer == 0) {
             input_locked = 1;
             if (1020 - (int)player.y_position >= 10) player.y_position += 10;
             else if (1020 - (int)player.y_position > 0 && 1020 - (int)player.y_position < 10) player.y_position = 1020;
             else {
                 player.y_position = 1020;
                 player.y_speed = 0;
                 player.timer = 0;
                 player.on_ground = TRUE;
                 player.x_speed = 0;
                 event_organizer++;
             }
         }
         else if (event_organizer == 1) {
             if (player.cards[5] == 1) {
                 input_locked = 1;
                 finishing = 1;
             }
             else { input_locked = 0; }
             event_organizer = 0;
             call_event = 0;
         }
     }
     else if (event_number == 11) {
         if (event_organizer == 0) {
             input_locked = 1;
             if (1020 - (int)player.y_position >= 10) player.y_position += 10;
             else if (1020 - (int)player.y_position > 0 && 1020 - (int)player.y_position < 10) player.y_position = 1020;
             else {
                 player.y_speed = 0;
                 player.timer = 0;
                 player.y_position = 1020;
                 player.on_ground = TRUE;
                 player.x_speed = 5;
                 player.x_position += 5;
                 event_organizer++;
             }
         }
         else if (event_organizer == 34) {
              player.x_speed = 0;
              event_organizer++;
              initialize_sprite(1007, 3980, 1120, 1, 0);
         }
         else if (event_organizer < 34) { player.x_speed = 5; player.x_position += 5; event_organizer++; }
         else if (event_organizer >= 51 && event_organizer < 81) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 81)  { event_organizer = 0; call_event = 0; bossfight = 1; input_locked = 0; }
     }
     else if (event_number == 12) {
         set_dvalues(12);
         call_event = 0; 
         input_locked = 0;
     }
     else if (event_number == 14) {
         if (event_organizer < 40) {
              input_locked = 1;
              player.x_speed = 0;
              event_organizer++;
	   }
	   else if (event_organizer == 40) {
		  input_locked = 1;
		  player.x_speed = 0;
              initialize_sprite(1007, 3980, 1120, 1, 0);
		  event_organizer++;
         }
	   else if (event_organizer >= 51 && event_organizer < 81) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 81)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; input_locked = 0; }
     }
     else if (event_number == 15) {
         if (event_organizer >= 0 && event_organizer < 35) event_organizer++;
         else if (event_organizer == 35) { initialize_sprite(1001, 3180, -100, 0, 105); event_organizer = 200; }
         else if (event_organizer >= 106 && event_organizer < 136) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 136)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; }
     }
     else if (event_number == 16) {
         if (event_organizer == 0) {
             event_organizer = 45;
	   }
         else if (event_organizer >= 106 && event_organizer < 136) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 136)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; }
     }
     else if (event_number == 17) {
         if (event_organizer == 0) {
              player.x_speed = 0;
              event_organizer = 41;
         }
         else if (event_organizer > 40 && event_organizer < 57) event_organizer++;
         else if (event_organizer == 57) { initialize_sprite(27, 5750, 160, 0, 0); event_organizer++; }
         else if (event_organizer > 57 && event_organizer < 60) event_organizer++;
         else if (event_organizer == 60) { flash_screen = 1; event_organizer++; }
         else if (event_organizer == 61) { flash_screen = 2; event_organizer++; initialize_sprite(1004, 5720, 411, 0, 0); }
         else if (event_organizer == 62) { flash_screen = 1; event_organizer++; }
         else if (event_organizer == 63) { flash_screen = 0; event_organizer++; }
         else if (event_organizer > 63 && event_organizer < 68) event_organizer++;
         else if (event_organizer >= 68 && event_organizer < 98) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 98)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; }
     }
     else if (event_number == 18) {
         if (event_organizer == 0) {
              player.x_speed = 0;
              event_organizer = 35;
         }
         else if (event_organizer > 34 && event_organizer < 44) event_organizer++;
         else if (event_organizer >= 51 && event_organizer < 81) {
              if (bosslife == -1) bosslife = 0;
          
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 81)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; input_locked = 0; }
     }
     else if (event_number == 19) {
       if (event_organizer == 0) {
 	 	 event_organizer = 54;
	   }
	   else if (event_organizer >= 61 && event_organizer < 91) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
         }
         else if (event_organizer == 91)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; input_locked = 0; }
     }
     else if (event_number == 20) {
       if (event_organizer == 0) {
 	 	 lastageblack-=4;
 	 	 if (lastageblack <= 0) { lastageblack = 0; event_organizer = 3; }
	   }
	   else if (event_organizer >= 61 && event_organizer < 91) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; play_sample((SAMPLE *)mydatafile[RECUPERATOR].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0); event_organizer++;
       }
       else if (event_organizer == 91)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; input_locked = 0; }
     }
     
     else call_event = 0;
}
    
void input(){
    if (input_locked == 1) { player_colision(); return; }
    
    if ( key[KEY_P]) {
        stop_midi();
        //midi_pos += 10; 
        //midi_seek(midi_pos);
    }
    
    if (!key[KEY_F]) key_f_rest = 0;
    if (key[player.key_jump] && key_f_rest == 0){
	    if (jump_key_state == 0) jump_key_state = 1;
	    else if (jump_key_state == 1) jump_key_state = 2;
    }
    else jump_key_state = 0;
    
    if (key[player.key_fire] && player.shots < 4) fire_key++;
    else if (fire_key >= 1) fire_key++;
    else fire_key = 0;
    
    if (fire_key == 0) {
    if (key[player.key_weapon1]) {
        if (weaponlock == 0) {
            player.current_weapon++;
            if (player.current_weapon == 8) player.current_weapon = 1;
            if (player.current_weapon != 1) {
                for (int x = player.current_weapon; x <= 8; x++) {
                    if (x == 8) { player.current_weapon = 1; break; }
                    else if (player.cards[x-2] == 1) { player.current_weapon = x; break; } 
                }
            }
        }
        weaponlock++;
    }
    else if (key[player.key_weapon2]) {
        if (weaponlock == 0) {
            player.current_weapon--;
            if (player.current_weapon == 0) player.current_weapon = 7;
            if (player.current_weapon != 1) {
                for (int x = player.current_weapon; x >= 0; x--) {
                    if (x == 0) { player.current_weapon = 1; break; }
                    else if (player.cards[x-2] == 1) { player.current_weapon = x; break; } 
                }
            }
        }
        weaponlock++;
    }
    }
    
    if (!key[player.key_weapon1] && !key[player.key_weapon2]) weaponlock = 0;
    
    if (key[KEY_R]) recordinging = 1;
    if (key[KEY_K]) damage(20);
    if (key[KEY_L]) player.hp = player.hpmax;
    
    if (key[player.key_menu] && key_enter_rest == 0) {
        float x = player.x_position;
        float y = player.y_position;
        player.x_position = 0;
        player.y_position = 0;
        gamemenu();
        if (characterscreen == 1) return;
        player.x_position = x;
        player.y_position = y;
    }
    if (!key[player.key_menu]) key_enter_rest = 0;
    if (key[player.key_quit]) timetoquit = 1;
    
    if (fire_key == 0) {
      if (key[KEY_1]) player.current_weapon = 1;
      else if (key[KEY_2] && player.cards[0] == 1) player.current_weapon = 2;
      else if (key[KEY_3] && player.cards[1] == 1) player.current_weapon = 3;
      else if (key[KEY_4] && player.cards[2] == 1) player.current_weapon = 4;
      else if (key[KEY_5] && player.cards[3] == 1) player.current_weapon = 5;
      else if (key[KEY_6] && player.cards[4] == 1) player.current_weapon = 6;
      else if (key[KEY_7] && player.cards[5] == 1) player.current_weapon = 7;
    }
    
    if (player.current_weapon == 1) {
        if (fire_key == 1) { player.shots++; initialize_sprite(1,0,0,player.direction,0); }
        if ((fire_key >= 10 && !key[player.key_fire]) || (fire_key >= 25 && player.shots == 0)) fire_key = 0;
    }
    else if (player.current_weapon == 2) {
        if (fire_key == 1) initialize_sprite(2,0,0,player.direction,0);
        if (fire_key >= 50) fire_key = 0;
    }
    else if (player.current_weapon == 3) {
        if (fire_key == 1) initialize_sprite(3,0,0,player.direction,0);
    }
    else if (player.current_weapon == 4) {
        if (fire_key == 1) { player.shots++; initialize_sprite(4,0,0,player.direction,0); }
        if ((fire_key >= 35 && !key[player.key_fire]) || (fire_key >= 50 && player.shots == 0)) fire_key = 0;
    }
    else if (player.current_weapon == 5) {
        if (fire_key == 1) initialize_sprite(5,0,0,player.direction,0);
        if (fire_key >= 40) fire_key = 0;
    }
    else if (player.current_weapon == 6) {
        if (fire_key == 1) initialize_sprite(6,0,0,player.direction,0);
        if (fire_key >= 70) fire_key = 0;
    }
    else if (player.current_weapon == 7) {
        if (fire_key == 1) initialize_sprite(7,0,0,player.direction,0);
        if (fire_key >= 50) fire_key = 0;
    }
    
   	if ((key[player.key_right]) && !(key[player.key_left])) {
	    if (player.direction == 1) player.direction = 0;
	    if (player.x_speed < 0) player.x_speed = 0;
		else if (player.x_speed >= 1) player.x_speed += 1;
        else player.x_speed += 0.2;
	}
	
    else if ((key[player.key_left]) && !(key[player.key_right])) {
		if (player.direction == 0) player.direction = 1;
	    if (player.x_speed > 0) player.x_speed = 0;
		else if (player.x_speed <= -1) player.x_speed += -1;
        else player.x_speed += -0.2;
    }
	
	else if (!key[player.key_right] && !key[player.key_left]) player.x_speed = 0;
    else if (key[player.key_right] && key[player.key_left]) player.x_speed = 0;
    
    if (player.x_speed > 4) player.x_speed = 4;
    else if (player.x_speed < -4) player.x_speed = -4;
    move_player(player.x_speed, 0);
    
    if (player.on_ground == FALSE && player.timer > 0 && player.in_water == 0) {
        if (player.timer > 0 && player.timer < 11) player.y_speed+=0.1;
        else if (player.timer > 10 && player.timer < 21) player.y_speed+=0.06;
        else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
        else if (player.timer == 39) player.y_speed = (int)player.y_speed;
        if (player.y_speed >= 0) player.timer = -1;
        else  move_player(0, player.y_speed);
    }
    else if (player.on_ground == FALSE && player.timer > 0 && player.in_water == 1) {
        if (player.timer > 0 && player.timer < 3) player.y_speed+=0.1;
        else if (player.timer > 2 && player.timer < 21) player.y_speed+=0.06;
        else if (player.timer > 20 && player.timer < 39) player.y_speed+=0.04;
        else if (player.timer == 39) player.y_speed = (int)player.y_speed;
        if (player.y_speed >= 0) player.timer = -1;
        else  move_player(0, player.y_speed);
    }
    if (jump_key_state != 0 && player.on_ground == TRUE && w84go == 0) {
        player.y_speed = -2.0;
        move_player(0, player.y_speed);
    }
    if (jump_key_state == 0 && player.on_ground == FALSE && player.timer > 0) {
        player.timer = -1;
        player.y_speed = 0.4;
    }
    
    if (player.on_ground == FALSE && player.timer < 0 && player.in_water == 0) {
        if (player.timer < 0 && player.timer > -11) player.y_speed+=0.04;
        else if (player.timer < -10 && player.timer > -21) player.y_speed+=0.06;
        else if (player.timer < -20) player.y_speed+=0.1;
        if (player.y_speed > 2) player.y_speed = 2;
        if (player.y_speed <= 0) player.timer = 0;
        else move_player(0, player.y_speed);
    }
    else if (player.on_ground == FALSE && player.timer < 0 && player.in_water == 1) {
        if (player.timer < 0) player.y_speed+=0.04;
        if (player.y_speed > 1.2) player.y_speed = 1.2;
        if (player.y_speed <= 0) player.timer = 0;
        else move_player(0, player.y_speed);
    }
    
    player_colision();
    if (player.in_water == 1) {
        create_bubbles++;
        if (create_bubbles == 160) {
            if (player.direction == 0) initialize_sprite(70, (int)player.x_position + 30, (int)player.y_position + 15, player.direction, 0);
            else initialize_sprite(70, (int)player.x_position + 4, (int)player.y_position + 15, player.direction, 0);
            create_bubbles = 0;
        }
    }
    else create_bubbles = 0;
    if (music_volume_set == 0) midi_pause();
}

int main() {
    
    allegro_init();
    install_keyboard();
    install_timer();
    install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    srand( time(0) );

    LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));
    LOCK_VARIABLE(last_fps);
    LOCK_VARIABLE(frame_counter);
    LOCK_FUNCTION(count_frames);
    install_int_ex(count_frames, BPS_TO_TIMER(1));
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
    set_palette(desktop_palette);
    
    COLOR_MAP global_light_table;
    create_light_table(&global_light_table,
        desktop_palette, 10, 10, 60, NULL);
    set_trans_blender(0, 0, 0, 0);
            
    title = load_bitmap( "Title.bmp", NULL);
    draw_sprite(screen, title, 0, 0);
    title_music = load_midi("Title.mid");
    play_looped_midi(title_music, 93, 237);
    midi_pos = 6;
    midi_seek(midi_pos);
    gamestartmusic = 1;
    select_music = load_midi("CSelect.mid");
    mydatafile = load_datafile("files.dat");
    if(mydatafile == NULL) {
       set_gfx_mode(GFX_TEXT,0,0,0,0);
       allegro_message("Could not load datafile!");
       exit(EXIT_FAILURE);
    }
    
    create_trans_table(&global_trans_table, desktop_palette, 128, 128, 128, NULL);
    if (get_color_depth() == 8)
	  color_map = &global_trans_table;
    else
	  set_trans_blender(0, 0, 0, 128);
	  
    player.key_up = KEY_UP; player.key_down = KEY_DOWN;
    player.key_right = KEY_RIGHT; player.key_left = KEY_LEFT;
    player.key_jump = KEY_F; player.key_fire = KEY_D;
    player.key_weapon1 = KEY_S; player.key_weapon2 = KEY_A;
    player.key_menu = KEY_ENTER; player.key_quit = KEY_ESC;
    player.current_weapon = 1;
    player.cards[0] = player.cards[1] = player.cards[2] = player.cards[3] = player.cards[4] = player.cards[5] = 1;
    player.vidas = 5;
    player.score = 0;
    player.hpmax = 15;
    lastageportal[0] = lastageportal[1] = lastageportal[2] = lastageportal[3] = lastageportal[4] = lastageportal[5] = 1;
    
    while (!key[KEY_ENTER]) {draw_sprite(screen, title, 0, 0);}
    play_sample((SAMPLE *)mydatafile[ACCEPT].dat, (int)(255 * sound_volume_set / 255), 128, 1000, 0);
    buffer = create_bitmap(640, 480);
    draw_sprite(buffer, title, 0, 0);
    osutatakaefadeout = 255;
    while(osutatakaefadeout < 255) {
        set_trans_blender(0, 0, 0, 0);
        draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
        osutatakaefadeout += 5;
    }
    restartgame:
    speed_counter = 0;
    key_rest = 0;
    player.y_position = 105;
    
    startofgame:
                
    if (gamestartmusic == 0) {
        play_looped_midi(title_music, 93, 237);
        midi_pos = 6;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();
    }
    gamestartmusic = 0;
    
    while(osutatakaefadeout > 0) {
        draw_menu();
        osutatakaefadeout -= 15;
    }
    main_menu();
    while(osutatakaefadeout < 255) {
        draw_menu();
        osutatakaefadeout += 15;
    }
    if (menu == 4) { return 0; }
    menu = 0;
    player.x_position = 0;
    player.y_position = 0;
    player.imune = 0;
    
    characterselect:
    while (key[KEY_ENTER] || key[KEY_F]);
    menu = 0;
    player.x_position = 0;
    player.y_position = 0;
    player.imune = 0;
    current_level = 0;
    play_looped_midi(select_music, 149, 277);
    midi_pos = 4;
    midi_seek(midi_pos);
    if (music_volume_set == 0) midi_pause();
    while(osutatakaefadeout > 0) {
        draw_cselect();
        osutatakaefadeout -= 15;
    }
    cselect();
    while(osutatakaefadeout < 255) {
        draw_cselect();
        osutatakaefadeout += 15;
    }
    player.x_position = 0;
    player.y_position = 0;
    player.imune = 0;
    if (mainmenu == 1) { player.y_position = 105; mainmenu = 0; goto startofgame; }
    
    destroy_bitmap(buffer);
    current_level = 80; 
    lastagedoor = 7;
    
    setup_game();
    while(osutatakaefadeout > 0) {
        draw();
        osutatakaefadeout -= 15;
    }
    lastageportal[0] = lastageportal[1] = lastageportal[2] = lastageportal[3] = lastageportal[4] = lastageportal[5] = 0;

    speed_counter = 1;
    unsigned script_timer;
    
    do {
        while (speed_counter > 0) {
            input();
	        script_timer++;
	        if (script_timer % 4 == 1) { run_scripts(); if (itsover == 1) { myend(); goto restartgame; break; } }
	        speed_counter--;
	        if (player.y_position == (int)player.y_position) player.y_position += 0.01;
	        if (characterscreen == 1) { characterscreen = 0; goto characterselect; break; }
        }
	    draw();
        frame_counter++;
    } while (!key[KEY_ESC]);
    
    for(int i = 0; i < Map.height; i++)
        delete [] map[i];
    delete [] map;
    if (scenario != NULL) destroy_bitmap(scenario);
    if (buffer != NULL) destroy_bitmap(buffer);
    if (background != NULL) destroy_bitmap(background);
    if (bakg != NULL) destroy_bitmap(bakg);
    if (title != NULL) destroy_bitmap(title);
    if (foreground != NULL) destroy_bitmap(foreground);
    if (title_music != NULL) destroy_midi(title_music);
    if (select_music != NULL) destroy_midi(select_music);
    if (stage_music != NULL) destroy_midi(stage_music);
    if (mydatafile != NULL) unload_datafile(mydatafile);
    
    return 0;
}
END_OF_MAIN();
