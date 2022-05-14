#include "SearchMenu.h"

#ifndef TGBOT_MAINMENU_H
#define TGBOT_MAINMENU_H
class MainMenu{
public:
    Menu menu;
    MainMenu(TgBot::Bot *bot,int id,Client* client);
    ~MainMenu();

};
#endif //TGBOT_MAINMENU_H
