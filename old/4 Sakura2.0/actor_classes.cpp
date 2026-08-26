#include "actor_classes.h"

/*CYellowShot::CYellowShot(int x, int y, int d)
{
    active = 1;
    type = 1;
    width = 10;
    height = 10;
    frame = YELLOW_TOSKO_SHOT;
    x_position = x;
    y_position = y;
    direction = d;
    if (direction == 0) x_speed = 5;
    else x_speed = -5;
    play_sample((SAMPLE *)mydatafile[TIRO1].dat, (int)(205 * sound_volume_set / 255), 128, 1000, 0);
}

void CYellowShot::actor_update(Game *game, Player *player)
{
    for (int i = 0; i < 6; i++)
    {
        x_position += x_speed;
        game->actor_colision(this);
        if (!active) break;
    }
    if (active)
    {
        if (x_position > player->x_position && x_position - player->x_position > 640) this->animation(game);
        else if (x_position < player->x_position && player->x_position - x_position > 640) this->animation(game);
    }
}

void CYellowShot::animation(Player *player)
{
    type = 100;
    y_position -= 5;
    x_position -= 5;
    width = 20;
    height = 20;
    timer = 0;
    frame = SHOT_0_1;
    x_speed = 0;
    y_speed = 0;
    player.shots--;
}

C::C(int x, int y, int d, int t)
{

}

void C::actor_update(Player player, void (*actor_colision)(Actor))
{

}
*/


