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
    boost::asio::connect(socket, results.begin(), results.end());

// Создание сообщения http запроса
    http::request<http::string_body> req{http::verb::get, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

// Отправка http запроса
    http::write(socket, req);

// Объявление буфера для получения http ответа
    boost::beast::flat_buffer buffer;

// Объявление контейнера, в котором будет храниться http ответ
    http::response<http::dynamic_body> result;

// Получение http ответа
    http::read(socket, buffer, result);

// Закрытие сокета
    socket.shutdown(tcp::socket::shutdown_both);

    return result;
}

std::string siteSearch::getStringFromResponse(const http::response<http::dynamic_body> &response) {
    std::stringstream ss;
    ss << response;
    return ss.str();
}

bool siteSearch::checkAttr(size_t start, size_t end, const std::string &attr, const std::string &htmlFile) {
    if (!attr.empty()) {
        size_t attrPos = htmlFile.find(attr, start);
        if (attrPos == std::string::npos || attrPos > end)
            return false;
    }
    return true;
}

std::string
siteSearch::getBlockContent(const std::string &htmlFile, const std::string &htmlTag, const std::string &htmlClass,
                            const std::string &htmlId, size_t pos) {
    // Нужно найти в документе блок с тегом htmlTag. И, при наличии, с классом htmlClass и id htmlId.
    bool isFound = false;
    size_t startPos = pos;
    while (!isFound) {
        // ищем начало блока по тегу
        startPos = htmlFile.find(htmlTag, pos);
        pos = startPos + 1;
        if (startPos != -1) {
            isFound = true;
        } else {
            // если в документе, начиная с pos уже нет нужного тега.
            break;
        }
        // ищем конец открывающего блока
        size_t endPos = htmlFile.find('>', pos);

        // проверка, что в блоке есть нужный класс
        if (!checkAttr(startPos, endPos, htmlClass, htmlFile)) {
            isFound = false;
            continue;
        }

        // проверка, что в блоке есть нужный id
        if (!checkAttr(startPos, endPos, htmlId, htmlFile)) {
            isFound = false;
            continue;
        }
    }
    // если не нашли даже начала нужного блока
    if (!isFound)
        return "";

    // Теперь нужно найти конец блока. Сложность заключается в том, что блоки закрываются по тегу и нужно найти нужный
    // конец, учитывая, что те же теги могут быть вложенными.

    isFound = false;
    size_t endPos = pos;
    size_t searchStartPos = startPos;
    while (true) {
        endPos = htmlFile.find("/" + htmlTag, searchStartPos);
        // ищем конец открывающего блока
        size_t blockOpenEndPos = htmlFile.find('>', searchStartPos);
        // следующий тег с тем же названием, который может быть вложенный, из-за чего нужно искать закрытие тега дальше
        size_t nextTagPos = htmlFile.find(htmlTag, blockOpenEndPos);
        if (endPos == -1)
            break;
        if (nextTagPos > endPos || nextTagPos == std::string::npos || nextTagPos == -1) {
            isFound = true;
            break;
        }
        // на следующей итерации поиск производится после вложенного закрывающего тега
        ++endPos;
        searchStartPos = endPos;
    }

    // ищем начало содержания блока, для этого ищем конец открывающего блока
    startPos = htmlFile.find('>', startPos);
    ++startPos;

    if (!isFound || endPos <= startPos)
        return "";
    // учитываем "<"
    return htmlFile.substr(startPos, endPos - startPos - 1);
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

//TODO
std::string siteSearch::getNumber(const std::string &str) {
    return std::string();
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

//TODO
std::vector<std::string> siteSearch::Site::getItemsFromHtml(const std::string& htmlFile) const {
    // По параметру itemTemplate достает все предметы из html с их набором и возвращает vector этих предметов
    size_t startIndex = 0;
    std::vector<std::string> resultVector;

    if (htmlFile.empty() || !parameterMap.count(itemTemplate))
        return {};

    TemplateParameter itemParameter = parameterMap.at(itemTemplate);
    while (true) {
        std::string htmlItem = getBlockContent(htmlFile, itemParameter.getTag(), itemParameter.getCssClass(),
                                               itemParameter.getTag(), startIndex);
        if (htmlItem.empty())
            break;

        resultVector.push_back(htmlItem);
        startIndex = htmlFile.find(htmlItem, startIndex) + htmlItem.size();
    }

    return resultVector;
}

//TODO
std::string siteSearch::Site::singleCrawl(const Parameters &parameter, const std::string &chapter,
                                          const std::string &htmlItem) const {
    // просто из html с объектом забирает строковое представление нужного параметра и возвращает его
    return std::string();
}


//TODO
json siteSearch::Site::crawlChapter(const std::set<Parameters> &parameters_, const std::string &chapter,
                                    const std::string &htmlItem) const {
    // Вызывает singleCrawl для каждого параметра и затем соединяет это в один json файл для своего объекта
    return nlohmann::json();
}

// TODO
json siteSearch::Site::crawl(const std::set<Parameters> &parameters_, const std::set<Chapters> &chapters_) const {
    // В разделах из chapters сначала берется элемент из большого списка по параметру itemTemplate, затем уже внутри
    // него идет поиск параметров из parameters и формируется json, содержащий массив items, в каждом из которых
    // лежит словарь с parameters и значениями этих параметров. По сути, запускает crawlChapter для каждой главы из
    // chapters и соединяет это все в один json. При этом делает это для каждого предмета из большого списка.
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
