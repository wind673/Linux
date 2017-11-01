#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


void print_msg(char *ptr);
int cnt = 0;

int main()
{
    pthread_t thread1, thread2;
    int i, j;
    char msg1[32] = "  do sth1\n";
    char msg2[32] = "  do sth2\n";
	msg1[0] = 1;
	msg2[0] = 2;
    pthread_create(&thread1, NULL, (void *)(&print_msg), (void *)msg1);
    pthread_create(&thread2, NULL, (void *)(&print_msg), (void *)msg2);
    while(1)sleep(10);
    return 0;
}

void print_msg(char *ptr)
{
    int retval;
    int id = pthread_self();
	
	while(1)
	{
		if(ptr[0] == 1)cnt ++;
		else if(ptr[0] == 2)cnt --;
		
		printf("Thread ID: %x\n", id); 
		printf("%s\n", ptr);
		printf("%d\n", cnt); 
		printf("------------------\n\n"); 
		//pthread_exit(&retval);	
		usleep(100);
		
		
		
	}
}




