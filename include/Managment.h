//#include "Client.h"

#ifndef TGBOT_MANAGMENT_H
#define TGBOT_MANAGMENT_H
#include <vector>
#include <string.h>
#include "json.hpp"
#include <boost/beast/http.hpp>
#include <tgbot/tgbot.h>

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

    Managment( TgBot::Bot *bot);

    ~Managment();


    void get_product(int search_parametr);
// запрос на сервер о требуемом продукте

    void add_favorite(int product_id);
// добавление в отслеживаемое

    void delete_favorite(int product_id);
// удаление из отслеживания
    void get_res(nlohmann::json request);
private:
    TgBot::Bot *bot_mnm;
    nlohmann::json create_req(std::string some);
// создание request на сервер по параметру

    void parse_res(nlohmann::json html,int type);
// получение информации из hml запроса
    void display(std::string url,int id);
};

#endif //TGBOT_MANAGMENT_H
