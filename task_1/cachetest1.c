/**
 * Oscar Sims
 * osim082
 * task 1 - cache measurement
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h> // You have to add this #include for strcmp()!!

double getTime();
void usage();
double find_sum(unsigned int, unsigned int, int);

double getTime() {
  struct timeval t;
  double sec, msec;
  
  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;
  
  sec = sec + msec / 1000000.0;
  
  return sec;
}

void usage() {
	fprintf(stderr, "Usage: cachetest1/2 [--repetitions M] [--array_size N]\n");
	exit(1);
}

int main(int argc, char* argv[]) {
    unsigned int M = 1000;
    unsigned int N = 256 * 1024; 

    // Parse the parameters:
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--repetitions") == 0) {
            i++;
            if (i < argc) {
                sscanf(argv[i], "%u", &M);
            }
            else {
                usage();
            }
        } 
        else if (strcmp(argv[i], "--array_size") == 0) {
            i++;
            if (i < argc) {
                sscanf(argv[i], "%u", &N);
            }
            else {
                usage();
            }
        } 
        else {
            usage();
        } 
    }
        
    double t1, t2;
    double time_per_iteration;

    printf("running %u iterations of array size %u...\n", M, N);

    // Sequential:
    printf("\nsequential:\n");
    t1 = find_sum(N, M, 0); 
    printf("time: %6.2f secs\n", t1);
    time_per_iteration = (t1 / M) * 1000000000;
    printf("time per iteration: %6.2f\n", time_per_iteration);

    // Random:
    // printf("\nrandom:\n");
    // t2 = find_sum(N, M, 1);
    // printf("time: %6.2f secs\n", t2);
    // time_per_iteration = (t2 / M) * 1000000000;
    // printf("time per iteration: %6.2f\n", time_per_iteration);
    
    printf("\n\n");

    return 0;  
}

/*
 * Find the sum of an array of size N, M times.
 */
double find_sum(unsigned int N, unsigned int M, int random) {
    double t1, t2;
    unsigned int sum = 0;
    
    // Allocate memory for the arrays:
    unsigned int* a = malloc(sizeof(unsigned int) * N);
    unsigned int* b = malloc(sizeof(unsigned int) * N);

    // Initialize the arrays:
    for (unsigned int i = 0; i < N; i++) {
        a[i] = 2;
        b[i] = i;
    }

    // Randomize b[]
    // if (random) {
    //     for (unsigned int i = 0; i < 2 * N; i++) {
    //         unsigned int x = rand() % N;
    //         unsigned int y = rand() % N;
    //         unsigned int temp = b[x];
    //         b[x] = b[y];
    //         b[y] = temp; 
    //     }
    // }

    t1 = getTime();

    for (unsigned int i = 0; i < M; i++) {
        sum = 0;
        for (unsigned int j = 0; j < N; j++) {
            sum += a[b[j]];
        }
    }

    t2 = getTime(); 
    printf("sum: %u\n", sum);

    free(a);
    free(b);
    return t2 - t1;
}