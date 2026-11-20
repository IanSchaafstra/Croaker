#include "array_utils.h"

void reverse_array_in_place(int* array, int size) {
    int index = size - 1;
    int copied_arr[size];

    for (int i = 0; i < size; i++) {
        copied_arr[i] = array[i];
    }

    for (int i = 0; i < size; i++) {
        array[i] = copied_arr[index];
        index--;
    }
}