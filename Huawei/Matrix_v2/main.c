#include "dgemm.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define EPS 10e-6

int main() {
    int N, K, M;
    N = M = K = 11;

    double *A = (double *) malloc(sizeof(double) * M * K);
    double *B = (double *) malloc(sizeof(double) * K * N);
    double *C = (double *) malloc(sizeof(double) * M * N);

    //Time test
    {
        double *tmp = malloc(sizeof(double) * M * N);
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < K; ++j)
                A[i * K + j] = i * j;

        for (int i = 0; i < K; ++i)
            for (int j = 0; j < N; ++j)
                B[i * N + j] = i * j;

        struct timespec start, end;

        clock_gettime(CLOCK_REALTIME_COARSE, &start);
        dgemm(M, N, K, A, M, B, N, C, N);
        clock_gettime(CLOCK_REALTIME_COARSE, &end);

        //Наивное умножение для проверки
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

        double time = end.tv_sec - start.tv_sec + ((double) end.tv_nsec - start.tv_nsec) / 1000000000;
        printf("Count operation: %d, finished: %f, GFLOPS: %f\n", N * M * K * 2, time,
               (N * M * K * 2 / time) / 1000000000);
        free(tmp);
    }

    //A*0 = 0
    {
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < K; ++j)
                A[i * K + j] = i * j;

        for (int i = 0; i < K; ++i)
            B[i] = 0;


        matrixMulVector(N, K, A, K, B, C);
        dgemm(M, N, K, A, M, B, N, C, N);

        for (int i = 0; i < M; ++i)
            if (fabs(C[i]) > EPS) {
                fprintf(stderr, "Bad result\n");
                exit(-1);
            }
        printf("Test matrix*vector A*0=0 ok\n");
    }

    //A * (1)^K
    {
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < K; ++j)
                A[i * K + j] = j;

        for (int i = 0; i < K; ++i)
            B[i] = 1;


        matrixMulVector(N, K, A, K, B, C);

        for (int i = 0; i < M; ++i)
            if (fabs(C[i] - ((double) (K - 1) * K) / 2) > EPS) {
                fprintf(stderr, "Bad result\n");
                exit(-1);
            }
        printf("Test matrix*vector A * (1)^K ok\n");
    }

    free(A);
    free(B);
    free(C);
    return 0;
}
