//
// Created by ivan on 16.04.22.
//

#include "Connection.h"

Connection::Connection(tcp::socket &&socket): stream(std::move(socket)) {

}

void Connection::start() {

}

void Connection::do_read() {

}

void Connection::handle_read(beast::error_code e, std::size_t bytes_transferred) {

}

void Connection::handle_write(bool close, beast::error_code e,
                              std::size_t bytes_transferred) {

}

void Connection::do_close() {

}
