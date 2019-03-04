#include "./action.h"

bool bomberman_move_up(t_game *game, int x, int y)
{
    if (0 > y - 1) {
        return (false);
    }
    if (game->board[y - 1][x] & ENTITY_WALL) {
        return (false);
    }
    game->player.y--;
    game->board[y][x] = game->board[y][x] & ~ENTITY_BOMBERMAN;
    game->board[y - 1][x] = game->board[y - 1][x] | ENTITY_BOMBERMAN;
    return (true);
}

bool bomberman_move_down(t_game *game, int x, int y)
{
    if (y + 1 >= BOARD_HEIGHT) {
        return (false);
    }
    if (game->board[y + 1][x] & ENTITY_WALL) {
        return (false);
    }
    game->player.y++;
    game->board[y][x] = game->board[y][x] & ~ENTITY_BOMBERMAN;
    game->board[y + 1][x] = game->board[y + 1][x] | ENTITY_BOMBERMAN;
    return (true);
}

bool bomberman_move_right(t_game *game, int x, int y)
{
    if (x + 1 >= BOARD_WITDH) {
        return (false);
    }
    if (game->board[y][x +1] & ENTITY_WALL) {
        return (false);
    }
    game->player.x++;
    game->board[y][x] = game->board[y][x] & ~ENTITY_BOMBERMAN;
    game->board[y][x + 1] = game->board[y][x + 1] | ENTITY_BOMBERMAN;
    return (true);
}

bool bomberman_move_left(t_game *game, int x, int y)
{
    if (0 > x - 1) {
        return (false);
    }
    if (game->board[y][x - 1] & ENTITY_WALL) {
        return (false);
    }
    game->player.x--;
    game->board[y][x] = game->board[y][x] & ~ENTITY_BOMBERMAN;
    game->board[y][x - 1] = game->board[y][x - 1] | ENTITY_BOMBERMAN;
    return (true);
}

bool bomberman_place_bomb(t_game *game, int x, int y)
{
    if (y >= BOARD_HEIGHT || x >= BOARD_WITDH) {
        return (false);
    }
    if (game->board[y][x] | ENTITY_BOMBERMAN) {
        return (false);
    }
    game->board[y][x] = ENTITY_BOMB;
    return (true);
}
