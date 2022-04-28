#include <gtest/gtest.h>
#include "../Headers/Crawler.h"
#include "../Headers/Site.h"
#include "../Headers/Clothe.h"
#include "Mocks.h"

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


    void SetUp() {
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
}

TEST_F(TestSite, sets) {
}

TEST_F(TestSite, deletes) {
}

TEST_F(TestSite, operatorEquality) {
}

TEST_F(TestSite, resetSettings) {
}

TEST_F(TestSite, getSettings) {
    json emptySettings = {
            {"chapterMap",   json::array()},
            {"parameterMap", json::array()}
    };
    EXPECT_EQ(emptySettings, siteEmpty.getSettings());

    EXPECT_EQ(settings, site.getSettings());
}

TEST_F(TestSite, crawl) {
}

// TestCrawler

TEST_F(TestCrawler, constructors) {
}

TEST_F(TestCrawler, adds) {
}

TEST_F(TestCrawler, gets) {
}

TEST_F(TestCrawler, deletes) {
}

TEST_F(TestCrawler, getSettigs) {
}

TEST_F(TestCrawler, resetSettigs) {
}

TEST_F(TestCrawler, crawl) {
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}