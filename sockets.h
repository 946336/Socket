#ifndef SOCKETS_H
#define SOCKETS_H 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <string>

/***************CHANGE THESE WHENEVER YOU NEED TO*************/
static const char *SOCK_PATH = "GENERIC_SOCKET";
#define REQUEST_BACKLOG 5
#define RECV_BUF_LEN 1000
/*************************************************************/

// Sockets tend to be used in pairs. This header provides one
// that you can use by default. You can specify your own if
// you'd like
class Socket {
    public:
        // Client by default
        Socket();
        // Servers don't call connect
        Socket(bool server, const char *s_path = SOCK_PATH);
        ~Socket();

        // Hey! I haven't tested these!
        Socket(const Socket &source);
        Socket &operator= (const Socket &source);

        int ssend(std::string buf);
        int sreceive(std::string &buf);

    private:
        struct sockaddr_un remote;
        struct sockaddr_un local;
        const char *sock_path;

        char recv_buf[RECV_BUF_LEN];

        int remote_ID;
        int local_ID;

        bool active_server;
};


#endif