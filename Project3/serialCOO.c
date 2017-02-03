#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "serial_lib.h"
#include <math.h>


/* Main Function of COO Algorithm */
int main(int argc, char ** argv) 
{

	//Define N and Non Zero values
	int i, N, NZ;

	printf("Going to create a sparse Matrix of NxN elements. Give N\n");
	scanf("%d", &N);
 	
 	srand(time(NULL));

	NZ = createCOOVectors(N);

	printf("NZ = %d\n",NZ);
	createRandomVector(N);

	C =(double *) malloc( N * sizeof( double ));
	if ( C == NULL )
	{  
		printf("Error allocating memory!\n");
		free(C);
		exit(EXIT_FAILURE);
	}

	/* Initialize Vector */
	for(i=0;i<N;i++)
	{	
		C[i]=0.0;
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
	serialMatrixVectorMultiplication(NZ);
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);
	
	free(B);
	free(C);
	free(i_index);
	free(j_index);
	free(values);
	
	printf ("Time=\t%10g \tseconds\n",
	    ((double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
	    (double) (tv2.tv_sec - tv1.tv_sec)));

	printf("number of none zero values :: %d\n", NZ);
	return EXIT_SUCCESS;
}
 

	       