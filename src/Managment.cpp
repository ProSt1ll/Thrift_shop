#include "../include/Managment.h"

void Managment::parse_res(nlohmann::json request,int type) {
    switch(type){
        case 1:
            display(request["item"]["url"],request["user"]["id"]);
            break;
        case 2:

            break;

        case 3:

            break;
    }
}
void Managment::get_res(nlohmann::json request){
    parse_res(request["package"],request["type"]);
}
void Managment::display(std::string url,int id){
    bot_mnm->getApi().sendMessage(id, url);
}

Managment::Managment(TgBot::Bot *bot) {
    bot_mnm = bot;
};
Managment::~Managment() {

}

void Managment::get_product(int search_parametr) {

};