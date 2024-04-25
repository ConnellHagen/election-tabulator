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

    // 100000_votes_cpl.csv
    testing::internal::CaptureStdout();
    clock_t t = clock();
    ElectionData* cpl_100000 = ElectionDataParser::create_election("../testing/test_data/100000_votes_cpl.csv");
    cpl_100000->display();
    output = testing::internal::GetCapturedStdout();
    const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
    EXPECT_EQ(output, "30257 Republican:\n\t> Allen - WINNER\n\tNikki\n\tTaihui\n29664 Democratic:\n\t> Joe - WINNER\n\tSally\n\tAhmed\n20022 Reform:\n\t> Xinyue - WINNER\n\tNikita\n10516 Independent:\n\tMike\n10029 Green:\n\tBethany\n0 New Wave:\n\tSarah\n");
    EXPECT_TRUE(work_time <= 60 * 4); // this test should take less than 4 minutes to count 100,000 votes
}