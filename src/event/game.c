#include <string.h>
#include "../net/socket.h"
#include "../action/movement.h"
#include "../action/placement.h"
#include "../action/attack.h"

void        handle_game_inputs(SDL_Event *event, t_game *game)
{
    char    res_buff[20];

    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_UP:
                    if (move_bomberman_up(bomberman, game->player_x, game->player_y)) {
                        sprintf(res_buff, "mv up %d %d", game->player_x, game->player_y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_DOWN:
                    if (move_bomberman_down(bomberman, game->player_x, game->player_y)) {
                        sprintf(res_buff, "mv down %d %d", game->player_x, game->player_y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_LEFT:
                    if (move_bomberman_left(bomberman, game->player_x, game->player_y)) {
                        sprintf(res_buff, "mv left %d %d", game->player_x, game->player_y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_RIGHT:
                    if (move_bomberman_right(map, game->player_x, game->player_y)) {
                        sprintf(res_buff, "mv right %d %d", game->player_x, game->player_y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_SPACE:
                    if (allahu_akbar(game->player, game->player_x, game->player_y)) {
                        sprintf(res_buff, "bomb %d %d", game->player_x, game->player_y);
                        send_event(game->server, res_buff);
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

void handle_game_events(t_game *game)
{
    if (strncmp(buff, "spawn", 5) == 0) {
        char    nb_buff[2];
        int     x = 0;
        int     y = 0;

        strncpy(nb_buff, buff + 7, 1);
        x = atoi(nb_buff);
        strncpy(nb_buff, buff + 9, 1);
        y = atoi(nb_buff);
        place_bomberman(game->map, create_bomberman(), x, y);
    }
}

void handle_game_broadcasts(t_conn *s, int fd, char *packet)
{
    if (strncmp(packet, "spawn", 5) == 0) {
        broadcast_event(s, fd, packet);
    }
}
