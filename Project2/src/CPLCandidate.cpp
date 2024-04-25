#include "CPLCandidate.hpp"

#include <string>

CPLCandidate::CPLCandidate(std::string name) : Candidate(name) {
  winner = false;
}

CPLCandidate::~CPLCandidate() {}

std::string CPLCandidate::to_string() {
  std::string cand_string = name;
  if (winner) {
    cand_string = "> " + cand_string + " - WINNER";
  }
  return cand_string;
}