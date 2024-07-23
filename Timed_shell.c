#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/shm.h>

int main(void) {

    char comando[255];
    char argumento[255];
    pid_t pid = 1;
    struct timeval inicio_global, fim_global, inicio_local, fim_local;
    double soma = 0;
    int status;

    gettimeofday(&inicio_global, NULL);

    while(scanf("%s %s", comando, argumento) != EOF) {
        fflush(stdout);
        pid = fork();
        gettimeofday(&inicio_local, NULL);

        if(pid == 0) {
            execl(comando, comando, argumento, NULL);
            if(errno != 0)
                printf("> Erro: %s\n", strerror(errno));
            fflush(stdout);
            int erro = errno;
            fclose(stdin);
            exit(erro);
        }
        else {
            waitpid(pid, &status, WUNTRACED);
            int erro = WEXITSTATUS(status);
            gettimeofday(&fim_local, NULL);

            double tempo_execucao = (fim_local.tv_sec - inicio_local.tv_sec) + 1e-6 * (fim_local.tv_usec - inicio_local.tv_usec);
            printf("> Demorou %0.1lf segundos, retornou %i\n", tempo_execucao, erro);
            fflush(stdout);
        }

    }
    gettimeofday(&fim_global, NULL);

    double tempo_total = (fim_global.tv_sec - inicio_global.tv_sec) + 1e-6 * (fim_global.tv_usec - inicio_global.tv_usec);
    if(pid != 0) printf(">> O tempo total foi de %0.1lf segundos\n", tempo_total);

    return 0;
}
