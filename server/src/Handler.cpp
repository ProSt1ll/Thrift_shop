#include "../include/Handler.h"

// Формируем часть json ответа
std::string Handlers::get_user_body(std::string user_id,
                                    int option, std::size_t favorit_product_id) {
    json response_value = {
        {user_id, "user_id"},
        {option, "option"},
        {favorit_product_id, "favorit_product_id"}
    };
    return response_value.dump();
}
// Формируем часть json ответа
std::string Handlers::get_product_body(const bd::Product product) {
    json response_value = {
            {product.category, "product_category"},
            {product.price, "product_price"},
            {product.url_image, "product_url_image"},
            {product.url_product, "product_url_product"},
            {"product_param",   {
                {product.param.id, "id"},
                {product.param.size, "size"},
                {product.param.color, "color"},
                {product.param.brand, "brand"}
            }}
        };
    return response_value.dump();
}

// Создаем настройки сайтов (то, где будем бегать)
json Handlers::json_set(const json& jv) {

    json site_1 = {
            {"chapterMap",   {
                                     {siteSearch::index, "indexUrl_1"},
                                     {siteSearch::man,  "manUrl_1"},
                                     {siteSearch::woman, "womanUrl_1"},
                                     {siteSearch::boy,    "boyUrl_1"},
                                     {siteSearch::girl, "girlUrl_1"}
                             }},
            {"parameterMap", {
                                     {siteSearch::url,   {
                                                                 {"tag", "tagUrl_1"},
                                                                 {"id", "idUrl_1"},
                                                                 {"cssClass", "cssClassUrl_1"}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "tagCost_1"},
                                                                {"id", "idcCst_1"},
                                                                {"cssClass", "cssClassCost_1"}
                                                        }},
                                     {siteSearch::title, {
                                                                 {"tag", "tagTitle_1"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "cssClassTitle_1"}
                                                         }},
                                     {siteSearch::person, {
                                                                  {"tag", "tagPerson_1"},
                                                                  {"id", "idPerson_1"},
                                                                  {"cssClass", "cssClassPerson_1"}
                                                          }},
                                     {siteSearch::size, {
                                                                {"tag", "tagSize_1"},
                                                                {"id", "idSize_1"},
                                                                {"cssClass", "cssClassSize_1"}
                                                        }},
                                     {siteSearch::image, {
                                                                 {"tag", "tagImage_1"},
                                                                 {"id", "idImage_1"},
                                                                 {"cssClass", "cssClassImage_1"}
                                                         }}
                             }}
    };

    json site_2 = {
            {"chapterMap",   {
                                     {siteSearch::index, "indexUrl_2"},
                                     {siteSearch::man,  "manUrl_2"},
                                     {siteSearch::woman, "womanUrl_2"},
                                     {siteSearch::boy,    "boyUrl_2"},
                                     {siteSearch::girl, "girlUrl_2"}
                             }},
            {"parameterMap", {
                                     {siteSearch::url,   {
                                                                 {"tag", "tagUrl_2"},
                                                                 {"id", "idUrl_2"},
                                                                 {"cssClass", "cssClassUrl_2"}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "tagCost_2"},
                                                                {"id", "idcCst_2"},
                                                                {"cssClass", "cssClassCost_2"}
                                                        }},
                                     {siteSearch::title, {
                                                                 {"tag", "tagTitle_2"},
                                                                 {"id", "idTitle_2"},
                                                                 {"cssClass", "cssClassTitle_2"}
                                                         }},
                                     {siteSearch::person, {
                                                                  {"tag", "tagPerson_2"},
                                                                  {"id", "idPerson_2"},
                                                                  {"cssClass", "cssClassPerson_2"}
                                                          }},
                                     {siteSearch::size, {
                                                                {"tag", "tagSize_2"},
                                                                {"id", "idSize_2"},
                                                                {"cssClass", "cssClassSize_2"}
                                                        }},
                                     {siteSearch::image, {
                                                                 {"tag", "tagImage_2"},
                                                                 {"id", "idImage_2"},
                                                                 {"cssClass", "cssClassImage_2"}
                                                         }}
                             }}
    };

    json settings = {
            {"chapters",
                      {siteSearch::index, siteSearch::man,  siteSearch::woman, siteSearch::boy,    siteSearch::girl}},
            {"parameters",
                      {siteSearch::url,   siteSearch::cost, siteSearch::title, siteSearch::person, siteSearch::size, siteSearch::image}},
            {"sites", {site_1,
                                          site_2
                      }}
    };

    return settings;
}

// Формируем запрос к БД из json от crawler
bd::Product Handlers::site_json_pars(const json& jv) {

    bd::Product prod;

    jv.at("UrlContent").get_to(prod.url_product);
    jv.at("CostContent").get_to(prod.price);
    jv.at("TitleContent").get_to(prod.name);
    jv.at("PersonContent").get_to(prod.param.person);
    jv.at("SizeContent").get_to(prod.param.size);
    jv.at("ImageContent").get_to(prod.url_image);

    return prod;
}

// Добавляем в избранное
http::response<http::string_body>
        Handlers::to_favorite(http::request<http::string_body> request) {
    json jv = json::parse(request.body());
    // id пользователя
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    // избранный товар
    int product_id;
    jv.at("product_id").get_to(product_id);
    // категория
    bd::Categories category;
    jv.at("category").get_to(category);

    bd::BI data_base;

    data_base.set_user_chosen(user_id, category, product_id);

    http::response<http::string_body> response;
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_length,
                 std::to_string(request.body().size()));
    response.set(http::field::content_type, "application/json");
    response.result(http::status::ok);
    response.body() = R"("Favorite item add.")";;

    return response;

}

// Получаем товар по критериям
http::response<http::string_body>
        Handlers::get_item(http::request<http::string_body> request) {
    json jv = json::parse(request.body());
    // проверка обновлений
    time_t result_hours = time(nullptr) / 3600;
    if (result_hours % 3 == 0)
        check_update(jv);
    // id пользователя
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    // опция поиска
    int option;
    jv.at("option").get_to(option);
    // избранный товар
    std::size_t product_id;
    jv.at("product_id").get_to(product_id);

    // переходим в product
    jv = jv.at("product");

    // выбранная категория
    bd::Categories category;
    jv.at("category").get_to(category);

    bd::BI data_base;
    std::vector<bd::Product> need_items;

    // избранный товар
    if (option == 1)  {
        need_items = data_base.get_user_chosen(user_id);
    }
    // с ценой меньше или равной указанной
    else if (option == 2) {
        std::size_t price;
        jv.at("price").get_to(price);

        need_items = data_base.search_down_price(category, price);
    }
    // по параметрам
    else if (option == 3) {
        bd::Parametrs params;
        json jv_params = jv.at("parametrs");
        // or params.id = jv_params["id"];
        jv_params.at("id").get_to(params.id);
        // or params.size = jv_params["size"];
        jv_params.at("size").get_to(params.size);
        // or params.color = jv_params["color"];
        jv_params.at("color").get_to(params.color);
        // or params.brand = jv_params["brand"];
        jv_params.at("brand").get_to(params.brand);

        need_items = data_base.search_parametrs(category, params);
    }
    // простой поиск по категории
    else
        need_items = data_base.get_products(category);

    // формирование ответа
    std::string response_user_body = get_user_body(user_id,
                                                   option, product_id);
    std::string response_product_body = "{\"Products\": [";
    for (const bd::Product& item: need_items) {
        response_product_body += get_product_body(item) + ",";
    }
    response_product_body.pop_back();
    response_product_body += "]}";
    http::response<http::string_body> response;
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_length,
                 std::to_string(response_product_body.size()));
    response.set(http::field::content_type, "application/json");
    response.result(http::status::ok);
    response.body() = response_user_body + response_product_body;
    return response;

}

// Проверяем обновления
void Handlers::check_update(const json& jv) {

    // формируем настройки сайтов (по чему нужнобегать)
    json json_setting = json_set(jv);
    Crawler crawler = Crawler(json_setting);

    // пробегаемся по сайтам и возвращаем найденные объекты
    json result_jsons = json::array();
    result_jsons = crawler.crawl(crawler.getSites(), crawler.getParameters(),
                        crawler.getChapters());

    bd::BI data_base;
    bd::Product prod;
    // Формирование запроса к БД из обновления
    for (json result_json: result_jsons) {
        prod = site_json_pars(result_jsons);
        // обновляем БД
        data_base.set_product(prod);
    }

}

