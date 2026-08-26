#ifndef INTRO_H
#define INTRO_H

#include <allegro.h>

#include "player.h"
#include "timing.h"
#include "data.h"

class Game;

extern Game *game;

void intro_sequence(BITMAP *buffer);
void draw_intro_sequence(BITMAP *buffer, double *timer, double fade_n, bool fadein, bool fadeout);
void draw_fall_sequence(BITMAP *buffer, int pivot_factor, double center, bool fadein, bool fadeout);
void myend();
void drawend(Player player, int ending, int fadeout, int light_level, int sealevel, int scenario_width, int screenx, int screeny, int endtextx, int endtextw, BITMAP *endtext, BITMAP *buffer, BITMAP *background, BITMAP *scenario);
void myendsp();
void drawendsp();

#endif
