#include <unistd.h>
#include <SDL2/SDL.h>
#include "./menu.h"
#include "../game.h"

void            handle_menu_inputs(SDL_Event *event, t_game *game)
{
    (void) game;

    if (event->button.x > 10 && event->button.x < 600) {
        if (event->button.y > 10 && event->button.y < 600) {
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                write(1, "ici", 3);
            }
        }
    }
}
