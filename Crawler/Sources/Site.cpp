#include "../Headers/Site.h"
#include <iostream>

using siteSearch::Chapters;
using siteSearch::Parameters;
using siteSearch::TemplateParameter;

// Вспомогательные функции

http::response<http::dynamic_body>
siteSearch::getWebPage(const std::string &host, const std::string &target, const std::string &port, int version) {

    boost::asio::io_context ioc;
    tcp::resolver resolver{ioc};
    tcp::socket socket{ioc};

// Поиск домена
    auto const results = resolver.resolve(host, port);

// Соединение по IP адресу, полученному с поиска
    boost::asio::connect(socket, results
            .

                    begin(), results

                                 .

                                         end()

    );

// Создание сообщения http запроса
    http::request<http::string_body> req{http::verb::get, target, version};
    req.
            set(http::field::host, host
    );
    req.
            set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

// Отправка http запроса
    http::write(socket, req
    );

// Объявление буфера для получения http ответа
    boost::beast::flat_buffer buffer;

// Объявление контейнера, в котором будет храниться http ответ
    http::response<http::dynamic_body> result;

// Получение http ответа
    http::read(socket, buffer, result
    );

// Закрытие сокета
    socket.
            shutdown(tcp::socket::shutdown_both);

    return
            result;
}

std::string siteSearch::getStringFromResponse(const http::response<http::dynamic_body> &response) {
    std::stringstream ss;
    ss << response;
    return ss.str();
}

// TemplateParameter

// конструкторы

siteSearch::TemplateParameter::TemplateParameter() {
    tag = "";
    id = "";
    cssClass = "";
}

siteSearch::TemplateParameter::TemplateParameter(const std::string &tag_, const std::string &id_,
                                                 const std::string &cssClass_) {
    tag = tag_;
    id = id_;
    cssClass = cssClass_;

}

// Get методы

std::string siteSearch::TemplateParameter::getTag() const {
    return tag;
}

std::string siteSearch::TemplateParameter::getId() const {
    return id;
}

std::string siteSearch::TemplateParameter::getCssClass() const {
    return cssClass;
}

nlohmann::json siteSearch::TemplateParameter::getJson() const {
    nlohmann::json resultJson;

    resultJson["tag"] = tag;
    resultJson["id"] = id;
    resultJson["cssClass"] = cssClass;

    return resultJson;
}

// Set методы

void siteSearch::TemplateParameter::setTag(const std::string &newTag) {
    tag = newTag;
}

void siteSearch::TemplateParameter::setId(const std::string &newId) {
    id = newId;
}

void siteSearch::TemplateParameter::setCssClass(const std::string &newCssClass) {
    cssClass = newCssClass;
}

// перегрузка операторов

bool siteSearch::TemplateParameter::operator==(const TemplateParameter &comparableTemplateParameter) const {
    return (id == comparableTemplateParameter.id && tag == comparableTemplateParameter.tag &&
            cssClass == comparableTemplateParameter.cssClass);
}

// Site

// конструкторы

siteSearch::Site::Site() = default;

siteSearch::Site::Site(const json &settings) {

    chapterMap = getChapterMapFromJson(settings);
    parameterMap = getParameterMapFromJson(settings);


}


// получение полей из json настроек

std::map<Chapters, std::string> siteSearch::Site::getChapterMapFromJson(const json &settings) {
    std::map<Chapters, std::string> resultMap;
    for (const auto &element: settings["chapterMap"]) {
        Chapters key = element.at(0);
        std::string value = element.at(1);
        resultMap.emplace(std::pair<Chapters, std::string>{key, value});
    }
    return resultMap;
}

std::map<Parameters, TemplateParameter> siteSearch::Site::getParameterMapFromJson(const json &settings) {
    std::map<Parameters, TemplateParameter> resultMap;
    for (const auto &element: settings["parameterMap"]) {
        Parameters key = element.at(0);
        std::string tag = element.at(1)["tag"];
        std::string id = element.at(1)["id"];
        std::string cssClass = element.at(1)["cssClass"];
        TemplateParameter templateParameter(tag, id, cssClass);
        resultMap.emplace(std::pair<Parameters, TemplateParameter>{key, templateParameter});
    }
    return resultMap;
}

// Get методы

std::string siteSearch::Site::getChapterUrl(const siteSearch::Chapters &chapter) const {
    if (chapterMap.count(chapter))
        return chapterMap.at(chapter);
    return "";
}

siteSearch::TemplateParameter siteSearch::Site::getTemplateParameter(const siteSearch::Parameters &parameter) const {
    if (parameterMap.count(parameter))
        return parameterMap.at(parameter);
    return {};
}

std::set<Chapters> siteSearch::Site::getChapters() const {
    std::set<Chapters> returnSet;
    for (const auto &element: chapterMap) {
        returnSet.emplace(element.first);
    }
    return returnSet;
}

std::set<Parameters> siteSearch::Site::getParameters() const {
    std::set<Parameters> returnSet;
    for (const auto &element: parameterMap) {
        returnSet.emplace(element.first);
    }
    return returnSet;
}

// Set методы

void siteSearch::Site::setChapterUrl(const Chapters &chapter, const std::string &url) {
    if (chapterMap.count(chapter)) {
        chapterMap[chapter] = url;
        return;
    }
    chapterMap.insert(std::pair<Chapters, std::string>{chapter, url});
}

void siteSearch::Site::setTemplateParameter(const Parameters &parameter,
                                            const siteSearch::TemplateParameter &templateParameter) {
    if (parameterMap.count(parameter)) {
        parameterMap[parameter] = templateParameter;
        return;
    }
    parameterMap.insert(std::pair<Parameters, siteSearch::TemplateParameter>{parameter, templateParameter});
}

// перегрузка операторов

bool siteSearch::operator==(const siteSearch::Site &lhs, const siteSearch::Site &rhs) {
    if (lhs.chapterMap.size() != rhs.chapterMap.size() || lhs.parameterMap.size() != rhs.parameterMap.size())
        return false;

    for (const auto &element: lhs.chapterMap) {
        if (rhs.chapterMap.at(element.first) != element.second)
            return false;
    }

    for (const auto &element: lhs.parameterMap) {
        if (!(rhs.parameterMap.at(element.first) == element.second))
            return false;
    }

    return true;
}

bool siteSearch::operator!=(const siteSearch::Site &lhs, const siteSearch::Site &rhs) {
    return !siteSearch::operator==(lhs, rhs);
}

bool siteSearch::operator<(const siteSearch::Site &lhs, const siteSearch::Site &rhs) {
    siteSearch::Chapters compareParameter = siteSearch::index;
    if (lhs.chapterMap.count(compareParameter) == 0) {
        return rhs.chapterMap.count(compareParameter);
    }
    if (rhs.chapterMap.count(compareParameter) == 0) {
        return false;
    }
    return lhs.chapterMap.at(compareParameter) < rhs.chapterMap.at(compareParameter);
}

// delete методы

void siteSearch::Site::deleteChapter(const Chapters &chapter) {
    if (chapterMap.count(chapter))
        chapterMap.erase(chapter);
}

void siteSearch::Site::deleteParameter(const Parameters &parameter) {
    if (parameterMap.count(parameter))
        parameterMap.erase(parameter);
}

// основной функционал

void siteSearch::Site::resetSettings(const json &settings) {
    chapterMap = getChapterMapFromJson(settings);
    parameterMap = getParameterMapFromJson(settings);
}

// TODO
json siteSearch::Site::crawl(const std::set<Parameters> &parameters_, const std::set<Chapters> &chapters_) const {
    return nlohmann::json();
}

json siteSearch::Site::getSettings() const {
    nlohmann::json resultJson;

    resultJson["chapterMap"] = chapterMap;

    resultJson["parameterMap"] = nlohmann::json::object();

    json parameterMapArray = json::array();

    for (const auto &element: parameterMap) {
        Parameters key = element.first;
        parameterMapArray[parameterMapArray.size()] = json::array({key, element.second.getJson()});
    }

    resultJson["parameterMap"] = parameterMapArray;
    return resultJson;
}
