#include "../include/SearchMenu.h"

SearchMenu::SearchMenu(TgBot::Bot *bot,int id,Client* client) {

    TgBot::InlineKeyboardButton::Ptr first_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr sec_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr third_btn(new TgBot::InlineKeyboardButton);

    first_btn->text = "1";
    first_btn->callbackData = "1";

    sec_btn->text = "2";
    sec_btn->callbackData = "2";


    third_btn->text = "3";
    third_btn->callbackData = "3";
    menu.buttons.push_back(first_btn);
    menu.buttons.push_back(sec_btn);
    menu.buttons.push_back(third_btn);
    menu.keyboard->inlineKeyboard.push_back(menu.buttons);
    std::string label = "Choose parametr";
    menu.display(id,label,bot);
    TgBot::InlineKeyboardMarkup::Ptr tmp_keyboard = menu.keyboard;
    bot->getEvents().onCallbackQuery([&bot , &tmp_keyboard, &client](TgBot::CallbackQuery::Ptr query){
        if(query->data == "1"){
            client->sec_mgm->get_product(1);
        }
    });
}

SearchMenu::~SearchMenu() {

}
