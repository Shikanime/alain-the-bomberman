#include <stdio.h>
#include <unistd.h>
#include "./net.h"
#include "./system/bomberman.h"

void broadcast_event(t_conn *conn, int sender_fd, const char *event)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &conn->active_set)) {
            if (i != conn->fd && i != sender_fd) {
                send(i, event, 20, MSG_DONTWAIT);
            }
        }
    }
}

void close_connection(t_conn *conn, int fd)
{
    close(fd);
    FD_CLR(fd, &conn->active_set);
}

void        send_event(t_conn *conn, const char *command)
{
    char    buff[20];

    sprintf(buff, "%-*s\n", 20 - 2, command);
    send(conn->fd, buff, 20, MSG_DONTWAIT);
}

int conn_client_mode(t_conn *conn, const char *address, uint16_t port)
{
    conn->addr.sin_port = htons(port);
    conn->addr.sin_addr.s_addr = inet_addr(address);
    if (connect(conn->fd, (struct sockaddr*)&conn->addr, sizeof(conn->addr)) < 0) {
        perror("Client conn fail to connect");
        return (-1);
    }
    FD_ZERO(&conn->active_set);
    FD_SET(conn->fd, &conn->active_set);
    return (1);
}

int conn_server_mode(t_conn *conn, uint16_t port)
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
    return (1);
}
