#include "./explosion.h"
#include "../system/bomb.h"

void handle_explosion_events(t_client *client, int x, int y)
{
    if (client->map->matrix[y][x].bomb != NULL) {
        if (SDL_GetTicks() - client->map->matrix[y][x].bomb->drop_time > 2000) {
            bomb_explosion(client->map, client->map->matrix[y][x].bomb, (int)x, (int)y);
        }
        if (client->map->matrix[y][x].bomberman != NULL) {
            client->player_nb++;
        }
    }
}
