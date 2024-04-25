#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "OPLParty.hpp"
#include "ElectionData.hpp"
#include "AuditLog.hpp"

OPLParty::OPLParty(std::vector<Candidate*> candidates, std::string name)
    : Party(candidates, name) {
  srand(time(0));
  this->calculate_total_votes();
}

OPLParty::~OPLParty() {}

void OPLParty::calculate_total_votes() {
  // loop through candidates, summing votes into total_votes
  for (long unsigned int i = 0; i < candidates.size(); i++) {
    total_votes += candidates.at(i)->get_num_votes();
  }
}

void OPLParty::assign_seat_winners(int seats, AuditLog* log) {
  // Sort candidates based on num_votes, descending
  std::sort(candidates.begin(), candidates.end(),
            [](const Candidate* a, const Candidate* b) {
              return a->get_num_votes() > b->get_num_votes();
            });

  int remaining_seats = seats;
  int i = 0;
  int candidates_size = static_cast<int>(candidates.size());

  while (remaining_seats > 0 && i < candidates_size) {
    // Count the number of candidates with the same number of votes as the
    // current candidate
    int num_ties = 1;
    while (i + num_ties < candidates_size &&
           candidates[i]->get_num_votes() ==
               candidates[i + num_ties]->get_num_votes()) {
      num_ties++;
    }



    // Determine how many seats to assign among the tied candidates
    int seats_to_assign = std::min(remaining_seats, num_ties);

    std::vector<std::string> winners; // for logging tie winners

    // Break ties if needed and assign seats to tied candidates
    std::vector<int> tie_indices = ElectionData::break_tie(num_ties);
    for (int j = 0; j < seats_to_assign; ++j) {
      int winner_index = tie_indices[j];
      if (!candidates.at(i + winner_index)->get_winner()) {
        candidates.at(i + winner_index)->set_winner(true);
        winners.push_back(candidates.at(i + winner_index)->get_name());
        remaining_seats--;
      }
    }

    // write to log information relating to the tie
    if (num_ties > 1) {
        std::string tie_audit_header = "Tie Between: ";
        for (int j = i; j < i + num_ties; j++) {
            tie_audit_header += candidates.at(j)->get_name();
            if (j != i + num_ties - 1)
                tie_audit_header += ", ";
        }
        tie_audit_header += " for " + std::to_string(seats_to_assign) + " Seat(s)";

        std::string winners_str = "Winners: ";
        for (unsigned long int j = 0; j < winners.size(); j++) {
            winners_str += winners.at(i);
            if (j != winners.size() - 1)
                winners_str += ", ";
        }

        log->add_line(tie_audit_header);
        log->add_line(winners_str);
        log->add_line("");
    }
 

    i += num_ties;
  }
}

void OPLParty::sort_candidates() {
  std::sort(candidates.begin(), candidates.end(),
            OPLCandidate::compare_ptr_to_Candidate);
}
