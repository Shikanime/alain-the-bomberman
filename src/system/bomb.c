#include "./bomb.h"

bool bomb_have_been_plant(t_map *map, t_bomb *bomb, int x, int y)
{
    if (map->matrix[y][x].bomb != NULL) {
        return false;
    }
    map->matrix[y][x].bomb = bomb;
    return true;
}

bool bomb_explosion(t_map *map, t_bomb *bomb, int x, int y)
{
    if (map->matrix[y][x].bomb == NULL) {
        return false;
    }
    destroy_bomb(map->matrix[y][x].bomb);
    map->matrix[y][x].bomb = NULL;
    return true;
}
