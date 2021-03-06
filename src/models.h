#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"

#ifndef MODELS
#define MODELS

// Gerekli veri tanimlarini burada yapabilirsiniz

double model_by_similarity(House* houses,House new_house, int houseCount);
void create_data_matrices(House* houses, double** X, double** y, int size);
double** get_transpose(double** A, int size);
double** get_inverse(double** A, int size);
double** get_multiplication(double** A, double** B, int rowA, int colB, int colA);
double** calculate_parameter(double** X, double** y, int size);
void make_prediction(char* filename, double** W,int listSize);

#endif