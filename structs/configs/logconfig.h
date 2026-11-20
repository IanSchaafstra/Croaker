#pragma once

#include "../../components/direction.h"

struct logconfig {
    int row, col;
    direction dir;
    double cooldown;
};
typedef struct logconfig logconfig;