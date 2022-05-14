#include "../include/Client.h"

#include <iostream>
#include <string>

#include <boost/bind/bind.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>


using tcp = boost::asio::ip::tcp;
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>


Client::Client(boost::asio::io_context &io_context,Managment *main_mgm,std::string server, std::string port)
        : resolver_(net::make_strand(io_context)),
          stream_(net::make_strand(io_context)) {
    sec_mgm = main_mgm;
    port_server=port;
}

void Client::run() {
    request_.version(11);
    request_.method(http::verb::post);
    //request_.target(path);
    request_.set(http::field::host, "127.0.0.1");
    request_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    request_.find(http::field::host);

}

void Client::post(nlohmann::json package) {
    request_.target(package);
    resolver_.async_resolve(ip_server, port_server,
                            beast::bind_front_handler(
                                    &Client::handle_resolve,
                                    shared_from_this()));

}

void Client::handle_resolve(beast::error_code err,
                            tcp::resolver::results_type results) {
    if (!err) {
        stream_.async_connect(
                results,
                beast::bind_front_handler(
                        &Client::handle_connect,
                        shared_from_this()));
    } else {
        std::cout << "Error: " << err.message() << "\n";
    }
}

void Client::handle_connect(beast::error_code err, tcp::resolver::results_type::endpoint_type) {
    if (!err) {
        http::async_write(stream_, request_,
                          beast::bind_front_handler(
                                  &Client::handle_write_request,
                                  shared_from_this()));
    } else {
        std::cout << "Error: " << err.message() << "\n";
    }
}

void Client::handle_write_request(beast::error_code err,
                                  std::size_t bytes_transferred) {
    if (!err) {
        http::async_read(stream_, buffer_, response_,
                         beast::bind_front_handler(
                                 &Client::handle_read,
                                 shared_from_this()));
    } else {
        std::cout << "Error: " << err.message() << "\n";
    }
}

void Client::handle_read(beast::error_code err,
                         std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (!err) {
        // Write the message to standard out
        sec_mgm->get_res(response_.body());
        std::cout << response_ << std::endl;

        // Gracefully close the socket
        stream_.socket().shutdown(tcp::socket::shutdown_both, err);

        // not_connected happens sometimes so don't bother reporting it.
        if (err && err != beast::errc::not_connected)
            std::cout << err << "shutdown";
    } else {
        std::cout << "Error: " << err << "\n";
    }
}

//int main(int argc, char *argv[]) {
//    try {
//        if (argc != 4) {
//            std::cout << "Usage: async_client <server> <port> <path>\n";
//            std::cout << "Example:\n";
//            std::cout << "  async_client www.boost.org /LICENSE_1_0.txt\n";
//            return 1;
//        }
//
//        net::io_context io_context;
//
//        //std::make_shared<Client>(io_context)->run(argv[1], argv[2], argv[3]);
//
//        io_context.run();
//    }
//    catch (std::exception &e) {
//        std::cout << "Exception: " << e.what() << "\n";
//    }
//
//    return 0;
//}

