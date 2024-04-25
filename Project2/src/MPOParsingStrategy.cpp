#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <regex>

#include "MPOParsingStrategy.hpp"
#include "MPOElectionData.hpp"
#include "ElectionData.hpp"

MPOParsingStrategy::MPOParsingStrategy()
{}

MPOParsingStrategy::~MPOParsingStrategy()
{}

ElectionData* MPOParsingStrategy::create_election(std::vector<std::string> ballots) {
    std::string election_type;
    int num_seats;
    int num_ballots;
    int num_candidates;

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

    // Read the third line into num_candidates
    if (std::getline(file, line)) {
      std::istringstream(line) >> num_candidates;
    }

    auto MPO_candidates = create_MPO_candidates(file, num_candidates);

    // skip num ballots - need to calculate at end
    std::getline(file, line);

    // extract `Candidate` vector for vote assignment
    std::vector<Candidate*> candidates;
    for (const auto& tuple : MPO_candidates) {
      Candidate* candidate =
          std::get<1>(tuple);  // Get the second element of the tuple
      candidates.push_back(candidate);
    }

    assign_votes_to_candidates(file, candidates);

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
            
            assign_votes_to_candidates(next_file, candidates);

            next_file.close();
        }

    }

    // assign candidates to respective party objects
    std::vector<Party*> mpo_parties = create_MPO_parties(MPO_candidates);

    for (const auto& party : mpo_parties) {
        num_ballots += party->get_total_votes();
    }

    ElectionData* mpo_election_data =
        new MPOElectionData(mpo_parties, num_seats, num_ballots);
    return mpo_election_data;

}

std::vector<std::tuple<std::string, Candidate*>> MPOParsingStrategy::create_MPO_candidates(std::ifstream& file, int numCands) {
    std::vector<std::tuple<std::string, Candidate*>> candidates;
    std::string line;

    // Assume all data is on a single line
    if (std::getline(file, line)) {
        std::regex entry_regex("\\[([^,]+),\\s*([^\\]]+)\\]");  // Matches [name, party]
        std::smatch matches;

        std::string::const_iterator search_start(line.cbegin());
        while (std::regex_search(search_start, line.cend(), matches, entry_regex)) {
            std::string name = matches[1].str();
            std::string party = matches[2].str();
            Candidate* candidate = new MPOCandidate(name);

            candidates.push_back(std::make_tuple(party, candidate));
            search_start = matches.suffix().first;  // Continue to the end of the last match
        }
    }
    return candidates;
}

void MPOParsingStrategy::assign_votes_to_candidates(std::ifstream& file, std::vector<Candidate*> candidates) {
    std::string line;

    // Read each line until the end of the file
    while (std::getline(file, line)) {
        auto tokens =
            tokenize_lines(line);  // Tokenize the line to separate the votes

        // Iterate through each token to find the vote
        for (size_t i = 0; i < tokens.size(); ++i) {
        // Check if the token represents a vote (i.e., the token is "1")
        if (!tokens.at(i).empty() && tokens.at(i) == "1") {
            // If the position matches a candidate, add a vote to that candidate
            if (i < candidates.size()) {
            candidates.at(i)->set_num_votes(candidates.at(i)->get_num_votes() +
                                            1);
            }
        }
        }
    }
}

std::vector<Party*> MPOParsingStrategy::create_MPO_parties(std::vector<std::tuple<std::string, Candidate*>> candidates) {
    std::vector<Party*> parties;

    // Temporary storage for party names and candidates
    std::vector<std::string> party_names;
    std::vector<std::vector<Candidate*>> partyCandidates;

    // Organize candidates by their party names
    for (const auto& tuple : candidates) {
        const std::string& party_name = std::get<0>(tuple);
        Candidate* candidate = std::get<1>(tuple);

        auto it = std::find(party_names.begin(), party_names.end(),
                            party_name);  // establish iterator
        if (it == party_names.end()) {
        // If party name not found, add a new entry
        party_names.push_back(party_name);
        partyCandidates.push_back({candidate});
        } else {
        // If party name found, add candidate to existing party
        size_t index = std::distance(party_names.begin(), it);  // find index
        partyCandidates.at(index).push_back(candidate);         // add at index
        }
    }

    // Create Party objects based on organized data
    for (size_t i = 0; i < party_names.size(); ++i) {
        Party* party = new MPOParty(partyCandidates.at(i), party_names.at(i));
        parties.push_back(party);
    }

    return parties;

}