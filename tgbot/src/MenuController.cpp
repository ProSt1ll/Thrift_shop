#include "../include/MenuController.h"
std::vector<std::string>bot_commands ={"start"};
void MenuController::to_tg(std::string some,int id){
    bot.getApi().sendMessage(id, some);
}


void MenuController::show_vectorr(nlohmann::json items,
                                 std::function<void(std::string message, int target)> get_mes) {


    TgBot::InlineKeyboardMarkup::Ptr next_key1(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardMarkup::Ptr prev_key1(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardMarkup::Ptr all_key1(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardMarkup::Ptr back_key1(new TgBot::InlineKeyboardMarkup);

    nlohmann::json package2;

    std::string id = items["user_id"];
    std::vector<TgBot::InlineKeyboardButton::Ptr> next_buts;
    TgBot::InlineKeyboardButton::Ptr next_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr prev_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr tof_btn(new TgBot::InlineKeyboardButton);

    next_btn->text = ">>";
    next_btn->callbackData = "tnextt";

    prev_btn->text = "<<";
    prev_btn->callbackData = "tprevt";

    tof_btn->text = "back";
    tof_btn->callbackData = "back";


    next_buts.push_back(prev_btn);
    next_buts.push_back(next_btn);
    next_buts.push_back(tof_btn);

    all_key1->inlineKeyboard.push_back(next_buts);

    next_buts.clear();
    next_buts.push_back(next_btn);
    next_buts.push_back(tof_btn);

    next_key1->inlineKeyboard.push_back(next_buts);

    next_buts.clear();
    next_buts.push_back(prev_btn);
    next_buts.push_back(tof_btn);
    prev_key1->inlineKeyboard.push_back(next_buts);

    next_buts.clear();
    next_buts.push_back(tof_btn);
    back_key1->inlineKeyboard.push_back(next_buts);

    int ink1;
    int i = 0;
    ink1 = 0;
    to_tg(items["product"][i]["url_image"], std::stoi(id));
    to_tg(items["product"][i]["url_product"], std::stoi(id));
    //to_tg("цена: " + items["product"][i]["price"].dump(), 517318106);
    if (items["numb_item"]==1) {

        bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][i]["price"].dump(), false, 0, back_key1);
    }
    if (items["numb_item"]>1) {

        bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][i]["price"].dump(), false, 0, next_key1);
    }


    //int tmp = -30;
    bot.getEvents().onCallbackQuery([this, items, id, get_mes,&next_key1,&prev_key1,&all_key1,&package2,&ink1](TgBot::CallbackQuery::Ptr query) {
        if (query->data == "tnextt") {
            ink1++;

            to_tg(items["product"][ink1]["url_image"], std::stoi(id));
            to_tg(items["product"][ink1]["url_product"], std::stoi(id));
            //to_tg("цена: " + items["product"][ink1]["price"].dump(), 517318106);
            if (ink1 == 0) {
                bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink1]["price"].dump(), false, 0,
                                         next_key1);
            } else if (ink1 + 1 == items["numb_item"]) {

                bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink1]["price"].dump(), false, 0,
                                         prev_key1);
            } else {
                bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink1]["price"].dump(), false, 0,
                                         all_key1);

            }


        } else if (query->data == "tprevt") {
            ink1--;

            to_tg(items["product"][ink1]["url_image"], std::stoi(id));
            to_tg(items["product"][ink1]["url_product"], std::stoi(id));
            //to_tg("цена: " + items["product"][ink1]["price"].dump(), 517318106);
            std::cout<<items["numb_item"]<<" "<<std::to_string(ink1 + 1)<<std::endl;
            if (ink1 == 0) {
                bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink1]["price"].dump(), false, 0,
                                         next_key1);
            } else if (ink1 + 1 == items["numb_item"]) {

                bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink1]["price"].dump(), false, 0,
                                         prev_key1);
            } else {
                bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink1]["price"].dump(), false, 0,
                                         all_key1);

            }

        } else if (query->data == "toft") {

            package2["user_id"] = id;

            package2["product"] = items["product"][ink1];
            package2["product"]["category"] = "Dress";
            package2["option"] = 1;
            get_mes(package2.dump(), 2);
        }

    });



};
    void MenuController::show_vector(nlohmann::json items,
                                      std::function<void(std::string message, int target)> get_mes) {
        TgBot::InlineKeyboardMarkup::Ptr next_key(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardMarkup::Ptr prev_key(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardMarkup::Ptr all_key(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardMarkup::Ptr fav_key(new TgBot::InlineKeyboardMarkup);
        nlohmann::json package2;

        std::string id = items["user_id"];
        std::vector<TgBot::InlineKeyboardButton::Ptr> next_buts;
        TgBot::InlineKeyboardButton::Ptr next_btn(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr prev_btn(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr tof_btn(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr toffd_btn(new TgBot::InlineKeyboardButton);

        next_btn->text = ">>";
        next_btn->callbackData = "next";

        prev_btn->text = "<<";
        prev_btn->callbackData = "prev";

        tof_btn->text = "add";
        tof_btn->callbackData = "tof";

        toffd_btn->text = "favorite";
        toffd_btn->callbackData = "fav";


        next_buts.push_back(prev_btn);
        next_buts.push_back(next_btn);
        next_buts.push_back(tof_btn);
        next_buts.push_back(toffd_btn);

        all_key->inlineKeyboard.push_back(next_buts);

        next_buts.clear();
        next_buts.push_back(next_btn);
        next_buts.push_back(tof_btn);
        next_buts.push_back(toffd_btn);

        next_key->inlineKeyboard.push_back(next_buts);

        next_buts.clear();
        next_buts.push_back(prev_btn);
        next_buts.push_back(tof_btn);
        next_buts.push_back(toffd_btn);

        prev_key->inlineKeyboard.push_back(next_buts);

        next_buts.clear();
        next_buts.push_back(tof_btn);
        next_buts.push_back(toffd_btn);

        fav_key->inlineKeyboard.push_back(next_buts);
        int ink;
        int i = 0;
        ink = 0;
        to_tg(items["product"][i]["url_image"], std::stoi(id));
        to_tg(items["product"][i]["url_product"], std::stoi(id));
        if (items["numb_item"]==1) {

            bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][i]["price"].dump(), false, 0, fav_key);
        }
        if (items["numb_item"]>1) {

            bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][i]["price"].dump(), false, 0, next_key);
        }


        bot.getEvents().onCallbackQuery([this, items, id, get_mes,&next_key,&prev_key,&all_key,&ink,&package2](TgBot::CallbackQuery::Ptr query) {
            if (query->data == "next") {
                ink++;

                to_tg(items["product"][ink]["url_image"], std::stoi(id));
                to_tg(items["product"][ink]["url_product"], std::stoi(id));
                //to_tg("цена: " + items["product"][ink]["price"].dump(), 517318106);
                if (ink == 0) {
                    bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink]["price"].dump(), false, 0,
                                             next_key);
                } else if (ink + 1 == items["numb_item"]) {

                    bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink]["price"].dump(), false, 0,
                                             prev_key);
                } else {
                    bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink]["price"].dump(), false, 0,
                                             all_key);

                }


            } else if (query->data == "prev") {
                ink--;

                to_tg(items["product"][ink]["url_image"], std::stoi(id));
                to_tg(items["product"][ink]["url_product"], std::stoi(id));
                //to_tg("цена: " + items["product"][ink]["price"].dump(), 517318106);
                if (ink == 0) {
                    bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink]["price"].dump(), false, 0,
                                             next_key);
                } else if (ink + 1 == items["numb_item"]) {

                    bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink]["price"].dump(), false, 0,
                                             prev_key);
                } else {
                    bot.getApi().sendMessage(std::stoi(id), "Price: " + items["product"][ink]["price"].dump(), false, 0,
                                             all_key);

                }


            } else if (query->data == "tof") {

                package2["user_id"] = id;
                package2["product"] = items["product"][ink];
                package2["product"]["category"] = "Dress";
                package2["option"] = 1;
                get_mes(package2.dump(), 2);
                this->to_tg("Favorite item added",std::stoi(id));
            }

        });

    };


void MenuController::run(std::function<void (std::string message,int target)> get_mes){



    bot.getEvents().onCommand("start", [&get_mes, this](TgBot::Message::Ptr message) {
        MainMenu Main(&bot,message->chat->id,[&](std::string message,int target){get_mes(message,target); });
        Main.run([&](std::string message,int target){get_mes(message,target); });
    });


    bot.getEvents().onAnyMessage([](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        for (const auto& command : bot_commands){
            if ("/"+command == message->text){
                return;
            }
        }
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            //start();
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }

}

void MenuController::stop(){}

