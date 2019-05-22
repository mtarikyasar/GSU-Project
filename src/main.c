#include"dataset.h"
#include"models.h"

int main(int argc,char * argv[]){
  int cevap = 1;
  
  //TODO: Read database, read_house_data();

  int houseCount = calculate_house_count("data_train.csv");
  House *houses = malloc(houseCount*sizeof(struct house));

  read_house_data("data_train.csv", houses);

  int priceSim = 0;

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
    printf("5 - En yuksek fiyata sahip ilk 10 evi goster\n");
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
        //TODO: Top 10 house
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
        priceSim = model_by_similarity(houses, houses[0]);
        create_data_matrices(houses, x, y);
        w = calculate_parameter(x, y);
        make_prediction("fsonuc", w, houseCount);

        printf("Similarity: %.2lf\n", priceSim);
        break;
      }
      
      default: {
        printf("Please enter an acceptable value\n");
        break;
      }
        
    }
  }
}
