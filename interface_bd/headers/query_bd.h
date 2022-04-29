#ifndef QUERY_BD_H
#define QUERY_BD_H
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>

#define server "localhost"
#define user "admin"
#define password "Technosquad"
#define database "products"

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

namespace bd{

    class Query_BD{
            private:
                MYSQL *conn;
            public:
                //устанавливает соединение с БД 
                Query_BD();

                //разрывает соединение с БД
                ~Query_BD();

                void create_all_tables();

                void delete_all_tables();

                const char* insert_into(const char* query);

                std::vector<std::string> select_from(const char* query);
    };

}
#endif // QUERY_BD_H
