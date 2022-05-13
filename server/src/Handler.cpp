#include "../include/Handler.h"

//std::map<std::string, std::string>
//Handlers::parse_params(const std::string &url) {
//    std::map<std::string, std::string> map_;
//    auto delimiterPos = url.find('?');
//    std::string params = url.substr(delimiterPos + 1);
//    std::string single_param, name, value;
//    while (!params.empty()) {
//        delimiterPos = params.find('&');
//        if (delimiterPos != std::string::npos) {
//            single_param = params.substr(0, delimiterPos);
//            params = params.substr(delimiterPos + 1);
//        } else {
//            single_param = params;
//            params = "";
//        }
//        delimiterPos = single_param.find('=');
//        name = single_param.substr(0, delimiterPos);
//        value = single_param.substr(delimiterPos + 1);
//        map_[name] = value;
//    }
//    return map_;
//}
//
//std::string Handlers::get_user_body(User user) {
//    // нужно узнать, что возвращает БД
//    json response_value = {
//        {"user",
//         {
//            {"user_id", user.id},
//            {"name", user.name},
//            {"login", user.login},
//            {"created_at", user.created_at}
//         }
//        }
//    };
//    return response_value.dump();
//}
//
//std::string Handlers::get_product_body(bd::Product product) {
//    json response_value = {
//            {"product_category",    product.category},
//            {"product_name",        product.name},
//            {"product_price",       product.price},
//            {"product_url_image",   product.url_image},
//            {"product_url_product", product.url_product},
//            {"product_param",       product.param}
//    };
//    return response_value.dump();
//}

http::response<http::string_body>
        Handlers::add_user(http::request<http::string_body> request) {
    http::response<http::string_body> response;
//    // парсим
//    json jv = json::parse(request.body());
//    // выбираем поле
//    jv = jv.at("user");
//    // имя пользователя из json
//    std::string name;
//    jv.at("name").get_to(name);
//    // логин пользователя из json
//    std::string user_id;
//    jv.at("user_id").get_to(user_id);
//    // КАКАЯ-ТО структура данных от клиента
//    UserForm userForm;
//    userForm.name = name;
//    userForm.login = user_id;
//    // добавляем пользователя в базу
//    auto user = bd::BI::add_user(userForm);
//
//    std::string response_body = get_user_body(user);

//    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//    response.set(http::field::content_length,
//                 std::to_string(response_body.size()));
//    response.set(http::field::content_type, "application/json");
//    response.result(http::status::ok);
//    response.body() = response_body;
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_length,
                 std::to_string(request.body().size()));
    response.set(http::field::content_type, "application/json");
    response.result(http::status::ok);
    response.body() = request.body();

    return response;
}

//http::response<http::string_body>
//        Handlers::get_item(http::request<http::string_body> request) {
//    std::string tar = static_cast<std::string>(request.target());
//    auto category = parse_params(tar);
//    // Тут определяем по каким параметрам нужно искать шмотку и обращаемся к БД
//    // вместо auto - std::vector<Product>
//    auto need_items = bd::BI::get_products(category);
//    // или auto need_items = bd::BI::search_down_price(category, price);
//    // или auto need_items = bd::BI::search_parametrs(category, param);
//    // или auto need_items = bd::BI::search_parametrs(category, param);
//
//    std::string responseBody = "{\"messages\": [";
//    for (auto &item: need_items) {
//        responseBody += get_product_body(item) + ",";
//    }
//    responseBody.pop_back();
//    responseBody += "]}";
//
//    http::response<http::string_body> response;
//    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
//    response.set(http::field::content_length,
//                 std::to_string(responseBody.size()));
//    response.set(http::field::content_type, "application/json");
//    response.result(http::status::ok);
//    response.body() = responseBody;
//
//    return response;

//}

//std::string Handlers::check_update() {
//
//}
//
//std::map<Categories, Parametrs> Handlers::pars_param(json json_) {
//
//}
//
//json Handlers::need_item(bd::Product item) {

//}
