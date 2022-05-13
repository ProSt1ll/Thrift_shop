#ifndef THRIFT_SHOP_ROUTER_H
#define THRIFT_SHOP_ROUTER_H

#include <boost/beast/http.hpp>
#include <iostream>

namespace http = boost::beast::http;           // from <boost/beast/http.hpp>

template<typename Handler>
class Router {
public:
    // Сообщаем какой handler нужен для какого метода
    void addHandler(std::string method, Handler handler) {

    }

    // Обработка запроса
    http::response <http::string_body>
            processRoute(const std::string &method,
                         const http::request <http::string_body> &request) {

    }

private:
    // метод, функция
    std::map<std::string, Handler> Handlers;
};

#endif //THRIFT_SHOP_ROUTER_H
