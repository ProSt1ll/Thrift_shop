#ifndef TGBOT_MANAGMENT_H
#define TGBOT_MANAGMENT_H
#include <vector>
#include <string.h>
#include "json.hpp"
#include <boost/beast/http.hpp>
#include <tgbot/tgbot.h>
#include "Client.h"
#include "MenuController.h"

const std::string port = "5000";
const std::string server = "127.0.0.1";

class Package {
public:
    nlohmann::json j;

    Package() {
        j["Type"] = 0;
        j["Item"];
        j["Size"] = 0;
    }
};

class Item {
public:
    std::vector<std::string> urls;
    std::vector<int> prices;
};

class Managment {
public:
    std::vector<int> *search_parametrs;

    Managment():tgbot("5341881620:AAFENTOHJUFUwmpvyLun51Yu5FLmesHvZYU"){
        std::make_shared<Client>(io_context)->run(const_cast<std::string &>(server), port);
    };

    ~Managment();

    void run();
    void get_product(int search_parametr);
// запрос на сервер о требуемом продукте

    void add_favorite(int product_id);
// добавление в отслеживаемое

    void delete_favorite(int product_id);
// удаление из отслеживания
    void get_res(nlohmann::json request);

    void get_mes(std::string message);

    TgBot::Bot *bot_mnm;
    nlohmann::json create_req(std::string some);
// создание request на сервер по параметру

    void parse_res(nlohmann::json html,int type);
// получение информации из hml запроса
    void display(std::string url,int id);
    net::io_context io_context;
    MenuController tgbot;
};

#endif //TGBOT_MANAGMENT_H
