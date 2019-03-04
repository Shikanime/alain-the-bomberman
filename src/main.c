#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "./game.h"

// SDL flags
const Uint32    SDL_FLAGS = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
int             IMG_FLAGS = IMG_INIT_PNG;

// Bomberman subsystem
int     main_init();
void    main_quit();

int main()
{
    t_game *game = NULL;

    srand((unsigned int) time(NULL));
    if (main_init() < 0) {
        return (EXIT_FAILURE);
    }
    game = create_game();
    if (game == NULL) {
        fprintf(stderr, "Fail to create game! Error: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (init_game(game) < 0) {
        printf("Bomb could not be loaded! Error: %s\n", strerror(errno));
        return (-1);
    }
    join_game(game);
    while (game->state != GAME_EXIT) {
        input_game(game);
        SDL_RenderClear(game->renderer);
        render_game(game);
        SDL_Delay(100);
        SDL_RenderPresent(game->renderer);
    }
    main_quit();
    return (EXIT_SUCCESS);
}

int main_init()
{
    if (SDL_Init(SDL_FLAGS) < 0) {
        fprintf(stderr, "Fail to initialize SDL library! SDL_image Error: %s", SDL_GetError());
        return (-1);
    }
    if (!(IMG_Init(IMG_FLAGS) & IMG_FLAGS)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return (-1);
    }
    return (0);
}

void main_quit()
{
	IMG_Quit();
	SDL_Quit();
}
