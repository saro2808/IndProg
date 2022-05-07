#include <iostream>

#include "server.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        perror("Wrong args: need local broadcast IPv4 address");
        exit(1);
    }

    Server server(argv[1]);

    char msg[] = "Hello from server!";

    while (true) {
        server.sendData(msg, sizeof(msg));
        puts("Message sent");
        sleep(1);
    }

    return 0;
}
