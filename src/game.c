#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include "./game.h"
#include "./bomberman/render.h"
#include "./bomberman/action.h"
#include "./bomb/render.h"

int init_game(t_game *game)
{
    if (init_bomb(game->renderer) < 0) {
        printf("Bomb could not be loaded! Error: %s\n", strerror(errno));
        return (-1);
    }
    if (init_bomberman(game->renderer) < 0) {
        printf("Bomberman could not be loaded! Error: %s\n", strerror(errno));
        return (-1);
    }

    return (0);
}

t_game *create_game()
{
    t_game *game = (t_game*) malloc(sizeof(t_game));

    if (game == NULL) {
        perror("Allocation failure");
        return (NULL);
    }
    game->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (game->window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_image Error: %s", SDL_GetError());
        return (NULL);
    }
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (game->renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s", SDL_GetError());
        return (NULL);
    }
    game->state = GAME_MENU;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WITDH; x++) {
            if (x == 0 || y == 0 || (x + 1) == BOARD_WITDH || (y + 1) == BOARD_HEIGHT) {
                game->board[y][x] = ENTITY_WALL;
            } else {
                game->board[y][x] = ENTITY_GRASS;
            }
        }
    }
    return (game);
}

void destroy_game(t_game *game)
{
    if (game != NULL) {
        if (game->renderer != NULL) {
            SDL_DestroyRenderer(game->renderer);
            game->renderer = NULL;
        }
        if (game->window != NULL) {
            SDL_DestroyWindow(game->window);
            game->window = NULL;
        }
        free(game);
    }
}

void render_game(t_game *game)
{
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WITDH; x++) {
            if (game->board[y][x] & ENTITY_BOMB) {
                render_bomb(game->renderer, x * BOARD_CELL_WIDTH, y * BOARD_CELL_HEIGHT);
            }
            if (game->board[y][x] & ENTITY_BOMBERMAN) {
                render_bomberman(game->renderer, x * BOARD_CELL_WIDTH, y * BOARD_CELL_HEIGHT);
            }
        }
    }
}

void input_game(t_game *game)
{
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_QUIT) {
            game->state = GAME_EXIT;
            return ;
        }
        if (game->event.type == SDL_KEYDOWN) {
            switch (game->event.key.keysym.sym) {
                case SDLK_UP:
                    bomberman_move_up(game, game->player.x, game->player.y);
                    break;
                case SDLK_DOWN:
                    bomberman_move_down(game, game->player.x, game->player.y);
                    break;
                case SDLK_LEFT:
                    bomberman_move_left(game, game->player.x, game->player.y);
                    break;
                case SDLK_RIGHT:
                    bomberman_move_right(game, game->player.x, game->player.y);
                    break;
            }
        }
    }
}

void join_game(t_game *game)
{
    int x = rand() % BOARD_WITDH;
    int y = rand() % BOARD_HEIGHT;

    while (game->board[y][x] != ENTITY_GRASS) {
        x = rand() % BOARD_WITDH;
        y = rand() % BOARD_HEIGHT;
    }
    game->player.x = x;
    game->player.y = y;
    game->board[y][x] = ENTITY_GRASS | ENTITY_BOMBERMAN;
}
