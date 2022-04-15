#include <nlohmann/json.hpp>
#include <set>
#include "Clothe.h"
#include "Site.h"

using siteSearch::Site;
using siteSearch::Parameters;
using siteSearch::Chapters;
using nlohmann::json;

#ifndef CRAWLER_CRAWLER_H
#define CRAWLER_CRAWLER_H

class Crawler {
private:
    // сайты, которые можем обходить
    std::set<Site> sites;
    // параметры, которые можем искать
    std::set<Parameters> parameters;
    // главы, которые можем искать
    std::set<Chapters> chapters;
public:
    // конструкторы

    Crawler();

    // принимает json с настройками сайтов
    explicit Crawler(json settings);

    // add методы

    // добавляет параметр для поиска в словарь
    void addParameter(Parameters parameter);

    // добавляет главу для поиска в словарь
    void addChapter(Chapters chapter);

    // добавляет сайт для поиска
    void addSite(const Site &site);

    // get методы

    std::set<Site> getSites() const;

    std::set<Parameters> getParameters() const;

    std::set<Chapters> getChapters() const;

    // delete методы

    void deleteSite(Site site);

    void deleteChapter(Chapters chapter);

    void deleteParameter(Parameters parameter);

    // основной функционал

    // обходит сайты из sites_ по главам из chapters_ в поиске параметров из parameters_; возвращает json
    // с найденными объектами
    json crawl(std::set<Site> sites_, std::set<Parameters> parameters_,
               std::set<Chapters> chapters_) const;

    // применяет настройки из json; возвращает true, если успешно и false иначе
    bool resetSettings(json settings);

    // возвращает текущие настройки в формате json
    json getSettings() const;
};


#endif //CRAWLER_CRAWLER_H
