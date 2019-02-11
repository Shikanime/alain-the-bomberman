// #include <SDL_ttf.h>
#include "./engine.h"

const char *SCREEN_TITLE = "Bomberman";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int8_t init_window(t_engine *engine);

t_engine        *create_engine()
{
    t_engine    *engine = malloc(sizeof(t_engine));

    if (engine) {
        // if (TTF_Init() < 0) goto DEFER_TTF;
        if (init_window(engine) < 0) {
            destroy_engine(engine);
            return (engine);
        }
    }
    return (engine);
}

int8_t init_window(t_engine *engine)
{
    engine->window = SDL_CreateWindow(SCREEN_TITLE,
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
    if (!engine->window) {
        perror("Fail to create engine window");
        return (-1);
    }
    return (0);
}

void destroy_engine(t_engine *engine)
{
    if (engine) {
        if (engine->window) {
            SDL_DestroyWindow(engine->window);
        }
    }
}
