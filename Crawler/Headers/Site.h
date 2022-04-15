#include <string>
#include <map>
#include <set>
#include <nlohmann/json.hpp>
#include "Clothe.h"

using nlohmann::json;

#ifndef CRAWLER_SITE_H
#define CRAWLER_SITE_H

namespace siteSearch {

    enum Chapters {
        index, man, woman, boy, girl
    };

    enum Parameters {
        url, cost, title, person, size, image
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

        explicit TemplateParameter(std::string tag_ = "", std::string id_ = "", std::string cssClass_ = "");

        // get методы

        std::string getTag() const;

        std::string getId() const;

        std::string getCssClass() const;

        // set методы

        void setTag(std::string newTag);

        void setId(std::string newId);

        void setCssClass(std::string newCssClass);

    };

    class Site {
    private:
        // key - раздел, в котором нужно искать; value - url на раздел
        std::map<Chapters, std::string> chapterMap;
        // key - параметр, который ищем; value - класс с шаблоном параметра
        std::map<Parameters, TemplateParameter> parameterMap;
    public:

        // конструкторы

        Site();

        Site(nlohmann::json settings);

        // get методы

        std::string getChapterUrl(Chapters chapter) const;

        TemplateParameter getTemplateParameter(Parameters parameter) const;

        // возвращает все доступные разделы на сайте
        std::set<Chapters> getChapters() const;

        // возвращает все доступные для поиска параметры на сайте
        std::set<Parameters> getParameters() const;

        // set методы

        // изменяет адрес раздела; если раздела не существует, то добавляет его с адресом
        void setChapterUrl(std::string url);

        // изменяет шаблон параметра; если параметра нет, то добавляет его с шаблоном
        void setTemplateParameter(TemplateParameter templateParameter);

        // перегрузка операторов
        bool operator==(const Site &site);

        // delete методы

        // удаляет из chapterMap главу по ключу chapter
        void deleteChapter(Chapters chapter);

        // удаляет из parameterMap параметр по ключу parameter
        void deleteParameter(Parameters parameter);

        // основной функционал

        // изменяет настройки сайта, принимая json с настройками;
        // возвращает: true в случае успеха и false иначе
        bool resetSettings(nlohmann::json settings);

        // ищет на сайте параметры parameters в разделах chapters
        // возвращает json с найденными объектами
        json crawl(std::set<Parameters> parameters_, std::set<Chapters> chapters_) const;

        // возвращает текущие настройки в формате json
        json getSettings() const;


    };
}

#endif //CRAWLER_SITE_H
