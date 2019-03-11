#pragma once

#include <arpa/inet.h>
#include <sys/time.h>

typedef struct          s_conn
{
    int                 fd;
    struct sockaddr_in  addr;
    socklen_t           len;
    fd_set              active_set;
    fd_set              read_set;
}                       t_conn;

t_conn  *create_conn();
void    destroy_conn(t_conn *client);
