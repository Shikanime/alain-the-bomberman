#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./client.h"
#include "./server.h"
#include "./boot.h"

void *detact_server(void *nav);

int     main(void)
{
    int code = EXIT_FAILURE;

    if (init_subsystem() < 0) {
        return (code);
    }
    code = run_client();
    quit_subsystem();
    return (code);
}
