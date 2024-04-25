#include <gtest/gtest.h>

#include "../src/include/ElectionDataParser.hpp"
// #include "../src/include/MPOElectionData.hpp"

TEST(MPOElectionDataUnitTest, SingleFile) {
    ElectionData* election1 = ElectionDataParser::create_election("../testing/test_data/mpo_example_1.csv");
    ElectionData* election2 = ElectionDataParser::create_election("../testing/test_data/mpo_example_2.csv");
    ASSERT_FALSE(election1 == nullptr);
    ASSERT_FALSE(election2 == nullptr);

    std::string output;

    testing::internal::CaptureStdout();
    election1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "> 3 Pike, D - WINNER\n> 2 Foster, D - WINNER\n2 Borg, R\n1 Jones, R\n1 Smith, I\n0 Deutsch, R\n" 
             || output == "> 3 Pike, D - WINNER\n> 2 Borg, R - WINNER\n2 Foster, D\n1 Jones, R\n1 Smith, I\n0 Deutsch, R\n");

    testing::internal::CaptureStdout();
    election2->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, ">5 Q, D - WINNER\n4 FosterLongLongLongLongLongLongName, D\n");
}

TEST(MPOElectionDataUnitTest, MultipleFiles) {
    ElectionData* election1 = ElectionDataParser::create_election(std::vector({
        "../testing/test_data/mpo_mult1_1.csv",
        "../testing/test_data/mpo_mult1_2.csv"
    }));
    ElectionData* election2 = ElectionDataParser::create_election(std::vector({
        "../testing/test_data/mpo_mult2_1.csv",
        "../testing/test_data/mpo_mult2_2.csv",
        "../testing/test_data/mpo_mult2_3.csv"
    }));
    ASSERT_FALSE(election1 == nullptr);
    ASSERT_FALSE(election2 == nullptr);

    std::string output;

    testing::internal::CaptureStdout();
    election1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "> 6 Pike, D - WINNER\n> 3 Foster, D - WINNER\n3 Deutsch, R\n"
             || output == "> 6 Pike, D - WINNER\n> 3 Deutsch, R - WINNER\n3 Foster, D\n");

    testing::internal::CaptureStdout();
    election2->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "> 3 Deutsch, R - WINNER\n> 3 Bingus, D - WINNER\n2 Pike, D\n2 Foster, D\n1 D, R\n1 Tingle, L\n");
}
