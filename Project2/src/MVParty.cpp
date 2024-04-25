#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

#include "MVParty.hpp"
#include "ElectionData.hpp"
#include "AuditLog.hpp"

MVParty::MVParty(std::vector<Candidate*> candidates, std::string name)
    : Party(candidates, name) {
  srand(time(0));
  this->calculate_total_votes();
}

MVParty::~MVParty() {}

void MVParty::calculate_total_votes() {
  // loop through candidates, summing votes into total_votes
  for (long unsigned int i = 0; i < candidates.size(); i++) {
    total_votes += candidates.at(i)->get_num_votes();
  }
}

void MVParty::sort_candidates() {
  std::sort(candidates.begin(), candidates.end(),
            MVCandidate::compare_ptr_to_Candidate);
}
