#include "./movement.h"

void move_hero_up(t_hero *hero, t_env *env)
{
    (void)env;
    if (0 <= hero->position->y - (int)hero->body->width / 2) {
        hero->position->y = hero->position->y - (int) hero->speed;
    } else {
        hero->position->y = 0;
    }
}

void move_hero_down(t_hero *hero, t_env *env)
{
    if (hero->position->y + (int)hero->body->height < (int)env->sz.height) {
        hero->position->y = hero->position->y + (int) hero->speed;
    } else {
        hero->position->y = (int)(env->sz.height - hero->body->height);
    }
}

void move_hero_left(t_hero *hero, t_env *env)
{
    (void)env;
    if (0 <= hero->position->x - (int)hero->body->height / 2) {
        hero->position->x = hero->position->x - (int) hero->speed;
    } else {
        hero->position->x = 0;
    }
}

void move_hero_right(t_hero *hero, t_env *env)
{
    if (hero->position->x + (int)hero->body->width
        < (int)env->sz.width) {
        hero->position->x = hero->position->x + (int) hero->speed;
    } else {
        hero->position->x = (int)(
            env->sz.width - hero->body->width
        );
    }
}
