#include "MPOCandidate.hpp"

#include <string>

MPOCandidate::MPOCandidate(std::string name) : Candidate(name) {
  winner = false;
  num_votes = 0;
}

MPOCandidate::~MPOCandidate() {}

std::string MPOCandidate::to_string() {
  std::string cand_string = std::to_string(num_votes) + " " + name;
  if (winner) {
    cand_string = "> " + cand_string + " - WINNER";
  }
  return cand_string;
}