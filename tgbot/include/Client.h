

#ifndef TGBOT_CLIENT_H
#define TGBOT_CLIENT_H

#include <iostream>
#include <string>
#include "json.hpp"
#include <boost/bind/bind.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>


using tcp = boost::asio::ip::tcp;
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>


class Client : public std::enable_shared_from_this<Client>
{
public:
    Client(boost::asio::io_context& io_context,std::string message,std::function<void(std::string message)> get_mes);
    void try_read();
    void run();
    void post(nlohmann::json package);
    void send_msg(std::string some);
private:
    void handle_resolve(beast::error_code err,
                        tcp::resolver::results_type results);
    void handle_resolver2(beast::error_code err,
                        tcp::resolver::results_type results);

    void handle_connect(beast::error_code err, tcp::resolver::results_type::endpoint_type);
    void handle_connect2(beast::error_code err, tcp::resolver::results_type::endpoint_type);
    void handle_write_request(beast::error_code err,
                              std::size_t bytes_transferred);

    void handle_read(beast::error_code err,
                     std::size_t bytes_transferred);
    void stop();
    void set(std::function<void(std::string message)> get_mes);
private:
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    std::basic_string<char> ip_server;
    std::basic_string<char> port_server;
    http::request<http::empty_body> request_;
    http::response<http::string_body> response_;
    std::string to_serv;
    std::function<void(std::string message)> manage;
    tcp::resolver::results_type result;

};


#endif //TGBOT_CLIENT_H
