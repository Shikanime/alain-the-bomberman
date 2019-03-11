#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./action/placement.h"
#include "./event/hero.h"

#ifdef __APPLE__
#define MSG_NOSIGNAL 0x2000
#endif

void        sub_events(t_game *game) {
    char    buff[MESSAGE_LENGTH];

    if (recv(game->client->fd, buff, MESSAGE_LENGTH, MSG_DONTWAIT | MSG_NOSIGNAL) > 0) {
        if (strncmp(buff, "spawn", 5) == 0) {
            char    nb_buff[2];
            int     pos_x = 0;
            int     pos_y = 0;

            strncpy(nb_buff, buff + 7, 1);
            pos_x = atoi(nb_buff);

            strncpy(nb_buff, buff + 9, 1);
            pos_y = atoi(nb_buff);

            place_hero(game->env, create_hero(pos_x, pos_y));
        }
    }
}

void            sub_inputs(e_game_flow *state, t_game *game)
{
    SDL_Event   event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *state = GAME_FLOW_EXIT;
        }
        if (*state == GAME_FLOW_MENU) {
            handle_menu_inputs(&event, game);
        }
        if (*state == GAME_FLOW_RUN) {
            handle_hero_inputs(&event, game);
        }
    }
}
