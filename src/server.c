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

t_server *create_server(size_t width, size_t height, int player_nb);
void destroy_server(t_server *server);
int enter_server_loop(t_server *server);

t_server        *create_server(size_t width, size_t height, int player_nb)
{
    t_server    *server = malloc(sizeof(t_server));

    if (server == NULL) {
        perror("Fail to allocate server");
        return (NULL);
    }
    server->state = SERVER_RUN;
    server->map = create_map(width, height);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
                server->map->matrix[i][j].env = ENV_WALL;
            }
            if (rand() % 100 >= 80) {
                server->map->matrix[i][j].env = ENV_WALL;
            }
        }
    }
    server->conn = create_conn();
    server->player_nb = 0;
    server->limit_player_nb = player_nb;
    return server;
}

void destroy_server(t_server *server)
{
    if (server != NULL) {
        destroy_map(server->map);
        destroy_conn(server->conn);
        free(server);
    }
}

int             run_server(uint16_t port, int player_nb)
{
    t_server    *server = create_server(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20, player_nb);

    if (server->conn == NULL) {
        fprintf(stderr, "Fail to create the server: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (conn_server_mode(server->conn, port) < 0) {
        fprintf(stderr, "Fail to start the server with exception: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    printf("Server mode run on: %hu\n", port);
    if (enter_server_loop(server) < 0) {
        fprintf(stderr, "Server exit with exception: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    destroy_server(server);
    return (EXIT_SUCCESS);
}

int enter_server_loop(t_server *server)
{
    while (server->state != SERVER_HALT) {
        server->conn->read_set = server->conn->active_set;
        sub_client_packets(server);
    }
    return (1);
}
