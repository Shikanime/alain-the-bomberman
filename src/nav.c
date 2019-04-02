#include "./nav.h"
#include "./net.h"
#include <unistd.h>

void *detact_server_cb(void *nav);

int start_server(t_client *client)
{
    if (pthread_create(&client->server_tr, NULL, detact_server_cb, client)) {
        perror("Thread fail to start\n");
        return (-1);
    }
    sleep(1);
    if (conn_client_mode(client->server, client->address, client->port) < 0) {
        perror("Fail to connect server\n");
        return (-1);
    }
    return (1);
}

void *detact_server_cb(void *nav)
{
    run_server(((t_client*) nav)->port, ((t_client*) nav)->player_capacity);
    return NULL;
}
