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

class TestClothe : public ::testing::Test {
public:


    void SetUp() {
    }

    void TearDown() {
    }
};

class TestTemplateParameters : public ::testing::Test {
public:


    void SetUp() {
    }

    void TearDown() {
    }
};

class TestSite : public ::testing::Test {
public:


    void SetUp() {
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

TEST_F(TestClothe, constructors) {
}

TEST_F(TestClothe, gets) {
}

TEST_F(TestClothe, sets) {
}

TEST_F(TestClothe, operatorAssignment) {
}

TEST_F(TestClothe, isEmpty) {
}

TEST_F(TestClothe, getJson) {
}

// TestTemplateParameters

TEST_F(TestTemplateParameters, constructors) {
}

TEST_F(TestTemplateParameters, gets) {
}

TEST_F(TestTemplateParameters, sets) {
}

// TestSite

TEST_F(TestSite, constructors) {
}

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