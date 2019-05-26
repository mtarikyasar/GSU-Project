#include <stdlib.h>
#include <stdio.h>
#include "dataset.h"

void swapper(House *x, House *y) {
    House temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int partition_price(House *array, int low, int high) {
    int pivot = high;
    int new_pivot = low;
    int d;
    for (d = low; d < high; d++) {
        if (array[d].saleprice < array[pivot].saleprice) {
            swapper(&array[d], &array[new_pivot]);
            new_pivot++;
        }
    }
    swapper(&array[new_pivot], &array[pivot]);
    return new_pivot;
}

int partition_year(House *array, int low, int high) {
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

int partition_lotArea(House *array, int low, int high) {
    int pivot = high;
    int new_pivot = low;
    int d;
    for (d = low; d < high; d++) {
        if (array[d].lotarea < array[pivot].lotarea) {
            swapper(&array[d], &array[new_pivot]);
            new_pivot++;
        }
    }
    swapper(&array[new_pivot], &array[pivot]);
    return new_pivot;
}

int partition_condition(House *array, int low, int high) {
    int pivot = high;
    int new_pivot = low;
    int d;
    for (d = low; d < high; d++) {
        if (array[d].overallcond < array[pivot].overallcond) {
            swapper(&array[d], &array[new_pivot]);
            new_pivot++;
        }
    }
    swapper(&array[new_pivot], &array[pivot]);
    return new_pivot;
}

int partition_quality(House *array, int low, int high) {
    int pivot = high;
    int new_pivot = low;
    int d;
    for (d = low; d < high; d++) {
        if (array[d].overallqual < array[pivot].overallqual) {
            swapper(&array[d], &array[new_pivot]);
            new_pivot++;
        }
    }
    swapper(&array[new_pivot], &array[pivot]);
    return new_pivot;
}


void quick_sort_unwrapper(House *array, int low, int high, int type) {
    int p;
    switch (type) {
        case 1: 
            if (low < high) {
                p = partition_price(array, low, high);
                quick_sort_unwrapper(array, low, p-1, type);
                quick_sort_unwrapper(array, p+1, high, type);
            }
            break;

        case 2: 
            if (low < high) {
                p = partition_year(array, low, high);
                quick_sort_unwrapper(array, low, p-1, type);
                quick_sort_unwrapper(array, p+1, high, type);
            }
            break;

        case 3:
            if (low < high) {
                p = partition_lotArea(array, low, high);
                quick_sort_unwrapper(array, low, p-1, type);
                quick_sort_unwrapper(array, p+1, high, type);
            }
            break;
        case 4:
            if (low < high) {
                p = partition_condition(array, low, high);
                quick_sort_unwrapper(array, low, p-1, type);
                quick_sort_unwrapper(array, p+1, high, type);
            }
            break;
        case 5:
            if (low < high) {
                p = partition_quality(array, low, high);
                quick_sort_unwrapper(array, low, p-1, type);
                quick_sort_unwrapper(array, p+1, high, type);
            }
            break;
        default: 
            break;
    }
}

void quick_sort_type(House *array, int size, int type) {
    quick_sort_unwrapper(array, 0, size-1, type);
} 
