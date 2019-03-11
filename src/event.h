#pragma once

#include "./game.h"

void sub_packets(t_game *game);
void sub_inputs(t_game *game);
void broadcast_packets(t_conn *s);
