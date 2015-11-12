#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "sockets.h"

int main()
{
    std::string recv_intermediate = "Did not receive message.";

    Socket listener(true, SOCK_PATH);

    listener.sreceive(recv_intermediate);

    std::cout << "Received: [" << recv_intermediate << "]" << std::endl;

    recv_intermediate = "I got your message!";
    std::cerr << "Replying: [" << recv_intermediate << "]\n";
    
    listener.ssend(recv_intermediate);

    return 0;
}