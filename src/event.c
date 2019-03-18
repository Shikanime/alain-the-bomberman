#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./event/game.h"
#include "./event/mv.h"
#include "./event/spawn.h"
#include "./event/explosion.h"
#include "./event/terrain.h"
#include "./event/navigation.h"
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
            handle_game_events(client);
            for (size_t i = 0; i < client->map->height; i++) {
                for (size_t j = 0; j < client->map->width; j++) {
                    handle_explosion_events(client, j, i);
                }
            }
            break;

        default:
            handle_navigation_events(client);
            break;
    }
}

void        sub_server_packets(t_client *client)
{
    char    packet[FIXED_PACKET_LENGHT];

    if (recv(client->server->fd, packet, FIXED_PACKET_LENGHT, MSG_DONTWAIT) >= 0) {
        handle_game_packets(client, packet);
        handle_mv_packets(client, packet);
        handle_spawn_packets(client, packet);
        handle_terrain_packets(client, packet);
    }
}

void sub_client_packets(t_server *server)
{
    server->conn->read_set = server->conn->active_set;
    if (select(FD_SETSIZE, &server->conn->read_set, NULL, NULL, NULL) >= 0) {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &server->conn->read_set)) {
                if (i == server->conn->fd) {
                    if (handle_join(server) < 0) {
                        printf("Fail to join socket of fd: %d\n", i);
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
