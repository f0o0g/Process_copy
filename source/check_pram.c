#include"process_copy.h"

//参数验证
int check_pram(int argc,const char * srcfile,int pronum)
{
    if(argc < 3)
    {
        printf("参数错误\n");
        return 0;
    }
    if(access(srcfile,F_OK) == -1)
    {   
        printf("文件不存在\n");
        return 0;
    }
    if(pronum < 3||pronum > 100)
    {
        printf("进程数错误\n");
        return 0;
    }

    return 1;
}