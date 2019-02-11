#pragma once

#include <arpa/inet.h>
#include "./model/net/socket.h"

#define MESSAGE_LENGTH 10

int await_event(t_socket *s);
int dispatch_event(t_socket *s);
void send_event(t_socket *socket, const char *command);
