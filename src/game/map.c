#include <stdio.h>
#include "./map.h"

t_map       *create_map(size_t width, size_t height)
{
    t_map   *map = malloc(sizeof(t_map));

    if (map == NULL) {
        perror("Fail to allocate map");
        return (NULL);
    }
    map->width = width;
    map->height = height;
    map->matrix = calloc(height, sizeof(t_cell*));
    for (size_t i = 0; i < height; i++) {
        map->matrix[i] = calloc(width, sizeof(t_cell));
        for (size_t j = 0; j < width; j++) {
            map->matrix[i][j].bomb = NULL;
            map->matrix[i][j].bomberman = NULL;
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                map->matrix[i][j].env = ENV_WALL;
            } else {
                map->matrix[i][j].env = ENV_GROUND;
            }
        }
    }
    return (map);
}

void destroy_map(t_map *map)
{
    if (map != NULL) {
        if (map->matrix != NULL) {
            for (size_t i = 0; i < map->height; i++) {
                if (map->matrix[i] != NULL) {
                    free(map->matrix[i]);
                }
            }
            free(map->matrix);
        }
        free(map);
        map = NULL;
    }
}
