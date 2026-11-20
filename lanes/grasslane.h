#pragma once

#include <stdbool.h>

#include "../structs/env_data.h"

struct grasslane {
    int row;
    bool drawn;
};
typedef struct grasslane grasslane;

grasslane* grasslane_init(int row);
void grasslane_draw(grasslane* lane, const env_data* data);