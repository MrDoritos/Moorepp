#ifdef __WIN32

#include <ws2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#define MAX_BUFFER_SIZE (49152)

#elif __linux__

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "tcpclient.h"

#endif

#pragma once

class tcplistener {
public:
tcplistener() {
declared = false;
serv_addr = new sockaddr_in();
}
int sockbind(sockaddr_in* serveraddress)
{
int err;
if (!declared){
if ((err = declare()) < 0 && declared) return err; else sockbind(serveraddress);
} else
{
bzero((char*)serv_addr, sizeof(sockaddr_in));
serv_addr = serveraddress;
if ((err = bind(sockfd, (struct sockaddr*) serv_addr, sizeof(sockaddr_in))) < 0) return err;
}
return 0;
}
int sockbind(int port)
{
sockaddr_in* xserv_addr = new sockaddr_in();
xserv_addr->sin_family = AF_INET;
xserv_addr->sin_addr.s_addr = INADDR_ANY;
xserv_addr->sin_port = htons(port);
return sockbind(xserv_addr);
}
int socklisten()
{
listen(sockfd,5);
clilen = sizeof(sockaddr_in);
}
void sockclose() {
close(sockfd);
}
int accept_client(tcpclient& out)
{
sockaddr* sock_addr = new sockaddr();
int newsock = accept(sockfd,(struct sockaddr*) sock_addr, &clilen);
std::cout << "newsock:" << newsock << std::endl;
if (newsock < 0) return newsock;
std::cout << "out:" << &out << std::endl;
//tcpclient* a = new tcpclient(newsock, sock_addr);
//out = a;
out = tcpclient(newsock,sock_addr);
//std::cout << "out:" << &out << std::endl;
return newsock;
}
private:
bool declared;
int declare()
{
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) { declared = false; return sockfd; }
declared = true;
return 0;
}
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int sockfd;
int newsockfd;
int portno;
socklen_t clilen;
char buffer[256];
sockaddr_in *serv_addr;
sockaddr_in *cli_addr;
int n;
};
