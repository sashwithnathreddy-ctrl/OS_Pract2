#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigint_received = 0;
volatile sig_atomic_t sigterm_received = 0;
volatile sig_atomic_t sigusr1_received = 0;

static void handler(int sig) {
    if (sig == SIGINT) sigint_received = 1;
    else if (sig == SIGTERM) sigterm_received = 1;
    else if (sig == SIGUSR1) sigusr1_received = 1;
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) { perror("sigaction SIGINT"); exit(1); }
    if (sigaction(SIGTERM, &sa, NULL) == -1) { perror("sigaction SIGTERM"); exit(1); }
    if (sigaction(SIGUSR1, &sa, NULL) == -1) { perror("sigaction SIGUSR1"); exit(1); }

    printf("Signal handling program started.\n");
    printf("Process PID = %d\n", getpid());
    printf("\nSend signals using:\n");
    printf("SIGINT  : kill -SIGINT %d\n", getpid());
    printf("SIGTERM : kill -SIGTERM %d\n", getpid());
    printf("SIGUSR1 : kill -SIGUSR1 %d\n", getpid());

    while (1) {
        pause();
        if (sigint_received) {
            printf("\nSIGINT received!\n");
            printf("Interrupt signal handled.\n");
            sigint_received = 0;
        }
        if (sigusr1_received) {
            printf("SIGUSR1 received!\n");
            printf("User-defined event handled.\n");
            sigusr1_received = 0;
        }
        if (sigterm_received) {
            printf("SIGTERM received!\n");
            printf("Termination requested.\n");
            break;
        }
    }
    printf("Program terminating gracefully...\n");
    return 0;
}
