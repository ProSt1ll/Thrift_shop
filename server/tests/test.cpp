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
    request.body() = R"({"option":2,"user_id":"123qwery","product":{"category":"Dress","parameters":{"color":"Black","size":1}}})";

    http::response<http::string_body> response;

    EXPECT_NO_THROW(response = hand.get_item(request));

    json jv = json::parse(response.body());
    std::string user_id;
    jv.at("user_id").get_to(user_id);
    std::size_t product_id;
    jv.at("product_id").get_to(product_id);
    int option;
    jv.at("option").get_to(option);
    std::size_t price;
    jv.at("/product/price"_json_pointer).get_to(price);
    std::size_t id;
    jv.at("/product/parameters/id"_json_pointer).get_to(id);
    std::size_t size;
    jv.at("/product/parameters/size"_json_pointer).get_to(size);
    std::string brand;
    jv.at("/product/parameters/brand"_json_pointer).get_to(brand);
    std::string url_image;
    jv.at("/product/url_image"_json_pointer).get_to(url_image);
    std::string url_product;
    jv.at("/product/url_product"_json_pointer).get_to(url_product);

    EXPECT_EQ(user_id, "123qwery");
    EXPECT_EQ(option, 2);
    EXPECT_EQ(price, 62000);
    EXPECT_EQ(id, 1);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(url_image, "http://moda.oc-mod.ru/image/cache/catalog/revolution/demo_tovars/Fashion/Wooman/Odegda/Dresses/dress_1-228x228.jpg");
    EXPECT_EQ(url_product, "http://moda.oc-mod.ru/dress_1 ");

    EXPECT_EQ((int)response.result(), 200);

}


TEST(HANDLERS_TEST, TO_FAVORITE) {
    Handlers hand;

    http::request<http::string_body> request;
    request.body() = R"({"user_id":"123qwery","product":{"category":"Dress","parameters":{"id":2}}})";

    http::response<http::string_body> response;

    EXPECT_NO_THROW(response = hand.get_item(request));

    EXPECT_EQ(response.body(), "Favorite item add.");

    EXPECT_EQ((int)response.result(), 200);
}


int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
