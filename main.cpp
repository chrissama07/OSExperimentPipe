#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>

int pid1, pid2;

int main() {
    int fd[3];
    char OutPipe[100], InPipe[100];
    pipe(fd);
    while((pid1 = fork()) == -1);
    if(pid1 == 0) {
        printf("p1\n");
        lockf(fd[1], 1, 0);
        sprintf(OutPipe, "Children 1 process is sending a message!!");
        write(fd[1], OutPipe, 50);
        sleep(1);
        lockf(fd[1], 0, 0);
        _exit;
    } else {
        while((pid2 = fork()) == -1);
        if(pid2 == 0) {
            printf("p2\n");
            lockf(fd[1], 1, 0);
            sprintf(OutPipe, "Children 2 process is sending a message!!");
            write(fd[1], OutPipe, 50);
            sleep(1);
            lockf(fd[1], 0, 0);
            _exit;
        } else {
            printf("parent\n");
            wait(0);
            read(fd[0], InPipe, 50);
            printf("%s\n", InPipe);
            wait(0);
            read(fd[0], InPipe, 50);
            printf("%s\n", InPipe);
            _exit;
        }
    }
    return 0;
}
