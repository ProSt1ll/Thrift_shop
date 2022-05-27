//
// Created by ivan on 16.04.22.
//

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "../include/Server.h"

// Инициализируем на каком хосте и порту будем работать
Server::Server(const std::string &address, const std::string &port,
               std::size_t thread_pool_size):
               acceptor_(net::make_strand(io_context_)),
               thread_pool_size_(thread_pool_size) {

    // Открытие приемщика с возможностью повторного использования адреса (например, SO_REUSEADDR).
    boost::asio::ip::tcp::resolver resolver(io_context_);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(net::socket_base::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
}

// Запускаем цикл io_context сервера (создаем обработчики событий).
void Server::run() {
    start_accept();
    // тут формируем базу (раскомментить, когда будет работать кравлер)
//    Handlers handler_;
//    handler_.update_bd();

    // Создаем пул потоков для запуска всех io_contexts.
    std::vector<boost::shared_ptr<std::thread> > threads;
    for (std::size_t i = 0; i < thread_pool_size_; ++i)
    {
        // в каждом потоке запускаем "run" для io_context_
        boost::shared_ptr<std::thread> thread(new std::thread(
                boost::bind(&net::io_context::run, &io_context_)));
        threads.push_back(thread);
    }

    // Ожидание завершения всех потоков в пуле.
    for (auto &thread : threads)
        thread->join();
}

// Подготовка сокета, который будет испьзоваться для прослушивания
// Создаем новое соединение, которое будет использовано для обработки нового клиента
void Server::start_accept() {
    // Как только приходит пользователь, подключаем его
    // и вызываем "handle_accept" в качестве callback
    acceptor_.async_accept(
            net::make_strand(io_context_),
            beast::bind_front_handler(&Server::handle_accept, shared_from_this()));
}

// Обработка завершения асинхронной операции принятия.
void Server::handle_accept(beast::error_code error, tcp::socket socket) {
    if (!error) {
        std::cout << "accept!" << std::endl;
        // Запускаем процесс для соединения (клиента)
        auto c = std::make_shared<Connection>(std::move(socket), handlers);
        c->start();
    }
    // и уходим обратно
    start_accept();
}

// Обработка запроса на остановку сервера.
void Server::handle_stop() {
    io_context_.stop();
}
