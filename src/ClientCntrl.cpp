#include "../include/ClientCntrl.h"

ClientCntrl::ClientCntrl(std::string some,std::function<void(std::string message)> get_mes) {
    auto client= std::make_shared<Client>(io_context,some,get_mes);
    client->run();
    io_context.run();
}

ClientCntrl::~ClientCntrl() {

}
