#include <stdio.h>
#include <stdlib.h>

//инициализация
void init(int *n1, int *m1, int *n2, int *m2, int *A, int *B) {
    scanf("%d %d", n1, m1);

    A = (int *) malloc(sizeof(int) * *n1 * *m1);

    for (int i = 0; i < *n1; ++i) {
        for (int j = 0; j < *m1; ++j) {
            scanf("%d", &A[i * *m1 + j]);
        }
    }

    scanf("%d %d", n2, m2);

    B = (int *) malloc(sizeof(int) * *n2 * *m2);

    for (int i = 0; i < *n2; ++i) {
        for (int j = 0; j < *m2; ++j) {
            scanf("%d", &B[i * *m2 + j]);
        }
    }
}

//Функция с основным алгоритмом
void patternFind(int n1, int m1, int n2, int m2, const int *A, int *B) {
    int flag;

    //Циклы по матрице B
    for (int i = 0; i <= n2 - n1; ++i) {
        for (int j = 0; j <= m2 - m1; ++j) {
            flag = 1;
            //Циклы по матрице A, проверяющие совпадение A с подматрицей в B
            for (int k = 0; k < n1; ++k) {
                for (int p = 0; p < m1; ++p) {
                    //Если не совпало в позиции одной, нет смысла дальше проверять
                    if (B[(k + i) * m2 + j + p] != A[k * m1 + p]) {
                        flag = 0;
                        break;
                    }
                }

                if (!flag)
                    break;
            }
            //Если подматрица полностью совпала с A, меняем элементы B
            if (flag) {
                for (int k = 0; k < n1; ++k) {
                    for (int p = 0; p < m1; ++p) {
                        if (B[(k + i) * m2 + j + p] == 0)
                            B[(k + i) * m2 + j + p] = -1;
                        if (B[(k + i) * m2 + j + p] == 1)
                            B[(k + i) * m2 + j + p] = 2;
                    }
                }
                /*
                 * Сдвигаем счетчик по строке на кол-во столбцов
                 * матрицы A, так как в этих позициях совпадений уже не будет
                 * */
                j += n1 - 1;
            }
        }
    }
}

int main() {
    int n1, m1, n2, m2;
    int *A = NULL, *B = NULL;

    //Все элементы B будут заменены
    {
        n1 = 200;
        m1 = 200;
        n2 = 1000;
        m2 = 1000;

        A = malloc(sizeof(int) * n1 * m1);
        B = malloc(sizeof(int) * n2 * m2);

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m1; ++j) {
                A[i * m1 + j] = 1;
            }
        }

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                B[i * m2 + j] = 1;
            }
        }

        patternFind(n1, m1, n2, m2, A, B);

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                if (B[i * m2 + j] != 2) {
                    fprintf(stderr, "Bad result");
                    exit(-1);
                }
            }
        }
        printf("Test 1 ok\n");
        free(A);
        free(B);
    }

    //Один из размеров A больше B
    {
        n1 = 500;
        m1 = 500;
        n2 = 100;
        m2 = 1000;

        A = malloc(sizeof(int) * n1 * m1);
        B = malloc(sizeof(int) * n2 * m2);

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m1; ++j) {
                A[i * m1 + j] = 1;
            }
        }

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                B[i * m2 + j] = 1;
            }
        }

        patternFind(n1, m1, n2, m2, A, B);

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                if (B[i * m2 + j] != 1) {
                    fprintf(stderr, "Bad result");
                    exit(-1);
                }
            }
        }
        printf("Test 2 ok\n");
        free(A);
        free(B);
    }

    //Нет ни одного совпадения
    {
        n1 = 500;
        m1 = 500;
        n2 = 1000;
        m2 = 1000;

        A = malloc(sizeof(int) * n1 * m1);
        B = malloc(sizeof(int) * n2 * m2);

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < m1; ++j) {
                A[i * m1 + j] = 0;
            }
        }

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                B[i * m2 + j] = 1;
            }
        }

        patternFind(n1, m1, n2, m2, A, B);

        for (int i = 0; i < n2; ++i) {
            for (int j = 0; j < m2; ++j) {
                if (B[i * m2 + j] != 1) {
                    fprintf(stderr, "Bad result");
                    exit(-1);
                }
            }
        }
        printf("Test 3 ok\n");
        free(A);
        free(B);
    }

    //init(&n1, &m1, &n2, &m2, A, B);
    //patternFind(n1, m1, n2, m2, A, B);
    //free(A);
    //free(B);

    return 0;
}
