#include "minishell.h"
#include <signal.h>
#include <stdio.h>

void handle_signals(int sig, siginfo_t *info, void *vp)
{
    (void) info;
    (void) vp;
    if(sig == SIGQUIT)
    {
        // printf("QUIT\n");
        return;
    }
    if(sig == SIGINT)
    {
        // kill(-1, SIGINT);
        // while(wait(NULL) > 0);
        return;
    }
}

void init_signal(t_args *vars)
{
    struct sigaction sa;
    (void) vars;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signals;

    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}