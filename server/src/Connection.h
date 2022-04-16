#ifndef THRIFT_SHOP_CONNECTION_H
#define THRIFT_SHOP_CONNECTION_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "Router.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Connection: public std::enable_shared_from_this<Connection>
{
public:
    // Construct a connection with the given io_context.
    explicit Connection(tcp::socket&& socket);


    // Start the first asynchronous operation for the connection.
    void start();

private:
    void do_read();

    // Handle completion of a read operation.
    void handle_read(beast::error_code e,
                     std::size_t bytes_transferred);

    // Handle completion of a write operation.
    void handle_write(bool close,
                      beast::error_code e,
                      std::size_t bytes_transferred);

    void do_close();

private:
    // The handler used to process the incoming request.
    // Router<Response(*)(const Request &request)> &requestRouter_;

    beast::tcp_stream stream;
    beast::flat_buffer buffer;
    http::request<http::string_body> request;
    std::shared_ptr<void> res_;
};


#endif //THRIFT_SHOP_CONNECTION_H
