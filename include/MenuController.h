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
    void run(std::function<void(std::string message)> get_mes,std::function<void(void)> start);
    void stop();
    void(*get_msg)(std::string);
    int t_id;
    void to_tg(std::string some,int id);
    void key_favor(int id, int id_product);
    TgBot::Bot bot;
};
#endif //TGBOT_MENUCONTROLLER_H