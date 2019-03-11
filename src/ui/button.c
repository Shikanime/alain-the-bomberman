#include <stdio.h>
#include "./button.h"

t_button        *create_button(int x, int y, size_t width, size_t height, const char *text)
{
    t_button    *button = malloc(sizeof(t_button));

    if (!button) {
        perror("Fail to allocate button");
        return (NULL);
    }
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    button->text = text;
    return (button);
}

void destroy_button(t_button *button)
{
    if (button != NULL) {
        free(button);
    }
}
