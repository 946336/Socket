#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "sockets.h"

int main(int argc, char **argv)
{

    Socket sender(false, SOCK_PATH);

    std::string sendMsg;
    if (argc < 2)
        sendMsg = "I'm sending a message through a socket!";
    else
        sendMsg = std::string(argv[1]);

    std::cerr << "Sending: [" << sendMsg << "]\n";
    sender.ssend(sendMsg);
    sender.sreceive(sendMsg);
    std::cerr << "Look what I got back: [" << sendMsg
              << "]\n";

    return 0;
}
