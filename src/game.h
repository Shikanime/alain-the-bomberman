#pragma once

#include <SDL2/SDL.h>
#include "./bomberman.h"
#include "./bomb.h"

// Game rule
#define MAX_PLAYER 4

// Screen dimension constants
#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

// Board dimension
#define BOARD_CELL_WIDTH    40
#define BOARD_CELL_HEIGHT   40
#define BOARD_WITDH         SCREEN_WIDTH  / BOARD_CELL_WIDTH
#define BOARD_HEIGHT        SCREEN_HEIGHT / BOARD_CELL_HEIGHT

// Board element
typedef enum {
    ENTITY_NONE         = 1 << 0,
    ENTITY_BOMBERMAN    = 1 << 1,
    ENTITY_BOMB         = 1 << 2,
    ENTITY_WALL         = 1 << 3
}   e_entity;

typedef e_entity t_board[BOARD_WITDH][BOARD_HEIGHT];

// Game state machine
typedef enum {
    GAME_EXIT,
    GAME_MENU,
    GAME_GAME
} e_game_state;

// Player index
typedef struct  s_player{
    int         x;
    int         y;
}               t_player;

typedef struct      s_game
{
    t_player        player;
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    e_game_state    state;
    t_bomberman     bombermans[BOARD_HEIGHT][BOARD_WITDH];
    t_bomb          bombs[BOARD_HEIGHT][BOARD_WITDH];
    t_board         board;
}                   t_game;

t_game  *create_game();
int     init_game(t_game *game);
void    destroy_game(t_game *game);
void    render_game(t_game *game);
void    input_game(t_game *game);
void    join_game(t_game *game);
