

#ifndef TGBOT_SEARCHMENU_H
#define TGBOT_SEARCHMENU_H
#include "Menu.h"
class SearchMenu: public Menu{
public:
    Menu menu;
    SearchMenu( TgBot::Bot *bot,int id,std::function<void(std::string message)> get_mes,std::function<void(void)> back);
    ~SearchMenu();
    void run();
    int t_id;
    TgBot::Bot *t_bot;

};
#endif //TGBOT_SEARCHMENU_H
