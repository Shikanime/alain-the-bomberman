#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./event/game.h"
#include "./event/navigation.h"
#include "./net.h"
#include "./net/conn.h"
#include "./system/bomb.h"

void            sub_input_events(t_game *game)
{
    SDL_Event   event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->state = GAME_EXIT;
        } else {
            switch (game->state) {
                case GAME_MENU:
                    handle_menu_inputs(&event, game);
                    break;

                case GAME_RUN:
                    handle_game_inputs(&event, game);
                    break;

                default:
                    break;
            }
        }
    }
}

void        sub_navigation_events(t_game *game)
{
    char    packet_msg_buff[FIXED_PACKET_LENGHT];

    switch (game->state)
    {
        case GAME_INIT:

            if (recv(game->server->fd, packet_msg_buff, FIXED_PACKET_LENGHT, MSG_DONTWAIT) >= 0) {
                handle_game_server_init(game, packet_msg_buff);
            }
            break;

        default:
            handle_navigation_events(game);
            break;
    }
}

void sub_internal_events(t_game *game) {
    handle_game_internal_events(game);
}

void        sub_sever_events(t_game *game)
{
    char    packet_msg_buff[FIXED_PACKET_LENGHT];

    if (recv(game->server->fd, packet_msg_buff, FIXED_PACKET_LENGHT, MSG_DONTWAIT) >= 0) {
        switch (game->state) {
            case GAME_RUN:
                handle_game_server_events(game, packet_msg_buff);
                break;

            default:
                break;
        }
    }
}
void sub_client_events(t_conn *server, t_map *map)
{
    server->read_set = server->active_set;
    if (select(FD_SETSIZE, &server->read_set, NULL, NULL, NULL) >= 0) {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &server->read_set)) {
                if (i == server->fd) {
                    if (handle_join(server, map) < 0) {
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
