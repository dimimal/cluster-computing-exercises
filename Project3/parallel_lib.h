#ifndef parallel_lib
#define parallel_lib

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

double *B;
double *values;
double *C;
int *i_index, *j_index;


void quickSort( int *, int, int);
int partition( int *, int, int);

double numberGenerator(double min, double max);
int createCOOVectors(int size);
void createRandomVector(int size);
void serialMatrixVectorMultiplication(int size);
void parallelMulNOverP(int N, int NZ, int p,int myid);
void parallelMulNZOverP(int N, int NZ, int p,int myid);
void sendToAll(int N,int NZ);
void receiveFromMaster(int myid, int p, int *N, int *NZ);

#endif