#include "./terrain.h"

void        handle_terrain_packets(t_client *client, char *packet)
{
    int     x = 0;
    int     y = 0;

    if (strncmp(packet, "terrain", 7) == 0) {
        switch (client->state) {
            case CLIENT_GAME_INIT:
                if (sscanf(packet, "terrain 1 %02d %02d", &x, &y) == 2) {
                    client->map->matrix[y][x].env = ENV_WALL;
                }
                break;

            default:
                break;
        }
    }
}
