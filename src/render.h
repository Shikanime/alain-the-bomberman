#pragma once

#include <SDL2/SDL.h>
#include "./ressource.h"
#include "./game/env.h"
#include "./model/ui/menu.h"

void render_entites(SDL_Renderer *renderer, t_ressource *resssource, t_env *env);
void render_menu(SDL_Renderer *renderer, t_menu *menu);
