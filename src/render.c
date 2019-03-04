#include <unistd.h>
#include "./render.h"
#include "./render/hero.h"
#include "./render/bomb.h"
#include "./render/button.h"

void render_entites(SDL_Renderer *renderer, t_ressource *resssource, t_env *env)
{
    for (size_t i = 0; i < env->hero_nb; i++) {
        render_hero(renderer, env->heros[i]);
    }

    for (size_t i = 0; i < env->bomb_nb; i++) {
        render_bomb(renderer, resssource->bomb, env->bombs[i]);
    }
}

void render_menu(SDL_Renderer *renderer, t_menu *menu)
{
    render_button(renderer, menu->client_mode);
    render_button(renderer, menu->server_mode);
}
