
#ifndef TGBOT_MENU_H
#define TGBOT_MENU_H
#include <tgbot/tgbot.h>
#include <stdio.h>
#include "json.hpp"

class Menu{
public:
    std::vector<TgBot::InlineKeyboardButton::Ptr> buttons;
    TgBot::InlineKeyboardMarkup::Ptr keyboard;
    Menu();
    ~Menu();
};
#endif //TGBOT_MENU_H
