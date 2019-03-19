#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "./client.h"
#include "./server.h"
#include "./boot.h"

typedef struct  s_app {
    char        *address;
    uint16_t    port;
    int         player_nb;
}               t_app;

void *detact_server(void *vargp);

int main(int argc, char *argv[])
{
    pthread_t   tr;
    t_app       app = {NULL, 4321, 2};

    if (init_subsystem() < 0) {
        return (EXIT_FAILURE);
    }
    for (int j = 0; j < argc; j++) {
        if (strcmp(argv[j], "--port") == 0 && j + 1 <= argc) {
            sscanf(argv[j + 1], "%"SCNu16, &app.port);
        }
        if (strcmp(argv[j], "--address") == 0 && j + 1 <= argc) {
            app.address = argv[j + 1];
        }
        if (strcmp(argv[j], "--player_number") == 0 && j + 1 <= argc) {
            sscanf(argv[j + 1], "%d", &app.player_nb);
        }
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--server") == 0) {
            if (pthread_create(&tr, NULL, detact_server, &app)) {
                printf("Thread fail to start\n");
                return (EXIT_FAILURE);
            }
        }
    }
    if (app.address == NULL) {
        run_client("127.0.0.1", app.port);
    } else {
        run_client(app.address, app.port);
    }
    quit_subsystem();
    return (EXIT_SUCCESS);
}

void *detact_server(void *app)
{
    run_server(((t_app*) app)->port, ((t_app*) app)->player_nb);
    return NULL;
}
