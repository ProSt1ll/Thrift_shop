#include <gmock/gmock.h>
#include <string>
#include "../headers/interface_BD.h"

using namespace bd;

class MockBI : public BI {
public:
    MockBI() : BI() {}

    MOCK_METHOD(void,set_product,(Categories, Product, Parametrs));
    MOCK_METHOD(void,set_url_product_price,(Categories,void(std::size_t price),void(std::string url_product)));

    MOCK_METHOD(Product*,get_products,(Categories));
    MOCK_METHOD(Product*,search_price,(Categories, float));
    MOCK_METHOD(Product*,search_parametrs,(Categories, Parametrs));

    MOCK_METHOD(void,set_user_chosen,(std::string, Categories, std::size_t));
    MOCK_METHOD(Product*,get_user_chosen,(std::string));

};
