#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "tcpclient.h"
#pragma once
class tcplistener {
public:
tcplistener(/*unsigned short port*/) {
/*port = (port == 0 ? 80 : port);*/
declared = false;
serv_addr = new sockaddr_in();
/*
//OPEN SOCKET
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
	error("ERROR opening socket");
//ZERO
bzero((char*)&serv_addr, sizeof(serv_addr));
//DEFINE PORT
portno = port;
//DEFINE IP + PORT
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(port);
//BIND SOCKET
if (bind(sockfd, (struct sockaddr*) &serv_addr,
	sizeof(serv_addr)) < 0)
	error("ERROR on binding");
//LISTEN
listen(sockfd,5);
clilen = sizeof(cli_addr);
//ACCEPT A SOCKET
//newsockfd = accept(sockfd,
//	(struct sockaddr*) &cli_addr,
//	&clilen);
//if (newsockfd < 0)
//	error("ERROR on accept");
//ZERO
//bzero(buffer,256);

//READING FROM SOCKET
//n = read(newsockfd,buffer,255);
//if (n < 0) error("ERROR reading from socket");
//printf("Here is the message: %s\n",buffer);

//WRITING TO SOCKET
//n = write(newsockfd, "I got your message", 18);
//if (n < 0) error("ERROR writing to socket");

//CLOSING THE SOCKET
//close(newsockfd);
//close(sockfd);
*/
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
