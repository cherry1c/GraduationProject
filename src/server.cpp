#include "server.h"
#include "constant.h"

#include <sys/epoll.h>
#include <memory>

Server(const int sockfd):_tcp_socket(sockfd) {
    // 开一个线程去等待客户端的连接
    pthread_t thread;
    int temp = pthread_create(&thread, NULL, TcpEngine::WaitForConnect, NULL);
    if (temp != 0) {
        std::cout << "create thread faild" << ", error number is: " << temp << std::endl;
    }
    temp = pthread_detach(thread);
    if (temp != 0) {
        std::cout << "detach thread faild" << ", error number is: " << temp << std::endl;
    }
}
~Server() {

}


void* Server::WaitForConnect(void *arg) {
    int epollfd = epoll_create(kClientAmount);
    if (epollfd == -1) {
        perror("create epoll failed");
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = _tcp_socket;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, _tcp_socket, &ev) == -1) {
        perror("add tcp socketfd failed");
    }
    struct epoll_event* evs = malloc(sizeof(struct epoll_event) * kClientAmount);
    

    while (true) {
        int volume = epoll_wait(epollfd, evs, kClientAmount, -1);
        if (volume == 0) {
            continue;
        }
        else if (volume == -1) {
            perror("epoll wait failed");
        }

        for (int i = 0; i != volume; ++i) {
            if (evs[i].data.fd == _tcp_socket) {
                int clifd = accept(_tcp_socket, NULL, NULL);
                if (clifd == -1) {
                    perror("accept failed");
                    continue;
                }
                ev.data.fd = clifd;
                ev.events = EPOLLIN;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, clifd, &ev) == -1) {
                    perror("add client file describe failed");
                }
                _client_list.push_back(clifd);
            }
            else if (evs[i].events & EPOLLIN) {
                // 从客户端接收数据
            }
            else {
                std::cout << "unkown epoll condition" << std::endl;
            }
        }
    }
    close(epollfd);
}