
#include "./attack.h"
#include "./placement.h"

bool allahu_akbar(t_map *map, size_t x, size_t y)
{
    if (map->matrix[y][x].hero == NULL) {
        return false;
    }
    return place_bomb(map, create_bomb(), x, y);
}
