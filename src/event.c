#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./event/game.h"
#include "./event/mv.h"
#include "./event/spawn.h"
#include "./event/explosion.h"
#include "./event/supply.h"
#include "./event/terrain.h"
#include "./net.h"
#include "./net/conn.h"
#include "./system/bomb.h"

void            sub_inputs(t_client *client)
{
    SDL_Event   event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            client->state = CLIENT_EXIT;
        } else {
            switch (client->state) {
                case CLIENT_MENU:
                    handle_menu_inputs(&event, client);
                    break;

                case CLIENT_GAME:
                    handle_game_inputs(&event, client);
                    break;

                default:
                    break;
            }
        }
    }
}

void sub_events(t_client *client)
{
    switch (client->state) {
        case CLIENT_GAME:
            for (size_t i = 0; i < client->map->height; i++) {
                for (size_t j = 0; j < client->map->width; j++) {
                    handle_explosion_events(client, (int)j, (int)i);
                    handle_provisioning_event(client, (int)j, (int)i);
                }
            }
            if (client->player_nb <= 1) {
                client->state = CLIENT_EXIT;
            }
            break;

        default:
            break;
    }
}

void        sub_server_packets(t_client *client)
{
    char    packet[FIXED_PACKET_LENGHT];

    switch (client->state)
    {
        case CLIENT_GAME:
        case CLIENT_GAME_INIT:
            if (recv(client->server->fd, packet, FIXED_PACKET_LENGHT, MSG_DONTWAIT) >= 0) {
                handle_spawn_packets(client, packet);
                handle_terrain_packets(client, packet);
                handle_mv_packets(client, packet);
                handle_game_packets(client, packet);
            }
            break;

        default:
            break;
    }
}

void sub_client_packets(t_server *server)
{
    if (select(FD_SETSIZE, &server->conn->read_set, NULL, NULL, NULL) >= 0) {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &server->conn->read_set)) {
                if (i == server->conn->fd) {
                    if (server->player_nb < server->player_capacity) {
                        if (handle_join(server) < 0) {
                            printf("Fail to join socket of fd: %d\n", i);
                        }
                    }
                    if (server->player_nb == server->player_capacity) {
                        char packet[FIXED_PACKET_LENGHT];

                        sprintf(packet, "ready");
                        broadcast_packet(server->conn, server->conn->fd, packet);
                    }
                } else {
                    if (handle_packet(server, i) < 0) {
                        printf("Fail to handle a message from fd: %d\n", i);
                    }
                }
            }
        }
    }
}
