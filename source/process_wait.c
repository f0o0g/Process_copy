#include"process_copy.h"

//父进程循环回收
void process_wait(void)
{
    pid_t pid;
    while((pid = waitpid(-1,NULL,WNOHANG)) != -1)
    {
        if(pid > 0)
            printf("子进程%d已回收\n",pid);
    }
}