#ifndef MATRIX_V2_DGEMM_H
#define MATRIX_V2_DGEMM_H

#include <malloc.h>
#include <immintrin.h>
#include <math.h>
#include <fmaintrin.h>

#define BLOCK_V 128
#define BLOCK_G 32

#define regA 3
#define regB 4

#define min(i, j) ((i) < (j) ? (i) : (j))

void dgemm(int m, int n, int k, const double *a, int lda, const double *b, int ldb, double *c, int ldc);

void matrixMulVector(int N, int M, const double *A, int lda, const double *X, double *result);

void transpose(int N, int M, const double *A, int lda, double *B, int ldb);

#endif //MATRIX_V2_DGEMM_H
