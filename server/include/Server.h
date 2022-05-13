#ifndef THRIFT_SHOP_SERVER_H
#define THRIFT_SHOP_SERVER_H

#include <boost/asio.hpp>

#include "Handler.h"
#include "Connection.h"

class Server : public std::enable_shared_from_this<Server> {
public:
    // Инициализируем на каком хосте и порту будем работать
    explicit Server(const std::string &address, const std::string &port,
                    std::size_t thread_pool_size);

    // Запускаем цикл io_context сервера.
    void run();

private:
    // Подготовка сокета, который будет испьзоваться для прослушивания
    void start_accept();

    // Обработка завершения асинхронной операции принятия.
    void handle_accept(beast::error_code error, tcp::socket socket);

    // Обработка запроса на остановку сервера.
    void handle_stop();

    // io_context, используемый для выполнения асинхронных операций.
    net::io_context io_context_;
    // Приемщик, используемый для прослушивания входящих соединений.
    tcp::acceptor acceptor_;
    // Количество потоков, которые будут вызывать io_context::run().
    std::size_t thread_pool_size_;

    Handlers handlers;

};


#endif //THRIFT_SHOP_SERVER_H
