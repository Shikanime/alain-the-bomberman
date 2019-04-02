#include "./explosion.h"
#include "../system/bomb.h"

void handle_explosion_events(t_client *client, int x, int y)
{
    if (client->map->matrix[y][x].bomb != NULL) {
        if (SDL_GetTicks() - client->map->matrix[y][x].bomb->drop_time > BOMB_BASIC_TIME) {
            client->player_nb -= bomb_explosion(client->map, client->map->matrix[y][x].bomb, (int)x, (int)y);
            printf("%d", client->player_nb);
            fflush(stdout);
            if (SDL_GetTicks() - client->map->matrix[y][x].bomb->drop_time > BOMB_BASIC_TIME + BLAST_TIME) {
                clear_explosion(client->map, client->map->matrix[y][x].bomb, (int)x, (int)y);
            }
        }
    }
}
