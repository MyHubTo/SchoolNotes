#include <iostream>
#include <chrono>
extern "C"
{
    #include <stdio.h>
    #include <string.h>
}

#include "csapp.h"
#include <thread>
#include <fstream>
using namespace std;

void run(rio_t *rp)
{
    char buff[1024];
    size_t n = sizeof(buff);
    while (1)
    {
        rio_readlineb(rp, buff, n);
        cout << buff;
    }
}
int main()
{
    int clientfd;
    char *host, *port, buff[MAXLINE];
    rio_t rio;
    host = "10.103.0.89";
    port = "8848";
    clientfd = open_clientfd(host, port);
    rio_readinitb(&rio, clientfd);

    while (1)
    {
        fgets(buff, MAXLINE, stdin);
        rio_writen(clientfd, buff, strlen(buff));
        std::thread t1(run, &rio);
        t1.detach();
    }
    close(clientfd);
    return 0;
}