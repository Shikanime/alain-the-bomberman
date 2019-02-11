#include <stdio.h>
#include <unistd.h>
#include "./game.h"
#include "./client.h"
#include "./engine.h"
#include "./net.h"
#include "./event.h"
#include "./render.h"
#include "./model/ui/menu.h"
#include "./action/placement.h"

const Uint32 SDL_CONFIG = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;

int enter_game_loop(t_engine *engine, t_game *game);

int             run_client(const char *address, uint16_t port)
{
    t_engine    *engine = NULL;
    t_game      *game = NULL;

    if (SDL_Init(SDL_CONFIG) < 0) {
        return (EXIT_FAILURE);
    }
    engine = create_engine();
    if (!engine) {
        fprintf(stderr, "Game engine fail to start");
        return (EXIT_FAILURE);
    }
    game = create_game(address, port);
    if (!game) {
        fprintf(stderr, "Game instance fail to start");
        destroy_engine(engine);
        SDL_Quit();
        return (EXIT_FAILURE);
    }
    place_hero(game->env, game->player);
    if (enter_game_loop(engine, game) < 0) {
        fprintf(stderr, "Game quit with exception");
        destroy_engine(engine);
        destroy_game(game);
        SDL_Quit();
        return (EXIT_FAILURE);
    }
    destroy_engine(engine);
    destroy_game(game);
    SDL_Quit();
    return (EXIT_SUCCESS);
}

int                 enter_game_loop(t_engine *engine, t_game *game)
{
    SDL_Renderer    *renderer = SDL_CreateRenderer(engine->window, -1, 0);
    e_game_flow     state = GAME_FLOW_RUN;

    if (!renderer) {
        SDL_DestroyRenderer(renderer);
        return (-1);
    }
    while (state != GAME_FLOW_EXIT) {
        if (state == GAME_FLOW_MENU) {
            t_menu  *menu = create_menu();
            sub_events(game);
            sub_inputs(&state, game);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            render_menu(renderer, menu);
        } else if (state != GAME_FLOW_SKIP && state != GAME_FLOW_EXIT) {
            sub_events(game);
            sub_inputs(&state, game);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            render_entites(renderer, game->env);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    return (0);
}
