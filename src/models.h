#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

#ifndef MODELS
#define MODELS


// Gerekli veri tanimlarini burada yapabilirsiniz


int model_by_similarity(House* houses,House new_house);
void create_data_matrices(House* houses, double** X, double* y);
double** get_transpose(double** A, int size);
double** get_inverse(double** A);
double** get_multiplication(double** A, double** B);
double** calculate_parameter(double** X, double* y);
double** make_prediction(char* filename, double** W);

#endif
