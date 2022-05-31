#include "../headers/query_bd.h"

using namespace bd;

//устанавливает соединение с БД 
Query_BD::Query_BD(){
    this->conn = mysql_init(NULL);

      /* Connect to database */
      if (!mysql_real_connect(this->conn, server,
            user, password, database, port, NULL, 0)) {
          fprintf(stderr, "%s\n", mysql_error(this->conn));
          exit(1);
      }
}

//разрывает соединение с БД
Query_BD::~Query_BD(){
    mysql_close(this->conn);
}

void Query_BD::create_all_tables(){
    mysql_query(this->conn, "CREATE TABLE Sneakers (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Sneakers_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Sneakers (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Shirts (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Shirts_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Shirts (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Tshirts (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Tshirts_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Tshirts (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Dress (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Dress_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Dress (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Shorts (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Shorts_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Shorts (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Skirts (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Skirts_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Skirts (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Vintage_shoes (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(500) UNIQUE NOT NULL, url_image VARCHAR(500), size INT, gender VARCHAR(30), color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Vintage_shoes_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price INT, url_product VARCHAR(500) UNIQUE, FOREIGN KEY (product_id) REFERENCES Vintage_shoes (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Users (id INT PRIMARY KEY AUTO_INCREMENT, tg_id VARCHAR(255) UNIQUE NOT NULL);");
    mysql_query(this->conn, "CREATE TABLE Users_chosen (id INT PRIMARY KEY AUTO_INCREMENT, user_id tg_id VARCHAR(255) NOT NULL, id_product INT NOT NULL, category VARCHAR(255) NOT NULL, FOREIGN KEY (user_id) REFERENCES Users (tg_id) ON DELETE CASCADE, CONSTRAINT chosen_unique UNIQUE (user_id, id_product, category));");
}

void Query_BD::delete_all_tables(){
    mysql_query(this->conn, "DROP TABLE Sneakers_urls");
    mysql_query(this->conn, "DROP TABLE Shirts_urls");
    mysql_query(this->conn, "DROP TABLE Tshirts_urls");
    mysql_query(this->conn, "DROP TABLE Dress_urls");
    mysql_query(this->conn, "DROP TABLE Shorts_urls");
    mysql_query(this->conn, "DROP TABLE Skirts_urls");
    mysql_query(this->conn, "DROP TABLE Vintage_shoes_urls");
    mysql_query(this->conn, "DROP TABLE Sneakers");
    mysql_query(this->conn, "DROP TABLE Shirts");
    mysql_query(this->conn, "DROP TABLE Tshirts");
    mysql_query(this->conn, "DROP TABLE Dress");
    mysql_query(this->conn, "DROP TABLE Shorts");
    mysql_query(this->conn, "DROP TABLE Skirts");
    mysql_query(this->conn, "DROP TABLE Vintage_shoes");
    mysql_query(this->conn, "DROP TABLE Users_chosen");
    mysql_query(this->conn, "DROP TABLE Users");
}

const char* Query_BD::insert_into(const char* query){
    if (mysql_query(this->conn, query)) {
          return mysql_error(conn);
    }
    return NULL;
}

std::vector<std::string> Query_BD::select_from(const char* query){
    if (mysql_query(this->conn, query)) {
          fprintf(stderr, "%s\n", mysql_error(this->conn));
          exit(1);
      }

    MYSQL_RES *res;
    MYSQL_ROW row;

    res = mysql_use_result(this->conn);
    std::vector<std::string> answer; 

    int columns = mysql_num_fields(res);
    

    while ((row = mysql_fetch_row(res)) != NULL){
        for(int i = 0; i < columns; i++){
            if(row[i] == NULL)
                answer.push_back("NULL");
            else answer.push_back(row[i]);
        }
    }

    mysql_free_result(res);
    return answer;
}
