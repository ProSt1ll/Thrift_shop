#include <string>
#include <map>
#include <set>
#include <vector>
#include <nlohmann/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "Clothe.h"

using nlohmann::json;
using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

#ifndef CRAWLER_SITE_H
#define CRAWLER_SITE_H

namespace siteSearch {

// принимает хост, порт, целевую страницу, версию http; возвращает http ответ
    http::response<http::dynamic_body>
    getWebPage(const std::string &host, const std::string &target = "/", const std::string &port = "80",
               int version = 11);

// возвращает строковое представление результата http запроса
    std::string getStringFromResponse(const http::response<http::dynamic_body> &response);

// Проверяет, что в открывающем блоке есть аттрибут Attr. start - позиция "<", end - позиция ">"
    bool checkAttr(size_t start, size_t end, const std::string &attr, const std::string &htmlFile);

// Возвращает строковое содержание тега tag, начиная с позиции start, в файле file
    std::string
    getBlockContent(const std::string &htmlFile, const std::string &htmlTag, const std::string &htmlClass = "",
                    const std::string &htmlId = "", size_t pos = 0);

// Находит в строке первое число и возвращает его в виде строки
    std::string getNumber(const std::string &str);

    enum Chapters {
        index, man, woman, boy, girl
    };

    enum Parameters {
        url, cost, title, person, size, image, itemTemplate
    };

    class TemplateParameter {
    private:
        // тэг, в котором находится параметр
        std::string tag;
        // id, в котором находится параметр
        std::string id;
        // css класс, в котором находится параметр
        std::string cssClass;

    public:
        // конструкторы

        TemplateParameter();

        explicit TemplateParameter(const std::string &tag_, const std::string &id_ = "",
                                   const std::string &cssClass_ = "");

        // get методы

        std::string getTag() const;

        std::string getId() const;

        std::string getCssClass() const;

        // set методы

        void setTag(const std::string &newTag);

        void setId(const std::string &newId);

        void setCssClass(const std::string &newCssClass);


        // перегрузка операторов

        bool operator==(const TemplateParameter &comparableTemplateParameter) const;

        // возвращает json представление класса

        nlohmann::json getJson() const;
    };

    class Site {
    private:
        // key - раздел, в котором нужно искать; value - url на раздел
        std::map<Chapters, std::string> chapterMap;
        // key - параметр, который ищем; value - класс с шаблоном параметра
        std::map<Parameters, TemplateParameter> parameterMap;

        // получение полей из json настроек

        // возвращает chapterMap из json файла настроек
        static std::map<Chapters, std::string> getChapterMapFromJson(const nlohmann::json &settings);

        // возвращает parameterMap из json файла настроек
        static std::map<Parameters, TemplateParameter> getParameterMapFromJson(const nlohmann::json &settings);

    public:

        // конструкторы

        Site();

        explicit Site(const nlohmann::json &settings);

        // get методы

        std::string getChapterUrl(const Chapters &chapter) const;

        TemplateParameter getTemplateParameter(const Parameters &parameter) const;

        // возвращает все доступные разделы на сайте
        std::set<Chapters> getChapters() const;

        // возвращает все доступные для поиска параметры на сайте
        std::set<Parameters> getParameters() const;

        // set методы

        // изменяет адрес раздела; если раздела не существует, то добавляет его с адресом
        void setChapterUrl(const Chapters &chapter, const std::string &url);

        // изменяет шаблон параметра; если параметра нет, то добавляет его с шаблоном
        void setTemplateParameter(const Parameters &parameter, const TemplateParameter &templateParameter);

        // перегрузка операторов

        friend bool operator==(const Site &lhs, const Site &rhs);

        friend bool operator!=(const Site &lhs, const Site &rhs);

        // сравнение идет по строке ссылки на index
        friend bool operator<(const Site &lhs, const Site &rhs);

        // delete методы

        // удаляет из chapterMap главу по ключу chapter
        void deleteChapter(const Chapters &chapter);

        // удаляет из parameterMap параметр по ключу parameter
        void deleteParameter(const Parameters &parameter);

        // основной функционал

        // изменяет настройки сайта, принимая json с настройками;
        void resetSettings(const nlohmann::json &settings);

        // из html страницы с предметами достает каждый предмет и возвращает vector с ними
        std::vector<std::string> getItemsFromHtml(const std::string &htmlFile) const;

        // ищет значение параметра в html предмета и возвращает строковое значение параметра
        std::string
        singleCrawl(const Parameters &parameter, const std::string &htmlItem) const;

        // ищет значения всех параметров в html и возвращает json с параметрами предмета из htmlItem
        json crawlHtml(const std::set<Parameters> &parameters_, const std::string &htmlFile) const;

        // ищет все предметы из массива html страниц и возвращает json с предметами
        json crawlHtmlVector(const std::set<Parameters> &parameters_, const std::vector<std::string> &htmlVector) const;

        // скачивает страницы из chapters и возвращает json предметов из них
        json crawlChapters(const std::set<Parameters> &parameters_, const std::set<Chapters> &chapters_) const;

        // возвращает текущие настройки в формате json
        json getSettings() const;


    };
}

#endif //CRAWLER_SITE_H
