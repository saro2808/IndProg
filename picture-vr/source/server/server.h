#ifndef _SERVER_H_
#define _SERVER_H_


#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "../imitator/TreeNode.h"


class Server {
public:
    Server(const char* IPv4="255.255.255.255");
    ~Server();
    ssize_t sendScene(const TreeNodeHeader& scene);
    ssize_t sendData(const char* data, size_t len);

private:
    int sockfd = 0;
    sockaddr_in sockaddr = {};
};


#endif // _SERVER_H_