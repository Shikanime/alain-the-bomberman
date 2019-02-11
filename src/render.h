#pragma once

#include <SDL2/SDL.h>
#include "./model/entity/env.h"
#include "./model/ui/menu.h"

void render_entites(SDL_Renderer *renderer, t_env *env);
void render_menu(SDL_Renderer *renderer, t_menu *menu);
