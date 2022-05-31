#include "../include/SearchMenu.h"
std::vector<std::string> Category = {"Empty", "Sneakers", "Shirts", "Tshirts","Dress","Skirts","Vintage_shoes"};
std::vector<std::string> Color = {"None",
                                  "White",
                                  "Blue",
                                  "Red",
                                  "Orange",
                                  "Yellow",
                                  "Green",
                                  "Black"};
std::vector<int> Size = {         40,
                                 44,
                                 46,
                                 48
};


SearchMenu::SearchMenu(TgBot::Bot *bot, int id, std::function<void(std::string message,int target)> get_mes,int type_search):t_id(id),t_bot(bot),type(type_search) {
    color_key = TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);
    category_key = TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);
    size_key = TgBot::InlineKeyboardMarkup::Ptr(new TgBot::InlineKeyboardMarkup);

    menu.buttons.clear();
    menu.keyboard->inlineKeyboard.clear();

    TgBot::InlineKeyboardButton::Ptr color1_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color2_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color3_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color4_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color5_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color6_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color7_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr color8_btn(new TgBot::InlineKeyboardButton);

    TgBot::InlineKeyboardButton::Ptr size1_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr size2_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr size3_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr size4_btn(new TgBot::InlineKeyboardButton);
    int i = 0;
    color1_btn->text = Color[i];
    color1_btn->callbackData = Color[i];
    i++;
    color2_btn->text = Color[i];
    color2_btn->callbackData = Color[i];
    i++;
    color3_btn->text = Color[i];
    color3_btn->callbackData = Color[i];
    i++;
    color4_btn->text = Color[i];
    color4_btn->callbackData = Color[i];
    i++;
    color5_btn->text = Color[i];
    color5_btn->callbackData = Color[i];
    i++;
    color6_btn->text = Color[i];
    color6_btn->callbackData = Color[i];
    i++;
    color7_btn->text = Color[i];
    color7_btn->callbackData = Color[i];
    i++;
    color8_btn->text = Color[i];
    color8_btn->callbackData = Color[i];
    color_but.push_back(color1_btn);
    color_but.push_back(color2_btn);
    color_but.push_back(color3_btn);
    color_but.push_back(color4_btn);
    color_but.push_back(color5_btn);
    color_but.push_back(color6_btn);
    color_but.push_back(color7_btn);
    color_but.push_back(color8_btn);
    color_key->inlineKeyboard.push_back(color_but);

    i = 0;
    size1_btn->text = std::to_string(Size[i]);
    size1_btn->callbackData = std::to_string(Size[i]);

    i++;
    size2_btn->text = std::to_string(Size[i]);
    size2_btn->callbackData = std::to_string(Size[i]);
    i++;
    size3_btn->text = std::to_string(Size[i]);
    size3_btn->callbackData = std::to_string(Size[i]);
    i++;
    size4_btn->text = std::to_string(Size[i]);
    size4_btn->callbackData = std::to_string(Size[i]);
    i++;

    size_but.push_back(size1_btn);
    size_but.push_back(size2_btn);
    size_but.push_back(size3_btn);
    size_but.push_back(size4_btn);

    size_key->inlineKeyboard.push_back(size_but);
    nlohmann::json package2;

    t_bot = bot;
    package["user_id"]=std::to_string(id);
    bot->getEvents().onCallbackQuery([bot, id, this,&package2,get_mes,type_search](TgBot::CallbackQuery::Ptr query) {
            for (const auto bot_color: Color) {
                if (query->data == bot_color) {
                    this->package["product"]["parameters"]["color"]=query->data;
                    bot->getApi().sendMessage(query->message->chat->id,"Choose size",false,0,size_key);
                }
            }
        for (const auto bot_size: Size) {
            std::string tmp = std::to_string(bot_size);
            if (query->data == tmp) {
                package["user_id"]=std::to_string(query->message->chat->id);
                package["product"]["parameters"]["size"]=bot_size;
                package["option"]=2;
                tmp = package.dump();
                get_mes(tmp,1);
            }
        }
        for (const auto bot_category: Category) {
            if (query->data == bot_category) {
                package2["user_id"]=std::to_string(query->message->chat->id);
                package["product"]["category"]=bot_category;
                if(type_search==2) {
                    bot->getApi().sendMessage(query->message->chat->id, "Choose color", false, 0, color_key);
                }
                else if (type_search == 3){
                    bot->getApi().sendMessage(query->message->chat->id, "Set Price" );
                }
                else if (type_search == 4){
                    package["user_id"]=std::to_string(query->message->chat->id);

                    package["option"]=4;
                    package["user_id"]=std::to_string(query->message->chat->id);
                    get_mes(package.dump(),1);
                }
                }
        }

    });

    bot->getEvents().onAnyMessage([this,get_mes,type_search](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        std::vector<std::string>bot_commands ={"start"};
        for (const auto& command : bot_commands) {
            if ("/" + command == message->text) {
                return;
            }
            if (type_search == 3) {
                package["user_id"]=std::to_string(message->chat->id);
                package["option"]=3;
                package["product"]["price"]=std::stoi(message->text.c_str());
                get_mes(this->package.dump(),1);
            }
        }
    });
    this->run();
}

void SearchMenu::run() {
    TgBot::InlineKeyboardButton::Ptr category1_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category2_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category3_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category4_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category5_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category6_btn(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr category7_btn(new TgBot::InlineKeyboardButton);


    TgBot::InlineKeyboardButton::Ptr back_btn(new TgBot::InlineKeyboardButton);


    category1_btn->text = "Empty";
    category1_btn->callbackData = "Empty";

    category2_btn->text = "Sneakers";
    category2_btn->callbackData = "Sneakers";

    category3_btn->text = "Shirts";
    category3_btn->callbackData = "Shirts";

    category4_btn->text = "Tshirts";
    category4_btn->callbackData = "Tshirts";

    category5_btn->text = "Dress";
    category5_btn->callbackData = "Dress";


    category6_btn->text = "Skirts";
    category6_btn->callbackData = "Skirts";


    category7_btn->text = "Vintage shoes";
    category7_btn->callbackData = "Vintage_shoes";

    back_btn->text = "Back to main menu";
    back_btn->callbackData = "back";

    menu.buttons.push_back(category1_btn);
    menu.buttons.push_back(category2_btn);
    menu.buttons.push_back(category3_btn);


    menu.keyboard->inlineKeyboard.push_back(menu.buttons);

    std::string label = "Choose category";

    t_bot->getApi().sendMessage(t_id,label,false,0,menu.keyboard);
    menu.buttons.clear();
    menu.keyboard->inlineKeyboard.clear();

    menu.buttons.push_back(category4_btn);
    menu.buttons.push_back(category5_btn);
    menu.buttons.push_back(category6_btn);


    menu.keyboard->inlineKeyboard.push_back(menu.buttons);

    std::cout<<"key:"<<menu.keyboard->inlineKeyboard.size()<<std::endl;
    t_bot->getApi().sendMessage(t_id,".",false,0,menu.keyboard);
    menu.buttons.clear();

    menu.keyboard->inlineKeyboard.clear();

    menu.buttons.push_back(category7_btn);
    menu.buttons.push_back(back_btn);

    menu.keyboard->inlineKeyboard.push_back(menu.buttons);

    t_bot->getApi().sendMessage(t_id,".",false,0,menu.keyboard);
}

SearchMenu::~SearchMenu() {

}
