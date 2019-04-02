#include "./bomb.h"

bool bomb_have_been_plant(t_map *map, t_bomb *bomb, int x, int y)
{
    if (map->matrix[y][x].bomb != NULL) {
        return (false);
    }
    map->matrix[y][x].bomb = bomb;
    map->matrix[y][x].bomberman->bomb_nb--;
    return true;
}

int     bomb_explosion(t_map *map, t_bomb *bomb, int x, int y)
{
    int n = 0;

    if (map->matrix[y][x].bomb == NULL) {
        return (0);
    }
    for (int i = x - 2; i < x + (2 * 2 + 1); i++) {
        if (i < 0 || i >= (int)map->width) {
            continue;
        }
        if (i == x) {
            continue;
        }
        if (map->matrix[y][i].env == ENV_WALL) {
            break;
        }
        if (map->matrix[y][i].bomberman != NULL) {
            destroy_bomberman(map->matrix[y][i].bomberman);
            map->matrix[y][i].bomberman = NULL;
            n++;
        }
        map->matrix[y][i].env = ENV_FIRE;
    }
    for (int i = y - 2; i < y + (2 * 2 + 1); i++) {
        if (i < 0 || i >= (int)map->height) {
            continue;
        }
        if (i == y) {
            continue;
        }
        if (map->matrix[i][x].env == ENV_WALL) {
            break;
        }
        if (map->matrix[i][x].bomberman != NULL) {
            destroy_bomberman(map->matrix[i][x].bomberman);
            map->matrix[i][x].bomberman = NULL;
            n++;
        }
        map->matrix[i][x].env = ENV_FIRE;
    }
    return (n);
}

int     clear_explosion(t_map *map, t_bomb *bomb, int x, int y)
{
    if (map->matrix[y][x].bomb == NULL) {
        return (0);
    }
    for (int i = x - 2; i < x + (2 * 2 + 1); i++) {
        if (i < 0 || i >= (int)map->width) {
            continue;
        }
        if (i == x) {
            continue;
        }
        if (map->matrix[y][i].env == ENV_WALL) {
            break;
        }
        map->matrix[y][i].env = ENV_GROUND;
    }
    for (int i = y - 2; i < y + (2 * 2 + 1); i++) {
        if (i < 0 || i >= (int)map->height) {
            continue;
        }
        if (i == y) {
            continue;
        }
        if (map->matrix[i][x].env == ENV_WALL) {
            break;
        }
        map->matrix[i][x].env = ENV_GROUND;
    }
    destroy_bomb(map->matrix[y][x].bomb);
    map->matrix[y][x].bomb = NULL;
    return (-1);
}
