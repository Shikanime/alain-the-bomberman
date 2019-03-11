#include <sys/socket.h>
#include "./event.h"
#include "./event/menu.h"
#include "./event/game.h"
#include "./net.h"
#include "./net/conn.h"

int handle_join(t_conn *s);
int handle_packet(t_conn *s, int fd);
int read_from_socket(int fd, char (*msg_buff)[20]);

void        sub_packets(t_game *game)
{
    char    packet_msg_buff[20];

    if (recv(game->client->fd, packet_msg_buff, 20, MSG_DONTWAIT | MSG_NOSIGNAL) < 0) {
        switch (state) {
            case GAME_FLOW_RUN:
                handle_game_events(game);
                break;

            default:
                break;
        }
    }
}

void            sub_inputs(t_game *game)
{
    SDL_Event   event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game->state = GAME_FLOW_EXIT;
        } else {
            switch (game->state) {
                case GAME_FLOW_MENU:
                    handle_menu_inputs(&event, game);
                    break;

                case GAME_FLOW_RUN:
                    handle_game_inputs(&event, game);
                    break;

                default:
                    break;
            }
        }
    }
}

void broadcast_packets(t_conn *s)
{
    s->read_set = s->active_set;
    if (select(FD_SETSIZE, &s->read_set, NULL, NULL, NULL) >= 0) {
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &s->read_set)) {
                if (i == s->fd) {
                    if (handle_join(s) < 0) {
                        printf("Fail to join socket of fd: %d\n", i);
                    }
                } else {
                    if (handle_packet(s, i) < 0) {
                        printf("Fail to hanle a message from fd: %d\n", i);
                    }
                }
            }
        }
    }
}

int     handle_join(t_conn *s)
{
    int fd = 0;

    fd = accept(s->fd, (struct sockaddr*)&s->addr, &s->len);
    if (fd < 0) {
        return (-1);
    }
    FD_SET(fd, &s->active_set);
    printf("New connection on %d\n", fd);
    return (1);
}

int         handle_packet(t_conn *s, int fd)
{
    char    msg_buff[20];

    if (read_from_socket(fd, &msg_buff) < 0) {
        close_connection(s, fd);
        return (-1);
    }
    handle_game_broadcasts(s, fd, msg_buff);
    printf("Message received from %d of content: %.*s", fd, 20, msg_buff);
    return (1);
}

int         read_from_socket(int fd, char (*msg_buff)[20])
{
    ssize_t n = recv(fd, msg_buff, 20, 0);

    if (n < 0) {
    return (-1);
    }
    if (n == 0) {
        return (-1);
    }
    return 0;
}
