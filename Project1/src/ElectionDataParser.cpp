#include "ElectionDataParser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "CPLElectionData.hpp"
#include "ElectionData.hpp"
#include "OPLElectionData.hpp"

std::vector<std::string> ElectionDataParser::tokenize_lines(std::string line) {
  std::vector<std::string> tokens;
  std::istringstream stream(line);
  std::string token;

  while (std::getline(stream, token, ',')) {
    // Remove leading and trailing white spaces
    token.erase(0, token.find_first_not_of(" \t\r\n"));
    token.erase(token.find_last_not_of(" \t\r\n") + 1);
    tokens.push_back(token);
  }

  // gets the value after the final comma
  if (!line.empty() && line.back() == ',') {
    tokens.push_back("");
  }

  return tokens;
}

std::vector<std::tuple<std::string, Candidate*>>
ElectionDataParser::create_OPL_candidates(std::ifstream& file, int numCands) {
  std::vector<std::tuple<std::string, Candidate*>> candidates;
  std::string line;

  for (int i = 0; i < numCands; i++) {
    if (std::getline(file, line)) {
      auto tokens = tokenize_lines(line);  // party, name
      if (!tokens.empty()) {
        std::string party = tokens.at(0);  // party name
        std::string name = tokens.at(1);   // candidate name
        Candidate* candidate = new OPLCandidate(name);
        candidates.push_back(std::make_tuple(party, candidate));
      }
    }
  }
  return candidates;
}

void ElectionDataParser::assign_votes_to_candidates(
    std::ifstream& file, std::vector<Candidate*> candidates) {
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

std::vector<Party*> ElectionDataParser::create_OPL_parties(
    std::vector<std::tuple<std::string, Candidate*>> candidates) {
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
    Party* party = new OPLParty(partyCandidates.at(i), party_names.at(i));
    parties.push_back(party);
  }

  return parties;
}

std::vector<Party*> ElectionDataParser::create_CPL_parties(std::ifstream& file,
                                                           int num_parties) {
  std::vector<Party*> parties;
  std::string line;

  for (int i = 0; i < num_parties; i++) {
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

void ElectionDataParser::assign_votes_to_parties(std::ifstream& file,
                                                 std::vector<Party*> parties) {
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

ElectionData* ElectionDataParser::create_election(std::string filename) {
  std::string election_type;
  int num_seats;
  int num_ballots;

  std::ifstream file(filename);
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

  // Read the third line into num_ballots
  if (std::getline(file, line)) {
    std::istringstream(line) >> num_ballots;
  }

  if (election_type == "OPL") {
    int num_candidates;

    // Read the fourth line into num_candidates
    if (std::getline(file, line)) {
      std::istringstream(line) >> num_candidates;
    }

    auto OPL_candidates = create_OPL_candidates(file, num_candidates);

    // extract `Candidate` vector for vote assignment
    std::vector<Candidate*> candidates;
    for (const auto& tuple : OPL_candidates) {
      Candidate* candidate =
          std::get<1>(tuple);  // Get the second element of the tuple
      candidates.push_back(candidate);
    }

    assign_votes_to_candidates(file, candidates);

    // assign candidates to respective party objects
    auto opl_parties = create_OPL_parties(OPL_candidates);

    file.close();

    ElectionData* opl_election_data =
        new OPLElectionData(opl_parties, num_seats, num_ballots);
    return opl_election_data;

  } else {
    int num_parties;

    // Read the fourth line into num_parties
    if (std::getline(file, line)) {
      std::istringstream(line) >> num_parties;
    }

    auto cpl_parties = create_CPL_parties(file, num_parties);

    assign_votes_to_parties(file, cpl_parties);

    file.close();
    ElectionData* cpl_election_data =
        new CPLElectionData(cpl_parties, num_seats, num_ballots);
    return cpl_election_data;
  }
}