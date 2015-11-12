#include "sockets.h"

Socket::Socket()
{
    sock_path = SOCK_PATH;
    active_server = false;

    int len;

    if ((remote_ID = socket(AF_UNIX, SOCK_STREAM, 0))
                == -1) {
        perror("socket");
        exit(1);
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) +
          sizeof(remote.sun_family);
    if (connect(remote_ID, (struct sockaddr *)&remote,
                len) == -1) {
        perror("connect");
        exit(1);
    }
}

Socket::Socket(bool server, const char *s_path)
{
    sock_path = s_path;

    int len;

    if (!server) {
        if ((remote_ID = socket(AF_UNIX, SOCK_STREAM, 0))
                    == -1) {
            perror("socket");
            exit(1);
        }
        
        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, SOCK_PATH);
        len = strlen(remote.sun_path) +
              sizeof(remote.sun_family);
        if (connect(remote_ID, (struct sockaddr *)&remote, len)
                    == -1) {
            perror("connect");
            exit(1);
        }
        active_server = false;
    }

    if (server){
        if ((local_ID = socket(AF_UNIX, SOCK_STREAM, 0))
                    == -1) {
            perror("socket");
            exit(1);
        }

        local.sun_family = AF_UNIX;
        strcpy(local.sun_path, SOCK_PATH);

        unlink(local.sun_path);
        len = strlen(local.sun_path) + sizeof(local.sun_family);
        if (bind(local_ID, (struct sockaddr *)&local, len)
                == -1) {
            perror("bind");
            exit(1);
        }

        if (listen(local_ID, REQUEST_BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }
  
        socklen_t t = sizeof(remote);
        if ((remote_ID = accept(local_ID, (struct sockaddr *)&remote, &t))
             == -1) {
            perror("accept");
            exit(1);
        }
        active_server = true;
    }
}

Socket::Socket(const Socket &source)
{
    local_ID = source.local_ID;
    remote_ID = source.remote_ID;
    sock_path = source.sock_path;
    active_server = source.active_server;
    memcpy(&remote, &source.remote, sizeof(remote));
    memcpy(&local, &source.local, sizeof(local));
    memcpy(&recv_buf, &source.recv_buf,
        RECV_BUF_LEN * sizeof(char));
}

Socket& Socket::operator= (const Socket &source)
{
    if (this != &source) {
        local_ID = source.local_ID;
        remote_ID = source.remote_ID;
        sock_path = source.sock_path;
        active_server = source.active_server;
        memcpy(&remote, &source.remote, sizeof(remote));
        memcpy(&local, &source.local, sizeof(local));
        memcpy(&recv_buf, &source.recv_buf,
            RECV_BUF_LEN * sizeof(char));
    }
    return *this;
}

int Socket::ssend(std::string buf)
{
    return send(remote_ID, buf.c_str(), buf.length() + 1, 0);
}

int Socket::sreceive(std::string &buf)
{
    int ret = recv(remote_ID, recv_buf, RECV_BUF_LEN, 0);
    buf = std::string(recv_buf);
    return ret;
}

Socket::~Socket()
{
    close(remote_ID);

    if (active_server) {
        close(remote_ID);
    }
}