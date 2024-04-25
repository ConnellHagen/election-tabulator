#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "../src/include/ElectionDataParser.hpp"
#include "../src/include/CPLElectionData.hpp"
#include "../src/include/Party.hpp"
#include "../src/include/CPLParty.hpp"
#include "../src/include/Candidate.hpp"
#include "../src/include/CPLCandidate.hpp"

TEST(CPLElectionDataUnitTest, Display) {
    std::string output;

    ElectionData* cpl_1p = ElectionDataParser::create_election("../testing/test_data/1_person_cpl.csv");
    ElectionData* std_case_1 = ElectionDataParser::create_election("../testing/test_data/sys_test3_cpl.csv");

    // 1_person_cpl.csv
    testing::internal::CaptureStdout();
    cpl_1p->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "2 Democratic:\n\t> Gary - WINNER\n");

    // sys_test3_cpl.csv
    testing::internal::CaptureStdout();
    std_case_1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "3 Democratic:\n\t> Joe - WINNER\n\tSally\n\tAhmed\n2 Republican:\n\t> Allen - WINNER\n\tNikki\n\tTaihui\n2 Reform:\n\t> Xinyue - WINNER\n\tNikita\n1 Green:\n\tBethany\n1 Independent:\n\tMike\n0 New Wave:\n\tSarah\n");
}


TEST(CPLElectionDataUnitTest, TimeLimitTest) {
    std::string output;
    testing::internal::CaptureStdout();
    clock_t t = clock();
    ElectionData* cpl1 = ElectionDataParser::create_election("../testing/test_data/100000_votes_cpl.csv");
    cpl1->display();
    output = testing::internal::GetCapturedStdout();
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    EXPECT_EQ(output, "30257 Republican:\n\t> Allen - WINNER\n\tNikki\n\tTaihui\n29664 Democratic:\n\t> Joe - WINNER\n\tSally\n\tAhmed\n20022 Reform:\n\t> Xinyue - WINNER\n\tNikita\n10516 Independent:\n\tMike\n10029 Green:\n\tBethany\n0 New Wave:\n\tSarah\n");
    EXPECT_TRUE(work_time <= 60 * 4); // this test should take less than 4 minutes to count 100,000 votes
}

TEST(CPLElectionDataUnitTest, MultipleFiles) {
    std::string output;
    ElectionData* cpl1 = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/cpl_mult1_1.csv", "../testing/test_data/cpl_mult1_2.csv"}));
    ElectionData* cpl2 = ElectionDataParser::create_election(std::vector<std::string>({"../testing/test_data/cpl_mult2_1.csv", "../testing/test_data/cpl_mult2_2.csv", "../testing/test_data/cpl_mult2_3.csv"}));

    testing::internal::CaptureStdout();
    cpl1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "6 Democratic:\n\t> Gary - WINNER\n");

    testing::internal::CaptureStdout();
    cpl2->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "8 Democratic:\n\t> Joe - WINNER\n\tSally\n\tAhmed\n7 Green:\n\t> Bethany - WINNER\n4 Reform:\n\t> Xinyue - WINNER\n\tNikita\n3 Republican:\n\tAllen\n\tNikki\n\tTaihui\n2 Independent:\n\tMike\n0 New Wave:\n\tSarah\n");
}