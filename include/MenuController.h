#include "MainMenu.h"
#include "SearchMenu.h"
#include "Client.h"

#include<string>
#include<vector>
#include <stdio.h>

#ifndef TGBOT_MENUCONTROLLER_H
#define TGBOT_MENUCONTROLLER_H

class MenuController{
public:
    MenuController()= default;;
    ~MenuController()= default;
    void run();
    void stop();
};
#endif //TGBOT_MENUCONTROLLER_H