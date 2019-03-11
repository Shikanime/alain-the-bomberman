#pragma once

#include <arpa/inet.h>
#include <sys/time.h>

typedef struct          s_socket
{
    int                 fd;
    struct sockaddr_in  addr;
    socklen_t           len;
    fd_set              active_set;
    fd_set              read_set;
}                       t_socket;

t_socket    *create_socket();
int         socket_client_mode(t_socket *sok, const char *address, uint16_t port);
int         socket_server_mode(t_socket *sok, uint16_t port);
void        destroy_socket(t_socket *client);
