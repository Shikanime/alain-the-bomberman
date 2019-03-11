#pragma once

#include "./button.h"

typedef struct      s_menu
{
    t_button        *server_mode;
    t_button        *client_mode;
}                   t_menu;

t_menu  *create_menu();
void    destroy_menu(t_menu *menu);
