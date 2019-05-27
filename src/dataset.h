#include<stdio.h>
#include <stdlib.h>
#include <string.h>

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
  double saleprice;
  char* neighborhood;
  int yearbuilt;
  int overallqual;
  int overallcond;
  char* kitchenqual;
} House;

typedef struct houseYear {
  int year;
  int counter;
  double mean_price;
} hYear;

void read_house_testData(char* filename, House houses[]);
int calculate_house_count(char* filename);
void read_house_data(char* filename, House houses[]);
void print_house(House *houses, int houseCount);
void print_house_by_id(House *houses, int id);
void get_house_byid(House *houses, int houseCount);
void get_neighborhoods(House *houses, int houseCount);
void mean_sale_prices(House* houses, int houseCount);
void sort_houses(House* houses, int houseCount, int criter);

int find_smallest_lotarea(House* houses, int houseCount);
int find_biggest_lotarea(House* houses, int houseCount);
void print_topN(House* houses, int houseCount, int N);

#endif
