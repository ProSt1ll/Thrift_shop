#include "MainMenu.h"
#include "SearchMenu.h"

#ifndef TGBOT_MENUCONTROLLER_H
#define TGBOT_MENUCONTROLLER_H
class MenuController{
public:
    SearchMenu search_menu;
    MainMenu main_menu;
    MenuController();
    ~MenuController();
    void run();
    void stop();
};
#endif TGBOT_MENUCONTROLLER_H