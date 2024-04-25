#include <gtest/gtest.h>
#include "../src/include/OPLParty.hpp"
#include "../src/include/Party.hpp"
#include "../src/include/OPLCandidate.hpp"

class OPLPartyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for creating candidates if necessary
        candidates.push_back(new OPLCandidate("Candidate 1"));
        candidates.push_back(new OPLCandidate("Candidate 2"));
        candidates.push_back(new OPLCandidate("Candidate 3"));
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

TEST_F(OPLPartyTest, ConstructorTest) {
    OPLParty* party = new OPLParty(candidates, "Party 1");
    EXPECT_EQ(party->get_name(), "Party 1");
    auto partyCandidates = party->get_candidates();
    ASSERT_EQ(partyCandidates.size(), candidates.size());
    for (size_t i = 0; i < candidates.size(); ++i) {
        EXPECT_EQ(partyCandidates[i], candidates[i]);
    }
}

TEST_F(OPLPartyTest, GetCandidatesTest) {
    OPLParty* party = new OPLParty(candidates, "Party 1");
    auto partyCandidates = party->get_candidates();
    ASSERT_EQ(partyCandidates.size(), 3);
    EXPECT_EQ(partyCandidates[0]->get_name(), "Candidate 1");
    EXPECT_EQ(partyCandidates[1]->get_name(), "Candidate 2");
    EXPECT_EQ(partyCandidates[2]->get_name(), "Candidate 3");
}

TEST_F(OPLPartyTest, GetNameTest) {
    OPLParty* party = new OPLParty(candidates, "Party 1");
    EXPECT_EQ(party->get_name(), "Party 1");
}

TEST_F(OPLPartyTest, GetSetTotalVotes) {
    OPLParty* party = new OPLParty(candidates, "Party 1");
    party->set_total_votes(5);
    EXPECT_EQ(party->get_total_votes(), 5);
}

TEST_F(OPLPartyTest, GetTotalVotesTest) {
    // Create candidates with different vote counts
    candidates[0]->set_num_votes(10);
    candidates[1]->set_num_votes(20);
    candidates[2]->set_num_votes(30);

    OPLParty* party = new OPLParty(candidates, "Party 1");
    
    // Calculate expected total votes
    int expected_total_votes = 10 + 20 + 30;

    EXPECT_EQ(party->get_total_votes(), expected_total_votes);
}

TEST_F(OPLPartyTest, AssignSeatWinners_singleSeat) {
    // Set vote counts for candidates
    candidates[0]->set_num_votes(30);
    candidates[1]->set_num_votes(20);
    candidates[2]->set_num_votes(10);

    OPLParty* party = new OPLParty(candidates, "Party 1");
    party->assign_seat_winners(1);

    // Only the candidate with the highest votes should win the seat
    EXPECT_TRUE(candidates[0]->get_winner());
    EXPECT_FALSE(candidates[1]->get_winner());
    EXPECT_FALSE(candidates[2]->get_winner());
}

TEST_F(OPLPartyTest, AssignSeatWinners_multipleSeats) {
    // Set vote counts for candidates
    candidates[0]->set_num_votes(30);
    candidates[1]->set_num_votes(25);
    candidates[2]->set_num_votes(20);

    OPLParty* party = new OPLParty(candidates, "Party 1");
    party->assign_seat_winners(2);

    // Top 2 candidates should win the seats
    EXPECT_TRUE(candidates[0]->get_winner());
    EXPECT_TRUE(candidates[1]->get_winner());
    EXPECT_FALSE(candidates[2]->get_winner());
}

TEST_F(OPLPartyTest, AssignSeatWinners_equalVotes) {
    // Set equal vote counts for candidates
    candidates[0]->set_num_votes(30);
    candidates[1]->set_num_votes(30);
    candidates[2]->set_num_votes(30);

    OPLParty* party = new OPLParty(candidates, "Party 1");
    party->assign_seat_winners(2);

    // Check each candidate's winner status
    int num_winners = 0;
    for (int i = 0; i < static_cast<int>(candidates.size()); i++) {
        if (candidates[i]->get_winner()) {
            // std::cout << std::endl << i << "winner\n"; 
            num_winners++;
        }
    }
    // Ensure exactly two winners are selected
    EXPECT_EQ(num_winners, 2);
}


