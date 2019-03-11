#include "./movement.h"

bool            move_bomberman_up(t_map *map, t_player *player)
{
    t_bomberman *bomberman = NULL;

    if (map->matrix[player->y][player->x].bomberman == NULL) {
        return false;
    }
    bomberman = map->matrix[player->y][player->x].bomberman;
    map->matrix[player->y][player->x].bomberman = NULL;
    if (player->y - 1 < 0) {
        player->y = map->height - 1;
    } else {
        player->y -= 1;
    }
    map->matrix[player->y][player->x].bomberman = bomberman;
    return true;
}

bool            move_bomberman_down(t_map *map, t_player *player)
{
    t_bomberman *bomberman = NULL;

    if (map->matrix[player->y][player->x].bomberman == NULL) {
        return false;
    }
    bomberman = map->matrix[player->y][player->x].bomberman;
    map->matrix[player->y][player->x].bomberman = NULL;
    if (player->y + 1 >= map->height) {
        player->y = 0;
    } else {
        player->y += 1;
    }
    map->matrix[player->y][player->x].bomberman = bomberman;
    return true;
}

bool            move_bomberman_left(t_map *map, t_player *player)
{
    t_bomberman *bomberman = NULL;

    if (map->matrix[player->y][player->x].bomberman == NULL) {
        return false;
    }
    bomberman = map->matrix[player->y][player->x].bomberman;
    map->matrix[player->y][player->x].bomberman = NULL;
    if (player->x - 1 < 0) {
        map->matrix[player->y][map->width - 1].bomberman = map->matrix[player->y][player->x].bomberman;
        player->x = map->width - 1;
    } else {
        map->matrix[player->y][player->x - 1].bomberman = map->matrix[player->y][player->x].bomberman;
        player->x -= 1;
    }
    map->matrix[player->y][player->x].bomberman = bomberman;
    return true;
}

bool            move_bomberman_right(t_map *map, t_player *player)
{
    t_bomberman *bomberman = NULL;

    if (map->matrix[player->y][player->x].bomberman == NULL) {
        return false;
    }
    bomberman = map->matrix[player->y][player->x].bomberman;
    map->matrix[player->y][player->x].bomberman = NULL;
    if (player->x + 1 >= map->width) {
        player->x = 0;
    } else {
        player->x += 1;
    }
    map->matrix[player->y][player->x].bomberman = bomberman;
    return true;
}
