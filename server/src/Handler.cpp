#include "../include/Handler.h"


std::string Handlers::get_user_body(std::string user_id,
                                    int option, std::size_t favorit_product_id) {
    json response_value = {
        {user_id, "user_id"},
        {option, "option"},
        {favorit_product_id, "favorit_product_id"}
    };
    return response_value.dump();
}

std::string Handlers::get_product_body(bd::Product product) {
    json response_value = {
        {"product",   {
            {product.category, "product_category"},
            {product.name, "product_name"},
            {product.price, "product_price"},
            {product.url_image, "product_url_image"},
            {product.url_product, "product_url_product"},
            {"product_param",   {
                {product.param.id, "id"},
                {product.param.size, "size"},
                {product.param.color, "color"},
                {product.param.brand, "brand"}
            }}
        }}};
    return response_value.dump();
}

http::response<http::string_body>
        Handlers::to_favorite(http::request<http::string_body> request) {
    json jv = json::parse(request.body());
    // id пользователя
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    // избранный товар
    std::size_t product_id;
    jv.at("product_id").get_to(product_id);
    // категория
    bd::Categories category;
    jv.at("category").get_to(category);

    bd::BI::set_user_chosen(user_id, category, product_id);

    http::response<http::string_body> response;
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_length,
                 std::to_string(request.body().size()));
    response.set(http::field::content_type, "application/json");
    response.result(http::status::ok);
    response.body() = R"("Favorite item add.")";;

    return response;

}


http::response<http::string_body>
        Handlers::get_item(http::request<http::string_body> request) {
    json jv = json::parse(request.body());
    // проверка обновлений
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

    // избранный товар
    if (option == 1)  {
        std::vector<bd::Product> need_items = bd::BI::get_user_chosen(user_id);
    }
    // с ценой меньше или равной указанной
    else if (option == 2) {
        std::size_t price;
        jv.at("price").get_to(price);

        std::vector<bd::Product> need_items = bd::BI::search_down_price(category, price);
    }
    // по параметрам
    else if (option == 3) {
        bd::Parametrs params;
        json jv_params = jv.at("parametrs");
        params.id = jv_params["id"];
        params.size = jv_params["size"];
        params.size = jv_params["size"];
        jv_params.at("color").get_to(params.color);
        std::string brand;
        params.brand = jv_params["brand"];

        std::vector<bd::Product> need_items = bd::BI::search_parametrs(category, params);
    }
    // простой поиск по категории
    else
        std::vector<bd::Product> need_items = bd::BI::get_products(category);
    // формирование ответа
    std::string response_user_body = get_user_body(user_id,
                                                   option, product_id);
    std::string response_product_body = "{\"Products\": [";
    for (bd::Product item: need_items) {
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

// В разработке...
std::string Handlers::check_update(json jv) {
    json new_items = crawl(std::set<siteSearch::Site> sites_,
                           std::set<siteSearch::Parameters> parameters_,
                           std::set<siteSearch::Chapters> chapters_)

    bd::Product prod site_json_pars(new_items);
    set_product(bd::Product prod);

    set_url_product_price(bd::Categories category, int id_prod, std::size_t price, std::string url_product);

    }

