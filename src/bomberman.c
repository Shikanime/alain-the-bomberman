#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "./client.h"
#include "./server.h"

void *detact_server(void *vargp);

// TODO: Refactor to getopt_long
int main(int argc, char *argv[])
{
    pthread_t   tr;
    char        *address = NULL;
    uint16_t    port = 0;

    for (int j = 0; j < argc; j++) {
        if (strcmp(argv[j], "--port") == 0 && j + 1 <= argc) {
            sscanf(argv[j + 1], "%"SCNu16, &port);
        }
        if (strcmp(argv[j], "--address") == 0 && j + 1 <= argc) {
            address = argv[j + 1];
        }
    }
    if (!port) {
        printf("No server port specified\n");
        return (EXIT_FAILURE);
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--server") == 0) {
            if (pthread_create(&tr, NULL, detact_server, &port)) {
                printf("Thread fail to start\n");
                return (EXIT_FAILURE);
            }
            address = (char *) "127.0.0.1";
        }
    }
    if (!address) {
        printf("No server IP specified\n");
        return (EXIT_FAILURE);
    }
    return run_client(address, port);
}

void *detact_server(void *vargp)
{
    run_server(*((uint16_t *) vargp));
    return NULL;
}
