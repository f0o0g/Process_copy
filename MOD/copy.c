#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>

int main(int argc,char *argv[])
{
    int sfd;//源地址
    int dfd;//目标地址
    int offset = atoi(argv[3]);//偏移量
    int blocksize = atoi(argv[4]);//块大小  
    
    if((sfd = open(argv[1],O_RDONLY)) == -1)
        perror("open srcfile,failed");
    if((dfd = open(argv[2],O_WRONLY|O_CREAT,0664)) == -1)
        perror("open destfile,failed");
    
    //跳转偏移量
    lseek(sfd,offset,SEEK_SET);
    lseek(dfd,offset,SEEK_SET);

    char buffer[blocksize];
    int len;
    printf("child p %d execl Copy,offect %d,blocksize %d\n",getpid(),offset,blocksize);
    //读写操作
    len = read(sfd,buffer,sizeof(buffer));
    write(dfd,buffer,len);
    close(sfd);
    close(dfd);

    return 0;
}