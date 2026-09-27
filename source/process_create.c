#include"process_copy.h"

//创建子进程
int process_create(const char * srcfile,const char * destfile,int pronum,int blocksize)
{
    int i;
    pid_t pid;
    char str_offset[100];
    char str_blocksize[100];
    for(i = 0;i < pronum;i++)
    {
        pid =fork();
        if(pid == 0)
            break;
    }

    if(pid > 0)
        process_wait();//父进程循环回收
    else if(pid == 0)
    {
        sprintf(str_offset,"%d",i * blocksize);
        sprintf(str_blocksize,"%d",blocksize);
        execl("/home/ubuntu/projects/process_copy/MOD/copy","copy",srcfile,destfile,str_offset,str_blocksize,NULL);

        exit(0);
    }
    else
        return 0;

    return 1;
}