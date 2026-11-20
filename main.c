#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "entities/car.h"
#include "entities/log.h"
#include "entities/player.h"
#include "entities/scoreboard.h"
#include "lanes/lanemanager.h"
#include "structs/env_data.h"
#include "structs/configs/logconfig.h"
#include "structs/config.h"
#include "util/colors.h"

void quit(lanemanager* manager);

int main(void) {
    srand(time(NULL));
    int rows = 0, cols = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, true);
    curs_set(0);
    start_color();

    init_colors();
    bool game_over = false;

    mvprintw(0, 1, "Croaker! A legally distinct Frogger clone");
    getmaxyx(stdscr, rows, cols);
    refresh();

    // env data
    env_data data;
    data.cols = cols;
    data.rows = rows;

    lanemanager* manager = manager_init(&data);

    while (!game_over) {
        move(0, 30);
        int ch = getch();
        getmaxyx(stdscr, rows, cols);
        data.cols = cols;
        data.rows = rows;

        if (ch == 'q') {
            quit(manager);
        }

        if (ch == '\n') {
            game_over = true;
        }

        if (ch == ' ') {
            manager_regenerate(manager, &data);
        }

        if (manager_is_game_over(manager)) {
            game_over = true;
            break;
        }

        manager_update(manager, &data);
        manager_set_player_input(manager, ch);

        manager_draw(manager, &data);

        refresh();

        napms(16);
    }

    clear();
    move(rows / 2, cols / 2 - 5);
    addstr("GAME OVER!");
    refresh();
    while (getch() != 'q') {
    }
    quit(manager);
    return 0;
}

void quit(lanemanager* manager) {
    lanemanager_destroy(manager);
    clear();
    refresh();
    endwin();
    exit(0);
}