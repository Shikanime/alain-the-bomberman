#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "./net/socket.h"
#include "./server.h"
#include "./net.h"

int enter_server_loop(t_socket *s);

int             run_server(uint16_t port)
{
    t_socket*   server = create_socket();

    if (!server) {
        fprintf(stderr, "Fail to create the server: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (connect_server(server, port) < 0) {
        fprintf(stderr, "Fail to start the server with exception: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    printf("Server mode run on: %hu\n", port);
    if (enter_server_loop(server) < 0) {
        fprintf(stderr, "Server exit with exception: %s\n", strerror(errno));
        destroy_socket(server);
        return (EXIT_FAILURE);
    }
    destroy_socket(server);
    return (EXIT_SUCCESS);
}

int                 enter_server_loop(t_socket *s)
{
    e_server_status  state = SERVER_RUN;

    while (state != SERVER_HALT) {
        if (await_event(s) < 0) {
            return (-1);
        }
        if (dispatch_event(s) < 0) {
            printf("Fail to process an event\n");
        }
    }
    return (1);
}
