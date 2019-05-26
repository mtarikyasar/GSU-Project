#include "dataset.h"
#include "quick_sort_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LINEMAXX 1024


int calculate_house_count(char* filename){
  char lineBuffer[LINEMAXX];
  char *field;
  int counter = 0;

  FILE *dataFile = fopen(filename, "r");
  if (dataFile == NULL) {
    printf("Failed to open file < %s >\n", filename);
    printf("(At dataset.c, line 15)\n");
    return 1;
  }

  fgets(lineBuffer, sizeof(lineBuffer), dataFile); //For first line

  while ((getc(dataFile) != EOF)) {
    fgets(lineBuffer, sizeof(lineBuffer), dataFile);
    counter++;
  }

  fclose(dataFile);

  return counter;
}

void read_house_testData(char* filename, House houses[]){
  printf("Reading file: %s\n",filename);  
  // TODO
  char lineBuffer[LINEMAXX];
  char lineRead[LINEMAXX];
  char *field; 
  int i;

  FILE *dataTestFile = fopen(filename, "r");
  if (dataTestFile == NULL) {
    printf("Failed to open file < %s >\n", filename);
    printf("(At dataset.c, line 42)\n");
    return;
  }

  fgets(lineBuffer, sizeof(lineBuffer), dataTestFile);
  
  i = 0;

  while (fgets(lineRead, sizeof(lineRead), dataTestFile)) {
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
    //Get saleprice
      houses[i].saleprice = 0;
      i++;
  }

  fclose(dataTestFile);
}

void read_house_data(char* filename, House houses[]){
  printf("Reading file: %s\n",filename);  
  // TODO
  char lineBuffer[LINEMAXX];
  char lineRead[LINEMAXX];
  char *field; 
  int i;

  FILE *dataFile = fopen(filename, "r");
  if (dataFile == NULL) {
    printf("Failed to open file < %s >\n", filename);
    printf("(At dataset.c, line 97)\n");
    return;
  }

  fgets(lineBuffer, sizeof(lineBuffer), dataFile);
  
  i = 0;

  while (fgets(lineRead, sizeof(lineRead), dataFile)) {
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
      houses[i].saleprice = atof(field);
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
  }

  fclose(dataFile);
}

void print_house(House *house, int houseCount){
  // TODO
  for (size_t i = 0; i < houseCount; i++) {
    printf("House information: \n");
    printf("\tID: %d\n", house[i].id);
    printf("\tLot area: %d\n", house[i].lotarea);
    printf("\tStreet: %s\n", house[i].street);
    printf("\tSale price: %.lf\n", house[i].saleprice);
    printf("\tNeighborhood: %s\n", house[i].neighborhood);
    printf("\tBuilt in: %d\n", house[i].yearbuilt);
    printf("\tOverall Quality: %d\n", house[i].overallqual);
    printf("\tOverall Condition: %d\n", house[i].overallcond);
    printf("\tKitchen Quality: %s\n", house[i].kitchenqual);
  }
}

void get_house_byid(House *house, int houseCount){
  int id = 0;
  printf("Get house with id: ");
  scanf("%d", &id);
  // TODO
    print_house_by_id(house, id);
}

void get_neighborhoods(House *houses, int houseCount){
  int id = 0;
  printf("\n\n");
  printf("Get neighborhoods of house with id\n");
  printf("Enter the house id of then neighborhood that you want to search: ");
  scanf("%d", &id);
  id -= 101;

  for (size_t i = 0; i < houseCount; i++) {
    if (!strcmp(houses[id].neighborhood, houses[i].neighborhood)) {
      print_house_by_id(houses, i+101);
    }
  }
}

void print_house_by_id(House *house, int id){
  id -= 101;
  printf("\n\n");
  printf("\tID: %d\n", house[id].id);
  printf("\tLot area: %d\n", house[id].lotarea);
  printf("\tStreet: %s\n", house[id].street);
  printf("\tSale price: %.lf\n", house[id].saleprice);
  printf("\tNeighborhood: %s\n", house[id].neighborhood);
  printf("\tBuilt in: %d\n", house[id].yearbuilt);
  printf("\tOverall Quality: %d\n", house[id].overallqual);
  printf("\tOverall Condition: %d\n", house[id].overallcond);
  printf("\tKitchen Quality: %s\n", house[id].kitchenqual);
}

void mean_sale_prices(House* houses, int houseCount){
  int yearAnswer;
  double price;
  int minY = 3000, maxY = 0;
  int criters = 0;
  // TODO
    printf("\n\nCalculate house prices by your criter choice.\n");
    printf("Your choices: \n");
    printf("[1]Neighborhoods\n");
    printf("[2]Kitchen Quality\n");
    printf("[3]Overall Quality\n");
    printf("[4]Overall Condition\n");
    printf("[5]Lot Area\n");
    printf("[6]Years\n");
    printf("Enter your choice: ");
    scanf("%d", &criters);

  //Initialisations
    //For neighbourhoods
      char** listN = malloc(sizeof(char *));
      int* ctrN = malloc(sizeof(int));
      double* pricesN = malloc(sizeof(double));
      int lim = 0;

      //Memory error checkif

      if (listN == NULL){
        printf("Failed to allocate memory for < listN > \n");
        printf("(At dataset.c, line 218)");
        return;
      }

      if (ctrN == NULL){
        printf("Failed to allocate memory for < ctrN > \n");
        printf("(At dataset.c, line 219)\n");
        return;
      }
      
      if (pricesN == NULL){
        printf("Failed to allocate memory for < pricesN > \n");
        printf("(At dataset.c, line 220)\n");
        return;
      }


    //For kitchenqual
      int kitQ[] = {0, 0, 0, 0, 0};
      double kitQua[] = {0, 0, 0, 0, 0};

    //For overallqual
      //Interval 2 for easy grouping
      int counterOQ[] = {0, 0, 0, 0, 0};
      double overallQual[] = {0, 0, 0, 0, 0};

    //For overallcond
      //Interval 2 for easy grouping
      int counterOC[] = {0, 0, 0, 0, 0};
      double overallcond[] = {0, 0, 0, 0, 0};

    //For lotarea
      int smallestLotArea = find_smallest_lotarea(houses, houseCount);
      int biggestLotArea = find_biggest_lotarea(houses, houseCount);
      double interval = (double)(biggestLotArea - smallestLotArea)/8; //We took 8 intervals
      int counters[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      double lotArea[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  //////////////////////

  switch (criters) {
    case 1:
      for (int i = 0, cur = 0; i < houseCount; i++) {
        while (cur < lim) {
          if (!strcmp(houses[i].neighborhood, listN[cur])) {
            pricesN[cur] += houses[i].saleprice;
            ctrN[cur]++;
            break;
          }
          else {
            cur++;
          }
        }
        if (cur == lim) {
          listN = realloc(listN, (lim + 1) * sizeof(char *));
          listN[lim] = malloc(10*sizeof(char));
          ctrN = realloc(ctrN, (lim + 1)*sizeof(int));
          pricesN = realloc(pricesN, (lim + 1)*sizeof(double));
          listN[lim] = strdup(houses[i].neighborhood);
          ctrN[lim] = 1;
          pricesN[lim] = houses[i].saleprice;
          lim++;
        }
        cur = 0;
      }

      printf("\nNeighborhoods:\tMean Prices:\n");
      for (int i = 0; i < lim; i++) {
        printf("%s\t%.2lf\n", listN[i], pricesN[i] / ctrN[i]);
      }
      printf("\n");

      free(listN); listN = NULL;
      free(ctrN); ctrN = NULL;
      free(pricesN); pricesN = NULL;
      break;
    
    case 2:

      for (size_t i = 0; i < houseCount; i++){
        if (strncmp("Ex", houses[i].kitchenqual, 1) == 0) {
          kitQua[0] = kitQua[0] + (double)houses[i].saleprice;
          kitQ[0]++; 
        }

        else if(strncmp("Gd", houses[i].kitchenqual, 1) == 0) {
          kitQua[1] = kitQua[1] + (double)houses[i].saleprice;
          kitQ[1]++;
        }

        else if(strncmp("TA", houses[i].kitchenqual, 1) == 0) {
          kitQua[2] = kitQua[2] + (double)houses[i].saleprice;
          kitQ[2]++;
        }

        else if(strncmp("Fa", houses[i].kitchenqual, 1) == 0) {
          kitQua[3] = kitQua[3] + (double)houses[i].saleprice;
          kitQ[3]++;
        }

        else if(strncmp("Po", houses[i].kitchenqual, 1) == 0) {
          kitQua[4] = kitQua[4] + (double)houses[i].saleprice;
          kitQ[4]++;
        }
      }

    //Sonucun nan cikmamasi icin kontrol
      for (size_t i = 0; i < 5; i++) {
        if (kitQ[i] == 0){
          kitQ[i] = 1;
        } 
      }
      
      printf("\n\nAverage Excellent Quality Kitchens:\t\t %6.0lf $\n", (kitQua[0]/(double)(kitQ[0])));
      printf("Average Good Quality Kitchens:\t\t\t %6.0lf $\n", (kitQua[1]/(double)(kitQ[1])));
      printf("Average Typical/Average Quality Kitchens:\t %6.0lf $\n", (kitQua[2]/(double)(kitQ[2])));
      printf("Average Fair Quality Kitchens:\t\t\t %6.0lf $\n", (kitQua[3]/(double)(kitQ[3])));
      printf("Average Poor Quality Kitchens:\t\t\t %6.0lf $\n\n\n", (kitQua[4]/(double)(kitQ[4])));

      break;

    case 3:

      for (size_t i = 0; i < houseCount; i++){
        if (0 <= houses[i].overallqual && houses[i].overallqual < 2) {
          overallQual[0] = overallQual[0] + houses[i].saleprice;
          counterOQ[0]++; 
        }

        else if(2 <= houses[i].overallqual && houses[i].overallqual < 4) {
          overallQual[1] = overallQual[1] + houses[i].saleprice;
          counterOQ[1]++;
        }

        else if(4 <= houses[i].overallqual && houses[i].overallqual < 6) {
          overallQual[2] = overallQual[2] + houses[i].saleprice;
          counterOQ[2]++;
        }

        else if(6 <= houses[i].overallqual && houses[i].overallqual < 8) {
          overallQual[3] = overallQual[3] + houses[i].saleprice;
          counterOQ[3]++;
        }

        else if(8 <= houses[i].overallqual && houses[i].overallqual <= 10) {
          overallQual[4] = overallQual[4] + houses[i].saleprice;
          counterOQ[4]++;
        }
      }

    //Sonucun nan cikmamasi icin kontrol
      for (size_t i = 0; i < 5; i++) {
        if (counterOQ[i] == 0){
          counterOQ[i] = 1;
        } 
      }

      printf("\n\nAverage Price of 0-2 Overall Quality Houses:\t%6.0lf $\n", (overallQual[0]/(double)(counterOQ[0])));
      printf("Average Price of 2-4 Overall Quality Houses:\t%6.0lf $\n", (overallQual[1]/(double)(counterOQ[1])));
      printf("Average Price of 4-6 Overall Quality Houses:\t%6.0lf $\n", (overallQual[2]/(double)(counterOQ[2])));
      printf("Average Price of 6-8 Overall Quality Houses:\t%6.0lf $\n", (overallQual[3]/(double)(counterOQ[3])));
      printf("Average Price of 8-10 Overall Quality Houses:\t%6.0lf $\n\n\n", (overallQual[4]/(double)(counterOQ[4])));

    break;

    case 4:
    //At 2 intervals

      for (size_t i = 0; i < houseCount; i++) {
        if (0 <= houses[i].overallcond && houses[i].overallcond < 2) {
          overallcond[0] = overallcond[0] + houses[i].saleprice;
          counterOC[0]++; 
        }

        else if(2 <= houses[i].overallcond && houses[i].overallcond < 4) {
          overallcond[1] = overallcond[1] + houses[i].saleprice;
          counterOC[1]++;
        }

        else if(4 <= houses[i].overallcond && houses[i].overallcond < 6) {
          overallcond[2] = overallcond[2] + houses[i].saleprice;
          counterOC[2]++;
        }

        else if(6 <= houses[i].overallcond && houses[i].overallcond < 8) {
          overallcond[3] = overallcond[3] + houses[i].saleprice;
          counterOC[3]++;
        }

        else if(8 <= houses[i].overallcond && houses[i].overallcond <= 10) {
          overallcond[4] = overallcond[4] + houses[i].saleprice;
          counterOC[4]++;
        }
      }

    //Sonucun nan cikmamasi icin kontrol
      for (size_t i = 0; i < 5; i++) {
        if (counterOC[i] == 0) {
          counterOC[i] = 1;
        } 
      }

      printf("\n\nAverage Price of 0-2 Overall Condition Houses:\t%6.0lf $\n", (overallcond[0]/(double)(counterOC[0])));
      printf("Average Price of 2-4 Overall Condition Houses:\t%6.0lf $\n", (overallcond[1]/(double)(counterOC[1])));
      printf("Average Price of 4-6 Overall Condition Houses:\t%6.0lf $\n", (overallcond[2]/(double)(counterOC[2])));
      printf("Average Price of 6-8 Overall Condition Houses:\t%6.0lf $\n", (overallcond[3]/(double)(counterOC[3])));
      printf("Average Price of 8-10 Overall Condition Houses:\t%6.0lf $\n\n\n", (overallcond[4]/(double)(counterOC[4])));

    break;

    case 5:
      
      for (size_t i = 0; i < houseCount; i++){
        if (houses[i].lotarea > (biggestLotArea-interval) && houses[i].lotarea <= biggestLotArea) {
          lotArea[0] += houses[i].lotarea;
          counters[0]++;
        }

        else if (houses[i].lotarea > (biggestLotArea-interval*2) && houses[i].lotarea <= (biggestLotArea-interval)) {
          lotArea[1] += houses[i].lotarea;
          counters[1]++;
        }
        
        else if (houses[i].lotarea > (biggestLotArea-interval*3) && houses[i].lotarea <= (biggestLotArea-interval*2)) {
          lotArea[2] += houses[i].lotarea;
          counters[2]++;
        }

        else if (houses[i].lotarea > (biggestLotArea-interval*4) && houses[i].lotarea <= (biggestLotArea*-interval*3)) {
          lotArea[3] += houses[i].lotarea;
          counters[3]++;
        }

        else if (houses[i].lotarea > (biggestLotArea-interval*5) && houses[i].lotarea <= (biggestLotArea-interval*4)) {
          lotArea[4] += houses[i].lotarea;
          counters[4]++;
        }

        else if (houses[i].lotarea > (biggestLotArea-interval*6) && houses[i].lotarea <= (biggestLotArea-interval*5)) {
          lotArea[5] += houses[i].lotarea;
          counters[5]++;
        }

        else if (houses[i].lotarea > (biggestLotArea-interval*7) && houses[i].lotarea <= (biggestLotArea-interval*6)) {
          lotArea[6] += houses[i].lotarea;
          counters[6]++;
        }

        else if (houses[i].lotarea >= (biggestLotArea-interval*8) && houses[i].lotarea <= (biggestLotArea-interval*7)) {
          lotArea[7] += houses[i].lotarea;
          counters[7]++;
        }
      }

    //Sonucun nan cikmamasi icin kontrol
      for (size_t i = 0; i < 8; i++) {
        if (counters[i] == 0) {
          counters[i] = 1;
        }
      }
      
      printf("\n\nAverage price for the houses of lotarea between [%d-%.0lf]:\t%6.0lf $\n", biggestLotArea, ((double)biggestLotArea-interval), (lotArea[0]/counters[0]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t%6.0lf $\n", ((double)biggestLotArea-interval*1), ((double)biggestLotArea-interval*2), (lotArea[1]/counters[1]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t%6.0lf $\n", ((double)biggestLotArea-interval*2), ((double)biggestLotArea-interval*3), (lotArea[2]/counters[2]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t%6.0lf $\n", ((double)biggestLotArea-interval*3), ((double)biggestLotArea-interval*4), (lotArea[3]/counters[3]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t\t%6.0lf $\n", ((double)biggestLotArea-interval*4), ((double)biggestLotArea-interval*5), (lotArea[4]/counters[4]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t\t%6.0lf $\n", ((double)biggestLotArea-interval*5), ((double)biggestLotArea-interval*6), (lotArea[5]/counters[5]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t\t%6.0lf $\n", ((double)biggestLotArea-interval*6), ((double)biggestLotArea-interval*7), (lotArea[6]/counters[6]));
      printf("Average price for the houses of lotarea between [%.0lf-%.0lf]:\t\t%6.0lf $\n\n\n", ((double)biggestLotArea-interval*7), ((double)biggestLotArea-interval*8), (lotArea[7]/counters[7]));
    
    break;

    case 6:
      for (int i = 0; i < houseCount; i++) {
        if (houses[i].yearbuilt < minY) {
          minY = houses[i].yearbuilt;
        }
        if (houses[i].yearbuilt > maxY) {
          maxY = houses[i].yearbuilt;
        }
      }

      int yearSize = maxY - minY + 1;
      hYear *yearTable = malloc(yearSize*sizeof(hYear));
      if (yearTable == NULL) {
        printf("Failed to allocate memory for < yearTable >\n");
        printf("(At dataset.c, line 510)\n");
      }
      for (int i = 0; i < yearSize; i++) {
        yearTable[i].year = minY + i;
        yearTable[i].counter = 0;
        yearTable[i].price = 0;
      }

      quick_sort_type(houses, houseCount, YEAR);

      for (int i = 0, j = 0; i < yearSize; i++) {
        yearTable[i].mean_price = 0;
        while ((yearTable[i].year == houses[j].yearbuilt) && (j < houseCount)) {
          yearTable[i].mean_price += houses[j].saleprice;
          yearTable[i].counter++; 
          j++;
        }
        yearTable[i].mean_price /= yearTable[i].counter;
      }

      printf("\nEnter a year to find the mean price (%d - %d): ", minY, maxY);
      scanf("%d", &yearAnswer);
      yearAnswer = yearSize - (maxY - yearAnswer) - 1;
      if (yearTable[yearAnswer].counter != 0) {
        printf("There are %d houses built in %d\n", yearTable[yearAnswer].counter, yearTable[yearAnswer].year);
        printf("Mean price is %.2lf\n\n", yearTable[yearAnswer].mean_price);
      }
      else {
        printf("There are no houses built in that year\n\n");
      }

      free(yearTable); yearTable = NULL;
      break;

    default:
      break;
  }

  return ;
}

void sort_houses(House* houses, int houseCount, int criter) {
  printf("Sorting houses...\n");
  quick_sort_type(houses, houseCount, criter);
  for (int i = 0, j = houseCount - 1; i < houseCount/2; i++, j--) {
    swapper(&houses[i], &houses[j]);
  } 
  return ;
}

int find_smallest_lotarea(House* houses, int houseCount){
  int min = houses[0].lotarea;

  for (size_t i = 0; i < houseCount; i++) {
    if(houses[i].lotarea <= min){
      min = houses[i].lotarea;
    }
  }
  
  return min;
}

int find_biggest_lotarea(House* houses, int houseCount){
  int max = houses[0].lotarea;

  for (size_t i = 0; i < houseCount; i++) {
    if (houses[i].lotarea >= max){
      max = houses[i].lotarea;
    }
  }
    
  return max;
}

void print_topN(House* houses, int houseCount, int N) {
  int id;
  quick_sort_type(houses, houseCount, PRICE);
  for (int i = 1; i < N + 1; i++) {
    id = houseCount - i + 101;
    print_house_by_id(houses, id);
  }
}

