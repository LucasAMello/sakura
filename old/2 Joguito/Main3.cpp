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
             Map.number = 1; lastagedoor = 0; lastageportal[0] = 1;
             Map.startingpointx = 100; Map.startingpointy = 1160;
	   }
         else if (lastagedoor == 2) { 
             Map.number = 1; lastagedoor = 0; lastageportal[1] = 1;
             Map.startingpointx = 580; Map.startingpointy = 1280;
	   }
         else if (lastagedoor == 3) { 
             Map.number = 1; lastagedoor = 0; lastageportal[2] = 1;
             Map.startingpointx = 100; Map.startingpointy = 1160;
	   }
         else if (lastagedoor == 4) { 
             Map.number = 1; lastagedoor = 0; lastageportal[3] = 1;
             Map.startingpointx = 100; Map.startingpointy = 1160;
	   }
         else if (lastagedoor == 5) { 
             Map.number = 1; lastagedoor = 0; lastageportal[4] = 1;
             Map.startingpointx = 100; Map.startingpointy = 1160;
	   }
         else if (lastagedoor == 6) { 
             Map.number = 1; lastagedoor = 0; lastageportal[5] = 1;
             Map.startingpointx = 100; Map.startingpointy = 1160;
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
         Map.limitleft = 5360;
         Map.limitright = 6000;
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
     else if (mapnumber == 77) {
         Map.width = 300;
         Map.height = 32;
         Map.limitleft = 5360;
         Map.limitright = 6000;
         Map.limitup = 60;
         Map.limitdown = 540;
         Map.number = 1;
         Map.startingpointx = 5500;
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
     else if (mapnumber == 78) {
         Map.width = 500;
         Map.height = 40;
         Map.limitleft = 9360;
         Map.limitright = 10000;
         Map.limitup = 320;
         Map.limitdown = 800;
         Map.number = 1;
         Map.water_position = 300;
         Map.startingpointx = 9500;
         Map.startingpointy = 660;
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
     else if (mapnumber == 79) {
         Map.width = 300;
         Map.height = 120;
         Map.limitleft = 5360;
         Map.limitright = 6000;
         Map.limitup = 1920;
         Map.limitdown = 2400;
         Map.number = 0;
         Map.water_position = 0;
         Map.startingpointx = 5500;
         Map.startingpointy = 2180;
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
       //bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(10000, 720);
       scenario = create_bitmap(10000, 720);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(24,16,30));
       dead = 1;
       initiate_level(70);
    }
    else if (current_level == 71) {
       //bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(10000, 800);
       scenario = create_bitmap(10000, 800);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(24,16,30));
       dead = 1;
       initiate_level(71);
    }
    else if (current_level == 72) {
       //bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(15000, 800);
       scenario = create_bitmap(15000, 800);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(24,16,30));
       dead = 1;
       initiate_level(72);
    }
    else if (current_level == 73) {
       //bakg = load_bitmap("bg6.bmp", NULL);
       background = create_bitmap(3000, 1600);
       scenario = create_bitmap(3000, 1600);
       buffer = create_bitmap(640, 480);
       clear_to_color(scenario, makecol(255,0,255));
       clear_to_color(background, makecol(24,16,30));
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

}

void initiate_level(int mapnumber) {
     if (mapnumber == 10) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(10);
        }
        
        texture = TEXTURES01;
        for (int i = 0; i <= 27; i++){
            for( int t = 0; t <= 449; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(20 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(60 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(20 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(40 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(0 , 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(40 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(0 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
            }       
        }
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
    
        if (player.cards[32] == 0) initialize_sprite(69, 4052, 260, 0, 32);
        if (player.cards[43] == 0) initialize_sprite(65, 6470, 120, 0, 43);
        initialize_sprite(10, 800, 320, 0, 0);
        initialize_sprite(10, 1480, 320, 0, 0);
        initialize_sprite(10, 1780, 240, 1, 0);
        initialize_sprite(10, 2920, 120, 0, 0);
        initialize_sprite(10, 3220, 120, 0, 0);
        initialize_sprite(10, 3720, 280, 0, 0);
        initialize_sprite(10, 5140, 400, 0, 0);
        initialize_sprite(10, 5500, 340, 0, 0);
        initialize_sprite(10, 5800, 280, 0, 0);
        initialize_sprite(10, 7060, 420, 0, 0);
        initialize_sprite(10, 7480, 240, 0, 0);
        initialize_sprite(10, 7700, 160, 0, 0);
        initialize_sprite(10, 7900, 120, 0, 0);
    
        initialize_sprite(11, 2720, 220, 0, 0);
        initialize_sprite(11, 6480, 380, 0, 0);
        initialize_sprite(11, 7060, 400, 0, 0);
    
        initialize_sprite(14, 4320, 120, 0, 0);
        initialize_sprite(14, 6100, 160, 0, 0);
        initialize_sprite(14, 6180, 160, 0, -10);
        
        initialize_sprite(1010, 8960, 280, 100, 11);
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 13, 165);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();
        
    }
    else if (mapnumber == 11) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(11);
        }
        
        texture = TEXTURES01;
        for (int i = 0; i <= 99; i++){
            for( int t = 0; t <= 39; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(20 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(60 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(20 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(40 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(0 , 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(40 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(0 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
            }       
        }
        
        if (player.cards[42] == 0) initialize_sprite(69, 612, 740, 0, 42);
        initialize_sprite(10, 300, 180, 0, 0);
        initialize_sprite(10, 180, 560, 0, 0);
        initialize_sprite(10, 180, 1200, 0, 0);
        initialize_sprite(10, 420, 1440, 0, 0);
        initialize_sprite(10, 480, 1720, 1, 0);
        initialize_sprite(10, 380, 1720, 0, 0);
        
        initialize_sprite(11, 480, 420, 0, 0);
        initialize_sprite(11, 460, 1100, 0, 0);
        initialize_sprite(11, 280, 1540, 0, 0);
        
        initialize_sprite(12, 340, 880, 0, 0);
        initialize_sprite(12, 400, 880, 1, 0);
        initialize_sprite(12, 620, 1860, 0, 0);
        
        initialize_sprite(1010, 760, 1820, 100, 12);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        
    }
    else if (mapnumber == 12) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           //set_dvalues(doorrecord - 1);
           load_map(12);
        }
        
        texture = TEXTURES01;
        for (int i = 0; i <= 29; i++){
            for( int t = 0; t <= 419; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(20 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(60 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(20 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(40 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(0 , 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(40 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(0 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
            }       
        }
        
        if (player.cards[10] == 0) initialize_sprite(69, 2552, 380, 0, 10);
        if (player.cards[37] == 0) initialize_sprite(65, 7180, 80, 0, 37);
        initialize_sprite(10, 680, 360, 0, 0);
        initialize_sprite(10, 1860, 400, 0, 0);
        initialize_sprite(10, 2440, 120, 0, 0);
        initialize_sprite(10, 4720, 280, 0, 0);
        initialize_sprite(10, 7240, 300, 0, 0);
        
        initialize_sprite(11, 880, 340, 0, 0);
        initialize_sprite(11, 4180, 380, 0, 0);
        initialize_sprite(11, 4240, 380, 0, -20);
        initialize_sprite(11, 6760, 360, 0, 0);
        initialize_sprite(11, 6805, 360, 0, -5);
        initialize_sprite(11, 6850, 360, 0, -10);
        
        initialize_sprite(12, 980, 500, 0, 0);
        initialize_sprite(12, 2420, 440, 0, 0);
        initialize_sprite(12, 5710, 240, 0, 0);
        initialize_sprite(12, 7480, 420, 1, 0);
        
        initialize_sprite(14, 4030, 50, 0, 0);
        initialize_sprite(14, 4880, 180, 0, 0);
        initialize_sprite(14, 6080, 100, 0, 0);
        
        initialize_sprite(55, 3440, 320, 0, 0);
        initialize_sprite(55, 6240, 240, 0, 0);
        initialize_sprite(55, 5080, 240, 0, 0);
        
        initialize_sprite(1010, 8360, 420, 120, 13);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 13) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(13);
        }
        texture = TEXTURES01;
        for (int i = 0; i <= 89; i++){
            for( int t = 0; t <= 39; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(20 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(60 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(20 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(40 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(0 , 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(40 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(0 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
            }       
        }
        if (player.cards[38] == 0) initialize_sprite(69, 562, 1720, 0, 28);
        if (player.cards[13] == 0) initialize_sprite(69, 620, 240, 0, 13);
        initialize_sprite(10, 500, 1200, 0, 0); initialize_sprite(10, 380, 940, 0, 0);
        initialize_sprite(10, 300, 120, 0, 0); initialize_sprite(10, 480, 120, 1, 0);
        initialize_sprite(11, 340, 1600, 0, 0); initialize_sprite(11, 310, 360, 0, 0);
        initialize_sprite(12, 470, 700, 0, 0); initialize_sprite(55, 600, 1740, 0, 0);
        initialize_sprite(55, 320, 1120, 0, 0); initialize_sprite(55, 400, 580, 0, 0);
        initialize_sprite(1010, 760, 40, 100, 14);
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 14) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(14);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        texture = TEXTURES01;
        for (int i = 0; i <= 27; i++){
            for( int t = 0; t <= 199; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(20 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(60 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(20 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(40 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(0 , 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(40 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(0 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
            }       
        }
        if (player.cards[20] == 0) initialize_sprite(69, 1720, 280, 0, 20);
        initialize_sprite(10, 580, 380, 0, 0); initialize_sprite(10, 1380, 360, 0, 0);
        initialize_sprite(14, 1170, 160, 0, 0); initialize_sprite(14, 1250, 180, 0, -10);
        initialize_sprite(14, 1540, 260, 0, 0); initialize_sprite(1000, 2120, 280, 0, 0);
        initialize_sprite(1000, 2730, 280, 0, 1); initialize_sprite(2001, 2760, 380, 0, 0);
        initialize_sprite(2000, 2780, 380, 0, 0); initialize_sprite(2000, 2860, 380, 0, 0);
        initialize_sprite(2000, 2940, 380, 0, 0); initialize_sprite(2000, 3020, 380, 0, 0);
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        //for (int i = 0; i < number_of_sprites; i++) {
        //    if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        //}
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 20) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(20);
        }
        
        texture = TEXTURES02;
        for (int i = 0; i <= 23; i++){
            for( int t = 0; t <= 99; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(40 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(80 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') { initialize_wall(100, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'n') { initialize_wall(100, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(80, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
            }       
        }
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        if (player.cards[12] == 0) initialize_sprite(69, 1770, 280, 0, 12);
        initialize_sprite(15, 1580, 200, 0, 0);
        
        initialize_sprite(1010, 1960, 100, 240, 21);
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 13, 177);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }    
    else if (mapnumber == 21) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(21);
        }
        
        texture = TEXTURES02;
        for (int i = 0; i <= 27; i++){
            for( int t = 0; t <= 209; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(40 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(80 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') { initialize_wall(100, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'n') { initialize_wall(100, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(80, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
            }       
        }
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        if (player.cards[16] == 0) initialize_sprite(69, 2040, 300, 0, 16);
        initialize_sprite(59, 2100, 180, 0, 0);
        initialize_sprite(60, 1120, 370, 0, 0);
        initialize_sprite(60, 3860, 390, 0, 22);
        
        initialize_sprite(15, 510, 220, 0, 0);
        initialize_sprite(15, 1300, 200, 0, 0);
        initialize_sprite(15, 2670, 280, 0, 0);
        initialize_sprite(15, 3630, 400, 0, 0);
        
        initialize_sprite(16, 3120, 180, 1580, 140);
        
        initialize_sprite(1010, 4160, 340, 120, 22);
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 22) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(22);
        }
        
        texture = TEXTURES02;
        for (int i = 0; i <= 69; i++){
            for( int t = 0; t <= 119; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(40 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(80 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') { initialize_wall(100, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'n') { initialize_wall(100, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(80, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
            }       
        }
        
        if (player.cards[47] == 0) initialize_sprite(69, 1680, 200, 1, 47);
        if (player.cards[39] == 0) initialize_sprite(69, 40, 1040, 1, 39);
        initialize_sprite(60, 1180, 250, 0, 0);
        initialize_sprite(60, 400, 1250, 0, 0);
        initialize_sprite(60, 1770, 990, 0, 35);
        
        initialize_sprite(53, 740, 352, 1, 120);
        initialize_sprite(53, 1620, 352, 1, 160);
        initialize_sprite(53, 2100, 772, 1, 100);
        initialize_sprite(53, 1160, 772, 1, 220);
        initialize_sprite(53, 620, 772, 1, 120);
        initialize_sprite(53, 1160, 1172, 1, 120);
        
        initialize_sprite(15, 600, 230, 0, 0);
        initialize_sprite(15, 1800, 200, 0, 0);
        initialize_sprite(15, 1860, 560, 1, 0);
        initialize_sprite(15, 720, 1080, 0, 0);
        initialize_sprite(15, 1610, 960, 0, 0);
        
        initialize_sprite(61, 120, 560, 2400, 140);
        
        initialize_sprite(1010, 2360, 940, 120, 23);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 23) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(23);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES02;
        for (int i = 0; i <= 35; i++){
            for( int t = 0; t <= 299; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(40 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(80 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') { initialize_wall(100, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'n') { initialize_wall(100, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'w') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'q') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') { initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(80, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
            }       
        }

        if (player.cards[24] == 0) initialize_sprite(69, 660, 60, 1, 24);
        initialize_sprite(60, 3860, 530, 0, 27);
        initialize_sprite(53, 340, 652, 1, 2500);
        
        initialize_sprite(1000, 4700, 440, 0, 2);
        initialize_sprite(1000, 5310, 440, 0, 3);
        
        initialize_sprite(1002, 5700, 530, 0, 0);
        
        initialize_sprite(15, 620, 340, 0, 0);
        initialize_sprite(15, 860, 460, 0, 0);
        initialize_sprite(15, 1230, 530, 0, 0);
        initialize_sprite(15, 1400, 200, 0, 0);
        initialize_sprite(15, 1760, 400, 0, 0);
        initialize_sprite(15, 2160, 260, 0, 0);
        initialize_sprite(15, 3300, 460, 0, 0);
        
        initialize_sprite(16, 4560, 440, 3080, 140);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 30) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(30);
        }
        
        texture = TEXTURES04;
        for (int i = 0; i <= 29; i++){
            for( int t = 0; t <= 499; t++){
                 if( map[i][t] == '2') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(100, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(120, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'q') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(0, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'y') initialize_wall(20, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '#') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '$') initialize_wall(40, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '%') initialize_wall(60, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(80, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '+') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '_') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
            }       
        }   
        
        if (player.cards[25] == 0) initialize_sprite(69, 2230, 310, 1, 25);
        if (player.cards[21] == 0) initialize_sprite(69, 6300, 260, 1, 21);
        if (player.cards[38] == 0) initialize_sprite(65, 8540, 100, 0, 38);
        initialize_sprite(19, 900, 260, 0, 5);
        initialize_sprite(19, 1380, 100, 0, 10);
        initialize_sprite(19, 1480, 340, 1, 0);
        initialize_sprite(19, 4080, 300, 1, 0);
        initialize_sprite(19, 4260, 300, 2, 0);
        initialize_sprite(19, 6740, 340, 1, 0);
        initialize_sprite(21, 4580, 450, 0, 0);
        initialize_sprite(21, 5620, 310, 0, 0);
        initialize_sprite(21, 8760, 370, 0, 0);
        initialize_sprite(23, 2770, 260, 0, 0);
        initialize_sprite(23, 6200, 140, 0, 0);
        initialize_sprite(23, 7150, 280, 0, 0);
        initialize_sprite(23, 7670, 240, 0, 0);
        initialize_sprite(23, 5140, 210, 0, 0);
        initialize_sprite(24, 3180, 116, 0, 0);
        initialize_sprite(24, 3330, 356, 2, 0);
        initialize_sprite(24, 4716, 260, 3, 0);
        initialize_sprite(24, 5760, 56, 0, 0);
        initialize_sprite(24, 9160, 196, 0, 0);
        initialize_sprite(24, 9360, 336, 2, 0);
        initialize_sprite(1010, 9960, 220, 140, 31);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 77, 277);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();
        
    }
    else if (mapnumber == 31) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(31);
        }
        
        texture = TEXTURES04;
        for (int i = 0; i <= 79; i++){
            for( int t = 0; t <= 99; t++){
                 if( map[i][t] == '2') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(100, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(120, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'q') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(0, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'y') initialize_wall(20, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '#') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '$') initialize_wall(40, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '%') initialize_wall(60, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(80, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '+') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '_') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
            }       
        }
        
        if (player.cards[6] == 0) initialize_sprite(69, 80, 1480, 1, 6);
        if (player.cards[17] == 0) initialize_sprite(69, 1760, 400, 1, 17);
        initialize_sprite(19, 820, 280, 2, 0);
        initialize_sprite(19, 240, 380, 0, 0);
        initialize_sprite(19, 430, 380, 0, 15);
        initialize_sprite(19, 620, 380, 0, 0);
        initialize_sprite(19, 720, 920, 1, 0);
        initialize_sprite(19, 880, 1340, 0, 0);
        initialize_sprite(21, 560, 150, 0, 0);
        initialize_sprite(21, 930, 1470, 0, 0);
        initialize_sprite(21, 1740, 490, 0, 0);
        initialize_sprite(21, 1840, 230, 0, 0);
        initialize_sprite(23, 1660, 1200, 0, 0);
        initialize_sprite(23, 1240, 1000, 0, 0);
        initialize_sprite(23, 1240, 220, 0, 0);
        initialize_sprite(24, 110, 796, 2, 0);
        initialize_sprite(24, 876, 680, 1, 0);
        initialize_sprite(24, 876, 780, 1, -10);
        initialize_sprite(24, 216, 1100, 3, 0);
        initialize_sprite(24, 216, 1180, 3, -12);
        initialize_sprite(24, 216, 1260, 3, -24);
        initialize_sprite(24, 436, 1140, 1, -6);
        initialize_sprite(24, 436, 1220, 1, -18);
        initialize_sprite(24, 110, 1316, 0, -24);
        initialize_sprite(24, 170, 1316, 0, -44);
        initialize_sprite(24, 1276, 820, 3, 0);
        initialize_sprite(24, 1696, 920, 3, 0);
        initialize_sprite(1010, 1960, 140, 160, 32);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        
    }
    else if (mapnumber == 32) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(32);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES04;
        for (int i = 0; i <= 31; i++){
            for( int t = 0; t <= 299; t++){
                 if( map[i][t] == '2') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(100, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(120, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'q') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(0, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'y') initialize_wall(20, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '#') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '$') initialize_wall(40, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '%') initialize_wall(60, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(80, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '+') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '_') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
            }       
        }
        
        if (player.cards[26] == 0) initialize_sprite(69, 4020, 220, 1, 26);
        if (player.cards[48] == 0) initialize_sprite(69, 1520, 360, 1, 48);
        initialize_sprite(19, 1110, 240, 0, 0);
        initialize_sprite(19, 1350, 240, 0, 0);
        initialize_sprite(19, 1590, 240, 0, 15);
        initialize_sprite(19, 3760, 300, 1, 0);
        initialize_sprite(19, 3760, 380, 1, 20);
        initialize_sprite(19, 3760, 460, 1, 10);
        initialize_sprite(21, 1000, 450, 0, 0);
        initialize_sprite(21, 3260, 290, 0, 0);
        initialize_sprite(21, 4600, 410, 0, 0);
        initialize_sprite(23, 2160, 140, 0, 0);
        initialize_sprite(23, 3140, 100, 0, 0);
        initialize_sprite(24, 1111, 556, 2, -10);
        initialize_sprite(24, 1351, 556, 2, -50);
        initialize_sprite(24, 1591, 556, 2, -20);
        initialize_sprite(24, 1232, 156, 0, -40);
        initialize_sprite(24, 1472, 156, 0, 0);
        initialize_sprite(24, 1712, 156, 0, -30);
        initialize_sprite(1000, 4720, 380, 0, 4);
        initialize_sprite(1000, 5330, 380, 0, 5);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        
    }
    else if (mapnumber == 40) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(40);
        }
        
        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++){
            for( int t = 0; t <= 449; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') { initialize_wall(40, 20, 10, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20); initialize_wall(40, 20, 2, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'a') { initialize_wall(60, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'b') { initialize_wall(60, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'c') { initialize_wall(80, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'd') { initialize_wall(80, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'e') { initialize_wall(100, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'f') { initialize_wall(100, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'g') { initialize_wall(100, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'h') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') { initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'j') { initialize_wall(40, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'k') { initialize_wall(60, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') { initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'o') { initialize_wall(40, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(60, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(80, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(120, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(40, 40, 12, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '}') initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '{') initialize_wall(40, 60, 12, 20, 20, t * 20, i * 20);
                 
            }       
        }
        
        if (player.cards[50] == 0) initialize_sprite(69, 20, 220, 1, 50);
        if (player.cards[8] == 0) initialize_sprite(69, 3220, 470, 1, 8);
        initialize_sprite(66, 7290, 344, 0, 34);
        initialize_sprite(29, 700, 300, 0, 0);
        initialize_sprite(29, 1440, 380, 0, 0);
        initialize_sprite(29, 6270, 380, 0, 0);
        initialize_sprite(31, 3860, 600, 0, 0);
        initialize_sprite(31, 8540, 540, 0, 0);
        initialize_sprite(32, 3170, 480, 0, 0);
        initialize_sprite(32, 3220, 450, 0, 0);
        initialize_sprite(32, 3190, 500, 0, 0);
        initialize_sprite(32, 3230, 485, 0, 0);
        initialize_sprite(32, 3185, 445, 0, 0);
        initialize_sprite(32, 5280, 470, 0, 0);
        initialize_sprite(32, 5300, 485, 0, 0);
        initialize_sprite(32, 5270, 515, 0, 0);
        initialize_sprite(32, 5285, 500, 0, 0);
        initialize_sprite(32, 8200, 480, 0, 0);
        initialize_sprite(34, 2040 + 6, 433 + 13, 0, 0);
        initialize_sprite(33, 2040, 433, 0, 0);
        initialize_sprite(34, 4690 + 6, 493 + 13, 0, 0);
        initialize_sprite(33, 4690, 493, 0, 0);
        initialize_sprite(34, 5920 + 6, 473 + 13, 0, 0);
        initialize_sprite(33, 5920, 473, 0, 0);
        initialize_sprite(34, 6990 + 6, 373 + 13, 0, 0);
        initialize_sprite(33, 6990, 373, 0, 0);
        initialize_sprite(34, 7560 + 1, 413 + 13, 1, 0);
        initialize_sprite(33, 7560, 413, 1, 0);
        initialize_sprite(1010, 8960, 360, 220, 41);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 185, 357);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 41) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 1;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           bossfight = 0;
           load_map(41);
        }
        
        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++){
            for( int t = 0; t <= 449; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') { initialize_wall(40, 20, 10, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20); initialize_wall(40, 20, 2, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'a') { initialize_wall(60, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'b') { initialize_wall(60, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'c') { initialize_wall(80, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'd') { initialize_wall(80, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'e') { initialize_wall(100, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'f') { initialize_wall(100, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'g') { initialize_wall(100, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'h') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') { initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'j') { initialize_wall(40, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'k') { initialize_wall(60, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') { initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'o') { initialize_wall(40, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(60, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(80, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(120, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(40, 40, 12, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '}') initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '{') initialize_wall(40, 60, 12, 20, 20, t * 20, i * 20);
                 
            }       
        }
        
        if (player.cards[36] == 0) initialize_sprite(69, 810, 310, 1, 36);
        if (player.cards[30] == 0) initialize_sprite(69, 8660, 80, 1, 30);
        initialize_sprite(66, 6980, 164, 0, 40);
        initialize_sprite(29, 7120, 200, 0, 0);
        initialize_sprite(32, 770, 280, 0, 0);
        initialize_sprite(32, 870, 320, 0, 0);
        initialize_sprite(32, 800, 320, 0, 0);
        initialize_sprite(32, 830, 290, 0, 0);
        initialize_sprite(32, 786, 300, 0, 0);
        initialize_sprite(32, 1770, 480, 0, 0);
        initialize_sprite(32, 1870, 460, 0, 0);
        initialize_sprite(32, 1700, 490, 0, 0);
        initialize_sprite(32, 1740, 500, 0, 0);
        initialize_sprite(32, 3320, 420, 0, 0);
        initialize_sprite(32, 3300, 440, 0, 0);
        initialize_sprite(32, 3335, 405, 0, 0);
        initialize_sprite(32, 3785, 385, 0, 0);
        initialize_sprite(32, 3805, 355, 0, 0);
        initialize_sprite(32, 4660, 285, 0, 0);
        initialize_sprite(32, 4685, 275, 0, 0);
        initialize_sprite(32, 4670, 305, 0, 0);
        initialize_sprite(32, 7900, 220, 0, 0);
        initialize_sprite(32, 7920, 225, 0, 0);
        initialize_sprite(32, 7960, 235, 0, 0);
        initialize_sprite(32, 7970, 255, 0, 0);
        initialize_sprite(32, 8000, 220, 0, 0);
        initialize_sprite(31, 2050, 620, 0, 0);
        initialize_sprite(31, 2940, 560, 0, 0);
        initialize_sprite(31, 3140, 560, 0, 0);
        initialize_sprite(31, 5740, 320, 0, 0);
        initialize_sprite(31, 8480, 380, 0, 0);
        initialize_sprite(34, 2650 + 6, 533 + 13, 0, 0);
        initialize_sprite(33, 2650, 533, 0, 0);
        initialize_sprite(34, 4000 + 6, 453 + 13, 0, 0);
        initialize_sprite(33, 4000, 453, 0, 0);
        initialize_sprite(34, 4180 + 6, 393 + 13, 0, 0);
        initialize_sprite(33, 4180, 393, 0, 0);
        initialize_sprite(34, 6600 + 6, 233 + 13, 0, 0);
        initialize_sprite(33, 6600, 233, 0, 0);
        initialize_sprite(34, 1360 + 1, 593 + 13, 1, 0);
        initialize_sprite(33, 1360, 593, 1, 0);
        initialize_sprite(34, 7280 + 1, 233 + 13, 1, 0);
        initialize_sprite(33, 7280, 233, 1, 0);
        initialize_sprite(1010, 8960, 0, 240, 42);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 42) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(42);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++){
            for( int t = 0; t <= 499; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') { initialize_wall(40, 20, 10, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20); initialize_wall(40, 20, 2, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'a') { initialize_wall(60, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'b') { initialize_wall(60, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'c') { initialize_wall(80, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'd') { initialize_wall(80, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'e') { initialize_wall(100, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'f') { initialize_wall(100, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'g') { initialize_wall(100, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'h') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') { initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'j') { initialize_wall(40, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'k') { initialize_wall(60, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') { initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'o') { initialize_wall(40, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(60, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(80, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(120, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(40, 40, 12, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '}') initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '{') initialize_wall(40, 60, 12, 20, 20, t * 20, i * 20);
                 
            }       
        }       
        
        if (player.cards[30] == 0) initialize_sprite(69, 5480, 480, 1, 30);
        if (player.cards[36] == 0) initialize_sprite(69, 3550, 330, 0, 36);
        initialize_sprite(66, 2510, 204, 0, 11);
        initialize_sprite(29, 1790, 260, 0, 0);
        initialize_sprite(29, 2170, 240, 0, 0);
        
        initialize_sprite(31, 1160, 400, 0, 0);
        initialize_sprite(31, 4210, 420, 0, 0);
        initialize_sprite(31, 5720, 620, 0, 0);
        initialize_sprite(31, 5755, 620, 0, 0);
        initialize_sprite(31, 8180, 580, 0, 0);
        initialize_sprite(31, 8220, 580, 0, 0);
        initialize_sprite(31, 8260, 580, 0, 0);
        
        initialize_sprite(32, 960, 275, 0, 0);
        initialize_sprite(32, 930, 320, 0, 0);
        initialize_sprite(32, 3560, 320, 0, 0);
        initialize_sprite(32, 3550, 300, 0, 0);
        initialize_sprite(32, 3580, 340, 0, 0);
        initialize_sprite(32, 3560, 355, 0, 0);
        initialize_sprite(32, 3980, 300, 0, 0);
        initialize_sprite(32, 3900, 325, 0, 0);
        initialize_sprite(32, 5270, 460, 0, 0);
        initialize_sprite(32, 5200, 465, 0, 0);
        initialize_sprite(32, 5370, 470, 0, 0);
        initialize_sprite(32, 5250, 430, 0, 0);
        initialize_sprite(32, 5320, 480, 0, 0);
        initialize_sprite(32, 5235, 475, 0, 0);
        initialize_sprite(32, 7450, 460, 0, 0);
        initialize_sprite(32, 7400, 480, 0, 0);
        initialize_sprite(32, 7510, 500, 0, 0);
        initialize_sprite(32, 7465, 493, 0, 0);
        initialize_sprite(32, 7710, 460, 0, 0);
        initialize_sprite(32, 7765, 435, 0, 0);
        
        initialize_sprite(34, 2680 + 6, 213 + 13, 0, 0);
        initialize_sprite(33, 2680, 213, 0, 0);
        initialize_sprite(34, 4700 + 6, 473 + 13, 0, 0);
        initialize_sprite(33, 4700, 473, 0, 0);
        initialize_sprite(34, 6440 + 6, 513 + 13, 0, 0);
        initialize_sprite(33, 6440, 513, 0, 0);
        initialize_sprite(34, 2300 + 1, 213 + 13, 1, 0);
        initialize_sprite(33, 2300, 213, 1, 0); 
        initialize_sprite(34, 7040 + 1, 493 + 13, 1, 0);
        initialize_sprite(33, 7040, 493, 1, 0); 
        
        initialize_sprite(1000, 8720, 540, 0, 6);
        initialize_sprite(1000, 9330, 540, 0, 7);
        initialize_sprite(1005, 9770, 570, 0, 0);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 50) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(50);
        }
        
        texture = TEXTURES06;
        for (int i = 0; i <= 79; i++){
            for( int t = 0; t <= 39; t++){
                 if( map[i][t] == '2') initialize_wall(20, 20, 1, 40, 40, t * 20, i * 20);
                 //else if( map[i][t] == '3') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == '4') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == '5') initialize_wall(40, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(140, 60, 1, 40, 40, t * 20, i * 20);
                 //else if( map[i][t] == '7') initialize_wall(160, 60, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == '8') initialize_wall(140, 80, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == '9') initialize_wall(160, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '0') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(100, 0, 1, 40, 40, t * 20, i * 20);
                 //else if( map[i][t] == 'b') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == 'c') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == 'd') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(100, 40, 1, 40, 40, t * 20, i * 20);
                 //else if( map[i][t] == 'f') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == 'g') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 //else if( map[i][t] == 'h') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'p') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '>') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'q') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 't') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'u') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '<') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'v') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'y') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'B') { initialize_wall(160, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'C') { initialize_wall(180, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'D') { initialize_wall(200, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'E') { initialize_wall(220, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'F') { initialize_wall(200, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(180, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(180, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(200, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(220, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(200, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'I') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'J') { initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(220, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(200, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
            }       
        }       
        
        if (player.cards[29] == 0) initialize_sprite(69, 535, 850, 1, 29);
        initialize_sprite(37, 496, 200, 1, 0);
        initialize_sprite(37, 184, 360, 0, -15);
        initialize_sprite(38, 480, 940, 1, 0);
        initialize_sprite(41, 320, 1147, 0, 0);
        initialize_sprite(44, 220, 1540, 0, 140);
        initialize_sprite(44, 440, 1540, 0, 220);
        initialize_sprite(1010, 760, 1300, 200, 51);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 45, 193);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 51) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(51);
        }
        
        texture = TEXTURES06;
        for (int i = 0; i <= 35; i++){
            for( int t = 0; t <= 359; t++){
                 if( map[i][t] == '2') initialize_wall(20, 20, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(140, 60, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '0') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(100, 0, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(100, 40, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'p') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '>') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'q') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 't') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'u') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '<') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'v') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'y') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'B') { initialize_wall(160, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'C') { initialize_wall(180, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'D') { initialize_wall(200, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'E') { initialize_wall(220, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'F') { initialize_wall(200, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(180, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(180, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(200, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(220, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(200, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'I') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'J') { initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(220, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(200, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
            }       
        }       

        if (player.cards[33] == 0) initialize_sprite(69, 3460, 320, 1, 33);
        if (player.cards[15] == 0) initialize_sprite(69, 7060, 420, 1, 15);
        initialize_sprite(37, 4900, 320, 0, 0);
        initialize_sprite(37, 5180, 380, 1, -10);
        initialize_sprite(37, 4900, 440, 0, -20);
        initialize_sprite(38, 2340, 500, 1, 0);
        initialize_sprite(38, 2400, 260, 0, -40);
        initialize_sprite(38, 2460, 500, 1, 0);
        initialize_sprite(38, 2520, 260, 0, -40);
        initialize_sprite(38, 2580, 500, 1, 0);
        initialize_sprite(38, 2640, 260, 0, -40);
        initialize_sprite(38, 6040, 300, 0, 0);
        initialize_sprite(38, 6040, 580, 1, 0);
        initialize_sprite(38, 6400, 300, 0, -40);
        initialize_sprite(38, 6400, 580, 1, -40);
        initialize_sprite(38, 6840, 300, 0, 0);
        initialize_sprite(38, 6840, 580, 1, 0);
        
        initialize_sprite(41, 610, 467, 0, 0);
        initialize_sprite(41, 1840, 587, 0, 0);
        initialize_sprite(41, 2080, 547, 0, 0);
        initialize_sprite(41, 4280, 227, 0, 0);
        initialize_sprite(42, 5800, 340, 0, 0);
        initialize_sprite(42, 6160, 340, 0, 0);
        initialize_sprite(42, 6320, 340, 1, 0);
        initialize_sprite(42, 6520, 340, 0, 0);
        initialize_sprite(42, 6680, 340, 0, 0);
        
        initialize_sprite(44, 860, 520, 0, 160);
        initialize_sprite(44, 1140, 520, 0, 160);
        initialize_sprite(44, 3060, 520, 0, 480);
        initialize_sprite(44, 4060, 300, 0, 160);
        initialize_sprite(44, 4380, 300, 0, 200);
        
        initialize_sprite(45, 1200, 540, 0, 0);
        initialize_sprite(45, 4120, 320, 0, 0);
        initialize_sprite(45, 4440, 320, 0, 0);
        
        initialize_sprite(1010, 7160, 340, 160, 52);

        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 52) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(52);
        }
        
        texture = TEXTURES06;
        for (int i = 0; i <= 79; i++){
            for( int t = 0; t <= 59; t++){
                 if( map[i][t] == '2') initialize_wall(20, 20, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(140, 60, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '0') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(100, 0, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(100, 40, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'p') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '>') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'q') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 't') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'u') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '<') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'v') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'y') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'B') { initialize_wall(160, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'C') { initialize_wall(180, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'D') { initialize_wall(200, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'E') { initialize_wall(220, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'F') { initialize_wall(200, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(180, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(180, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(200, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(220, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(200, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'I') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'J') { initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(220, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(200, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
            }       
        }       
        
        if (player.cards[7] == 0) initialize_sprite(69, 880, 80, 1, 7);
        initialize_sprite(37, 260, 1160, 0, 0);
        initialize_sprite(37, 20, 360, 0, -30);
        initialize_sprite(37, 140, 440, 0, 0);
        
        initialize_sprite(41, 140, 1027, 0, 0);
        initialize_sprite(41, 860, 1387, 0, 0);
        initialize_sprite(41, 620, 867, 0, 0);
        initialize_sprite(41, 560, 547, 0, 0);
        initialize_sprite(42, 760, 460, 0, 0);
        
        initialize_sprite(44, 700, 320, 0, 280);
        
        initialize_sprite(45, 740, 340, 0, 0);
        initialize_sprite(45, 800, 340, 0, 0);
        initialize_sprite(45, 860, 340, 0, 0);
        
        initialize_sprite(1010, 1160, 180, 120, 53);

        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 53) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(53);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES06;
        for (int i = 0; i <= 119; i++){
            for( int t = 0; t <= 299; t++){
                 if( map[i][t] == '2') initialize_wall(20, 20, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(140, 60, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '0') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(100, 0, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(100, 40, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'p') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '>') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'q') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 't') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'u') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '<') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'v') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'y') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'B') { initialize_wall(160, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'C') { initialize_wall(180, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'D') { initialize_wall(200, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'E') { initialize_wall(220, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'F') { initialize_wall(200, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(180, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(180, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(200, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(220, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(200, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'I') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'J') { initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(220, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(200, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
            }       
        }       

        if (player.cards[45] == 0) initialize_sprite(69, 3110, 320, 0, 45);
        if (player.cards[19] == 0) initialize_sprite(69, 5860, 680, 0, 19);
        if (player.cards[9] == 0) initialize_sprite(65, 2820, 1200, 0, 9);
        initialize_sprite(37, 2980, 320, 0, 0);
        initialize_sprite(37, 3180, 320, 1, -40);
        initialize_sprite(37, 540, 800, 0, 0);
        initialize_sprite(37, 540, 840, 0, -10);
        initialize_sprite(37, 540, 880, 0, -20);
        initialize_sprite(37, 780, 800, 1, -30);
        initialize_sprite(37, 780, 840, 1, -40);
        initialize_sprite(37, 780, 880, 1, -50);
        initialize_sprite(38, 4200, 300, 1, 0);
        initialize_sprite(38, 3040, 740, 1, 0);
        initialize_sprite(38, 3720, 740, 1, 0);
        initialize_sprite(38, 2560, 1540, 1, 0);
        initialize_sprite(38, 2620, 1540, 1, -40);
        initialize_sprite(38, 2680, 1540, 1, 0);
        
        initialize_sprite(41, 1220, 267, 0, 0);
        initialize_sprite(41, 3660, 347, 0, 0);
        initialize_sprite(41, 4060, 347, 0, 0);
        initialize_sprite(41, 3860, 347, 1, 0);
        initialize_sprite(41, 4440, 347, 0, 0);
        initialize_sprite(41, 1400, 1347, 0, 0);
        initialize_sprite(41, 1940, 1347, 0, 0);
        initialize_sprite(41, 3640, 1427, 0, 0);
        initialize_sprite(41, 4200, 1427, 0, 0);
        initialize_sprite(42, 3760, 140, 0, 0);
        initialize_sprite(42, 4040, 140, 1, 0);
        initialize_sprite(42, 2900, 620, 0, 0);
        initialize_sprite(42, 3260, 620, 1, 0);
        initialize_sprite(42, 3660, 620, 0, 0);
        initialize_sprite(42, 4000, 620, 1, 0);
        
        initialize_sprite(44, 980, 320, 0, 120);
        initialize_sprite(44, 1500, 320, 0, 160);
        initialize_sprite(44, 1740, 320, 0, 200);
        initialize_sprite(44, 2020, 320, 0, 400);
        initialize_sprite(44, 4760, 760, 0, 1060);
        initialize_sprite(44, 2140, 760, 0, 240);
        initialize_sprite(44, 1700, 760, 0, 160);
        initialize_sprite(44, 1260, 760, 0, 160);
        initialize_sprite(44, 1060, 760, 0, 120);
        initialize_sprite(44, 5300, 2320, 0, 80);
        initialize_sprite(44, 5540, 2320, 0, 140);
        initialize_sprite(44, 5840, 2320, 0, 60);
        
        initialize_sprite(45, 1600, 340, 0, 0);
        initialize_sprite(45, 2100, 340, 0, 0);
        initialize_sprite(45, 2360, 340, 0, 0);
        initialize_sprite(45, 1760, 780, 0, 0);
        initialize_sprite(45, 1100, 780, 0, 0);
        
        initialize_sprite(1011, 4980, 1300, 0, 8);
        initialize_sprite(1011, 5420, 1460, 0, 9);
        initialize_sprite(1006, 5700, 2205, 1, 0);

        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 60) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(60);
        }
        
        texture = TEXTURES07;
        for (int i = 0; i <= 33; i++){
            for( int t = 0; t <= 399; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(60, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'b') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'e') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'f') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'i') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(140, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(160, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') { initialize_wall(160, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(160, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(160, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') { initialize_wall(20, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'O') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(20, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'P') { initialize_wall(0, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') { initialize_wall(0, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'r') { initialize_wall(40, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'R') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 's') { initialize_wall(40, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'S') { initialize_wall(60, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 't') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'T') { initialize_wall(60, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'u') { initialize_wall(100, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(100, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'v') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(80, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'w') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(80, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(120, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(120, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') { initialize_wall(120, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(140, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(140, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(140, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '(') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(140, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(160, 40, 20, 20, 20, t * 20, i * 20);
            }       
        }      
        
        if (player.cards[41] == 0) initialize_sprite(65, 3380, 120, 0, 41);
        if (player.cards[14] == 0) initialize_sprite(69, 6180, 460, 0, 14);
        initialize_sprite(67, 1840, 390, 0, 51);
        initialize_sprite(50, 1140, 277, 0, 0);
        initialize_sprite(50, 2500, 357, 0, 0);
        initialize_sprite(50, 3540, 477, 0, 0);
        initialize_sprite(50, 4880, 517, 0, 0);
        initialize_sprite(50, 7460, 397, 0, 0);
        
        initialize_sprite(51, 4184, 281, 0, 0);
        initialize_sprite(52, 4219, 282, 0, 0);
        initialize_sprite(51, 5624, 361, 0, 0);
        initialize_sprite(52, 5659, 362, 0, 0);
        initialize_sprite(51, 6404, 281, 0, 0);
        initialize_sprite(52, 6439, 282, 0, 0);
        
        initialize_sprite(53, 7140, 492, 0, 140);
        
        initialize_sprite(1010, 7960, 300, 260, 61);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        play_looped_midi(stage_music, 29, 157);
        midi_pos = 5;
        midi_seek(midi_pos);
        if (music_volume_set == 0) midi_pause();

    }
    else if (mapnumber == 61) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(61);
        }
        
        texture = TEXTURES07;
        for (int i = 0; i <= 49; i++){
            for( int t = 0; t <= 399; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(60, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'b') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'e') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'f') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'i') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(140, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(160, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '0') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '0'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') { initialize_wall(160, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(160, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(160, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') { initialize_wall(20, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'O') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(20, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'P') { initialize_wall(0, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') { initialize_wall(0, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'r') { initialize_wall(40, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'R') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 's') { initialize_wall(40, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'S') { initialize_wall(60, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 't') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'T') { initialize_wall(60, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'u') { initialize_wall(100, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(100, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'v') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(80, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'w') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(80, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(120, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(120, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') { initialize_wall(120, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(140, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(140, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(140, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '(') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(140, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(160, 40, 20, 20, 20, t * 20, i * 20);
            }       
        }      

        if (player.cards[49] == 0) initialize_sprite(69, 6540, 280, 1, 49);
        if (player.cards[18] == 0) initialize_sprite(69, 5780, 720, 0, 18);
        initialize_sprite(67, 7460, 810, 0, 44);
        initialize_sprite(50, 1320, 877, 0, 0);
        initialize_sprite(50, 1760, 577, 0, 0);
        initialize_sprite(50, 2760, 517, 0, 0);
        initialize_sprite(50, 3630, 517, 0, 0);
        initialize_sprite(50, 6120, 337, 0, 0);
        initialize_sprite(50, 5320, 817, 0, 0);
        initialize_sprite(50, 7740, 737, 0, 0);
        
        initialize_sprite(51, 544, 541, 0, 0);
        initialize_sprite(52, 579, 542, 0, 0);
        initialize_sprite(51, 1804, 341, 0, 0);
        initialize_sprite(52, 1839, 342, 0, 0);
        initialize_sprite(51, 4384, 141, 0, 0);
        initialize_sprite(52, 4419, 142, 0, 0);
        initialize_sprite(51, 6024, 721, 0, 0);
        initialize_sprite(52, 6059, 722, 0, 0);
        initialize_sprite(51, 7464, 561, 0, 0);
        initialize_sprite(52, 7499, 562, 0, 0);
        
        initialize_sprite(53, 3000, 652, 0, 200);
        initialize_sprite(53, 5320, 352, 0, 140);
        initialize_sprite(53, 6280, 472, 0, 240);
        
        initialize_sprite(55, 1500, 680, 0, 0);
        initialize_sprite(55, 4520, 400, 0, 0);
        
        initialize_sprite(1010, 7960, 580, 120, 62);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 62) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(62);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else if (doorrecord != 12) set_dvalues(doorrecord);
        }
        
        texture = TEXTURES07;
        for (int i = 0; i <= 59; i++){
            for( int t = 0; t <= 199; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(60, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'b') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'e') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'f') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'i') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(140, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(160, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '0') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '0'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') { initialize_wall(160, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(160, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(160, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') { initialize_wall(20, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'O') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(20, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'P') { initialize_wall(0, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') { initialize_wall(0, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'r') { initialize_wall(40, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'R') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 's') { initialize_wall(40, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'S') { initialize_wall(60, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 't') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'T') { initialize_wall(60, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'u') { initialize_wall(100, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(100, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'v') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(80, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'w') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(80, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(120, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(120, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') { initialize_wall(120, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(140, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(140, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(140, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '(') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(140, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(160, 40, 20, 20, 20, t * 20, i * 20);
            }       
        }      

        if (player.cards[23] == 0) initialize_sprite(69, 840, 900, 1, 23);
        if (player.cards[31] == 0) initialize_sprite(69, 2140, 260, 1, 31);
        initialize_sprite(67, 1980, 1010, 0, 46);
        initialize_sprite(1011, 620, 660, 0, 12);
        initialize_sprite(999, 2740, 960, 0, 10);
        initialize_sprite(999, 3350, 960, 0, 11);
        initialize_sprite(2003, 2740, 960, 0, 0);
        initialize_sprite(2002, 3320, 960, 0, 0);
        initialize_sprite(500, 3440, 990, 0, 1);
        initialize_sprite(500, 3460, 990, 0, 2);
        initialize_sprite(500, 3480, 990, 0, 1);
        initialize_sprite(500, 3760, 990, 0, 2);
        initialize_sprite(500, 3780, 990, 0, 1);
        initialize_sprite(500, 3800, 990, 0, 2);
        
        initialize_sprite(50, 660, 257, 0, 0);
        initialize_sprite(50, 1580, 337, 0, 0);
        initialize_sprite(50, 3440, 377, 0, 0);
        initialize_sprite(50, 1660, 617, 0, 0);
        initialize_sprite(50, 2340, 617, 0, 0);
        initialize_sprite(50, 3020, 617, 0, 0);
        initialize_sprite(50, 880, 1097, 0, 0);
        initialize_sprite(50, 1620, 1017, 0, 0);
        
        initialize_sprite(51, 1384, 81, 0, 0);
        initialize_sprite(52, 1419, 82, 0, 0);
        initialize_sprite(51, 2104, 161, 0, 0);
        initialize_sprite(52, 2139, 162, 0, 0);
        initialize_sprite(51, 784, 521, 0, 0);
        initialize_sprite(52, 819, 522, 0, 0);
        
        initialize_sprite(53, 1220, 392, 0, 260);
        initialize_sprite(53, 1940, 432, 0, 500);
        initialize_sprite(53, 2600, 432, 0, 200);
        initialize_sprite(53, 1400, 712, 0, 140);
        
        initialize_sprite(55, 2140, 300, 0, 0);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
            else if (sprites[i].type == 999 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 70) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(70);
        }

        texture = TEXTURES08;
        for (int i = 0; i <= 35; i++){
            for(int t = 0; t <= 499; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') { initialize_wall(60, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '6') { initialize_wall(80, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(60, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') { initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '<') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') { initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '!') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '@') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '#') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '$') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '%') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'W') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'R') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(60, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(80, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Z') initialize_wall(0, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'X') initialize_wall(20, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(40, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'V') initialize_wall(60, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(80, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') { initialize_wall(0, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '^') initialize_wall(20, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '?') initialize_wall(40, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(60, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') { initialize_wall(80, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '7') { initialize_wall(100, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '8') { initialize_wall(120, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(140, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '"') { initialize_wall(160, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '-') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(180, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(140, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(180, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(140, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'L') initialize_wall(160, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Y') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'U') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(140, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') initialize_wall(160, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') { initialize_wall(100, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == ')') { initialize_wall(120, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '_') { initialize_wall(140, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; break; }
                 else if( map[i][t] == '{') { initialize_wall(100, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '}') { initialize_wall(120, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '+') { initialize_wall(140, 120, 20, 20, 20, t * 20, i * 20); break; }
                 else if( map[i][t] == ';') initialize_wall(100, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(120, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '=') { initialize_wall(140, 140,  1, 20, 20, t * 20, i * 20); break; }
                 else if( map[i][t] == '&') initialize_wall(100, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '|') initialize_wall(120, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '`') { initialize_wall(140, 160,  1, 20, 20, t * 20, i * 20); break; }
                 else if( map[i][t] == '~') initialize_wall(100, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(120, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') { initialize_wall(140, 180, 20, 20, 20, t * 20, i * 20); break; }
            }       
        }      

	  initialize_sprite(14, 1380, 340, 0, 0);
	  initialize_sprite(14, 1460, 300, 0, -15);
	  initialize_sprite(14, 2700, 240, 0, 0);

	  initialize_sprite(10, 1660, 460, 0, 0);
	  initialize_sprite(10, 1920, 460, 1, 0);

	  initialize_sprite(12, 2100, 320, 0, 0);

	  initialize_sprite(16, 5280, 380, 2600, 170);

	  initialize_sprite(15, 5200, 300, 0, 0);
	  initialize_sprite(15, 5820, 200, 0, 0);
	  initialize_sprite(15, 6280, 620, 0, 0);

	  initialize_sprite(21, 7520, 510, 0, 0);
	  initialize_sprite(21, 8420, 390, 0, 0);
	  initialize_sprite(21, 9820, 310, 0, 0);

	  initialize_sprite(23, 7600, 300, 0, 0);
	  initialize_sprite(23, 7820, 300, 0, 0);
	  initialize_sprite(23, 9060, 180, 0, 0);
	  initialize_sprite(23, 9420, 100, 0, 0);
	  
	  initialize_sprite(1010, 9960, 160, 360, 71);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
            else if (sprites[i].type == 999 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 71) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(71);
        }

        texture = TEXTURES08;
        for (int i = 0; i <= 39; i += 1, texture = TEXTURES08){
            for(int t = 0; t <= 499; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') { initialize_wall(60, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '6') { initialize_wall(80, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(60, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') { initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '<') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') { initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '!') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '@') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '#') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '$') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '%') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'W') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'R') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(60, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(80, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Z') initialize_wall(0, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'X') initialize_wall(20, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(40, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'V') initialize_wall(60, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(80, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') { initialize_wall(0, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '^') initialize_wall(20, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '?') initialize_wall(40, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(60, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') { initialize_wall(80, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '7') { initialize_wall(100, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '8') { initialize_wall(120, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(140, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '"') { initialize_wall(160, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '-') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(180, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(140, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(180, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(140, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'L') initialize_wall(160, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Y') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'U') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(140, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') initialize_wall(160, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') { initialize_wall(100, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == ')') { initialize_wall(120, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '_') { initialize_wall(140, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '{') { initialize_wall(100, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '}') { initialize_wall(120, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '+') { initialize_wall(140, 120, 20, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == ';') initialize_wall(100, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(120, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '=') { initialize_wall(140, 140,  1, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '&') initialize_wall(100, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '|') initialize_wall(120, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '`') { initialize_wall(140, 160,  1, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '~') initialize_wall(100, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(120, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') { initialize_wall(140, 180, 20, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 if (t == 97) texture = TEXTURES09;
            }       
        }      

        initialize_sprite(23, 820, 140, 0, 0);
        initialize_sprite(23, 1160, 140, 0, 0);

        initialize_sprite(21, 1460, 450, 0, 0);

        initialize_sprite(34, 2200 + 6, 573 + 13, 0, 0);
        initialize_sprite(33, 2200, 573, 0, 0);
        initialize_sprite(34, 3100 + 6, 653 + 13, 0, 0);
        initialize_sprite(33, 3100, 653, 0, 0);
        initialize_sprite(34, 4570 + 6, 573 + 13, 0, 0);
        initialize_sprite(33, 4570, 573, 0, 0);
        initialize_sprite(34, 4630 + 6, 533 + 13, 0, 0);
        initialize_sprite(33, 4630, 533, 0, 0);
        initialize_sprite(34, 3960 + 1, 613 + 13, 1, 0);
        initialize_sprite(33, 3960, 613, 1, 0); 

        initialize_sprite(71, 2660, 800, 0, 0); 
        initialize_sprite(71, 3320, 800, 0, 0); 
        initialize_sprite(71, 4400, 800, 0, 0); 

        initialize_sprite(41, 5700, 407, 0, 0);
        initialize_sprite(41, 6020, 487, 0, 0);
        initialize_sprite(41, 6800, 567, 0, 0);

        initialize_sprite(42, 6900, 320, 0, 0);
        initialize_sprite(42, 7150, 320, 1, 0);
        initialize_sprite(42, 7500, 320, 0, 0);
        initialize_sprite(42, 7740, 320, 1, 0);

        initialize_sprite(50, 8440, 557, 0, 0);
        initialize_sprite(55, 8840, 540, 0, 0);
        initialize_sprite(50, 9200, 557, 0, 0);

	  initialize_sprite(1010, 9960, 240, 240, 72);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
            else if (sprites[i].type == 999 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 72) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(72);
        }

        texture = TEXTURES09;
        for (int i = 0; i <= 39; i += 1, texture = TEXTURES09){
            for(int t = 0; t <= 749; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') { initialize_wall(60, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '6') { initialize_wall(80, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(60, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') { initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '<') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') { initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '!') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '@') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '#') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '$') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '%') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'W') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'R') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(60, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(80, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Z') initialize_wall(0, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'X') initialize_wall(20, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(40, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'V') initialize_wall(60, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(80, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') { initialize_wall(0, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '^') initialize_wall(20, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '?') initialize_wall(40, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(60, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') { initialize_wall(80, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '7') { initialize_wall(100, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '8') { initialize_wall(120, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(140, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '"') { initialize_wall(160, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '-') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(180, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(140, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(180, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(140, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'L') initialize_wall(160, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Y') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'U') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(140, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') initialize_wall(160, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') { initialize_wall(100, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == ')') { initialize_wall(120, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '_') { initialize_wall(140, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '{') { initialize_wall(100, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '}') { initialize_wall(120, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '+') { initialize_wall(140, 120, 20, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == ';') initialize_wall(100, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(120, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '=') { initialize_wall(140, 140,  1, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '&') initialize_wall(100, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '|') initialize_wall(120, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '`') { initialize_wall(140, 160,  1, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '~') initialize_wall(100, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(120, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') { initialize_wall(140, 180, 20, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 if (t == 97) texture = TEXTURES08;
	 	     if (t == 445) texture = TEXTURES09;
            }       
        }      

        initialize_sprite(55, 780, 580, 0, 0);
        initialize_sprite(50, 1080, 477, 0, 0);
        initialize_sprite(55, 1400, 540, 0, 0);

        initialize_sprite(14, 2240, 420, 0, 0);
        initialize_sprite(14, 2880, 290, 0, 0);
        initialize_sprite(14, 2960, 290, 0, -10);
        initialize_sprite(10, 2660, 480, 0, 0);
        initialize_sprite(10, 3100, 480, 0, 0);
        initialize_sprite(12, 3500, 340, 0, 0);

        initialize_sprite(16, 6340, 400, 4020, 200);
        initialize_sprite(15, 4640, 620, 0, 0);
        initialize_sprite(15, 5590, 480, 0, 0);
        initialize_sprite(15, 6300, 340, 0, 0);

        initialize_sprite(23, 7000, 260, 0, 0);
        initialize_sprite(23, 7560, 160, 0, 0);
        initialize_sprite(23, 8660, 300, 0, 0);
        initialize_sprite(21, 7340, 450, 0, 0);
        initialize_sprite(21, 8540, 530, 0, 0);

        initialize_sprite(34, 10010 + 6, 693 + 13, 0, 0);
        initialize_sprite(33, 10010, 693, 0, 0);
        initialize_sprite(34, 10190 + 6, 653 + 13, 0, 0);
        initialize_sprite(33, 10190, 653, 0, 0);
        initialize_sprite(34, 9330 + 1, 693 + 13, 1, 0);
        initialize_sprite(33, 9330, 693, 1, 0);
        initialize_sprite(71, 9730, 800, 0, 0);
        initialize_sprite(71, 10600, 800, 0, 0);
	  initialize_sprite(71, 10680, 800, 0, 0);

        initialize_sprite(41, 11760, 527, 0, 0);
        initialize_sprite(41, 12900, 527, 1, 0);
        initialize_sprite(41, 13200, 567, 0, 0);
        initialize_sprite(42, 11950, 440, 0, 0);
        initialize_sprite(42, 12300, 440, 1, 0);
        initialize_sprite(42, 12660, 440, 0, 0);
        initialize_sprite(42, 12940, 440, 1, 0);

        initialize_sprite(50, 13600, 517, 0, 0);
        initialize_sprite(50, 14000, 437, 1, 0);
        initialize_sprite(55, 14360, 360, 0, 0);

	  initialize_sprite(1010, 14960, 120, 200, 73);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
            else if (sprites[i].type == 999 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 73) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(73);
        }

        texture = TEXTURES09;
        for (int i = 0; i <= 79; i += 1, texture = TEXTURES09){
            for(int t = 0; t <= 149; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') { initialize_wall(60, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '6') { initialize_wall(80, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(60, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') { initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '<') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') { initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '!') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '@') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '#') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '$') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '%') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'W') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'R') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(60, 140, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(80, 140, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Z') initialize_wall(0, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'X') initialize_wall(20, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(40, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'V') initialize_wall(60, 160, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(80, 160, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') { initialize_wall(0, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '^') initialize_wall(20, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '?') initialize_wall(40, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(60, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') { initialize_wall(80, 180, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '7') { initialize_wall(100, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '8') { initialize_wall(120, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(140, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '"') { initialize_wall(160, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '-') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(180, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(140, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(180, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(140, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'L') initialize_wall(160, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'Y') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'U') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(140, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') initialize_wall(160, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') { initialize_wall(100, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == ')') { initialize_wall(120, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '_') { initialize_wall(140, 100,  1, 20, 20, t * 20, i * 20); map[i][t] = '1'; if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '{') { initialize_wall(100, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '}') { initialize_wall(120, 120, 20, 20, 20, t * 20, i * 20); map[i][t] = 'q'; }
                 else if( map[i][t] == '+') { initialize_wall(140, 120, 20, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == ';') initialize_wall(100, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(120, 140,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '=') { initialize_wall(140, 140,  1, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '&') initialize_wall(100, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '|') initialize_wall(120, 160,  1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '`') { initialize_wall(140, 160,  1, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 else if( map[i][t] == '~') initialize_wall(100, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(120, 180, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') { initialize_wall(140, 180, 20, 20, 20, t * 20, i * 20); if (texture == TEXTURES09) texture = TEXTURES08; else texture = TEXTURES09; }
                 if (t == 25) texture = TEXTURES08;
	 	     if (t == 100) texture = TEXTURES09;
            }       
        }      

	  if (lastageportal[0] == 0) initialize_sprite(73, 60, 1140, 0, 74);
	  if (lastageportal[1] == 0) initialize_sprite(73, 540, 1260, 0, 75);
	  if (lastageportal[2] == 0) initialize_sprite(73, 1140, 1460, 0, 76);
	  if (lastageportal[3] == 0) initialize_sprite(74, 1795, 1460, 0, 77);
	  if (lastageportal[4] == 0) initialize_sprite(74, 2395, 1260, 0, 78);
	  if (lastageportal[5] == 0) initialize_sprite(74, 2875, 1140, 0, 79);
	  initialize_sprite(201, 1500, 1260, 0, 0);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
            else if (sprites[i].type == 999 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 47;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 74) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(74);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else if (doorrecord != 12) set_dvalues(doorrecord);
        }
        
        texture = TEXTURES07;
        for (int i = 0; i <= 59; i++){
            for( int t = 0; t <= 199; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(60, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(20, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(40, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'b') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'B') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'C') initialize_wall(140, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'e') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'E') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'f') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'F') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'G') initialize_wall(160, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'H') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'i') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'I') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'J') initialize_wall(140, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'K') initialize_wall(160, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '0') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '0'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') { initialize_wall(160, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(160, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(160, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') { initialize_wall(20, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'O') { initialize_wall(20, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(20, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'P') { initialize_wall(0, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') { initialize_wall(0, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Q') { initialize_wall(0, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'r') { initialize_wall(40, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'R') { initialize_wall(40, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 's') { initialize_wall(40, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'S') { initialize_wall(60, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 't') { initialize_wall(60, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'T') { initialize_wall(60, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'u') { initialize_wall(100, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(100, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'v') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(80, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'w') { initialize_wall(80, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(80, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'x') { initialize_wall(120, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(120, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'y') { initialize_wall(120, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(140, 80, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(140, 100, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(140, 120, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '(') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(140, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(160, 40, 20, 20, 20, t * 20, i * 20);
            }       
        }

        initialize_sprite(500, 3440, 990, 0, 1);
        initialize_sprite(500, 3460, 990, 0, 2);
        initialize_sprite(500, 3480, 990, 0, 1);
        initialize_sprite(500, 3760, 990, 0, 2);
        initialize_sprite(500, 3780, 990, 0, 1);
        initialize_sprite(500, 3800, 990, 0, 2);

        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
            else if (sprites[i].type == 999 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 75) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(75);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        texture = TEXTURES01;
        for (int i = 0; i <= 27; i++){
            for( int t = 0; t <= 199; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(20 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(60 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(20 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(40 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(0 , 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(40 , 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(0 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
            }       
        }
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
    }
    else if (mapnumber == 76) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(76);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES02;
        for (int i = 0; i <= 35; i++){
            for( int t = 0; t <= 299; t++){
                 if( map[i][t] == '2') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(40 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(40 , 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(60 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(80 , 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(60 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(80 , 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') { initialize_wall(100, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'n') { initialize_wall(100, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'w') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'q') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') { initialize_wall(60, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'z') { initialize_wall(80, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
            }       
        }
        initialize_sprite(1002, 5700, 530, 0, 0);        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 77) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(77);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES04;
        for (int i = 0; i <= 31; i++){
            for( int t = 0; t <= 299; t++){
                 if( map[i][t] == '2') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '3') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '4') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '5') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '9') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'b') initialize_wall(20, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'c') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'd') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(40, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'f') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'g') initialize_wall(40, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'h') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(100, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(100, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'p') initialize_wall(120, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'q') initialize_wall(120, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(100, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(0, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'y') initialize_wall(20, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '/') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '#') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '$') initialize_wall(40, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '%') initialize_wall(60, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '*') initialize_wall(80, 100, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '+') initialize_wall(120, 60, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '<') initialize_wall(0, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '>') initialize_wall(20, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ':') initialize_wall(40, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '-') initialize_wall(60, 120, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '_') initialize_wall(80, 120, 20, 20, 20, t * 20, i * 20);
            }       
        }        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;
        
    }
    else if (mapnumber == 78) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(78);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES05;
        for (int i = 0; i <= 39; i++){
            for( int t = 0; t <= 499; t++){
                 if( map[i][t] == '2') { initialize_wall(0, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '3') { initialize_wall(20, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '4') { initialize_wall(40, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '5') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(20, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '7') initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') initialize_wall(0, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') initialize_wall(20, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'D') initialize_wall(40, 20, 1, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '8') { initialize_wall(40, 20, 10, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == '9') { initialize_wall(40, 20, 20, 20, 20, t * 20, i * 20); initialize_wall(40, 20, 2, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'a') { initialize_wall(60, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'b') { initialize_wall(60, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'c') { initialize_wall(80, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'd') { initialize_wall(80, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'e') { initialize_wall(100, 20, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'f') { initialize_wall(100, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'g') { initialize_wall(100, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'h') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'i') { initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'j') { initialize_wall(40, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'k') { initialize_wall(60, 40, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'l') { initialize_wall(120, 0, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'm') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') { initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'o') { initialize_wall(40, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'p') { initialize_wall(60, 60, 2, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'q') initialize_wall(120, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(120, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 't') initialize_wall(100, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'u') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'v') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ',') initialize_wall(80, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(120, 20, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(20, 40, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(40, 40, 12, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '}') initialize_wall(20, 60, 11, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '{') initialize_wall(40, 60, 12, 20, 20, t * 20, i * 20);
                 
            }       
        }       
        initialize_sprite(1005, 9770, 570, 0, 0);
        
        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

    }
    else if (mapnumber == 79) {
        if (dead == 1) { player.imune = 0;
           destroysprite();
           destroywall();
           screenx = 0;
           screeny = 0;
           dead = 0;
           player.direction = 0;
           player.timer = 0;
           player.x_speed = 0;
           player.y_speed = 0;
           if (paulaumfromhell == 0) {
             player.current_weapon = 1;
             player.hp = player.hpmax;
           }
           else paulaumfromhell = 0;
           player.in_water = 0;
           limpation = 0;
           dieanimation = 0;
           input_locked = 0;
           screen_locked = 0;
           bosslife = -1;
           load_map(79);
           if (bossfight == 1) { bossfight = 0; set_dvalues(doorrecord - 1); }
           else set_dvalues(doorrecord);
        }
        
        texture = TEXTURES06;
        for (int i = 0; i <= 119; i++){
            for( int t = 0; t <= 299; t++){
                 if( map[i][t] == '2') initialize_wall(20, 20, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '6') initialize_wall(140, 60, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == '0') initialize_wall(60, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'a') initialize_wall(100, 0, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'e') initialize_wall(100, 40, 1, 40, 40, t * 20, i * 20);
                 else if( map[i][t] == 'i') initialize_wall(20, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'j') initialize_wall(40, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'k') initialize_wall(60, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'l') initialize_wall(20, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'm') initialize_wall(40, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'n') initialize_wall(60, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'o') initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'O') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'p') initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'P') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '>') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'q') initialize_wall(0, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'r') initialize_wall(0, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 's') initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'S') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(0, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 't') initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'T') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 0, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'u') initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '@') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == '<') { initialize_wall(100, 80, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 20, 20, 20, 20, t * 20, i * 20); number_of_walls--; }
                 else if( map[i][t] == 'v') initialize_wall(80, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'w') initialize_wall(80, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'x') initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '!') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); initialize_wall(80, 80, 20, 20, 20, t * 20, i * 20); }
                 else if( map[i][t] == 'y') initialize_wall(20, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'z') initialize_wall(140, 0, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '(') initialize_wall(60, 40, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ')') initialize_wall(60, 60, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'A') { initialize_wall(180, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'B') { initialize_wall(160, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'C') { initialize_wall(180, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'D') { initialize_wall(200, 0, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'E') { initialize_wall(220, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'F') { initialize_wall(200, 20, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'U') { initialize_wall(180, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'V') { initialize_wall(160, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'W') { initialize_wall(180, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'X') { initialize_wall(200, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Y') { initialize_wall(220, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'Z') { initialize_wall(200, 40, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'I') { initialize_wall(20, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'J') { initialize_wall(40, 60, 1, 20, 20, t * 20, i * 20); map[i][t] = '1'; }
                 else if( map[i][t] == 'L') initialize_wall(100, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'M') initialize_wall(120, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == 'N') initialize_wall(180, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == ']') initialize_wall(220, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '[') initialize_wall(200, 80, 20, 20, 20, t * 20, i * 20);
                 else if( map[i][t] == '.') initialize_wall(160, 0, 20, 20, 20, t * 20, i * 20);
            }       
        }       

        initialize_sprite(44, 5300, 2320, 0, 80);
        initialize_sprite(44, 5540, 2320, 0, 140);
        initialize_sprite(44, 5840, 2320, 0, 60);
        initialize_sprite(1006, 5700, 2205, 1, 0);

        player.on_ground = TRUE;
        player.x_position = Map.startingpointx;
        player.y_position = Map.startingpointy;
        player.frame = PLAYER_MOVING01;
        fire_key = 0;
        
        for (int i = 0; i < number_of_sprites; i++) {
            if (sprites[i].type == 1000 && sprites[i].timer == doorrecord) sprites[i].timer = -1;
        }
    
        starting = 1;
        input_locked = 1;
        stopall = 1;
        draw();
        rest(10);
        clear_keybuf();
        speed_counter = 1;
        texture = -1;

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
         Map.limitright = 6960;
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
              bosslife++; event_organizer++;
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
		bibinhafeia = 140965;
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
              bosslife++; event_organizer++;
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
              bosslife++; event_organizer++;
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
          
              bosslife++; event_organizer++;
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
              bosslife++; event_organizer++;
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
              bosslife++; event_organizer++;
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
              bosslife++; event_organizer++;
         }
         else if (event_organizer == 81)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; input_locked = 0; }
     }
     else if (event_number == 15) {
         if (event_organizer > 0 && event_organizer < 35) event_organizer++;
         else if (event_organizer == 35) { initialize_sprite(1001, 3180, -100, 0, 105); event_organizer = 200; }
         else if (event_organizer >= 106 && event_organizer < 136) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; event_organizer++;
         }
         else if (event_organizer == 136)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; }
     }
     else if (event_number == 16) {
         if (event_organizer == 0) {
             event_organizer = 45;
	   }
         else if (event_organizer >= 106 && event_organizer < 136) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; event_organizer++;
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
              bosslife++; event_organizer++;
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
          
              bosslife++; event_organizer++;
         }
         else if (event_organizer == 81)  { event_organizer = 0; call_event = 0; bossfight = 1; lastageboss = 1; input_locked = 0; }
     }
     else if (event_number == 19) {
         if (event_organizer == 0) {
 	 	 event_organizer = 61;
	   }
	   else if (event_organizer >= 61 && event_organizer < 91) {
              if (bosslife == -1) bosslife = 0;
              bosslife++; event_organizer++;
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
    if (key[KEY_K]) damage(15);
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
    lastageportal[0] = lastageportal[1] = lastageportal[2] = lastageportal[3] = lastageportal[4] = lastageportal[5] = 0;
    
    while (!key[KEY_ENTER]) {draw_sprite(screen, title, 0, 0);}
    buffer = create_bitmap(640, 480);
    draw_sprite(buffer, title, 0, 0);
    osutatakaefadeout = 255;
    while(osutatakaefadeout < 255) {
        set_trans_blender(0, 0, 0, 0);
        draw_lit_sprite(screen, buffer, 0, 0, osutatakaefadeout);
        osutatakaefadeout += 5;
    }
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
    current_level = 73;
    
    setup_game();
    while(osutatakaefadeout > 0) {
        draw();
        osutatakaefadeout -= 15;
    }
    speed_counter = 1;
    unsigned script_timer;
    
    do {
        while (speed_counter > 0) {
            input();
	        script_timer++;
	        if (script_timer % 4 == 1) run_scripts();
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
