#include <gtest/gtest.h>
// #include <fstream>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <regex>

#include "../src/include/ElectionDataParser.hpp"
#include "../src/include/ElectionData.hpp"
#include "../src/include/MPOParsingStrategy.hpp"
// #include "../src/include/OPLCandidate.hpp"
// #include "../src/include/CPLCandidate.hpp"
// #include "../src/include/OPLParty.hpp"
// #include "../src/include/CPLParty.hpp"
// #include "../src/include/CPLElectionData.hpp"
// #include "../src/include/OPLElectionData.hpp"


// TEST(MPOParsingStrategyTest, createCandidates) {

//     std::vector<std::tuple<std::string, Candidate*>> candidates;
//     std::string line = "[Pike, D], [Foster, D], [Deutsch, R], [Borg, R], [Jones, R], [Smith, I]";
    
//     // Assume all data is on a single line
    
//         std::regex entry_regex("\\[([^,]+),\\s*([^\\]]+)\\]");  // Matches [name, party]
//         std::smatch matches;

//         std::string::const_iterator search_start(line.cbegin());
//         while (std::regex_search(search_start, line.cend(), matches, entry_regex)) {
//             std::string name = matches[1].str();
//             std::string party = matches[2].str();
//             Candidate* candidate = new MPOCandidate(name);
//             candidates.push_back(std::make_tuple(party, candidate));
//             search_start = matches.suffix().first;  // Continue to the end of the last match
//         }

//     EXPECT_EQ(candidates.size(), 6);

//     EXPECT_EQ(std::get<0>(candidates[0]), "D");
//     EXPECT_EQ(std::get<1>(candidates[0])->get_name(), "Pike");

//     EXPECT_EQ(std::get<0>(candidates[1]), "D");
//     EXPECT_EQ(std::get<1>(candidates[1])->get_name(), "Foster");

//     EXPECT_EQ(std::get<0>(candidates[2]), "R");
//     EXPECT_EQ(std::get<1>(candidates[2])->get_name(), "Deutsch");

//     EXPECT_EQ(std::get<0>(candidates[3]), "R");
//     EXPECT_EQ(std::get<1>(candidates[3])->get_name(), "Borg");

//     EXPECT_EQ(std::get<0>(candidates[4]), "R");
//     EXPECT_EQ(std::get<1>(candidates[4])->get_name(), "Jones");

//     EXPECT_EQ(std::get<0>(candidates[5]), "I");
//     EXPECT_EQ(std::get<1>(candidates[5])->get_name(), "Smith");
// }



// TEST_F(ElectionDataParserTest, CreateOPLParties) {
//     std::ifstream file(oplTestFile);
    
//     if (!file.is_open()) {
//         // Handle the error by throwing an exception
//         throw std::runtime_error("Failed to open file: " + oplTestFile);
//     }

//     // Read the first line into electionType
//     if (std::getline(file, line)) {
//         election_type = line;
//     }
//     // Read the second line into numSeats
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numSeats;
//     }
//     // Read the third line into numBallots
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numBallots;
//     }
//     // Read fourth line into numCandidates
//     if (std::getline(file, line)) {
//             std::istringstream(line) >> numCandidates;
//     }
//     std::vector<std::tuple<std::string, Candidate*>> candidates = ElectionDataParser::create_OPL_candidates(file, numCandidates);

//     std::vector<Party*> parties = ElectionDataParser::create_OPL_parties(candidates);

//     EXPECT_EQ(parties.size(), 3);
//     EXPECT_EQ(parties[0]->get_name(), "Democrat");
//     EXPECT_EQ(parties[0]->get_candidates().size(), 3);
//     EXPECT_EQ(parties[1]->get_name(), "Republican");
//     EXPECT_EQ(parties[1]->get_candidates().size(), 2);
//     EXPECT_EQ(parties[2]->get_name(), "Independent1");
//     EXPECT_EQ(parties[2]->get_candidates().size(), 1);

//     for (const auto& candidate : candidates) {
//         delete std::get<1>(candidate);
//     }

//     for (Party* party : parties) {
//         delete party;
//     }

//     file.close();
// }

// TEST_F(ElectionDataParserTest, CreateCPLParties) {
//     std::ifstream file(cplTestFile);
    
//     if (!file.is_open()) {
//         // Handle the error by throwing an exception
//         throw std::runtime_error("Failed to open file: " + cplTestFile);
//     }

//     // Read the first line into electionType
//     if (std::getline(file, line)) {
//         election_type = line;
//     }
//     // Read the second line into numSeats
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numSeats;
//     }
//     // Read the third line into numBallots
//     if (std::getline(file, line)) {
//         std::istringstream(line) >> numBallots;
//     }
//     // Read fourth line into numCandidates
//     if (std::getline(file, line)) {
//             std::istringstream(line) >> numParties;
//     }
//     std::vector<Party*> parties = ElectionDataParser::create_CPL_parties(file, numParties);
//     file.close();

//     EXPECT_EQ(parties.size(), 6);
//     EXPECT_EQ(parties[0]->get_name(), "Democratic");
//     EXPECT_EQ(parties[0]->get_candidates().size(), 3);
//     EXPECT_EQ(parties[1]->get_name(), "Republican");
//     EXPECT_EQ(parties[1]->get_candidates().size(), 3);
//     EXPECT_EQ(parties[2]->get_name(), "New Wave");
//     EXPECT_EQ(parties[2]->get_candidates().size(), 1);
//     EXPECT_EQ(parties[3]->get_name(), "Reform");
//     EXPECT_EQ(parties[3]->get_candidates().size(), 2);
//     EXPECT_EQ(parties[4]->get_name(), "Green");
//     EXPECT_EQ(parties[4]->get_candidates().size(), 1);
//     EXPECT_EQ(parties[5]->get_name(), "Independent");
//     EXPECT_EQ(parties[5]->get_candidates().size(), 1);

//     for (Party* party : parties) {
//         for (Candidate* candidate : party->get_candidates()) {
//             delete candidate;
//         }
//         delete party;
//     }
// }

// // TEST_F(ElectionDataParserTest, AssignVotesToParties) {
// //     std::ifstream file(cplTestFile);
    
// //     if (!file.is_open()) {
// //         // Handle the error by throwing an exception
// //         throw std::runtime_error("Failed to open file: " + cplTestFile);
// //     }

// //     // Read the first line into electionType
// //     if (std::getline(file, line)) {
// //         election_type = line;
// //     }
// //     // Read the second line into numSeats
// //     if (std::getline(file, line)) {
// //         std::istringstream(line) >> numSeats;
// //     }
// //     // Read the third line into numBallots
// //     if (std::getline(file, line)) {
// //         std::istringstream(line) >> numBallots;
// //     }
// //     // Read fourth line into numCandidates
// //     if (std::getline(file, line)) {
// //             std::istringstream(line) >> numParties;
// //     }
// //     std::vector<Party*> parties = ElectionDataParser::create_CPL_parties(file, numParties);

// //     ElectionDataParser::assign_votes_to_parties(file, parties);
// //     file.close();

// //     EXPECT_EQ(parties[0]->get_total_votes(), 3);
// //     EXPECT_EQ(parties[1]->get_total_votes(), 2);
// //     EXPECT_EQ(parties[2]->get_total_votes(), 0);
// //     EXPECT_EQ(parties[3]->get_total_votes(), 2);
// //     EXPECT_EQ(parties[4]->get_total_votes(), 1);
// //     EXPECT_EQ(parties[5]->get_total_votes(), 1);

// //     for (Party* party : parties) {
// //         for (Candidate* candidate : party->get_candidates()) {
// //             delete candidate;
// //         }
// //         delete party;
// //     }
// // }


// //create_election testing is system level testing