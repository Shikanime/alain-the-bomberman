#include "./movement.h"

int compute_bomberman_up_move(t_map *map, int y)
{
    if (y - 1 < 0) {
        return (int)map->height - 1;
    }
    return y - 1;
}

int compute_bomberman_down_move(t_map *map, int y)
{
    if ((size_t)(y + 1) >= map->height) {
        return 0;
    }
    return y + 1;
}

int compute_bomberman_left_move(t_map *map, int x)
{
    if (x - 1 < 0) {
        return (int)map->width - 1;
    }
    return x - 1;
}

int compute_bomberman_right_move(t_map *map, int x)
{
    if (x + 1 >= (int)map->width) {
        return 0;
    }
    return x + 1;
}
