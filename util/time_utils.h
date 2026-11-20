#pragma once

#include <time.h>

void timespec_add_ms(struct timespec* ts, long ms);
long timespec_get_ms_difference(struct timespec* t1, struct timespec* t2);