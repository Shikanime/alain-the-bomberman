#include "./movement.h"

bool move_bomberman_up(t_map *map, size_t x, size_t y)
{
    if (map->matrix[y][x].bomberman == NULL) {
        return false;
    }
    if (y - 1 < 0) {
        map->matrix[map->height][x].bomberman = map->matrix[y][x].bomberman;
    } else {
        map->matrix[y - 1][x].bomberman = map->matrix[y][x].bomberman;
    }
    map->matrix[y][x].bomberman = NULL;
    return true;
}

void move_bomberman_down(t_map *map, size_t x, size_t y)
{
    if (map->matrix[y][x].bomberman == NULL) {
        return false;
    }
    if (y + 1 > map->height) {
        map->matrix[0][x].bomberman = map->matrix[y][x].bomberman;
    } else {
        map->matrix[y + 1][x].bomberman = map->matrix[y][x].bomberman;
    }
    map->matrix[y][x].bomberman = NULL;
    return true;
}

void move_bomberman_left(t_map *map, size_t x, size_t y)
{
    if (map->matrix[y][x].bomberman == NULL) {
        return false;
    }
    if (x + 1 > map->width) {
        map->matrix[y][0].bomberman = map->matrix[y][x].bomberman;
    } else {
        map->matrix[y][x + 1].bomberman = map->matrix[y][x].bomberman;
    }
    map->matrix[y][x].bomberman = NULL;
    return true;
}

void move_bomberman_right(t_map *map, size_t x, size_t y)
{
    if (map->matrix[y][x].bomberman == NULL) {
        return false;
    }
    if (x - 1 < 0) {
        map->matrix[y][map->width].bomberman = map->matrix[y][x].bomberman;
    } else {
        map->matrix[y][x - 1].bomberman = map->matrix[y][x].bomberman;
    }
    map->matrix[y][x].bomberman = NULL;
    return true;
}
