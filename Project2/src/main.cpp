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

// checks if a file exists
bool file_exists(std::string file) {
    std::ifstream f(file);
    bool exists = f.good();
    f.close();
    return exists;
}

// handles the taking of input, and returns a vector of valid paths to ballot files
std::vector<std::string> take_ballot_input() {
    std::vector<std::string> ballots;

    std::cout << std::endl; // clear a line for readability

    while (true) {
        std::cout << "Please Enter the File Path of a Ballot File: ";
        std::string potential_ballot;
        std::cin >> potential_ballot;

        if (!file_exists(potential_ballot)) {
            // exit program on invalid file
            std::cout << "ERROR: File not Found / Invalid Path" << std::endl;
            exit(0);
        }

        ballots.push_back(potential_ballot);

        std::cout << "Would You Like to Add Another File? (y/n): ";
        char response;
        std::cin >> response;
        if (response == 'n' || response == 'N')
            break;
        std::cout << std::endl;
    }

    return ballots;
}

int main(int argc, char* argv[]) {

    std::vector<std::string> ballots;

    if (argc == 1) // no files input on command line
        ballots = take_ballot_input();
    else // files input on command line
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (file_exists(arg))
                ballots.push_back(arg);
        }
    
    // calculate and display election results
    ElectionData* election = ElectionDataParser::create_election(ballots);
    
    if (election == nullptr) {
        std::cout << "WARNING: Create election failed, terminating...\n";
        return 0;
    }

    election->display();

    // generate an audit file, if the user chooses
    char audit_input;
    std::cout << "Would You Like to Generate an Audit File? (y/n): ";
    std::cin >> audit_input;
    std::cout << std::endl;

    if (audit_input == 'y' || audit_input == 'Y')
        election->generate_audit_file();
  
    delete election;
}