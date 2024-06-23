#include<process_copy.h>


int process_create(const char * src,const char *dest,int pronum,int blocksize){

printf("进程创建:%d\n",pronum);
 pid_t pid;
 pid_t fpid=getpid();
for(int i=0;i<pronum;i++){
   pid=fork();
  if(pid==0)
	{  
	  break;
	  }
}
if(pid>0)
{
 process_wait();
}
else if(pid==0){
	char *blo_buf[20];
	char *pos_buf2[20];
int pos=blocksize*(getpid()-fpid);
sprintf(pos_buf2,"%d",pos);
sprintf(blo_buf,"%d",blocksize);
execl("/home/colin/20230912/folktest/process_copy/source/copy","copy",src,dest,blo_buf,pos_buf2,NULL);
}

return 0;
}
