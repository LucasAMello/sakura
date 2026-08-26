#include "wall.h"

Wall::Wall(int framex, int framey, int type, int w, int h, int x, int y, int texture, BITMAP *scenario, BITMAP *foreground)
{
    this->type = type;
    active = 1;
    width = w;
    height = h;
    x_position = x;
    y_position = y;
    if (type == 1)
    {
        blit((BITMAP*)mydatafile[texture].dat, scenario, framex, framey, x, y, w, h);
    }
    else if (type == 2)
    {
        blit((BITMAP*)mydatafile[texture].dat, foreground, framex, framey, x, y, w, h);
    }
    else if (type == 20) masked_blit((BITMAP*)mydatafile[texture].dat, scenario, framex, framey, x, y, w, h);
    else if (type == 10) masked_blit((BITMAP*)mydatafile[texture].dat, foreground, framex, framey, x, y, w, h);
    else if (type == 11)
    {
        masked_blit((BITMAP*)mydatafile[texture].dat, scenario, framex - 20, framey, x, y, w, h);
        masked_blit((BITMAP*)mydatafile[texture].dat, foreground, framex, framey, x, y, w, h);
    }
    else if (type == 12)
    {
        masked_blit((BITMAP*)mydatafile[texture].dat, scenario, framex, framey, x, y, w, h);
        masked_blit((BITMAP*)mydatafile[texture].dat, foreground, framex - 40, framey, x, y, w, h);
    }
}
