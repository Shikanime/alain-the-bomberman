#include "./supply.h"
#include "../system/bomberman.h"

void handle_provisioning_event(t_client *client, int x, int y)
{
    if (client->map->matrix[y][x].bomberman != NULL) {
        if (SDL_GetTicks() - client->map->matrix[y][x].bomberman->bomb_supply_time > BOMB_PROVISIONNING) {
            if (supply_bomberman(client->map, x, y)) {
                client->map->matrix[y][x].bomberman->bomb_supply_time = SDL_GetTicks();
            }
        }
    }
}
