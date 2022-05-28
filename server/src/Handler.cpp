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
                                     {siteSearch::index, "moda.oc-mod.ru"},
                                     {siteSearch::man,  "/wooman/wooman_odegda/wooman_dresses/"},
                                     {siteSearch::woman, "/"},
                                     {siteSearch::boy,          "/"},
                                     {siteSearch::girl, "/"}
                             }},
            {"parameterMap", {
                                     {siteSearch::title, {
                                                                 {"tag", "span"},
                                                                 {"id", "itemprop=\"name\""},
                                                                 {"cssClass", ""}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "span"},
                                                                {"id", " "},
                                                                {"cssClass", "class=\"price_no_format"}
                                                        }},
                                     {siteSearch::image, {
                                                                 {"tag", "img"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "rr-def__img rr-product-img swiper-lazy swiper-lazy-loaded"}
                                                         }},
                                     {siteSearch::itemTemplate, {
                                                                        {"tag", "div"},
                                                                        {"id", ""},
                                                                        {"cssClass", "class=\"caption product-info clearfix\""}
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
bd::Product Handlers::site_json_pars(const json& jv) {

    bd::Product prod;

    prod.url_image = "3112";
    prod.url_product = "123r";
    prod.param.id = 1;
    prod.param.color = bd::Colors::Black;
    // None == NULL
    std::string brand;
//    jv.at("0").get_to(prod.url_product);
    std::string str_price;
    jv.at("1").get_to(str_price);
    prod.price = std::stoi(str_price);
    jv.at("2").get_to(prod.name);
    //jv.at("PersonContent").get_to(prod.param.person);
//    std::string str_size;
//    jv.at("4").get_to(str_size);
    prod.param.size = 1;
    prod.category = bd::Categories::Tshirts;
//    jv.at("5").get_to(prod.url_image);

    return prod;
}

// Добавляем в избранное
http::response<http::string_body>
        Handlers::to_favorite(http::request<http::string_body> request) {
    json jv = json::parse(request.body());
//    json jv = {
//            {"user_id", "123qwery"},
//            {"option", 3},
//            {"product_id", 0},
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
//    time_t result_hours = time(nullptr) / 3600;
//    if (result_hours % 3 == 0)
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

        // временно
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

    // пробегаемся по сайтам и возвращаем найденные объекты
    json result_jsons = json::array();
    result_jsons = crawler.crawl(crawler.getSites(), crawler.getParameters(),
                        crawler.getChapters());
    std::cout << result_jsons << std::endl;
    bd::BI data_base;
    bd::Product prod;
    // Формирование запроса к БД из обновления
    for (const auto &res_json: result_jsons) {
        prod = site_json_pars(res_json);
        // обновляем БД
        data_base.set_product(prod);
    }

}
