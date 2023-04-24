#include <immintrin.h>
const char* dgemv_desc = "Vectorized implementation of matrix-vector multiply.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */
void my_dgemv(int n, double* A, double* x, double* y) {
   // insert your code here: implementation of vectorized vector-matrix multiply
    __m256d y_vec = _mm256_load_pd(y);
    for (int i = 0; i < n; i++) {
        __m256d a_vec = _mm256_load_pd(&A[i*n]); // load a row of A
        __m256d x_vec = _mm256_broadcast_sd(&x[i]); // broadcast x[i] to a vector
        y_vec = _mm256_fmadd_pd(a_vec, x_vec, y_vec); // multiply-add a_vec and x_vec to y_vec
    }
    _mm256_store_pd(y, y_vec);

}
