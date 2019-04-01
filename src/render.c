#include <unistd.h>
#include "./render.h"
#include "./render/bomberman.h"
#include "./render/bomb.h"
#include "./render/button.h"
#include "./render/env.h"

void sub_renderer(t_client *client, SDL_Renderer *renderer, t_ressource *ressource)
{
    switch (client->state) {
        case CLIENT_GAME:
        case CLIENT_GAME_INIT:
            for (size_t i = 0; i < client->map->height; i++) {
                for (size_t j = 0; j < client->map->width; j++) {
                    if (client->map->matrix[i][j].bomberman != NULL) {
                        render_bomberman(renderer, ressource->bomberman[client->map->matrix[i][j].bomberman->skin], (int)j, (int)i);
                    } else if (client->map->matrix[i][j].bomb != NULL) {
                        render_bomb(renderer, ressource->bomb, (int)j, (int)i);
                    } else {
                        render_env(renderer, ressource->env[client->map->matrix[i][j].env], (int)j, (int)i);
                    }
                }
            }
            break;

        case CLIENT_MENU:
            render_button(renderer, ressource->font, "Join server", 200, 40, 220, 60, client->nav->cursor == JOIN_GAME ? true : false);
            render_button(renderer, ressource->font, "Create server", 200, 40, 220, 100, client->nav->cursor == CREATE_GAME ? true : false);
            break;

        default:
            break;
    }
}
