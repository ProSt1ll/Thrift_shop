//
// Created by ivan on 16.04.22.
//

#include "../include/Server.h"

Server::Server(const std::string &address, const std::string &port,
               std::size_t thread_pool_size): acceptor(net::make_strand(io_context)),
                                              thread_pool_size(thread_pool_size) {

}

void Server::Run() {
    StartAccept();

}

void Server::StartAccept() {

}

void Server::HandleAccept() {

}

void Server::HandleStop() {

}
