#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "CPLParsingStrategy.hpp"
#include "CPLElectionData.hpp"
#include "ElectionData.hpp"

CPLParsingStrategy::CPLParsingStrategy()
{}

CPLParsingStrategy::~CPLParsingStrategy()
{}

ElectionData* CPLParsingStrategy::create_election(std::vector<std::string> ballots) {
    std::string election_type;
    int num_seats;
    int num_ballots;
    int num_parties;

    std::ifstream file(ballots[0]);
    std::string line;

    // Error handling
    if (!file.is_open()) {
        return nullptr;
    }

    // Read the first line into election_type
    if (std::getline(file, line)) {
        election_type = line;
    }

    // Read the second line into num_seats
    if (std::getline(file, line)) {
        std::istringstream(line) >> num_seats;
    }

    // skip num ballots - need to calculate at end
    std::getline(file, line);

    // Read the fourth line into num_parties
    if (std::getline(file, line)) {
      std::istringstream(line) >> num_parties;
    }

    auto cpl_parties = create_CPL_parties(file, num_parties);

    assign_votes_to_parties(file, cpl_parties);

    file.close();

    //check for additional files, add ballots if so.
    int num_files = ballots.size(); 
    if(num_files > 1) {

        for (int i = 1; i < num_files; i++) {
            std::ifstream next_file(ballots[i]);
            
            // Error handling for the next file
            if (!next_file.is_open()) {
                continue; // Skip to the next file if it cannot be opened
            }

            // Skip to line where ballots start (assuming it's the 5th line)
            for (int j = 0; j < 4; j++) {
                std::getline(next_file, line); // Discard lines until reaching the 5th line
            }
            
            assign_votes_to_parties(next_file, cpl_parties);

            next_file.close();
        }

    }

    for (const auto& party : cpl_parties) {
        num_ballots += party->get_total_votes();
    }

    ElectionData* cpl_election_data =
        new CPLElectionData(cpl_parties, num_seats, num_ballots);
    return cpl_election_data;
}

std::vector<Party*> CPLParsingStrategy::create_CPL_parties(std::ifstream& file, int numParties) {
    std::vector<Party*> parties;
    std::string line;

    for (int i = 0; i < numParties; i++) {
        if (std::getline(file, line)) {
        auto tokens = tokenize_lines(line);  // party, name, name, name, ...

        if (!tokens.empty()) {
            std::string party_name = tokens.at(0);  // party name

            // create candidate vector from rest of line
            std::vector<Candidate*> candidates;
            for (long unsigned int j = 1; j < tokens.size(); j++) {
            Candidate* temp_cand = new CPLCandidate(tokens.at(j));
            candidates.push_back(temp_cand);
            }

            // create party object and push onto vector
            Party* temp_party = new CPLParty(candidates, party_name);
            parties.push_back(temp_party);
        }
        }
    }
    return parties;
}

void CPLParsingStrategy::assign_votes_to_parties(std::ifstream& file, std::vector<Party*> parties){
    std::string line;

    // read each line until the end of the file
    while (std::getline(file, line)) {
        // tokenize the line to separate the votes
        auto tokens = tokenize_lines(line);

        // iterate through each token to find the vote
        for (size_t i = 0; i < tokens.size(); ++i) {
            // check if the token represents a vote (i.e., the token is "1")
            if (!tokens.at(i).empty() && tokens.at(i) == "1") {
                // if the position matches a candidate, add a vote to that candidate
                if (i < parties.size()) {
                parties.at(i)->set_total_votes(parties.at(i)->get_total_votes() + 1);
                }
            }
        }
    }
}