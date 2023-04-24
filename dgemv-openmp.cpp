#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {

   #pragma omp parallel
   {
      int nthreads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
   
   
   }
#pragma omp parallel for
for (int i = 0; i < n; i++) {
double temp = 0.0;
for (int j = 0; j < n; j++) {
temp += A[i*n+j] * x[j];
}
#pragma omp atomic
y[i] += temp;
}
}

int main(int argc, char **argv) {

// matrix dimension
int n = 10000;

// allocate memory for matrix and vectors
double A = (double)malloc(n * n * sizeof(double));
double x = (double)malloc(n * sizeof(double));
double y = (double)malloc(n * sizeof(double));

// initialize matrix and vectors
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
A[i*n+j] = rand() / (double)RAND_MAX;
}
x[i] = rand() / (double)RAND_MAX;
y[i] = rand() / (double)RAND_MAX;
}

// perform dgemv operation
my_dgemv(n, A, x, y);

// deallocate memory
free(A);
free(x);
free(y);

return 0;
}
   // insert your dgemv code here. you may need to create additional parallel regions,
   // and you may want to comment out the above parallel code block that prints out
   // nthreads and thread_id so as to not taint your timings

}

