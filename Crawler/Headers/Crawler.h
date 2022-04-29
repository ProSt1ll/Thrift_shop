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
    std::set<Site, std::equal_to<Site>> sites;
    // параметры, которые можем искать
    std::set<Parameters> parameters;
    // главы, которые можем искать
    std::set<Chapters> chapters;

    static std::set<Site, std::equal_to<Site>> getSitesFromSettings(const json& settings);

    static std::set<Parameters> getParametersFromSettings(const json& settings);

    static std::set<Chapters> getChaptersFromSettings(const json& settings);
public:
    // конструкторы

    Crawler();

    // принимает json с настройками сайтов
    explicit Crawler(const json &settings);

    // add методы

    // добавляет параметр для поиска в словарь
    void addParameter(const Parameters &parameter);

    // добавляет главу для поиска в словарь
    void addChapter(const Chapters &chapter);

    // добавляет сайт для поиска
    void addSite(const Site &site);

    // get методы

    std::set<Site, std::equal_to<Site>> getSites() const;

    std::set<Parameters> getParameters() const;

    std::set<Chapters> getChapters() const;

    // delete методы

    void deleteSite(const Site &site);

    void deleteChapter(const Chapters &chapter);

    void deleteParameter(const Parameters &parameter);

    // основной функционал

    // обходит сайты из sites_ по главам из chapters_ в поиске параметров из parameters_; возвращает json
    // с найденными объектами
    json crawl(const std::set<Site> &sites_, const std::set<Parameters> &parameters_,
               const std::set<Chapters> &chapters_) const;

    // применяет настройки из json
    void resetSettings(const json& settings);

    // возвращает текущие настройки в формате json
    json getSettings() const;
};


#endif //CRAWLER_CRAWLER_H
