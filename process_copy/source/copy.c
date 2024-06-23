#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>


int main(int argc,char **argv){
if(argc!=5){
	printf("进程参数错误\n");
	return 0;
}
int blocksize=atoi(argv[3]);
int pos=atoi(argv[4]);
int fd_src=open(argv[1],O_RDONLY);
int fd_dest=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0664);
char readbuf[1024];
int len=0;
int size2=lseek(fd_dest,(pos-blocksize),SEEK_SET);//移动下标
int size=lseek(fd_src,pos,SEEK_SET);
printf("当前下标为:%d,工作:%d\n",size2,blocksize);
len=read(fd_src,readbuf,blocksize);
if(len==-1)
{
	printf("读取错误\n");
	return 1;
}else{
	write(fd_dest,readbuf,len);//写入文件
}

close(fd_src);
close(fd_dest);
return 0;
}
