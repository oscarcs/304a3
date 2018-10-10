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
    
    double* A = malloc(sizeof(double) * N * N);
    double* B = malloc(sizeof(double) * N * N);

    for (int i = 0; i < N * N; i++) {
        A[i] = rand() % 3 + 1;
        B[i] = rand() % 3 + 1;
    }

    t1 = getTime();
    double* C = matrix_mul(A, B, N);
    t2 = getTime();    
    printf("time: %6.2f secs\n",(t2 - t1));

    return 0;  
}

// Matrix multiplication with temp copy
double* matrix_mul(double* A, double* B, int N) {
    double* T = malloc(sizeof(double) * N * N);
    double* C = malloc(sizeof(double) * N * N);

    // Transpose matrix b:
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            T[i+j*N] = B[N*i+j];
        }
    }

    // Perform multiply (accounting for transposition)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0;
            
            for (int k = 0; k < N; k++) {
                sum += A[N*i+k] * T[k+j*N];
            }
            C[N*i+j] = sum;
        }
    }

    free(T);
    return C;
}