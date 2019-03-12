#include "./bomb.h"

bool place_bomb(t_map *map, t_bomb *bomb, int x, int y)
{
    if (map->matrix[y][x].bomb != NULL) {
        return false;
    }
    map->matrix[y][x].bomb = bomb;
    return true;
}
