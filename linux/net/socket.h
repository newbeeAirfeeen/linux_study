
#include<bits/types.h>
/*
    大端序和小端序: 大端->最高有效字节放在最前面。
                  小端->最低有效字节放在最前面。

*/
/* 原型为: socket
 * 头文件：sys/socket.h
 * 
 * @description : 获得与open类似的文件操作符。
 * @param domain: AF_INET    -IPV4因特网
 *                AF_INET6   -IPV6因特网 
 *                AF_UNIX    -UNIX域
 *                AF_UPSPEC  -未指定
 * 
 * @param type  : SOCK_DGRAM  固定长度的，无连接，不可靠的报文传递 -- UDP
 *                SOCK_STREAM tcp
 *                SOCK_RAW 
 *                SOCK_SEQPACKET
 * @param protocol 通常是0, 默认协议
 * 
 * 成功返回0, 出错返回-1。
**/
int socket(int domain, int type, int protocol);

/*
 * @description : 禁用一个套接字的读或写。
 * @param sockfd: 套接字文件描述符
 * @param how   : SHUT_RD 关闭读端
 *                SHUT_WR 关闭写端
 *                SHUT_RDWR 读写关闭
 * 相比与close, close需要等所有文件描述符的引用全部释放，才关闭此文件描述符。
**/
int shutdown(int sockfd, int how);



/*
    地址格式
    为使不同的地址格式能够传入到套接字函数，地址会被强制转换成一个通用的地址
    struct sockaddr
*/
/*
struct sockaddr
{
    sa_family_t sa_family;
    char        sa_data[];
    //...
    //..
};*/

/*
    因特网地址在头文件 netinet/in.h 头文件中

*/
//IPv4
/*
struct in_addr
{
    in_addr_t  s_addr;  // IPv4 address //
};
套接字用
struct sockaddr_in
{
    sa_family_t     sin_family;
    in_port_t       sin_port;
    struct in_addr  sin_addr;  IPv4 address
};
表示
*/

/*
    IPv6
    用
    struct in6_addr
    {
        uint8_t s6_addr[16]; IPv6
    };
    struct sockaddr_in6
    {
        sa_family_t     sin_family; address family
        in_port_t       sin_port;   port number
        uint32_t        sin6flowinfo;   
        ...
        ..
        ..
    };


    两类地址最后会被转成sockaddr类型以便函数调用
*/



/*  一般用于地址格式的转换 */
/*
    网络字节序
    头文件: arpa/inet.h
*/
/*
 h : host 
 n : net
 l : long 4字节
  h to nl 代表主机到网络地址的转换
*/
using int32 = unsigned int;
using int16 = unsigned short;

int32 htonl(int32 hostint32);
int32 ntohl(int32 netint32);
int16 htons(int16 hostinit16);
int16 ntohs(int16 netint16);

//将网络字节序的二进制地址转换成字符串格式
/*@param domain: AF_INET 
                 AF_INET6
  @param size  : INET_ADDRSTRLEN 
                 INET6_ADDRSTRLEN
                 指定了足够大的长度               
*/        
//成功返回指针，失败返回NULL        
const char* inet_ntop(int domain, const void*  _addr, char*  str, __socklen_t size);
//成功返回0, 失败返回-1, 1为格式无效
int inet_pton(int domain, const char* str, void*  addr);





















