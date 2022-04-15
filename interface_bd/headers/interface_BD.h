#ifndef INTERFACE_BD_H
#define INTERFACE_BD_H
#include <sqlite3.h>
#include <string>

#define PATH_DB " "

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
        std::string brand;
        // "NULL"== NULL
    } Parametrs;

    typedef struct {
        std::string name;
        float price;
        std::string url_image;
        std::string url_product;
        Parametrs param;
    } Product;

    enum Categories {
        Sneakers, Shirts, Tshirts
    };

    class BI {
    private:
        sqlite3* DB;
    public:
        // конструктор будет открывать БД
        BI();

        // деструктор будет закрывать БД
        ~BI();

        // добавляем всё, кроме ссылки и цены(они в отдельной таблице), в таблицу с именем category. Если товар уже есть то обновляется запись
        void set_product(Categories category, Product prod, Parametrs param);

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
        std::string* get_user_chosen(std::string user_id);
    };

}

#endif // INTERFACE_BD_H
