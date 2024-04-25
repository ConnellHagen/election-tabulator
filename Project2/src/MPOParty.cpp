#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "MPOParty.hpp"
#include "ElectionData.hpp"
#include "AuditLog.hpp"

MPOParty::MPOParty(std::vector<Candidate*> candidates, std::string name)
    : Party(candidates, name) {
  srand(time(0));
  this->calculate_total_votes();
}

MPOParty::~MPOParty() {}

void MPOParty::calculate_total_votes() {
  // loop through candidates, summing votes into total_votes
  for (long unsigned int i = 0; i < candidates.size(); i++) {
    total_votes += candidates.at(i)->get_num_votes();
  }
}

void MPOParty::sort_candidates() {
  std::sort(candidates.begin(), candidates.end(),
            MPOCandidate::compare_ptr_to_Candidate);
}
