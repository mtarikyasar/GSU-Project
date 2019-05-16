#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

  if (dataFile == 0){
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

void print_house(House *house, int houseCount){
  // TODO
  for (size_t i = 0; i < houseCount-1; i++)
  {
    printf("House information: \n");
    printf("\tID: %d\n", house[i].id);
    printf("\tLot area: %d\n", house[i].lotarea);
    printf("\tStreet: %s\n", house[i].street);
    printf("\tSale price: %d\n", house[i].saleprice);
    printf("\tNeighborhood: %s\n", house[i].neighborhood);
    printf("\tBuilt in: %d\n", house[i].yearbuilt);
    printf("\tOverall Quality: %d\n", house[i].overallqual);
    printf("\tOverall Condition: %d\n", house[i].overallcond);
    printf("\tKitchen Quality: %s\n", house[i].kitchenqual);
    sleep(1/2);

  }
}

House get_house_byid(House *houses, int houseCount){
  int id = 0;
  printf("Get house with id %d \n", id);
  scanf("%d", &id);
  // TODO

  for (size_t i = 0; i < houseCount; i++){
    if (id == houses[i].id){
      return houses[i];
    }
  }
}

House* get_neighborhoods(House *houses, int houseCount, int id){
  //HATALI
  int j = 0;
  House *neighList;
  printf("Get neighborhoods of house with id %d\n", id);
  // TODO

    for (size_t i = 0; i < houseCount; i++){
      if (strcmp(houses[id].neighborhood, houses[i].neighborhood)){
        neighList[j].neighborhood = houses[i].neighborhood;
        j++;
      }
    }

    return neighList;
}

void mean_sale_prices(House* houses,char* criter_name, int houseCount){
  printf("Calculate mean sale prices by %s \n", criter_name);
  // TODO

  //Initialisations
    //For kitchenqual
      int ctrEx = 0;
      int ctrGd = 0;
      int ctrTA = 0;
      int ctrFa = 0;
      int ctrPo = 0;
      double kitQua[] = {0, 0, 0, 0, 0};

    //For overallqual
      //2 intervals for easy grouping
      int ctr1 = 0;
      int ctr2 = 0;
      int ctr3 = 0;
      int ctr4 = 0;
      int ctr5 = 0;
      double overallQual[] = {0, 0, 0, 0, 0};

    //For overallcond
      //2 intervals for easy grouping
      int ctr1_2 = 0;
      int ctr2_2 = 0;
      int ctr3_2 = 0;
      int ctr4_2 = 0;
      int ctr5_2 = 0;
      double overallcond[] = {0, 0, 0, 0, 0};

    //For lotarea
      int smallestLotArea = find_smallest_lotarea(houses, houseCount);
      int biggestLotArea = find_biggest_lotarea(houses, houseCount);
      double interval = (double)(biggestLotArea - smallestLotArea)/8; //We took 8 intervals
      int counters[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      double lotArea[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  //////////////////////

  House *newList;
  int neighCtr = 0; //For counting different neighborhoods
  int j = 0;
  int avg = 0;
  newList[0].neighborhood = malloc(sizeof(houses[0].neighborhood));
  strcpy(newList[0].neighborhood, houses[0].neighborhood);
  int criter = 0;

  if (strcmp(criter_name, "neighborhoods") == 1 || strcmp(criter_name, "neighborhood") == 1){
    criter = 1;
  }

  if (strcmp(criter_name, "kitchenqual")){
    criter = 2;
  }
  
  if (strcmp(criter_name, "overallqual")){
    criter = 3;
  }
  
  if (strcmp(criter_name, "overallcond")){
    criter = 4;
  }

  if (strcmp(criter_name, "lotarea")){
    criter = 5;
  }
  
  switch (criter) {
    case 1:
      for (size_t i = 0; i < houseCount; i++)
      {
        if (strcmp(newList[j].neighborhood, houses[i].neighborhood) == 0)
        {
          newList[j].neighborhood = malloc(sizeof(houses[i].neighborhood));
          strcpy(newList[j].neighborhood, houses[i].neighborhood);
          neighCtr++;
          j++;
        }
      }

      for (size_t j = 0; j < neighCtr; j++)
      {
        for (size_t i = 0; i < houseCount; i++)
        {
          /* code */
        }
        
      }
      
      break;
    
    case 2:

      for (size_t i = 0; i < houseCount; i++){
        if (strcmp("Ex", houses[i].kitchenqual)){
          kitQua[0] = kitQua[0] + houses[i].saleprice;
          ctrEx++; 
        }

        else if(strcmp("Gd", houses[i].kitchenqual)){
          kitQua[1] = kitQua[1] + houses[i].saleprice;
          ctrGd++;
        }

        else if(strcmp("TA", houses[i].kitchenqual)){
          kitQua[2] = kitQua[2] + houses[i].saleprice;
          ctrTA++;
        }

        else if(strcmp("Fa", houses[i].kitchenqual)){
          kitQua[3] = kitQua[3] + houses[i].saleprice;
          ctrFa++;
        }

        else if(strcmp("Po", houses[i].kitchenqual)){
          kitQua[4] = kitQua[4] + houses[i].saleprice;
          ctrPo++;
        }
      }

      printf("Average Excellent Quality Kitchens: %lf\n", (kitQua[0]/(double)(ctrEx)));
      printf("Average Good Quality Kitchens: %lf\n", (kitQua[1]/(double)(ctrGd)));
      printf("Average Typical/Average Quality Kitchens: %lf\n", (kitQua[2]/(double)(ctrTA)));
      printf("Average Fair Quality Kitchens: %lf\n", (kitQua[3]/(double)(ctrFa)));
      printf("Average Poor Quality Kitchens: %lf\n", (kitQua[4]/(double)(ctrPo)));

      break;

    case 3:

      for (size_t i = 0; i < houseCount; i++){
        if (0 <= houses[i].overallqual && houses[i].overallqual < 2){
          overallQual[0] = overallQual[0] + houses[i].saleprice;
          ctr1++; 
        }

        else if(2 <= houses[i].overallqual && houses[i].overallqual < 4){
          overallQual[1] = overallQual[1] + houses[i].saleprice;
          ctr2++;
        }

        else if(4 <= houses[i].overallqual && houses[i].overallqual < 6){
          overallQual[2] = overallQual[2] + houses[i].saleprice;
          ctr3++;
        }

        else if(6 <= houses[i].overallqual && houses[i].overallqual < 8){
          overallQual[3] = overallQual[3] + houses[i].saleprice;
          ctr4++;
        }

        else if(8 <= houses[i].overallqual && houses[i].overallqual <= 10){
          overallQual[4] = overallQual[4] + houses[i].saleprice;
          ctr5++;
        }
      }

      printf("Average Price of 0-2 Overall Quality Houses: %lf\n", (overallQual[0]/(double)(ctr1)));
      printf("Average Price of 2-4 Overall Quality Houses: %lf\n", (overallQual[1]/(double)(ctr2)));
      printf("Average Price of 4-6 Overall Quality Houses: %lf\n", (overallQual[2]/(double)(ctr3)));
      printf("Average Price of 6-8 Overall Quality Houses: %lf\n", (overallQual[3]/(double)(ctr4)));
      printf("Average Price of 8-10 Overall Quality Houses: %lf\n", (overallQual[4]/(double)(ctr5)));

    break;

    case 4:
    //At 2 intervals
      

      for (size_t i = 0; i < houseCount; i++){
        if (0 <= houses[i].overallcond && houses[i].overallcond < 2){
          overallcond[0] = overallcond[0] + houses[i].saleprice;
          ctr1_2++; 
        }

        else if(2 <= houses[i].overallcond && houses[i].overallcond < 4){
          overallcond[1] = overallcond[1] + houses[i].saleprice;
          ctr2_2++;
        }

        else if(4 <= houses[i].overallcond && houses[i].overallcond < 6){
          overallcond[2] = overallcond[2] + houses[i].saleprice;
          ctr3_2++;
        }

        else if(6 <= houses[i].overallcond && houses[i].overallcond < 8){
          overallcond[3] = overallcond[3] + houses[i].saleprice;
          ctr4_2++;
        }

        else if(8 <= houses[i].overallcond && houses[i].overallcond <= 10){
          overallcond[4] = overallcond[4] + houses[i].saleprice;
          ctr5_2++;
        }
      }

      printf("Average Price of 0-2 Overall Condition Houses: %lf\n", (overallcond[0]/(double)(ctr1_2)));
      printf("Average Price of 2-4 Overall Condition Houses: %lf\n", (overallcond[1]/(double)(ctr2_2)));
      printf("Average Price of 4-6 Overall Condition Houses: %lf\n", (overallcond[2]/(double)(ctr3_2)));
      printf("Average Price of 6-8 Overall Condition Houses: %lf\n", (overallcond[3]/(double)(ctr4_2)));
      printf("Average Price of 8-10 Overall Condition Houses: %lf\n", (overallcond[4]/(double)(ctr5_2)));

    break;

    case 5:
      

      for (size_t i = 0; i < houseCount; i++){
        if (houses[i].lotarea > (biggestLotArea-interval) && houses[i].lotarea < biggestLotArea){
          lotArea[0] += houses[i].lotarea;
          counters[0] += 1;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*2) && houses[i].lotarea < (biggestLotArea-interval)){
          lotArea[1] += houses[i].lotarea;
          counters[1] += 1;
        }
        
        if (houses[i].lotarea > (biggestLotArea-interval*3) && houses[i].lotarea < (biggestLotArea-interval*2)){
          lotArea[2] += houses[i].lotarea;
          counters[2] += 1;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*4) && houses[i].lotarea < (biggestLotArea*-interval*3)){
          lotArea[3] += houses[i].lotarea;
          counters[3] += 1;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*5) && houses[i].lotarea < (biggestLotArea-interval*4)){
          lotArea[4] += houses[i].lotarea;
          counters[4] += 1;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*6) && houses[i].lotarea < (biggestLotArea-interval*5)){
          lotArea[5] += houses[i].lotarea;
          counters[5] += 1;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*7) && houses[i].lotarea < (biggestLotArea-interval*6)){
          lotArea[6] += houses[i].lotarea;
          counters[6] += 1;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*8) && houses[i].lotarea < (biggestLotArea-interval*7)){
          lotArea[7] += houses[i].lotarea;
          counters[7] += 1;
        }
      }

      printf("Average price for the houses between [%d-%.2lf]: %.2lf\n", biggestLotArea, ((double)biggestLotArea-interval), (lotArea[0]/counters[0]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*1), ((double)biggestLotArea-interval*2), (lotArea[1]/counters[1]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*2), ((double)biggestLotArea-interval*3), (lotArea[2]/counters[2]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*3), ((double)biggestLotArea-interval*4), (lotArea[3]/counters[3]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*4), ((double)biggestLotArea-interval*5), (lotArea[4]/counters[4]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*5), ((double)biggestLotArea-interval*6), (lotArea[5]/counters[5]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*6), ((double)biggestLotArea-interval*7), (lotArea[6]/counters[6]));
      printf("Average price for the houses between [%.2lf-%.2lf]: %.2lf\n", ((double)biggestLotArea-interval*7), ((double)biggestLotArea-interval*8), (lotArea[7]/counters[7]));
    
    break;

    default:
      break;
  }

  return ;
}

void sort_houses(House* houses,char* criter_name){
  printf("Sort house by %s and save \n",criter_name);
  // TODO
  return ;
}

int find_smallest_lotarea(House* houses, int houseCount){
  int min = houses[0].lotarea;

  for (size_t i = 0; i < houseCount; i++){
    if(houses[i].lotarea <= min){
        min = houses[i].lotarea;
    }
  }
  
  return min;
}

int find_biggest_lotarea(House* houses, int houseCount){
  int max = houses[0].lotarea;

  for (size_t i = 0; i < houseCount; i++){
    if (houses[i].lotarea >= max){
      max = houses[i].lotarea;
    }
  }
    
  return max;
}
