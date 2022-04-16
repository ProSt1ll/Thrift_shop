#include <gmock/gmock.h>
#include "../include/Connection.h"
#include "../include/Handler.h"
#include "../include/Router.h"
#include "../include/Server.h"

#ifndef SERVER_MOCKS_H
#define SERVER_MOCKS_H

class MockServer {
public:

    MOCK_METHOD(void, Run, ());
    MOCK_METHOD(void, StartAccept, ());
    MOCK_METHOD(void, HandleAccept, ());
    MOCK_METHOD(void, HandleStop, ());

};

class MockRouter {
public:

    MOCK_METHOD(void, addHandler, (std::string method, Handlers handler));
    MOCK_METHOD(http::response <http::string_body>,
    processRoute, (const std::string &method,
                 const http::request <http::string_body> &request));
};

class MockConnection {
public:

    MOCK_METHOD(void, start, ());

private:

    MOCK_METHOD(void, do_read, ());
    MOCK_METHOD(void, handle_read, (beast::error_code e,
                                 std::size_t bytes_transferred));
    MOCK_METHOD(void, handle_write, (bool close,
                                  beast::error_code e,
                                  std::size_t bytes_transferred));
    MOCK_METHOD(void, do_close, ());
};

class MockHandler {
public:

    MOCK_METHOD(http::response <http::string_body>,
            add_user, (http::request <http::string_body> request));
    MOCK_METHOD(http::response <http::string_body>,
            get_item, (http::request <http::string_body> request));

private:

    MOCK_METHOD(std::string, check_update, ());
    MOCK_METHOD(std::string, pars_param, (boost::json));
    MOCK_METHOD(boost::json, need_item, (Product));
};

#endif //SERVER_MOCKS_H
