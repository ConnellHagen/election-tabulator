#include <gtest/gtest.h>

#include "../src/include/ElectionData.hpp"
#include "../src/include/Party.hpp"

// TEST(ElectionDataUnitTest, breaktieTest) {
//     int num1 = ElectionData::break_tie(5);
//     EXPECT_GE(num1, 0);
//     EXPECT_LE(num1, 4);
//     int num2 = ElectionData::break_tie(72);
//     EXPECT_GE(num2, 0);
//     EXPECT_LE(num2, 71);
//     int num3 = ElectionData::break_tie(2);
//     EXPECT_GE(num3, 0);
//     EXPECT_LE(num3, 1);
// }