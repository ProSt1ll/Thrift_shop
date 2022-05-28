#include "Client.h"

#ifndef TGBOT_CLIENTCNTRL_H
#define TGBOT_CLIENTCNTRL_H
class ClientCntrl{
public:
    ClientCntrl(std::string some,std::function<void(std::string message)> get_mes);
    ~ClientCntrl();
    boost::asio::io_context io_context;

};
#endif //TGBOT_CLIENTCNTRL_H
