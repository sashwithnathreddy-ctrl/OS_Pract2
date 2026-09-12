#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3

int main() {
    pid_t child_pid[NUM_CHILDREN];
    pid_t pid;
    int status;

    printf("Parent Process: PID = %d\n\n", getpid());

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            printf("Child %d: PID = %d, PPID = %d\n", i + 1, getpid(), getppid());
            sleep(1);
            exit((i + 1) * 10);
        } else {
            child_pid[i] = pid;
        }
    }

    printf("\n--- Using wait() ---\n");
    pid = wait(&status);
    if (pid > 0 && WIFEXITED(status)) {
        printf("wait(): Child PID %d terminated with exit status %d\n",
               pid, WEXITSTATUS(status));
    }

    printf("\n--- Using waitpid() ---\n");
    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (child_pid[i] == pid) continue;
        pid = waitpid(child_pid[i], &status, 0);
        if (pid > 0 && WIFEXITED(status)) {
            printf("waitpid(): Child PID %d terminated with exit status %d\n",
                   pid, WEXITSTATUS(status));
        }
    }

    printf("\nParent: All children have completed.\n");
    return 0;
}
