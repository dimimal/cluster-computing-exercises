/*
*****************************************************************
Project 1
Askisi 1
*****************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/*
    Declare Vector Multiplication Functions For k = 1,2,4,8,16
*/
double vector_mul_k1(double *a, double *b, unsigned int size)
{
    clock_t begin,end;
    double time_spent;
    int i;
    double register res = 0.0;

    begin = clock();

    for (i = 0; i < size; ++i)
    {
        res += a[i] * b[i];
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("For k = 1 --> time:: %lf seconds\n", time_spent);

    return res;
}

double vector_mul_k2(double *a, double *b, unsigned int size)
{
    clock_t begin,end;
    double time_spent;
    int i;
    double register res = 0.0;

    begin = clock();
    for (i = 0; i < size; i+=2)
    {
        res += a[i] * b[i]+ a[i+1] * b[i+1];
        
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("For k = 2 --> time:: %lf seconds\n", time_spent);
    return res;
}


double vector_mul_k4(double *a, double *b, unsigned int size)
{
    clock_t begin, end;
    double time_spent;
    double register res = 0.0;
    int i;
    
    begin = clock();
    for (i = 0; i <= size-4; i+=4)
    {
        res += a[i] * b[i] + a[i+1] * b[i+1] +
        a[i+2] * b[i+2] + a[i+3] * b[i+3];
        
    }
    end = clock();
    
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("For k = 4 --> time:: %lf seconds\n", time_spent);
    return res;

}


double vector_mul_k8(double *a, double *b, unsigned int size)
{
    clock_t begin,end;
    double time_spent;
    int i;
    double register res = 0.0;

    begin = clock();
    for (i = 0; i <= size-8; i+=8)
    {
        res += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] +
            a[i+3] * b[i+3] + a[i+4] * b[i+4] + a[i+5] * b[i+5] +
            a[i+6] * b[i+6] + a[i+7] * b[i+7];

    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("For k = 8 --> time:: %lf seconds\n", time_spent);
    return res;

}


double vector_mul_k16(double *a, double *b, unsigned int size)
{
    clock_t begin,end;
    double time_spent;
    int i;
    double register res = 0.0;

    begin = clock();
    for (i = 0; i <= size-16; i+=16)
    {
        res += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] +
        a[i+3] * b[i+3] + a[i+4] * b[i+4] + a[i+5] * b[i+5] + 
        a[i+6] * b[i+6] + a[i+7] * b[i+7] + a[i+8] * b[i+8] +
        a[i+9] * b[i+9] + a[i+10] * b[i+10] + a[i+11] * b[i+11] + 
        a[i+12] * b[i+12] + a[i+13] * b[i+13] + 
        a[i+14] * b[i+14] + a[i+15] * b[i+15];
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("For k = 16 --> time:: %lf seconds\n", time_spent);
    return res;
}

double vector_mul_k32(double *a, double *b, unsigned int size)
{
    clock_t begin,end;
    double time_spent;
    int i;
    double register res = 0.0;

    begin = clock();
    for (i = 0; i <= size-32; i+=32)
    {
        res += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] +
        a[i+3] * b[i+3] + a[i+4] * b[i+4] + a[i+5] * b[i+5] + 
        a[i+6] * b[i+6] + a[i+7] * b[i+7] + a[i+8] * b[i+8] +
        a[i+9] * b[i+9] + a[i+10] * b[i+10] + a[i+11] * b[i+11] + 
        a[i+12] * b[i+12] + a[i+13] * b[i+13] + 
        a[i+14] * b[i+14] + a[i+15] * b[i+15] + 
        a[i+16] * b[i+16] + a[i+17] * b[i+17] + a[i+18] * b[i+18] +
        a[i+19] * b[i+19] + a[i+20] * b[i+20] + a[i+21] * b[i+21] + 
        a[i+22] * b[i+22] + a[i+23] * b[i+23] + a[i+24] * b[i+24] +
        a[i+25] * b[i+25] + a[i+26] * b[i+26] + a[i+27] * b[i+27] + 
        a[i+28] * b[i+28] + a[i+29] * b[i+29] + 
        a[i+30] * b[i+30] + a[i+31] * b[i+31];
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("For k = 32 --> time:: %lf seconds\n", time_spent);
    return res;
}

/*
Random Number Generator which produces random numbers for the vectors
*/
double random_num()
{
    return (double)rand() / (double)RAND_MAX;
}

/*
****************************************************************************
************************* Main function ************************************
****************************************************************************
*/
int main(int argc, char **argv)
{
    int i;
    /* Define Size of vectors (only power of 2) */
    unsigned int SIZE = pow(2,20);
    /* allocate memory for vectors a,b,c */
    double k1_result, k2_result, k4_result, 
        k8_result, k16_result, k32_result;

    double *a = malloc(sizeof(double)*SIZE);
    double *b = malloc(sizeof(double)*SIZE);

    /*Check for memory allocation errors */
    if (!a || !b)
    {
        printf("Memory allocaation Error\n");
        exit(EXIT_FAILURE);      
    }

    //Initialize num generator
    srand(time(NULL));

    //Generate random real numers to vectors
    for (i = 0; i < SIZE; ++i)
    {
        a[i] = random_num();
        b[i] = random_num();
    }
    
    k1_result = vector_mul_k1(a, b, SIZE);
    k2_result = vector_mul_k2(a, b, SIZE);
    k4_result = vector_mul_k4(a, b, SIZE);
    k8_result = vector_mul_k8(a, b, SIZE);
    k16_result = vector_mul_k16(a, b, SIZE);
    k32_result = vector_mul_k32(a, b, SIZE);

    free(a);
    free(b);
    /*
    printf("Result for k = 1 :: %lf\n",k1_result );
    printf("Result for k = 2 :: %lf\n",k2_result );
    printf("Result for k = 4 :: %lf\n",k4_result );
    printf("Result for k = 8 :: %lf\n",k8_result );
    printf("Result for k = 16 :: %lf\n",k16_result );
    printf("Result for k = 32 :: %lf\n",k32_result );
    */
    return 0;
}
