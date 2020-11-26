/*
    filename : client.cpp
    description: 简单聊天室的客户端代码

    1. 根据用户命令行输入， 设置想要连接的服务IP地址和端口。
    2. 根据基于IPv4的数据流方式socket对象。
    3. 向服务器发起连接。
    4. 创建子进程, 子进程阻塞等待服务器端数据， 如果接受到数据，打印该数据。
   父进程阻塞终端，等待终端输入数据。
   
*/
#define MAXBUF 1024
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char**argv)
{
    int sockfd;
    int len;
    struct sockaddr_in dest;    
    char buffer[MAXBUF + 1];

    if( argc != 3 )
    {
        printf("error format,<process parameter's count must > 3");
        exit(-1);
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) != 0)
    {
        perror("socket create error");
        exit(-1);
    }

    printf("socket created\n");
    dest.sin_family = AF_INET;            
    dest.sin_port = htons(atoi(argv[2]));   /*对方端口*/

    /*对方ip地址*/
    if( inet_aton(argv[1], (struct in_addr*)&dest.sin_addr.s_addr) == 0)
    {
        perror(argv[1]);
        exit(-1);
    }


    /* 开始连接 */
    if( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) == -1)
    {
        perror("Connect error: ");
        exit(-1);
    }


    printf("server connected\n");
    pid_t pid;

    if( (pid = fork()) == -1)
    {
        perror("fork");
        exit(-1);
    }
    else if( pid == 0)
    {
        while(1)
        {
            len = recv(sockfd, buffer, MAXBUF, 0);
            if( len > 0)
            {
                printf("recv successful: '%s', %d bytes recv", buffer, len);
            }
            else if( len < 0 )
            {
                perror("recv error");
                break;
            }
            else
            {
                printf("the other one close ,quit\n");
                break;
            }
            
        }
    }
    else
    {
        while(1)
        {
            printf("pls send message to send:");
            fgets(buffer, MAXBUF, stdin);
            if( strcmp(buffer, "quit") == 0)
            {
                break;
            }

            len = send(sockfd,  buffer, strlen(buffer) - 1, 0);
            if( len <  0)
            {
                perror("send error");
                break;
            }
        }
    }
    close(sockfd);
    return 0;
}