#include <gmock/gmock.h>
#include "../Headers/Clothe.h"
#include "../Headers/Crawler.h"
#include "../Headers/Site.h"

using item::Clothe;
using item::Persons;
using item::Sizes;
using siteSearch::Site;
using siteSearch::Chapters;
using siteSearch::Parameters;

#ifndef CRAWLER_MOCKS_H
#define CRAWLER_MOCKS_H

class MockClothe {
public:

    // get методы

    MOCK_METHOD(std::size_t, getCost, ());
    MOCK_METHOD(std::string, getTitle, ());
    MOCK_METHOD(std::string, getUrl, ());
    MOCK_METHOD(std::string, getImage, ());
    MOCK_METHOD(std::size_t, getPerson, ());
    MOCK_METHOD(std::size_t, getSize, ());

    // Остальные методы

    MOCK_METHOD(bool, isEmpty, ());
    MOCK_METHOD(json, getJson, ());
};

class MockSite {
public:

    // get методы

    MOCK_METHOD(std::string, getChapterUrl, (Chapters));
    MOCK_METHOD(siteSearch::TemplateParameter, getTemplateParameter, (Parameters));
    MOCK_METHOD(std::set<Chapters>, getChapters, ());
    MOCK_METHOD(std::set<Parameters>, getParameters, ());

    // основной функционал

    MOCK_METHOD(bool, resetSettings, (json));
    MOCK_METHOD(json, crawl, (std::set<Parameters>, std::set<Chapters>));
    MOCK_METHOD(json, getSettings, ());

};

class MockCrawler {
public:

    // get методы

    MOCK_METHOD(std::set<Site>, getSites, ());
    MOCK_METHOD(std::set<Chapters>, getChapters, ());
    MOCK_METHOD(std::set<Parameters>, getParameters, ());

    // основной функционал

    MOCK_METHOD(json, crawl, (std::set<Site>, std::set<Parameters>, std::set<Chapters>));
    MOCK_METHOD(bool, resetSettings, (json));
    MOCK_METHOD(json, getSettings, ());
};

#endif //CRAWLER_MOCKS_H
