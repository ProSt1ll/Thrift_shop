//
// Created by ivan on 26.05.22.
//

#include <gtest/gtest.h>

#include <boost/beast/core.hpp>

#include "../include/Handler.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using nlohmann::json;

TEST(HANDLERS_TEST, AddUser) {
    Handlers hand;
    http::request<http::string_body> request;
    http::response<http::string_body> response;

    {"user_id", "123qwery"},
    {"option", 3},
    {"product_id", 0},
    {"product", {
                {"category", 1},
                {"price", 100},
                {"url_image", "url_imag"},
                {"url_product", "url_prod"},
                {"parameters", {
                                     {"id", 15},
                                     {"size", 2},
                                     {"color", 1},
                                     {"brand", "gucci"}
                             }
                }
        }
    }
    request.body() = R"({
                          "user_id":"123qwery",
"user_id":"123qwery",
                          "c": {
                            "f": null
                          }
                        })";
    EXPECT_NO_THROW(response = hand.AddUser(request));
    json::value jv = json::parse(response.body());
    json::object const &obj = jv.as_object();
    jv = obj.at("user");
    auto login = json::value_to<std::string>(obj.at("login"));
    auto name = json::value_to<std::string>(obj.at("name"));
    EXPECT_EQ(login, "login_test");
    EXPECT_EQ(name, "name_test");
    EXPECT_TRUE((json::value_to<boost::json::array>(obj.at("chats_id"))).empty());
    EXPECT_EQ((int)response.result(), 200);
    request.body() = "{\"user\": \n"
                     "\t{\n"
                     "\t\"login\": \"login_test\",\n"
                     "\t\"name\": \"name_test\",\n"
                     "\t\"password\": \"password_test\",\n"
                     "\t\"profile_avatar\": \"\""
                     "\t}\n"
                     "}";
    EXPECT_THROW(response = hand.AddUser(request), pqxx::unique_violation);
}


TEST(HANDLERS_TEST, GetUser) {
    Handlers hand;
    http::request<http::string_body> request;
    http::response<http::string_body> response;
    request.target("/user_info?id=1");
    EXPECT_NO_THROW(response = hand.GetUser(request));
    json::value jv = json::parse(response.body());
    json::object const &obj = jv.as_object();
    jv = obj.at("user");
    auto login = json::value_to<std::string>(obj.at("login"));
    auto name = json::value_to<std::string>(obj.at("name"));
    EXPECT_EQ(login, "user1");
    EXPECT_EQ(name, "name1");
    EXPECT_EQ(json::value_to<boost::json::array>(obj.at("chats_id")), json::array({1,2,3}));
    EXPECT_EQ((int)response.result(), 200);
}


int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
