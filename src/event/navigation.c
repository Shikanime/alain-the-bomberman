#include "./navigation.h"

void handle_navigation_events(t_client *client)
{
    if (client->state == CLIENT_GAME_OUT) {
        client->state = CLIENT_EXIT;
    }
}
