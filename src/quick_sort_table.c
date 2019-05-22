#include <stdlib.h>
#include <stdio.h>
#include "dataset.h"

void swapper(House *x, House *y) {
    House temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int partition(House *array, int low, int high) {
    int pivot = high;
    int new_pivot = low;
    int d;
    for (d = low; d < high; d++) {
        if (array[d].yearbuilt < array[pivot].yearbuilt) {
            swapper(&array[d], &array[new_pivot]);
            new_pivot++;
        }
    }
    swapper(&array[new_pivot], &array[pivot]);
    return new_pivot;
}

void quick_sort_unwrapper(House *array, int low, int high) {
    int p;
    if (low < high) {
        p = partition(array, low, high);
        quick_sort_unwrapper(array, low, p-1);
        quick_sort_unwrapper(array, p+1, high);
    }
}

void quick_sort_houses(House *array, int size) {
    quick_sort_unwrapper(array, 0, size-1);
}