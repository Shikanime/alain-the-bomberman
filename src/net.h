#pragma once

#include <arpa/inet.h>
#include "./net/socket.h"

#define MESSAGE_LENGTH 15

int await_event(t_socket *s);
int dispatch_event(t_socket *s);
void send_event(t_socket *socket, const char *command);
