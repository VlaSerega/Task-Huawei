/**
 * В данном файле представлены функции для:
 * -перемножения матриц
 * -умножения матрицы на вектор
 * -скалярное умножение вещественных векторов
 * -транспонирование матриц
 *
 * В решении использовались расширение AVX и технология OpenMP
 * */

#include "dgemm.h"
#include <omp.h>

static inline double vectorMultiplicationNotParallel(int N, const double *A, const double *B) {
    register int i = 0;
    double res;

    __asm__ __volatile__(".intel_syntax noprefix\n\t"
                         "vxorpd  ymm0, ymm0, ymm0\n\t"
                         "jmp .LLT2\n\t"

                         ".LLT1:\n\t"
                         "vmovupd xmm1, [%4]\n\t"
                         "vinsertf128     ymm1, ymm1, [%4+16], 0x1\n\t"
                         "vmovupd xmm2, [%5]\n\t"
                         "vinsertf128     ymm2, ymm2, [%5+16], 0x1\n\t"
                         "vfmadd231pd ymm0, ymm1, ymm2\n\t"
                         "add %6, 4\n\t"

                         "add %4, 32\n\t"
                         "add %5, 32\n\t"

                         ".LLT2:\n\t"
                         "cmp %6, %3\n\t"
                         "jle .LLT1\n\t"

                         "vhaddpd ymm0, ymm0, ymm0\n\t"
                         "vextractf128 xmm3, ymm0, 0x1\n\t"
                         "vaddsd xmm0, xmm0, xmm3\n\t"
                         "vmovsd [%7], xmm0\n\t"
                         ".att_syntax \n\t"
    : "=r"(A), "=r"(B), "=r"(i)
    :"r"(N - 4), "0"(A), "1"(B), "2"(i), "r"(&res)
    : "ymm0", "ymm1", "ymm2", "ymm3"
    );

    for (; i < N; ++i) {
        res += *A * *B;
        A++;
        B++;
    }

    return res;
}

//Умножение блоков матриц
static void dgemmSmall(int K, const double *A, int lda, const double *B, int ldb, double *C, int ldc) {
    const long int lda8 = lda * 8;
    const long int ldb8 = ldb * 8;
    const long int ldc8 = ldc * 8;
    register const double *endB = B + ((K >> 2) << 2);
    int count = K % 4;

    __asm__ __volatile__ (".intel_syntax noprefix\n\t"
                          "vxorpd  ymm0, ymm0, ymm0\n\t"
                          "vxorpd  ymm1, ymm1, ymm1\n\t"
                          "vxorpd  ymm2, ymm2, ymm2\n\t"
                          "vxorpd  ymm3, ymm3, ymm3\n\t"
                          "vxorpd  ymm4, ymm4, ymm4\n\t"
                          "vxorpd  ymm5, ymm5, ymm5\n\t"
                          "vxorpd  ymm6, ymm6, ymm6\n\t"
                          "vxorpd  ymm7, ymm7, ymm7\n\t"
                          "vxorpd  ymm8, ymm8, ymm8\n\t"
                          "vxorpd  ymm9, ymm9, ymm9\n\t"
                          "vxorpd  ymm10, ymm10, ymm10\n\t"
                          "vxorpd  ymm11, ymm11, ymm11\n\t"

                          "jmp .LLL2\n\t"

                          ".LLL1:\n\t"
                          "vmovupd ymm12, [%6]\n\t"
                          "mov rbx, %6\n\t"
                          "add rbx, %2\n\t"
                          "vmovupd ymm13, [rbx]\n\t"
                          "add rbx, %2\n\t"
                          "vmovupd ymm14, [rbx]\n\t"

                          "vmovupd ymm15, [%7]\n\t"
                          "vfmadd231pd ymm0, ymm12, ymm15\n\t"
                          "vfmadd231pd ymm1, ymm13, ymm15\n\t"
                          "vfmadd231pd ymm2, ymm14, ymm15\n\t"

                          "mov rbx, %7\n\t"
                          "add rbx, %3\n\t"
                          "vmovupd ymm15, [rbx]\n\t"
                          "vfmadd231pd ymm3, ymm12, ymm15\n\t"
                          "vfmadd231pd ymm4, ymm13, ymm15\n\t"
                          "vfmadd231pd ymm5, ymm14, ymm15\n\t"

                          "add rbx, %3\n\t"
                          "vmovupd ymm15, [rbx]\n\t"
                          "vfmadd231pd ymm6, ymm12, ymm15\n\t"
                          "vfmadd231pd ymm7, ymm13, ymm15\n\t"
                          "vfmadd231pd ymm8, ymm14, ymm15\n\t"

                          "add rbx, %3\n\t"
                          "vmovupd ymm15, [rbx]\n\t"
                          "vfmadd231pd ymm9, ymm12, ymm15\n\t"
                          "vfmadd231pd ymm10, ymm13, ymm15\n\t"
                          "vfmadd231pd ymm11, ymm14, ymm15\n\t"

                          "add %6, 32\n\t"
                          "add %7, 32\n\t"

                          ".LLL2:\n\t"
                          "cmp %5, %7\n\t"
                          "jne .LLL1\n\t"


                          "vhaddpd ymm0, ymm0, ymm0\n\t"
                          "vextractf128    xmm15, ymm0, 0x1\n\t"
                          "vaddsd xmm0, xmm0, xmm15\n\t"
                          "vaddsd xmm0, xmm0, [%8]\n\t"
                          "vmovsd [%8], xmm0\n\t"

                          "vhaddpd ymm3, ymm3, ymm3\n\t"
                          "vextractf128    xmm15, ymm3, 0x1\n\t"
                          "vaddsd xmm3, xmm3, xmm15\n\t"
                          "vaddsd xmm3, xmm3, [%8+8]\n\t"
                          "vmovsd [%8+8], xmm3\n\t"

                          "vhaddpd ymm6, ymm6, ymm6\n\t"
                          "vextractf128    xmm15, ymm6, 0x1\n\t"
                          "vaddsd xmm6, xmm6, xmm15\n\t"
                          "vaddsd xmm6, xmm6, [%8+16]\n\t"
                          "vmovsd [%8+16], xmm6\n\t"

                          "vhaddpd ymm9, ymm9, ymm9\n\t"
                          "vextractf128    xmm15, ymm9, 0x1\n\t"
                          "vaddsd xmm9, xmm9, xmm15\n\t"
                          "vaddsd xmm9, xmm9, [%8+24]\n\t"
                          "vmovsd [%8+24], xmm9\n\t"


                          "mov rbx, %8\n\t"
                          "add rbx, %4\n\t"
                          "vhaddpd ymm1, ymm1, ymm1\n\t"
                          "vextractf128    xmm15, ymm1, 0x1\n\t"
                          "vaddsd xmm1, xmm1, xmm15\n\t"
                          "vaddsd xmm1, xmm1, [rbx]\n\t"
                          "vmovsd [rbx], xmm1\n\t"

                          "vhaddpd ymm4, ymm4, ymm4\n\t"
                          "vextractf128    xmm15, ymm4, 0x1\n\t"
                          "vaddsd xmm4, xmm4, xmm15\n\t"
                          "vaddsd xmm4, xmm4, [rbx+8]\n\t"
                          "vmovsd [rbx+8], xmm4\n\t"

                          "vhaddpd ymm7, ymm7, ymm7\n\t"
                          "vextractf128    xmm15, ymm7, 0x1\n\t"
                          "vaddsd xmm7, xmm7, xmm15\n\t"
                          "vaddsd xmm7, xmm7, [rbx+16]\n\t"
                          "vmovsd [rbx+16], xmm7\n\t"

                          "vhaddpd ymm10, ymm10, ymm10\n\t"
                          "vextractf128    xmm15, ymm10, 0x1\n\t"
                          "vaddsd xmm10, xmm10, xmm15\n\t"
                          "vaddsd xmm10, xmm10, [rbx+24]\n\t"
                          "vmovsd [rbx+24], xmm10\n\t"


                          "add rbx, %4\n\t"

                          "vhaddpd ymm2, ymm2, ymm2\n\t"
                          "vextractf128    xmm15, ymm2, 0x1\n\t"
                          "vaddsd xmm2, xmm2, xmm15\n\t"
                          "vaddsd xmm2, xmm2, [rbx]\n\t"
                          "vmovsd [rbx], xmm2\n\t"

                          "vhaddpd ymm5, ymm5, ymm5\n\t"
                          "vextractf128    xmm15, ymm5, 0x1\n\t"
                          "vaddsd xmm5, xmm5, xmm15\n\t"
                          "vaddsd xmm5, xmm5, [rbx+8]\n\t"
                          "vmovsd [rbx+8], xmm5\n\t"

                          "vhaddpd ymm8, ymm8, ymm8\n\t"
                          "vextractf128    xmm15, ymm8, 0x1\n\t"
                          "vaddsd xmm8, xmm8, xmm15\n\t"
                          "vaddsd xmm8, xmm8, [rbx+16]\n\t"
                          "vmovsd [rbx+16], xmm8\n\t"

                          "vhaddpd ymm11, ymm11, ymm11\n\t"
                          "vextractf128    xmm15, ymm11, 0x1\n\t"
                          "vaddsd xmm11, xmm11, xmm15\n\t"
                          "vaddsd xmm11, xmm11, [rbx+24]\n\t"
                          "vmovsd [rbx+24], xmm11\n\t"

                          ".att_syntax \n\t"
    : "=r"(A), "=r"(B)
    :"r"(lda8), "r"(ldb8), "r"(ldc8), "r"(endB), "0"(A), "1"(B), "r"(C)
    : "rbx", "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
    );
    //Умножение оставшихся элементов
    for (; count != 0; count--) {
        register double cur = A[0];
        C[0] += B[0] * cur;
        C[1] += B[ldb] * cur;
        C[2] += B[2 * ldb] * cur;
        C[3] += B[3 * ldb] * cur;
        cur = A[lda];
        C[ldc] += B[0] * cur;
        C[ldc + 1] += B[ldb] * cur;
        C[ldc + 2] += B[2 * ldb] * cur;
        C[ldc + 3] += B[3 * ldb] * cur;
        cur = A[2 * lda];
        C[2 * ldc] += B[0] * cur;
        C[2 * ldc + 1] += B[ldb] * cur;
        C[2 * ldc + 2] += B[2 * ldb] * cur;
        C[2 * ldc + 3] += B[3 * ldb] * cur;
        B++;
        A++;
    }
}

void dgemm(int M, int N, int K, register const double *A, int lda, const double *B, int ldb, double *C, int ldc) {
    double *newB = malloc(sizeof(double) * N * K);
    //Транспонирование мтарицы B для последовательного ее обхода
    transpose(K, N, B, ldb, newB, K);
    //Разбиение матриц на блоки
#pragma omp parallel for
    for (int i = 0; i <= M - regA; i += regA) {
        register const double *tmpA = A + i * lda;
        for (int j = 0; j <= N - regB; j += regB) {
            register double *tmpNB = newB + j * K;
            //Блочное умножение матриц
            dgemmSmall(K, tmpA, lda, tmpNB, ldb, C + i * ldc + j, ldc);
        }
    }
    //Умножение оставшихся блоков матриц
#pragma omp parallel for
    for (int j = 0; j < N; ++j) {
        register double *tmpNB = newB + j * K;
        for (int i = M - (M % regA); i < M; ++i) {
            register const double *tmpAA = A + i * lda;
            register double *tmpC = C + i * ldc + j;
            *tmpC = vectorMultiplicationNotParallel(K, tmpAA, tmpNB);
        }
    }

#pragma omp parallel for
    for (int i = 0; i < M; ++i) {
        register const double *tmpAA = A + i * lda;
        for (int j = N - (N % regB); j < N; ++j) {
            register double *tmpC = C + i * ldc + j;
            register double *tmpNB = newB + j * K;
            *tmpC = vectorMultiplicationNotParallel(K, tmpAA, tmpNB);
        }
    }

    free(newB);
}

void matrixMulVector(int N, int M, const double *A, int lda, const double *X, register double *result) {
#pragma omp parallel for
    for (register int i = 0; i < N; ++i) {
        *(result + i) = vectorMultiplicationNotParallel(M, A + i * lda, X);
    }
}

static inline void transposeBlock(int N, int M, const double *A, int lda, double *B, int ldb) {
    for (register int i = 0; i < N; ++i) {
        for (register int j = 0; j < M; ++j) {
            B[j * ldb + i] = A[i * lda + j];
        }
    }
}

void transpose(int N, int M, const double *A, int lda, double *B, int ldb) {
    //Разбиение матрицы на блоки
#pragma omp parallel for
    for (int i = 0; i < N; i += BLOCK_V) {
        int nn = min(BLOCK_V, N - i);
        for (int j = 0; j < M; j += BLOCK_G) {
            int mm = min(BLOCK_G, M - j);
            //Блочное транспонирование матриц
            transposeBlock(nn, mm, A + i * lda + j, lda, B + j * ldb + i, ldb);
        }
    }
}