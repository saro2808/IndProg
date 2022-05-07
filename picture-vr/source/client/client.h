#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

class Client {
public:
    Client();
    ~Client();

    ssize_t receive(char *buf, size_t len, int flags);

private:
    int sockfd = 0;
    sockaddr_in sockaddr = {};
};