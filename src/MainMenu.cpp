#include "../include/MainMenu.h"

MainMenu::MainMenu(TgBot::Bot *bot,int id,Client* client) {
    TgBot::InlineKeyboardButton::Ptr search_btn(new TgBot::InlineKeyboardButton);
    search_btn->text = "Search menu";
    search_btn->callbackData = "search";
    menu.buttons.push_back(search_btn);
    menu.keyboard->inlineKeyboard.push_back(menu.buttons);
    std::string label = "Choose menu";
    menu.display(id,label,bot);
    TgBot::InlineKeyboardMarkup::Ptr tmp_keyboard = menu.keyboard;
    bot->getEvents().onCallbackQuery([ &tmp_keyboard, &id, &client, &bot](TgBot::CallbackQuery::Ptr query){
        if(query->data == "search"){
            SearchMenu search(bot,id,client);
        }
    });

}

MainMenu::~MainMenu() {

}
