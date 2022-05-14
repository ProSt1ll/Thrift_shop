#include "../include/Menu.h"

Menu::~Menu() {

}

Menu::Menu() {
    keyboard = TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);

}

void Menu::display(int id, std::string text,TgBot::Bot* bot) {
    bot->getApi().sendMessage(id,text,false,0,keyboard);
}
