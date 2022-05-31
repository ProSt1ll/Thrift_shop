#include "../include/MainMenu.h"
MainMenu::MainMenu(TgBot::Bot *bot,int id,std::function<void(std::string message,int target)> get_mes):t_id(id),t_bot(bot) {
    menu.buttons.clear();
    menu.keyboard->inlineKeyboard.clear();
    search_key = TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);


    std::vector<TgBot::InlineKeyboardButton::Ptr> search_buts;
    TgBot::InlineKeyboardButton::Ptr search1_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr favorite_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr search2_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr search3_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr search_btn(new TgBot::InlineKeyboardButton);

    search_btn->text = "Search menu";
    search_btn->callbackData = "searcht";

    favorite_btn->text = "Favorite";
    favorite_btn->callbackData = "fav";

    search1_btn->text = "Parametrs";
    search1_btn->callbackData = "search1";

    search2_btn->text = "Category and price";
    search2_btn->callbackData = "search2";

    search3_btn->text = "Category";
    search3_btn->callbackData = "search3";


    menu.buttons.push_back(search_btn);
    menu.buttons.push_back(favorite_btn);
    menu.keyboard->inlineKeyboard.push_back(menu.buttons);

    search_buts.push_back(search1_btn);
    search_buts.push_back(search2_btn);
    search_buts.push_back(search3_btn);
    search_key->inlineKeyboard.push_back(search_buts);


    //menu.display(id,label,bot);
    //t_id = id;
    t_bot = bot;

    //TgBot::InlineKeyboardMarkup::Ptr tmp_keyboard = menu.keyboard;


}
void MainMenu::run(std::function<void(std::string message,int target)> get_mes){
    std::string label = "Choose menu";
    t_bot->getApi().sendMessage(t_id,label,false,0,menu.keyboard);
  //  menu.display(t_id,label,t_bot);

    t_bot->getEvents().onCallbackQuery([get_mes,*this](TgBot::CallbackQuery::Ptr query){
        if(query->data == "search1"){
            SearchMenu search(t_bot,query->message->chat->id,[&](std::string message,int target){get_mes(message,target); },2);
        }
        if (query->data == "searcht"){

            t_bot->getApi().sendMessage(query->message->chat->id, "Choose search type", false, 0, this->search_key);
        }
        if(query->data == "search2"){
            SearchMenu search1(t_bot,query->message->chat->id,[&](std::string message,int target){get_mes(message,target); },3);

        }
        if(query->data == "search3"){
            SearchMenu search2(t_bot,query->message->chat->id,[&](std::string message,int target){get_mes(message,target); },4);

        }
        if(query->data == "fav") {
            nlohmann::json package2;
            package2["option"]=1;
            package2["user_id"]=std::to_string(query->message->chat->id);
            get_mes(package2.dump(),1);
}

    });
}

MainMenu::~MainMenu() {

}
