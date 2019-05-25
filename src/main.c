#include"dataset.h"
#include"models.h"
#include"quick_sort_table.h"

int main(int argc,char * argv[]){
  int cevap = 1;
  int answrID = 0;
  int topN = 0;
  int criter;

  //TODO: Read database, read_house_data();

  int houseCount = calculate_house_count("data_train.csv");
  int houseCountTest = calculate_house_count("data_test.csv");

  House *houses = malloc(houseCount*sizeof(struct house));
  House *housesTest = malloc(houseCountTest*sizeof(struct house));

  read_house_data("data_train.csv", houses);
  read_house_testData("data_test.csv", housesTest);


  double priceSim = 0;

  double** matRes;

  while(cevap != 0){
    printf("Emlak Programina Hos geldiniz!\n");
    printf("Yapmak istediginiz islemi seciniz\n");
    printf("1 - Evleri listele\n");
    printf("2 - ID degeri verilen evi goster\n");
    printf("3 - ID degeri verilen evin komsu evlerini bul \n");
    printf("4 - Semtlere gore satis fiyati ortalamalarini goster\n");
    printf("5 - En yuksek fiyata sahip ilk N evi goster\n");
    printf("6 - Sirali ev listesini kaydet\n");
    printf("7 - Fiyat tahmini yap\n");
    printf("Programdan cikmak icin 0 a basiniz.\n");
    scanf("%d",&cevap);
    
    switch (cevap) {
      case 1: {
        print_house(houses, houseCount);
        break;
      }

      case 2: {
        get_house_byid(houses, houseCount);
        break;
      }

      case 3: {
        get_neighborhoods(houses, houseCount);
        break;
      }

      case 4: {
        mean_sale_prices(houses, houseCount);
        break;
      }

      case 5: {
        //sort_houses();
        //TODO: Top N house
        printf("Please enter N for the information of top N houses: ");
        scanf("%d", &topN);
        printf("\n");
        print_topN(houses, houseCount, topN);
        break;
      }

      case 6: {
        //TODO: Create file, save the list
        
        printf("Please select a criter for sorting the house list:\n");
        printf("Your choices: \n");
        printf("[0]Return to the main menu\n");
        printf("[1]Sale Prices\n");
        printf("[2]Years\n");
        printf("[3]Lot Area\n");
        printf("[4]Overall Condition\n");
        printf("[5]Overall Quality\n");
        printf("Enter your choice: ");
        scanf("%d", &criter);

        switch (criter) {
        case 0:
          printf("\n");
          break;

        case 1:
          sort_houses(houses, houseCount, PRICE);
          break;
        
        case 2:
          sort_houses(houses, houseCount, YEAR);
          break;
        
        case 3:
          sort_houses(houses, houseCount, AREA);
          break;

        case 4:
          sort_houses(houses, houseCount, CONDITION);
          break;

        case 5:
          sort_houses(houses, houseCount, QUALITY);
          break;
        
        default:
          printf("Please enter an acceptable value\n");
          printf("\n");
          break;
        }
        
        FILE* flist = fopen("sorted_list.txt", "w");
        if (flist == NULL) {
          printf("Failed to save sorted list in file...\n");
          break;
        }

        fprintf(flist, "ID\tLotArea\tStreet\tSalePrice\tNeighborhood\tYearBuilt\tOverallQuality\tOverallCondition\tKitchenQuality\n");      
        for (int i = 0; i < houseCount; i++) {
          fprintf(flist, "%d\t%d\t%s\t%.lf\t%s\t%d\t%d\t%d\t%s\n", 
          houses[i].id, houses[i].lotarea, houses[i].street, 
          houses[i].saleprice, houses[i].neighborhood, houses[i].yearbuilt,
          houses[i].overallqual, houses[i].overallcond, houses[i].kitchenqual);
        }

        fclose(flist);
        printf("\n");
        break;
      }
                
      case 7: {
        //TODO: Price guess
        //priceSim = model_by_similarity(houses, houses[456], houseCount);
        //printf("Similarity: %.2lf\n", priceSim);

        FILE* fsim = fopen("prices_by_similarity.txt", "w");
        fprintf(fsim, "ID: \t Price:\n");
        for (int i = 0; i < houseCountTest; i++) {
          housesTest[i].saleprice = model_by_similarity(houses, housesTest[i], houseCount);
          fprintf(fsim, "%d \t %.2lf\n", housesTest[i].id, housesTest[i].saleprice);
        }
        fclose(fsim);

        //w = calculate_parameter(x, y);
        //matRes = make_prediction("data_train.csv", houseCount);
        break;
      }
      
      default: {
        printf("Please enter an acceptable value\n");
        break;
      }
        
    }
  }
}
