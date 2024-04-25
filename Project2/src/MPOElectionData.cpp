#include "MPOElectionData.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "MPOParty.hpp"
#include "MPOCandidate.hpp"
#include "Party.hpp"

void MPOElectionData::calculate_winners() {
    int remaining_seats = total_seats;
    std::unordered_map<std::string, int> seat_map;
    std::vector<Candidate*> tracker;

    srand(time(0));  // Seeds rand() based on the current time

    // Generate temporary data structure for tracking votes and max seats allowed
    for (int i = 0; i < num_parties; i++) {

        auto temp_candidates = parties.at(i)->get_candidates();
        int temp_num_candidates = temp_candidates.size();

        for(int j = 0; j < temp_num_candidates; j++) {
            Candidate* temp_candidate_object = temp_candidates.at(j);
            tracker.push_back(temp_candidate_object);
        }
    }

    // sort the tracker by votes
    std::sort(tracker.begin(), tracker.end(), [](const Candidate* a, const Candidate* b) {
        return a->get_num_votes() > b->get_num_votes();
    });
    

    int num_candidates = tracker.size();

    int i = 0;

    while (remaining_seats > 0 && i < num_candidates) {  // Allocate seats and handle ties
    
        int num_ties = 1;

        while (i + num_ties < num_candidates &&
            tracker.at(i)->get_num_votes() ==
                tracker.at(i + num_ties)->get_num_votes() ) {  // Check for tied votes
            num_ties++;
        }

        int seats_to_assign = std::min(remaining_seats, num_ties);

        // Break ties if needed and assign seats to tied candidates
        std::vector<int> tie_indices = ElectionData::break_tie(num_ties);

        if (num_ties > 1) {  // Prepare tie-breaker logging information

        std::stringstream candidates_involved;
        for (int ti = 0; ti < num_ties; ++ti) {
            if (ti > 0) candidates_involved << ", ";
            candidates_involved << (tracker[i + ti])->get_name();
        }

        std::string array_produced = "";
        for (unsigned long int j = 0; j < tie_indices.size(); j++) {
            array_produced += std::to_string(tie_indices.at(j));
            if (j != tie_indices.size() - 1)
                array_produced += ", ";
        }

        int random_seed = rand();
        // Log tie-breaker details
        audit_log.add_line("TIE BREAKER INFO | PARTY SEAT ALLOCATION");
        audit_log.add_line("Tie breaker between [" + candidates_involved.str() +
                            "] for " + std::to_string(seats_to_assign) + " seats");
        audit_log.add_line(
            "Random seed generated: " + std::to_string(random_seed) +
            ", Results from sample #1001...");
        audit_log.add_line("Randomized array produced: [" + array_produced +
                            "]");
        }

        std::stringstream winners; // for logging tie winners

        for (int j = 0; j < seats_to_assign; ++j) {
            int winner_index = tie_indices[j];
            if (!tracker.at(i + winner_index)->get_winner()) {

                tracker.at(i + winner_index)->set_winner(true);

                std::string winner_name = tracker.at(i + winner_index)->get_name();
                if (j > 0) winners << ", ";
                winners << winner_name;
                
                remaining_seats--;
                
                }
        }

        if (num_ties > 1) {
        audit_log.add_line("Winner(s) of the tie breaker: [" + winners.str() +
                            "]" + "\n");
        }

        i += num_ties;
  }

}


void MPOElectionData::add_audit_header() {
  audit_log.add_line("Election Type: MPO");
  audit_log.add_line("Total Votes: " + std::to_string(total_ballots));
  audit_log.add_line("Seats Up for Election: " + std::to_string(total_seats));
  audit_log.add_line("Votes per Guaranteed Seat: " + std::to_string(quota));
  audit_log.add_line("");
}

MPOElectionData::MPOElectionData(std::vector<Party*> parties, int total_seats,
                                 int total_ballots)
    : ElectionData(parties, total_seats, total_ballots,
                   std::ceil(static_cast<double>(total_ballots) /
                             static_cast<double>(total_seats))) {
  add_audit_header();
  calculate_winners();
  sort_parties();
}

MPOElectionData::~MPOElectionData() {
  for (Party* party : parties) {
      for (Candidate* candidate: party->get_candidates()) {
        delete candidate;
      }  
    delete party;
  }
}
