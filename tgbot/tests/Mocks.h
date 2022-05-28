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

    MOCK_METHOD( void, start_accept, ());
    MOCK_METHOD(nlohmann::json, get_response, ());
    MOCK_METHOD( void, send_request, ());
    MOCK_METHOD( void, stop, ());
    MOCK_METHOD( void, run, ());


};

class MockManagment {
public:
    MOCK_METHOD( nlohmann::json, get_product, (int *parametrs));
    MOCK_METHOD( nlohmann::json, create_html, (std::string));
    MOCK_METHOD( void, add_favorite, (int));
    MOCK_METHOD( void, delete_favorite, (int));
    MOCK_METHOD( std::string, parse_html, (nlohmann::json));


};

#endif //TGBOT_MOCKS_H