#include <gmock/gmock.h>
#include <string>
#include "../headers/interface_BD.h"

using namespace bd;

class MockBI : public BI {
public:
    MockBI() : BI() {}

    MOCK_METHOD(void,set_product,(Categories, Product));
    MOCK_METHOD(void,set_price,(Categories, std::string, float));
    MOCK_METHOD(void,set_url_image,(Categories, std::string, std::string));
    MOCK_METHOD(void,set_url_product,(Categories, std::string, std::string));
    MOCK_METHOD(void,set_parametrs,(Categories, std::string, Parametrs));

    MOCK_METHOD(Product*,get_products,(Categories));
    MOCK_METHOD(Product*,search_price,(Categories, float));
    MOCK_METHOD(Product*,search_parametrs,(Categories, Parametrs));

};
