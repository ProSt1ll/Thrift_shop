#ifndef THRIFT_SHOP_HANDLER_H
#define THRIFT_SHOP_HANDLER_H

#include <boost/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>

#include "Crawler.h"
#include "interface_BD.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Handlers {
public:

    http::response <http::string_body>
    add_user(http::request <http::string_body> request);

    http::response <http::string_body>
    get_item(http::request <http::string_body> request);


private:
    std::string check_update();

    std::map<Categories, Parametrs> pars_param(boost::json json)

    boost::json need_item(Product item);



};


#endif //THRIFT_SHOP_HANDLER_H
