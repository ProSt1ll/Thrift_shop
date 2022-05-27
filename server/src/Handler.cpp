#include "../include/Handler.h"

// Формируем часть json ответа
std::string Handlers::get_user_body(std::string user_id,
                                    int option, std::size_t favorit_product_id) {
    json response_value = {
        {"user_id", user_id},
        {"option", option},
        {"product_id", favorit_product_id}
    };
    return response_value.dump();
}
// Формируем часть json ответа
std::string Handlers::get_product_body(const bd::Product product) {
    json response_value = {
            {"category", product.category},
            {"price", product.price},
            {"url_image", product.url_image},
            {"url_product", product.url_product},
            {"parameters",   {
                {"id", product.param.id},
                {"size", product.param.size},
                {"color", product.param.color},
                {"brand", product.param.brand}
            }}
        };

    return response_value.dump();
}

// Создаем настройки сайтов (то, где будем бегать)
json Handlers::json_set() {

    json site_1 = {
            {"chapterMap",   {
                             {siteSearch::index, "www.ostin.com"},
                             {siteSearch::man,  "www.ostin.com/catalog/muzhchiny"},
                             {siteSearch::woman, "www.ostin.com/catalog/zhenschiny"},
                             {siteSearch::boy,  "www.ostin.com/catalog/malchiki"},
                             {siteSearch::girl, "www.ostin.com/catalog/devochki"}
                             }},
            {"parameterMap", {
                             {siteSearch::url,   {
                                                 {"tag", "a"},
                                                 {"id", "idTitle_1"},
                                                 {"cssClass", "rr-item__info"}
                                                 }},
                             {siteSearch::cost, {
                                                {"tag", "div"},
                                                {"id", "idTitle_1"},
                                                {"cssClass", "rr-item__price-value"}
                                                }},
                             {siteSearch::title, {
                                                 {"tag", "div"},
                                                 {"id", "idTitle_1"},
                                                 {"cssClass", "rr-itemname-block  rr-itemtitle"}
                                                 }},
                             {siteSearch::person, {
                                                  {"tag", "tagPerson_1"},
                                                  {"id", "idTitle_1"},
                                                  {"cssClass", "cssClassPerson_1"}
                                                }},
                             {siteSearch::image, {
                                                 {"tag", "img"},
                                                 {"id", "idTitle_1"},
                                                 {"cssClass", "rr-def__img rr-product-img swiper-lazy swiper-lazy-loaded"}
                                                 }},
                             {siteSearch::size, {
                                                {"tag", "tagSize_1"},
                                                {"id", "idTitle_1"},
                                                {"cssClass", "cssClassSize_1"}
                                                }},
                             {siteSearch::itemTemplate,  {
                                                         {"tag", "div"},
                                                         {"id", "idTitle_1"},
                                                         {"cssClass", "rr-item"}
                                                         }}
                             }}
    };

    json settings = {
            {"chapters",
                      {siteSearch::index, siteSearch::man,  siteSearch::woman, siteSearch::boy,    siteSearch::girl}},
            {"parameters",
                      {siteSearch::url,   siteSearch::cost, siteSearch::title, siteSearch::person, siteSearch::size, siteSearch::image}},
            {"sites", {site_1}}
    };

    return settings;
}

// Формируем запрос к БД из json от crawler
void Handlers::site_json_pars(bd::Product& prod, const json& jv) {

//    bd::Product prod;

    jv.at("UrlContent").get_to(prod.url_product);
    jv.at("CostContent").get_to(prod.price);
    jv.at("TitleContent").get_to(prod.name);
    //jv.at("PersonContent").get_to(prod.param.person);
    jv.at("SizeContent").get_to(prod.param.size);
    jv.at("ImageContent").get_to(prod.url_image);

//    return prod;
}

// Добавляем в избранное
http::response<http::string_body>
        Handlers::to_favorite(http::request<http::string_body> request) {
//    json jv = json::parse(request.body());
    json jv = {
            {"user_id", "123qwery"},
            {"option", 3},
            {"product_id", 0},
            {"product", {
                                {"category", 1},
                                {"price", 100},
                                {"url_image", "url_imag"},
                                {"url_product", "url_prod"},
                                {"parameters", {
                                                       {"id", 15},
                                                       {"size", 2},
                                                       {"color", 1},
                                                       {"brand", "gucci"}
                                               }
                                }
                        }
            }
    };
    // id пользователя
    std::string user_id;
    jv.at("user_id").get_to(user_id);

    // избранный товар
    std::size_t product_id;
    jv.at("product_id").get_to(product_id);

    // выбранная категория
    bd::Categories category;
    jv.at("/product/category"_json_pointer).get_to(category);

    bd::BI data_base;

    data_base.set_user_chosen(user_id, category, product_id);

    http::response<http::string_body> response;
    response.body() = R"("Favorite item add.")";

    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_length,
                 std::to_string(response.body().size()));
    response.set(http::field::content_type, "application/json");
    response.result(http::status::ok);

    return response;

}

// Получаем товар по критериям
http::response<http::string_body>
        Handlers::get_item(const http::request<http::string_body>& request) {

//    json jv = json::parse(request.body());
// пока так
    json jv = {
            {"user_id", "123qwery"},
            {"option", 3},
            {"product_id", 0},
            {"product", {
                                {"category", 1},
                                {"price", 100},
                                {"url_image", "url_imag"},
                                {"url_product", "url_prod"},
                                {"parameters", {
                                                          {"id", 15},
                                                          {"size", 2},
                                                          {"color", 1},
                                                          {"brand", "gucci"}
                                                  }
                                }
                        }
            }
    };

    // проверка обновлений
    time_t result_hours = time(nullptr) / 3600;
    if (result_hours % 3 == 0)
        update_bd();
    // id пользователя
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    // опция поиска
    int option;
    jv.at("option").get_to(option);
    // избранный товар
    std::size_t product_id;
    jv.at("product_id").get_to(product_id);

    // выбранная категория
    bd::Categories category;
    jv.at("/product/category"_json_pointer).get_to(category);

    bd::BI data_base;
    std::vector<bd::Product> need_items;

    // временно
    bd::Product product;

    // избранный товар
    if (option == 1)  {
        need_items = data_base.get_user_chosen(user_id);
    }
    // с ценой меньше или равной указанной
    else if (option == 2) {
        std::size_t price;
        jv.at("/product/price"_json_pointer).get_to(price);

        need_items = data_base.search_down_price(category, price);
    }
    // по параметрам
    else if (option == 3) {
        bd::Parametrs params;
        jv.at("/product/parameters/id"_json_pointer).get_to(params.id);
        jv.at("/product/parameters/size"_json_pointer).get_to(params.size);
        jv.at("/product/parameters/color"_json_pointer).get_to(params.color);
        jv.at("/product/parameters/brand"_json_pointer).get_to(params.brand);

        product.category = category;
        jv.at("/product/price"_json_pointer).get_to(product.price);
        jv.at("/product/url_image"_json_pointer).get_to(product.url_image);
        jv.at("/product/url_product"_json_pointer).get_to(product.url_product);
        product.param = params;

//        need_items = data_base.search_parametrs(category, params);

    }
    // простой поиск по категории
    else
        need_items = data_base.get_products(category);

    // формирование ответа
    std::string response_user_body = get_user_body(user_id,
                                                   option, product_id);
    response_user_body.pop_back();
    std::string response_product_body = ",\"product\":";
    // временно
//    for (const bd::Product& item: need_items) {
//        response_product_body += get_product_body(item) + ",";
//    }
    response_product_body += get_product_body(product);
    response_product_body.pop_back();
    response_product_body += "}}";
    http::response<http::string_body> response;
    response.body() = response_user_body + response_product_body;

    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_length,
                 std::to_string(response.body().size()));
    response.set(http::field::content_type, "application/json");
    response.result(http::status::ok);

    return response;
}

// Проверяем обновления
void Handlers::update_bd() {

    // формируем настройки сайтов (по чему нужно бегать)
    json json_setting = json_set();

    Crawler crawler = Crawler(json_setting);
//    for (auto i: crawler.getParameters())
//        std::cout << i << std::endl;
//    for (auto i: crawler.getChapters())
//        std::cout << i << std::endl;
    // пробегаемся по сайтам и возвращаем найденные объекты
    json result_jsons = json::array();
    result_jsons = crawler.crawl(crawler.getSites(), crawler.getParameters(),
                        crawler.getChapters());
    std::cout << "After crawler" << std::endl;
    bd::BI data_base;
    bd::Product prod;
    // Формирование запроса к БД из обновления
    for (json result_json: result_jsons) {
        site_json_pars(prod,result_jsons);
        // обновляем БД
        data_base.set_product(prod);
        std::cout << "After BD" << std::endl;
    }

}
