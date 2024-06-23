#include<process_copy.h>

int check_pram(int argc,const char * src,int pronum)
{
if(argc!=4){
	return 1;
}
if(access(src,F_OK)){
	return 2;
}
if(pronum>10){
	return 3;
}

return 0;
}
