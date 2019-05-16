#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#ifndef DATASET
#define DATASET


/*
 * Ornek ev veri yapisi
 * Bu veri yapisini kullanabilir
 * ya da kendiniz yeni bir yapi 
 * kodlayabilirsiniz.  
 */

typedef struct house{
  int id;
  int lotarea;
  char* street;
  int saleprice;
  char* neighborhood;
  int yearbuilt;
  int overallqual;
  int overallcond;
  char* kitchenqual;
} House;


int read_house_data(char* filename, House houses[]);
void print_house(House *house, int houseCount);
House get_house_byid(House *houses, int houseCount);
House* get_neighborhoods(House *house, int houseCount, int id);
void mean_sale_prices(House* houses,char* criter_name, int houseCount);
void sort_houses(House* houses,char* criter_name);

int find_smallest_lotarea(House* houses, int houseCount);
int find_biggest_lotarea(House* houses, int houseCount);

#endif
