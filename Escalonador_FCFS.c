#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    unsigned int id, i;
    int* instruction;
} Process;

typedef struct Queue {
    Process* processes;
    int front, rear, size, capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->processes = (Process*)malloc(queue->capacity * sizeof(Process));
    return queue;


}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, Process process) {
    if (isFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->processes[queue->rear] = process;
    queue->size = queue->size + 1;
}

Process dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        Process dummy = {0, 0, NULL};
        return dummy;
    }
    Process process = queue->processes[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return process;
}

int main() {
    unsigned int n, instruction, acc = 0;
    scanf("%d", &n);

    Process* processes = (Process*)malloc(sizeof(Process) * n);
    Queue* queue = createQueue(n);

    for (unsigned int i = 0; i < n; i++) {
        scanf("%d", &processes[i].i);
        processes[i].id = i + 1;
        processes[i].instruction = (int*)malloc(sizeof(int) * processes[i].i);
    }

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < processes[i].i; j++) {
            scanf("%d", &instruction);
            processes[i].instruction[j] = instruction;
        }
        enqueue(queue, processes[i]);
    }

    while (!isEmpty(queue)) {
        unsigned int i = 0;
        Process cp = dequeue(queue);
        while (cp.i != 0 && cp.instruction[i] != 1) {
            cp.i--;
            acc += 10;
            i++;
        }

        if (cp.i == 0) {
            printf("%d (%d)\n", cp.id, acc);
        } else {
            cp.instruction[i] = 0;
            for (unsigned int j = 0; j < cp.i; j++) {
                cp.instruction[j] = cp.instruction[i++];
            }
            enqueue(queue, cp);
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        free(processes[i].instruction);
    }
    free(processes);
    free(queue->processes);
    free(queue);

    return 0;
}
