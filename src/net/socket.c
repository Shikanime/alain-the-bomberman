#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "./socket.h"

int8_t allocate_fd(t_socket *sok, uint16_t port);
int8_t connect_client(t_socket *sok, const char *address);
int8_t open_server_conn(t_socket *sok);

t_socket        *create_client_socket(const char *address, uint16_t port)
{
    t_socket    *sok = malloc(sizeof(t_socket));

    if (sok) {
        if (allocate_fd(sok, port) < 0) {
            destroy_socket(sok);
            return (NULL);
        }
        if (connect_client(sok, address) < 0) {
            destroy_socket(sok);
            return (NULL);
        }
    }
    return (sok);
}

int8_t connect_client(t_socket *sok, const char *address)
{
    sok->addr.sin_addr.s_addr = inet_addr(address);
    if (connect(sok->fd, (struct sockaddr*)&sok->addr, sizeof(sok->addr)) < 0) {
        perror("Client socket fail to connect");
        return (-1);
    }
    FD_ZERO(&sok->active_set);
    FD_SET(sok->fd, &sok->active_set);
    return (0);
}

t_socket        *create_server_socket(uint16_t port)
{
    t_socket    *sok = malloc(sizeof(t_socket));

    if (sok) {
        if (allocate_fd(sok, port) < 0) {
            destroy_socket(sok);
            return (NULL);
        }
        if (open_server_conn(sok) < 0) {
            destroy_socket(sok);
            return (NULL);
        }
    }
    return (sok);
}

int8_t open_server_conn(t_socket *sok)
{
    sok->addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sok->fd, (struct sockaddr*)&sok->addr, sizeof(sok->addr)) < 0) {
        perror("Server socket fail to listen port");
        sok->fd = -1;
        return (-1);
    }
    if (listen(sok->fd, 4) < 0) {
        perror("Server socket fail to listen port");
        return (-1);
    }
    FD_ZERO(&sok->active_set);
    FD_SET(sok->fd, &sok->active_set);
    return (0);
}

int8_t allocate_fd(t_socket *sok, uint16_t port)
{
    sok->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sok->fd < 0) {
        perror("Fail to create socket file descriptor");
        return (-1);
    }
    sok->addr.sin_port = htons(port);
    sok->addr.sin_family = AF_INET;
    return (0);
}

void destroy_socket(t_socket *sok)
{
    if (sok) {
        if (sok->fd >= 0) {
            close(sok->fd);
        }
        free(sok);
    }
}
