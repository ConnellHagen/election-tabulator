#include <gtest/gtest.h>

#include "../src/include/OPLElectionData.hpp"
#include "../src/include/ElectionDataParser.hpp"

TEST(OPLElectionDataUnitTest, Display) {
    std::string output;

    ElectionData* std_case_1 = ElectionDataParser::create_election("../testing/test_data/2_party_opl.csv");

    // sys_test1_opl.csv
    testing::internal::CaptureStdout();
    std_case_1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "6 Republican:\n\t> 4 Alawa - WINNER\n\t2 Etta\n3 Democrat:\n\t> 2 Pike - WINNER\n\t1 Lucy\n\t0 Beiye\n");
    
    // 100000_votes_cpl.csv
    testing::internal::CaptureStdout();
    clock_t t = clock();
    ElectionData* opl_100000 = ElectionDataParser::create_election("../testing/test_data/100000_votes_opl.csv");
    opl_100000->display();
    output = testing::internal::GetCapturedStdout();
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    EXPECT_EQ(output, "69997 Republican:\n\t> 49995 Alawa - WINNER\n\t20002 Etta\n29994 Democrat:\n\t> 19993 Pike - WINNER\n\t10001 Lucy\n\t0 Beiye\n");
    EXPECT_TRUE(work_time <= 60 * 4); // this test should take less than 4 minutes to count 100,000 votes
}
