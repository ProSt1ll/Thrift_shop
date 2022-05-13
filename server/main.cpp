#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <exception>

#include "include/Server.h"

int main(int argc, char* argv[]) {
    try
    {
        // Проверяем аргументы командной строки
        if (argc != 4)
        {
            std::cerr << "Usage: http_server <address> <port> <threads>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80 1 \n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80 1 \n";
            return 1;
        }

        // Количество потоков, которые необходимо создать
        auto num_threads = boost::lexical_cast<std::size_t>(argv[3]);
        // Инициализация сервера (хост, порт, количество потоков)
        auto s = std::make_shared<Server>(argv[1], argv[2], num_threads);

        // Запускаем сервер, пока он не будет остановлен
        s->run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
