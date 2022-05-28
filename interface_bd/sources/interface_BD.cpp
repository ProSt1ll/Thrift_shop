#include "../headers/interface_BD.h"
#include "../headers/query_bd.h"

using namespace bd;

        Parametrs::Parametrs(){
                id = 0;
                gender = "NULL";
                size = 0;
                color = None;
                brand = "NULL";
        }

        Product::Product(){
                category = Empty;
                name = "NULL";
                price = 0;
                url_image = "NULL";
                url_product = "NULL";
        }

        std::string ColorsToString( Colors color ) {
                switch( color ){
                case White:
                {
                return "White";
                break;
                }
                case Blue:
                {
                return "Blue";
                break;
                }
                case Red:
                {
                return "Red";
                break;
                }
                case Orange:
                {
                return "Orange";
                break;
                }
                case Yellow:
                {
                return "Yellow";
                break;
                }
                case Green:
                {
                return "Green";
                break;
                }
                case Black:
                {
                return "Black";
                break;
                }
        }
        }

        Colors StringToColors( std::string color_string ) {
                if(color_string == "NULL") 
                {
                return None;
                }
                if(color_string =="White") 
                {
                return White;
                }
                if(color_string =="Blue")
                {
                return Blue;
                }
                if(color_string == "Red")
                {
                return Red;
                }
                if(color_string == "Orange")
                {
                return Orange;
                }
                if(color_string == "Yellow")
                {
                return Yellow;
                }
                if(color_string == "Green")
                {
                return Green;
                }
                if(color_string == "Black")
                {
                return Black;
                }
        }

        std::string CategoriesToString( Categories catagory ) {
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
        case Dress:
                {
                return "Dress";
                break;
                }
        case Shorts:
                {
                return "Shorts";
                break;
                }
        case Skirts:
                {
                return "Skirts";
                break;
                }
        case Vintage_shoes:
                {
                return "Vintage_shoes";
                break;
                }
        }
        }

        // добавляем всё, кроме ссылки и цены(их в отдельную таблицу), в таблицу с именем category. Если товар уже есть то обновляется запись
        void BI::set_product(Product prod){
                std::string temp_parametrs;
                if(prod.param.size != 0)
                        temp_parametrs += ",size";
                if(prod.param.gender != "NULL")
                        temp_parametrs += ",gender";
                if(prod.param.color != None)
                        temp_parametrs += ",color";

                if(prod.param.brand != "NULL")
                        temp_parametrs += ",brand";
                temp_parametrs += " ";

                std::string temp_query = "INSERT INTO " + CategoriesToString(prod.category) + " (name, url_image" + temp_parametrs + ")" + " VALUES " + "('" + prod.name + "','" + prod.url_image + "'";

                if(prod.param.size != 0){
                        temp_query += ",'" + std::to_string(prod.param.size) + "'";
                }

                if(prod.param.gender != "NULL"){
                        temp_query += ",'" + prod.param.gender + "'";
                }

                if(prod.param.color != None){
                        temp_query += ",'" + ColorsToString(prod.param.color) + "'";
                }

                if(prod.param.brand != "NULL"){
                        temp_query += ",'" + prod.param.brand + "'";
                }

                temp_query += ");";

                Query_BD instance;
                if(instance.insert_into(temp_query.c_str()))
                        printf("\nerror\n"); 

                temp_query = "SELECT id FROM " + CategoriesToString(prod.category) + " WHERE name = '" + prod.name + "'";

                if(prod.param.size != 0){
                        temp_query += " AND size ='" + std::to_string(prod.param.size) + "'";
                }

                if(prod.param.gender != "NULL"){
                        temp_query += " AND gender = '" + prod.param.gender + "'";
                }

                if(prod.param.color != None){
                        temp_query += " AND color = '" + ColorsToString(prod.param.color) + "'";
                }

                if(prod.param.brand != "NULL"){
                        temp_query += " AND brand = '" + prod.param.brand + "'";
                }

                temp_query += ";";

                std::vector<std::string> id_string = instance.select_from(temp_query.c_str());
                int id = std::stoi(id_string[0]);

                BI url_price;

                url_price.set_url_product_price(prod.category, id, prod.price, prod.url_product);
                
        }

        // добавляем ссылку на товар и цену в таблицу catagory_url связанную с таблицой category:один(товар) ко многим(ссылкам+ценам), нет проверки параметров
        void BI::set_url_product_price(Categories category, int id_prod, std::size_t price, std::string url_product){
            std::string query_url = "INSERT INTO " + CategoriesToString(category) + "_urls" + " (product_id,price,url_product) VALUES ('" + std::to_string(id_prod) + "','" + std::to_string(price) + "','" + url_product + "');";

            Query_BD instance;
                if(instance.insert_into(query_url.c_str()))
                        printf("\nerror\n"); 
        }

        // Возвращает все записи из данной категории 
        std::vector<Product> BI::get_products(Categories category, std::string conditions){
            Query_BD instance;
            std::string name_table = CategoriesToString(category);
            std::string query = "SELECT " + name_table + ".name, " + name_table + ".url_image, " + name_table + ".size, " + name_table + ".gender, " + name_table + ".color, " + name_table + ".brand, " + name_table + "_urls.price, " + name_table + "_urls.url_product, " + name_table + ".id" + " FROM " + name_table +" INNER JOIN " + name_table + "_urls ON " + name_table + ".id = " + name_table + "_urls.product_id" + conditions + ";";

            std::vector<std::string> category_products = instance.select_from(query.c_str());
            std::vector<Product> res_products; 
            res_products.resize(category_products.size()/9);
            int j = 0;
            for(int i = 0; i < category_products.size()/9; i++ ){
                    res_products[i].category = category;
                    res_products[i].name = category_products[j];
                    j++;
                    res_products[i].url_image = category_products[j];
                    j++;
                    if(category_products[j] != "NULL")
                        res_products[i].param.size = std::stoi(category_products[j]);
                    else res_products[i].param.size = 0;
                    j++;
                    if(category_products[j] != "NULL")
                        res_products[i].param.gender = category_products[j];
                    else res_products[i].param.gender = "NULL";
                    j++;
                    if(category_products[j] != "NULL")
                        res_products[i].param.color = StringToColors(category_products[j]);
                    else res_products[i].param.color = None;
                    j++;
                    if(category_products[j] != "NULL")
                        res_products[i].param.brand = category_products[j];
                    else res_products[i].param.brand = "NULL";
                    j++;
                    res_products[i].price = std::stoi(category_products[j]);
                    j++;
                    res_products[i].url_product = category_products[j];
                    j++;
                    res_products[i].param.id = std::stoi(category_products[j]);
                    j++;
            }

            return res_products;
        }

        // Возвращает все записи из данной категории с ценой меньше или равной указанной
        std::vector<Product> BI::search_down_price(Categories category, std::size_t price){
             BI interface;
             std::string conditions = " WHERE " + CategoriesToString(category) + "_urls.price <= " + std::to_string(price);
             std::vector<Product> answer = interface.get_products(category,conditions);
             return answer;
        }

        // Возвращает все записи из данной категории с определёнными параметрами
        std::vector<Product> BI::search_parametrs(Categories category, Parametrs param){
                BI interface;
                std::string conditions = " ";
                if(param.size != 0){
                        conditions = " WHERE " + CategoriesToString(category) + ".size = '" + std::to_string(param.size) + "'";
                        if(param.gender != "NULL")
                                conditions += " AND " + CategoriesToString(category) + ".gender = '" + param.gender + "'";
                        if(param.color != None)
                                conditions += " AND " + CategoriesToString(category) + ".color = '" + ColorsToString(param.color) + "'";
                        if(param.brand != "NULL")
                                conditions += " AND " + CategoriesToString(category) + ".brand = '" + param.brand + "'";
                } else if(param.gender != "NULL"){
                        conditions += " AND " + CategoriesToString(category) + ".gender = '" + param.gender + "'";
                        if(param.color != None)
                                conditions += " AND " + CategoriesToString(category) + ".color = '" + ColorsToString(param.color) + "'";
                        if(param.brand != "NULL")
                                conditions += " AND " + CategoriesToString(category) + ".brand = '" + param.brand + "'"; 
                } else if(param.color != None){
                        conditions = " WHERE " + CategoriesToString(category) + ".color = '" + ColorsToString(param.color) + "'";
                        if(param.brand != "NULL")
                                conditions += " AND " + CategoriesToString(category) + ".brand = '" + param.brand + "'"; 
                } else if(param.brand != "NULL")
                        conditions = " WHERE " + CategoriesToString(category) + ".brand = '" + param.brand + "'"; 
                std::vector<Product> answer = interface.get_products(category,conditions);
                return answer;
        }

        // В таблице пользователей создаёт запись об избранном товаре(отношение многие ко многим)
        void BI::set_user_chosen(std::string user_id, Categories category, std::size_t product_id){
                Query_BD instance;
                std::string query_user = "INSERT INTO Users (tg_id) VALUES ('" + user_id + "');";
                instance.insert_into(query_user.c_str());

                query_user = "INSERT INTO Users_chosen(user_id, id_product, category) VALUES ('" + user_id + "','" + std::to_string(product_id) + "','" + CategoriesToString(category) + "');";
                instance.insert_into(query_user.c_str());
        }

        void help_func_get_us(std::string &conditions, std::vector<std::string> &products_id, int i){
                if(i==0)
                        conditions += products_id[i+1] + ".id  = " + products_id[i];
                else
                        conditions += " OR " + products_id[i+1] + ".id  = " + products_id[i];
        }

        // Возвращает избранное пользователем
        std::vector<Product> BI::get_user_chosen(std::string user_id){
                Query_BD instance;
                std::string temp_query = "SELECT Users_chosen.id_product,Users_chosen.category FROM Users INNER JOIN Users_chosen ON Users.id = Users_chosen.user_id WHERE Users.id ='" + user_id + "';";
                std::vector<std::string> products_id = instance.select_from(temp_query.c_str());
          
                std::string conditions_sneakers = " WHERE ";
                std::string conditions_shirts = " WHERE ";
                std::string conditions_tshirts = " WHERE ";
                std::string conditions_dress = " WHERE ";
                std::string conditions_shorts = " WHERE ";
                std::string conditions_skirts = " WHERE ";
                std::string conditions_vintage_shoes = " WHERE ";
                for(int i = 0; i < products_id.size(); i+=2){
                        if(products_id[i+1] == CategoriesToString(Sneakers)){
                                help_func_get_us(conditions_sneakers, products_id, i);
                        } else if(products_id[i+1] == CategoriesToString(Shirts)){
                                help_func_get_us(conditions_shirts, products_id, i);
                        } else if(products_id[i+1] == CategoriesToString(Tshirts)){
                                help_func_get_us(conditions_tshirts, products_id, i);
                        } else if(products_id[i+1] == CategoriesToString(Dress)){
                                help_func_get_us(conditions_dress, products_id, i);
                        } else if(products_id[i+1] == CategoriesToString(Shorts)){
                                help_func_get_us(conditions_shorts, products_id, i);
                        } else if(products_id[i+1] == CategoriesToString(Skirts)){
                                help_func_get_us(conditions_skirts, products_id, i);
                        } else if(products_id[i+1] == CategoriesToString(Vintage_shoes))
                                help_func_get_us(conditions_vintage_shoes, products_id, i);
                }

                BI interface;
                std::vector<Product> result;
                std::vector<Product> result1;
                std::vector<Product> result2; 
                std::vector<Product> result3; 
                std::vector<Product> result4;
                std::vector<Product> result5; 
                std::vector<Product> result6; 
                std::vector<Product> result7; 
                if(conditions_sneakers != " WHERE "){
                        result1 = interface.get_products(Sneakers, conditions_sneakers);
                        result.insert(result.end(),std::make_move_iterator(result1.begin()),std::make_move_iterator(result1.end()));
                }
                if(conditions_shirts != " WHERE "){
                        result2 = interface.get_products(Shirts, conditions_shirts);
                        result.insert(result.end(),std::make_move_iterator(result2.begin()),std::make_move_iterator(result2.end()));
                }
                if(conditions_tshirts != " WHERE "){
                        result3 = interface.get_products(Tshirts, conditions_tshirts);
                        result.insert(result.end(),std::make_move_iterator(result3.begin()),std::make_move_iterator(result3.end()));
                }
                if(conditions_dress != " WHERE "){
                        result4 = interface.get_products(Dress, conditions_dress);
                        result.insert(result.end(),std::make_move_iterator(result4.begin()),std::make_move_iterator(result4.end()));
                }
                if(conditions_shorts != " WHERE "){
                        result5 = interface.get_products(Shorts, conditions_shorts);
                        result.insert(result.end(),std::make_move_iterator(result5.begin()),std::make_move_iterator(result5.end()));
                }
                if(conditions_skirts != " WHERE "){
                        result6 = interface.get_products(Skirts, conditions_skirts);
                        result.insert(result.end(),std::make_move_iterator(result6.begin()),std::make_move_iterator(result6.end()));
                }
                if(conditions_vintage_shoes != " WHERE "){
                        result7 = interface.get_products(Vintage_shoes, conditions_vintage_shoes);
                        result.insert(result.end(),std::make_move_iterator(result7.begin()),std::make_move_iterator(result7.end()));
                }

                return result;
        }
