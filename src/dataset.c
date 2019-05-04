#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINEMAXX 1024

void read_house_data(char* filename, House houses[], int houseCount){
  printf("Reading file %s\n",filename);  
  // TODO
  char lineBuffer[LINEMAXX];
  char lineRead[LINEMAXX];
  char *field;
  int i;

  FILE *dataFile = fopen(filename, "r");

  if (dataFile == 0){
    printf("FILE OPENING ERROR!\n");
  }

  fgets(lineBuffer, sizeof(lineBuffer), dataFile);

  fgets(lineRead, sizeof(lineRead), dataFile);

  i = 0;

  while ((getc(dataFile)) != EOF){
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
    fgets(lineRead, sizeof(lineRead), dataFile);
    houseCount = i;
  }

  
  return;
}

void print_house(House house){
  printf("Print House dataset\n");
  // TODO
  printf("House information: \n")
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

float* mean_sale_prices(House* houses,char* criter_name){
  printf("Calculate mean sale prices by %s \n",criter_name);
  // TODO

  return ;
}
void sort_houses(House* houses,char* criter_name){
  printf("Sort house by %s and save \n",criter_name);
  // TODO
  return ;
}
