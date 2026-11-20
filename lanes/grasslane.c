#include "grasslane.h"

#include "../util/colors.h"

#include <ncurses.h>
#include <stdlib.h>

grasslane* grasslane_init(int row) {
    grasslane* lane = malloc(sizeof(grasslane));
    lane->row = row;
    lane->drawn = false;

    return lane;
}

void grasslane_draw(grasslane* lane, const env_data* data) {
    if (!lane->drawn) {
        attron(COLOR_PAIR(GRASS_COLOR));
        for (int y = lane->row; y < lane->row + 3; y++) {
            for (int x = 0; x < data->cols; x++) {
                move(y, x);
                addch(' ');
            }
        }
        attroff(COLOR_PAIR(GRASS_COLOR));
        lane->drawn = true;
    }
}
