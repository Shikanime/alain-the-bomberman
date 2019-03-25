#include "./spawn.h"
#include "../system/bomberman.h"

void        handle_spawn_packets(t_client *client, char *packet)
{
    int     type = 0;
    int     x = 0;
    int     y = 0;

    if (strncmp(packet, "spawn", 5) == 0) {
        switch (client->state) {
            case CLIENT_GAME_INIT:
                if (sscanf(packet, "spawn 1 %d %02d %02d", &type, &x, &y) == 3) {
                    if (place_bomberman(client->map, create_bomberman((e_bomberman_skin) type), x, y)) {
                        if (client->player == NULL) {
                            client->player = create_player(x, y);
                            printf("Player spawn at: %d:%d\n", x, y);
                        }
                        client->player_nb++;
                    }
                }
                break;

            case CLIENT_GAME:
                if (sscanf(packet, "spawn 2 1 %02d %02d", &x, &y) == 2) {
                    allahu_akbar(client->map, create_bomb(BOMB_BASIC_TYPE, SDL_GetTicks()), x, y);
                }
                break;

            default:
                break;
        }
    }
}
