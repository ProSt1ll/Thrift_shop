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

    // Формирование общую часть json
    std::string get_user_body(std::string user_id,
                              int option, std::size_t favorit_product_id);
    // Формирование json для каждого товара
    std::string get_product_body(bd::Product product);
    // Настройки сайтов
    json json_set();
    // Формирование запроса к БД из обновления
    bd::Product site_json_pars(const json& jv);

};

/*
 ПРИМЕРНЫЙ JSON
{
	"user_id": 12345,
	"option": 1 || 0 - just category; 1 - favorite; 2 - price; 3 - parametrs
	"product_id": 63452 (or 0),
	"product": {
		"category": [
			 Empty,
			 Sneakers,
			 Shirts,
			 Tshirts
			 ],
		"price": 1000,
		"url_image": 12ew2313r,
		"url_product": g3423rf,
		"parametrs": {
			 "id": 1245,
			 "size": 45,
			 "color": [
				 None,
				 White,
				 Blue,
				 Red,
				 Orange,
				 Yellow,
				 Green,
				 Black
				 ],
		 	 "brand": gucci
		 	 }
 	}
}
 */


#endif //THRIFT_SHOP_HANDLER_H
