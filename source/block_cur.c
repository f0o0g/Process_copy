#include "process_copy.h"

//切片
int block_cur(const char * srcfile,int pronum)
{
    struct stat st;
    stat(srcfile,&st);
    int filesize = st.st_size;
    if(filesize % pronum == 0)
    {
        return filesize / pronum;
    }
    return (filesize / pronum) + 1;
}