#ifndef INTERFACE_BD_H
#define INTERFACE_BD_H
#include <string>
#include <vector>
#include <iterator>

#include <iostream>

namespace bd {

    enum Colors {
        None, White, Blue, Red, Orange, Yellow, Green, Black
    };

    typedef struct Parametrs{
        std::size_t id;
        // 0 == NULL
        std::string gender;
        // "NULL"== NULL, m - мужская, w-женская, u-неважно
        std::size_t size;
        // 0 == NULL
        Colors color;
        // None == NULL
        std::string brand;
        // "NULL"== NULL
        Parametrs();
    } Parametrs;

   #ifndef CATEGORIES
    #define CATEGORIES
    enum Categories {
        Empty , Sneakers, Shirts, Tshirts , Dress, Shorts, Skirts, Vintage_shoes
    };
    #endif // CATEGORIES

    typedef struct Product{
        Categories category;
        std::string name;
        std::size_t price;
        std::string url_image;
        std::string url_product;
        Parametrs param;
        Product();
    } Product;

    class BI {
    public:
        // добавляем всё, кроме ссылки и цены(их в отдельную таблицу), в таблицу с именем category. Если товар уже есть то обновляется запись
        void set_product(Product prod);

        // добавляем ссылку на товар и цену в таблицу catagory_url_price связанную с таблицой category:один(товар) ко многим(ссылкам+ценам). 
        void set_url_product_price(Categories category, int id_prod, std::size_t price, std::string url_product);

        // Возвращает все записи из данной категории 
        std::vector<Product> get_products(Categories category, std::string conditions = " ");

        // Возвращает все записи из данной категории с ценой меньше или равной указанной
        std::vector<Product> search_down_price(Categories category, std::size_t price);

        // Возвращает все записи из данной категории с определёнными параметрами
        std::vector<Product> search_parametrs(Categories category, Parametrs param);

        // В таблице пользователей создаёт запись об избранном товаре(отношение многие ко многим)
        void set_user_chosen(std::string user_id, Categories category, std::size_t product_id);

        // Возвращает избранное пользователем
        std::vector<Product> get_user_chosen(std::string user_id);
    };

}

#endif // INTERFACE_BD_H
