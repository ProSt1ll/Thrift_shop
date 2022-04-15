#include "../headers/interface_BD.h"

using namespace bd;

BI::BI(){
    sqlite3_open(PATH_DB, &DB);
}

BI::~BI(){
        sqlite3_close(DB);
}

void BI::set_product(Categories category, Product prod){

}

void BI::set_price(Categories category, std::string name, float price){

}

void BI::set_url_image(Categories category, std::string name, std::string url_image){

}

void BI::set_url_product(Categories category, std::string name, std::string url_product){

}

void BI::set_parametrs(Categories category, std::string name, Parametrs param){

}

Product* BI::get_products(Categories category){

}

Product* BI::search_price(Categories category, float price){

}

Product* BI::search_parametrs(Categories category, Parametrs param){

}
