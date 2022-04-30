#include <gtest/gtest.h>
#include "../Headers/Crawler.h"
#include "../Headers/Site.h"
#include "../Headers/Clothe.h"
#include "Mocks.h"
#include <set>

using item::Clothe;
using item::Persons;
using item::Sizes;
using siteSearch::Site;
using siteSearch::Chapters;
using siteSearch::Parameters;
using siteSearch::TemplateParameter;

class TestClothe : public ::testing::Test {
public:
    Clothe clotheEmpty;
    Clothe clothe;

    std::string title = "Title";
    int cost = 100;
    std::string url = "someSite.com/catalog/someItem";
    Persons person = item::man;
    Sizes size = item::m;
    std::string image = "someSite.com/catalog/someImageUrl";

protected:

    void SetUp() override {
        clotheEmpty = Clothe();

        clothe = Clothe(title, cost, url, person, size, image);


    }

    void TearDown() {
    }
};

class TestTemplateParameters : public ::testing::Test {
public:
    TemplateParameter templateParameterEmpty;
    TemplateParameter templateParameter;

    std::string tag = "someTag";
    std::string id = "someId";
    std::string cssClass = "someCssClass";

protected:
    void SetUp() {
        templateParameterEmpty = TemplateParameter();
        templateParameter = TemplateParameter(tag, id, cssClass);
    }

    void TearDown() {
    }
};

class TestSite : public ::testing::Test {
public:

    Site siteEmpty;
    Site site;
    json emptySettings = {
            {"chapterMap",   json::array()},
            {"parameterMap", json::array()}
    };
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


    void SetUp() {
        siteEmpty = Site();
        site = Site(settings);
    }

    void TearDown() {
    }
};

class TestCrawler : public ::testing::Test {
public:
    Crawler crawler;
    Crawler crawlerEmpty;
    std::set<Chapters> chapters = {siteSearch::index, siteSearch::man, siteSearch::woman, siteSearch::boy,
                                   siteSearch::girl};
    std::set<Parameters> parameters = {siteSearch::url, siteSearch::cost, siteSearch::title, siteSearch::person,
                                       siteSearch::size, siteSearch::image};
    std::set<Chapters> chaptersEmpty;
    std::set<Parameters> parametersEmpty;
    std::set<Site> sitesEmpty;

    json site_1 = {
            {"chapterMap",   {
                                     {siteSearch::index, "indexUrl_1"},
                                     {siteSearch::man,  "manUrl_1"},
                                     {siteSearch::woman, "womanUrl_1"},
                                     {siteSearch::boy,    "boyUrl_1"},
                                     {siteSearch::girl, "girlUrl_1"}
                             }},
            {"parameterMap", {
                                     {siteSearch::url,   {
                                                                 {"tag", "tagUrl_1"},
                                                                 {"id", "idUrl_1"},
                                                                 {"cssClass", "cssClassUrl_1"}
                                                         }},
                                     {siteSearch::cost, {
                                                                {"tag", "tagCost_1"},
                                                                {"id", "idcCst_1"},
                                                                {"cssClass", "cssClassCost_1"}
                                                        }},
                                     {siteSearch::title, {
                                                                 {"tag", "tagTitle_1"},
                                                                 {"id", "idTitle_1"},
                                                                 {"cssClass", "cssClassTitle_1"}
                                                         }},
                                     {siteSearch::person, {
                                                                  {"tag", "tagPerson_1"},
                                                                  {"id", "idPerson_1"},
                                                                  {"cssClass", "cssClassPerson_1"}
                                                          }},
                                     {siteSearch::size, {
                                                                {"tag", "tagSize_1"},
                                                                {"id", "idSize_1"},
                                                                {"cssClass", "cssClassSize_1"}
                                                        }},
                                     {siteSearch::image, {
                                                                 {"tag", "tagImage_1"},
                                                                 {"id", "idImage_1"},
                                                                 {"cssClass", "cssClassImage_1"}
                                                         }}
                             }}
    };

    json site_2 = {
            {"chapterMap", {
                    {siteSearch::index, "indexUrl_2"},
                    {siteSearch::man, "manUrl_2"},
                    {siteSearch::woman, "womanUrl_2"},
                    {siteSearch::boy, "boyUrl_2"},
                    {siteSearch::girl, "girlUrl_2"}
            }},
            {"parameterMap", {
                    {siteSearch::url, {
                            {"tag", "tagUrl_2"},
                            {"id", "idUrl_2"},
                            {"cssClass", "cssClassUrl_2"}
                    }},
                    {siteSearch::cost, {
                            {"tag", "tagCost_2"},
                            {"id", "idcCst_2"},
                            {"cssClass", "cssClassCost_2"}
                    }},
                    {siteSearch::title, {
                            {"tag", "tagTitle_2"},
                            {"id", "idTitle_2"},
                            {"cssClass", "cssClassTitle_2"}
                    }},
                    {siteSearch::person, {
                            {"tag", "tagPerson_2"},
                            {"id", "idPerson_2"},
                            {"cssClass", "cssClassPerson_2"}
                    }},
                    {siteSearch::size, {
                            {"tag", "tagSize_2"},
                            {"id", "idSize_2"},
                            {"cssClass", "cssClassSize_2"}
                    }},
                    {siteSearch::image, {
                            {"tag", "tagImage_2"},
                            {"id", "idImage_2"},
                            {"cssClass", "cssClassImage_2"}
                    }}
            }}
    };

    json emptySettings = {
            {"chapters",   json::array()},
            {"parameters", json::array()},
            {"sites",      json::array()}
    };

    json settings = {
            {"chapters",
                      {siteSearch::index, siteSearch::man,  siteSearch::woman, siteSearch::boy,    siteSearch::girl}},
            {"parameters",
                      {siteSearch::url,   siteSearch::cost, siteSearch::title, siteSearch::person, siteSearch::size, siteSearch::image}},
            {"sites", {site_1,
                                          site_2
                      }}
    };

    std::set<Site> sites = {Site(site_1), Site(site_2)};

    void SetUp() {
        crawlerEmpty = Crawler();
        crawler = Crawler(settings);
        sites = {Site(site_1), Site(site_2)};
        chapters = {siteSearch::index, siteSearch::man, siteSearch::woman, siteSearch::boy,
                    siteSearch::girl};
        parameters = {siteSearch::url, siteSearch::cost, siteSearch::title, siteSearch::person,
                      siteSearch::size, siteSearch::image};
    }

    void TearDown() {
    }
};

// TestClothe

TEST_F(TestClothe, gets) {
    // empty clothe
    EXPECT_EQ(clotheEmpty.getCost(), 0);
    EXPECT_EQ(clotheEmpty.getImage(), "");
    EXPECT_EQ(clotheEmpty.getPerson(), item::undefinedPerson);
    EXPECT_EQ(clotheEmpty.getSize(), item::undefinedSize);
    EXPECT_EQ(clotheEmpty.getTitle(), "");
    EXPECT_EQ(clotheEmpty.getUrl(), "");

    // not emtpy clothe
    EXPECT_EQ(clothe.getCost(), cost);
    EXPECT_EQ(clothe.getImage(), image);
    EXPECT_EQ(clothe.getPerson(), person);
    EXPECT_EQ(clothe.getSize(), size);
    EXPECT_EQ(clothe.getTitle(), title);
    EXPECT_EQ(clothe.getUrl(), url);
}

TEST_F(TestClothe, sets) {
    int newCost = 50;
    std::string newImage = image + "New";
    Persons newPerson = item::woman;
    Sizes newSize = item::l;
    std::string newTitle = title + "New";
    std::string newUrl = url + "New";

    clothe.setCost(newCost);
    clothe.setImage(newImage);
    clothe.setPerson(newPerson);
    clothe.setSize(newSize);
    clothe.setTitle(newTitle);
    clothe.setURL(newUrl);

    EXPECT_EQ(clothe.getCost(), newCost);
    EXPECT_EQ(clothe.getImage(), newImage);
    EXPECT_EQ(clothe.getPerson(), newPerson);
    EXPECT_EQ(clothe.getSize(), newSize);
    EXPECT_EQ(clothe.getTitle(), newTitle);
    EXPECT_EQ(clothe.getUrl(), newUrl);
}

TEST_F(TestClothe, operatorComparator) {
    EXPECT_FALSE(clothe == clotheEmpty);

    clotheEmpty.setCost(cost);
    clotheEmpty.setImage(image);
    clotheEmpty.setPerson(person);
    clotheEmpty.setSize(size);
    clotheEmpty.setTitle(title);
    clotheEmpty.setURL(url);

    EXPECT_TRUE(clothe == clotheEmpty);
}

TEST_F(TestClothe, operatorAssignment) {
    clotheEmpty = clothe;

    EXPECT_TRUE(clothe == clotheEmpty);
}

TEST_F(TestClothe, isEmpty) {
    EXPECT_TRUE(clotheEmpty.isEmpty());
    EXPECT_FALSE(clothe.isEmpty());
}

TEST_F(TestClothe, getJson) {
    json emptyJson = {
            {"cost",   0},
            {"title",  ""},
            {"url",    ""},
            {"person", item::undefinedPerson},
            {"size",   item::undefinedSize},
            {"image",  ""}
    };
    EXPECT_EQ(emptyJson, clotheEmpty.getJson());

    json notEmptyJson = {
            {"cost",   cost},
            {"title",  title},
            {"url",    url},
            {"person", person},
            {"size",   size},
            {"image",  image}
    };
    EXPECT_EQ(notEmptyJson, clothe.getJson());
}

// TestTemplateParameters

TEST_F(TestTemplateParameters, operatorComparator) {
    TemplateParameter comparableTemplateParameter(tag, id, cssClass);
    EXPECT_TRUE(comparableTemplateParameter == templateParameter);
    EXPECT_FALSE(comparableTemplateParameter == templateParameterEmpty);
}

TEST_F(TestTemplateParameters, gets) {
    EXPECT_EQ(templateParameterEmpty.getTag(), "");
    EXPECT_EQ(templateParameterEmpty.getId(), "");
    EXPECT_EQ(templateParameterEmpty.getCssClass(), "");

    EXPECT_EQ(templateParameter.getTag(), tag);
    EXPECT_EQ(templateParameter.getId(), id);
    EXPECT_EQ(templateParameter.getCssClass(), cssClass);
}

TEST_F(TestTemplateParameters, sets) {
    templateParameterEmpty.setTag(tag);
    templateParameterEmpty.setId(id);
    templateParameterEmpty.setCssClass(cssClass);

    EXPECT_EQ(templateParameterEmpty.getTag(), tag);
    EXPECT_EQ(templateParameterEmpty.getId(), id);
    EXPECT_EQ(templateParameterEmpty.getCssClass(), cssClass);
}

TEST_F(TestTemplateParameters, getJson) {
    json emptyJson = {
            {"tag",      ""},
            {"id",       ""},
            {"cssClass", ""}
    };
    EXPECT_EQ(emptyJson, templateParameterEmpty.getJson());

    json notEmptyJson = {
            {"tag",      tag},
            {"id",       id},
            {"cssClass", cssClass}
    };
    EXPECT_EQ(notEmptyJson, templateParameter.getJson());
}

// TestSite

TEST_F(TestSite, gets) {
    // getChapterUrl
    EXPECT_EQ(site.getChapterUrl(siteSearch::index), settings["chapterMap"][siteSearch::index].at(1));
    EXPECT_EQ(site.getChapterUrl(siteSearch::man), settings["chapterMap"][siteSearch::man].at(1));
    EXPECT_EQ(site.getChapterUrl(siteSearch::woman), settings["chapterMap"][siteSearch::woman].at(1));
    EXPECT_EQ(site.getChapterUrl(siteSearch::boy), settings["chapterMap"][siteSearch::boy].at(1));
    EXPECT_EQ(site.getChapterUrl(siteSearch::girl), settings["chapterMap"][siteSearch::girl].at(1));
    EXPECT_EQ(siteEmpty.getChapterUrl(siteSearch::man), "");

    // getTemplateParameter
    EXPECT_EQ(siteEmpty.getTemplateParameter(siteSearch::url), TemplateParameter());
    json currentSetting = settings["parameterMap"][siteSearch::url];
    EXPECT_EQ(site.getTemplateParameter(siteSearch::url),
              TemplateParameter(currentSetting.at(1)["tag"], currentSetting.at(1)["id"],
                                currentSetting.at(1)["cssClass"]));
    currentSetting = settings["parameterMap"][siteSearch::cost];
    EXPECT_EQ(site.getTemplateParameter(siteSearch::cost),
              TemplateParameter(currentSetting.at(1)["tag"], currentSetting.at(1)["id"],
                                currentSetting.at(1)["cssClass"]));
    currentSetting = settings["parameterMap"][siteSearch::title];
    EXPECT_EQ(site.getTemplateParameter(siteSearch::title),
              TemplateParameter(currentSetting.at(1)["tag"], currentSetting.at(1)["id"],
                                currentSetting.at(1)["cssClass"]));
    currentSetting = settings["parameterMap"][siteSearch::person];
    EXPECT_EQ(site.getTemplateParameter(siteSearch::person),
              TemplateParameter(currentSetting.at(1)["tag"], currentSetting.at(1)["id"],
                                currentSetting.at(1)["cssClass"]));
    currentSetting = settings["parameterMap"][siteSearch::size];
    EXPECT_EQ(site.getTemplateParameter(siteSearch::size),
              TemplateParameter(currentSetting.at(1)["tag"], currentSetting.at(1)["id"],
                                currentSetting.at(1)["cssClass"]));
    currentSetting = settings["parameterMap"][siteSearch::image];
    EXPECT_EQ(site.getTemplateParameter(siteSearch::image),
              TemplateParameter(currentSetting.at(1)["tag"], currentSetting.at(1)["id"],
                                currentSetting.at(1)["cssClass"]));

    // getChapters
    std::set<Chapters> setChapters;
    EXPECT_EQ(setChapters, siteEmpty.getChapters());
    for (const auto &element: settings["chapterMap"]) {
        Chapters currentChapter = element.at(0);
        setChapters.insert(currentChapter);
    }
    EXPECT_EQ(setChapters, site.getChapters());

    // getParameters
    std::set<Parameters> setParameters;
    EXPECT_EQ(setParameters, siteEmpty.getParameters());
    for (const auto &element: settings["parameterMap"]) {
        Parameters currentParameter = element.at(0);
        setParameters.insert(currentParameter);
    }
    EXPECT_EQ(setParameters, site.getParameters());
}

TEST_F(TestSite, sets) {
    // setChapterUrl
    Chapters chapter = siteSearch::index;
    json currentSetting = settings["chapterMap"][chapter].at(1);
    siteEmpty.setChapterUrl(chapter, currentSetting);
    EXPECT_EQ(siteEmpty.getChapterUrl(chapter), currentSetting);

    chapter = siteSearch::man;
    currentSetting = settings["chapterMap"][chapter].at(1);
    siteEmpty.setChapterUrl(chapter, currentSetting);
    EXPECT_EQ(siteEmpty.getChapterUrl(chapter), currentSetting);

    chapter = siteSearch::woman;
    currentSetting = settings["chapterMap"][chapter].at(1);
    siteEmpty.setChapterUrl(chapter, currentSetting);
    EXPECT_EQ(siteEmpty.getChapterUrl(chapter), currentSetting);

    chapter = siteSearch::boy;
    currentSetting = settings["chapterMap"][chapter].at(1);
    siteEmpty.setChapterUrl(chapter, currentSetting);
    EXPECT_EQ(siteEmpty.getChapterUrl(chapter), currentSetting);

    chapter = siteSearch::girl;
    currentSetting = settings["chapterMap"][chapter].at(1);
    siteEmpty.setChapterUrl(chapter, currentSetting);
    EXPECT_EQ(siteEmpty.getChapterUrl(chapter), currentSetting);

    // setTemplateParameter
    Parameters parameter = siteSearch::url;
    currentSetting = settings["parameterMap"][parameter].at(1);
    TemplateParameter templateParameter(currentSetting["tag"], currentSetting["id"],
                                        currentSetting["cssClass"]);
    siteEmpty.setTemplateParameter(parameter, templateParameter);
    EXPECT_EQ(siteEmpty.getTemplateParameter(parameter), templateParameter);

    parameter = siteSearch::cost;
    currentSetting = settings["parameterMap"][parameter].at(1);
    templateParameter = TemplateParameter(currentSetting["tag"], currentSetting["id"],
                                          currentSetting["cssClass"]);
    siteEmpty.setTemplateParameter(parameter, templateParameter);
    EXPECT_EQ(siteEmpty.getTemplateParameter(parameter), templateParameter);

    parameter = siteSearch::title;
    currentSetting = settings["parameterMap"][parameter].at(1);
    templateParameter = TemplateParameter(currentSetting["tag"], currentSetting["id"],
                                          currentSetting["cssClass"]);
    siteEmpty.setTemplateParameter(parameter, templateParameter);
    EXPECT_EQ(siteEmpty.getTemplateParameter(parameter), templateParameter);

    parameter = siteSearch::person;
    currentSetting = settings["parameterMap"][parameter].at(1);
    templateParameter = TemplateParameter(currentSetting["tag"], currentSetting["id"],
                                          currentSetting["cssClass"]);
    siteEmpty.setTemplateParameter(parameter, templateParameter);
    EXPECT_EQ(siteEmpty.getTemplateParameter(parameter), templateParameter);

    parameter = siteSearch::size;
    currentSetting = settings["parameterMap"][parameter].at(1);
    templateParameter = TemplateParameter(currentSetting["tag"], currentSetting["id"],
                                          currentSetting["cssClass"]);
    siteEmpty.setTemplateParameter(parameter, templateParameter);
    EXPECT_EQ(siteEmpty.getTemplateParameter(parameter), templateParameter);

    parameter = siteSearch::image;
    currentSetting = settings["parameterMap"][parameter].at(1);
    templateParameter = TemplateParameter(currentSetting["tag"], currentSetting["id"],
                                          currentSetting["cssClass"]);
    siteEmpty.setTemplateParameter(parameter, templateParameter);
    EXPECT_EQ(siteEmpty.getTemplateParameter(parameter), templateParameter);

    EXPECT_TRUE(siteEmpty == site);
}

TEST_F(TestSite, deletes) {
    // deleteChapter
    Chapters chapter = siteSearch::index;
    site.deleteChapter(chapter);
    EXPECT_EQ(site.getChapterUrl(chapter), "");

    chapter = siteSearch::man;
    site.deleteChapter(chapter);
    EXPECT_EQ(site.getChapterUrl(chapter), "");

    chapter = siteSearch::woman;
    site.deleteChapter(chapter);
    EXPECT_EQ(site.getChapterUrl(chapter), "");

    chapter = siteSearch::boy;
    site.deleteChapter(chapter);
    EXPECT_EQ(site.getChapterUrl(chapter), "");

    chapter = siteSearch::girl;
    site.deleteChapter(chapter);
    EXPECT_EQ(site.getChapterUrl(chapter), "");

    //deleteParameter
    //url, cost, title, person, size, image
    Parameters parameter = siteSearch::url;
    site.deleteParameter(parameter);
    EXPECT_EQ(site.getTemplateParameter(parameter), TemplateParameter());

    parameter = siteSearch::cost;
    site.deleteParameter(parameter);
    EXPECT_EQ(site.getTemplateParameter(parameter), TemplateParameter());

    parameter = siteSearch::title;
    site.deleteParameter(parameter);
    EXPECT_EQ(site.getTemplateParameter(parameter), TemplateParameter());

    parameter = siteSearch::person;
    site.deleteParameter(parameter);
    EXPECT_EQ(site.getTemplateParameter(parameter), TemplateParameter());

    parameter = siteSearch::size;
    site.deleteParameter(parameter);
    EXPECT_EQ(site.getTemplateParameter(parameter), TemplateParameter());

    parameter = siteSearch::image;
    site.deleteParameter(parameter);
    EXPECT_EQ(site.getTemplateParameter(parameter), TemplateParameter());
}

TEST_F(TestSite, operatorCompare) {
    Site equalitySiteEmpty;
    Site equalitySite(settings);

    EXPECT_TRUE(equalitySiteEmpty == siteEmpty);
    EXPECT_TRUE(equalitySite == site);

    EXPECT_FALSE(site == siteEmpty);

    EXPECT_FALSE(site < siteEmpty);
    EXPECT_TRUE(siteEmpty < site);

    siteEmpty.setChapterUrl(siteSearch::index, "a" + site.getChapterUrl(siteSearch::index));
    EXPECT_FALSE(site < siteEmpty);
    EXPECT_TRUE(siteEmpty < site);

    siteEmpty.setChapterUrl(siteSearch::index, "z");
    EXPECT_TRUE(site < siteEmpty);
    EXPECT_FALSE(siteEmpty < site);
}

TEST_F(TestSite, resetSettings) {
    site.resetSettings(emptySettings);
    EXPECT_EQ(emptySettings, site.getSettings());

    site.resetSettings(settings);
    EXPECT_EQ(settings, site.getSettings());
}

TEST_F(TestSite, getSettings) {
    EXPECT_EQ(emptySettings, siteEmpty.getSettings());

    EXPECT_EQ(settings, site.getSettings());
}

// TODO
TEST_F(TestSite, crawl) {
}

// TestCrawler

TEST_F(TestCrawler, adds) {
    for (const auto &element: parameters) {
        crawlerEmpty.addParameter(element);
    }
    for (const auto &element: chapters) {
        crawlerEmpty.addChapter(element);
    }
    for (const auto &element: sites) {
        crawlerEmpty.addSite(element);
    }
    EXPECT_EQ(crawlerEmpty.getParameters(), parameters);
    EXPECT_EQ(crawlerEmpty.getChapters(), chapters);
    EXPECT_EQ(crawlerEmpty.getSites(), sites);
}

TEST_F(TestCrawler, gets) {
    EXPECT_EQ(parametersEmpty, crawlerEmpty.getParameters());
    EXPECT_EQ(chaptersEmpty, crawlerEmpty.getChapters());
    EXPECT_EQ(sitesEmpty, crawlerEmpty.getSites());

    EXPECT_EQ(parameters, crawler.getParameters());
    EXPECT_EQ(chapters, crawler.getChapters());
    EXPECT_EQ(sites, crawler.getSites());
}

TEST_F(TestCrawler, deletes) {
    for (const auto &element: parameters) {
        crawler.deleteParameter(element);
    }
    for (const auto &element: chapters) {
        crawler.deleteChapter(element);
    }
    for (const auto &element: sites) {
        crawler.deleteSite(element);
    }
    EXPECT_EQ(crawlerEmpty.getParameters(), crawler.getParameters());
    EXPECT_EQ(crawlerEmpty.getChapters(), crawler.getChapters());
    EXPECT_EQ(crawlerEmpty.getSites(), crawler.getSites());
}

TEST_F(TestCrawler, getSettings) {
    EXPECT_EQ(settings, crawler.getSettings());
    EXPECT_EQ(emptySettings, crawlerEmpty.getSettings());
}

TEST_F(TestCrawler, resetSettigs) {
    crawlerEmpty.resetSettings(settings);
    crawler.resetSettings(emptySettings);
    EXPECT_EQ(settings, crawlerEmpty.getSettings());
    EXPECT_EQ(emptySettings, crawler.getSettings());
}

// TODO
TEST_F(TestCrawler, crawl) {
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}