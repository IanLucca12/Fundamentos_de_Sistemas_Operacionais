#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int counter = 0;

void signalHandler(int signal);

int main() {

    signal(SIGUSR1, signalHandler); // Intercepta sinal 10

    signal(SIGUSR2, signalHandler); // Intercepta sinal 12

    while(1) {
        // Mantém o programa em execução
    }

    return 0;
}

void signalHandler(int signal) {

    if(signal == 10) {
        if(counter == 2) {
            exit(0);
        }
        if(counter == 1) {
            counter++;
            wait(NULL);
        }
        if(counter == 0) {
            counter++;
            if(fork() == 0) exit(0);
        }
    }

    if(signal == 12) {
        if(counter == 2) {
            exit(0);
        }
        if(counter == 1) {
            counter++;
            wait(NULL);
        }
        if(counter == 0) {
            counter++;
            if(fork() == 0) exit(0);
        }
    }
}
