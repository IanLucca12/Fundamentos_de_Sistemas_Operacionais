#include <stdio.h>
#include <stdlib.h>

// Função para encontrar a posição de um elemento no array
int find(int *arr, int size, int element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return i;
        }
    }
    return -1;
}

// Função para realizar a rotação de elementos no array
void rotate(int *arr, int start, int size) {
    int temp = arr[start];
    for (int i = start; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
}

// Função para implementar o LRU
void LRU(int *queue, int size, int element) {
    int pos = find(queue, size, element);
    if (pos != -1) {
        rotate(queue, pos, size);
    }
}

int main() {
    int q, pages, pickpage, page_faults = 0;
    scanf("%d %d %d", &q, &pages, &pickpage);

    int *queue = (int *)malloc(q * sizeof(int));
    int size = 0;

    // Inicializando a fila com a primeira página
    queue[size++] = pickpage;
    page_faults++;
    pages--;

    while (pages) {
        scanf("%d", &pickpage);
        int pos = find(queue, size, pickpage);
        if (pos == -1) { // Página não encontrada na fila
            if (size < q) {
                queue[size++] = pickpage;
            } else {
                // Remove a página menos recentemente usada
                for (int i = 1; i < size; i++) {
                    queue[i - 1] = queue[i];
                }
                queue[size - 1] = pickpage;
            }
            page_faults++;
        } else {
            // Atualiza a fila para refletir o acesso recente à página
            LRU(queue, size, pickpage);
        }
        pages--;
    }

    printf("%d\n", page_faults);

    free(queue);
    return 0;
}
