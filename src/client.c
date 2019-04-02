#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "./client.h"
#include "./net.h"
#include "./event.h"
#include "./render.h"
#include "./ressource.h"
#include "./config.h"
#include "./system/bomberman.h"

int enter_client_loop(SDL_Window *window, t_client *client);

t_client        *create_client(size_t width, size_t height)
{
    t_client    *client = malloc(sizeof(t_client));

    if (client == NULL) {
        perror("Fail to allocate client");
        return (NULL);
    }
    client->state = CLIENT_MENU;
    client->menu = create_menu();
    client->nav = create_nav();
    client->map = create_map(width, height);
    client->server = create_conn();
    client->player = NULL;
    client->player_nb = 2;
    client->address = "127.0.0.1";
    client->port = 3542;
    return client;
}

void destroy_client(t_client *client)
{
    if (client != NULL) {
        destroy_map(client->map);
        destroy_conn(client->server);
        free(client);
    }
}

int             run_client()
{
    SDL_Window  *window = NULL;
    t_client    *client = NULL;

    window = SDL_CreateWindow(SCREEN_TITLE,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Game window fail to start: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }
    client = create_client(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20);
    if (!client) {
        fprintf(stderr, "Game client fail to start: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    if (enter_client_loop(window, client) < 0) {
        fprintf(stderr, "Game quit with exception: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }
    destroy_client(client);
    SDL_DestroyWindow(window);
    return (EXIT_SUCCESS);
}

int                 enter_client_loop(SDL_Window *window, t_client *client)
{
    SDL_Renderer    *renderer = NULL;
    Uint32          current_time = 0;
    Uint32          previous_time = 0;
    Uint32          mspf = 1000 / 60;
    t_ressource     *ressource = NULL;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_DestroyRenderer(renderer);
        return (-1);
    }
    ressource = create_ressource(renderer);
    if (!ressource) {
        SDL_DestroyRenderer(renderer);
        return (-1);
    }
    while (client->state != CLIENT_EXIT) {
        sub_server_packets(client);
        sub_inputs(client);
        sub_events(client);
        current_time = SDL_GetTicks();
        if (current_time - previous_time > mspf) {
            previous_time = current_time;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            sub_renderer(client, renderer, ressource);
            SDL_RenderPresent(renderer);
        } else {
            SDL_Delay(mspf - (current_time - previous_time));
        }
    }
    destroy_ressource(ressource);
    SDL_DestroyRenderer(renderer);
    return (1);
}
