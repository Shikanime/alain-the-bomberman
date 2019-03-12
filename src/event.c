#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./event/game.h"
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

void sub_internal_events(t_game *game) {
    for (size_t i = 0; i < game->map->height; i++) {
        for (size_t j = 0; j < game->map->width; j++) {
            if (game->map->matrix[i][j].bomb != NULL) {
                if (SDL_GetTicks() - game->map->matrix[i][j].bomb->drop_time > 5000) {
                    bomb_explosion(game->map, game->map->matrix[i][j].bomb, j, i);
                }
            }
        }
    }
}

void        sub_sever_events(t_game *game)
{
    char    packet_msg_buff[20];

    if (recv(game->server->fd, packet_msg_buff, 20, MSG_DONTWAIT) >= 0) {
        switch (game->state) {
            case GAME_RUN:
                handle_game_server_events(game, packet_msg_buff);
                break;

            default:
                break;
        }
    }
}
void sub_client_events(t_conn *s)
{
    s->read_set = s->active_set;
    if (select(FD_SETSIZE, &s->read_set, NULL, NULL, NULL) >= 0) {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &s->read_set)) {
                if (i == s->fd) {
                    if (handle_join(s) < 0) {
                        printf("Fail to join socket of fd: %d\n", i);
                    }
                } else {
                    if (handle_packet(s, i) < 0) {
                        printf("Fail to handle a message from fd: %d\n", i);
                    }
                }
            }
        }
    }
}
