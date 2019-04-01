#include <stdio.h>
#include "./nav.h"

t_nav       *create_nav()
{
    t_nav   *nav = malloc(sizeof(t_nav));

    if (nav == NULL) {
        perror("Fail to allocate nav");
        return (NULL);
    }
    nav->size = 2;
    nav->valided = false;
    nav->cursor = 0;
    return (nav);
}

void destroy_nav(t_nav *nav)
{
    if (nav != NULL) {
        free(nav);
    }
}
