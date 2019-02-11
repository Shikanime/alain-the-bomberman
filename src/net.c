#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "./net.h"

int read_from_socket(int fd, char (*buff)[MESSAGE_LENGTH]);
int handshake(t_socket *s);
int handle_inc(t_socket *s, int fd);
int broadcast_event(t_socket *s, int sender, const char *evt);
void close_connection(t_socket *s, int fd);
void new_active_set(t_socket *s);

int await_event(t_socket *s)
{
    new_active_set(s);
    if (select(FD_SETSIZE, &s->read_set, NULL, NULL, NULL) < 0) {
        return (-1);
    }
    return (1);
}

int dispatch_event(t_socket *s)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &s->read_set)) {
            if (i == s->fd) {
                if (handshake(s) < 0) {
                    return (-1);
                } else {
                    printf("New connection\n");
                }
                // TODO: broadcast spawn event
                // if (broadcast_event(s, i, "spawn") < 0) {
                //     return (-1);
                // }
            } else {
                if (handle_inc(s, i) < 0) {
                    printf("Fail to hanle a message from fd: %d\n", i);
                }
            }
        }
    }
    return (1);
}

int    handshake(t_socket *s)
{
    int fd = accept(
        s->fd,
        (struct sockaddr*)&s->addr,
        &s->len
    );

    if (fd < 0) {
        return (-1);
    }
    FD_SET(fd, &s->active_set);
    return (1);
}

int handle_inc(t_socket *s, int fd)
{
    char buff[MESSAGE_LENGTH];

    if (read_from_socket(fd, &buff) < 0) {
        close_connection(s, fd);
        return (-1);
    }
    printf("Message received from %d of content: %.10s", fd, buff);
    if (broadcast_event(s, fd, buff) < 0) {
        close_connection(s, fd);
        return (-1);
    }
    return (1);
}

int         read_from_socket(int fd, char (*buff)[MESSAGE_LENGTH])
{
    ssize_t n = recv(fd, buff, MESSAGE_LENGTH, 0);

    if (n < 0) {
      return (-1);
    }
    if (n == 0) {
        return (-1);
    }
    return 0;
}

int         broadcast_event(t_socket *s, int sender, const char *evt)
{
    for (int i = 3; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &s->active_set)) {
            if (i != s->fd && i != sender) {
                if (send(i, evt, MESSAGE_LENGTH, 0) < 0) {
                    return (-1);
                }
            }
        }
    }
    return (0);
}

void close_connection(t_socket *s, int fd)
{
    close(fd);
    FD_CLR(fd, &s->active_set);
    printf("Connection closed\n");
}

void send_event(t_socket *socket, const char *command)
{
    send(socket->fd, command, 10, 0);
}

void new_active_set(t_socket *s)
{
    s->read_set = s->active_set;
}
