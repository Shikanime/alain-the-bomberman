#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "./conn.h"

t_conn      *create_conn()
{
    t_conn  *conn = malloc(sizeof(t_conn));

    if (conn == NULL) {
        perror("Fail to allocate conn");
        return (NULL);
    }
    conn->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (conn->fd < 0) {
        perror("Fail to create conn file descriptor");
        return (NULL);
    }
    conn->addr.sin_family = AF_INET;
    return (conn);
}

void destroy_conn(t_conn *conn)
{
    if (conn) {
        if (conn->fd >= 0) {
            close(conn->fd);
        }
        free(conn);
    }
}
