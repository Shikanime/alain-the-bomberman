
#include "./attack.h"
#include "./placement.h"

int allahu_akbar(t_env *env, t_hero *hero)
{
    t_bomb *bomb = create_bomb(
        hero->position->x
            + BOMB_HEIGHT / 2
            - BOMB_WIDTH / 2,
        hero->position->y
            + BOMB_HEIGHT / 2
            - BOMB_WIDTH / 2
    );

    if (bomb) {
        return (place_bomb(env, bomb));
    }
    return (-1);
}
