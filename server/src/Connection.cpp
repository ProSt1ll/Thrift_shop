//
// Created by ivan on 16.04.22.
//

#include "../include/Connection.h"

// Создание соединения с заданным io_context.
Connection::Connection(tcp::socket &&socket, Handlers &handlers):
stream_(std::move(socket)), handlers_(handlers) {
}

// Запуск первой асинхронной операции (чтения) для Connection.
void Connection::start() {
    net::dispatch(stream_.get_executor(),
                  beast::bind_front_handler(&Connection::do_read,
                                            shared_from_this()));
}

// Чтение)
void Connection::do_read() {
    request_ = {};
    // Читаем request_
    http::async_read(stream_, buffer_, request_,
                     beast::bind_front_handler(
                             &Connection::handle_read,
                             shared_from_this()));
}

// Обработка завершения операции асинхронного чтения.
void Connection::handle_read(beast::error_code error, std::size_t bytes_transferred) {
    // Закрываем сессию
    if(error == http::error::end_of_stream)
        return do_close();

    std::cout << "Request target: " << request_.target() << std::endl;
    std::cout << "Request body: " << request_.body() << std::endl;
    // тут вызываем логику
    if (!error) {
        http::response<http::string_body> res{http::status::bad_request,
                                              request_.version()};
        try {
            std::string req_tar = static_cast<std::string>(request_.target());
            auto delimiterPos = req_tar.find('?');
            auto target = req_tar.substr(0, delimiterPos);

            if (target == "/add_user" &&
                request_.method() == http::verb::post) {
                res = handlers_.add_user(request_);
            } else if (target == "/get_item" &&
                       request_.method() == http::verb::post) {
                res = handlers_.get_item(request_);
            // Пока это вся логика (нужно бы навесить еще)
            } else {
                res.set(http::field::content_type, "application/json");
                res.result(http::status::not_found);
                res.body() = "Not found";
            }
        };
        std::cout << "Response status: " << std::endl << res.reason()<< std::endl;
        std::cout << "Response body: " << std::endl << res.body() << std::endl;
        std::cout << "======================================================="<< std::endl;

        auto sp = std::make_shared<http::message<false,
                http::string_body>>(std::move(res));
        res_ = sp;

        http::async_write(stream_,*sp,
                          beast::bind_front_handler(
                                  &Connection::handle_write,
                                  shared_from_this(),
                                  sp->need_eof()));
    }

}

// Обработка завершения операции асинхронной записи.
void Connection::handle_write(bool close, beast::error_code e,
                              std::size_t bytes_transferred) {
    if(close)
        // Это означает, что мы должны закрыть соединение,
        // обычно потому, что ответ указывает на семантику «Соединение: закрыть»
        return do_close();
    if (!e)
        do_read();
}

// Закрытие)
void Connection::do_close() {
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
}
