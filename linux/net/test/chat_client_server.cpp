#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
char buf[256];



void* _recv(void* arg)
{
    while(true)
    {
        char buff[265];
        int res = recv(*(int*)arg, buff, sizeof(buf),0);
        if( res <= 0)
        {
            perror("recv error: ");
            exit(-1);
        }
        printf("recv: %s\n", buff);
    }
}


void* _send(void* arg)
{
    while(true)
    {
        char buff[265];
        fgets(buff, sizeof(buff), stdin);
        int res = send(*(int*)arg, buff, sizeof(buf),0);
        if( res <= 0)
        {
            perror("send error: ");
            exit(-1);
        }
       // printf("recv: %s\n", buff);
    }
}



const char* getIPaddr(const char* name, int family, int port, const char* service)
{

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    int result = getaddrinfo(name, service, &hints, &res);
    if( result != 0 )
    {
        printf("get ip error: %s\n", gai_strerror(result));
    }
    for(struct addrinfo* iter = res; iter != NULL; iter=iter->ai_next)
    {
        struct sockaddr_in* addrip = (struct sockaddr_in*)(iter->ai_addr);
        inet_ntop(AF_INET, &(addrip->sin_addr), buf, sizeof(sockaddr_in));
    }
    return buf;
}

int main()
{

    //创建端口

    int sockfd;
    int ip;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    

    getIPaddr("localhost",AF_INET, 8080, NULL);
    int res1 = inet_pton(AF_INET, buf, &ip);

    struct sockaddr_in addrin;
    addrin.sin_port = 8080;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = ip;
    //绑定地址
    if(bind(sockfd, (struct sockaddr*)&addrin, sizeof(sockaddr_in)) != 0)
    {
        perror("bind error: ");
        exit(-1);
    }



    //监听地址
    int res = listen(sockfd, 10);
    if( res != 0)
    {
        perror("listen error");
        exit(-1);
    }


    //接受连接
    struct sockaddr_in clientaddr;
    socklen_t len;
    int clientfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);


    //小于0出错， 0 格式无效
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, buf, sizeof(sockaddr_in));
    //打印客户端的信息
    printf("accept: %s\n", buf);

    pthread_t serverpit, sendpit;
    res = pthread_create(&serverpit, NULL, _recv, (void*)&clientfd);
    res = pthread_create(&sendpit, NULL, _send, (void*)&clientfd);


    pthread_join(serverpit, NULL);
    pthread_join(sendpit, NULL);


    return 0;
}
