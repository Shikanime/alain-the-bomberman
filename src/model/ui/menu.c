#include <stdlib.h>
#include <stdio.h>
#include "./menu.h"

t_menu      *create_menu()
{
    t_menu  *menu = malloc(sizeof(t_menu));

    if (menu) {
        menu->client_mode = create_button(0, 80, 320, 400, "Search");
        if (menu->client_mode) {
            destroy_menu(menu);
            return (menu);
        }
        menu->server_mode = create_button(320, 80, 320, 400, "Host");
        if (menu->server_mode) {
            destroy_menu(menu);
            return (menu);
        }
    } else {
        perror("Fail to create menu");
    }
    return (menu);
}

void destroy_menu(t_menu *menu)
{
    if (menu) {
        if (menu->client_mode) {
            destroy_button(menu->client_mode);
        }
        if (menu->server_mode) {
            destroy_button(menu->server_mode);
        }
        free(menu);
    }
}
