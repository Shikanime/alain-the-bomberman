#include "./mv.h"
#include "../system/bomberman.h"
#include "../compute/movement.h"

void        handle_mv_packets(t_client *client, char *packet)
{
    int     x = 0;
    int     y = 0;

    if (strncmp(packet, "mv", 2) == 0) {
        switch (client->state) {
            case CLIENT_GAME:
                if (sscanf(packet, "mv 1 %02d %02d", &x, &y) == 2) {
                    move_bomberman(client->map, x, y, x, compute_bomberman_up_move(client->map, y));
                } else if (sscanf(packet, "mv 2 %02d %02d", &x, &y) == 2) {
                    move_bomberman(client->map, x, y, x, compute_bomberman_down_move(client->map, y));
                } else if (sscanf(packet, "mv 3 %02d %02d", &x, &y) == 2) {
                    move_bomberman(client->map, x, y, compute_bomberman_left_move(client->map, x), y);
                } else if (sscanf(packet, "mv 4 %02d %02d", &x, &y) == 2) {
                    move_bomberman(client->map, x, y, compute_bomberman_right_move(client->map, x), y);
                }
                break;

            default:
                break;
        }
    }
}
