#include "time_utils.h"

void timespec_add_ms(struct timespec* ts, long ms)
{
    ts->tv_nsec += ms * 1000000L;
    ts->tv_sec  += ts->tv_nsec / 1000000000L;
    ts->tv_nsec %= 1000000000L;
}

long timespec_get_ms_difference(struct timespec* t1, struct timespec* t2) {
    return (t2->tv_sec - t1->tv_sec) * 1000L + (t2->tv_nsec - t1->tv_nsec) / 1000000L;
}
