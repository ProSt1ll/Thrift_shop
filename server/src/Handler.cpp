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
                                     {siteSearch::womanOuter, "/wooman/wooman_odegda/wooman_dresses/"},
                                     {siteSearch::womanDown, "/wooman/wooman_odegda/wooman_skirts/"},
                                     {siteSearch::womanShoes,   "/wooman/wooman_shoes/wooman_tufli/"}
                             }},
            {"parameterMap", {
                                     {siteSearch::title, {
                                                                 {"tag", "span"},
                                                                 {"id", "itemprop=\"name\""},
                                                                 {"cssClass", ""}
                                                         }},
                                     {siteSearch::cost,       {
                                                                      {"tag", "span"},
                                                                      {"id", " "},
                                                                      {"cssClass", "class=\"price_no_format"}
                                                              }},
                                     {siteSearch::url,       {
                                                                     {"tag", "link"},
                                                                     {"id", " "},
                                                                     {"cssClass", "itemprop=\"url\""}
                                                             }},
                                     {siteSearch::image,     {
                                                                        {"tag", "img"},
                                                                        {"id", " "},
                                                                        {"cssClass", "img-responsive"}
                                                                }},
                                     {siteSearch::itemTemplate, {
                                                                        {"tag", "div"},
                                                                        {"id", ""},
                                                                        {"cssClass", "class=\"product-layout product-list"}
                                                                }}
                             }}
    };
    json settings = {
            {"chapters",
                      {siteSearch::index, siteSearch::womanOuter, siteSearch::womanDown, siteSearch::womanShoes}},
            {"parameters",
                      {siteSearch::url,   siteSearch::cost,    siteSearch::title,     siteSearch::person, siteSearch::size, siteSearch::image}},
            {"sites", {site_1}}
    };

    return settings;
}

// Формируем запрос к БД из json от crawler
bd::Product Handlers::site_json_pars(const json& jv) {

    bd::Product prod;

    jv.at("0").get_to(prod.url_product);
    std::string str_price;
    jv.at("1").get_to(str_price);
    prod.price = std::stoi(str_price);
    jv.at("2").get_to(prod.name);
//    std::string str_size;
//    jv.at("4").get_to(str_size);
    prod.param.size = 1;
    jv.at("5").get_to(prod.url_image);

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
    std::size_t product_id;
    jv.at("/product/parameters/id"_json_pointer).get_to(product_id);

    // выбранная категория;
    std::string str_category;
    jv.at("/product/category"_json_pointer).get_to(str_category);
    bd::Categories category = str_to_category(str_category);

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

    json jv = json::parse(R"({"option":2,"user_id":"123qwery","product":{"category":"Dress","parameters":{"brand":"gucci","color":"Black","id":15,"size":2},"price":40000,"url_image":"url_imag","url_product":"url_prod"}})");

    // проверка обновлений/заполнение базы
//    time_t result_hours = time(nullptr) / 3600;
//    if (result_hours % 3 == 0)
    update_bd();
    // id пользователя
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    // опция поиска
    int option;
    jv.at("option").get_to(option);

    // выбранная категория;
    std::string str_category;
    jv.at("/product/category"_json_pointer).get_to(str_category);
    bd::Categories category = str_to_category(str_category);

    bd::BI data_base;
    std::vector<bd::Product> need_items;

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
        jv.at("/product/parameters/size"_json_pointer).get_to(params.size);
        std::string param_color;
        jv.at("/product/parameters/color"_json_pointer).get_to(param_color);
        params.color = str_to_color(param_color);

        need_items = data_base.search_parametrs(category, params);

    }
    // простой поиск по категории
    else
        need_items = data_base.get_products(category);

    // формирование ответа
    json response_value = {
            {"user_id", user_id},
            {"option", 2}
    };
    std::string response_user_body = response_value.dump();

    response_user_body.pop_back();
    std::string response_product_body = ",\"product\":[";

    for (const bd::Product& item: need_items) {
        response_product_body += get_product_body(item) + ",";
    }

    response_product_body.pop_back();
    response_product_body += "]}";
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
    json result_jsons;

    bd::BI data_base;
    bd::Product prod;

    result_jsons = crawler.crawl(crawler.getSites(), crawler.getParameters(),
                                 std::set<siteSearch::Chapters>{siteSearch::womanOuter});
    std::cout << result_jsons << std::endl;
    // Формирование запроса к БД из обновления
    for (const auto &res_json: result_jsons) {
        prod = site_json_pars(res_json);
        prod.category = bd::Categories::Dress;
        // обновляем БД
        data_base.set_product(prod);
    }

    result_jsons = crawler.crawl(crawler.getSites(), crawler.getParameters(),
                                 std::set<siteSearch::Chapters>{siteSearch::womanDown});
    std::cout << result_jsons << std::endl;
    // Формирование запроса к БД из обновления
    for (const auto &res_json: result_jsons) {
        prod = site_json_pars(res_json);
        prod.category = bd::Categories::Skirts;
        // обновляем БД
        data_base.set_product(prod);
    }

    result_jsons = crawler.crawl(crawler.getSites(), crawler.getParameters(),
                                 std::set<siteSearch::Chapters>{siteSearch::womanShoes});
    std::cout << result_jsons << std::endl;
    // Формирование запроса к БД из обновления
    for (const auto &res_json: result_jsons) {
        prod = site_json_pars(res_json);
        prod.category = bd::Categories::Vintage_shoes;
        // обновляем БД
        data_base.set_product(prod);
    }

}


bd::Colors Handlers::str_to_color(const std::string& color_string ) {
    if(color_string =="White")
        return bd::Colors::White;
    if(color_string =="Blue")
        return bd::Colors::Blue;
    if(color_string == "Red")
        return bd::Colors::Red;
    if(color_string == "Orange")
        return bd::Colors::Orange;
    if(color_string == "Yellow")
        return bd::Colors::Yellow;
    if(color_string == "Green")
        return bd::Colors::Green;
    if(color_string == "Black")
        return bd::Colors::Black;

    return bd::Colors::None;
}

bd::Categories Handlers::str_to_category(const std::string& category_string ) {
    if(category_string =="Sneakers")
        return bd::Categories::Sneakers;
    if(category_string =="Shirts")
        return bd::Categories::Shirts;
    if(category_string == "Tshirts")
        return bd::Categories::Tshirts;
    if(category_string == "Dress")
        return bd::Categories::Dress;
    if(category_string == "Shorts")
        return bd::Categories::Shorts;
    if(category_string == "Skirts")
        return bd::Categories::Skirts;
    if(category_string == "Vintage_shoes")
        return bd::Categories::Vintage_shoes;

    return bd::Categories::Empty;
}