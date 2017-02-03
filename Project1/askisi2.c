/*
*****************************************************************
Project 1
Askisi 2
*****************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Random Number Generator which produces random numbers for the vectors
*/

double random_num()
{
    return (double)rand() / (double)RAND_MAX;
}



/*
Multiply A,B 
*/

double mult(int SIZE, int block_size, double A[SIZE][SIZE], double B[SIZE][SIZE], double C[SIZE][SIZE]){

	int i , j , kk , k , jj ;
	double  sum, result;	
	clock_t begin, end;
	
	begin = clock();
	for (kk =0; kk< SIZE; kk+=block_size){
			for (jj =0; jj< SIZE; jj+=block_size){
				for (i = 0; i < SIZE; i++) {
					for (j = jj; j < jj + block_size; j++){

						sum = C[i][j];
						for (k = kk; k < kk + block_size; k++){
							sum += A[i][k]*B[k][j];
						}
						C[i][j] = sum;
					}

				}
			}

	} 
	end = clock();
   	result = (double)(end - begin) / CLOCKS_PER_SEC;
    return result;

}


/*
****************************************************************************
************************* Main function ************************************
****************************************************************************
*/

int main(){

	
	double result, sum;
	int i , j , SIZE;

	/*Define size of matrices a,b */
	SIZE = 512;

	//Initialize num generator
    srand(time(NULL));


	double A[SIZE][SIZE] , B[SIZE][SIZE] , C[SIZE][SIZE] ;
	
	/* Initialize Values for a,b and c matrices */
	for (i = 0; i<SIZE; i++){
		for (j = 0; j<SIZE; j++){
			A[i][j] = random_num();
			B[i][j] = random_num();
			C[i][j] = 0.0;
		}
	}
	
	//Initiallize sum and result time for block size = 1
	sum = result = 0;
	//mult function calling for block size=1
	for(i=0; i<100; i++){
		result = mult(SIZE, 1, A, B,C);
		sum += result;
	}

	//average time for block size = 1
	sum /= 100;
	//print average time for block size =1
	printf ("Time CPU = %10g\n",sum);

	//Initiallize sum and result time for block size = 2
	sum = result = 0;
	//mult function calling for block size=2
	for(i=0; i<100; i++){
		result = mult(SIZE, 2, A, B,C);
		sum += result;

	}
	//average time for block size = 2
	sum = sum/100;
	//print average time for block size =2
	printf ("Time CPU = %10g\n",sum);

	//Initiallize sum and result time for block size = 4
	sum = 0;
	//mult function calling for block size=4
	for(i=0; i<100; i++){
		result = mult(SIZE, 4, A, B,C);
		sum += result;

	}
	//average time for block size = 4
	sum = sum/100;
	//print average time for block size =4
	printf ("Time CPU = %10g\n",sum);

	//Initiallize sum and result time for block size = 8
	sum = result = 0;
	//mult function calling for block size=8
	for(i=0; i<100; i++){
		result = mult(SIZE, 8, A, B,C);
		sum += result;

	}
	//average time for block size = 8
	sum = sum/100;
	//print average time for block size =8
	printf ("Time CPU = %10g\n",sum);

	//Initiallize sum and result time for block size = 16
	sum = result = 0;
	//mult function calling for block size=16
	for(i=0; i<100; i++){
		result = mult(SIZE, 16, A, B,C);
		sum += result;

	}
	//average time for block size = 16
	sum = sum/100;
	//print average time for block size =16
	printf ("Time CPU = %10g\n",sum);

	return 0;

}
