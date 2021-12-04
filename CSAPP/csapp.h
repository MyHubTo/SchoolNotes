#ifndef _CSAPP_H_
#define _CSAPP_H_

#include <iostream>
#include <string>
#include <vector>
extern "C"
{
    #include <unistd.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/socket.h>
    #include <netdb.h>
}

using namespace std;

#define MAXLINE 1024

#define LISTENQ 1024
//!---------------------------------------------RIO(I/O)--------------------------------------------------
/**
* @brief RIO(Robus I/O) CSAPP -page 626
* 在某些情况下,UNIX 下的 read(),write()传送的字节顺序要比程序要求的少,这些不足值不表示错误,主要由以下几种原因组成:
* 1. 读时遇到EOF(end of file);
* 2. 从终端读文本行;
* 3. 读和写网络套接字;

* 在像网络编程中,容易出现不足值的应用中,RIO可以高效的处理这些不知足值.
* 1. 无缓冲的的输入输出函数: 这些函数直接在内存和文件之间传送数据,没有应用级缓冲.他们对将二进制数据读写到网络和从网络
*    读写二进制数据尤其重要;
* 2. 带缓冲的的输入输出函数: 这些函数允许你高效的从文件中读取文本行和二进制数据,这些文件的内容缓存在应用级缓冲区内.
**/

/**
 * @param RIO_BUFSIZE 内部缓冲区大小
 * **/
#define RIO_BUFSIZE 8192 /*内部缓冲区大小*/

/**
 * @param rio_fd     内部缓冲区描述符
 * @param rio_cnt    内部缓冲区未读字节数
 * @param rio_bufptr 内部缓冲区中的下一个未读字节
 * @param rio_buf    内部缓冲区
 * **/
typedef struct
{
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
} rio_t;

//! 无缓冲的的输入输出函数:
/**
 * @brief 从文件描述符 fd 的当前文件位置最多传送n个字节到内存位置 usrbuf.
 * @param fd 文件描述符;
 * @param usrbuf 缓冲区;
 * @param n 缓冲区大小;
 * @return 若成功则返回传送的字节数,若EOF则为0,若出错返回-1;
 * **/
ssize_t rio_readn(int fd, void *usrbuf, size_t n);

/**
 * @brief 从位置usrbuf 传送 n个字节到描述符fd;
 * @param fd 文件描述符;
 * @param usrbuf 缓冲区;
 * @param n 缓冲区大小;
 * @return 若成功则返回传送的字节数,若出错返回-1;
 * **/
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

//!带缓冲的的输入输出函数

/**
 * @brief 初始化,将描述fd和地址rp处的一个类型为rio_t 的读缓冲区联系起来;
 * @param rp rio_t 类型指针;
 * @param fd 文件描述符;
 * @return 无;
 * **/
void rio_readinitb(rio_t *rp, int fd);

/**
 * @brief 从文件rp 读出下一个文本行(包括结尾的换行符),将它复制到内存位置为usrbuf,并且用NULL字符来结束这个文本行.
 * rio_readinitb 最多读取maxlen-1 个字节,最后一个字节用于NULL;
 * @param rp rio_t 类型指针;
 * @param usrbuf 缓冲区;
 * @param maxlen 最大长度;
 * @return 若成功则为读取的字节数,若EOF则为0,若出错则为-1;
*/
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/**
 * @brief 从文件rp 最多读取 n 个字节到内存位置 usrbuf
 * @param rp rio_t 类型指针;
 * @param usrbuf 缓冲区;
 * @param n 最大读取字节数;
 * @return 若成功则为读取的字节数,若EOF则为0,若出错则为-1;
*/
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);


//!---------------------------------------------read metadata--------------------------------------------
//!获取文件信息


/**
 * 1. stat();
 * 2. fstat();
*/
//  struct stat {
//                dev_t     st_dev;         /* ID of device containing file */
//                ino_t     st_ino;         /* inode number */
//                mode_t    st_mode;        /* protection */
//                nlink_t   st_nlink;       /* number of hard links */
//                uid_t     st_uid;         /* user ID of owner */
//                gid_t     st_gid;         /* group ID of owner */
//                dev_t     st_rdev;        /* device ID (if special file) */
//                off_t     st_size;        /* total size, in bytes */
//                blksize_t st_blksize;     /* blocksize for filesystem I/O */
//                blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

//                 Since Linux 2.6, the kernel supports nanosecond
//                   precision for the following timestamp fields.
//                   For the details before Linux 2.6, see NOTES.

//                struct timespec st_atim;  /* time of last access */
//                struct timespec st_mtim;  /* time of last modification */
//                struct timespec st_ctim;  /* time of last status change */

/**
 * @brief 获取文件大小(字节)
*/
int filesize(const string filename);

/**
 * @brief 上次修改时间
*/
string last_modification_time(const string filename);

/**
 * @brief 上一次状态改变时间
*/
string last_status_change_time(const string filename);

/**
 * @brief 上一次访问时间
*/
string last_access_time(const string filename);

//!--------------------------------------------- DIR -----------------------------------------------------
//!获取指定目录下的所有文件名

/**
 * @brief 获取指定路径下的所有文件名
*/
vector<string> getfiles_name(const string filename);

/**
 * @brief 获取指定路径下的所有绝对路径文件名
*/
vector<string> getfiles_name_with_path(const string filename);


//!--------------------------------------------- INTERNET ------------------------------------------------

/**
 * @brief 建立与服务器的连接,返回一个打开的套接字的描述符
 * @param hostname 主机名
 * @param port 端口号
 * @return 若成功返回套接字文件描述符,否则返回-1;
*/
int open_clientfd(char *hostname,char *port);

/**
 * @brief 服务器创建一个监听的文件描述符,准备好接收连接请求
 * @param port 端口号
 * @return 若成功返回监听文件描述符,否则返回-1;
*/
int open_listenfd(char *port);
#endif