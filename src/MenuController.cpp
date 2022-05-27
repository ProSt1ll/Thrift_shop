#include "../include/MenuController.h"

    void MenuController::run(std::function<void (std::string message)> get_mes){

        std::vector<std::string>bot_commands ={"start"};

        bot.getEvents().onCommand("start", [this, &get_mes](TgBot::Message::Ptr message) {
            bot.getApi().sendMessage(message->chat->id, "Hello, sweetie");
            MainMenu Main(&bot,message->chat->id,[&](std::string message){get_mes(message); });
            SearchMenu search()
            Main.run();
        });
        bot.getEvents().onAnyMessage([this, &bot_commands](TgBot::Message::Ptr message) {
            printf("User wrote %s\n", message->text.c_str());
            for (const auto& command : bot_commands){
                if ("/"+command == message->text){
                    return;
                }
                bot.getApi().sendMessage(message->chat->id, "не понял...");
            }
        });


        try {
            printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
            TgBot::TgLongPoll longPoll(bot);
            while (true) {
                printf("Long poll started\n");
                longPoll.start();
            }
        } catch (TgBot::TgException& e) {
            printf("error: %s\n", e.what());
        }

    }

void MenuController::stop(){}

