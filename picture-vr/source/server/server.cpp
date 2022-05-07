#include "server.h"
#include "../serializer/Serializer.h"

Server::Server(const char* IPv4) :
    sockfd(socket(AF_INET, SOCK_DGRAM, 0)),
    sockaddr{.sin_family = AF_INET,
             .sin_port = htons(8000),
             .sin_addr = {inet_addr(IPv4)}} {
    if (-1 == sockfd) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set socket to broadcast mode
    int broadcast = 1;

    if (-1 == setsockopt(sockfd,
            SOL_SOCKET,
            SO_BROADCAST,
            &broadcast,
            sizeof(broadcast))) {
        perror("Error in setting Broadcast option");
        close(sockfd);
        exit(1);
    }
}


Server::~Server() {
    close(sockfd);
}


ssize_t Server::sendScene(const TreeNodeHeader& scene) {
    std::string str = Serializer::serialize_to_string(scene);
    return sendData(str.data(), str.size());
}


ssize_t Server::sendData(const char* data, size_t len) {
    return sendto(sockfd,
        data,
        len,
        0,
        (struct sockaddr*) &sockaddr,
        sizeof(sockaddr));
}
