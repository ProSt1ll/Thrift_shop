#include <gmock/gmock.h>
#include <string>
#include "../headers/interface_BD.h"
#include "../headers/query_bd.h"

using namespace bd;

class MockBI : public BI {
public:
    MOCK_METHOD(void,set_product,(Product, Parametrs));
    MOCK_METHOD(void,set_url_product_price,(Categories,void(std::size_t price),void(std::string url_product)));

    MOCK_METHOD(std::vector<Product>,get_products,(Categories));
    MOCK_METHOD(std::vector<Product>,search_price,(Categories, float));
    MOCK_METHOD(std::vector<Product>,search_parametrs,(Categories, Parametrs));

    MOCK_METHOD(void,set_user_chosen,(std::string, Categories, std::size_t));
    MOCK_METHOD(std::vector<Product>,get_user_chosen,(std::string));

};

class MockQuery_BD : public Query_BD {
public:
    MockQuery_BD() : Query_BD() {}

    MOCK_METHOD(void,insert_into,(Categories, std::string));
    MOCK_METHOD(std::string,select_from,(Categories,std::string));
};
