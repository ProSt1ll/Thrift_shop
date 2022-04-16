#include "Server.h"
#include <vector>
#include <string.h>

#ifndef TGBOT_MANAGMENT_H
#define TGBOT_MANAGMENT_H

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
    int *search_parametrs;

    Managment();

    ~Managment();


    nlohmann::json get_product(int *search_parametr);
// запрос на сервер о требуемом продукте

    void add_favorite(int product_id);
// добавление в отслеживаемое

    void delete_favorite(int product_id);
// удаление из отслеживания
private:
    Server server;

    nlohmann::json create_html(std::string some);
// создание html запроса на сервер по параметру

    std::string parse_html(nlohmann::json html);
// получение информации из hml запроса
};

#endif TGBOT_MANAGMENT_H