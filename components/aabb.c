#include "aabb.h"

bool aabb_colliding(const aabb* self, const aabb* other) {
    bool coll_left = true;
    bool coll_right = true;
    bool coll_top = true;
    bool coll_bottom = true;

    if (self->posx >= other->posx + other->sizex) {
        coll_left = false;
    }

    if (self->posx + self->sizex <= other->posx) {
        coll_right = false;
    }

    if (self->posy >= other->posy + other->sizey) {
        coll_bottom = false;
    }

    if (self->posy + self->sizey <= other->posy) {
        coll_top = false;
    }

    return coll_left && coll_right && coll_top && coll_bottom;
}