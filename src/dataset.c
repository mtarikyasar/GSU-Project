#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "quick_sort_table.h"
#define LINEMAXX 1024

int calculate_house_count(char* filename){
  char lineBuffer[LINEMAXX];
  char *field;
  int counter = 0;

  FILE *dataFile = fopen(filename, "r");

  fgets(lineBuffer, sizeof(lineBuffer), dataFile); //For first line


  while((getc(dataFile) != EOF)){
    fgets(lineBuffer, sizeof(lineBuffer), dataFile);
    counter++;
  }

  fclose(dataFile);

  return counter;
}

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
  int j = 101;

  while ((getc(dataFile)) != EOF){
    fgets(lineRead, sizeof(lineRead), dataFile);
    
      //Get ID
          //ID'ler her 100 degerde bir basa donuyor
          //O yuzden mecburen boyle bir cozum yolu izledik
        field = strtok(lineRead, ",");

        if (i == 0){
          j = atoi(field);
        }
        
        houses[i].id = j; 
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
      j++;
      houseCount = i;
  }

  return houseCount;
}

void print_house(House *house, int houseCount){
  // TODO
  for (size_t i = 0; i < houseCount; i++)
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
  }
}

House *get_house_byid(House *house, int houseCount){
  int id = 0;
  printf("Get house with id: ");
  scanf("%d", &id);
  // TODO
    print_house_by_id(house, id-1); //house dizisinin index'i id'den 1 deger kucuk oldugu icin id-1 yazdik
}

void get_neighborhoods(House *houses, int houseCount){
  int j = 0;
  int id = 0;

  printf("\n\n");
  printf("Get neighborhoods of house with id\n");
  printf("Enter the house id of then neighborhood that you want to search: ");
  scanf("%d", &id);
  // TODO
    for (size_t i = 0; i < houseCount; i++){
      if (strcmp(houses[id-1].neighborhood, houses[i].neighborhood) == 0){
          print_house_by_id(houses, i);
      }
    }
}

void print_house_by_id(House *house, int id){
    printf("\n\n");
    printf("\tID: %d\n", house[id].id);
    printf("\tLot area: %d\n", house[id].lotarea);
    printf("\tStreet: %s\n", house[id].street);
    printf("\tSale price: %d\n", house[id].saleprice);
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
          //strcpy(listN[lim - 1], houses[i].neighborhood);
          listN[lim] = strdup(houses[i].neighborhood);
          ctrN[lim] = 1;
          pricesN[lim] = houses[i].saleprice;
          lim++;
        }
        cur = 0;
      }

      printf("Neighbourhoods:\tMean Prices:\n");
      for (int i = 0; i < lim; i++) {
        printf("%s\t%.2lf\n", listN[i], pricesN[i] / ctrN[i]);
      }
      
      free(listN);
      free(ctrN);
      free(pricesN);
      break;
    
    case 2:

      for (size_t i = 0; i < houseCount; i++){
        if (strncmp("Ex", houses[i].kitchenqual, 1) == 0){
          kitQua[0] = kitQua[0] + (double)houses[i].saleprice;
          kitQ[0]++; 
        }

        else if(strncmp("Gd", houses[i].kitchenqual, 1) == 0){
          kitQua[1] = kitQua[1] + (double)houses[i].saleprice;
          kitQ[1]++;
        }

        else if(strncmp("TA", houses[i].kitchenqual, 1) == 0){
          kitQua[2] = kitQua[2] + (double)houses[i].saleprice;
          kitQ[2]++;
        }

        else if(strncmp("Fa", houses[i].kitchenqual, 1) == 0){
          kitQua[3] = kitQua[3] + (double)houses[i].saleprice;
          kitQ[3]++;
        }

        else if(strncmp("Po", houses[i].kitchenqual, 1) == 0){
          kitQua[4] = kitQua[4] + (double)houses[i].saleprice;
          kitQ[4]++;
        }
      }

    //Sonucun nan cikmamasi icin kontrol

      for (size_t i = 0; i < 5; i++){
        if (kitQ[i] == 0){
          kitQ[i] = 1;
        } 
      }
      
      printf("\n\nAverage Excellent Quality Kitchens:\t %6.0lf $\n", (kitQua[0]/(double)(kitQ[0])));
      printf("Average Good Quality Kitchens:\t\t %6.0lf $\n", (kitQua[1]/(double)(kitQ[1])));
      printf("Average Typical/Average Quality Kitchens:%6.0lf $\n", (kitQua[2]/(double)(kitQ[2])));
      printf("Average Fair Quality Kitchens:\t\t %6.0lf $\n", (kitQua[3]/(double)(kitQ[3])));
      printf("Average Poor Quality Kitchens:\t\t %6.0lf $\n\n\n", (kitQua[4]/(double)(kitQ[4])));

      break;

    case 3:

      for (size_t i = 0; i < houseCount; i++){
        if (0 <= houses[i].overallqual && houses[i].overallqual < 2){
          overallQual[0] = overallQual[0] + houses[i].saleprice;
          counterOQ[0]++; 
        }

        else if(2 <= houses[i].overallqual && houses[i].overallqual < 4){
          overallQual[1] = overallQual[1] + houses[i].saleprice;
          counterOQ[1]++;
        }

        else if(4 <= houses[i].overallqual && houses[i].overallqual < 6){
          overallQual[2] = overallQual[2] + houses[i].saleprice;
          counterOQ[2]++;
        }

        else if(6 <= houses[i].overallqual && houses[i].overallqual < 8){
          overallQual[3] = overallQual[3] + houses[i].saleprice;
          counterOQ[3]++;
        }

        else if(8 <= houses[i].overallqual && houses[i].overallqual <= 10){
          overallQual[4] = overallQual[4] + houses[i].saleprice;
          counterOQ[4]++;
        }
      }

      for (size_t i = 0; i < 5; i++){
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
      

      for (size_t i = 0; i < houseCount; i++){
        if (0 <= houses[i].overallcond && houses[i].overallcond < 2){
          overallcond[0] = overallcond[0] + houses[i].saleprice;
          counterOC[0]++; 
        }

        else if(2 <= houses[i].overallcond && houses[i].overallcond < 4){
          overallcond[1] = overallcond[1] + houses[i].saleprice;
          counterOC[1]++;
        }

        else if(4 <= houses[i].overallcond && houses[i].overallcond < 6){
          overallcond[2] = overallcond[2] + houses[i].saleprice;
          counterOC[2]++;
        }

        else if(6 <= houses[i].overallcond && houses[i].overallcond < 8){
          overallcond[3] = overallcond[3] + houses[i].saleprice;
          counterOC[3]++;
        }

        else if(8 <= houses[i].overallcond && houses[i].overallcond <= 10){
          overallcond[4] = overallcond[4] + houses[i].saleprice;
          counterOC[4]++;
        }
      }

      for (size_t i = 0; i < 5; i++){
        if (counterOC[i] == 0){
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
        if (houses[i].lotarea > (biggestLotArea-interval) && houses[i].lotarea <= biggestLotArea){
          lotArea[0] += houses[i].lotarea;
          counters[0]++;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*2) && houses[i].lotarea <= (biggestLotArea-interval)){
          lotArea[1] += houses[i].lotarea;
          counters[1]++;
        }
        
        if (houses[i].lotarea > (biggestLotArea-interval*3) && houses[i].lotarea <= (biggestLotArea-interval*2)){
          lotArea[2] += houses[i].lotarea;
          counters[2]++;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*4) && houses[i].lotarea <= (biggestLotArea*-interval*3)){
          lotArea[3] += houses[i].lotarea;
          counters[3]++;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*5) && houses[i].lotarea <= (biggestLotArea-interval*4)){
          lotArea[4] += houses[i].lotarea;
          counters[4]++;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*6) && houses[i].lotarea <= (biggestLotArea-interval*5)){
          lotArea[5] += houses[i].lotarea;
          counters[5]++;
        }

        if (houses[i].lotarea > (biggestLotArea-interval*7) && houses[i].lotarea <= (biggestLotArea-interval*6)){
          lotArea[6] += houses[i].lotarea;
          counters[6]++;
        }

        if (houses[i].lotarea >= (biggestLotArea-interval*8) && houses[i].lotarea <= (biggestLotArea-interval*7)){
          lotArea[7] += houses[i].lotarea;
          counters[7]++;
        }
      }

      for (size_t i = 0; i < 8; i++)
      {
        if (counters[i] == 0)
        {
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

      for (int i = 0; i < yearSize; i++) {
        yearTable[i].year = minY + i;
        yearTable[i].counter = 0;
        yearTable[i].price = 0;
      }

      quick_sort_houses(houses, houseCount);

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
      printf("There are %d houses built in %d\n", yearTable[yearAnswer].counter, yearTable[yearAnswer].year);
      printf("Mean price is %.2lf\n\n", yearTable[yearAnswer].mean_price);
    
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
