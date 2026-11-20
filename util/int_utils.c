#include "int_utils.h"

int get_nth_digit(int value, int pos) {
    int divider = 1;
    int val = -1;
    if (value == 0) {
        return -1;
    }
    for (int i = 0; i < pos; i++) {
        val = value;
        val /= divider;
        divider *= 10;
    }

    if (val == -1) {
        return -1;
    }
    return val % 10;
}
