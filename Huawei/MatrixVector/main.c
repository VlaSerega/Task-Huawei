#include <stdio.h>
#include <stdlib.h>
#include "dgemm.h"
#include <time.h>

#define EPS 10e-6

int main() {
    int N, K, M;
    M = 1000;
    N = 1000;
    K = 1000;

    double *A = (double *) malloc(sizeof(double) * M * K);
    double *B = (double *) malloc(sizeof(double) * K * N);
    double *C = (double *) malloc(sizeof(double) * M * N);
    double *tmp = (double *) malloc(sizeof(double) * M * N);
    double time;
    struct timespec start, end;

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < K; ++j)
            A[i * K + j] = j;

    for (int i = 0; i < K; ++i)
        for (int j = 0; j < N; ++j)
            B[i * N + j] = j;

    clock_gettime(CLOCK_REALTIME_COARSE, &start);
    dgemm(M, N, K, A, K, B, N, C, N);
    clock_gettime(CLOCK_REALTIME_COARSE, &end);

    time = end.tv_sec - start.tv_sec + ((double) end.tv_nsec - start.tv_nsec) / 1000000000;

    printf("Finished: %f, GFLOPS: %f\n", time, ((double) N * M * K * 2 / time) / 1000000000);
    //Проверка правильности умножения
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            tmp[i * N + j] = 0;
            for (int k = 0; k < K; ++k) {
                tmp[i * N + j] += A[i * K + k] * B[k * N + j];
            }
            if (fabs(tmp[i * N + j] - C[i * N + j]) > EPS) {
                fprintf(stderr, "Bad result\n");
                exit(-1);
            }
        }
    }
    printf("Multiplication test ok\n");

    transpose(M, N, C, K, tmp, N);

    //Проверка правильности транспонирования
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (tmp[i * N + j] != C[j * M + i]) {
                fprintf(stderr, "Bad result\n");
                exit(-1);
            }
        }
    }
    printf("Transpose test ok\n");

    matrixMulVector(M, K, A, K, B, C);

    //Проверка правильности умножения Матрицы на вектор
    for (int i = 0; i < M; ++i) {
        tmp[i] = 0;
        for (int j = 0; j < N; ++j) {
            tmp[i] += A[i * K + j] * B[j];
        }
        if (fabs(tmp[i] - C[i]) > EPS) {
            fprintf(stderr, "Bad result\n");
            exit(-1);
        }
    }
    printf("Multiplication matrix and vector test ok\n");

    free(tmp);
    return 0;
}
