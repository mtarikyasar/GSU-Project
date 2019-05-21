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
    if (!strcmp(new_house.neighborhood, houses[i].neighborhood)) {
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

  for (int i = 0; i < sizeArr; i++) {
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
  } */

  // 4 - Kalan evleri yillarina gore siralayin

  quick_sort_libc(lotAreaClose, ctr_C, compare_yearBuilt);

  // 5 - new_house degiskenin yearbuilt parametresine en yakin
  // evleri secin, bu evlerin yapim tarihleri
  //  (new_house.yearbuilt+5) ve (new_house-5) arasinda olabilir.

  sizeArr = ctr_C;
  House *yearClose = malloc(sizeof(House));
  House *yearNotClose = malloc(sizeof(House));
  ctr_C = 0;
  ctr_nC = 0;

  for (int i = 0; i < sizeArr; i++) {
    if (lotAreaClose[i].yearbuilt >= (new_house.yearbuilt-5) && lotAreaClose[i].yearbuilt <= (new_house.yearbuilt+5))
    {
      ctr_C++;
      realloc(yearClose, ctr_C*sizeof(House));
      yearClose[ctr_C-1] = lotAreaClose[i];
    }
    else {
      ctr_nC++;
      realloc(yearNotClose, ctr_nC*sizeof(House));
      yearNotClose[ctr_nC-1] = lotAreaClose[i];
    }
  }

  // 6 - Ek olarak kaliteye gore secim yapabilirsiniz.

  sizeArr = ctr_C;

  if (ctr_C > 5) {
    //TODO optional
  }

  // 7 - Son elemeden sonra elinizde kalan evlerin fiyat ortalamasini alin
  
  price = 0;
  for (int i = 0; i < sizeArr; i++) {
    price += yearClose[i].saleprice;
  }
  price = price / sizeArr;
  
  // 8 - Yeni gelen ev icin fiyat degeri bu ortalama olmalidir.
  
  return price;

}



void create_data_matrices(House* houses, double** X, double* y){
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

double** get_transpose(double** A, int size){
  double ** Atranspose; 
  prdoublef("Get Transpose\n");
  // TODO
  Atranspose = (double**) malloc(sizeof(double)*2);
  for (int i = 0; i < 2; i++) {
    Atranspose = (double*) malloc(sizeof(double)*size);
  }

  for (int i = 0; i < size; i++) {
    Atranspose[i][0] = A[0][i];
    Atranspose[i][1] = A[1][i];
  }

  return Atranspose;
}


double** get_inverse(double** A){
  double** Ainverse;
  printf("Get inverse\n");
  // TODO
  double rowA = sizeof(A) / sizeof(A[0]);
  double colA = sizeof(A[0]) / sizeof(A[0][0]);
  if (rowA != colA) {
    printf("Can't get inverse of a non-square matrix.\n");
    return A;
  }

  //double temp[rowA][colA];
  Ainverse = (double**) malloc(sizeof(double)*rowA);
  for (int i = 0; i < rowA; i++) {
    Ainverse[i] = (double*) malloc(sizeof(double)*colA);
  }

  double det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
  if (det == 0) {
    printf("Can't get inverse, determinant is zero.\n");
    return A;
  }

  double coef = A[1][1] * A[0][0] - A[0][1] * A[1][0];

  Ainverse[0][0] = A[1][1] / coef;
  Ainverse[0][1] = -1 * (A[0][1] / coef);
  Ainverse[1][0] = -1 * (A[1][0] / coef);
  Ainverse[1][1] = A[0][0] / coef;
  
  return Ainverse;
}


double** get_multiplication(double** A, double** B){
  double ** C;
  printf("Multiplication\n");  
  // TODO

  double rowA = sizeof(A) / sizeof(A[0]);
  double colA = sizeof(A[0]) / sizeof(A[0][0]);
  double rowB = sizeof(B) / sizeof(B[0]);
  double colB = sizeof(B[0]) / sizeof(B[0][0]);

  C = (double**) malloc(sizeof(double)*rowA);

  for (int i = 0; i < rowA; i++) {
    C[i] = (double*) malloc(sizeof(double)*colB);
  }

  //Asagidaki islemi test et, kesin degil
  double res;
  for (int i = 0; i < rowA; i++) {
    for (int j = 0; j < colB; j++) {
      res = 0;
      for (int d = 0; d < rowB; d++) {
        res += A[i][d] * B[d][j];
      }
      C[i][j] = res;
    }
  }

  return C;
}


double** calculate_parameter(double** X, double* y){
  double** W;
  printf("Calculate parameters for dataset\n");
  // TODO
  double rowX = sizeof(X) / sizeof(X[0]);
  double colX = sizeof(X[0]) / sizeof(X[0][0]);
  int size = rowX * colX;

  double** transX = get_transpose(X, size);
  double** temp = get_multiplication(X, transX);
  temp = get_inverse(temp);
  temp = get_multiplication(temp, transX);
  W = get_multiplication(temp, y);

  return W;

}

double** make_prediction(char* filename,double** W){
  double** predicted_prices;
  printf("Make prediction\n");
  // TODO
  // 1 - filename olarak verilen test verisini oku,
  //   yeni houses dizisi olustur
  FILE* fread = fopen(filename, "r");
  char buffer[1];
  int listSize = 0;
  while(feof(fread)) {
    fgets(buffer[0], "\n", fread);
    listSize++;
  }
  House* houseList = malloc(sizeof(House)*listSize); 
  fclose(fread);

  read_house_data(filename, houseList);

  // 2 - create_data_matrices kullanarak X ve y matrislerini olustur
  double** X;
  double* y;
  create_data_matrices(houseList, X, y);

  // 3 - Daha onceden hesaplanan W parametresini kullanarak
  //  fiyat tahmini yap, burda yapilmasi gereken
  //  X ve W matrislerinin carpimini bulmak
  double** matRes = get_multiplication(X, W);

  // 4 - Sonuclari bir dosyaya yaz
  FILE* fprice = fopen("predicted_prices.txt", "w");

  fprintf(fprice, "ID\tSalePrice\n");
  for (int i = 0; i < listSize; i++) {
    fprintf(fprice, "%d\t%d\n", houseList[i].id, matRes[i][0]);
  }
}



