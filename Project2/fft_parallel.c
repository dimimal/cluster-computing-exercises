/*
This id parallel FFT Algorithm using OpenMP Threads
*/

#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 
#include "omp.h"
#include <time.h>

typedef struct complex_t {
	double re;
	double im;
} complex;

char** binaryID;
struct timespec  tv1, tv2;

void getBin(int num, char *str,unsigned int n);
int check(int pos1,int pos2,int m,unsigned int n);
void iterative_fft(complex *x,complex *y, unsigned int n);
complex polar_to_complex(double r, double theta_radians);
complex complex_mult(complex left, complex right);
complex complex_add(complex left, complex right);

complex polar_to_complex(double r, double theta_radians) {
	complex result;
	result.re = r * cos(theta_radians);
	result.im = r * sin(theta_radians);
	return result;
}

complex complex_add(complex left, complex right) {
	complex result;
	result.re = left.re + right.re;
	result.im = left.im + right.im;
	return result;
}

complex complex_mult(complex left, complex right) {
	complex result;
	result.re = left.re*right.re - left.im*right.im;
	result.im = left.re*right.im + left.im*right.re;
	return result;
}

/* FFT Algorithm Function */
void iterative_fft(complex *x,complex *y, unsigned int n){
	int i,m,k;
	int r = log2(n);
	complex *S;
	
	S = malloc(n * sizeof(complex));

	if (S == NULL) {
		printf("Error allocating memory!\n");
		free(S);
		exit(EXIT_FAILURE);
	}

	#pragma omp parallel for 
	for(i=0; i<n; i++){
		y[i]=x[i];
	}

	for(m=0; m<r; m++){
		#pragma omp parallel for 
		for(i=0; i<n; i++){
			S[i]=y[i];
		}
		for(i=0; i<n; i++){
			#pragma omp parallel for 
			for(k=0; k<n; k++){		
				if(check(i,k,m,n)){
					S[k] = complex_mult(polar_to_complex(1, -2.0*M_PI*k/r), S[k]);
					y[i] = complex_add(S[i] , S[k]);
				}
			}
		}
	}
	return;
}


void getBin(int num, char *str,unsigned int n)
{
	int c,k,r;
	r = log2(n);
	
	for (c = 0; c <r; c++)
	{
		k = num >> c;
		
		if (k & 1)
			str[r-1-c]='1';
		else
			str[r-1-c]='0';
	}
	str[r]='\0';

}

int check(int pos1,int pos2,int m,unsigned int n){
	
	int j,r;
	r = log2(n);
	for(j=0;j<r;j++){
		if(j!=m){
			if(binaryID[pos1][j]!=binaryID[pos2][j])
				return 0;
		}
		if(j==m){
			if(binaryID[pos1][j]==binaryID[pos2][j])
				return 0;
		}
	}
	return 1;
}


/*
    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 		Main Function 
   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
int main(int argc, char *argv[]){
	
	complex *X,*Y;
	unsigned int i, n, numthreads;
	n = pow(2,atoi(argv[1]));
	printf("n = %d\n",n);
	numthreads = atoi(argv[2]);

	omp_set_num_threads(numthreads);

	#pragma omp parallel
	#pragma omp master
	numthreads = omp_get_num_threads();
	printf("numthreads = %d\n", numthreads);

	/* Initialize */
	X = malloc(n* sizeof( complex));
	Y = malloc(n* sizeof( complex));
	binaryID = malloc(n*sizeof(char*));

	if (X == NULL || Y == NULL || binaryID == NULL) {
		printf("Error allocating memory!\n");
		free(X);
		free(Y);
		free(binaryID); 
		exit(EXIT_FAILURE);
	}

  	for(i=0; i<n; i++){
	    X[i].re = (double ) (rand()%10); 
	    X[i].im = (double ) (rand()%10);
    	//printf("X[%d] = %lf + %lfi\n",i,X[i].re,X[i].im);
  	}

 	for(i =0; i<n; i++){
	 	binaryID[i]=malloc((log2(n)+1)*sizeof(char));
	  	if(binaryID[i] == NULL) {
			printf("Couldn't Allocate memory\n");
		  	exit(EXIT_FAILURE);
	  	}

	  	getBin(i, binaryID[i], n);
  	}

    
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
    for(i=0; i<10; i++){	    
		iterative_fft(X,Y,n);
		printf(".\n");
		break;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);

    printf ("Time=\t%10g \tseconds\n",
	    ((double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
	    (double) (tv2.tv_sec - tv1.tv_sec)));

    free(X);
    free(Y);
    return 1;
}
