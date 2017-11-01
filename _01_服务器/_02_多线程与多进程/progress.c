#include<unistd.h>  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

int main(void)  
{  
    pid_t pid;  

	pid = fork(); 
	if(pid < 0)  
	{  
		perror("fork");  
		exit(1);  
	}  
	else if(pid == 0) //子进程中  
	{  
		printf("\n in child \n");   
		printf("tchild pid = %d\n",getpid());  	
		printf("tchild ppid = %d\n",getppid());  	
		if(execl("/mywork/progress/server", "server",(char*)0) < 0)//转换成服务器进程
		{
			perror("execl");  
			exit(1);  
		}
	}  
	else   //父进程   
	{   
		printf("\n in parent \n");   
		printf("tparent pid = %d\n",getpid());  	
		printf("tparent ppid = %d\n",getppid());  	
		wait(NULL);
	}  
	
}  


