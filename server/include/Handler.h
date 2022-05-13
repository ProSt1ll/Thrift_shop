#ifndef THRIFT_SHOP_HANDLER_H
#define THRIFT_SHOP_HANDLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <nlohmann/json.hpp>

//#include "Crawler.h"
#include "../../interface_bd/headers/interface_BD.h"

//#include "структура из клиента"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using nlohmann::json;

class Handlers {
public:
    // мб нужен конструктор

    http::response <http::string_body>
    add_user(http::request <http::string_body> request);

//    http::response <http::string_body>
//    get_item(http::request <http::string_body> request);


private:
//    std::map<std::string, std::string>
//    parse_params(const std::string &url);
//
//    std::string get_user_body(User user);
//
//    std::string get_product_body(bd::Product product);
//
//    std::string check_update();
//
//    std::map<Categories, Parametrs> pars_param(json json_);
//
//    json need_item(Product item);

};


#endif //THRIFT_SHOP_HANDLER_H
