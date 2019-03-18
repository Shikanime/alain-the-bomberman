#include <stdio.h>
#include <unistd.h>
#include "./net.h"
#include "./system/bomberman.h"

int read_from_socket(int fd, char (*msg_buff)[FIXED_PACKET_LENGHT]);
void sync_player(t_conn *server, int fd, t_map *map);
void sync_map(int fd, t_map *map);

void broadcast_event(t_conn *conn, int sender_fd, const char *event)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &conn->active_set)) {
            if (i != conn->fd && i != sender_fd) {
                send(i, event, FIXED_PACKET_LENGHT, MSG_DONTWAIT);
            }
        }
    }
}

void close_connection(t_conn *conn, int fd)
{
    close(fd);
    FD_CLR(fd, &conn->active_set);
}

void        send_event(int fd, const char *command)
{
    char    buff[FIXED_PACKET_LENGHT];

    sprintf(buff, "%-*s\n", FIXED_PACKET_LENGHT - 2, command);
    send(fd, buff, FIXED_PACKET_LENGHT, MSG_DONTWAIT);
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

int     handle_join(t_conn *server, t_map *map)
{
    int fd = 0;

    fd = accept(server->fd, (struct sockaddr*)&server->addr, &server->len);
    if (fd < 0) {
        return (-1);
    }
    FD_SET(fd, &server->active_set);
    sync_map(fd, map);
    sync_player(server, fd, map);
    printf("New connection on %d\n", fd);
    return (1);
}

int         handle_packet(t_conn *server, int fd)
{
    char    msg_buff[FIXED_PACKET_LENGHT];

    if (read_from_socket(fd, &msg_buff) < 0) {
        close_connection(server, fd);
        return (-1);
    }
    broadcast_event(server, fd, msg_buff);
    printf("Message received from %d of content: %.*s", fd, FIXED_PACKET_LENGHT, msg_buff);
    return (1);
}

int         read_from_socket(int fd, char (*msg_buff)[FIXED_PACKET_LENGHT])
{
    ssize_t n = recv(fd, msg_buff, FIXED_PACKET_LENGHT, 0);

    if (n < 0) {
    return (-1);
    }
    if (n == 0) {
        return (-1);
    }
    return 0;
}

void        sync_player(t_conn *server, int fd, t_map *map)
{
    char        packet[FIXED_PACKET_LENGHT];
    int         x = 0;
    int         y = 0;
    t_bomberman *player = create_bomberman();

    do {
        x = rand() % map->width;
        y = rand() % map->height;
    } while (!place_bomberman(map, player, x, y));
    sprintf(packet, "spawn 1 %02d %02d", x, y);
    send_event(fd, packet);
    broadcast_event(server, fd, packet);
}

void        sync_map(int fd, t_map *map)
{
    char    packet[FIXED_PACKET_LENGHT];
    int     x = 0;
    int     y = 0;

    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            switch (map->matrix[i][j].env) {
                case ENV_WALL:
                    sprintf(packet, "terrain 1 %02d %02d", x, y);
                    send_event(fd, packet);
                    break;

                default:
                    break;
            }
        }
    }
}
