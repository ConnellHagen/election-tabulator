#include "Party.hpp"

#include <string>
#include <vector>

#include "Candidate.hpp"

Party::Party(std::vector<Candidate*> candidates, std::string name)
    : candidates(candidates), name(name), total_votes(0), seats_allocated(0) {}

Party::~Party() {}

std::string Party::to_string() {
  std::string party_string = "";

  party_string += std::to_string(total_votes) + " " + name + ":\n";
  for (Candidate* c : candidates) {
    party_string += "\t" + c->to_string() + "\n";
  }

  return party_string;
}

void Party::sort_candidates() {}