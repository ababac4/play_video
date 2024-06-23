#include<process_copy.h>


int blocksize_cur(const char * src,int pronum)
{
	int fd = open(src,O_RDWR|O_CREAT,0664);
	int len=lseek(fd,0,SEEK_END);
	printf("文件大小为：%d\n",len);
    int block_size=len/pronum;
	printf("每个进程工作：%d\n",block_size+1);
return block_size+1;
}
