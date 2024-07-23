#include <stdio.h>
#include <stdlib.h>

int isInQueue(int *queue, int size, int page) {
    for (int i = 0; i < size; i++) {
        if (queue[i] == page) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int q, pages, pickpage, page_faults = 0;
    scanf("%d %d %d", &q, &pages, &pickpage);

    int *queue = (int *)malloc(q * sizeof(int));
    int front = 0, rear = 0, size = 0;

    queue[rear] = pickpage;
    rear = (rear + 1) % q;
    size++;
    page_faults++;
    pages--;

    while (pages) {
        scanf("%d", &pickpage);
        if (!isInQueue(queue, size, pickpage)) {
            if (size != q) {
                queue[rear] = pickpage;
                rear = (rear + 1) % q;
                size++;
            } else {
                queue[front] = pickpage;
                front = (front + 1) % q;
                rear = (rear + 1) % q;
            }
            page_faults++;
        }
        pages--;
    }

    printf("%d\n", page_faults);

    free(queue);
    return 0;
}
