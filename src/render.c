#include <unistd.h>
#include "./render.h"
#include "./render/bomberman.h"
#include "./render/bomb.h"
#include "./render/button.h"
#include "./render/env.h"

void render_entites(SDL_Renderer *renderer, t_ressource *resssource, t_map *map)
{
    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            if (map->matrix[i][j].bomberman != NULL) {
                render_bomberman(renderer, resssource->bomberman[map->matrix[i][j].bomberman->skin], (int)j, (int)i);
            } else if (map->matrix[i][j].bomb != NULL) {
                render_bomb(renderer, resssource->bomb, (int)j, (int)i);
            } else {
                render_env(renderer, resssource->env[map->matrix[i][j].env], (int)j, (int)i);
            }
        }
    }
}

void render_menu(SDL_Renderer *renderer, t_ressource *resssource, t_menu *menu)
{
    (void) resssource;
    (void) menu;

    render_button(renderer, NULL, 200, 200, 10, 10);
    render_button(renderer, NULL, 200, 200, 10, 20);
}
