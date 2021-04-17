#include "network.h"

#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

TcpEngine(): _tcp_socket(-1) {
    
}

~TcpEngine() {
    if (_tcp_socket != -1) {
        close(_tcp_socket);
    }
}

bool TcpEngine::Init(const std::string& ip, int port) {
    this->_tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_tcp_socket == -1) {
        perror("socket failed");
        return false;
    }

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &sa.sin_addr) != 1) {
        perror("inet_pton failed");
        return false;
    }

    // 是否设置端口重用

    if (bind(this->_tcp_socket, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        perror("bind failed");
        return false;
    }

    if (listen(this->_tcp_socket, 5) == -1) {
        perror("listen failed");
        return false;
    }

    return true;
}

int TcpEngine::GetTcpSocket() const {
    return _tcp_socket;
}

