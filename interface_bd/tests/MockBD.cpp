#include "../headers/interface_BD.h"
#include "MockBD.h"

using namespace bd;

TEST(TestBI, construstor)
{
    EXPECT_CALL(basedata, MockBI())                
      .Times(AtLeast(1));

    MockBI basedata;
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
