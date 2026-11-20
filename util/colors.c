#include "colors.h"

#include <stdlib.h>

#include "ncurses.h"

void init_colors() {
    if (has_colors()) {
        init_color(LIGHT_GREEN, 600, 1000, 600);
        init_color(COLOR_BROWN, 270, 137, 47);
        init_color(COLOR_GREY, 200, 200, 200);
        init_color(COLOR_LIGHT_BLUE, 611, 1000, 1000);
        init_color(COLOR_BEIGE, 1000, 839, 611);
        init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(GRASS_COLOR, COLOR_GREEN, COLOR_GREEN);
        init_pair(ROAD_COLOR, COLOR_BLACK, COLOR_BLACK);
        init_pair(ROAD_STRIPE_COLOR, COLOR_WHITE, COLOR_WHITE);
        init_pair(FROG_COLOR, LIGHT_GREEN, LIGHT_GREEN);
        init_pair(WATER_COLOR, COLOR_WHITE, COLOR_BLUE);
        init_pair(LOG_COLOR, COLOR_BROWN, COLOR_BROWN);
        init_pair(CAR_COLOR_RED, COLOR_RED, COLOR_RED);
        init_pair(CAR_TIRE_COLOR, COLOR_GREY, COLOR_GREY);
        init_pair(CAR_GLASS_COLOR, COLOR_LIGHT_BLUE, COLOR_LIGHT_BLUE);
        init_pair(LOG_BROWN_COLOR, COLOR_BROWN, COLOR_BROWN);
        init_pair(LOG_BEIGE_COLOR, COLOR_BEIGE, COLOR_BEIGE);
        init_pair(CAR_COLOR_BLUE, COLOR_CYAN, COLOR_CYAN);
        init_pair(CAR_COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    } else {
        printf("Your terminal does not support colors! Exiting now.");
        exit(1);
    }
}