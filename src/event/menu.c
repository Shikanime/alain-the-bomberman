#include <unistd.h>
#include "../nav.h"
#include "../net.h"
#include "./menu.h"

void handle_menu_inputs(SDL_Event *event, t_client *client)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_UP:
                    client->nav->cursor = (1 + client->nav->cursor) % client->nav->size;
                    break;

                case SDLK_DOWN:
                    client->nav->cursor = (1 - client->nav->cursor) % client->nav->size;
                    break;

                case SDLK_SPACE:
                    switch (client->nav->cursor) {
                        case JOIN_GAME:
                            if (conn_client_mode(client->server, client->address, client->port) > 0) {
                                client->state = CLIENT_GAME_INIT;
                            }
                            break;

                        case CREATE_GAME:
                            if (start_server(client) > 0) {
                                client->state = CLIENT_GAME_INIT;
                            }
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
    }
}
