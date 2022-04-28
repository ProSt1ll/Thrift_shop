#include <iostream>
#include "Headers/Site.h"
# include <nlohmann/json.hpp>

using nlohmann::json;

int main() {

    json settings = {
            {"chapterMap",   {
                                     {siteSearch::index, "indexUrl"},
                                     {siteSearch::man,  "manUrl"},
                                     {siteSearch::woman, "womanUrl"},
                                     {siteSearch::boy,    "boyUrl"},
                                     {siteSearch::girl, "girlUrl"}
                             }},
            {"parameterMap", {
                                     {siteSearch::url,   {
                                                                 {"tag", "tagUrl"},
                                                                 {"id", "idUrl"},
                                                                 {"cssClass", "cssClassUrl"}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "tagCost"},
                                                                {"id", "idcCst"},
                                                                {"cssClass", "cssClassCost"}
                                                        }},
                                     {siteSearch::title, {
                                                                 {"tag", "tagTitle"},
                                                                 {"id", "idTitle"},
                                                                 {"cssClass", "cssClassTitle"}
                                                         }},
                                     {siteSearch::person, {
                                                                  {"tag", "tagPerson"},
                                                                  {"id", "idPerson"},
                                                                  {"cssClass", "cssClassPerson"}
                                                          }},
                                     {siteSearch::size, {
                                                                {"tag", "tagSize"},
                                                                {"id", "idSize"},
                                                                {"cssClass", "cssClassSize"}
                                                        }},
                                     {siteSearch::image, {
                                                                 {"tag", "tagImage"},
                                                                 {"id", "idImage"},
                                                                 {"cssClass", "cssClassImage"}
                                                         }}
                             }}
    };

    json newSettings;
    newSettings["chapterMap"][std::to_string(siteSearch::index)] = "indexUrl";


    siteSearch::Site site(settings);

    std::cout << settings << std::endl << site.getSettings() << std::endl << newSettings << std::endl;
    return 0;
}
