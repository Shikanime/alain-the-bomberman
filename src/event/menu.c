#include <unistd.h>
#include "./menu.h"

void handle_menu_inputs(SDL_Event *event)
{
    if (event->button.x > 10 && event->button.x < 600) {
        if (event->button.y > 10 && event->button.y < 600) {
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                write(1, "ici", 3);
            }
        }
    }
}
