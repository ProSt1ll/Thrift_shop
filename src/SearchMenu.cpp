#include "../include/SearchMenu.h"

SearchMenu::SearchMenu(TgBot::Bot *bot,int id,std::function<void(std::string message)> get_mes,std::function<void(void)> back) {
    t_id = id;
    t_bot = bot;

    TgBot::InlineKeyboardMarkup::Ptr tmp_keyboard = menu.keyboard;
    bot->getEvents().onCallbackQuery([&bot , back](TgBot::CallbackQuery::Ptr query){
        if(query->data == "back"){
           back();
        }
    });
}
void SearchMenu::run(){
    TgBot::InlineKeyboardButton::Ptr category1_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category2_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category3_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category4_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr back_btn(new TgBot::InlineKeyboardButton);

    category1_btn->text = "Empty";
    category1_btn->callbackData = "Empty";

    category2_btn->text = "Sneakers";
    category2_btn->callbackData = "Sneakers";

    category3_btn->text = "Shirts";
    category3_btn->callbackData = "Shirts";

    category4_btn->text = "Tshirts";
    category4_btn->callbackData = "Tshirts";

    back_btn->text="Back to main menu";
    back_btn->callbackData = "back";

    menu.buttons.push_back(category1_btn);
    menu.buttons.push_back(category2_btn);
    menu.buttons.push_back(category3_btn);
    menu.buttons.push_back(category4_btn);
    menu.buttons.push_back(back_btn);

    menu.keyboard->inlineKeyboard.push_back(menu.buttons);

    std::string label = "Choose category";
    menu.display(t_id,label,t_bot);
}
SearchMenu::~SearchMenu() {

}
