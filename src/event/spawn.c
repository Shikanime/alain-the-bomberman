#include "./spawn.h"
#include "../system/bomberman.h"

void        handle_spawn_packets(t_client *client, char *packet)
{
    int     x = 0;
    int     y = 0;

    if (strncmp(packet, "spawn", 5) == 0) {
        switch (client->state) {
            case CLIENT_GAME_INIT:
                if (sscanf(packet, "spawn 1 %02d %02d", &x, &y) == 2) {
                    if (place_bomberman(client->map, create_bomberman(), x, y)) {
                        client->player->x = x;
                        client->player->y = y;
                    }
                }
                break;

            case CLIENT_GAME:
                if (sscanf(packet, "spawn 1 %02d %02d", &x, &y) == 2) {
                    place_bomberman(client->map, create_bomberman(), x, y);
                } else if (sscanf(packet, "spawn 2 1 %02d %02d", &x, &y) == 2) {
                    allahu_akbar(client->map, create_bomb(BOMB_BASIC_TYPE, SDL_GetTicks()), x, y);
                }
                break;

            default:
                break;
        }
    }
}
