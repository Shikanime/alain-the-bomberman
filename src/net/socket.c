#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "./socket.h"

t_socket        *create_socket()
{
    t_socket    *conn = malloc(sizeof(t_socket));

    if (conn) {
        conn->fd = socket(AF_INET, SOCK_STREAM, 0);
        if (conn->fd < 0) {
            perror("Fail to create conn file descriptor");
            return (NULL);
        }
        conn->addr.sin_family = AF_INET;
    }
    return (conn);
}

int socket_client_mode(t_socket *conn, const char *address, uint16_t port)
{
    conn->addr.sin_port = htons(port);
    conn->addr.sin_addr.s_addr = inet_addr(address);
    if (connect(conn->fd, (struct sockaddr*)&conn->addr, sizeof(conn->addr)) < 0) {
        perror("Client conn fail to connect");
        return (-1);
    }
    FD_ZERO(&conn->active_set);
    FD_SET(conn->fd, &conn->active_set);
    return (0);
}

int socket_server_mode(t_socket *conn, uint16_t port)
{
    conn->addr.sin_port = htons(port);
    conn->addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(conn->fd, (struct sockaddr*)&conn->addr, sizeof(conn->addr)) < 0) {
        perror("Server conn fail to listen port");
        conn->fd = -1;
        return (-1);
    }
    if (listen(conn->fd, 4) < 0) {
        perror("Server conn fail to listen port");
        return (-1);
    }
    FD_ZERO(&conn->active_set);
    FD_SET(conn->fd, &conn->active_set);
    return (0);
}

void destroy_socket(t_socket *conn)
{
    if (conn) {
        if (conn->fd >= 0) {
            close(conn->fd);
        }
        free(conn);
    }
}
