
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
/*
    json site_1 = {
            {"chapterMap",   {
                                     {siteSearch::index, "www.nbloom.ru"},
                                     {siteSearch::man,  "/catalog/muzhchinam_vesenniaia_kollektciia/"},
                                     {siteSearch::woman, "/"},
                                     {siteSearch::boy,    "/"},
                                     {siteSearch::girl,  "/"}
                             }},
            {"parameterMap", {
                                     {siteSearch::url,   {
                                                                 {"tag", "a"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "rr-item__info"}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "span"},
                                                                {"id", ""},
                                                                {"cssClass", "product-item-price-current"}
                                                        }},
                                     {siteSearch::title, {
                                                                 {"tag", "div"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "rr-itemname-block  rr-itemtitle"}
                                                         }},
                                     {siteSearch::person, {
                                                                  {"tag", "tagPerson_1"},
                                                                  {"id", "idTitle_1"},
                                                                  {"cssClass", "cssClassPerson_1"}
                                                          }},
                                     {siteSearch::image, {
                                                                 {"tag", "img"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "rr-def__img rr-product-img swiper-lazy swiper-lazy-loaded"}
                                                         }},
                                     {siteSearch::size, {
                                                                {"tag", "tagSize_1"},
                                                                {"id", "idTitle_1"},
                                                                {"cssClass", "cssClassSize_1"}
                                                        }},
                                     {siteSearch::itemTemplate, {
                                                                        {"tag", "div"},
                                                                        {"id", ""},
                                                                        {"cssClass", "product-item"}
                                                                }}
                             }}
    };

    json settings = {
            {"chapters",
                      {siteSearch::index, siteSearch::man,  siteSearch::woman, siteSearch::boy,    siteSearch::girl}},
            {"parameters",
                      {siteSearch::url,   siteSearch::cost, siteSearch::title, siteSearch::person, siteSearch::size, siteSearch::image}},
            {"sites", {site_1}}
    };
*/


    json site_1 = {
            {"chapterMap",   {
                                     {siteSearch::index, "moda.oc-mod.ru"},
                                     {siteSearch::man,  "/wooman/wooman_odegda/wooman_dresses/"},
                                     {siteSearch::woman, "/"},
                                     {siteSearch::boy,          "/"},
                                     {siteSearch::girl, "/"}
                             }},
            {"parameterMap", {
                                     {siteSearch::title, {
                                                                 {"tag", "span"},
                                                                 {"id", "itemprop=\"name\""},
                                                                 {"cssClass", ""}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "span"},
                                                                {"id", " "},
                                                                {"cssClass", "class=\"price_no_format"}
                                                        }},
                                     {siteSearch::image, {
                                                                 {"tag", "img"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "rr-def__img rr-product-img swiper-lazy swiper-lazy-loaded"}
                                                         }},
                                     {siteSearch::itemTemplate, {
                                                                        {"tag", "div"},
                                                                        {"id", ""},
                                                                        {"cssClass", "class=\"caption product-info clearfix\""}
                                                                }}
                             }}
    };
    json settings = {
            {"chapters",
                      {siteSearch::index, siteSearch::man,  siteSearch::woman, siteSearch::boy,    siteSearch::girl}},
            {"parameters",
                      {siteSearch::url,   siteSearch::cost, siteSearch::title, siteSearch::person, siteSearch::size, siteSearch::image}},
            {"sites", {site_1}}
    };
    Crawler crawler(settings);
    std::cout << crawler.crawl(crawler.getSites(), crawler.getParameters(), crawler.getChapters());

    return 0;
}

