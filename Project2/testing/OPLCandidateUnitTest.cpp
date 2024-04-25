#include <gtest/gtest.h>

#include "../src/include/OPLCandidate.hpp"


TEST(OPLCandidateUnitTest, DefaultTest) { 
    OPLCandidate* def = nullptr;
    EXPECT_EQ(def, nullptr);
}

TEST(OPLCandidateUnitTest, getNameTest){
    OPLCandidate* joe = new OPLCandidate ("Joe Schmo");
    EXPECT_EQ ("Joe Schmo", joe->get_name());
    OPLCandidate* sam = new OPLCandidate("Sam Politician");
    EXPECT_EQ ("Sam Politician", sam->get_name());
}

TEST(OPLCandidateUnitTest, getWinnerTest){
    OPLCandidate* steven = new OPLCandidate ("Steven Carter");
    EXPECT_EQ(false, steven->get_winner());
    steven->set_winner(true);
    EXPECT_EQ(true, steven->get_winner());
}

TEST(OPLCandidateUnitTest, setWinnerTest){
    OPLCandidate* jenna = new OPLCandidate("Jenna America");
    EXPECT_EQ(false, jenna->get_winner());
    jenna->set_winner(true);
    EXPECT_EQ(true, jenna->get_winner());
    jenna->set_winner(false);
    EXPECT_EQ(false, jenna->get_winner());
    EXPECT_NE(true, jenna->get_winner());
}

TEST(OPLCandidateUnitTest, toStringTest) {
    OPLCandidate* tom = new OPLCandidate("Tom Clancy");
    tom->set_num_votes(5);
    EXPECT_EQ("5 Tom Clancy", tom->to_string());
    tom->set_winner(true);
    EXPECT_EQ("> 5 Tom Clancy - WINNER", tom->to_string());
    EXPECT_NE("5 Tom Clancy", tom->to_string());
}

TEST(OPLCandidateUnitTest, getandsetNumVotesTest) {
    OPLCandidate* jerry = new OPLCandidate("Jerry Seinfeld");
    EXPECT_EQ(0, jerry->get_num_votes());
    jerry->set_num_votes(6);
    EXPECT_EQ(6, jerry->get_num_votes());
    jerry->set_num_votes(0);
    EXPECT_EQ(0, jerry->get_num_votes());

}
