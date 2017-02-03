#include "serial_lib.h"
 
/* Generates Random number */
double numberGenerator(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}
 
/* 
Creates 3 vectors:: i_ndex, j_index and values which
Contains the non-zero values from sparse matrix A
Returns the non zero counter
*/ 
int createCOOVectors(int size){
	int i, j, NZ, max_bound;

	/* 
	Define the number of non zero elements
	Between N - N* log(N)
	*/
	max_bound = size * (int)log10(size);
	NZ = rand() % (max_bound + 1 - size) + size;

	/* Allocate memory */
	values =(double *) malloc( NZ * sizeof( double ));
	if ( values == NULL )
	{  
		printf("Error allocating memory!\n");
		free(values);
		exit(EXIT_FAILURE);
	}
	i_index =(int *) malloc( NZ * sizeof( int ));
	if ( i_index == NULL )
	{  
		printf("Error allocating memory!\n");
		free(i_index);
		exit(EXIT_FAILURE);
	}
	j_index =(int *) malloc( NZ * sizeof( int ));
	if ( j_index == NULL )
	{  
		printf("Error allocating memory!\n");
		free(j_index);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < NZ; ++i)
	{
		values[i] = numberGenerator(0,25);	
		i_index[i] = rand() % (size + 1);
		j_index[i] = rand() % (size + 1);
	}

	return NZ;
}
 

/* Sparse Matrix Multiplication Function */
void serialMatrixVectorMultiplication(int size){
	int i;

	for(i = 0; i < size; i++)
	{
		C[i_index[i]]+= values[i] * B[j_index[i]];
	}
}

/* Creates a random vector of size */ 
void createRandomVector(int size){
	int i;

	B =(double *) malloc( size * sizeof( double ));
	if ( B == NULL )
	{  
		printf("Error allocating memory!\n");
		free(B);
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < size; i++)
	{
		B[i] = numberGenerator(1,10);
	}

}
