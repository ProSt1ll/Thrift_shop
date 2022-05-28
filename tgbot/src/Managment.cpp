#include "../include/Managment.h"

//void Managment::parse_res(std::string request,int type) {
//    switch(type){
//        case 1:
//            display(request["item"]["url"],request["user"]["id"]);
//            break;
//        case 2:
//
//            break;
//
//        case 3:
//
//            break;
//    }
//}

//void Managment::get_res(nlohmann::json request){
//    parse_res(request["package"],request["type"]);
//}
void Managment::display(std::string url,int id){
    bot_mnm->getApi().sendMessage(id, url);
}


Managment::~Managment() {

}
void Managment::get_mes(std::string message) {
    ClientCntrl client(message,[&](std::string message){get_mes_from_serv(message); });
};
void Managment::get_mes_from_serv(std::string message) {
    if(message[0]=='{') {

        if (message[10] == '3') {
            nlohmann::json res = nlohmann::json::parse(message);
            tgbot.to_tg(res["product"]["url_image"], 517318106);
            tgbot.to_tg(res["product"]["url_product"], 517318106);
            tgbot.to_tg("цена: " +res["product"]["price"].dump(), 517318106);

        }
    }
   // tgbot.to_tg(message, 517318106);
};
void Managment::get_product(int search_parametr) {

}
void Managment::run_serv(){
    io_context.run();

}
void Managment::run() {
//        Client client;
//        client.run();
//    auto client= std::make_shared<Client>(io_context);
//    clin = client;
//    Client client();
//    std::make_shared<Client>(io_context)->run();
    //client->run();
    //run_serv();
//    get_mes("ww");
//    run_serv();
//    boost::asio::ip::tcp::endpoint ep( boost::asio::ip::address::from_string("127.0.0.1"), 5000);
//    boost::asio::io_context service;
    //boost::asio::io_context io_context;
//    talk_to_svr client(service);
//    client.connect(ep);
//    client.write("parts/");

tgbot.run([&](std::string message){get_mes(message); },[&](){run_serv(); });

}
