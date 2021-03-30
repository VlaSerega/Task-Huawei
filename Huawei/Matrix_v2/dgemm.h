//
// Created by sergo on 07.02.2021.
//

#ifndef MATRIX_V2_DGEMM_H
#define MATRIX_V2_DGEMM_H

#include <malloc.h>
#include <immintrin.h>

#define CM 128
#define CN 256
#define CK 128

#define BLOCK_V 8
#define BLOCK_G 8

#define min(i, j) ((i) < (j) ? (i) : (j))

void dgemm(int m, int n, int k, const double *a, int lda, const double *b, int ldb, double *c, int ldc);

void dgemmSmall(int m, int n, int k, const double *a, const double *b, int ldb, double *c,
                int ldc, int flag);

void matrixMulVector(int N, int M, const double *A, int lda, const double *X, double *result);

void transpose(int N, int M, const double *A, int lda, double *B, int ldb);
void transposeBlock(int N, int M, const double *A, int lda, double *B, int ldb);

#endif //MATRIX_V2_DGEMM_H
