#ifndef WALL_H
#define WALL_H

#include <allegro.h>
#include <list>

#include "timing.h"

class Wall
{
public:
    char active;

    int type;
    int width, height;

    float x_position, y_position;

    Wall(int framex, int framey, int type, int w, int h, int x, int y, int texture, BITMAP *scenario, BITMAP *foreground);
};

typedef std::list<Wall> WallList;

#endif
