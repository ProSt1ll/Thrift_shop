#include "../include/Managment.h"


Managment::~Managment() {

}
void Managment::get_mes(std::string message,int target) {
    std::string targett;
    if (target ==1){
    targett="/get_item";
    }else{
        targett="/to_favorite";
    }
    ClientCntrl client(message,[&](std::string message){get_mes_from_serv(message); },targett);
};
void Managment::get_mes_from_serv(std::string message) {
    if(message[0]=='{') {
        nlohmann::json res = nlohmann::json::parse(message);
        if(res["numb_item"]<1){
            std::string id = res["user_id"];
            tgbot.to_tg("Nothing found",std::stoi(id));

        }
        if(res["numb_item"]>0) {
            if (res["option"] == 2) {
                tgbot.show_vector(res, [&](std::string message,int target){get_mes(message,target); });

            } else if (res["option"] == 4) {
                //tgbot.show_vector(res,1);
                    tgbot.show_vector(res, [&](std::string message,int target){get_mes(message,target); });

            } else if (res["option"] == 3) {
                tgbot.show_vector(res, [&](std::string message,int target){get_mes(message,target); });
//
            }else if(res["option"] == 1){
                tgbot.show_vectorr(res, [&](std::string message,int target){get_mes(message,target); });
            }
        }
    }

    // tgbot.to_tg(message, 517318106);
};

void Managment::run_serv(){
    io_context.run();

}
void Managment::run() {

tgbot.run([&](std::string message,int target){get_mes(message,target); });

}
