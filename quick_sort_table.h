#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"
#define PRICE 1
#define YEAR 2
#define AREA 3

#ifndef QUICK
#define QUICK

void swapper(House *x, House *y);
int partition_price(House *array, int low, int high);
int partition_year(House *array, int low, int high);
int partition_lotArea(House *array, int low, int high);

void quick_sort_unwrapper(House *array, int low, int high, int type);
void quick_sort_type(House *array, int size, int type);

#endif