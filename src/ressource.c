#include "./ressource.h"
#include "./render/bomb.h"

t_ressource     *create_ressource(SDL_Renderer *renderer)
{
    t_ressource *ressource = malloc(sizeof(t_ressource));

    if (!ressource) {
        destroy_ressource(ressource);
        return (NULL);
    }
    ressource->bomb = load_bomb(renderer);
    return (ressource);
}

void destroy_ressource(t_ressource *ressource)
{
  if (ressource) {
    free(ressource);
  }
}
