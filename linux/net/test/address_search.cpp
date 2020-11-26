#include<netdb.h>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
using namespace std;
int main()
{
    const char* hostname = "www.baidu.com";
    struct addrinfo hints, *result, *rp;
    int err;
    in_addr addr;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;

    if((err = getaddrinfo(hostname, NULL, &hints, &result)) != 0)
    {
        printf("error %d: %s\n", err, gai_strerror(err));
        return 1;
    }
    for(rp = result; rp != NULL; rp = rp -> ai_next)
    {
        addr.s_addr = ((sockaddr_in*)(rp->ai_addr))->sin_addr.s_addr;
        printf("ip address %s\n", inet_ntoa(addr));
    }










    return 0;
}