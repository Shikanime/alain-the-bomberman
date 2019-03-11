#include "./placement.h"

bool place_bomb(t_map *map, t_bomb *bomb, size_t x, size_t y)
{
    if (map->matrix[y][x].bomb != NULL) {
        return false;
    }
    map->matrix[y][x].bomb = bomb;
    return true;
}

bool place_bomberman(t_map *map, t_bomberman *bomberman, size_t x, size_t y)
{
    if (map->matrix[y][x].bomberman != NULL) {
        return false;
    }
    map->matrix[y][x].bomberman = bomberman;
    return true;
}
