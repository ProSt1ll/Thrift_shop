#include "Managment.h"
#include <stdio.h>
#include <tgbot/tgbot.h>
#ifndef TGBOT_MENU_H
#define TGBOT_MENU_H
class Menu{
public:
    TgBot::Bot bot;
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    TgBot::InlineKeyboardMarkup::Ptr keyboard;
    Menu();
    ~Menu();
};
#endif TGBOT_MENU_H