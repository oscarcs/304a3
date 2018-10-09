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
int* matrix_mul(int* A, int* B, int N);

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
    
    int* A = malloc(sizeof(int) * N * N);
    int* B = malloc(sizeof(int) * N * N);

    // Simple:
    t1 = getTime();
    matrix_mul(A, B, N);
    t2 = getTime();    
    printf("time: %6.2f secs\n",(t2 - t1));

    return 0;  
}

// Matrix multiplication with blocking
int* matrix_mul(int* A, int* B, int N) {

}