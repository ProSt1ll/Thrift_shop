#include "../include/Menu.h"

Menu::~Menu() {

}

Menu::Menu() {
    keyboard = TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);

}

