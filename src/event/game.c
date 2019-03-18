#include <string.h>
#include "./game.h"
#include "../net.h"
#include "../net/conn.h"
#include "../system/bomb.h"
#include "../system/bomberman.h"
#include "../compute/movement.h"

void        handle_game_inputs(SDL_Event *event, t_client *client)
{
    char    packet[FIXED_PACKET_LENGHT];
    int     x = 0;
    int     y = 0;

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_UP:
                    y = compute_bomberman_up_move(client->map, client->player->y);
                    if (move_bomberman(client->map, client->player->x, client->player->y, client->player->x, y)) {
                        sprintf(packet, "mv 1 %02d %02d", client->player->x, client->player->y);
                        send_packet(client->server->fd, packet);
                        client->player->y = y;
                    }
                    break;

                case SDLK_DOWN:
                    y = compute_bomberman_down_move(client->map, client->player->y);
                    if (move_bomberman(client->map, client->player->x, client->player->y, client->player->x, y)) {
                        sprintf(packet, "mv 2 %02d %02d", client->player->x, client->player->y);
                        send_packet(client->server->fd, packet);
                        client->player->y = y;
                    }
                    break;

                case SDLK_LEFT:
                    x = compute_bomberman_left_move(client->map, client->player->x);
                    if (move_bomberman(client->map, client->player->x, client->player->y, x, client->player->y)) {
                        sprintf(packet, "mv 3 %02d %02d", client->player->x, client->player->y);
                        send_packet(client->server->fd, packet);
                        client->player->x = x;
                    }
                    break;

                case SDLK_RIGHT:
                    x = compute_bomberman_right_move(client->map, client->player->x);
                    if (move_bomberman(client->map, client->player->x, client->player->y, x, client->player->y)) {
                        sprintf(packet, "mv 4 %02d %02d", client->player->x, client->player->y);
                        send_packet(client->server->fd, packet);
                        client->player->x = x;
                    }
                    break;

                case SDLK_SPACE:
                    if (allahu_akbar(client->map, create_bomb(BOMB_BASIC_TYPE, SDL_GetTicks()), client->player->x, client->player->y)) {
                        sprintf(packet, "spawn 2 1 %02d %02d", client->player->x, client->player->y);
                        send_packet(client->server->fd, packet);
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void handle_game_events(t_client *client)
{
    if (client->map->matrix[client->player->y][client->player->x].bomberman == NULL) {
        client->state = CLIENT_GAME_OUT;
    }
}

void handle_game_packets(t_client *client, char *packet)
{
    switch (client->state) {
        case CLIENT_GAME_INIT:
            if (strncmp(packet, "ready", 5) == 0) {
                client->state = CLIENT_GAME;
            }
            break;

        default:
            break;
    }
}
