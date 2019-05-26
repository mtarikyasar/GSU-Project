#include"dataset.h"
#include"models.h"
#include"quick_sort_table.h"

int main(int argc,char * argv[]){
  if (argc != 3) {
    printf("Usage: ./main [file to read] [file to calculate the prices]\n");
    printf("Exiting program...\n");
    return 0;
  }

  int cevap = 1;
  int topN = 0;
  int criter;
  double** w;

  int houseCount = calculate_house_count(argv[1]);
  int houseCountTest = calculate_house_count(argv[2]);

  House *houses = malloc(houseCount*sizeof(struct house));
  if (houses == NULL) {
    printf("Failed to allocate memory for struct array < houses >\n");
    printf("(At main.c, line 20)\n");
  }

  House *housesSave = malloc(houseCount*sizeof(struct house));
  if (housesSave == NULL) {
    printf("Failed to allocate memory for struct array < housesSave >\n");
    printf("(At main.c, line 26)\n");
  }

  House *housesTest = malloc(houseCountTest*sizeof(struct house));
  if (houses == NULL) {
    printf("Failed to allocate memory for struct array < housesTest >\n");
    printf("(At main.c, line 32)\n");
  }

  read_house_data("data_train.csv", houses);
  read_house_testData("data_test.csv", housesTest);
  printf("\n");

  for (int i = 0; i < houseCount; i++) {
    housesSave[i] = houses[i];
  }

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
    printf("Cevabiniz: ");
    scanf("%d",&cevap);
    
    switch (cevap) {
      case 0: 
        printf("Exiting program...\n");
        break;
    
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
        
        printf("\nPlease select a criter for sorting the house list:\n");
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
          printf("Failed to create file < sorted_list >\n");
          printf("(At main.c, line 139)\n");
          break;
        }

        fprintf(flist, " ID\t\tLotArea\t\tStreet\tSalePrice\tNeighborhood\tYearBuilt\tOverallQuality\tOverallCondition\tKitchenQuality\n");      
        for (int i = 0; i < houseCount; i++) {
          fprintf(flist, "%4d\t%4d\t\t%s\t%2.0lf\t\t%s\t\t  %8d\t\t%8d\t\t%9d\t\t\t\t  %s\n", 
          houses[i].id, houses[i].lotarea, houses[i].street, 
          houses[i].saleprice, houses[i].neighborhood, houses[i].yearbuilt,
          houses[i].overallqual, houses[i].overallcond, houses[i].kitchenqual);
        }
        fclose(flist);
        
        printf("Sorted list successfully saved to sorted_list.txt file\n\n");
        break;
      }
                
      case 7: {
        FILE* fsim = fopen("prices_by_similarity.txt", "w");
        if (fsim == NULL) {
          printf("Failed to create file < prices_by_similarity >\n");
          printf("(At main.c, line 160)\n");
          break;
        }

        fprintf(fsim, "ID: \t Price:\n");
        printf("Karsilastirma yontemiyle fiyat tahmini yapiliyor...\n");
        for (int i = 0; i < houseCountTest; i++) {
          housesTest[i].saleprice = model_by_similarity(houses, housesTest[i], houseCount);
          fprintf(fsim, "%d \t %.2lf\n", housesTest[i].id, housesTest[i].saleprice);
        }
        fclose(fsim);
        printf("Islem tamamlandi! Fiyat tahminleri prices_by_similarity.txt dosyasina kaydedildi.\n\n");
        
        double** X = malloc(houseCount * sizeof(double*));
        double* y = malloc(houseCount * sizeof(double));
        for (int i = 0; i < houseCount; i++) {
          X[i] = malloc(2 * sizeof(double));
        }
        if ((X == NULL) || (y == NULL)) {
          printf("Failed to allocate memory for matrices < X > and < y >\n");
          printf("(At main.c, line 176)\n");
          break;
        }        

        create_data_matrices(houses, X, y, houseCount);
        w = calculate_parameter(X, y, houseCount);
        make_prediction("data_test.csv", w, houseCountTest);
        
        for (int i = 0; i < houseCount; i++) {
          free(X[i]);
        }
        free(X); free(y);
        y = NULL; X = NULL;

        break;
      }
      
      default: {
        printf("Please enter an acceptable value\n\n");
        break;
      }
        
    }
    for (int i = 0; i < houseCount; i++) {
      houses[i] = housesSave[i];
    }
  }

  return 0;
}
