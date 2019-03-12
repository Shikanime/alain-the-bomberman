#include <stdio.h>
#include <unistd.h>
#include "./net.h"
#include "./system/bomberman.h"

int read_from_socket(int fd, char (*msg_buff)[20]);

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

int     handle_join(t_conn *s)
{
    int fd = 0;

    fd = accept(s->fd, (struct sockaddr*)&s->addr, &s->len);
    if (fd < 0) {
        return (-1);
    }
    FD_SET(fd, &s->active_set);
    printf("New connection on %d\n", fd);
    return (1);
}

int         handle_packet(t_conn *s, int fd)
{
    char    msg_buff[20];

    if (read_from_socket(fd, &msg_buff) < 0) {
        close_connection(s, fd);
        return (-1);
    }
    broadcast_event(s, fd, msg_buff);
    printf("Message received from %d of content: %.*s", fd, 20, msg_buff);
    return (1);
}

int         read_from_socket(int fd, char (*msg_buff)[20])
{
    ssize_t n = recv(fd, msg_buff, 20, 0);

    if (n < 0) {
    return (-1);
    }
    if (n == 0) {
        return (-1);
    }
    return 0;
}
