#include "OPLCandidate.hpp"

#include <string>

OPLCandidate::OPLCandidate(std::string name) : Candidate(name) {
  winner = false;
  num_votes = 0;
}

OPLCandidate::~OPLCandidate() {}

std::string OPLCandidate::to_string() {
  std::string cand_string = std::to_string(num_votes) + " " + name;
  if (winner) {
    cand_string = "> " + cand_string + " - WINNER";
  }
  return cand_string;
}