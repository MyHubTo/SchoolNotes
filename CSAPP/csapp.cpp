#include "csapp.h"
#include <algorithm>
extern "C"
{
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
}
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = static_cast<char *>(usrbuf);

    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, nleft)) < 0)
        {
            if (errno == EINTR) /* 信号中断 */
            {
                nread = 0;
            }
            else
            {
                return -1; /*error set by read()*/
            }
        }
        else if (nread == 0)
        {
            break; /*EOF*/
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft); /*return >=0*/
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = static_cast<char *>(usrbuf);

    while (nleft > 0)
    {
        if ((nwritten = write(fd, bufp, nleft)) <= 0)
        {
            if (errno == EINTR) /* 信号中断 */
            {
                nwritten = 0;
            }
            else
            {
                return -1;
            }
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;
    while (rp->rio_cnt <= 0) /*refil buffer if buffer is empty*/
    {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));

        if (rp->rio_cnt < 0)
        {
            if (errno != EINTR)
            {
                return -1;
            }
        }
        else if (rp->rio_cnt == 0)
        {
            return 0; /* EOF */
        }
        else
        {
            rp->rio_bufptr = rp->rio_buf; /*reset buffer ptr*/
        }
    }

    cnt = n;
    if (rp->rio_cnt < n)
    {
        cnt = rp->rio_cnt;
    }

    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = static_cast<char *>(usrbuf);

    for (n = 1; n < maxlen; n++)
    {
        if ((rc = rio_read(rp, &c, 1)) == 1)
        {
            *bufp++ = c;
            if (c == '\n')
            {
                n++;
                break;
            }
        }
        else if (rc == 0)
        {
            if (n == 1)
            {
                return 0; /* EOF ,no data read*/
            }
            else
            {
                break; /* EOF ,some data was read*/
            }
        }
        else
        {
            return -1; /*Error*/
        }
    }
    *bufp = 0;
    return n - 1;
}

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = static_cast<char *>(usrbuf);

    while (nleft > 0)
    {
        if ((nread = rio_read(rp, bufp, nleft)) < 0)
        {
            return -1; /*errno set by read()*/
        }
        else if (nread == 0)
        {
            break; /* EOF */
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

int filesize(const string filename)
{
    struct stat buf;
    int re = stat(filename.c_str(), &buf);
    return buf.st_size;
}

string last_modification_time(const string filename)
{
    struct stat buf;
    int re = stat(filename.c_str(), &buf);
    struct timespec time = buf.st_mtim;
    string lastTime = asctime(localtime(&time.tv_nsec));
    return lastTime;
}

string last_status_change_time(const string filename)
{
    struct stat buf;
    int re = stat(filename.c_str(), &buf);
    struct timespec time = buf.st_ctim;
    string lastchange = asctime(localtime(&time.tv_nsec));
    return lastchange;
}
string last_access_time(const string filename)
{
    struct stat buf;
    int re = stat(filename.c_str(), &buf);
    struct timespec time = buf.st_atim;
    string lastaccess = asctime(localtime(&time.tv_nsec));
    return lastaccess;
}

vector<string> getfiles_name(const string filename)
{
    vector<string> names;
    string name;
    errno = 0;
    DIR *dir = opendir(filename.c_str());
    dirent *dirent_;

    while ((dirent_ = readdir(dir)) != NULL)
    {
        name = dirent_->d_name;
        if ((name == ".") || (name == ".."))
        {
            continue;
        }
        names.push_back(name);
    }

    if (errno != 0)
    {
        perror("readdir error");
    }
    return names;
}
vector<string> getfiles_name_with_path(const string filename)
{
    vector<string> names;
    string name;
    int i;
    names = getfiles_name(filename);

    for (i = 0; i < names.size(); i++)
    {
        names[i] = filename + "/" + names[i];
    }
    return names;
}

int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    addrinfo *p, *listp, hints;
    char buf[MAXLINE];

    memset(&hints, 0, sizeof(addrinfo));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;

    // hints.ai_family=AF_INET;

    getaddrinfo(hostname, port, &hints, &listp);

    for (p = listp; p; p = p->ai_next)
    {
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
        {
            continue;
        }
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
        {
            break;
        }
        close(clientfd);
    }

    freeaddrinfo(listp);
    if (!p)
    {
        return -1;
    }
    else
    {
        return clientfd;
    }
}

int open_listenfd(char *port)
{
    addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    memset(&hints, 0, sizeof(addrinfo));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;

    // cout<<p->ai_family<<endl;

    getaddrinfo(NULL, port, &hints, &listp);

    for (p = listp; p; p = p->ai_next)
    {
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
        {
            continue;
        }
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
        {
            break;
        }

        close(listenfd);
    }

    freeaddrinfo(listp);
    if(!p)
    {
        return -1;
    }
    if(listen(listenfd,LISTENQ)<0)
    {
        close(listenfd);
        return -1;
    }
    return listenfd;
}