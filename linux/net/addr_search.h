/**
 * 地址查询
 * 网络配置信息被存放在许多地方。
 * /etc/hosts
 * /etc/services
 * 
 * 
 * 头文件: netdb.h
 * 
 * 
*/
/*若成功，返回指针，若失败返回NULL*/
struct hostnet* gethostent(void);
void  sethostent(int stayopen);
void  endhostent(void);