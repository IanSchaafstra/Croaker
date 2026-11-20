#pragma once
#include <time.h>

#include "../components/aabb.h"
#include "../components/direction.h"
#include "../structs/configs/logconfig.h"

#define LOG_COOLDOWN 400 // ms
#define LOG_SIZE_X 12
#define LOG_SIZE_Y 3

typedef struct env_data env_data;

struct log {
    int posx, posy;
    int prevposx, prevposy;
    aabb collider;
    // double start_time, diff_time;
    struct timespec s_time, d_time;
    direction dir;
    long cooldown;
};
typedef struct log log;

log* log_init_from_config(const logconfig* conf);
void log_update(log* log, const env_data* data);
void log_draw(log* log, const env_data* data);
void log_update_aabb(log* log);
void log_sprite_draw(log* log, const env_data* data);