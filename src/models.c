#include "models.h"
#include "dataset.h"
#include "quick_sort_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAT_COL 2

double model_by_similarity(House* houses,House new_house, int houseCount){
  //printf("Find price for house %d\n",new_house.id);
  double price = 0;
  int sizeArr = houseCount;

  // 1 - Oncelikle ayni komsuluktaki evleri bulun

  House *housesNeigh = malloc(sizeof(House));
  if (housesNeigh == NULL) {
    printf("Failed to allocate memory for struct array < housesNeigh >\n");
    printf("(At models.c, line 16)\n");
    return 0;
  }
  int ctr_C = 0;

  for (int i = 0; i < sizeArr; i++) {
    if (!strcmp(new_house.neighborhood, houses[i].neighborhood)) {
      ctr_C++;
      housesNeigh = realloc(housesNeigh, ctr_C*sizeof(House));
      housesNeigh[ctr_C - 1] = houses[i];
    }
  }
  
  // 2 - Bu evleri lotArea ya gore siralayin

  quick_sort_type(housesNeigh, ctr_C, AREA);

  // 3 - new_house degiskenin lotarea parametresine en
  //  yakin evleri alin, bu evlerin alanlari 
  //  (new_house.lotarea+2000) ve (new_house.lotarea-2000) metrekare arasinda
  //   olabilir.

  House *lotAreaClose = malloc(sizeof(House));
  if (lotAreaClose == NULL) {
    printf("Failed to allocate memory for struct array < lotAreaClose >\n");
    printf("(At models.c, line 16)\n");
    return 0;
  }
  sizeArr = ctr_C;
  ctr_C = 0;

  for (int i = 0; i < sizeArr; i++) {
    if (housesNeigh[i].lotarea >= (new_house.lotarea - 1000) && housesNeigh[i].lotarea <= (new_house.lotarea + 1000)) {
      ctr_C++;
      lotAreaClose = realloc(lotAreaClose, ctr_C*sizeof(House));
      lotAreaClose[ctr_C - 1] = housesNeigh[i];
    }
  }

  if (ctr_C == 0) {
    for (int i = 0; i < sizeArr; i++) {
      price += housesNeigh[i].saleprice;
    }
    price /= sizeArr;
    free(housesNeigh); housesNeigh = NULL;
    free(lotAreaClose); lotAreaClose = NULL;
    return price;
  }

  // 4 - Kalan evleri yillarina gore siralayin
  
  quick_sort_type(lotAreaClose, ctr_C, YEAR);

  // 5 - new_house degiskenin yearbuilt parametresine en yakin
  // evleri secin, bu evlerin yapim tarihleri
  //  (new_house.yearbuilt+5) ve (new_house-5) arasinda olabilir.

  House *yearClose = malloc(sizeof(House));
  if (yearClose == NULL) {
    printf("Failed to allocate memory for struct array < yearClose >\n");
    printf("(At models.c, line 76)\n");
    return 0;
  }
  sizeArr = ctr_C;
  ctr_C = 0;

  for (int i = 0; i < sizeArr; i++) {
    if (lotAreaClose[i].yearbuilt >= (new_house.yearbuilt-5) && lotAreaClose[i].yearbuilt <= (new_house.yearbuilt+5))
    {
      ctr_C++;
      yearClose = realloc(yearClose, ctr_C * sizeof(House));
      yearClose[ctr_C - 1] = lotAreaClose[i];
    }
  }
  
  if (ctr_C == 0) {
    for (int i = 0; i < sizeArr; i++) {
      price += lotAreaClose[i].saleprice;
    }
    price /= sizeArr;
    free(housesNeigh); housesNeigh = NULL;
    free(lotAreaClose); lotAreaClose = NULL;
    free(yearClose); yearClose = NULL;
    return price;
  }

  // 6 - Ek olarak kaliteye gore secim yapabilirsiniz.

  sizeArr = ctr_C;

  if (ctr_C > 5) {
    ctr_C = 0;
    House *overallClose = malloc(sizeof(House));
    if (overallClose == NULL) {
      printf("Failed to allocate memory for struct array < overallClose >\n");
      printf("(At models.c, line 111)\n");
      return 0;
    }
    double overallCheck;
    double overallCur;

    for (int i = 0; i < sizeArr; i++) {
      overallCheck = (yearClose[i].overallcond + yearClose[i].overallqual) / 2;
      overallCur = (new_house.overallcond + new_house.overallqual) / 2;

      if ((overallCheck >= overallCur - 1) && (overallCheck <= overallCur + 1)) {
        ctr_C++;
        overallClose = realloc(overallClose, ctr_C*sizeof(House));
        overallClose[ctr_C - 1] = yearClose[i];
      }
    }

    if (ctr_C == 0) {
      for (int i = 0; i < sizeArr; i++) {
        price += yearClose[i].saleprice;
      }
      price /= sizeArr;
      free(housesNeigh); housesNeigh = NULL;
      free(lotAreaClose); lotAreaClose = NULL;
      free(yearClose); yearClose = NULL;
      free(overallClose); overallClose = NULL;
      return price;
    }
    else {
      sizeArr = ctr_C;
      for (int i = 0; i < sizeArr; i++) {
        price += overallClose[i].saleprice;
      }
      price /= sizeArr;
      free(housesNeigh); housesNeigh = NULL;
      free(lotAreaClose); lotAreaClose = NULL;
      free(yearClose); yearClose = NULL;
      free(overallClose); overallClose = NULL;
      return price;
    }
  }

  // 7 - Son elemeden sonra elinizde kalan evlerin fiyat ortalamasini alin
  
  for (int i = 0; i < sizeArr; i++) {
    price += yearClose[i].saleprice;
  }
  price = price / sizeArr;

  free(housesNeigh); housesNeigh = NULL;
  free(lotAreaClose); lotAreaClose = NULL;
  free(yearClose); yearClose = NULL;

  // 8 - Yeni gelen ev icin fiyat degeri bu ortalama olmalidir.
  return price;
}



void create_data_matrices(House* houses, double** X, double* y, int size){
  printf("Creating data matrices from dataset...\n");

  for(int i = 0; i < size; i++) {
    X[i][0] = 1;
    X[i][1] = houses[i].lotarea;
    y[i] = houses[i].saleprice;
  }
  return;
}

double** get_transpose(double** A, int size){
  printf("Getting Transpose...\n");

  double ** Atranspose; 
  Atranspose = malloc(MAT_COL * sizeof(double*));
  for (int i = 0; i < MAT_COL; i++){
    Atranspose[i] = malloc(size * sizeof(double));
  }

  for (int i = 0; i < size; i++){
    Atranspose[0][i] = A[i][0];
    Atranspose[1][i] = A[i][1];
  }

  return Atranspose;
}


double** get_inverse(double** A, int size) {
  printf("Getting inverse...\n");

  double** Ainverse;
  Ainverse = malloc(MAT_COL * sizeof(double));
  for (int i = 0; i < MAT_COL; i++) {
    Ainverse[i] = malloc(MAT_COL * sizeof(double));
  }

  double det = A[0][0] * A[1][1] - A[1][0] * A[0][1];
  if (det == 0) {
    printf("Can't get inverse, determinant is zero.\n");
    return A;
  }

  Ainverse[0][0] = A[1][1] / det;
  Ainverse[0][1] = -1 * (A[0][1] / det);
  Ainverse[1][0] = -1 * (A[1][0] / det);
  Ainverse[1][1] = A[0][0] / det;
  
  return Ainverse;
}


double** get_multiplication(double** A, double** B, int rowA, int colB, int colA){
  printf("Multiplication in progress...\n");  

  double** C;
  C = malloc(rowA * sizeof(double*));
  for (int i = 0; i < rowA; i++) {
    C[i] = malloc(colB * sizeof(double));
  }

  double res;
  for (int i = 0; i < rowA; i++) {
    for (int j = 0; j < colB; j++) {
      res = 0;
      for (int d = 0; d < colA; d++) {
        res += A[i][d] * B[d][j];
      }
      C[i][j] = res;
    }
  }
  return C;
}


double** calculate_parameter(double** X, double* y, int size){
  printf("Calculating parameters for dataset...\n");

  double** W;
  double** transX = get_transpose(X, size);
  double** temp = get_multiplication(transX, X, MAT_COL, MAT_COL, size);
  double** temp2 = get_inverse(temp, size);
  temp = get_multiplication(temp2, transX, MAT_COL, size, MAT_COL);
  
  double** tempY = malloc(size * sizeof(double *));
  for (int i = 0; i < size; i++) {
    tempY[i] = malloc(sizeof(double));
    tempY[i][0] = y[i];
  }

  W = get_multiplication(temp, tempY, MAT_COL, MAT_COL, size);

  return W;
}

void make_prediction(char* filename, double** W, int listSize){
  printf("Making prediction...\n");

  // 1 - filename olarak verilen test verisini oku,
  //   yeni houses dizisi olustur
  House* houseList = malloc(sizeof(House)*listSize); 
  read_house_testData(filename, houseList);

  // 2 - create_data_matrices kullanarak X ve y matrislerini olustur
  double** X = malloc(listSize * sizeof(double*));
  double* y = malloc(listSize * sizeof(double));
  for (int i = 0; i < listSize; i++) {
    X[i] = malloc(2 * sizeof(double));
  }

  create_data_matrices(houseList, X, y, listSize);

  // 3 - Daha onceden hesaplanan W parametresini kullanarak
  //  fiyat tahmini yap, burda yapilmasi gereken
  //  X ve W matrislerinin carpimini bulmak

  double** matRes = malloc(listSize * sizeof(double *));
  for (int i = 0; i < listSize; i++) {
    matRes[i] = malloc(sizeof(double));
  }
  matRes = get_multiplication(X, W, listSize, 1, MAT_COL);

  // 4 - Sonuclari bir dosyaya yaz
  FILE* fprice = fopen("predicted_prices.txt", "w");

  fprintf(fprice, "ID\tSalePrice\n");
  for (int i = 0; i < listSize; i++) {
    fprintf(fprice, "%d\t%.2lf\n", houseList[i].id, matRes[i][0]);
  }

  fclose(fprice);
  printf("Prediction completed! Predicted prices are saved to predicred_prices.txt file\n\n");

  for (int i = 0; i < listSize; i++) {
    free(X[i]);
  }
  free(y); y = NULL;
  free(X); X = NULL;
}