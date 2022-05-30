#ifndef TGBOT_SEARCHMENU_H
#define TGBOT_SEARCHMENU_H
#include "Menu.h"

class SearchMenu: public Menu{
public:
    Menu menu;
    SearchMenu( TgBot::Bot *bot,int id,std::function<void(std::string,int target)> get_mes);
    ~SearchMenu();
    void run();
    int t_id;
    TgBot::Bot *t_bot;
    std::vector<TgBot::InlineKeyboardButton::Ptr> color_but;
    std::vector<TgBot::InlineKeyboardButton::Ptr> size_but;

};
#endif //TGBOT_SEARCHMENU_H
