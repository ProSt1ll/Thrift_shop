#ifndef THRIFT_SHOP_SERVER_H
#define THRIFT_SHOP_SERVER_H

#include <boost/asio.hpp>

#include "Handler.h"
#include "Connection.h"
#include "Router.h"

class Server : public std::enable_shared_from_this<Server> {
public:
    explicit Server(const std::string &address, const std::string &port,
                    std::size_t thread_pool_size);

    void Run();

private:
    void StartAccept();

    void HandleAccept();

    void HandleStop();

private:
    net::io_context io_context;
    tcp::acceptor acceptor;
    std::size_t thread_pool_size;
};


#endif //THRIFT_SHOP_SERVER_H
