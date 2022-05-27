#include "../include/MainMenu.h"

MainMenu::MainMenu(TgBot::Bot *bot,int id,std::function<void(std::string message)> get_mes,std::function<void(void)> back) {
    TgBot::InlineKeyboardButton::Ptr search_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr favorite_btn(new TgBot::InlineKeyboardButton);
    search_btn->text = "Search menu";
    search_btn->callbackData = "search";
    favorite_btn->text = "Favorite";
    favorite_btn->callbackData = "fav";
    menu.buttons.push_back(search_btn);
    menu.buttons.push_back(favorite_btn);
    menu.keyboard->inlineKeyboard.push_back(menu.buttons);
    //menu.display(id,label,bot);

    t_id = id;
    t_bot = bot;
    get_mes("lol");
    TgBot::InlineKeyboardMarkup::Ptr tmp_keyboard = menu.keyboard;
    bot->getEvents().onCallbackQuery([get_mes,back, &tmp_keyboard, id, bot,this](TgBot::CallbackQuery::Ptr query){
        if(query->data == "search"){
            SearchMenu search(bot,id,[&](std::string message){get_mes(message); },[&](){back(); });
            search.run();
        }

    });

}
void MainMenu::run(){
    std::string label = "Choose menu";
    menu.display(t_id,label,t_bot);
}

void MainMenu::rerun(){
this->run();
}

MainMenu::~MainMenu() {

}
