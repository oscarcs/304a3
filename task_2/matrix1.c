/**
 * Oscar Sims
 * osim082
 * task 2 - matrix product
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double getTime();
double* matrix_mul(double* A, double* B, int N);

double getTime() {
    struct timeval t;
    double sec, msec;

    while (gettimeofday(&t, NULL) != 0);
    sec = t.tv_sec;
    msec = t.tv_usec;

    sec = sec + msec / 1000000.0;

    return sec;
}

int main(int argc, char* argv[]) {
    double t1, t2; 
    
    int N = 1000;
    // int N = 3;
    
    double* A = malloc(sizeof(double) * N * N);
    double* B = malloc(sizeof(double) * N * N);

    // Test (N=3):
    // double a[] = {1, 2, 1, 0, 1, 0, 2, 3, 4};
    // A = &a; 
    // double b[] = {2, 5, 1, 6, 7, 1, 1, 8, 1};
    // B = &b;
    // &C = [15, 27, 4, 6, 7, 1, 26, 63, 9];

    for (int i = 0; i < N * N; i++) {
        A[i] = rand() % 3 + 1;
        B[i] = rand() % 3 + 1;
    }

    // Simple:
    t1 = getTime();
    double* C = matrix_mul(A, B, N);
    t2 = getTime();    
    printf("time: %6.2f secs\n",(t2 - t1));

    return 0;  
}

/**
 * Simple matrix multiplication.
 * Takes two single-dimensional arrays.
 */
double* matrix_mul(double* A, double* B, int N) {
    double* C = calloc(N*N, sizeof(double));

    // Simplest matrix multiplication algorithm.
    // A very easy speedup could be obtained by swapping the order of the loops.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[N*i+j] += A[N*i+k] * B[N*k+j];
            }
        }
    }

    return C;
}