#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#pragma once
class tcpclient
{
public:
tcpclient(int clientfd, sockaddr* clientaddr)
{
//std::cout << "this->_clientfd:" << this->_clientfd << std::endl;
//std::cout << "clientfd:" << clientfd << std::endl;
_clientfd = clientfd;
//std::cout << "this->_clientfd:"<< this->_clientfd << std::endl;
//std::cout << "clientfd:" << clientfd << std::endl;
this->clientaddr = clientaddr;
}
void cliclose(){
close(_clientfd);
}
int cliread(void* buffer, size_t count)
{
std::cout << _clientfd << std::endl;
return read(_clientfd, buffer, count);
}
int cliwrite(void* buffer, size_t length)
{
std::cout << _clientfd << std::endl;
return write(_clientfd, buffer, length);
}
int getfd() { return _clientfd; }
private:
int _clientfd;
sockaddr* clientaddr;
};

