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
#include "Handler.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Connection: public std::enable_shared_from_this<Connection>
{
public:
    // Создание соединения с заданным io_context.
    explicit Connection(tcp::socket&& socket, Handlers &handlers);


    // Запуск первой асинхронной операции для Connection.
    void start();

private:
    // Чтение)
    void do_read();

    // Обработка завершения операции асинхронного чтения.
    void handle_read(beast::error_code error,
                     std::size_t bytes_transferred);

    // Обработка завершения операции асинхронной записи.
    void handle_write(bool close,
                      beast::error_code e,
                      std::size_t bytes_transferred);

    // Закрытие)
    void do_close();

private:
    // Обработчик, используемый для обработки входящего запроса request_.
    // Router<Response(*)(const Request &request_)> &requestRouter_;

    beast::tcp_stream stream_;
    Handlers &handlers_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> request_;
    std::shared_ptr<void> res_;
    // нужен парсер
};


#endif //THRIFT_SHOP_CONNECTION_H
