#include "./hero.h"
#include "../action/movement.h"
#include "../action/attack.h"

void dispatch_move_event(SDL_Keycode key, t_hero *hero, t_game *game);

void handle_hero_inputs(SDL_Event *event, t_game *game)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            for (size_t i = 0; i < game->env->hero_nb; i++) {
                dispatch_move_event(event->key.keysym.sym, game->env->heros[i], game);
            }
            if (event->key.keysym.sym == SDLK_SPACE) {
                if (allahu_akbar(game->env, game->env->heros[0]) > 0) {
                    send_event(game->client, "bomb     \n");
                }
            }
            break;

        default:
            break;
    }
}

void dispatch_move_event(SDL_Keycode key, t_hero *hero, t_game *game)
{
    switch (key) {
        case SDLK_UP:
            move_hero_up(hero, game->env);
            send_event(game->client, "up");
            break;
        case SDLK_DOWN:
            move_hero_down(hero, game->env);
            send_event(game->client, "down");
            break;
        case SDLK_LEFT:
            move_hero_left(hero, game->env);
            send_event(game->client, "left");
            break;
        case SDLK_RIGHT:
            move_hero_right(hero, game->env);
            send_event(game->client, "right");
            break;
    }
}
