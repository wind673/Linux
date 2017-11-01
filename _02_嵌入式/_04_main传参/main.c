#include <stdio.h>
#include <string.h>

int main(int arg,char *argc[])
{
	int i = 0;
	
	printf("\n ---------------------------------------------------- \n");
	
	for(i = 0;i < arg;i++)
		printf("\n\n %d  \n\n %s \n\n",arg,argc[i]);
		
	printf("\n ---------------------------------------------------- \n"); 
	
	while(1);
	return 0;
}


/*
					说明
					
	第一个参数传递的是参数的个数，后面的数组就是参数；
在linux下，若使用./test/main 1 2 
则arg = 3；分别是 “./test/main” ， "1”， "2";
传递的都是字符串，如此就可以理解了。 
	 

*/


