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

    // Simple:
    t1 = getTime();
    double* C = matrix_mul(A, B, N);
    t2 = getTime();    
    printf("time: %6.2f secs\n",(t2 - t1));

    // for (int i = 0; i < N * N; i++) {
    //     printf("%2.1f ", C[i]);
    // }

    return 0;  
}

// Matrix multiplication with blocking
double* matrix_mul(double* A, double* B, int N) {
    double* C = calloc(N*N, sizeof(double));

    // Set the block size based on the cache line size:
    int block_size = 16;

    // The outer three loops set the upper and lower bounds for each of the
    // three inside loops:
    for (int i0 = 0; i0 < N; i0 += block_size) {
        int i1 = i0+block_size > N ? N : i0+block_size;

        for (int j0 = 0; j0 < N; j0 += block_size) {
            int j1 = j0+block_size > N ? N : j0+block_size;

            for (int k0 = 0; k0 < N; k0 += block_size) {
                int k1 = k0+block_size > N ? N : k0+block_size;

                // The inside three loops are the same as the 
                // other implementations:

                for (int i = i0; i < i1; i++) {
                    for (int j = j0; j < j1; j++) {
                        for (int k = k0; k < k1; k++) {
    
                            // Same formula as (1)
                            C[N*i+j] += A[N*i+k] * B[N*k+j];
                        }
                    }
                }
            }
        }
    }

    return C;
}