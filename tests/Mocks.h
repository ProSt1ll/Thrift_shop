#include <gmock/gmock.h>
#include "../include/MenuController.h"
#include "../include/Server.h"
#include "../include/Managment.h"
#include "../include/Menu.h"
#include "../include/SearchMenu.h"
#include "../include/json.hpp"

#ifndef TGBOT_MOCKS_H
#define TGBOT_MOCKS_H
using namespace Server;
class MockServerr {
public:
    MockServerr(): Server{};

    MOCK_METHOD( nlohmann::json, get_response, ());
};
class MockManagment {
public:
    MOCK_METHOD( nlohmann::json, Managment::get_product, (int *parametrs);
    MOCK_METHOD( nlohmann::json, create_html, std::string);
    MOCK_METHOD(std::set<Chapters>, getChapters, ());
    MOCK_METHOD(std::set<Parameters>, getParameters, ());

\
    MOCK_METHOD(bool, resetSettings, (json));
    MOCK_METHOD(json, crawl, (std::set<Parameters>, std::set<Chapters>));
    MOCK_METHOD(json, getSettings, ());

};

class MockCrawler {
public:

    // get методы

    MOCK_METHOD(std::set<Site>, getSites, ());
    MOCK_METHOD(std::set<Chapters>, getChapters, ());
    MOCK_METHOD(std::set<Parameters>, getParameters, ());

    // основной функционал

    MOCK_METHOD(json, crawl, (std::set<Site>, std::set<Parameters>, std::set<Chapters>));
    MOCK_METHOD(bool, resetSettings, (json));
    MOCK_METHOD(json, getSettings, ());
};

#endif //TGBOT_MOCKS_H