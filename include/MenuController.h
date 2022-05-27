#include "MainMenu.h"
#include "SearchMenu.h"

#include<string>
#include<vector>
#include <stdio.h>

#ifndef TGBOT_MENUCONTROLLER_H
#define TGBOT_MENUCONTROLLER_H
#include "MainMenu.h"
#include "SearchMenu.h"
class MenuController{
public:
    MenuController(std::string token):bot(token){};
    ~MenuController()= default;
    void run(std::function<void(std::string message)> get_mes);
    void stop();
    void(*get_msg)(std::string);

    TgBot::Bot bot;
};
#endif //TGBOT_MENUCONTROLLER_H