#pragma once

#include <stdint.h>

typedef enum {
    SERVER_HALT,
    SERVER_RUN
} e_server_status;

int run_server(uint16_t port);
