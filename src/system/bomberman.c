#include "./bomb.h"
#include "./bomberman.h"

bool allahu_akbar(t_map *map, int x, int y)
{
    if (map->matrix[y][x].bomberman == NULL) {
        return false;
    }
    return place_bomb(map, create_bomb(), x, y);
}

bool place_bomberman(t_map *map, t_bomberman *bomberman, int x, int y)
{
    if (map->matrix[y][x].bomberman != NULL) {
        return false;
    }
    map->matrix[y][x].bomberman = bomberman;
    return true;
}

bool spawn_bomberman(t_map *map, t_bomberman *bomberman, int x, int y)
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

bool move_bomberman(t_map *map, int sx, int sy, int dx, int dy)
{
    if (map->matrix[sy][sx].bomberman == NULL) {
        return false;
    }
    if (map->matrix[dy][dx].bomberman != NULL) {
        return false;
    }
    map->matrix[dy][dx].bomberman = map->matrix[sy][sx].bomberman;
    map->matrix[sy][sx].bomberman = NULL;
    return true;
}
