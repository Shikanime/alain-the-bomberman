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
    map->matrix = calloc(height, sizeof(**t_cell));
    for (size_t i = 0; i < height; i++) {
        map->matrix[i] = calloc(width, sizeof(*t_cell));
    }
    return (map);
}

void destroy_map(t_map *map)
{
    if (map != NULL) {
        if (map->matrix != NULL) {
            for (size_t i = 0; i < map->width; i++) {
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
