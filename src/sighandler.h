#ifndef SIGHANDLER_H
#define SIGHANDLER_H

enum sig_type {
    USR1,
    USR2
};

void handler(int signo);

int init_signal();

int print_signal(enum sig_type msg, int pid);

#endif /*__SIGHANDLER_H__*/