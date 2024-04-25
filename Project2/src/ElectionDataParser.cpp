#include "ElectionDataParser.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "ElectionData.hpp"
#include "CPLElectionData.hpp"
#include "OPLElectionData.hpp"
#include "MPOElectionData.hpp"
#include "MVElectionData.hpp"

#include "OPLParsingStrategy.hpp"
#include "CPLParsingStrategy.hpp"
#include "MPOParsingStrategy.hpp"
#include "MVParsingStrategy.hpp"

ElectionData* ElectionDataParser::create_election(std::vector<std::string> ballots) {

  std::string election_type;

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

    ElectionParsingStrategy* strategy = nullptr;

    if (election_type == "OPL") {
        strategy = new OPLParsingStrategy(); 
    }
    else if (election_type == "CPL") {
        strategy = new CPLParsingStrategy(); 
    }
    else if (election_type == "MPO") {
        strategy = new MPOParsingStrategy(); 
    }
    else if (election_type == "MV"){
        strategy = new MVParsingStrategy();
    }
    else {
        std::cout << "\nWARNING: System does not support this election type yet\n";
        return nullptr;
    }

    return strategy->create_election(ballots);
}

ElectionData* ElectionDataParser::create_election(std::string ballot) {
    std::vector<std::string> ballots;
    ballots.push_back(ballot);
    return create_election(ballots);
}
