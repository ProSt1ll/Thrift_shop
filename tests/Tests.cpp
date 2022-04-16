#include <iostream>
#include "Mocks.h"
#include <gtest/gtest.h>
class TestServer : public ::testing::Test {
public:


    void SetUp() {
    }

    void TearDown() {
    }
};

class TestManagment : public ::testing::Test {
public:


    void SetUp() {
    }

    void TearDown() {
    }
};


TEST_F(TestServer, get_response) {
}

TEST_F(TestManagment, get_product) {
}

TEST_F(TestManagment, create_html) {
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}