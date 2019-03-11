#include <string.h>
#include "./game.h"
#include "../net.h"
#include "../net/conn.h"
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
                    if (move_bomberman_up(game->map, game->player)) {
                        sprintf(res_buff, "mv up %d %d", game->player->x, game->player->y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_DOWN:
                    if (move_bomberman_down(game->map, game->player)) {
                        sprintf(res_buff, "mv down %d %d", game->player->x, game->player->y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_LEFT:
                    if (move_bomberman_left(game->map, game->player)) {
                        sprintf(res_buff, "mv left %d %d", game->player->x, game->player->y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_RIGHT:
                    if (move_bomberman_right(game->map, game->player)) {
                        sprintf(res_buff, "mv right %d %d", game->player->x, game->player->y);
                        send_event(game->server, res_buff);
                    }
                    break;

                case SDLK_SPACE:
                    if (allahu_akbar(game->map, game->player)) {
                        sprintf(res_buff, "bomb %d %d", game->player->x, game->player->y);
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

void        handle_server_events(t_game *game, char *packet)
{
    int     x = 0;
    int     y = 0;

    if (sscanf(packet, "spawn %02d %02d", &x, &y) == 2) {
        place_bomberman(game->map, create_bomberman(), x, y);
        printf("A new player have been connected at %d:%d", x, y);
    } else if (sscanf(packet, "mv down %02d %02d", &x, &y) == 2) {
        t_player *player = malloc(sizeof(t_player));

        player->x = x;
        player->y = y;
        move_bomberman_down(game->map, player);
    } else if (sscanf(packet, "mv up %02d %02d", &x, &y) == 2) {
        t_player *player = malloc(sizeof(t_player));

        player->x = x;
        player->y = y;
        move_bomberman_up(game->map, player);
    } else if (sscanf(packet, "mv right %02d %02d", &x, &y) == 2) {
        t_player *player = malloc(sizeof(t_player));

        player->x = x;
        player->y = y;
        move_bomberman_right(game->map, player);
    } else if (sscanf(packet, "mv left %02d %02d", &x, &y) == 2) {
        t_player *player = malloc(sizeof(t_player));

        player->x = x;
        player->y = y;
        move_bomberman_left(game->map, player);
    }
}
