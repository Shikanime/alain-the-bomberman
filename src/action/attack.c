#include "./attack.h"
#include "./placement.h"

bool allahu_akbar(t_map *map, t_player *player)
{
    if (map->matrix[player->y][player->x].bomberman == NULL) {
        return false;
    }
    return place_bomb(map, create_bomb(), player->x, player->y);
}
