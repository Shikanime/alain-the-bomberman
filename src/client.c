#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "./game.h"
#include "./client.h"
#include "./net.h"
#include "./event.h"
#include "./render.h"
#include "./ressource.h"
#include "./model/ui/menu.h"
#include "./action/placement.h"

const Uint32 SDL_CONFIG = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
const char *SCREEN_TITLE = "Bomberman";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int8_t init_subsystem();
void quit_subsystem();
int enter_game_loop(SDL_Window *window, t_game *game);

int             run_client(const char *address, uint16_t port)
{
    SDL_Window  *window = NULL;
    t_game      *game = NULL;

    if (init_subsystem() < 0) {
        return (EXIT_FAILURE);
    }
    window = SDL_CreateWindow(SCREEN_TITLE,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Game window fail to start: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    game = create_game(address, port);
    if (!game) {
        fprintf(stderr, "Game instance fail to start: %s\n", strerror(errno));
        SDL_DestroyWindow(window);
        quit_subsystem();
        return (EXIT_FAILURE);
    }
    place_hero(game->env, game->player);
    send_event(game->client, "spawn");
    if (enter_game_loop(window, game) < 0) {
        fprintf(stderr, "Game quit with exception: %s\n", strerror(errno));
        destroy_game(game);
        SDL_DestroyWindow(window);
        quit_subsystem();
        return (EXIT_FAILURE);
    }
    destroy_game(game);
    SDL_DestroyWindow(window);
    quit_subsystem();
    return (EXIT_SUCCESS);
}

int                 enter_game_loop(SDL_Window *window, t_game *game)
{
    SDL_Renderer    *renderer = NULL;
    t_ressource     *ressource = NULL;
    e_game_flow     state = GAME_FLOW_RUN;

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
    while (state != GAME_FLOW_EXIT) {
        SDL_RenderClear(renderer);
        if (state == GAME_FLOW_MENU) {
            t_menu  *menu = create_menu();
            sub_events(game);
            sub_inputs(&state, game);
            render_menu(renderer, menu);
        } else if (state != GAME_FLOW_SKIP && state != GAME_FLOW_EXIT) {
            sub_events(game);
            sub_inputs(&state, game);
            render_entites(renderer, ressource, game->env);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    	SDL_Delay(100);
    }
    destroy_ressource(ressource);
    SDL_DestroyRenderer(renderer);
    return (0);
}

int8_t init_subsystem()
{
    if (SDL_Init(SDL_CONFIG) < 0) {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return (-1);
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Could not initialize sdl2_image: %s\n", IMG_GetError());
        return (-1);
    }
    return (0);
}

void quit_subsystem()
{
    SDL_Quit();
    IMG_Quit();
}
