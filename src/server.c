#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "./server.h"
#include "./event.h"
#include "./net.h"
#include "./net/conn.h"
#include "./config.h"

int enter_server_loop(t_conn *server, t_map *map);

int         run_server(uint16_t port)
{
    t_map   *map = create_map(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20);
    t_conn  *server = create_conn();

    if (server == NULL) {
        fprintf(stderr, "Fail to create the server: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (conn_server_mode(server, port) < 0) {
        fprintf(stderr, "Fail to start the server with exception: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    printf("Server mode run on: %hu\n", port);
    if (enter_server_loop(server, map) < 0) {
        fprintf(stderr, "Server exit with exception: %s\n", strerror(errno));
        destroy_conn(server);
        return (EXIT_FAILURE);
    }
    destroy_conn(server);
    return (EXIT_SUCCESS);
}

int                     enter_server_loop(t_conn *server, t_map *map)
{
    e_server_status     state = SERVER_RUN;

    while (state != SERVER_HALT) {
        sub_client_events(server, map);
    }
    return (1);
}
