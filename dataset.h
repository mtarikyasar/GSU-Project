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
  int saleprice;
  char* neighborhood;
  int yearbuilt;
  int overallqual;
  int overallcond;
  char* kitchenqual;
} House;

typedef struct houseYear {
  int year;
  double price;
  int counter;
  double mean_price;
  struct houseYear *next;
} hYear;

void read_house_testData(char* filename, House houses[]);
int calculate_house_count(char* filename);
void read_house_data(char* filename, House houses[]);
void print_house(House *house, int houseCount);
void print_house_by_id(House *house, int id);
House *get_house_byid(House *house, int houseCount);
void get_neighborhoods(House *house, int houseCount);
void mean_sale_prices(House* houses, int houseCount);
void sort_houses(House* houses,char* criter_name);
void binarySort(House *houses, int houseCount);
void house_changer(House a, House b);

int find_smallest_lotarea(House* houses, int houseCount);
int find_biggest_lotarea(House* houses, int houseCount);

#endif