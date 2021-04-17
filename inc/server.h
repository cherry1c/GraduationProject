#ifndef __SERVER_H__
#define __SERVER_H__

#include <list>

class Server {
public:
    Server(const int sockfd);
    ~Server();
    void* WaitForConnect(void* arg);
private:
    std::list<int> _client_list; // 已连接的客户端列表
    int _tcp_socket;
};

#endif
