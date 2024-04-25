#include <gtest/gtest.h>

#include "../src/include/ElectionDataParser.hpp"
#include "../src/include/ElectionData.hpp"
#include "../src/include/CPLElectionData.hpp"
#include "../src/include/OPLElectionData.hpp"
#include "../src/include/Party.hpp"

TEST(ElectionDataUnitTest, MultipleElectionsSameRunTest) {
    std::string output;

    // running back to back elections of different types to test for data corruption in all orderings
    ElectionData* elec1 = ElectionDataParser::create_election("../testing/test_data/1_person_cpl.csv");
    ElectionData* elec2 = ElectionDataParser::create_election("../testing/test_data/2_party_opl.csv");
    ElectionData* elec3 = ElectionDataParser::create_election("../testing/test_data/1_person_cpl.csv");

    testing::internal::CaptureStdout();
    elec1->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "2 Democratic:\n\t> Gary - WINNER\n");

    testing::internal::CaptureStdout();
    elec2->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "6 Republican:\n\t> 4 Alawa - WINNER\n\t2 Etta\n3 Democrat:\n\t> 2 Pike - WINNER\n\t1 Lucy\n\t0 Beiye\n");
    
    testing::internal::CaptureStdout();
    elec3->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "2 Democratic:\n\t> Gary - WINNER\n");

    // testing if display method ordering is causing data corruption
    ElectionData* elec4 = ElectionDataParser::create_election("../testing/test_data/1_person_cpl.csv");
    ElectionData* elec5 = ElectionDataParser::create_election("../testing/test_data/2_party_opl.csv");

    testing::internal::CaptureStdout();
    elec5->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "6 Republican:\n\t> 4 Alawa - WINNER\n\t2 Etta\n3 Democrat:\n\t> 2 Pike - WINNER\n\t1 Lucy\n\t0 Beiye\n");
    
    testing::internal::CaptureStdout();
    elec4->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "2 Democratic:\n\t> Gary - WINNER\n");

    testing::internal::CaptureStdout();
    elec5->display();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "6 Republican:\n\t> 4 Alawa - WINNER\n\t2 Etta\n3 Democrat:\n\t> 2 Pike - WINNER\n\t1 Lucy\n\t0 Beiye\n");
    
}

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