#include "../include/MenuController.h"


    void MenuController::run(){
        TgBot::Bot bot("5341881620:AAFENTOHJUFUwmpvyLun51Yu5FLmesHvZYU");
        Managment main_mgm(&bot);
        net::io_context io_context;
        Client client(io_context, &main_mgm, "127.0.0.1", "5000");
        try{

            io_context.run();
        }

        catch (std::exception &e) {
            std::cout << "Exception: " << e.what() << "\n";
        }


        std::vector<std::string>bot_commands ={"start"};

        bot.getEvents().onCommand("start", [&bot, &client](TgBot::Message::Ptr message) {
            bot.getApi().sendMessage(message->chat->id, "Hello, sweetie");
            MainMenu(&bot,message->chat->id,&client);
        });
        bot.getEvents().onAnyMessage([&bot, &bot_commands](TgBot::Message::Ptr message) {
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

void MenuController::stop(){};
