#include <gtest/gtest.h>

#include "../src/include/ElectionDataParser.hpp"
#include "../src/include/CPLElectionData.hpp"
#include "../src/include/Party.hpp"
#include "../src/include/CPLParty.hpp"
#include "../src/include/Candidate.hpp"
#include "../src/include/CPLCandidate.hpp"


TEST(OPLElectionDataUnitTest, Display) {
    std::string output;

    std::vector<std::string> file_paths = { "../testing/test_data/2_party_opl.csv" };
    ElectionData* std_case_1 = ElectionDataParser::create_election(file_paths);

    // sys_test1_opl.csv
    testing::internal::CaptureStdout();
    std_case_1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "6 Republican:\n\t> 4 Alawa - WINNER\n\t2 Etta\n3 Democrat:\n\t> 2 Pike - WINNER\n\t1 Lucy\n\t0 Beiye\n");
}

TEST(OPLElectionDataUnitTest, TimeLimitTest) {
    std::string output;
    testing::internal::CaptureStdout();
    clock_t t = clock();
    ElectionData* opl_100000 = ElectionDataParser::create_election("../testing/test_data/100000_votes_opl.csv");
    opl_100000->display();
    output = testing::internal::GetCapturedStdout();
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    EXPECT_EQ(output, "69997 Republican:\n\t> 49995 Alawa - WINNER\n\t20002 Etta\n29994 Democrat:\n\t> 19993 Pike - WINNER\n\t10001 Lucy\n\t0 Beiye\n");
    EXPECT_TRUE(work_time <= 60 * 4); // this test should take less than 4 minutes to count 100,000 votes
}

TEST(OPLElectionDataUnitTest, MultipleFiles1) {
    std::string output;
    ElectionData* opl1 = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/opl_mult1_1.csv","../testing/test_data/opl_mult1_2.csv","../testing/test_data/opl_mult1_3.csv","../testing/test_data/opl_mult1_4.csv"}));

    testing::internal::CaptureStdout();
    opl1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "24 Republican:\n\t> 13 Etta - WINNER\n\t11 Alawa\n17 Democrat:\n\t> 9 Pike - WINNER\n\t8 Lucy\n\t0 Beiye\n");
}

TEST(OPLElectionDataUnitTest, MultipleFiles2) {
    std::string output;
    ElectionData* opl1 = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/opl_mult2_1.csv","../testing/test_data/opl_mult2_2.csv"}));

    testing::internal::CaptureStdout();
    opl1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "7 Democratic:\n\t> 7 Gary - WINNER\n");
}
