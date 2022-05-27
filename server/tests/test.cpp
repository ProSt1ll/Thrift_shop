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

TEST(HANDLERS_TEST, GET_ITEM) {
    Handlers hand;

    http::request<http::string_body> request;
    request.body() = R"({"option":3,"product_id":42,"user_id":"123qwery","product":{"category":1,"parameters":{"brand":"gucci","color":2,"id":15,"size":2},"price":100,"url_image":"url_imag","url_product":"url_prod"}})";

    http::response<http::string_body> response;

    EXPECT_NO_THROW(response = hand.to_favorite(request));

    json jv = json::parse(response.body());
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    std::size_t product_id;
    jv.at("product_id").get_to(product_id);
    int option;
    jv.at("option").get_to(option);
    bd::Categories category;
    jv.at("/product/category"_json_pointer).get_to(category);
    std::size_t price;
    jv.at("/product/price"_json_pointer).get_to(price);
    std::size_t id;
    jv.at("/product/parameters/id"_json_pointer).get_to(id);
    std::size_t size;
    jv.at("/product/parameters/size"_json_pointer).get_to(size);
    int color;
    jv.at("/product/parameters/color"_json_pointer).get_to(color);
    std::string brand;
    jv.at("/product/parameters/brand"_json_pointer).get_to(brand);
    std::string url_image;
    jv.at("/product/url_image"_json_pointer).get_to(url_image);
    std::string url_product;
    jv.at("/product/url_product"_json_pointer).get_to(url_product);

    EXPECT_EQ(user_id, "123qwery");
    EXPECT_EQ(product_id, 42);
    EXPECT_EQ(option, 3);
    EXPECT_EQ(category, 1);
    EXPECT_EQ(price, 100);
    EXPECT_EQ(id, 15);
    EXPECT_EQ(size, 15);
    EXPECT_EQ(color, 2);
    EXPECT_EQ(brand, "gucci");
    EXPECT_EQ(url_image, "url_imag");
    EXPECT_EQ(url_product, "url_prod");

    EXPECT_EQ((int)response.result(), 200);

//    request.body() = R"({"option":3,"product_id":42,"user_id":"123qwery","product":{"category":1,"parameters":{"brand":"gucci","color":2,"id":15,"size":2},"price":100,"url_image":"url_imag","url_product":"url_prod"}})";
//    EXPECT_THROW(response = hand.to_favorite(request), pqxx::unique_violation);
}


TEST(HANDLERS_TEST, TO_FAVORITE) {
    Handlers hand;

    http::request<http::string_body> request;
    request.body() = R"({"option":3,"product_id":42,"user_id":"123qwery","product":{"category":1,"parameters":{"brand":"gucci","color":2,"id":15,"size":2},"price":100,"url_image":"url_imag","url_product":"url_prod"}})";

    http::response<http::string_body> response;

    EXPECT_NO_THROW(response = hand.get_item(request));

    EXPECT_EQ(response.body(), "Favorite item add.");

    EXPECT_EQ((int)response.result(), 200);
}


int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
