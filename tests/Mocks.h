#include <gmock/gmock.h>
#include "../include/MenuController.h"
#include "../include/Server.h"
#include "../include/Managment.h"
#include "../include/Menu.h"
#include "../include/SearchMenu.h"
#include "../include/json.hpp"
#ifndef TGBOT_MOCKS_H
#define TGBOT_MOCKS_H

class MockServer {
public:

    MOCK_METHOD( nlohmann::json, get_response, ());
};

class MockManagment {
public:
    MOCK_METHOD( nlohmann::json, get_product, (int *parametrs));
    MOCK_METHOD( nlohmann::json, create_html, (std::string));


};

#endif //TGBOT_MOCKS_H