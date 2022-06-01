//#include "sync.h"
#ifndef TGBOT_MANAGMENT_H
#define TGBOT_MANAGMENT_H
#include <vector>
#include <string.h>
#include "json.hpp"
#include <boost/beast/http.hpp>
#include <tgbot/tgbot.h>
#include "ClientCntrl.h"
#include "MenuController.h"

const std::string port = "5000";
const std::string server = "127.0.0.1";



class Managment {
public:
    Managment(std::string api):tgbot(api){

    };

    ~Managment();

    void run();
private:



    void get_mes(std::string message,int target);
    void get_mes_from_serv(std::string message);
    TgBot::Bot *bot_mnm;
    std::shared_ptr<Client> clin;
    boost::asio::io_context io_context;
    MenuController tgbot;
};

#endif //TGBOT_MANAGMENT_H
