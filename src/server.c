#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "./server.h"
#include "./event.h"
#include "./net.h"
#include "./net/conn.h"

int enter_server_loop(t_conn *s);

int         run_server(uint16_t port)
{
    t_conn* server = create_conn();

    if (server == NULL) {
        fprintf(stderr, "Fail to create the server: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (conn_server_mode(server, port) < 0) {
        fprintf(stderr, "Fail to start the server with exception: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    printf("Server mode run on: %hu\n", port);
    if (enter_server_loop(server) < 0) {
        fprintf(stderr, "Server exit with exception: %s\n", strerror(errno));
        destroy_conn(server);
        return (EXIT_FAILURE);
    }
    destroy_conn(server);
    return (EXIT_SUCCESS);
}

int                 enter_server_loop(t_conn *s)
{
    e_server_status  state = SERVER_RUN;

    while (state != SERVER_HALT) {
        sub_client_inputs(s);
    }
    return (1);
}
