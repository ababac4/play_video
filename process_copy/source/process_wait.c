#include<process_copy.h>

int process_wait(void){
	printf("回收进程\n");
	wait(NULL);
return 0;
}
