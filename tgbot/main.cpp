#include <iostream>
#include "include/Managment.h"
int main() {
    std::string api;
    std::cout<<"enter tg api"<<std::endl;
    std::cin>>api;
    Managment tgbot(api);
    tgbot.run();
    return 0;
}