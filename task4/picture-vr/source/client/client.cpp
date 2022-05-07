#include "client.h"

Client::Client() : sockfd{socket(AF_INET, SOCK_DGRAM, 0)},
                   sockaddr{.sin_family = AF_INET,
                            .sin_port = htons(8000),
                            .sin_addr = {htonl(INADDR_ANY)}}
{
    // Set socket to broadcast mode,
    // Makes possible to send one message for all clients
    int true_flag = 1;

    if (-1 == setsockopt(sockfd,
                         SOL_SOCKET,
                         SO_BROADCAST,
                         &true_flag,
                         sizeof(true_flag))) {
        perror("Error in setting Broadcast option");
        close(sockfd);
        exit(1);
    }

    // Set socket to reuseport mode
    // Makes possible to run several clients at the same time
    if (-1 == setsockopt(sockfd,
                         SOL_SOCKET,
                         SO_REUSEPORT,
                         &true_flag,
                         sizeof(true_flag))) {
        perror("Error in setting Reuseport option");
        close(sockfd);
        exit(1);
    }

    if(bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        perror("Cant bind to the host");
        close(sockfd);
        exit(1);
    }
}

ssize_t  Client::receive(char* buf, size_t len, int flags) {
    ssize_t bytes_read = recvfrom(sockfd, buf, 1024, 0, NULL, NULL);
    buf[bytes_read] = '\0';
    return bytes_read;
}

Client::~Client() {
    close(sockfd);
}