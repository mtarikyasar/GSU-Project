#include"dataset.h"
#include"models.h"

int main(int argc,char * argv[]){
  int cevap;
  
  //TODO: Read database, read_house_data();

  while(cevap!=0){
    printf("Emlak Programina Hosgeldiniz!\n");
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
        print_house();
        break;
      }
      case 2: {
        get_house_byid();
        break;
      }
      case 3: {
        get_neighborhoods();
        break;
      }
      case 4: {
        mean_sale_prices();
        break;
      }
      case 5: {
        sort_houses();
        //TODO: Top 10 house
        break;
      }
      case 6: {
        sort_houses();
        //TODO: Create file, save the list
        //Tarik'a NOT: switch - case icerisinde degisken yaratmak
        //sikinti cikarabilir, calismas ise hallederiz sonra.
        FILE flist;
        flist = fopen("sorted_list.txt", "w+);
        if (flist == NULL) {
          printf("Failed creating file...\n);
          break;
        }
                
                 
                      
        break;
      }
      case 7: {
        //TODO: Price guess
        break;
      }
      default: {
        pritf("Please enter an acceptable value\n");
        break;
      }
        
    }
        
    /*
    if (cevap==1){
      printf("Ev listesi \n");
      // TODO
      // Butun evleri listele
      print_house
     }
    else if (cevap==2){
      printf("ID degeri verilen ev \n");
      // TODO
      // print_house ile tek evi goster
      // get_house_byid cagrisi yap
     }
     else if (cevap==3){
      printf("Komsu evler \n");
      // TODO
      // get_neighborhoods 
     }
     else if(cevap==4){
       printf("Ortalama satislar\n");
       // TODO
       // mean_sale_prices
     }
     else if (cevap==5){
       printf("En yuksek fiyatli evler\n");
       // TODO 
     }
     else if (cevap==6){
       printf("Sirali evler\n");
       // TODO 
     }
     else if(cevap==7){
       printf("Fiyat tahmini yap\n");
       // TODO
     }
    printf("Programdan cikiliyor\n");
    */
  }

  return 0; 
}
