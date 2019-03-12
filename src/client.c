#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "./client.h"
#include "./net.h"
#include "./game.h"
#include "./event.h"
#include "./render.h"
#include "./ressource.h"

const char *SCREEN_TITLE = "Bomberman";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int enter_game_loop(SDL_Window *window, t_game *game);

int             run_client(const char *address, uint16_t port)
{
    SDL_Window  *window = NULL;
    t_game      *game = NULL;

    window = SDL_CreateWindow(SCREEN_TITLE,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Game window fail to start: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }
    game = create_game((SCREEN_WIDTH / 20) - 1, (SCREEN_HEIGHT / 20) - 1);
    if (!game) {
        fprintf(stderr, "Game game fail to start: %s\n", strerror(errno));
        SDL_DestroyWindow(window);
        return (EXIT_FAILURE);
    }
    if (sync_player(game, address, port) < 0) {
        fprintf(stderr, "Fail to connect server: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (enter_game_loop(window, game) < 0) {
        fprintf(stderr, "Game quit with exception: %s\n", strerror(errno));
        destroy_game(game);
        SDL_DestroyWindow(window);
        return (EXIT_FAILURE);
    }
    destroy_game(game);
    SDL_DestroyWindow(window);
    return (EXIT_SUCCESS);
}

int                 enter_game_loop(SDL_Window *window, t_game *game)
{
    SDL_Renderer    *renderer = NULL;
    t_ressource     *ressource = NULL;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_DestroyRenderer(renderer);
        return (-1);
    }
    ressource = create_ressource(renderer);
    if (!ressource) {
        SDL_DestroyRenderer(renderer);
        return (-1);
    }
    while (game->state != GAME_EXIT) {
        SDL_RenderClear(renderer);
        if (game->state == GAME_RUN) {
            sub_sever_inputs(game);
            sub_inputs(game);
            render_entites(renderer, ressource, game->map);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    	SDL_Delay(100);
    }
    destroy_ressource(ressource);
    SDL_DestroyRenderer(renderer);
    return (1);
}
