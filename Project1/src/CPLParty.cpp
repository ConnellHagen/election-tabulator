#include "CPLParty.hpp"

CPLParty::CPLParty(std::vector<Candidate*> candidates, std::string name)
    : Party(candidates, name) {}

CPLParty::~CPLParty() {}

void CPLParty::assign_seat_winners(int seats) {
  // if more seats provided than candidates, sets seat count to # candidates
  if (seats > static_cast<int>(candidates.size())) {
    seats = candidates.size();
  }

  for (int i = 0; i < seats; i++) {
    candidates.at(i)->set_winner(true);
  }
}
