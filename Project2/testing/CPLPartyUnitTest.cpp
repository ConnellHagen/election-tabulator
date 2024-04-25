#include <gtest/gtest.h>
// #include "CPLParty.h" // Include the header file for your CPLParty class
#include "../src/include/CPLParty.hpp"
#include "../src/include/Party.hpp"
#include "../src/include/CPLCandidate.hpp"

class CPLPartyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for creating candidates if necessary
        candidates.push_back(new CPLCandidate("Candidate 1"));
        candidates.push_back(new CPLCandidate("Candidate 2"));
        candidates.push_back(new CPLCandidate("Candidate 3"));
    }

    void TearDown() override {
        // Clean up any test case setup
        for (auto* candidate : candidates) {
            delete candidate;
        }
        candidates.clear();
    }

    std::vector<Candidate*> candidates;
};

TEST_F(CPLPartyTest, ConstructorTest) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    EXPECT_EQ(party->get_name(), "Party 1");
    auto partyCandidates = party->get_candidates();
    ASSERT_EQ(partyCandidates.size(), candidates.size());
    for (size_t i = 0; i < candidates.size(); ++i) {
        EXPECT_EQ(partyCandidates[i], candidates[i]);
    }
}

TEST_F(CPLPartyTest, GetCandidatesTest) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    auto partyCandidates = party->get_candidates();
    ASSERT_EQ(partyCandidates.size(), 3);
    EXPECT_EQ(partyCandidates[0]->get_name(), "Candidate 1");
    EXPECT_EQ(partyCandidates[1]->get_name(), "Candidate 2");
    EXPECT_EQ(partyCandidates[2]->get_name(), "Candidate 3");
}

TEST_F(CPLPartyTest, GetNameTest) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    EXPECT_EQ(party->get_name(), "Party 1");
}

TEST_F(CPLPartyTest, GetSetTotalVotes) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    party->set_total_votes(5);
    EXPECT_EQ(party->get_total_votes(), 5);
}


TEST_F(CPLPartyTest, AssignSeatWinners_base) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    party->assign_seat_winners(2);
    EXPECT_TRUE(candidates[0]->get_winner());
    EXPECT_TRUE(candidates[1]->get_winner());
    EXPECT_FALSE(candidates[2]->get_winner());
}

TEST_F(CPLPartyTest, AssignSeatWinners_zero) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    party->assign_seat_winners(0);
    EXPECT_FALSE(candidates[0]->get_winner());
    EXPECT_FALSE(candidates[1]->get_winner());
    EXPECT_FALSE(candidates[2]->get_winner());
}

TEST_F(CPLPartyTest, AssignSeatWinners_over) {
    CPLParty* party = new CPLParty(candidates, "Party 1");
    party->assign_seat_winners(4);
    EXPECT_TRUE(candidates[0]->get_winner());
    EXPECT_TRUE(candidates[1]->get_winner());
    EXPECT_TRUE(candidates[2]->get_winner());
}