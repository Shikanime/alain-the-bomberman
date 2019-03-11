#include <unistd.h>
#include "./render.h"
#include "./render/bomberman.h"
#include "./render/bomb.h"
#include "./render/button.h"

void render_entites(SDL_Renderer *renderer, t_ressource *resssource, t_map *map)
{
    for (size_t i = 0; i < map->height; i++) {
        render_bomberman(renderer, resssource->bomb, map->matrix[i].bomberman);
        render_bomb(renderer, resssource->bomb, map->matrix[i].bomb);
    }
}

void render_menu(SDL_Renderer *renderer, t_ressource *resssource, t_menu *menu)
{
    (void) resssource;

    render_button(renderer, menu->client_mode);
    render_button(renderer, menu->server_mode);
}
