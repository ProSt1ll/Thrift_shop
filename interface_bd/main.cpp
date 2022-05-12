#include "headers/interface_BD.h"
#include "headers/query_bd.h"

using namespace bd;

std::string ColorsToString( Colors color );
Colors StringToColors( std::string color_string );
std::string CategoriesToString(Categories catagory);

 main() {
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
      
        std::vector<Product> answer = interface.search_parametrs(Sneakers,prod.param);
        std::cout<<"\n"<< CategoriesToString(answer[0].category)<<"\n";

        interface.set_user_chosen("1",Sneakers,1);
        interface.set_user_chosen("1",Sneakers,2);

        answer = interface.get_user_chosen("1");
        std::cout<<"\n"<< answer[0].name <<"\n";
    }
