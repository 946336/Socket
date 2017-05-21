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
#ifndef SOCK_PATH
#define SOCK_PATH "GENERIC_SOCKET"
#endif

#ifndef REQUEST_BACKLOG
#define REQUEST_BACKLOG 5
#endif

#ifndef RECV_BUF_LEN
#define RECV_BUF_LEN 4096
#endif

/*************************************************************/

// Sockets tend to be used in pairs. This header provides one
// that you can use by default. You can specify your own if
// you'd like
class Socket {
    public:
        // Servers don't call connect
        Socket(bool server, const char *s_path = SOCK_PATH);
        ~Socket();

        int ssend(const std::string &buf);
        int sreceive(std::string &buf);

    private:
        // Dont even think about it
        Socket(const Socket &source);
        Socket &operator= (const Socket &source);

        struct sockaddr_un remote;
        struct sockaddr_un local;
        const char *sock_path;

        char recv_buf[RECV_BUF_LEN];

        int remote_ID;
        int local_ID;

        bool active_server;
};

template<typename T>
Socket& operator<<(Socket &sock, T thing)
{
    sock.ssend(std::to_string(thing));
}

Socket& operator>>(Socket &sock, std::string &buf)
{
    sock.sreceive(buf);
    return sock;
}

#endif

