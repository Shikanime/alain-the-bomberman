#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./game/player.h"
#include "./game/map.h"
#include "./net/conn.h"

typedef enum {
    CLIENT_INIT,
    CLIENT_RUN,
    CLIENT_PAUSE,
    CLIENT_OVER,
    CLIENT_EXIT,
    CLIENT_MENU
}   e_client_state;

typedef struct      t_client {
    e_client_state  state;
    t_conn          *server;
    t_map           *map;
    t_player        *player;
}                   t_client;

t_client    *create_client(size_t width, size_t height);
void        destroy_client(t_client *client);
int         run_client(const char *address, uint16_t port);

