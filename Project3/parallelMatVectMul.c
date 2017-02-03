#include <stdio.h>
#include <stdlib.h>
#include "parallel_lib.h"
#include <mpi.h>
#include <time.h>


int main(int argc, char ** argv) {
	int i, N, NZ, myid, p, ierr;

	double start_time, end_time;
	
	srand(time(NULL));	
	
	ierr = MPI_Init(&argc,&argv);              	/* starts MPI */
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);  	/* get current process id */
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);     	/* get number of processes */
		
	
	if (myid == 0)
	{
		printf("p = %d\t",p);
		if (argc != 2)
		{
			printf("N not given as argument >> Programm will exit\n");
			MPI_Abort(MPI_COMM_WORLD, 0);
			exit(EXIT_FAILURE);
		}
		else
		{
			N = atoi(argv[1]);
			printf("N == %d\n", N);
			if(N <= 1)
			{
				
				printf("Incorrect number of N  >> Programm will exit\n");
                        	MPI_Abort(MPI_COMM_WORLD, 0);
                        	exit(EXIT_FAILURE);

			}
		}

	}
	
	if(myid == 0)
	{
		
		NZ = createCOOVectors(N);
		printf("NZ = %d\n",NZ);
		createRandomVector(N);
		
		sendToAll(N, NZ);
	}
	else if (myid != 0)
	{
		/* All processors Receive data from master */
		receiveFromMaster(myid, p, &N, &NZ);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	start_time = MPI_Wtime();

	/* Allocate Result Vector */
	C = (double *) malloc( N * sizeof( double ));
	if ( C == NULL )
	{  
		printf("Error allocating memory!\n");
		free(C);
		exit(EXIT_FAILURE);
	}
	
	for(i=0; i<N; i++) {	
		C[i] = 0.0;
	}

	if(p == 1) 
	{
		printf("Serial execution\n");
		serialMatrixVectorMultiplication(NZ);	
		
	} 
	else
	{
		//parallelMulNOverP(N, NZ, p, myid);
		parallelMulNZOverP(N, NZ, p, myid);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	end_time = MPI_Wtime();

	
	if(myid == 0)
	{	
		printf("time = %lf\n", end_time - start_time);
	}
	
	MPI_Finalize();
	free(B);
	free(C);
	free(i_index);
	free(j_index);
	free(values);
	
	return EXIT_SUCCESS;
}
