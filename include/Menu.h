
#ifndef TGBOT_MENU_H
#define TGBOT_MENU_H
#include <tgbot/tgbot.h>
#include "Managment.h"
#include <stdio.h>
#include "Client.h"


class Menu{
public:
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    TgBot::InlineKeyboardMarkup::Ptr keyboard;
    Menu();
    ~Menu();

    void display(int id, std::string text,TgBot::Bot* bot);
};
#endif //TGBOT_MENU_H
