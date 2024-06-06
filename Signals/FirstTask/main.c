#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void siguser(int sig, siginfo_t *info, void *ucontext){
    int signum = info->si_signo;
    pid_t pid = info->si_pid;
    printf("сигнал %d был получен от %d\n", signum, pid);
}

int main(){
    struct sigaction action;
    memset(&action, 0 ,sizeof(action));

    action.sa_sigaction = siguser;
    action.sa_flags |= SA_SIGINFO;
    sigaction(SIGUSR1, &action, NULL);
    while(1){

    }
    return 0;
}
