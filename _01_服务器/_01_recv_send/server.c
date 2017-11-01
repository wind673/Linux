#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define SERVER_PORT 6060
#define MAXLINE 4096

int main(int argc, char **argv)
{
    int     socket_fd ,connect_fd ,n;
    struct  sockaddr_in in_client ,in_server;
    char    str_recv[4096],str_addr_client[INET_ADDRSTRLEN]; 
    socklen_t len;
	
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);//初始化Socket
    if(socket_fd < 0)
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
    
	//设置servaddr的内容
    memset(&in_server, 0, sizeof(in_server));
    in_server.sin_family = AF_INET;
    in_server.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。
    in_server.sin_port = htons(SERVER_PORT);//设置的端口为DEFAULT_PORT

    //将本地地址绑定到所创建的套接字上
    if(bind(socket_fd, (struct sockaddr *)&in_server, sizeof(in_server)) < 0)
    {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
	
    //开始监听是否有客户端连接
    if(listen(socket_fd, 10) < 0)//参数二：backlog参数的大小，决定了TCP服务器的连接请求队列大小
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }
	
    printf("======waiting for client's request======\n");
	
    while(1)
    { 
		len = sizeof(in_client);
        if((connect_fd = accept(socket_fd, (struct sockaddr *)&in_client, &len)) < 0) //accept 里面是个死循环，起到阻塞作用
        {
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
            continue;	
        }
		
		//打印客户端信息
		inet_ntop(AF_INET,&in_client.sin_addr,str_addr_client,sizeof(str_addr_client));   
        printf("client ip:%s,port:%d\n",str_addr_client,ntohs(in_client.sin_port));  
		
        n = recv(connect_fd, str_recv, MAXLINE, 0); //接受客户端传过来的数据
        str_recv[n] = '\0';
		
        if(send(connect_fd, str_recv, 26, 0) < 0) //向客户端发送回应数据
            perror("send error");
		   
        printf("recv msg from client: %s\n", str_recv);
        close(connect_fd);
    }
    close(socket_fd);
}





