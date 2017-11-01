#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 		4096
#define SERVER_PORT 	6060


int main(int argc, char **argv)
{
    int     sockfd , recv_len ;
    char    str_send[MAXLINE] , str_recv[MAXLINE];
    struct  sockaddr_in in_server;


    if( argc != 2)//argv[0]是调用者的名字，argv[1]是第一个参数。argc是参数的个数（包括argv[0]）
    {
        printf("usage: ./client <ipaddress>\n");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //创建socket。AF_INET表示IPV4，SOCK_STREAM表示建立有序且无误的通讯
    if(sockfd < 0)
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    //在这里填写servaddr的相关内容
    memset(&in_server, 0, sizeof(in_server)); //将in_server前 sizeof(in_server) 个字节设为0；即将in_server清零
    in_server.sin_family = AF_INET;//AF_INET表示IPV4
    in_server.sin_port = htons(SERVER_PORT);//端口6060，htons用来统一转换成网络字节顺序

    if(inet_pton(AF_INET, argv[1], &in_server.sin_addr) < 0)//转换网络地址格式
    {
        printf("inet_pton error for %s\n", argv[1]);
        exit(0);
    }
	 
    if(connect(sockfd, (struct sockaddr *)&in_server, sizeof(in_server)) < 0)//用上面创立的sockfd，servaddr建立连接
    {
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
	 
    printf("send msg to server: \n");
    fgets(str_send, MAXLINE, stdin);//获取键盘输入，换行结束。
    if(send(sockfd, str_send, strlen(str_send), 0) < 0)
    {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    if((recv_len = recv(sockfd, str_recv, MAXLINE, 0)) < 0)
    {
        perror("recv error");
        exit(1);
    }
    str_recv[recv_len]  = '\0';
    printf("Received : %s ", str_recv);
	
    close(sockfd);
    exit(0);
}


