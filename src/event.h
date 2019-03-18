#pragma once

#include "./client.h"
#include "./server.h"

void sub_inputs(t_client *client);
void sub_events(t_client *client);
void sub_server_packets(t_client *client);
void sub_client_packets(t_server *server);
