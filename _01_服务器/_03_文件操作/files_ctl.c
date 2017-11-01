#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

int main()
{
    int fd, size;
    char s[100] = "Linux Programmer!\n", buffer[800];
    fd = open("/mywork/files_ctl/temp.txt", O_RDWR|O_CREAT|O_APPEND); 
    write(fd, s, strlen(s));
    close(fd);
    fd = open("/mywork/files_ctl/temp.txt", O_RDWR|O_CREAT|O_APPEND);
    size = read(fd, buffer, sizeof(buffer));
    close(fd);
    printf("%s",buffer);
	return 0;
}



