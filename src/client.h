#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <SDL2/SDL_image.h>
#include "./game/player.h"
#include "./game/map.h"
#include "./game/nav.h"
#include "./net/conn.h"
#include "./ui/menu.h"

typedef enum {
    CLIENT_EXIT,
    CLIENT_MENU,
    CLIENT_GAME_INIT,
    CLIENT_GAME,
    CLIENT_GAME_PAUSE
}   e_client_state;

typedef struct      t_client {
    e_client_state  state;
    pthread_t       server_tr;
    t_conn          *server;
    t_nav           *nav;
    t_map           *map;
    t_player        *player;
    t_menu          *menu;
    char            *address;
    uint16_t        port;
    int             player_nb;
    int             player_capacity;
}                   t_client;

t_client    *create_client(size_t width, size_t height);
void        destroy_client(t_client *client);
int         run_client();

