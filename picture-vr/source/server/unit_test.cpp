#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "server.h"

#include "../imitator/TreeNode.h"

namespace {
    // Simple client for recieving broadcast messages
    class Client {
    public:
        Client() :
            sockfd{socket(AF_INET, SOCK_DGRAM, 0)},
            sockaddr{.sin_family = AF_INET,
                     .sin_port = htons(8000),
                     .sin_addr = {htonl(INADDR_ANY)}}
        {
            int true_flag = 1;

            // Set socket to broadcast mode,
            // Makes possible to send one message for all clients
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


        ~Client() {
            close(sockfd);
        }


        ssize_t receive(char* buf, size_t len) {
            return recvfrom(sockfd, buf, len, 0, NULL, NULL);
        }

    private:
        int sockfd = 0;
        sockaddr_in sockaddr = {};
    };


    TEST(ServerTest, Constructing) {
        char send_buffer[] = "Test message from server";
        const int buffer_size = sizeof(send_buffer);

        Server server_def;
        ASSERT_EQ(server_def.sendData(send_buffer, buffer_size), buffer_size) << "Error sending with default ip";

        Server server_lan("192.168.255.255");
        ASSERT_EQ(server_lan.sendData(send_buffer, buffer_size), buffer_size) << "Error sending with lan brodacast ip";
    }


    TEST(ServerTest, SendingData) {
        Server server;
        ASSERT_LT(server.sendData(nullptr, 10), 0) << "Wrong result for NULL input";
        ASSERT_EQ(server.sendData(nullptr, 0), 0) << "Wrong result for NULL input";
        ASSERT_EQ(server.sendData("Not empty message", 0), 0) << "Wrong sent count";

        char send_buffer[] = "Test message from server";
        const int buffer_size = sizeof(send_buffer);

        {
            std::vector<Client> clients(10);
        
            ASSERT_EQ(server.sendData(send_buffer, buffer_size), buffer_size) << "Wrong sent count";
        
            for (auto client : clients) {
                char recv_buffer[buffer_size] = {};
                ASSERT_EQ(client.receive(recv_buffer, buffer_size), buffer_size) << "Wrong recieved count";
                ASSERT_EQ(strcmp(send_buffer, recv_buffer), 0) << "Unequal messages";
            }
        }

        {
            std::vector<Client> clients(10);
        
            ASSERT_EQ(server.sendData(send_buffer, buffer_size / 2), buffer_size / 2) << "Wrong sent count";
        
            send_buffer[buffer_size / 2] = '\0';

            for (auto client : clients) {
                char recv_buffer[buffer_size] = {};
                ASSERT_EQ(client.receive(recv_buffer, buffer_size), buffer_size / 2) << "Wrong recieved count";
                ASSERT_EQ(strcmp(send_buffer, recv_buffer), 0) << "Unequal messages";
            }
        }
    }


    TEST(ServerTest, SendingScene) {
        Server server;

        // Create simple scnene for sending
        TreeNode object;
        TreeNode sub_object;
        object.add(&sub_object);
        TreeNodeHeader scene(&object, 1, 0);

        {
            std::vector<Client> clients(10);

            ssize_t res = server.sendScene(scene);
        
            ASSERT_GT(res, 0) << "Wrong sent count";
        
            for (auto client : clients) {
                char recv_buffer[res] = {};
                ASSERT_EQ(client.receive(recv_buffer, res), res) << "Wrong recieved count";
            }
        }
    }
}; // namespace
