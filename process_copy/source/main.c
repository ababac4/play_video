#include<process_copy.h>

int main(int argc,char **argv)
{
  int pronum;
  int blocksize;
  if(argv[3]==0)
{
	pronum=5;
}
  else{
	  pronum=atoi(argv[3]);
  }
	  int res=check_pram(argc,argv[1],pronum);
	  if(res==1)
	  {
		printf("参数缺少\n");
		  return 0;
	  }else if(res==2){

		  printf("目标文件不存在\n");
		  return 0;
	  }else if(res==3){
		  printf("进程创建太多\n");
		  return 0;
}
		  else{
			  printf("输入成功`\n");
	  blocksize=blocksize_cur(argv[1],pronum);
	  process_create(argv[1],argv[2],pronum,blocksize);
		  }

return 0;
}
