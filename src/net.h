#pragma once

#include <arpa/inet.h>
#include "./net/conn.h"

void broadcast_event(t_conn *s, int sender_fd, const char *event);
void close_connection(t_conn *s, int fd);
void send_event(t_conn *conn, const char *command);
int conn_client_mode(t_conn *conn, const char *address, uint16_t port);
int conn_server_mode(t_conn *conn, uint16_t port);
int handle_packet(t_conn *s, int fd);
int handle_join(t_conn *s);
