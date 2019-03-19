#pragma once

#include <stdint.h>
#include "./net/conn.h"
#include "./game/map.h"

typedef enum {
    SERVER_HALT,
    SERVER_RUN
}   e_server_state;

typedef struct      t_server {
    e_server_state  state;
    t_conn          *conn;
    t_map           *map;
    int             player_nb;
    int             limit_player_nb;
}                   t_server;

int run_server(uint16_t port, int player_nb);
