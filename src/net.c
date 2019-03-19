#include <stdio.h>
#include <unistd.h>
#include "./net.h"
#include "./system/bomberman.h"

int read_from_socket(int fd, char (*msg_buff)[FIXED_PACKET_LENGHT]);
void sync_player(t_server *server, int fd);
void sync_map(t_server *server, int fd);

void broadcast_packet(t_conn *conn, int sender_fd, const char *packet)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &conn->active_set)) {
            if (i != conn->fd && i != sender_fd) {
                send(i, packet, FIXED_PACKET_LENGHT, MSG_DONTWAIT);
            } else if (sender_fd == conn->fd) {
                send(i, packet, FIXED_PACKET_LENGHT, MSG_DONTWAIT);
            }
        }
    }
}

void close_connection(t_conn *conn, int fd)
{
    close(fd);
    FD_CLR(fd, &conn->active_set);
}

void        send_packet(int fd, const char *packet)
{
    char    buff[FIXED_PACKET_LENGHT];

    sprintf(buff, "%-*s\n", FIXED_PACKET_LENGHT - 2, packet);
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

int         handle_join(t_server *server)
{
    int     fd = 0;

    fd = accept(server->conn->fd, (struct sockaddr*)&server->conn->addr, &server->conn->len);
    if (fd < 0) {
        return (-1);
    }
    FD_SET(fd, &server->conn->active_set);
    sync_player(server, fd);
    sync_map(server, fd);
    server->player_nb++;
    printf("New connection on %d\n", fd);
    return (1);
}

int         handle_packet(t_server *server, int fd)
{
    char    msg_buff[FIXED_PACKET_LENGHT];

    if (read_from_socket(fd, &msg_buff) < 0) {
        close_connection(server->conn, fd);
        return (-1);
    }
    broadcast_packet(server->conn, fd, msg_buff);
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

void        sync_player(t_server *server, int fd)
{
    char        packet[FIXED_PACKET_LENGHT];
    int         x = 0;
    int         y = 0;
    t_bomberman *player = create_bomberman();

    do {
        x = rand() % (int)server->map->width;
        y = rand() % (int)server->map->height;
    } while (!place_bomberman(server->map, player, x, y));
    sprintf(packet, "spawn 1 %02d %02d", x, y);
    send_packet(fd, packet);
    broadcast_packet(server->conn, fd, packet);
}

void        sync_map(t_server *server, int fd)
{
    char    packet[FIXED_PACKET_LENGHT];

    for (size_t i = 0; i < server->map->height; i++) {
        for (size_t j = 0; j < server->map->width; j++) {
            if (server->map->matrix[i][j].bomberman) {
                sprintf(packet, "spawn 1 %02d %02d", (int)j, (int)i);
                send_packet(fd, packet);
            }
            switch (server->map->matrix[i][j].env) {
                case ENV_WALL:
                    sprintf(packet, "terrain 1 %02d %02d", (int)j, (int)i);
                    send_packet(fd, packet);
                    break;

                default:
                    break;
            }
        }
    }
}
