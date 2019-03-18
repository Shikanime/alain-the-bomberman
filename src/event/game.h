#pragma once

#include <SDL2/SDL.h>
#include "../client.h"

void handle_game_inputs(SDL_Event *event, t_client *client);
void handle_game_events(t_client *client);
void handle_game_server_init(t_client *client, char *packet);
void handle_game_server_packets(t_client *client, char *packet);
