#pragma once
#include <stdbool.h>

struct aabb { // axis-aligned bounding box, used for collision detection
    int posx, posy;
    int sizex, sizey;
};
typedef struct aabb aabb;

bool aabb_colliding(const aabb* self, const aabb* other);