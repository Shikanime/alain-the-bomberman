#include "./spawn.h"

bool spawn_bomberman(t_map *map, t_bomberman *bomberman, size_t x, size_t y)
{
    if (map->matrix[y][x].bomberman != NULL) {
        return false;
    }
    if (map->matrix[y][x].bomb != NULL) {
        return false;
    }
    map->matrix[y][x].bomberman = bomberman;
    return true;
}
