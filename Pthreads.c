#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_M 3
#define MAX_N 3

int m;  // Número de linhas da matriz
int n;  // Número de colunas da matriz
int thread_count;  // Número de threads

int A[MAX_M][MAX_N];  // Matriz (inteiros)

void* GenerateRandomNumbers(void* rank) {
    long my_rank = (long) rank;
    int elements_per_thread = m * n / thread_count;
    int my_start = my_rank * elements_per_thread;
    int my_end = (my_rank == thread_count - 1) ? (m * n) : (my_start + elements_per_thread);

    srand(time(NULL));

    for (int i = my_start; i < my_end; i++) {
        A[i / n][i % n] = rand() % 100; // Números inteiros aleatórios entre 0 e 99 (ajuste conforme necessário)
    }

    return NULL;
}

int main() {
    // Defina os valores de m, n, thread_count e outros parâmetros, se necessário
    m = 3;  // 3 linhas na matriz
    n = 3;  // 3 colunas na matriz
    thread_count = 2;  // Número de threads

    // Aloque espaço para armazenar identificadores das threads
    pthread_t* thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (long thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, GenerateRandomNumbers, (void*) thread);
    }

    for (long thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    // Imprima a matriz A com formatação
    printf("Matriz A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%02d ", A[i][j]); // Formatação para dois dígitos com zero à esquerda
        }
        printf("\n");
    }

    return 0;
}
