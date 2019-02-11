#include <stdlib.h>
#include <stdio.h>
#include "./button.h"

t_button        *create_button(int x, int y, size_t width, size_t height, const char *text)
{
    t_button    *button = malloc(sizeof(t_button));

    if (button) {
        button->position = create_position(x, y);
        button->body = create_rect(width ,height);
        button->text = text;
    } else {
        perror("Fail to create button");
    }
    return (button);
}

void destroy_button(t_button *button)
{
    if (button) {
        destroy_position(button->position);
        destroy_rect(button->body);
        free(button);
    }
}
