#pragma once

#include "./client.h"
#include "./server.h"

void sub_navigation_events(t_client *client);
void sub_input_events(t_client *client);
void sub_game_events(t_client *client);
void sub_server_packets(t_client *client);
void sub_client_packets(t_server *server);
