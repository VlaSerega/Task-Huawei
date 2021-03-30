//
// Created by sergo on 09.02.2021.
//

#include "dgemm.h"

static inline double horizontal_add(__m256d a) {
    __m256d t1 = _mm256_hadd_pd(a, a);
    __m128d t2 = _mm256_extractf128_pd(t1, 1);
    __m128d t3 = _mm_add_sd(_mm256_castpd256_pd128(t1), t2);
    return _mm_cvtsd_f64(t3);
}

void dgemm(int M, int N, int K, const double *A, int lda, const double *B, int ldb, double *C, int ldc) {
    const int ldb8 = ldb * 8;
    const int ldc8 = ldc * 8;
//Создание потоков
#pragma omp parallel
    {
        double new_a1[CM * CK] = {0};
        //Распараллеливание цикла по i
#pragma omp for
        for (int i = 0; i < M; i += CM) {
            int mm = min(CM, M - i);

            for (int k = 0; k < K; k += CK) {

                int kk = min(CK, K - k);
                register double *tmp;
                //Копирование блока размера mm * kk митрицы A
                for (int tmpi = 0; tmpi < mm; ++tmpi) {
                    register const double *tmpa = &A[(i + tmpi) * lda + k];
                    tmp = new_a1 + tmpi * CK;
                    for (int tmpk = 0; tmpk < kk; ++tmpk) {
                        *tmp = *tmpa;
                        tmp++;
                        tmpa++;
                    }
                }
                const double *tmpB = (double *) ((char *) B + k * ldb8);
                double *tmpC = (double *) ((char *) C + i * ldc8);

                for (int j = 0; j < N; j += CN) {
                    int nn = min(CN, N - j);
                    if (k == 0)
                        dgemmSmall(mm, nn, kk, new_a1, tmpB, ldb, tmpC, ldc, 0);
                    else
                        dgemmSmall(mm, nn, kk, new_a1, tmpB, ldb, tmpC, ldc, 1);
                    tmpB += CN;
                    tmpC += CN;
                }
            }
        }
    }
}

//Умножение блоков матриц
inline void dgemmSmall(int M, int N, int K, const double *A, const double *B, int ldb, double *C,
                       int ldc, int flag) {
    const int tmpN = N - 4;
    const int ldb8 = ldb * 8;
    for (int i = 0; i < M; ++i) {
        double *tmpC = C + i * ldc;
        register const double *tmpA = A + i * CK;

        //Инициализация С

        for (int j = 0; j < N; ++j) {
            *tmpC = *tmpA * B[j] + *tmpC * flag;
            tmpC++;
        }

        tmpC = C + i * ldc;
        tmpA++;
        for (int k = 1; k < K; k++) {
            register int j;
            register double *ck = tmpC;
            register double cur = *tmpA;
            register const double *tmpb = (double *) ((char *) B + k * ldb8);
            //4 операции умножения за одну итерацию цикла
            for (j = 0; j <= tmpN; j += 4) {
                ck[0] += cur * tmpb[0];
                ck[1] += cur * tmpb[1];
                ck[2] += cur * tmpb[2];
                ck[3] += cur * tmpb[3];
                ck += 4;
                tmpb += 4;
            }
            //Умножение оставшихся элементов
            for (; j < N; ++j) {
                *ck += cur * *tmpb;
                ck++;
                tmpb++;
            }

            tmpA++;
        }
    }
}

void matrixMulVector(int N, int M, const double *A, int lda, const double *X, double *result) {
    register const int lda8 = lda << 3;
#pragma omp parallel
    {
        const double *tmpA = A;
        for (register int i = 0; i < N; ++i) {
            register int j;
            register const double *tmpAA = tmpA;
            register double *curR = result + i;
            register const double *curX = X;
            *curR = 0;
            __m256d res = _mm256_setzero_pd();

            for (j = 0; j <= M - 4; j += 4) {
                res = _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(tmpAA), _mm256_loadu_pd(curX)), res);
                tmpAA += 4;
                curX += 4;
            }

            for (; j < M; ++j) {
                *curR += *tmpAA * *curX;
                tmpAA++;
                curX++;
            }

            *curR += horizontal_add(res);
            tmpA = (double *) ((char *) tmpA + lda8);
        }
    }
}

void matrixMulVector_(int N, int M, const double *A, int lda, const double *X, double *result) {
    register const int lda8 = lda << 3;
    register const int tmpM = (M >> 2) << 2;
#pragma omp parallel for
    for (register int i = 0; i < N; ++i) {
        register int j = tmpM;
        register const double *tmpA = (double *) ((char *) A + i * lda8);
        register double *curR = result + i;
        register const double *curX = X;
        *curR = 0;
        __m256d res = _mm256_setzero_pd();

        do {
            res = _mm256_add_pd(_mm256_mul_pd(_mm256_loadu_pd(tmpA), _mm256_loadu_pd(curX)), res);
            tmpA += 4;
            curX += 4;
            j -= 4;
        } while (j != 0);

        for (; j >= 0; --j) {
            *curR += *tmpA * *curX;
            tmpA++;
            curX++;
        }

        *curR += horizontal_add(res);
    }
}

void transpose(int N, int M, const double *A, int lda, double *B, int ldb) {
#pragma omp parallel for
    for (int i = 0; i < N; i += BLOCK_V) {
        int nn = min(BLOCK_V, N - i);
        for (int j = 0; j < M; j += BLOCK_G) {
            int mm = min(BLOCK_G, M - j);
            transposeBlock(nn, mm, A + i * lda + j, lda, B + j * ldb + i, ldb);
        }
    }
}

inline void transposeBlock(int N, int M, const double *A, int lda, double *B, int ldb) {
    for (register int i = 0; i < N; ++i) {
        for (register int j = 0; j < M; ++j) {
            B[j * ldb + i] = A[i * lda + j];
        }
    }
}