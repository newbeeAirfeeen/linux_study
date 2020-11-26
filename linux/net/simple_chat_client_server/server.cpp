/*
    filename   : chat.cpp
    description: implements a chat server
    date :2020/11/26

    processflow: 根据用户命令行输入，绑定IP地址，端口以及listen队列的大小
    创建基于IPv4的数据流方式socket对象
    绑定IP地址，监听网络，等待客户连接。

    1.创建套接字
    2.绑定套接字
    3.监听套接字

    服务端创建一个套接字，就在这个套接字上进行发送和接受消息。
    此程序采用父子进程的方式
*/
#define MAXBUF 1024
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
int main(int argc, char* argv[])
{
    int pid;
    int sockfd, new_fd;
    socklen_t len;
    struct sockaddr_in myaddr;       /*本机IPv4地址*/
    struct sockaddr_in theiraddr;    /*客户端IPv4地址*/
    unsigned int port;               /*端口号*/
    unsigned int lisnum;             /*最大监听队列数*/
    char buf[MAXBUF + 1];            /*缓冲区*/

    
    if( argv[2] )
        port = atoi(argv[2]);        /*读入端口号*/
    else
    {
        port = 7575;    
    }

    if( argv[3] )
    {
        lisnum = atoi(argv[3]);      /*读入最大监听队列数*/
    }
    else
    {
        lisnum = 5;
    }


    /* 创建套接字部分 */


    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) /*创建套接字*/
    {
        perror("socket create error: ");
        exit(-1);
    }


    /* 绑定套接字部分 */


    if( argv[1])  /*将点分十进制字符串转换为网络顺序IP地址*/
        myaddr.sin_addr.s_addr = inet_addr(argv[1]);
    else
    {
        myaddr.sin_addr.s_addr = INADDR_ANY;
    }
    
    myaddr.sin_family = AF_INET;    /*指定协议族*/
    myaddr.sin_port = htons(port);  /*注意要转换为网络序，不为char*的都要转换*/

    if(bind(sockfd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr) == -1))
    {
        perror("bind error");
        exit(-1);
    }


    /* 监听部分 */


    if( listen(sockfd, lisnum) == -1)
    {
        perror("listen error");
        exit(-1);
    }
    printf("wait for connect...\n");




    /*accept部分, 接受连接部分*/



    len = sizeof(struct sockaddr);
    if((new_fd = accept(sockfd, (struct sockaddr*)&theiraddr, &len)) == -1)
    {
        perror("accept error");
        exit(-1);
    }

    printf("server:got connection from %s, port %d, socket %d\n", inet_ntoa(theiraddr.sin_addr), ntohs(theiraddr.sin_port), new_fd);



    //创建新进程去处理连接
    if((pid = fork()) == -1)
    {
        perror("fork error");
        exit(-1);
    }
    else if( pid == 0 )
    {
            /*代表子进程*/

        while(1)
        {
            printf("input the message to send: ");
            fgets(buf, MAXBUF, stdin);
            buf[MAXBUF - 1] = '\0';
            if( strcmp(buf, "quit") == 0)
            {
                break;
            }
            len = send(new_fd, buf, strlen(buf) - 1, 0);
            if( len < 0 )
            {
                printf("message'%s' send fail!\n");
                break;
            }
        }
    }  
    else                                /*父进程用于接收消息*/
    {
        while(1)
        {
            len = recv(new_fd, buf, MAXBUF, 0);
            buf[MAXBUF - 1] = '\0';
            if( len > 0 )
            {
                printf("message recv successful: %s, %d bytes", buf, len);
            }
            else if( len < 0 )
            {
                printf("recv fail! error code: %d, message: %s\n", errno, strerror(errno));
                break;
            }
            else
            {
                printf("the other one choose break");
                break;
            }
            
        }
        
    }
    
    close(new_fd);
    close(sockfd);
    return 0;
}















