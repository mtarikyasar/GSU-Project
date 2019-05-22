#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

#ifndef QUICK
#define QUICK

void swapper(House *x, House *y);
int partition(House *array, int low, int high);
void quick_sort_unwrapper(House *array, int low, int high);
void quick_sort_houses(House *array, int size);

#endif