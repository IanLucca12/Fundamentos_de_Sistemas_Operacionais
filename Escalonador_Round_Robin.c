#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id; // Identificador do processo
    int time; // Tempo restante de execução do processo em milissegundos
} Process;

int Quantum;

void solve(Process v[], int N) {
    int run = 0, actual = 0, max = N - 1;
    while (max > 0) {
        run += Quantum;
        v[actual].time -= Quantum;

        if (v[actual].time <= 0) {
            // Corrigir o tempo
            run += v[actual].time;
            printf("%d (%d)\n", v[actual].id, run);

            // Deslocar o vetor
            for (int i = actual; i < max; i++) {
                v[i] = v[i + 1];
            }
            max--;
        } else {
            actual++;
        }

        if (actual == max + 1) {
            actual = 0;
        }
    }

    // Otimizar o último
    printf("%d (%d)\n", v[0].id, v[0].time + run);
}

int main() {
    int N;
    scanf("%d", &N); // Número de processos
    Process v[N];
    scanf("%d", &Quantum); // Definir o quantum

    for (int i = 0; i < N; i++) {
        Process p;
        scanf("%d %d", &p.id, &p.time); // Ler o identificador e o tempo de execução
        p.time *= 1000; // Converter para milissegundos
        v[i] = p;
    }

    solve(v, N);

    return 0;
}
