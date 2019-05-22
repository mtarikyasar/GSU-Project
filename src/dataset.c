#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quick_sort_table.h"
#define LINEMAXX 1024

int read_house_data(char* filename, House houses[]){
  printf("Reading file: %s\n",filename);  
  // TODO
  char lineBuffer[LINEMAXX];
  char lineRead[LINEMAXX];
  char *field; 
  int i;
  int houseCount = 0;

  FILE *dataFile = fopen(filename, "r");
  
  if (dataFile == NULL){
    printf("Failed to open file...\n");
  } 
 
  fgets(lineBuffer, sizeof(lineBuffer), dataFile);
  i = 0;

  while ((getc(dataFile)) != EOF){
    fgets(lineRead, sizeof(lineRead), dataFile);
    
      //Get ID
        field = strtok(lineRead, ",");
        houses[i].id = atoi(field);
      //Get lotarea
        field = strtok(NULL, ",");
        houses[i].lotarea = atoi(field);
      //Get street
        field = strtok(NULL, ",");
        houses[i].street = malloc(sizeof(field));
        strcpy(houses[i].street, field);
      //Get saleprice
        field = strtok(NULL, ",");
        houses[i].saleprice = atoi(field);
      //Get neighborhood
        field = strtok(NULL, ",");
        houses[i].neighborhood = malloc(sizeof(field));
        strcpy(houses[i].neighborhood, field);
      //Get yearbuilt
        field = strtok(NULL, ",");
        houses[i].yearbuilt = atoi(field);
      //Get overallqual
        field = strtok(NULL, ",");
        houses[i].overallqual = atoi(field);
      //Get overallcond
        field = strtok(NULL, ",");
        houses[i].overallcond = atoi(field);
      //Get kitchenqual
        field = strtok(NULL, ",");
        houses[i].kitchenqual = malloc(sizeof(field));
        strcpy(houses[i].kitchenqual, field);

      i++;
      houseCount = i;
  }

  return houseCount;
}

void print_house(House house){
  printf("Print House dataset\n");
  // TODO
  printf("House information: \n");
  printf("\tID: %d\n", house.id);
  printf("\tLot area: %d\n", house.lotarea);
  printf("\tStreet: %s\n", house.street);
  printf("\tSale price: %d\n", house.saleprice);
  printf("\tNeighborhood: %s\n", house.neighborhood);
  printf("\tBuilt in: %d\n", house.yearbuilt);
  printf("\tOverall Quality: %d\n", house.overallqual);
  printf("\tOverall Condition: %d\n", house.overallcond);
  printf("\tKitchen Quality: %s\n", house.kitchenqual);

  return;
}

House get_house_byid(int id, House *houses, int houseCount){
  printf("Get house with id %d \n", id);
  // TODO

  for (size_t i = 0; i < houseCount; i++){
    if (id == houseCount){
      return houses[id];
    }
  }
}

House* get_neighborhoods(House *house, int houseCount, int id){
  int j = 0;
  House *neighList;
  printf("Get neighborhoods of house with id %d\n", id);
  // TODO
    for (size_t i = 0; i < houseCount; i++)
    {
      if (id == house[i].id)
      {
        neighList[j].neighborhood = house[i].neighborhood;
        j++;
      }
    }

    return neighList;
}

float mean_sale_prices(House* houses, int houseCount){
  printf("Calculate mean sale prices by ...\n");
  // TODO
  float price = 0;

  if (1 == 1) {

    
    int minY = 3000, maxY = 0;
    for (int i = 0; i < houseCount; i++) {
      if (houses[i].yearbuilt < minY) {
        minY = houses[i].yearbuilt;
      }
      if (houses[i].yearbuilt > maxY) {
        maxY = houses[i].yearbuilt;
      }
    }

    int yearSize = maxY - minY;
    printf("TESTESTESTEST\n");

    hYear *yearTable = malloc(yearSize*sizeof(hYear));

    for (int i = 0; i < yearSize; i++) {
      yearTable[i].year = minY + i;
      yearTable[i].counter = 0;
      yearTable[i].price = 0;
    }

    quick_sort_houses(houses, houseCount);

    for (int i = 0, j = 0; i < houseCount; i++) {
      yearTable[i].mean_price = 0;
      while ((yearTable[i].year == houses[j].yearbuilt) && (j < houseCount)) {
        yearTable[i].mean_price += houses[j].saleprice;
        yearTable[i].counter++; 
        j++;
      }
      yearTable[i].mean_price /= yearTable[i].counter;
    }
    price = yearTable[5].mean_price;
  }
  return price;
}

void sort_houses(House* houses,char* criter_name) {
  printf("Sort house by %s and save \n",criter_name);
  // TODO
  return ;
}



