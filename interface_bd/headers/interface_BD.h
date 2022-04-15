#ifndef INTERFACE_BD_H
#define INTERFACE_BD_H
#include <sqlite3.h>
#include <string>

#define PATH_DB " "

namespace bd {

    enum Colors {
        black, white, blue, red, orange, yellow, green
    };

    typedef struct {
        std::size_t size;
        Colors color;
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

        void set_product(Categories category, Product prod);

        void set_price(Categories category, std::string name, float price);

        void set_url_image(Categories category, std::string name, std::string url_image);

        void set_url_product(Categories category, std::string name, std::string url_product);

        void set_parametrs(Categories category, std::string name, Parametrs param);

        Product* get_products(Categories category);

        Product* search_price(Categories category, float price);

        Product* search_parametrs(Categories category, Parametrs param);
    };

}

#endif // INTERFACE_BD_H
