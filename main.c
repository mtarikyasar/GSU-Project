#include"dataset.h"
#include"models.h"

int main(int argc,char * argv[]){
  int cevap = 1;
  int answrID = 0;
  
  //TODO: Read database, read_house_data();

  int houseCountTrain = calculate_house_count("data_train.csv");
  int houseCountTest = calculate_house_count("data_test.csv");

  House *houses = malloc(houseCountTrain*sizeof(struct house));
  House *housesTest = malloc(houseCountTest*sizeof(struct house));

  read_house_data("data_train.csv", houses);
  //read_house_data("data_test.csv", housesTest);

  double priceSim = 0;

  double** x;
  double* y;
  double** w;

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
        print_house(houses, houseCountTrain);
        break;
      }

      case 2: {
        get_house_byid(houses, houseCountTrain);
        break;
      }

      case 3: {
        get_neighborhoods(houses, houseCountTrain);
        break;
      }

      case 4: {
        mean_sale_prices(houses, houseCountTrain);
        break;
      }

      case 5: {
        //sort_houses();
        //TODO: Top N house
        print_topN(houses, houseCountTrain, 3);
        break;
      }

      case 6: {
        /*sort_houses();
        //TODO: Create file, save the list
        //Tarik'a NOT: switch - case icerisinde degisken yaratmak
        //sikinti cikarabilir, calismas ise hallederiz sonra.
        FILE *flist;
        flist = fopen("sorted_list.txt", "w+"); */
        
          break;
        }
                
      case 7: {
        //TODO: Price guess
        priceSim = model_by_similarity(houses, houses[456], houseCountTrain);
        printf("Real price: %.2lf\n", houses[456].saleprice);
        printf("Similarity: %.2lf\n", priceSim);

        /*
        FILE* fsim = fopen("prices_by_similarity.txt", "w");
        fprintf(fsim, "ID: \t Price:\n");
        for (int i = 0; i < houseCountTest; i++) {
          housesTest[i].saleprice = model_by_similarity(houses, housesTest[i], houseCountTrain);
          fprintf(fsim, "%d \t %.2lf\n", housesTest[i].id, housesTest[i].saleprice);
        }
        */

        create_data_matrices(houses, x, y);
        w = calculate_parameter(x, y);
        make_prediction("fsonuc", w, houseCountTrain);

        break;
      }
      
      default: {
        printf("Please enter an acceptable value\n");
        break;
      }
        
    }
  }
}
