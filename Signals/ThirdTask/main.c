#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


int main(){
    sigset_t set, oset, pset;
    int sig;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, &oset);
    while(1){
        sigwait(&set, &sig);
        printf("Был получен сигнал\n");
    }
    return 0;
}
