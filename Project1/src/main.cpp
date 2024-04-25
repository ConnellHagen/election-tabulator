#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "CPLCandidate.hpp"
#include "CPLElectionData.hpp"
#include "CPLParty.hpp"
#include "Candidate.hpp"
#include "ElectionDataParser.hpp"
#include "Party.hpp"

int main(int argc, char* argv[]) {
  std::string ballots;

  if (argc == 1) {
    std::cout << "Please Enter the File Path of the Ballot File: ";
    std::cin >> ballots;
    std::cout << std::endl;
  } else if (argc == 2) {
    ballots = std::string(argv[1]);
  } else {
    std::cout << "Usage: ./election [file_name]\nOR ./election\n";
  }

  // test if file exists
  std::ifstream f(ballots);
  bool exists = f.good();
  f.close();

  // exit program on invalid file
  if (!exists) {
    std::cout << "Invalid File Path." << std::endl;
    exit(0);
  }

  // calculate and display election results
  ElectionData* election = ElectionDataParser::create_election(ballots);
  election->display();

  // generate an audit file, if the user chooses
  char audit_input;
  std::cout << "Would You Like to Generate an Audit File? (y/n): ";
  std::cin >> audit_input;
  std::cout << std::endl;

  if (audit_input == 'y' || audit_input == 'Y') election->generate_audit_file();
}
