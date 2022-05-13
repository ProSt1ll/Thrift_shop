#include <iostream>
#include <nlohmann/json.hpp>
#include "Headers/Site.h"
#include "Headers/Crawler.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;


int main() {
    auto tmp = siteSearch::getWebPage("www.example.com");
    auto result = siteSearch::getStringFromResponse(tmp);
    std::cout << result << std::endl;
    std::cout << std::stoi(" 19 ") << std::endl;
    return 0;
}
