#include <gtest/gtest.h>
#include "../headers/interface_BD.h"
#include "../headers/query_bd.h"

using namespace bd;

std::string ColorsToString( Colors color );
Colors StringToColors( std::string color_string );
std::string CategoriesToString(Categories catagory);

TEST(create_all_tables, work) {
    Query_BD instance;
    instance.create_all_tables();
    std::vector<std::string> ot = instance.select_from("SHOW TABLES");
    EXPECT_EQ("Dress", ot[0]);
    EXPECT_EQ("Dress_urls", ot[1]);
    EXPECT_EQ("Shirts", ot[2]);
    EXPECT_EQ("Shirts_urls", ot[3]);
    EXPECT_EQ("Shorts", ot[4]);
    EXPECT_EQ("Shorts_urls", ot[5]);
    EXPECT_EQ("Skirts", ot[6]);
    EXPECT_EQ("Skirts_urls", ot[7]);
    EXPECT_EQ("Sneakers", ot[8]);
    EXPECT_EQ("Sneakers_urls", ot[9]);
    EXPECT_EQ("Tshirts", ot[10]);
    EXPECT_EQ("Tshirts_urls", ot[11]);
    EXPECT_EQ("Users", ot[12]);
    EXPECT_EQ("Users_chosen", ot[13]);
    EXPECT_EQ("Vintage_shoes", ot[14]);
    EXPECT_EQ("Vintage_shoes_urls", ot[15]);
}

TEST(insert_into__select_from, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();
    instance.insert_into("INSERT INTO Sneakers (name, url_image, brand, gender) VALUES ('Nike Air Force 1 Crater Next Nature','https://','Nike','m');");
    std::vector<std::string> ot = instance.select_from("SELECT * FROM Sneakers");
    EXPECT_EQ("1", ot[0]);//id
    EXPECT_EQ("Nike Air Force 1 Crater Next Nature", ot[1]);//name
    EXPECT_EQ("https://", ot[2]);//url_image
    EXPECT_EQ("NULL", ot[3]);//size
    EXPECT_EQ("m", ot[4]);//gender
    EXPECT_EQ("NULL", ot[5]);//color
    EXPECT_EQ("Nike", ot[6]);//brand
}

TEST(insert_into__select_from, wrong) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();
    instance.insert_into("INSERT eakers (name, url_image, brand) VALUES ('Nike Air Force 1 Crater Next Nature','https://','Nike');");
    std::vector<std::string> ot = instance.select_from("SELECT * FROM Sneakers");
    EXPECT_EQ(0, ot.size());
}

TEST(set_product, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_image = "http";
    prod.url_product = "http1";
    prod.param.brand = "Nike";
    BI interface;
    interface.set_product(prod);

    std::vector<std::string> ot = instance.select_from("SELECT Sneakers.name, Sneakers.url_image, Sneakers.size, Sneakers.color, Sneakers.brand, Sneakers_urls.price, Sneakers_urls.url_product FROM Sneakers INNER JOIN Sneakers_urls ON Sneakers.id = Sneakers_urls.product_id;");
    EXPECT_EQ("Nike Air Force 1 Crater Next Nature", ot[0]);
    EXPECT_EQ("http", ot[1]);
    EXPECT_EQ("NULL", ot[2]);
    EXPECT_EQ("NULL", ot[3]);
    EXPECT_EQ("Nike", ot[4]);
    EXPECT_EQ("10421", ot[5]);
    EXPECT_EQ("http1", ot[6]);
}

TEST(set_product, no_double) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_image = "http";
    prod.url_product = "http1";
    prod.param.brand = "Nike";
    BI interface;
    interface.set_product(prod);
    interface.set_product(prod);

    std::vector<std::string> ot = instance.select_from("SELECT Sneakers.name, Sneakers.url_image, Sneakers.size, Sneakers.color, Sneakers.brand, Sneakers_urls.price, Sneakers_urls.url_product FROM Sneakers INNER JOIN Sneakers_urls ON Sneakers.id = Sneakers_urls.product_id;");
    EXPECT_EQ(7, ot.size());//!
    EXPECT_EQ("Nike Air Force 1 Crater Next Nature", ot[0]);
    EXPECT_EQ("http", ot[1]);
    EXPECT_EQ("NULL", ot[2]);
    EXPECT_EQ("NULL", ot[3]);
    EXPECT_EQ("Nike", ot[4]);
    EXPECT_EQ("10421", ot[5]);
    EXPECT_EQ("http1", ot[6]);
}

TEST(set_url_product_price, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();
    instance.insert_into("INSERT INTO Sneakers (name, url_image, brand) VALUES ('Nike Air Force 1 Crater Next Nature','https://','Nike');");

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_product = "http1";
    BI url_price;
    std::string temp_query = "SELECT id FROM " + CategoriesToString(prod.category) + " WHERE name = '" + prod.name + "';";
    std::vector<std::string> id_string = instance.select_from(temp_query.c_str());
    int id = std::stoi(id_string[0]);
    url_price.set_url_product_price(prod.category, id, prod.price, prod.url_product);

    std::vector<std::string> ot = instance.select_from("SELECT * FROM Sneakers_urls;");
    EXPECT_EQ("1", ot[0]); //id
    EXPECT_EQ("1", ot[1]); //product_id
    EXPECT_EQ("10421", ot[2]); //price
    EXPECT_EQ("http1", ot[3]); //url_product
}

TEST(get_products, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_image = "http";
    prod.url_product = "http1";
    prod.param.brand = "Nike";
    BI interface;
    interface.set_product(prod);
    std::vector<Product> ot = interface.get_products(prod.category);

    EXPECT_EQ(Sneakers, ot[0].category);
    EXPECT_EQ("Nike Air Force 1 Crater Next Nature", ot[0].name);
    EXPECT_EQ("http", ot[0].url_image);
    EXPECT_EQ(1, ot[0].param.id);
    EXPECT_EQ(0, ot[0].param.size);
    EXPECT_EQ(None, ot[0].param.color);
    EXPECT_EQ("Nike", ot[0].param.brand);
    EXPECT_EQ(10421, ot[0].price);
    EXPECT_EQ("http1", ot[0].url_product);
}

TEST(search_down_price, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_image = "http";
    prod.url_product = "http1";
    prod.param.brand = "Nike";
    BI interface;
    interface.set_product(prod);

    prod.category = Sneakers;
    prod.name = "Nike";
    prod.price = 1421;
    prod.url_image = "http";
    prod.url_product = "http2";
    prod.param.brand = "Nike";
    interface.set_product(prod);
    std::vector<Product> ot = interface.search_down_price(prod.category,2000);

    EXPECT_EQ(Sneakers, ot[0].category);
    EXPECT_EQ("Nike", ot[0].name);
    EXPECT_EQ("http", ot[0].url_image);
    EXPECT_EQ(0, ot[0].param.size);
    EXPECT_EQ(None, ot[0].param.color);
    EXPECT_EQ("Nike", ot[0].param.brand);
    EXPECT_EQ(1421, ot[0].price);
    EXPECT_EQ("http2", ot[0].url_product);
}

TEST(search_parametrs, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_image = "http";
    prod.url_product = "http1";
    prod.param.brand = "Nike";
    prod.param.size = 45;
    BI interface;
    interface.set_product(prod);

    prod.category = Sneakers;
    prod.name = "Nike";
    prod.price = 1421;
    prod.url_image = "http";
    prod.url_product = "http2";
    prod.param.brand = "Nike";
    prod.param.size = 47;
    interface.set_product(prod);

    std::vector<Product> ot = interface.search_parametrs(prod.category,prod.param);

    EXPECT_EQ(Sneakers, ot[0].category);
    EXPECT_EQ("Nike", ot[0].name);
    EXPECT_EQ("http", ot[0].url_image);
    EXPECT_EQ(47, ot[0].param.size);
    EXPECT_EQ(None, ot[0].param.color);
    EXPECT_EQ("Nike", ot[0].param.brand);
    EXPECT_EQ(1421, ot[0].price);
    EXPECT_EQ("http2", ot[0].url_product);
}

TEST(user_chosen, right) {
    Query_BD instance;
    instance.delete_all_tables();
    instance.create_all_tables();

    Product prod;
    prod.category = Sneakers;
    prod.name = "Nike Air Force 1 Crater Next Nature";
    prod.price = 10421;
    prod.url_image = "http";
    prod.url_product = "http1";
    prod.param.brand = "Nike";
    prod.param.size = 45;
    BI interface;
    interface.set_product(prod);

    prod.category = Sneakers;
    prod.name = "Nike";
    prod.price = 1421;
    prod.url_image = "http";
    prod.url_product = "http2";
    prod.param.brand = "Nike";
    prod.param.size = 47;
    interface.set_product(prod);

    interface.set_user_chosen("1",Sneakers,1);
    interface.set_user_chosen("1",Sneakers,2);

    std::vector<Product> ot = interface.get_user_chosen("1");

    EXPECT_EQ("Nike Air Force 1 Crater Next Nature", ot[0].name);
    EXPECT_EQ("http", ot[0].url_image);
    EXPECT_EQ(45, ot[0].param.size);
    EXPECT_EQ(None, ot[0].param.color);
    EXPECT_EQ("Nike", ot[0].param.brand);
    EXPECT_EQ(10421, ot[0].price);
    EXPECT_EQ("http1", ot[0].url_product);

    EXPECT_EQ(Sneakers, ot[1].category);
    EXPECT_EQ("Nike", ot[1].name);
    EXPECT_EQ("http", ot[1].url_image);
    EXPECT_EQ(47, ot[1].param.size);
    EXPECT_EQ(None, ot[1].param.color);
    EXPECT_EQ("Nike", ot[1].param.brand);
    EXPECT_EQ(1421, ot[1].price);
    EXPECT_EQ("http2", ot[1].url_product);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
