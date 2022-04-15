#include "../headers/interface_BD.h"

using namespace bd;

BI::BI(){
    sqlite3_open(PATH_DB, &DB);
}

BI::~BI(){
        sqlite3_close(DB);
}

// добавляем всё, кроме ссылки и цены(они в отдельной таблице), в таблицу с именем category. Если товар уже есть то обновляется запись
        void set_product(Categories category, Product prod, Parametrs param){

        }

        // добавляем ссылку на товар и цену в таблицу catagory_url_price связанную с таблицой category:один(товар) ко многим(ссылкам+ценам). 
        void set_url_product_price(Categories category, std::size_t price = -1, std::string url_product = "NULL"){
            
        }

        // Возвращает все записи из данной категории 
        Product* get_products(Categories category){
            
        }

        // Возвращает все записи из данной категории с ценой меньше или равной указанной
        Product* search_down_price(Categories category, float price){
            
        }

        // Возвращает все записи из данной категории с определёнными параметрами
        Product* search_parametrs(Categories category, Parametrs param){
            
        }

        // В таблице пользователей создаёт запись об избранном товаре(отношение многие ко многим)
        void set_user_chosen(std::string user_id, Categories category, std::size_t product_id){
            
        }

        // Возвращает избранное пользователем
        Product* get_user_chosen(std::string user_id){
            
        }
