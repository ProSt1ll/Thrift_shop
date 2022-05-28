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
    mysql_query(this->conn, "CREATE TABLE Sneakers (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255) UNIQUE NOT NULL, url_image VARCHAR(255), size INT, color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Sneakers_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price FLOAT, url_product VARCHAR(255) UNIQUE, FOREIGN KEY (product_id) REFERENCES Sneakers (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Shirts (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255) UNIQUE NOT NULL, url_image VARCHAR(255), size INT, color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Shirts_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price FLOAT, url_product VARCHAR(255) UNIQUE, FOREIGN KEY (product_id) REFERENCES Shirts (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Tshirts (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255) UNIQUE NOT NULL, url_image VARCHAR(255), size INT, color VARCHAR(30), brand VARCHAR(30));");
    mysql_query(this->conn, "CREATE TABLE Tshirts_urls (id INT PRIMARY KEY AUTO_INCREMENT, product_id int NOT NULL, price FLOAT, url_product VARCHAR(255) UNIQUE, FOREIGN KEY (product_id) REFERENCES Tshirts (id) ON DELETE CASCADE );");
    mysql_query(this->conn, "CREATE TABLE Users (id INT PRIMARY KEY AUTO_INCREMENT, tg_id VARCHAR(255) UNIQUE NOT NULL);");
    mysql_query(this->conn, "CREATE TABLE Users_chosen (id INT PRIMARY KEY AUTO_INCREMENT, user_id int NOT NULL, id_product INT NOT NULL, category VARCHAR(255) NOT NULL, FOREIGN KEY (user_id) REFERENCES Users (id) ON DELETE CASCADE, CONSTRAINT chosen_unique UNIQUE (user_id, id_product, category));");
}

void Query_BD::delete_all_tables(){
    mysql_query(this->conn, "DROP TABLE Sneakers_urls");
    mysql_query(this->conn, "DROP TABLE Shirts_urls");
    mysql_query(this->conn, "DROP TABLE Tshirts_urls");
    mysql_query(this->conn, "DROP TABLE Users_chosen");
    mysql_query(this->conn, "DROP TABLE Shirts");
    mysql_query(this->conn, "DROP TABLE Sneakers");
    mysql_query(this->conn, "DROP TABLE Tshirts");
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
