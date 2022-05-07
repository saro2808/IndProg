#include "client.h"

int main()
{
    char buf[1024];
    int bytes_read;

    Client my_client = Client();
    while(1)
    {
        bytes_read = my_client.receive(buf, 1024, 0);
        puts(buf);
    }

    return 0;
}
