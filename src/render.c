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
                render_bomberman(renderer, NULL, (int)j, (int)i);
            } else if (map->matrix[i][j].bomb != NULL) {
                render_bomb(renderer, resssource->bomb, (int)j, (int)i);
            } else if (map->matrix[i][j].env == ENV_GROUND) {
                render_ground(renderer, NULL, (int)j, (int)i);
            } else if (map->matrix[i][j].env == ENV_WALL) {
                render_wall(renderer, NULL, (int)j, (int)i);
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
