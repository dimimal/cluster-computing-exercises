#include "parallel_lib.h"

double numberGenerator(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}


/* Creates the COO vectors of sparse matrix */
int createCOOVectors(int size){
	int i, NZ, max_bound;

	/* 
		>>>	Define the number of non zero elements
		>>> Between N - N* log(N)
	*/
	max_bound = size * (int)log10(size);
	NZ = rand() % (max_bound + 1 - size) + size;
		
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

	quickSort(i_index, 0, NZ);
	quickSort(j_index, 0, NZ);

	return NZ;
}

/* Create random vector B */
void createRandomVector(int size){
	int i;
	 
	B =(double *) malloc( size * sizeof( double ));
	if ( B == NULL )
	{  
		printf("Error allocating memory!\n");
		free(B);
		return;
	}
	 
	for(i = 0; i < size; i++)
	{
		B[i] = numberGenerator(1,10);
	}
}

/* Serial Algorithm for P = 1 */
void serialMatrixVectorMultiplication(int size){
	int i;
	 
	for(i = 0; i < size; i++)
	{
		C[i_index[i]]+= values[i] * B[j_index[i]];
	}
}

/* Distribute N/P */
void parallelMulNOverP(int N, int NZ, int p,int myid){
	int i, ierr;//,j; ,k,err,pos;
	double *temp;
	int mod = N % p;
	
	for(i=0; i < NZ - mod; i++)
	{
		/*
		Check the index of matrix belongs to current processor
		<<<< (N/p)*i - (N/p)*(i+1) -1 >>>>>
		Then multiply
		*/
		if( (i_index[i]) >= ((N/p)*myid) && (i_index[i]) <= ((N/p)*(myid+1) -1) )
		{
			C[i_index[i]]+= values[i] * B[j_index[i]];
		}
	}
	if( myid == 0 )
	{
		for(i = NZ - mod; i < NZ; i++)
		{
			if( (i_index[i]) >= ((N/p)*myid) && (i_index[i]) <= ((N/p)*(myid+1) -1) )
			{
				C[i_index[i]]+= values[i] * B[j_index[i]];
			}
		}
	}

	
	if(myid == 0)
	{
		temp =(double *) malloc( N* sizeof( double ));
		if ( temp == NULL )
		{  
			printf("Error allocating memory!\n");
			free(temp);
			return;
		}
	}
	
	/* Reduce the sum to master */
	ierr = MPI_Reduce(C, temp, N, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if(myid==0)
	{
		C = temp;
	}

}

/* Split the blocks as NZ/P */
void parallelMulNZOverP(int N, int NZ, int p,int myid){
	int i, ierr;
	double *temp;
	int mod;
		
	mod = NZ % p;

	for(i=0; i < NZ-mod; i++)
	{
		if( i >= ((NZ/p) * myid) && i < ((NZ/p) * (myid+1)) )
		{
			C[i_index[i]]+= values[i] * B[j_index[i]];
		}
	}

	/* Multiply the rest of the matrix */
	for(i=NZ-mod; i<NZ; i++)
	{
		if(myid == 0)
		{
			C[i_index[i]]+= values[i] * B[j_index[i]];
		}
	}
	
	if(myid == 0)
	{
		temp = (double *) malloc( N * sizeof( double ));
		if (temp == NULL)
		{  
			printf("Error allocating memory!\n");
			free(temp);
			return;
		}
	}
	
	/* Reduce to master */
	ierr = MPI_Reduce(C, temp, N, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);

	if(myid == 0)
	{
		C = temp;
	}

}

/* Send vectors and values to all*/
void sendToAll(int N,int NZ){
	 
	/* Broadcast the values needed */ 
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);	 
 	MPI_Bcast(&NZ, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(B, N, MPI_INT, 0, MPI_COMM_WORLD);	
	MPI_Bcast(values, NZ, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(i_index, NZ, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(j_index, NZ, MPI_INT, 0, MPI_COMM_WORLD);
}

void receiveFromMaster(int myid, int p, int *N, int *NZ)
{
	int n,nz;

	MPI_Bcast(N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	n = *N;

	MPI_Bcast(NZ, 1, MPI_INT, 0, MPI_COMM_WORLD);
	nz = *NZ;

	B =(double *) malloc( n * sizeof( double ));
	if ( B == NULL )
	{  
		printf("Error allocating memory!\n");
		free(B);
		return;
	}
	
	MPI_Bcast(B, n, MPI_INT, 0, MPI_COMM_WORLD);

	values =(double *) malloc( nz * sizeof( double ));
	if ( values == NULL )
	{  
		printf("Error allocating memory!\n");
		free(values);
		exit(EXIT_FAILURE);
	}
	i_index =(int *) malloc( nz * sizeof( int ));
	if ( i_index == NULL )
	{  
		printf("Error allocating memory!\n");
		free(i_index);
		exit(EXIT_FAILURE);
	}
	j_index =(int *) malloc( nz * sizeof( int ));
	if ( j_index == NULL )
	{  
		printf("Error allocating memory!\n");
		free(j_index);
		exit(EXIT_FAILURE);
	}

	MPI_Bcast(values,  nz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(i_index, nz, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(j_index, nz, MPI_INT, 0, MPI_COMM_WORLD);

}



void quickSort( int *a, int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
       j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}



int partition( int *a, int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
