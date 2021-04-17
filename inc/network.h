#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <string>

class TcpEngine {
public:
    TcpEngine();
    ~TcpEngine();
    /**
     * @brief 绑定ip和端口，并生成监听套接字
     * @param ip    绑定本地的ip地址
     * @param port  绑定本地的端口号
     * @return
     *      false   fail
     *      true    succeed
     */
    bool Init(const std::string& ip, int port);

    int GetTcpSocket() const;

private:
    int _tcp_socket;    // 监听套接字
    
};

#endif