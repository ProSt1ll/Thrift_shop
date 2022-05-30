#ifndef THRIFT_SHOP_HANDLER_H
#define THRIFT_SHOP_HANDLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

#include <ctime>

#include "../../Crawler/Headers/Crawler.h"
#include "../../interface_bd/headers/interface_BD.h"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using nlohmann::json;

class Handlers {
public:
    // мб нужен конструктор

    // поиск по критериям
    http::response <http::string_body>
    get_item(const http::request <http::string_body>& request);

    // добавление в избранное
    http::response <http::string_body>
    to_favorite(http::request <http::string_body> request);

    // Обновление Базы
    void update_bd();

private:

    // Формирование json для каждого товара
    std::string get_product_body(bd::Product product);
    // Настройки сайтов
    json json_set();
    // Формирование запроса к БД из обновления
    bd::Product site_json_pars(const json& jv);

    static bd::Colors str_to_color(const std::string& color_string );

    static bd::Categories str_to_category(const std::string& category_string );

};

/*
 ПРИМЕРНЫЙ JSON
//    json jv = {
//            {"user_id", "123qwery"},
//            {"option", 3},
//            {"product", {
//                                {"category", 1},
//                                {"price", 100},
//                                {"url_image", "url_imag"},
//                                {"url_product", "url_prod"},
//                                {"parameters", {
//                                                       {"id", 15},
//                                                       {"size", 2},
//                                                       {"color", 1},
//                                                       {"brand", "gucci"}
//                                               }
//                                }
//                        }
//            }
//    };
 */


#endif //THRIFT_SHOP_HANDLER_H