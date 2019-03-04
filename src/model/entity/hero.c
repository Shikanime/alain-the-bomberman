#include <stdlib.h>
#include <stdio.h>
#include "./hero.h"

t_hero      *create_hero(int x, int y)
{
    t_hero  *hero = malloc(sizeof(t_hero));

    if (!hero) {
        perror("Fail to create hero");
        return (NULL);
    }
    hero->position = create_position(x, y);
    hero->body = create_rect(40, 40);
    hero->speed = 40;
    return (hero);
}

void destroy_hero(t_hero *hero)
{
    if (hero) {
        free(hero);
    }
}
