#ifndef INTERFACE_BD_H
#define INTERFACE_BD_H
#include <string>
#include <vector>

namespace bd {

    enum Colors {
        None, White, Blue, Red, Orange, Yellow, Green, Black
    };

    typedef struct {
        std::size_t id;
        // 0 == NULL
        std::size_t size;
        // 0 == NULL
        Colors color;
        // None == NULL
        std::vector<std::string> brand;
        // "NULL"== NULL
    } Parametrs;

   #ifndef CATEGORIES
    #define CATEGORIES
    enum Categories {
        Sneakers, Shirts, Tshirts
    };

    char* CategoriesToString( Categories catagory ) {
     switch( catagory ){
     case Sneakers:
         {
             return "Sneakers";
             break;
         }
     case Shirts:
         {
             return "Shirts";
             break;
         }
     case Tshirts:
         {
             return "Tshirts";
             break;
         }
     }
    }
    #endif // CATEGORIES

    typedef struct {
        Categories category;
        std::string name;
        float price;
        std::string url_image;
        std::string url_product;
        Parametrs param;
    } Product;

    class BI {
    public:
        // добавляем всё, кроме ссылки и цены(их в отдельную таблицу), в таблицу с именем category. Если товар уже есть то обновляется запись
        void set_product(Product prod, Parametrs param);

        // добавляем ссылку на товар и цену в таблицу catagory_url_price связанную с таблицой category:один(товар) ко многим(ссылкам+ценам). 
        void set_url_product_price(Categories category, std::size_t price = -1, std::string url_product = "NULL");

        // Возвращает все записи из данной категории 
        Product* get_products(Categories category);

        // Возвращает все записи из данной категории с ценой меньше или равной указанной
        Product* search_down_price(Categories category, float price);

        // Возвращает все записи из данной категории с определёнными параметрами
        Product* search_parametrs(Categories category, Parametrs param);

        // В таблице пользователей создаёт запись об избранном товаре(отношение многие ко многим)
        void set_user_chosen(std::string user_id, Categories category, std::size_t product_id);

        // Возвращает избранное пользователем
        Product* get_user_chosen(std::string user_id);
    };

}

#endif // INTERFACE_BD_H
