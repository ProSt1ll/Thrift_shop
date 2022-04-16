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
class TestMenu : public ::testing::Test {
public:


    void SetUp() {
    }

    void TearDown() {
    }
};


TEST_F(TestServer, get_response) {
}
TEST_F(TestServer, start_accept) {
}
TEST_F(TestServer,send_request) {
}
TEST_F(TestServer,run) {
}
TEST_F(TestServer,stop) {
}

TEST_F(TestManagment, get_product) {
}

TEST_F(TestManagment, create_html) {
}


int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}