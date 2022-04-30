#include "../Headers/Crawler.h"

// получение полей из json с настройками

std::set<Site> Crawler::getSitesFromSettings(const json &settings) {
    std::set<Site> resultSet;
    for (const auto &siteSettings: settings["sites"]) {
        Site site(siteSettings);
        resultSet.insert(Site(siteSettings));
    }
    return resultSet;
}

std::set<Parameters> Crawler::getParametersFromSettings(const json &settings) {
    std::set<Parameters> resultSet;
    for (const auto &parameterSettings: settings["parameters"]) {
        siteSearch::Parameters parameter = parameterSettings;
        resultSet.insert(parameter);
    }
    return resultSet;
}

std::set<Chapters> Crawler::getChaptersFromSettings(const json &settings) {
    std::set<Chapters> resultSet;
    for (const auto &chapterSettings: settings["chapters"]) {
        siteSearch::Chapters chapter = chapterSettings;
        resultSet.insert(chapter);
    }
    return resultSet;
}

// конструкторы

Crawler::Crawler() = default;


Crawler::Crawler(const json &settings) {
    sites = getSitesFromSettings(settings);
    parameters = getParametersFromSettings(settings);
    chapters = getChaptersFromSettings(settings);
}

// add методы

void Crawler::addParameter(const Parameters &parameter) {
    parameters.insert(parameter);
}

void Crawler::addChapter(const Chapters &chapter) {
    chapters.insert(chapter);
}

void Crawler::addSite(const Site &site) {
    sites.insert(site);
}

// get методы

std::set<Site> Crawler::getSites() const {
    return sites;
}

std::set<Parameters> Crawler::getParameters() const {
    return parameters;
}

std::set<Chapters> Crawler::getChapters() const {
    return chapters;
}

// delete методы

void Crawler::deleteSite(const Site &site) {
    if (sites.count(site))
        sites.erase(site);
}

void Crawler::deleteChapter(const Chapters &chapter) {
    if (chapters.count(chapter))
        chapters.erase(chapter);
}

void Crawler::deleteParameter(const Parameters &parameter) {
    if (parameters.count(parameter))
        parameters.erase(parameter);
}

// основной функционал

// TODO
json Crawler::crawl(const std::set<Site> &sites_, const std::set<Parameters> &parameters_,
                    const std::set<Chapters> &chapters_) const {
    return nlohmann::json();
}

void Crawler::resetSettings(const json &settings) {
    sites = getSitesFromSettings(settings);
    parameters = getParametersFromSettings(settings);
    chapters = getChaptersFromSettings(settings);
}

json Crawler::getSettings() const {
    json resultJson;
    resultJson["chapters"] = chapters;
    resultJson["parameters"] = parameters;

    json sitesJson = json::array();
    for (const auto &site: sites) {
        sitesJson[sitesJson.size()] = site.getSettings();
    }
    resultJson["sites"] = sitesJson;

    return resultJson;
}

