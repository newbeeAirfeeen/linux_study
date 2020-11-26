/*
    filename   : chat.cpp
    description: implements a chat server

    processflow: 根据用户命令行输入，绑定IP地址，端口以及listen队列的大小
    创建基于IPv4的数据流方式socket对象
    绑定IP地址，监听网络，等待客户连接。

    1.创建套接字
    2.绑定套接字
    3.监听套接字
*/#define MAXBUF 1024
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc, char* argv)
{
    int pid;
    int sockfd, new_fd;
    socklen_t len;
    struct sockaddr_in myaddr;       /*本机IPv4地址*/
    struct sockaddr_in theiraddr;    /*客户端IPv4地址*/

    






    return 0;
}















