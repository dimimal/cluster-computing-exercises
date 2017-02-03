#ifndef serial_library
#define serial_library

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


double *B;
double *values;
double *C;
int *i_index,*j_index;

struct timespec tv1,tv2;


double numberGenerator(double min, double max);
int createCOOVectors(int size);
void createRandomVector(int size);
void serialMatrixVectorMultiplication(int size);


#endif