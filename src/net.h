#pragma once

#include <arpa/inet.h>
#include "./server.h"
#include "./net/conn.h"
#include "./game/map.h"

#define FIXED_PACKET_LENGHT 20

void broadcast_packet(t_conn *s, int sender_fd, const char *packet);
void send_packet(int fd, const char *packet);
void close_connection(t_conn *s, int fd);
int conn_client_mode(t_conn *conn, const char *address, uint16_t port);
int conn_server_mode(t_conn *conn, uint16_t port);
int handle_packet(t_server *server, int fd);
int handle_join(t_server *server);
