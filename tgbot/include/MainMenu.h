#include "SearchMenu.h"

#ifndef TGBOT_MAINMENU_H
#define TGBOT_MAINMENU_H
class MainMenu{
public:


    MainMenu(TgBot::Bot *bot,int id,std::function<void(std::string message,int main)> get_mes);
    void run(std::function<void(std::string message,int main)> get_mes);

    ~MainMenu();
private:
    Menu menu;
    TgBot::InlineKeyboardMarkup::Ptr search_key;
    TgBot::Bot *t_bot;
    std::function<void(std::string message)> func;
    int t_id;
};
#endif //TGBOT_MAINMENU_H
