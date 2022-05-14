

#ifndef TGBOT_SEARCHMENU_H
#define TGBOT_SEARCHMENU_H
#include "Menu.h"
#include "Client.h"
class SearchMenu{
public:
    Menu menu;
    SearchMenu( TgBot::Bot *bot,int id,Client* client);
    ~SearchMenu();
};
#endif //TGBOT_SEARCHMENU_H
