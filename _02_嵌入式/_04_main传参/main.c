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
					˵��
					
	��һ���������ݵ��ǲ����ĸ����������������ǲ�����
��linux�£���ʹ��./test/main 1 2 
��arg = 3���ֱ��� ��./test/main�� �� "1���� "2";
���ݵĶ����ַ�������˾Ϳ�������ˡ� 
	 

*/


