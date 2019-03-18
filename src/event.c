#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./event/game.h"
#include "./event/navigation.h"
#include "./net.h"
#include "./net/conn.h"
#include "./system/bomb.h"

void            sub_input_events(t_client *client)
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

                case CLIENT_RUN:
                    handle_game_inputs(&event, client);
                    break;

                default:
                    break;
            }
        }
    }
}

void        sub_navigation_events(t_client *client)
{
    char    packet_msg_buff[FIXED_PACKET_LENGHT];

    switch (client->state)
    {
        case CLIENT_INIT:
            if (recv(client->server->fd, packet_msg_buff, FIXED_PACKET_LENGHT, MSG_DONTWAIT) >= 0) {
                handle_game_server_init(client, packet_msg_buff);
            }
            break;

        default:
            handle_navigation_events(client);
            break;
    }
}

void sub_game_events(t_client *client) {
    handle_game_events(client);
}

void        sub_server_packets(t_client *client)
{
    char    packet_msg_buff[FIXED_PACKET_LENGHT];

    if (recv(client->server->fd, packet_msg_buff, FIXED_PACKET_LENGHT, MSG_DONTWAIT) >= 0) {
        switch (client->state) {
            case CLIENT_RUN:
                handle_game_server_packets(client, packet_msg_buff);
                break;

            default:
                break;
        }
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
