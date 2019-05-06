#include "models.h"
#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_lotArea(const void *a, const void *b) {
  House *h1 = (House *) a;
  House *h2 = (House *) b;
  return h1->lotarea - h2->lotarea;
}

int compare_yearBuilt(const void *a, const void *b) {
  House *h1 = (House *) a;
  House *h2 = (House *) b;
  return h1->yearbuilt - h2->yearbuilt;
}

void quick_sort_libc(int *array, int size, int compareType) {
  qsort(array, size, sizeof(int), compareType);
}

/*
int model_by_similarity(House* houses,House new_house){
  //printf("Find price for house %d\n",new_house.id);
  int price;
  //TODO

  int sizeArr;  //BURAYI DUZELT

  // 1 - Oncelikle ayni komsuluktaki evleri bulun
  House *housesNeigh = malloc(sizeof(House));

  int ctr_hN = 0;
  int j = 0;
  int k = 0;

  for (int i = 0; i < sizeArr; i++) {
    if (!cmpstr(new_house.neighborhood, houses[i].neighborhood)) {
      ctr_hN++;
      realloc(housesNeigh, ctr_hN*sizeof(House));
      housesNeigh[ctr_hN-1] = houses[i];
    }
  }


  
  // 2 - Bu evleri lotArea ya gore siralayin
  quick_sort_libc(housesNeigh, ctr_hN, compare_lotArea);
  
  // 3 - new_house degiskenin lotarea parametresine en
  //  yakin evleri alin, bu evlerin alanlari 
  //  (new_house.lotarea+2000) ve (new_house.lotarea-2000) metrekare arasinda
  //   olabilir.

  House *lotAreaClose = malloc(sizeof(House));
  House *lotAreaNotClose = malloc(sizeof(House));
  int ctr_C = 0;
  int ctr_nC = 0;

  for (int i = 0; i < sizeArr; i++)
  {
    if (housesNeigh[i].lotarea >= (new_house.lotarea-2000) && housesNeigh[i].lotarea <= (new_house.lotarea+2000))
    {
      ctr_C++;
      realloc(lotAreaClose, ctr_C*sizeof(House));
      lotAreaClose[ctr_C-1] = housesNeigh[i];
    }
    else {
      ctr_nC++;
      realloc(lotAreaNotClose, ctr_nC*sizeof(House));
      lotAreaNotClose[ctr_nC-1] = housesNeigh[i];
    }
  }

  
  /*  ESKI KOD
  for (int i = 0; i < sizeArr; i++)
  {
    if (lotAreaArr[i] >= (new_house.lotarea-2000) && lotAreaArr[i] <= (new_house.lotarea+2000))
    {
      lotAreaClose[k] = lotAreaArr[i];
    }
    else 
    {
      lotAreaNotClose[j] = lotAreaArr[i];
      j++;
    }
  }

  // 4 - Kalan evleri yillarina gore siralayin

  quick_sort_libc(lotAreaNotClose, ctr_nC, compare_yearBuilt);

  // 5 - new_house degiskenin yearbuilt parametresine en yakin
  // evleri secin, bu evlerin yapim tarihleri
  //  (new_house.yearbuilt+5) ve (new_house-5) arasinda olabilir.
  // 6 - Ek olarak kaliteye gore secim yapabilirsiniz.
  // 7 - Son elemeden sonra elinizde kalan evlerin fiyat ortalamasini alin
  // 8 - Yeni gelen ev icin fiyat degeri bu ortalama olmalidir.
  
  return price;

}
*/


void create_data_matrices(House* houses,int** X,int* y){
  printf("Create data matrices from dataset\n");
  // TODO
  int size; //Ev sayisi
  X = (int**) malloc(sizeof(int)*size);
  y = (int*) malloc(sizeof(int)*size);

  for(int i = 0; i < size; i++) {
    X[i] = (int*) malloc(sizeof(int)*2);
    X[i][0] = 1;
    //X[i][1] = alan bilgisi
    //y[i] = fiyat bilgisi
  }
  return;
}

int** get_transpose(int** A, int size){
  int ** Atranspose; 
  printf("Get Transpose\n");
  // TODO
  Atranspose = (int**) malloc(sizeof(int)*2);
  for (int i = 0; i < 2; i++) {
    Atranspose = (int*) malloc(sizeof(int)*size);
  }

  for (int i = 0; i < size; i++) {
    Atranspose[i][0] = A[0][i];
    Atranspose[i][1] = A[1][i];
  }

  return Atranspose;
}


int** get_inverse(int** A){
  int** Ainverse;
  printf("Get inverse\n");
  // TODO

  return Ainverse;
}


int** get_multiplication(int** A, int** B){
  int ** C;
  printf("Multiplication\n");  
  // TODO

  int rowA = sizeof(A) / sizeof(A[0]);
  int colA = sizeof(A[0]) / sizeof(A[0][0]);
  int rowB = sizeof(B) / sizeof(B[0]);
  int colB = sizeof(B[0]) / sizeof(B[0][0]);

  C = (int**) malloc(sizeof(int)*rowA);

  for (int i = 0; i < rowA; i++) {
    C[i] = (int*) malloc(sizeof(int)*colB);
  }

  //Asagidaki islemi test et, kesin degil
  int res;
  for (int i = 0; i < rowA; i++) {
    res = 0;
    for (int j = 0; j < colB; j++) {
      res += A[i][j] * B[j][i];
    }
    C[i] = res;
  }

  return C;
}


int** calculate_parameter(int** X, int* y){
  int** W;
  printf("Calculate parameters for dataset\n");
  // TODO
  return W;

}

int** make_prediction(char* filename,int** W){
  int** predicted_prices;
  printf("Make prediction\n");
  // TODO
  // 1 - filename olarak verilen test verisini oku,
  //   yeni houses dizisi olustur
  // 2 - create_data_matrices kullanarak X ve y matrislerini olustur
  // 3 - Daha onceden hesaplanan W parametresini kullanarak
  //  fiyat tahmini yap, burda yapilmasi gereken
  //  X ve W matrislerinin carpimini bulmak
  // 4 - Sonuclari bir dosyaya yaz

}



