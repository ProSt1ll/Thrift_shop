#include "json.hpp"
#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <arpa/inet.h>#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <arpa/inet.h>#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <arpa/inet.h>#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <pthread.h>
#include <arpa/inet.h>

#ifndef TGBOT_SERVER_H
#define TGBOT_SERVER_H

class Server {
private:
    boost::asio::ip::tcp::endpoint server_ip;
    int port;
public:
    Server();
    ~Server();
    void run();
// запуск сервера

    void start_accept();
//инициализация сокета и начало приемо-передачи

    nlohmann::json get_response();
//получение данных с сервера

    void send_request();
//отправка данных на сервер

    void stop();
// остановка сервера (в случае, если не пользуемся)
};

#endif TGBOT_SERVER_H