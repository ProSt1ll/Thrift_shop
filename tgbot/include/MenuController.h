#include "MainMenu.h"
#include "SearchMenu.h"

#include<string>
#include<vector>
#include <stdio.h>

#ifndef TGBOT_MENUCONTROLLER_H
#define TGBOT_MENUCONTROLLER_H
#include "MainMenu.h"
#include "SearchMenu.h"
#include <boost/bind/bind.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
class MenuController{
public:
    MenuController(std::string token):bot(token){};
    ~MenuController()= default;
    void run(std::function<void(std::string message,int target)> get_mes);
    void stop();
    int t_id;
    void show_vector(nlohmann::json items,std::function<void(std::string message,int target)> get_mes);
    void show_vectorr(nlohmann::json items,std::function<void(std::string message,int target)> get_mes);
    void to_tg(std::string some,int id);
    TgBot::Bot bot;
};
#endif //TGBOT_MENUCONTROLLER_H